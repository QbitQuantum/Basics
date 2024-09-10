int latch_overlay_check_latch(latch_overlay_config_data *cfg, char *id) {

    int rc = LATCH_STATUS_UNKNOWN;
    char *account_id = NULL;
    char *response = NULL;
    json_object *json_response = NULL;
    json_object *json_data = NULL;
    json_object *json_operations = NULL;
    json_object *json_application = NULL;
    json_bool json_application_rc = FALSE;
    json_object *json_status = NULL;

    Log1(LDAP_DEBUG_TRACE, LDAP_LEVEL_DEBUG, ">>> %s\n", __func__);

    if (latch_overlay_get_account_id(cfg, id, &account_id) != ERROR) {

        if (account_id != NULL) {

            Log2(LDAP_DEBUG_TRACE, LDAP_LEVEL_DEBUG, "    %s: account_id %s\n", __func__, account_id);

            if (cfg->operation_id == NULL) {
                response = status(account_id);
            } else {
                response = operationStatus(account_id, cfg->operation_id);
            }

            if (response != NULL) {

                Log2(LDAP_DEBUG_TRACE, LDAP_LEVEL_DEBUG, "    %s: response %s\n", __func__, response);

                json_response = json_tokener_parse(response);

                if (json_response != NULL) {

                    if ((json_object_object_get_ex(json_response, "data", &json_data) == TRUE) && (json_data != NULL)) {

                        if ((json_object_object_get_ex(json_data, "operations", &json_operations) == TRUE) && (json_operations != NULL)) {

                            if (cfg->operation_id == NULL) {
                                json_application_rc = json_object_object_get_ex(json_operations, cfg->application_id, &json_application);
                            } else {
                                json_application_rc = json_object_object_get_ex(json_operations, cfg->operation_id, &json_application);
                            }

                            if ((json_application_rc) == TRUE && (json_application != NULL)) {
                                if ((json_object_object_get_ex(json_application, "status", &json_status) == TRUE) && (json_status != NULL)) {
                                    if (json_object_get_string(json_status) != NULL && strcmp("off", json_object_get_string(json_status)) == 0) {
                                        rc = LATCH_STATUS_LOCKED;
                                    } else if (json_object_get_string(json_status) != NULL && strcmp("on", json_object_get_string(json_status)) == 0) {
                                        rc = LATCH_STATUS_UNLOCKED;
                                    }
                                }
                            }

                        }

                    }

                    json_object_put(json_response);

                }

                free(response);

            } else {
                Log1(LDAP_DEBUG_ANY, LDAP_LEVEL_ERR, "    %s: There has been an error communicating with the backend\n", __func__);
            }

            free(account_id);

            if ((rc == LATCH_STATUS_UNKNOWN) && (cfg->sdk_stop_on_error == 1)) {
                Log1(LDAP_DEBUG_ANY, LDAP_LEVEL_ERR, "    %s: No valid response from backend but is required. Returning LATCH_STATUS_LOCKED\n", __func__);
                rc = LATCH_STATUS_LOCKED;
            }

        } else {
            if (cfg->required == 1) {
                Log1(LDAP_DEBUG_ANY, LDAP_LEVEL_ERR, "    %s: User is not paired but Latch is required. Returning LATCH_STATUS_LOCKED\n", __func__);
                rc = LATCH_STATUS_LOCKED;
            }
        }

    } else {
        if (cfg->ldap_stop_on_error == 1) {
            Log1(LDAP_DEBUG_ANY, LDAP_LEVEL_ERR, "    %s: No valid response from the LDAP server but is required. Returning LATCH_STATUS_LOCKED\n", __func__);
            rc = LATCH_STATUS_LOCKED;
        }
    }

    Log1(LDAP_DEBUG_TRACE, LDAP_LEVEL_DEBUG, "<<< %s\n", __func__);

    return rc;

}