/**
 * Set the new value.
 *
 * @param rowreq_ctx
 *        Pointer to the users context. You should know how to
 *        manipulate the value from this object.
 * @param AcInterfaceNetMask_val
 *        A u_long containing the new value.
 */
int
AcInterfaceNetMask_set( dot11AcInterfaceTable_rowreq_ctx *rowreq_ctx, u_long AcInterfaceNetMask_val )
{

    DEBUGMSGTL(("verbose:dot11AcInterfaceTable:AcInterfaceNetMask_set","called\n"));

    /** should never get a NULL pointer */
    netsnmp_assert(NULL != rowreq_ctx);

    /*
     * TODO:461:M: |-> Set AcInterfaceNetMask value.
     * set AcInterfaceNetMask value in rowreq_ctx->data
     */

    
    char command[128]   = { 0 };
    char oldmask[32]    = { 0 };
    char newmask[32]    = { 0 };
    char ip[32]         = { 0 };
    
    INET_NTOA(rowreq_ctx->data.AcInterfaceIP, ip);
    INET_NTOA(rowreq_ctx->data.AcInterfaceNetMask, oldmask);
    INET_NTOA(AcInterfaceNetMask_val,newmask);

    int oldMaskbit = 0, newmaskbit = 0;
    oldMaskbit = mask_bit(oldmask);
    newmaskbit = mask_bit(newmask);
    
    int ret = -1;    
    int status = 0;
    
    //delete old info
    memset(command, 0, sizeof(command));
    snprintf(command, sizeof(command) - 1, "sudo del_intf_ip.sh %s %s/%d 1>/dev/null 2>/dev/null",
                rowreq_ctx->data.AcInterfaceName, ip, oldMaskbit);
                
    status = system(command);
    ret = WEXITSTATUS(status);
    if(0 != ret) {
        snmp_log(LOG_WARNING, "delete old mask %s/%d fail\n", ip, oldMaskbit);
        return MFD_ERROR;
    }


    ret = -1;    
    status = 0;
    
    //add new info
    memset(command, 0, sizeof(command));
    snprintf(command, sizeof(command) - 1, "sudo /usr/bin/set_intf_ip.sh %s %s/%d > /dev/null 2>&1",
                rowreq_ctx->data.AcInterfaceName, ip ,newmaskbit);
                
    ret  = system(command);
    if(ret == 0) {
        rowreq_ctx->data.AcInterfaceNetMask = AcInterfaceNetMask_val;
        return  MFD_SUCCESS;
    }

    return MFD_ERROR;
} /* AcInterfaceNetMask_set */