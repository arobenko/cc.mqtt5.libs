#include "UnitTestQos0Base.h"

#include "qos0_client.h"

const UnitTestQos0Base::LibFuncs& UnitTestQos0Base::getFuncs()
{
    static LibFuncs funcs;
    funcs.m_alloc = &cc_mqtt5_qos0_client_alloc;
    funcs.m_free = &cc_mqtt5_qos0_client_free;
    funcs.m_tick = &cc_mqtt5_qos0_client_tick;
    funcs.m_process_data = &cc_mqtt5_qos0_client_process_data;
    funcs.m_notify_network_disconnected = &cc_mqtt5_qos0_client_notify_network_disconnected;
    funcs.m_is_network_disconnected = &cc_mqtt5_qos0_client_is_network_disconnected;
    funcs.m_set_default_response_timeout = &cc_mqtt5_qos0_client_set_default_response_timeout;
    funcs.m_get_default_response_timeout = &cc_mqtt5_qos0_client_get_default_response_timeout;
    funcs.m_pub_topic_alias_alloc = &cc_mqtt5_qos0_client_pub_topic_alias_alloc;
    funcs.m_pub_topic_alias_free = &cc_mqtt5_qos0_client_pub_topic_alias_free;
    funcs.m_pub_topic_alias_count = &cc_mqtt5_qos0_client_pub_topic_alias_count;
    funcs.m_pub_topic_alias_is_allocated = &cc_mqtt5_qos0_client_pub_topic_alias_is_allocated;
    funcs.m_set_verify_outgoing_topic_enabled = &cc_mqtt5_qos0_client_set_verify_outgoing_topic_enabled;
    funcs.m_get_verify_outgoing_topic_enabled = &cc_mqtt5_qos0_client_get_verify_outgoing_topic_enabled;
    funcs.m_set_verify_incoming_topic_enabled = &cc_mqtt5_qos0_client_set_verify_incoming_topic_enabled;
    funcs.m_get_verify_incoming_topic_enabled = &cc_mqtt5_qos0_client_get_verify_incoming_topic_enabled;
    funcs.m_set_verify_incoming_msg_subscribed = &cc_mqtt5_qos0_client_set_verify_incoming_msg_subscribed;
    funcs.m_get_verify_incoming_msg_subscribed = &cc_mqtt5_qos0_client_get_verify_incoming_msg_subscribed;
    funcs.m_init_user_prop = &cc_mqtt5_qos0_client_init_user_prop;
    funcs.m_connect_prepare = &cc_mqtt5_qos0_client_connect_prepare;
    funcs.m_connect_init_config_basic = &cc_mqtt5_qos0_client_connect_init_config_basic;
    funcs.m_connect_init_config_will = &cc_mqtt5_qos0_client_connect_init_config_will;
    funcs.m_connect_init_config_extra = &cc_mqtt5_qos0_client_connect_init_config_extra;
    funcs.m_connect_init_config_auth = &cc_mqtt5_qos0_client_connect_init_config_auth;
    funcs.m_connect_init_auth_info = &cc_mqtt5_qos0_client_connect_init_auth_info;
    funcs.m_connect_set_response_timeout = &cc_mqtt5_qos0_client_connect_set_response_timeout;
    funcs.m_connect_get_response_timeout = &cc_mqtt5_qos0_client_connect_get_response_timeout;
    funcs.m_connect_config_basic = &cc_mqtt5_qos0_client_connect_config_basic;
    funcs.m_connect_config_will = &cc_mqtt5_qos0_client_connect_config_will;
    funcs.m_connect_config_extra = &cc_mqtt5_qos0_client_connect_config_extra;
    funcs.m_connect_config_auth = &cc_mqtt5_qos0_client_connect_config_auth;
    funcs.m_connect_add_user_prop = &cc_mqtt5_qos0_client_connect_add_user_prop;
    funcs.m_connect_add_will_user_prop = &cc_mqtt5_qos0_client_connect_add_will_user_prop;
    funcs.m_connect_send = &cc_mqtt5_qos0_client_connect_send;
    funcs.m_connect_cancel = &cc_mqtt5_qos0_client_connect_cancel;
    funcs.m_connect_simple = &cc_mqtt5_qos0_client_connect_simple;
    funcs.m_connect_full = &cc_mqtt5_qos0_client_connect_full;
    funcs.m_is_connected = &cc_mqtt5_qos0_client_is_connected;
    funcs.m_disconnect_prepare = &cc_mqtt5_qos0_client_disconnect_prepare;
    funcs.m_disconnect_init_config = &cc_mqtt5_qos0_client_disconnect_init_config;
    funcs.m_disconnect_config = &cc_mqtt5_qos0_client_disconnect_config;
    funcs.m_disconnect_add_user_prop = &cc_mqtt5_qos0_client_disconnect_add_user_prop;
    funcs.m_disconnect_send = &cc_mqtt5_qos0_client_disconnect_send;
    funcs.m_disconnect_cancel = &cc_mqtt5_qos0_client_disconnect_cancel;
    funcs.m_disconnect = &cc_mqtt5_qos0_client_disconnect;
    funcs.m_subscribe_prepare = &cc_mqtt5_qos0_client_subscribe_prepare;
    funcs.m_subscribe_set_response_timeout = &cc_mqtt5_qos0_client_subscribe_set_response_timeout;
    funcs.m_subscribe_get_response_timeout = &cc_mqtt5_qos0_client_subscribe_get_response_timeout;
    funcs.m_subscribe_init_config_topic = &cc_mqtt5_qos0_client_subscribe_init_config_topic;
    funcs.m_subscribe_init_config_extra = &cc_mqtt5_qos0_client_subscribe_init_config_extra;
    funcs.m_subscribe_config_topic = &cc_mqtt5_qos0_client_subscribe_config_topic;
    funcs.m_subscribe_config_extra = &cc_mqtt5_qos0_client_subscribe_config_extra;
    funcs.m_subscribe_add_user_prop = &cc_mqtt5_qos0_client_subscribe_add_user_prop;
    funcs.m_subscribe_send = &cc_mqtt5_qos0_client_subscribe_send;
    funcs.m_subscribe_cancel = &cc_mqtt5_qos0_client_subscribe_cancel;
    funcs.m_subscribe_simple = &cc_mqtt5_qos0_client_subscribe_simple;
    funcs.m_subscribe_full = &cc_mqtt5_qos0_client_subscribe_full;    
    funcs.m_unsubscribe_prepare = &cc_mqtt5_qos0_client_unsubscribe_prepare;
    funcs.m_unsubscribe_set_response_timeout = &cc_mqtt5_qos0_client_unsubscribe_set_response_timeout;
    funcs.m_unsubscribe_get_response_timeout = &cc_mqtt5_qos0_client_unsubscribe_get_response_timeout;
    funcs.m_unsubscribe_init_config_topic = &cc_mqtt5_qos0_client_unsubscribe_init_config_topic;
    funcs.m_unsubscribe_config_topic = &cc_mqtt5_qos0_client_unsubscribe_config_topic;
    funcs.m_unsubscribe_add_user_prop = &cc_mqtt5_qos0_client_unsubscribe_add_user_prop;
    funcs.m_unsubscribe_send = &cc_mqtt5_qos0_client_unsubscribe_send;
    funcs.m_unsubscribe_cancel = &cc_mqtt5_qos0_client_unsubscribe_cancel;    
    funcs.m_unsubscribe_simple = &cc_mqtt5_qos0_client_unsubscribe_simple;
    funcs.m_unsubscribe_full = &cc_mqtt5_qos0_client_unsubscribe_full;        
    funcs.m_publish_prepare = &cc_mqtt5_qos0_client_publish_prepare;    
    funcs.m_publish_count = &cc_mqtt5_qos0_client_publish_count;    
    funcs.m_publish_init_config_basic = &cc_mqtt5_qos0_client_publish_init_config_basic;
    funcs.m_publish_init_config_extra = &cc_mqtt5_qos0_client_publish_init_config_extra;
    funcs.m_publish_set_response_timeout = &cc_mqtt5_qos0_client_publish_set_response_timeout;
    funcs.m_publish_get_response_timeout = &cc_mqtt5_qos0_client_publish_get_response_timeout;
    funcs.m_publish_set_resend_attempts = &cc_mqtt5_qos0_client_publish_set_resend_attempts;
    funcs.m_publish_get_resend_attempts = &cc_mqtt5_qos0_client_publish_get_resend_attempts;
    funcs.m_publish_config_basic = &cc_mqtt5_qos0_client_publish_config_basic;
    funcs.m_publish_config_extra = &cc_mqtt5_qos0_client_publish_config_extra;
    funcs.m_publish_add_user_prop = &cc_mqtt5_qos0_client_publish_add_user_prop;
    funcs.m_publish_send = &cc_mqtt5_qos0_client_publish_send;
    funcs.m_publish_cancel = &cc_mqtt5_qos0_client_publish_cancel;    
    funcs.m_publish_was_initiated = &cc_mqtt5_qos0_client_publish_was_initiated;    
    funcs.m_publish_set_out_of_order_allowed = &cc_mqtt5_qos0_client_publish_set_out_of_order_allowed;    
    funcs.m_publish_get_out_of_order_allowed = &cc_mqtt5_qos0_client_publish_get_out_of_order_allowed;    
    funcs.m_publish_simple = &cc_mqtt5_qos0_client_publish_simple;    
    funcs.m_publish_full = &cc_mqtt5_qos0_client_publish_full; 
    funcs.m_publish_set_ordering = &cc_mqtt5_qos0_client_publish_set_ordering;
    funcs.m_publish_get_ordering = &cc_mqtt5_qos0_client_publish_get_ordering;         
    funcs.m_reauth_prepare = &cc_mqtt5_qos0_client_reauth_prepare;    
    funcs.m_reauth_init_config_auth = &cc_mqtt5_qos0_client_reauth_init_config_auth;
    funcs.m_reauth_set_response_timeout = &cc_mqtt5_qos0_client_reauth_set_response_timeout;
    funcs.m_reauth_get_response_timeout = &cc_mqtt5_qos0_client_reauth_get_response_timeout;
    funcs.m_reauth_config_auth = &cc_mqtt5_qos0_client_reauth_config_auth;
    funcs.m_reauth_add_user_prop = &cc_mqtt5_qos0_client_reauth_add_user_prop;
    funcs.m_reauth_send = &cc_mqtt5_qos0_client_reauth_send;
    funcs.m_reauth_cancel = &cc_mqtt5_qos0_client_reauth_cancel;
    funcs.m_reauth = &cc_mqtt5_qos0_client_reauth;
    funcs.m_set_next_tick_program_callback = &cc_mqtt5_qos0_client_set_next_tick_program_callback;
    funcs.m_set_cancel_next_tick_wait_callback = &cc_mqtt5_qos0_client_set_cancel_next_tick_wait_callback;
    funcs.m_set_send_output_data_callback = &cc_mqtt5_qos0_client_set_send_output_data_callback;
    funcs.m_set_broker_disconnect_report_callback = &cc_mqtt5_qos0_client_set_broker_disconnect_report_callback;
    funcs.m_set_message_received_report_callback = &cc_mqtt5_qos0_client_set_message_received_report_callback;
    funcs.m_set_error_log_callback = &cc_mqtt5_qos0_client_set_error_log_callback;
    return funcs;
}