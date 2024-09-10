/*
 * __wt_connection_close --
 *	Close a connection handle.
 */
int
__wt_connection_close(WT_CONNECTION_IMPL *conn)
{
	WT_CONNECTION *wt_conn;
	WT_DECL_RET;
	WT_DLH *dlh;
	WT_SESSION_IMPL *s, *session;
	u_int i;

	wt_conn = &conn->iface;
	session = conn->default_session;

	/* Shut down transactions (wait for in-flight operations to complete. */
	WT_TRET(__wt_txn_global_shutdown(session));

	/* Shut down the subsystems, ensuring workers see the state change. */
	F_SET(conn, WT_CONN_CLOSING);
	WT_FULL_BARRIER();

	/*
	 * Clear any pending async operations and shut down the async worker
	 * threads and system before closing LSM.
	 */
	WT_TRET(__wt_async_flush(session));
	WT_TRET(__wt_async_destroy(session));

	/*
	 * Shut down server threads other than the eviction server, which is
	 * needed later to close btree handles.  Some of these threads access
	 * btree handles, so take care in ordering shutdown to make sure they
	 * exit before files are closed.
	 */
	WT_TRET(__wt_lsm_manager_destroy(session));

	/*
	 * Once the async and LSM threads exit, we shouldn't be opening any
	 * more files.
	 */
	F_SET(conn, WT_CONN_CLOSING_NO_MORE_OPENS);
	WT_FULL_BARRIER();

	WT_TRET(__wt_checkpoint_server_destroy(session));
	WT_TRET(__wt_statlog_destroy(session, true));
	WT_TRET(__wt_sweep_destroy(session));

	/* The eviction server is shut down last. */
	WT_TRET(__wt_evict_destroy(session));

	/* Shut down the lookaside table, after all eviction is complete. */
	WT_TRET(__wt_las_destroy(session));

	/* Close open data handles. */
	WT_TRET(__wt_conn_dhandle_discard(session));

	/* Shut down metadata tracking. */
	WT_TRET(__wt_meta_track_destroy(session));

	/*
	 * Now that all data handles are closed, tell logging that a checkpoint
	 * has completed then shut down the log manager (only after closing
	 * data handles).  The call to destroy the log manager is outside the
	 * conditional because we allocate the log path so that printlog can
	 * run without running logging or recovery.
	 */
	if (FLD_ISSET(conn->log_flags, WT_CONN_LOG_ENABLED) &&
	    FLD_ISSET(conn->log_flags, WT_CONN_LOG_RECOVER_DONE))
		WT_TRET(__wt_txn_checkpoint_log(
		    session, true, WT_TXN_LOG_CKPT_STOP, NULL));
	WT_TRET(__wt_logmgr_destroy(session));

	/* Free memory for collators, compressors, data sources. */
	WT_TRET(__wt_conn_remove_collator(session));
	WT_TRET(__wt_conn_remove_compressor(session));
	WT_TRET(__wt_conn_remove_data_source(session));
	WT_TRET(__wt_conn_remove_encryptor(session));
	WT_TRET(__wt_conn_remove_extractor(session));

	/* Disconnect from shared cache - must be before cache destroy. */
	WT_TRET(__wt_conn_cache_pool_destroy(session));

	/* Discard the cache. */
	WT_TRET(__wt_cache_destroy(session));

	/* Discard transaction state. */
	__wt_txn_global_destroy(session);

	/* Close the lock file, opening up the database to other connections. */
	if (conn->lock_fh != NULL)
		WT_TRET(__wt_close(session, &conn->lock_fh));

	/* Close any file handles left open. */
	WT_TRET(__wt_close_connection_close(session));

	/*
	 * Close the internal (default) session, and switch back to the dummy
	 * session in case of any error messages from the remaining operations
	 * while destroying the connection handle.
	 */
	if (session != &conn->dummy_session) {
		WT_TRET(session->iface.close(&session->iface, NULL));
		session = conn->default_session = &conn->dummy_session;
	}

	/*
	 * The session split stash, hazard information and handle arrays aren't
	 * discarded during normal session close, they persist past the life of
	 * the session. Discard them now.
	 */
	if (!F_ISSET(conn, WT_CONN_LEAK_MEMORY))
		if ((s = conn->sessions) != NULL)
			for (i = 0; i < conn->session_size; ++s, ++i) {
				__wt_free(session, s->dhhash);
				__wt_stash_discard_all(session, s);
				__wt_free(session, s->hazard);
			}

	/* Destroy the file-system configuration. */
	if (conn->file_system != NULL && conn->file_system->terminate != NULL)
		WT_TRET(conn->file_system->terminate(
		    conn->file_system, (WT_SESSION *)session));

	/* Close extensions, first calling any unload entry point. */
	while ((dlh = TAILQ_FIRST(&conn->dlhqh)) != NULL) {
		TAILQ_REMOVE(&conn->dlhqh, dlh, q);

		if (dlh->terminate != NULL)
			WT_TRET(dlh->terminate(wt_conn));
		WT_TRET(__wt_dlclose(session, dlh));
	}

	/* Destroy the handle. */
	__wt_connection_destroy(conn);

	return (ret);
}