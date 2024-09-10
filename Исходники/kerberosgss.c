int authenticate_gss_server_step(gss_server_state *state, const char *challenge)
{
    OM_uint32 maj_stat;
    OM_uint32 min_stat;
    gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;
    gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;
    int ret = AUTH_GSS_CONTINUE;
    
    // Always clear out the old response
    if (state->response != NULL)
    {
        free(state->response);
        state->response = NULL;
    }
    
    // If there is a challenge (data from the server) we need to give it to GSS
    if (challenge && *challenge)
    {
        size_t len;
        input_token.value = base64_decode(challenge, &len);
        input_token.length = len;
    }
    else
    {
        PyErr_SetString(KrbException_class, "No challenge parameter in request from client");
        ret = AUTH_GSS_ERROR;
        goto end;
    }
    
    Py_BEGIN_ALLOW_THREADS
    maj_stat = gss_accept_sec_context(&min_stat,
                                      &state->context,
                                      state->server_creds,
                                      &input_token,
                                      GSS_C_NO_CHANNEL_BINDINGS,
                                      &state->client_name,
                                      NULL,
                                      &output_token,
                                      NULL,
                                      NULL,
                                      &state->client_creds);
    Py_END_ALLOW_THREADS
    
    if (GSS_ERROR(maj_stat))
    {
        set_gss_error(maj_stat, min_stat);
        ret = AUTH_GSS_ERROR;
        goto end;
    }
    
    // Grab the server response to send back to the client
    if (output_token.length)
    {
        state->response = base64_encode((const unsigned char *)output_token.value, output_token.length);;
        maj_stat = gss_release_buffer(&min_stat, &output_token);
    }
    
    // Get the user name
    maj_stat = gss_display_name(&min_stat, state->client_name, &output_token, NULL);
    if (GSS_ERROR(maj_stat))
    {
        set_gss_error(maj_stat, min_stat);
        ret = AUTH_GSS_ERROR;
        goto end;
    }
    state->username = (char *)malloc(output_token.length + 1);
    strncpy(state->username, (char*) output_token.value, output_token.length);
    state->username[output_token.length] = 0;
    
    // Get the target name if no server creds were supplied
    if (state->server_creds == GSS_C_NO_CREDENTIAL)
    {
        gss_name_t target_name = GSS_C_NO_NAME;
        maj_stat = gss_inquire_context(&min_stat, state->context, NULL, &target_name, NULL, NULL, NULL, NULL, NULL);
        if (GSS_ERROR(maj_stat))
        {
            set_gss_error(maj_stat, min_stat);
            ret = AUTH_GSS_ERROR;
            goto end;
        }
        maj_stat = gss_display_name(&min_stat, target_name, &output_token, NULL);
        if (GSS_ERROR(maj_stat))
        {
            set_gss_error(maj_stat, min_stat);
            ret = AUTH_GSS_ERROR;
            goto end;
        }
        state->targetname = (char *)malloc(output_token.length + 1);
        strncpy(state->targetname, (char*) output_token.value, output_token.length);
        state->targetname[output_token.length] = 0;
    }

    ret = AUTH_GSS_COMPLETE;
    
end:
    if (output_token.length)
        gss_release_buffer(&min_stat, &output_token);
    if (input_token.value)
        free(input_token.value);
    return ret;
}