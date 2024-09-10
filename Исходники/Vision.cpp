int32 VisionApp::Identity(void*)
{
	int32 identSock(0), accepted(0);
	BString ident;
	char received[64];

	struct sockaddr_in localAddr;
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(113);
	localAddr.sin_addr.s_addr = INADDR_ANY;

	if ((identSock = socket(AF_INET, SOCK_STREAM, 0)) >= 0 &&
		bind(identSock, (struct sockaddr*)&localAddr, sizeof(localAddr)) == 0) {
		vision_app->fIdentSocket = identSock;

		struct linger lng = {0, 0};
		setsockopt(identSock, SOL_SOCKET, SO_LINGER, &lng, sizeof(linger));
		listen(identSock, 1);

		while (!vision_app->fShuttingDown) {
			struct fd_set rset, eset;
			struct sockaddr_in remoteSock;
			int size(sizeof(sockaddr_in));
			struct timeval tv = {10, 0};
			FD_ZERO(&rset);
			FD_ZERO(&eset);
			FD_SET(identSock, &rset);
			FD_SET(identSock, &eset);

			if (select(identSock + 1, &rset, 0, &eset, NULL) < 0 || FD_ISSET(identSock, &eset))
				break;
			else if (FD_ISSET(identSock, &rset)) {
				accepted = accept(identSock, (struct sockaddr*)&remoteSock, (socklen_t*)&size);
				if (accepted >= 0) {
					FD_ZERO(&rset);
					FD_ZERO(&eset);

					BString remoteIP(inet_ntoa(remoteSock.sin_addr));
					ident = vision_app->GetIdent(remoteIP.String());

					if (ident.Length() > 0) {
						memset(received, 0, 64);
						FD_SET(accepted, &rset);
						FD_SET(accepted, &eset);
						if (select(accepted + 1, &rset, 0, &eset, &tv) > 0 &&
							FD_ISSET(accepted, &rset) && !FD_ISSET(accepted, &eset)) {

							recv(accepted, received, 64, 0);
							int32 len(0);

							received[63] = 0;
							while ((len = strlen(received)) && isspace(received[len - 1]))
								received[len - 1] = 0;

							BString string;

							string.Append(received);
							string.Append(" : USERID : BeOS : ");
							string.Append(ident);
							string.Append("\r\n");

							send(accepted, string.String(), string.Length(), 0);
						}
					} else {
						BString string("0 , 0 : UNKNOWN : UNKNOWN-ERROR");
						send(accepted, string.String(), string.Length(), 0);
					}
					close(accepted);
				}
			}
		}
	}

	close(identSock);
	return 0;
}