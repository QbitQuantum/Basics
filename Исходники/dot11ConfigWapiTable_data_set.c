/**
 * Set the new value.
 *
 * @param rowreq_ctx
 *        Pointer to the users context. You should know how to
 *        manipulate the value from this object.
 * @param WAPIASIPAddress_val
 *        A u_long containing the new value.
 */
int
WAPIASIPAddress_set( dot11ConfigWapiTable_rowreq_ctx *rowreq_ctx, u_long WAPIASIPAddress_val )
{

    DEBUGMSGTL(("verbose:dot11ConfigWapiTable:WAPIASIPAddress_set","called\n"));

    /** should never get a NULL pointer */
    netsnmp_assert(NULL != rowreq_ctx);

/*
 * TODO:245:o: |-> Implement WAPIASIPAddress reverse mapping.
 * If the values for your data type don't exactly match the
 * possible values defined by the mib, you should map them here.
 */
    /*
     * TODO:461:M: |-> Set WAPIASIPAddress value.
     * set WAPIASIPAddress value in rowreq_ctx->data
     */
	int ret = 2;
	char input[DEFAULT_LEN] = {0};
	memset(input,0,DEFAULT_LEN);
	int ret_one = 2;
	int ret_two = 2;
	int ret_three = 2;	
	int rc = MFD_ERROR;

    void *connection = NULL;
    if(SNMPD_DBUS_ERROR == get_instance_dbus_connection(rowreq_ctx->data.parameter, &connection, SNMPD_INSTANCE_MASTER_V3))
        return MFD_ERROR;
    
	ret = config_wlan_service(rowreq_ctx->data.parameter, connection,rowreq_ctx->data.WapiSSID,"disable");
	if(ret == 1)
	{
		INET_NTOA(WAPIASIPAddress_val,input);
		ret_one = config_wapi_auth(rowreq_ctx->data.parameter, connection,rowreq_ctx->data.SecurityID,input,"X.509");
		if (ret_one == 1)
		{   
			ret_two = apply_wlanID(rowreq_ctx->data.parameter, connection,rowreq_ctx->data.SecurityID,rowreq_ctx->data.WapiSSID); 
			if(ret_two == 1)
			{
				ret_three = config_wlan_service(rowreq_ctx->data.parameter, connection,rowreq_ctx->data.WapiSSID,"enable");
				if (ret_three == 1)
				{
				    rowreq_ctx->data.WAPIASIPAddress = WAPIASIPAddress_val;
					rc = MFD_SUCCESS;
				}
				else
				{
					rc = MFD_ERROR;
				}
			}
			else
			{
				rc = MFD_ERROR;
			}					
		}	
		else
		{
			rc = MFD_ERROR;
		}								 	     

	}
	else 
	{
		rc = MFD_ERROR;
	}

    return rc;
} /* WAPIASIPAddress_set */