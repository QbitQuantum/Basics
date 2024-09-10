/**
 * Lookup a user based on a user ID. Calling functions should
 * free the result with authz_free_buffer().
 *
 * @param userid    user name to lookup
 *
 * @return a user info structure or NULL on error
 */
userinfo_t *authz_lookup_user(const char *userid)
{
    struct USER_INFO_23 *buf = NULL;
    userinfo_t *result = NULL;
    NET_API_STATUS status;

    pthread_mutex_lock(&_ctxmtx);

    if (!userid || !_netapictx) {
        pthread_mutex_unlock(&_ctxmtx);
        return NULL;
    }

    status = NetUserGetInfo(_host, userid, 23, (uint8_t **)&buf);
    if (status != NET_API_STATUS_SUCCESS) {
        log_warn("NetApi lookup for user %s failed (%d)", userid, status);
        pthread_mutex_unlock(&_ctxmtx);
        return NULL;
    }

    result = (userinfo_t *)malloc(sizeof(userinfo_t));
    bzero(result, sizeof(userinfo_t));

    result->logon_name = strdup(userid);
    result->display_name = strdup(buf->usri23_full_name);

    ConvertSidToStringSid(buf->usri23_user_sid, &result->sid);

    NetApiBufferFree(buf);
    pthread_mutex_unlock(&_ctxmtx);

    log_debug("found user %s with SID %s", userid, result->sid);
    return result;
}