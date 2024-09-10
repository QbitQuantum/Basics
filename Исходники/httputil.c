/**
*@description send requested file to sock
*@param sockFd int  socket Id
*@param request Request  http_request struct
*@return if failed, return negative number, otherwise, nonnegative
*/
int sendRequestedFile(int sockFd, Request * httpRequest) {
	char ok_line[]       = "HTTP/1.0 200 OK\r\n";
	char badReq_line[]   = "HTTP/1.0 400 Bad Request\r\n";  
	char badReq_content[] = "<html><head></head><body><h1>400 Bad Request</h1></body></html>";
	char notFound_line[] = "HTTP/1.0 404 Not Found\r\n";
	char notFound_content[] = "<html><head></head><body><h1>404 Not Found</h1></body></html>";
	char suffix_line[]   = "\r\n";
	char writeBuffer[MAX_WRITE_BUFFER];
	char * responseLine;
	char *filePath = (httpRequest->requestLine).path;
	int fileSize;
	if (!checkFileExist(filePath)) {
	  printf("file %s doesn't exist\n", filePath);
	}
	short isResolved = httpRequest->isResolved;
	if ( isResolved ) {
		fileSize = getFileSize(filePath);
		if (fileSize < 0) {
			printf("request file %s not found, so send 404 response\n", filePath);
			if (send(sockFd, notFound_line, strlen(notFound_line), 0) < 0) {
				return -1;
			}

			//send content length
			memset(writeBuffer, '\0', sizeof(writeBuffer));
			snprintf(writeBuffer, sizeof(writeBuffer), "%s: %lu\r\n","Content-Length",strlen(notFound_content));
			if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
				return -1;
			}

			//send persistent header
			memset(writeBuffer, '\0', sizeof(writeBuffer));
			if (httpRequest->isAlive == persistent) {
				snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Connection", "keep-alive");
			} else {
				snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Connection", "close");
			}
			if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
				return -1;
			}

			//send content-type header
			memset(writeBuffer, '\0', sizeof(writeBuffer));
			snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Content-Type", "text/html");
			if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
				return -1;
			}
			
			//send Date
			memset(writeBuffer, '\0', sizeof(writeBuffer));
			time_t current = time(0);
			time_t expire  = current + 60;
			struct tm currentTm = *gmtime(&current); 
			struct tm expireTm  = * gmtime(&expire);
			char timeStr[128];
			memset(timeStr, '\0', sizeof(timeStr));
			strftime(timeStr, sizeof(timeStr), "%a, %d %b %Y %H:%M:%S %Z", &currentTm);
			snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Date", timeStr);
			if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
				return -1;
			}

			memset(writeBuffer, '\0', sizeof(writeBuffer));
			memset(timeStr, '\0', sizeof(timeStr));
			strftime(timeStr, sizeof(timeStr), "%a, %d %b %Y %H:%M:%S %Z", &expireTm);
			snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Expires", timeStr);
			if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
				return -1;
			}
			//send suffix line
			if (send(sockFd, suffix_line, strlen(suffix_line), 0) < 0) {
				return -1;
			}
			//send content
			if (send(sockFd, notFound_content, strlen(notFound_content), 0) < 0) {
				return -1;
			}

			return 0;
		} else {

			printf("start to send request file of size %d bytes...\n", fileSize);
			//send 200 OK status line
			if (send(sockFd, ok_line, strlen(ok_line), 0) < 0) {
				return -1;
			}

			//send content-length header
			memset(writeBuffer, '\0', sizeof(writeBuffer));
			snprintf(writeBuffer, sizeof(writeBuffer), "%s: %d\r\n", "Content-Length", fileSize);
			if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
				return -1;
			}
			
			//send persistent header
			memset(writeBuffer, '\0', sizeof(writeBuffer));
			if (httpRequest->isAlive == persistent) {
				snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Connection", "keep-alive");
			} else {
				snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Connection", "close");
			}
			if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
				return -1;
			}

			//send content-type header
			memset(writeBuffer, '\0', sizeof(writeBuffer));
			snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Content-Type", "text/html");
			if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
				return -1;
			}
			
			//send Date
			memset(writeBuffer, '\0', sizeof(writeBuffer));
			time_t current = time(0);
			time_t expire  = current + 60;
			struct tm currentTm = *gmtime(&current); 
			struct tm expireTm  = * gmtime(&expire);
			char timeStr[128];
			memset(timeStr, '\0', sizeof(timeStr));
			strftime(timeStr, sizeof(timeStr), "%a, %d %b %Y %H:%M:%S %Z", &currentTm);
			snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Date", timeStr);
			if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
				return -1;
			}

			memset(writeBuffer, '\0', sizeof(writeBuffer));
			memset(timeStr, '\0', sizeof(timeStr));
			strftime(timeStr, sizeof(timeStr), "%a, %d %b %Y %H:%M:%S %Z", &expireTm);
			snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Expires", timeStr);
			if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
				return -1;
			}
			//send suffix line
			if (send(sockFd, suffix_line, strlen(suffix_line), 0) < 0) {
				return -1;
			}
			
			//send request body
			if (transferFile(filePath, sockFd) == 0) {
				printf("send  file %s of %d bytes successfully\n", filePath, fileSize);
			} else {
				return -1;
			}
		}
	} else {
		printf("start to send 400 bad request\n");
		if (send(sockFd, badReq_line, strlen(badReq_line), 0) < 0 ) {
			return -1;
		}
		//send content length
		memset(writeBuffer, '\0', sizeof(writeBuffer));
		snprintf(writeBuffer, sizeof(writeBuffer), "%s: %lu\r\n","Content-Length",strlen(badReq_content));
		if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
			return -1;
		}

		//send persistent header
		memset(writeBuffer, '\0', sizeof(writeBuffer));
		if (httpRequest->isAlive == persistent) {
			snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Connection", "keep-alive");
		} else {
			snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Connection", "close");
		}
		if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
			return -1;
		}

		//send content-type header
		memset(writeBuffer, '\0', sizeof(writeBuffer));
		snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Content-Type", "text/html");
		if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
			return -1;
		}
		
		//send Date
		memset(writeBuffer, '\0', sizeof(writeBuffer));
		time_t current = time(0);
		time_t expire  = current + 60;
		struct tm currentTm = *gmtime(&current); 
		struct tm expireTm  = * gmtime(&expire);
		char timeStr[128];
		memset(timeStr, '\0', sizeof(timeStr));
		strftime(timeStr, sizeof(timeStr), "%a, %d %b %Y %H:%M:%S %Z", &currentTm);
		snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Date", timeStr);
		if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
			return -1;
		}

		memset(writeBuffer, '\0', sizeof(writeBuffer));
		memset(timeStr, '\0', sizeof(timeStr));
		strftime(timeStr, sizeof(timeStr), "%a, %d %b %Y %H:%M:%S %Z", &expireTm);
		snprintf(writeBuffer, sizeof(writeBuffer), "%s: %s\r\n", "Expires", timeStr);
		if (send(sockFd, writeBuffer, strlen(writeBuffer), 0) < 0) {
			return -1;
		}
		//send suffix line
		if (send(sockFd, suffix_line, strlen(suffix_line), 0) < 0) {
			return -1;
		}
		//send content
		if (send(sockFd, notFound_content, strlen(notFound_content), 0) < 0) {
			return -1;
		}
		return 0;
	}

	return 1;
}