/* On OSF/1 (Digital Unix), pointers are 64 bits wide; the only exception to this is C programs for which one may
 * specify compiler and link editor options in order to use (and allocate) 32-bit pointers.  However, since C is
 * the only exception and, in particular because the operating system does not support such an exception, the argv
 * array passed to the main program is an array of 64-bit pointers.  Thus the C program needs to declare argv[]
 * as an array of 64-bit pointers and needs to do the same for any pointer it sets to an element of argv[].
 */
int main(int argc, char_ptr_t argv[])
{
	omi_conn_ll	conns;
	bool	  	set_pset();
	int 		ret_val;
	DCL_THREADGBL_ACCESS;

	GTM_THREADGBL_INIT;
	ctxt = NULL;
	common_startup_init(GTCM_SERVER_IMAGE);
	SPRINTF(image_id,"%s=gtcm_server", image_id);
#	ifdef SEQUOIA
	if (!set_pset())
		exit(-1);
#	endif
	/*  Initialize everything but the network */
	err_init(gtcm_exit_ch);
	gtm_chk_dist(argv[0]);
	omi_errno = OMI_ER_NO_ERROR;
	ctxt = ctxt;
	ESTABLISH_RET(omi_dbms_ch, -1);	/* any return value to signify error return */
	gtcm_init(argc, argv);
	gtcm_ltime = gtcm_stime = (int4)time(0);
#	ifdef GTCM_RC
	rc_create_cpt();
#	endif
	REVERT;
	if (OMI_ER_NO_ERROR != omi_errno)
		exit(omi_errno);
	/*  Initialize the network interface */
	if (0 != (ret_val = gtcm_bgn_net(&conns)))	/* Warning - assignment */
	{
		gtcm_rep_err("Error initializing TCP", ret_val);
		gtcm_exi_condition = ret_val;
		gtcm_exit();
	}
	SPRINTF(image_id,"%s(pid=%d) %s %s %s -id %d -service %s",
		image_id,
		omi_pid,
		( history ? "-hist" : "" ),
		( authenticate ? "-auth" : "" ),
		( ping_keepalive ? "-ping" : "" ),
		rc_server_id,
		omi_service
		);
	OPERATOR_LOG_MSG;
	omi_conns = &conns;
	/*  Should be forever, unless an error occurs */
	gtcm_loop(&conns);
	/*  Clean up */
	gtcm_end_net(&conns);
	gtcm_exit();
	return 0;
}