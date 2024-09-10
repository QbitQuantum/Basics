void Test_M2MResourceInstance::test_handle_put_request()
{
    uint8_t value[] = {"name"};
    sn_coap_hdr_s *coap_header = (sn_coap_hdr_s *)malloc(sizeof(sn_coap_hdr_s));
    memset(coap_header, 0, sizeof(sn_coap_hdr_s));

    coap_header->uri_path_ptr = value;
    coap_header->uri_path_len = sizeof(value);

    coap_header->msg_code = COAP_MSG_CODE_REQUEST_PUT;

    String *name = new String("name");
    common_stub::int_value = 0;
    m2mbase_stub::string_value = name;

    m2mbase_stub::operation = M2MBase::PUT_ALLOWED;
    m2mbase_stub::uint8_value = 200;

    common_stub::coap_header = (sn_coap_hdr_ *)malloc(sizeof(sn_coap_hdr_));
    memset(common_stub::coap_header,0,sizeof(sn_coap_hdr_));

    coap_header->payload_ptr = (uint8_t*)malloc(1);

    coap_header->options_list_ptr = (sn_coap_options_list_s*)malloc(sizeof(sn_coap_options_list_s));
    coap_header->options_list_ptr->uri_query_ptr = value;
    coap_header->options_list_ptr->uri_query_len = sizeof(value);

    coap_header->content_type_ptr = (uint8_t*)malloc(1);
    coap_header->content_type_len = 1;
    *coap_header->content_type_ptr = 99;
    m2mtlvdeserializer_stub::bool_value = true;

    m2mbase_stub::bool_value = false;

    sn_coap_hdr_s *coap_response = NULL;
    coap_response = resource_instance->handle_put_request(NULL,coap_header,handler);
    CHECK( coap_response != NULL);
    if(coap_response) {
        if(coap_response->content_type_ptr) {
            free(coap_response->content_type_ptr);
            coap_response->content_type_ptr = NULL;
        }
    }

    free(coap_header->options_list_ptr);
    coap_header->options_list_ptr = NULL;

    coap_response = resource_instance->handle_put_request(NULL,coap_header,handler);
    CHECK( coap_response != NULL);
    if(coap_response) {
        if(coap_response->content_type_ptr) {
            free(coap_response->content_type_ptr);
            coap_response->content_type_ptr = NULL;
        }
    }

    m2mtlvdeserializer_stub::bool_value = false;

    coap_response = resource_instance->handle_put_request(NULL,coap_header,handler);

    CHECK( coap_response != NULL);
    if(coap_response) {
        if(coap_response->content_type_ptr) {
            free(coap_response->content_type_ptr);
            coap_response->content_type_ptr = NULL;
        }
    }

    *coap_header->content_type_ptr = 100;

    coap_response = resource_instance->handle_put_request(NULL,coap_header,handler);

    CHECK( coap_response != NULL);
    if(coap_response) {
        if(coap_response->content_type_ptr) {
            free(coap_response->content_type_ptr);
            coap_response->content_type_ptr = NULL;
        }
    }

    m2mbase_stub::bool_value = true;

    coap_response = resource_instance->handle_put_request(NULL,coap_header,handler);

    CHECK( coap_response != NULL);
    if(coap_response) {
        if(coap_response->content_type_ptr) {
            free(coap_response->content_type_ptr);
            coap_response->content_type_ptr = NULL;
        }
    }

    m2mbase_stub::operation = M2MBase::NOT_ALLOWED;

    coap_response = resource_instance->handle_put_request(NULL,coap_header,handler);

    CHECK( coap_response != NULL);
    if(coap_response) {
        if(coap_response->content_type_ptr) {
            free(coap_response->content_type_ptr);
            coap_response->content_type_ptr = NULL;
        }
    }

    coap_response = resource_instance->handle_put_request(NULL,NULL,handler);

    CHECK( coap_response != NULL);
    if(coap_response) {
        if(coap_response->content_type_ptr) {
            free(coap_response->content_type_ptr);
            coap_response->content_type_ptr = NULL;
        }
    }

    free(coap_header->content_type_ptr);
    free(coap_header->options_list_ptr);
    free(coap_header->payload_ptr);
    free(common_stub::coap_header);
    delete name;
    free(coap_header);

    m2mtlvdeserializer_stub::clear();
    common_stub::clear();
    m2mbase_stub::clear();
}