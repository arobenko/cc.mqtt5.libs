//
// Copyright 2023 - 2024 (C). Alex Robenko. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "AppClient.h"
#include "ProgramOptions.h"

#include <boost/asio.hpp>

namespace cc_mqtt5_client_app
{

class Pub : public AppClient
{
    using Base = AppClient;
public:
    Pub(boost::asio::io_context& io);

    bool start(int argc, const char* argv[]);
private:
    ProgramOptions m_opts;
};

} // namespace cc_mqtt5_client_app
