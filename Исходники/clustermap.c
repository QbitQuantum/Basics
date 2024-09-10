static int externalServerSubmit(externalServer_t* pServer, request_t* pRequest) {
	int                  returnValue   = 0;
	connectionContext_t* pCContext     = 0;
	connection_t         newConnection = 0;

	listAddLast(pServer->unassignedRequests, pRequest);
	pCContext = listRemoveFirst(pServer->freeConnections);

	if (pCContext) {
		connectionWaitCancel(pCContext->connection, getGlobalEventBase());
	}

	if (!pCContext) {
		//check if we have reached max concurrent connections limit
		// if not, create a new connection
		if (listGetSize(pServer->activeConnections) < MAX_CONCURRENT_CONNECTIONS) {
			LOG(DEBUG, "creating new external connection");
			newConnection = connectionClientCreate(pServer->serverIP,
												pServer->serverPort,
												createConnectionHandler());
			IfTrue(newConnection, ERR, "Error creating new connection to %s", pServer->serverName);
			//got a new connection
			pCContext = connectionContextCreate(newConnection, pServer);
			IfTrue(pCContext, ERR, "Error allocting memory for connection context");
			connectionSetContext(newConnection, pCContext);
			newConnection = 0;

			int err = connectionConnect(pCContext->connection);
			IfTrue(err >= 0, ERR, "connect failed");

			if (err == 1) {
				LOG(DEBUG, "waiting for connect to complete");
				pCContext->status = status_connecting;
				connectionWaitForConnect(pCContext->connection, getGlobalEventBase());
				goto OnSuccess;
			}
		}else {
			//if we have reached max connection limit, we will let the request rest
			//in the queue. Whenever one of the current connections get free, we will
			//use that to send the request.
			returnValue = 1;
			goto OnSuccess;
		}
	}

	if (pCContext) {
		pCContext->status = status_active;
		connectionSubmitRequests(pServer, pCContext);
	}
	goto OnSuccess;
OnError:
	if (newConnection) {
		connectionClose(newConnection);
	}
	if (pCContext) {
		connectionContextDelete(pCContext, 0);
	}
	returnValue = 1;
OnSuccess:
	return returnValue;
}