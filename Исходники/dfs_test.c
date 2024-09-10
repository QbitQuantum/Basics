/* receives take place in an event, so we are free to process
 * the request list without fear of getting things out-of-order
 */
static void recv_dfs(int status, orte_process_name_t* sender,
                     opal_buffer_t* buffer, orte_rml_tag_t tag,
                     void* cbdata)
{
    orte_dfs_cmd_t cmd;
    int32_t cnt;
    orte_dfs_request_t *dfs, *dptr;
    opal_list_item_t *item;
    int remote_fd, rc;
    int64_t i64;
    uint64_t rid;
    orte_dfs_tracker_t *trk;

    /* unpack the command this message is responding to */
    cnt = 1;
    if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &cmd, &cnt, ORTE_DFS_CMD_T))) {
        ORTE_ERROR_LOG(rc);
        return;
    }

    opal_output_verbose(1, orte_dfs_base_framework.framework_output,
                        "%s recvd cmd %d from sender %s",
                        ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), (int)cmd,
                        ORTE_NAME_PRINT(sender));

    switch (cmd) {
    case ORTE_DFS_OPEN_CMD:
        /* unpack the request id */
        cnt = 1;
        if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &rid, &cnt, OPAL_UINT64))) {
            ORTE_ERROR_LOG(rc);
            return;
        }
        /* unpack the remote fd */
        cnt = 1;
        if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &remote_fd, &cnt, OPAL_INT))) {
            ORTE_ERROR_LOG(rc);
            return;
        }
        /* search our list of requests to find the matching one */
        dfs = NULL;
        for (item = opal_list_get_first(&requests);
             item != opal_list_get_end(&requests);
             item = opal_list_get_next(item)) {
            dptr = (orte_dfs_request_t*)item;
            if (dptr->id == rid) {
                /* as the request has been fulfilled, remove it */
                opal_list_remove_item(&requests, item);
                dfs = dptr;
                break;
            }
        }
        if (NULL == dfs) {
            opal_output_verbose(1, orte_dfs_base_framework.framework_output,
                                "%s recvd open file - no corresponding request found for local fd %d",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), local_fd);
            ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
            return;
        }

        /* if the remote_fd < 0, then we had an error, so return
         * the error value to the caller
         */
        if (remote_fd < 0) {
            opal_output_verbose(1, orte_dfs_base_framework.framework_output,
                                "%s recvd open file response error file %s [error: %d]",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                                dfs->uri, remote_fd);
            if (NULL != dfs->open_cbfunc) {
                dfs->open_cbfunc(remote_fd, dfs->cbdata);
            }
            /* release the request */
            OBJ_RELEASE(dfs);
            return;
        }
        /* otherwise, create a tracker for this file */
        trk = OBJ_NEW(orte_dfs_tracker_t);
        trk->requestor.jobid = ORTE_PROC_MY_NAME->jobid;
        trk->requestor.vpid = ORTE_PROC_MY_NAME->vpid;
        trk->host_daemon.jobid = sender->jobid;
        trk->host_daemon.vpid = sender->vpid;
        trk->filename = strdup(dfs->uri);
        /* define the local fd */
        trk->local_fd = local_fd++;
        /* record the remote file descriptor */
        trk->remote_fd = remote_fd;
        /* add it to our list of active files */
        opal_list_append(&active_files, &trk->super);
        /* return the local_fd to the caller for
         * subsequent operations
         */
        opal_output_verbose(1, orte_dfs_base_framework.framework_output,
                            "%s recvd open file completed for file %s [local fd: %d remote fd: %d]",
                            ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                            dfs->uri, trk->local_fd, remote_fd);
        if (NULL != dfs->open_cbfunc) {
            dfs->open_cbfunc(trk->local_fd, dfs->cbdata);
        }
        /* release the request */
        OBJ_RELEASE(dfs);
        break;

    case ORTE_DFS_SIZE_CMD:
        /* unpack the request id for this request */
        cnt = 1;
        if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &rid, &cnt, OPAL_UINT64))) {
            ORTE_ERROR_LOG(rc);
            return;
        }
        /* search our list of requests to find the matching one */
        dfs = NULL;
        for (item = opal_list_get_first(&requests);
             item != opal_list_get_end(&requests);
             item = opal_list_get_next(item)) {
            dptr = (orte_dfs_request_t*)item;
            if (dptr->id == rid) {
                /* request was fulfilled, so remove it */
                opal_list_remove_item(&requests, item);
                dfs = dptr;
                break;
            }
        }
        if (NULL == dfs) {
            opal_output_verbose(1, orte_dfs_base_framework.framework_output,
                                "%s recvd size - no corresponding request found for local fd %d",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), local_fd);
            ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
            return;
        }
        /* get the size */
        cnt = 1;
        if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &i64, &cnt, OPAL_INT64))) {
            ORTE_ERROR_LOG(rc);
            OBJ_RELEASE(dfs);
            return;
        }
        /* pass it back to the original caller */
        if (NULL != dfs->size_cbfunc) {
            dfs->size_cbfunc(i64, dfs->cbdata);
        }
        /* release the request */
        OBJ_RELEASE(dfs);
        break;

    case ORTE_DFS_SEEK_CMD:
        /* unpack the request id for this read */
        cnt = 1;
        if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &rid, &cnt, OPAL_UINT64))) {
            ORTE_ERROR_LOG(rc);
            return;
        }
        /* search our list of requests to find the matching one */
        dfs = NULL;
        for (item = opal_list_get_first(&requests);
             item != opal_list_get_end(&requests);
             item = opal_list_get_next(item)) {
            dptr = (orte_dfs_request_t*)item;
            if (dptr->id == rid) {
                /* request was fulfilled, so remove it */
                opal_list_remove_item(&requests, item);
                dfs = dptr;
                break;
            }
        }
        if (NULL == dfs) {
            opal_output_verbose(1, orte_dfs_base_framework.framework_output,
                                "%s recvd seek - no corresponding request found for local fd %d",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), local_fd);
            ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
            return;
        }
        /* get the returned offset/status */
        cnt = 1;
        if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &i64, &cnt, OPAL_INT64))) {
            ORTE_ERROR_LOG(rc);
            OBJ_RELEASE(dfs);
            return;
        }
        /* pass it back to the original caller */
        if (NULL != dfs->seek_cbfunc) {
            dfs->seek_cbfunc(i64, dfs->cbdata);
        }
        /* release the request */
        OBJ_RELEASE(dfs);
        break;

    case ORTE_DFS_READ_CMD:
        /* unpack the request id for this read */
        cnt = 1;
        if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &rid, &cnt, OPAL_UINT64))) {
            ORTE_ERROR_LOG(rc);
            return;
        }
        /* search our list of requests to find the matching one */
        dfs = NULL;
        for (item = opal_list_get_first(&requests);
             item != opal_list_get_end(&requests);
             item = opal_list_get_next(item)) {
            dptr = (orte_dfs_request_t*)item;
            if (dptr->id == rid) {
                /* request was fulfilled, so remove it */
                opal_list_remove_item(&requests, item);
                dfs = dptr;
                break;
            }
        }
        if (NULL == dfs) {
            opal_output_verbose(1, orte_dfs_base_framework.framework_output,
                                "%s recvd read - no corresponding request found for local fd %d",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME), local_fd);
            ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
            return;
        }
        /* get the bytes read */
        cnt = 1;
        if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &i64, &cnt, OPAL_INT64))) {
            ORTE_ERROR_LOG(rc);
            OBJ_RELEASE(dfs);
            return;
        }
        if (0 < i64) {
            cnt = i64;
            if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, dfs->read_buffer, &cnt, OPAL_UINT8))) {
                ORTE_ERROR_LOG(rc);
                OBJ_RELEASE(dfs);
                return;
            }
        }
        /* pass them back to the original caller */
        if (NULL != dfs->read_cbfunc) {
            dfs->read_cbfunc(i64, dfs->read_buffer, dfs->cbdata);
        }
        /* release the request */
        OBJ_RELEASE(dfs);
        break;

    case ORTE_DFS_POST_CMD:
        /* unpack the request id for this read */
        cnt = 1;
        if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &rid, &cnt, OPAL_UINT64))) {
            ORTE_ERROR_LOG(rc);
            return;
        }
        /* search our list of requests to find the matching one */
        dfs = NULL;
        for (item = opal_list_get_first(&requests);
             item != opal_list_get_end(&requests);
             item = opal_list_get_next(item)) {
            dptr = (orte_dfs_request_t*)item;
            if (dptr->id == rid) {
                /* request was fulfilled, so remove it */
                opal_list_remove_item(&requests, item);
                dfs = dptr;
                break;
            }
        }
        if (NULL == dfs) {
            opal_output_verbose(1, orte_dfs_base_framework.framework_output,
                                "%s recvd post - no corresponding request found",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
            ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
            return;
        }
        if (NULL != dfs->post_cbfunc) {
            dfs->post_cbfunc(dfs->cbdata);
        }
        OBJ_RELEASE(dfs);
        break;

    case ORTE_DFS_GETFM_CMD:
        /* unpack the request id for this read */
        cnt = 1;
        if (OPAL_SUCCESS != (rc = opal_dss.unpack(buffer, &rid, &cnt, OPAL_UINT64))) {
            ORTE_ERROR_LOG(rc);
            return;
        }
        /* search our list of requests to find the matching one */
        dfs = NULL;
        for (item = opal_list_get_first(&requests);
             item != opal_list_get_end(&requests);
             item = opal_list_get_next(item)) {
            dptr = (orte_dfs_request_t*)item;
            if (dptr->id == rid) {
                /* request was fulfilled, so remove it */
                opal_list_remove_item(&requests, item);
                dfs = dptr;
                break;
            }
        }
        if (NULL == dfs) {
            opal_output_verbose(1, orte_dfs_base_framework.framework_output,
                                "%s recvd getfm - no corresponding request found",
                                ORTE_NAME_PRINT(ORTE_PROC_MY_NAME));
            ORTE_ERROR_LOG(ORTE_ERR_NOT_FOUND);
            return;
        }
        /* return it to caller */
        if (NULL != dfs->fm_cbfunc) {
            dfs->fm_cbfunc(buffer, dfs->cbdata);
        }
        OBJ_RELEASE(dfs);
        break;

    default:
        opal_output(0, "TEST:DFS:RECV WTF");
        break;
    }
}