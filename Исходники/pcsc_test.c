						printf("response: ");
						for(i=0; i<dwRecvLength; i++){
							printf("%02X ", pbRecvBuffer[i]);
						}
						printf("\n");
					}
				}
			}
		}
	}
//						printf("j:%d",j);
}
rv = SCardDisconnect(hCard, SCARD_LEAVE_CARD);
CHECK("SCardDisconnect", rv)

#ifdef SCARD_AUTOALLOCATE
 rv = SCardFreeMemory(hContext, mszReaders);
 CHECK("SCardFreeMemory", rv)

#else
 free(mszReaders);
#endif

 rv = SCardReleaseContext(hContext);

 CHECK("SCardReleaseContext", rv)

 return 0;
}

