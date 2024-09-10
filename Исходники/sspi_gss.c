UINT32 SSPI_GSSAPI sspi_gss_add_cred(
    UINT32* minor_status,
    sspi_gss_cred_id_t input_cred_handle,
    sspi_gss_name_t desired_name,
    sspi_gss_OID desired_mech,
    sspi_gss_cred_usage_t cred_usage,
    UINT32 initiator_time_req,
    UINT32 acceptor_time_req,
    sspi_gss_cred_id_t* output_cred_handle,
    sspi_gss_OID_set* actual_mechs,
    UINT32* initiator_time_rec,
    UINT32* acceptor_time_rec)
{
	SECURITY_STATUS status;
	InitOnceExecuteOnce(&g_Initialized, sspi_GssApiInit, NULL, NULL);

	if (!(g_GssApi && g_GssApi->gss_add_cred))
		return SEC_E_UNSUPPORTED_FUNCTION;

	status = g_GssApi->gss_add_cred(minor_status, input_cred_handle, desired_name, desired_mech,
	                                cred_usage,
	                                initiator_time_req, acceptor_time_req, output_cred_handle, actual_mechs, initiator_time_rec,
	                                acceptor_time_rec);
	WLog_DBG(TAG, "gss_add_cred: %s (0x%08"PRIX32")",
	         GetSecurityStatusString(status), status);
	return status;
}