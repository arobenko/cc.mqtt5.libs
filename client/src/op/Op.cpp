//
// Copyright 2023 - 2024 (C). Alex Robenko. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "op/Op.h"

#include "ClientImpl.h"

#include "comms/util/ScopeGuard.h"
#include "comms/cast.h"

#include <algorithm>

namespace cc_mqtt5_client
{

namespace op
{

namespace 
{

static constexpr char TopicSep = '/';
static constexpr char MultLevelWildcard = '#';
static constexpr char SingleLevelWildcard = '+';

} // namespace 



Op::Op(ClientImpl& client) : 
    m_client(client),
    m_responseTimeoutMs(client.configState().m_responseTimeoutMs)
{
}    

void Op::sendMessage(const ProtMessage& msg)
{
    m_client.sendMessage(msg);
}

void Op::terminateOpImpl([[maybe_unused]] CC_Mqtt5AsyncOpStatus status)
{
    opComplete();
}

void Op::opComplete()
{
    m_client.opComplete(this);
}

void Op::doApiGuard()
{
    m_client.doApiGuard();
}

unsigned Op::allocPacketId()
{
    auto& packetId = m_client.sessionState().m_packetId;
    ++packetId;
    static constexpr auto MaxPacketId = std::numeric_limits<std::uint16_t>::max();
    if (MaxPacketId <= packetId) {
        packetId = 1U;
    }

    return packetId;
}

void Op::sendDisconnectWithReason(ClientImpl& client, DiconnectReason reason)
{
    DisconnectMsg disconnectMsg;
    disconnectMsg.field_reasonCode().setExists();
    disconnectMsg.field_propertiesList().setExists();
    disconnectMsg.field_reasonCode().field().setValue(reason);    
    client.sendMessage(disconnectMsg);
}

void Op::sendDisconnectWithReason(DiconnectReason reason)
{
    sendDisconnectWithReason(m_client, reason);
}

void Op::terminationWithReason(ClientImpl& client, DiconnectReason reason)
{
    sendDisconnectWithReason(client, reason);
    client.notifyDisconnected(true);
}

void Op::terminationWithReason(DiconnectReason reason)
{
    terminationWithReason(m_client, reason);
}

void Op::protocolErrorTermination(ClientImpl& client)
{
    terminationWithReason(client, DiconnectReason::ProtocolError);
}

void Op::protocolErrorTermination()
{
    protocolErrorTermination(m_client);
}

void Op::fillUserProps(const PropsHandler& propsHandler, UserPropsList& userProps)
{
    if constexpr (Config::HasUserProps) {    
        userProps.reserve(std::min(propsHandler.m_userProps.size() + userProps.size(), userProps.max_size()));
        auto endIter = propsHandler.m_userProps.end();
        if constexpr (Config::UserPropsLimit > 0U) {
            endIter = propsHandler.m_userProps.begin() + std::min(propsHandler.m_userProps.size(), std::size_t(Config::UserPropsLimit));
        }

        std::transform(
            propsHandler.m_userProps.begin(), endIter, std::back_inserter(userProps),
            [](auto* field)
            {
                return UserPropsList::value_type{field->field_value().field_first().value().c_str(), field->field_value().field_second().value().c_str()};
            });
    }
}

void Op::errorLogInternal(const char* msg)
{
    if constexpr (Config::HasErrorLog) {
        m_client.errorLog(msg);
    }    
}

bool Op::verifySubFilterInternal(const char* filter)
{
    if (Config::HasTopicFormatVerification) {
        if (!m_client.configState().m_verifyOutgoingTopic) {
            return true;
        }

        COMMS_ASSERT(filter != nullptr);
        if (filter[0] == '\0') {
            return false;
        }

        auto pos = 0U;
        int lastSep = -1;
        while (filter[pos] != '\0') {
            auto incPosGuard = 
                comms::util::makeScopeGuard(
                    [&pos]()
                    {
                        ++pos;
                    });

            auto ch = filter[pos];

            if (ch == TopicSep) {
                comms::cast_assign(lastSep) = pos;
                continue;
            }   

            if (ch == MultLevelWildcard) {
                if (filter[pos + 1] != '\0') {
                    errorLog("Multi-level wildcard \'#\' must be last.");
                    return false;
                }

                if (pos == 0U) {
                    return true;
                }

                if ((lastSep < 0) || (static_cast<decltype(lastSep)>(pos - 1U) != lastSep)) {
                    errorLog("Multi-level wildcard \'#\' must follow separator.");
                    return false;
                }

                return true;
            }

            if (ch != SingleLevelWildcard) {
                continue;
            }

            auto nextCh = filter[pos + 1];
            if ((nextCh != '\0') && (nextCh != TopicSep)) {
                errorLog("Single-level wildcard \'+\' must be last of followed by /.");
                return false;                
            }           

            if (pos == 0U) {
                continue;
            }

            if ((lastSep < 0) || (static_cast<decltype(lastSep)>(pos - 1U) != lastSep)) {
                errorLog("Single-level wildcard \'+\' must follow separator.");
                return false;
            }            
        }

        return true;
    }
    else {
        [[maybe_unused]] static constexpr bool ShouldNotBeCalled = false;
        COMMS_ASSERT(ShouldNotBeCalled);
        return false;
    }
}

bool Op::verifyPubTopicInternal(const char* topic, bool outgoing)
{
    if (Config::HasTopicFormatVerification) {
        if (outgoing && (!m_client.configState().m_verifyOutgoingTopic)) {
            return true;
        }

        if ((!outgoing) && (!m_client.configState().m_verifyIncomingTopic)) {
            return true;
        }

        COMMS_ASSERT(topic != nullptr);
        if (topic[0] == '\0') {
            return false;
        }

        if (outgoing && (topic[0] == '$')) {
            errorLog("Cannot start topic with \'$\'.");
            return false;
        }

        auto pos = 0U;
        while (topic[pos] != '\0') {
            auto incPosGuard = 
                comms::util::makeScopeGuard(
                    [&pos]()
                    {
                        ++pos;
                    });

            auto ch = topic[pos];

            if ((ch == MultLevelWildcard) || 
                (ch == SingleLevelWildcard)) {
                errorLog("Wildcards cannot be used in publish topic");
                return false;
            }
        }

        return true;
    }
    else {
        [[maybe_unused]] static constexpr bool ShouldNotBeCalled = false;
        COMMS_ASSERT(ShouldNotBeCalled);
        return false;
    }
}

} // namespace op

} // namespace cc_mqtt5_client
