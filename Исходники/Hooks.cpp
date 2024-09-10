	int handleRequest(request_rec *r) {
		DirConfig *config = getDirConfig(r);
		DirectoryMapper mapper(r, config);
		if (mapper.getBaseURI() == NULL || r->filename == NULL || fileExists(r->filename)) {
			return DECLINED;
		}
		
		try {
			if (mapper.getPublicDirectory().empty()) {
				return reportDocumentRootDeterminationError(r);
			}
		} catch (const FileSystemException &e) {
			return reportFileSystemError(r, e);
		}
		
		int httpStatus = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR);
    		if (httpStatus != OK) {
			return httpStatus;
		}
		
		try {
			this_thread::disable_interruption di;
			this_thread::disable_syscall_interruption dsi;
			apr_bucket_brigade *bb;
			apr_bucket *b;
			Application::SessionPtr session;
			bool expectingUploadData;
			shared_ptr<TempFile> uploadData;
			
			expectingUploadData = ap_should_client_block(r);
			if (expectingUploadData && atol(lookupHeader(r, "Content-Length"))
			                                 > UPLOAD_ACCELERATION_THRESHOLD) {
				uploadData = receiveRequestBody(r);
			}
			
			try {
				const char *defaultUser, *environment, *spawnMethod;
				unsigned int appSpawnerTimeout, frameworkSpawnerTimeout;
				ServerConfig *sconfig;
				
				sconfig = getServerConfig(r->server);
				if (sconfig->defaultUser != NULL) {
					defaultUser = sconfig->defaultUser;
				} else {
					defaultUser = "******";
				}
				if (mapper.getApplicationType() == DirectoryMapper::RAILS) {
					if (config->railsEnv == NULL) {
						environment = DEFAULT_RAILS_ENV;
					} else {
						environment = config->railsEnv;
					}
				} else if (mapper.getApplicationType() == DirectoryMapper::RACK) {
					if (config->rackEnv == NULL) {
						environment = DEFAULT_RACK_ENV;
					} else {
						environment = config->rackEnv;
					}
				} else {
					environment = DEFAULT_WSGI_ENV;
				}
				if (config->spawnMethod == DirConfig::SM_CONSERVATIVE) {
					spawnMethod = "conservative";
				} else {
					spawnMethod = "smart";
				}
				if (config->frameworkSpawnerTimeout < 0) {
					frameworkSpawnerTimeout = 0;
				} else {
					frameworkSpawnerTimeout = config->frameworkSpawnerTimeout;
				}
				if (config->appSpawnerTimeout < 0) {
					appSpawnerTimeout = 0;
				} else {
					appSpawnerTimeout = config->appSpawnerTimeout;
				}
				
				session = applicationPool->get(SpawnOptions(
					canonicalizePath(mapper.getPublicDirectory() + "/.."),
					true, defaultUser, environment, spawnMethod,
					mapper.getApplicationTypeString(),
					appSpawnerTimeout, frameworkSpawnerTimeout));
				P_TRACE(3, "Forwarding " << r->uri << " to PID " << session->getPid());
			} catch (const SpawnException &e) {
				if (e.hasErrorPage()) {
					ap_set_content_type(r, "text/html; charset=utf-8");
					ap_rputs(e.getErrorPage().c_str(), r);
					// Unfortunately we can't return a 500 Internal Server
					// Error. Apache's HTTP error handler would kick in.
					return OK;
				} else {
					throw;
				}
			} catch (const BusyException &e) {
				return reportBusyException(r);
			}
			
			session->setReaderTimeout(r->server->timeout / 1000);
			session->setWriterTimeout(r->server->timeout / 1000);
			sendHeaders(r, session, mapper.getBaseURI());
			if (expectingUploadData) {
				if (uploadData != NULL) {
					sendRequestBody(r, session, uploadData);
					uploadData.reset();
				} else {
					sendRequestBody(r, session);
				}
			}
			session->shutdownWriter();
			
			apr_file_t *readerPipe = NULL;
			int reader = session->getStream();
			apr_os_pipe_put(&readerPipe, &reader, r->pool);
			apr_file_pipe_timeout_set(readerPipe, r->server->timeout);

			bb = apr_brigade_create(r->connection->pool, r->connection->bucket_alloc);
			b = apr_bucket_pipe_create(readerPipe, r->connection->bucket_alloc);
			APR_BRIGADE_INSERT_TAIL(bb, b);

			b = apr_bucket_eos_create(r->connection->bucket_alloc);
			APR_BRIGADE_INSERT_TAIL(bb, b);

			ap_scan_script_header_err_brigade(r, bb, NULL);
			ap_pass_brigade(r->output_filters, bb);
			
			Container *container = new Container();
			container->session = session;
			apr_pool_cleanup_register(r->pool, container, Container::cleanup, apr_pool_cleanup_null);
			
			// Apparently apr_bucket_pipe or apr_brigade closes the
			// file descriptor for us.
			session->discardStream();

			return OK;
			
		} catch (const thread_interrupted &e) {
			P_TRACE(3, "A system call was interrupted during an HTTP request. Apache "
				"is probably restarting or shutting down. Backtrace:\n" <<
				e.backtrace());
			return HTTP_INTERNAL_SERVER_ERROR;
			
		} catch (const tracable_exception &e) {
			P_TRACE(3, "Unexpected error in mod_passenger: " <<
				e.what() << "\n" << "  Backtrace:" << e.backtrace());
			return HTTP_INTERNAL_SERVER_ERROR;
		
		} catch (const exception &e) {
			P_TRACE(3, "Unexpected error in mod_passenger: " <<
				e.what() << "\n" << "  Backtrace: not available");
			return HTTP_INTERNAL_SERVER_ERROR;
		
		} catch (...) {
			P_TRACE(3, "An unexpected, unknown error occured in mod_passenger.");
			throw;
		}
	}