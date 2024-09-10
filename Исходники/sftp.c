static void SftpGW(PCStr(host),int port,int gw){
	int tofrom_sftp[2];
	FILE *fc;
	FILE *tc;
	FILE *ts;
	FILE *fs;
	int rcc;
	CStr(req,1024);
	CStr(com,1024);
	const unsigned char *ucom = (const unsigned char*)com;
	CStr(arg,1024);
	CStr(scom,1024);
	CStr(user,128);
	CStr(passMD5,128);
	CStr(md5,1024);
	CStr(logindir,1024);
	CStr(rnfr,512);
	CStr(res,1024);
	CStr(xcom,1024);
	const char *dp;
	int vsock = -1;
	int dsock = -1;
	CStr(fifo,1024);
	CStr(sresp,0x10000);
	CStr(path,1024);
	CStr(resp1,1024);
	int Ok;
	int Bad;
	int xpid;
	int nready;
	int nfc;
	FILE *fpv[2];
	int rdv[2];
	int ncc = 0;
	int leng;

	FileSize datamax = DATA_MAX;
	IStr(opt1,128);
	if( getMountOpt1(MainConn(),"datamax",AVStr(opt1),sizeof(opt1)) ){
		datamax = kmxatoi(opt1);
		sv1log("## datamax=%s 0x%llX\n",opt1,datamax);
	}

	DEBUG("--SFTPGW start\n");
	fc = fdopen(gw,"r");
	tc = fdopen(gw,"w");
	putresp(tc,220,"SFTP/FTP gateway ready.");
	fflush(tc);
	ts = NULL;
	fs = NULL;

	logindir[0] = 0;
	fpv[0] = fc;
	nfc = 1;
	for(;;){
		nready = fPollIns(0,nfc,fpv,rdv);
		if( nready == 0 && errno == EINTR ){
			DEBUG("--SFTPGW ignored EINTR\n");
			sleep(1);
			continue;
		}
		if( nready <= 0 ){
			break;
		}
		if( 1 < nfc && 0 < rdv[1] ){
			DEBUG("--SFTPGW EOF from server?\n");
			relay_resp(fs,-1,0,AVStr(sresp),"",1);
			break;
		}

		fflush(tc);
		if( fgets(req,sizeof(req),fc) == 0 )
			break;
		dp = wordScan(req,com);
		if( *dp == ' ' ){
			textScan(dp+1,arg);
		}else
		lineScan(dp,arg);
		if( strcaseeq(com,"PASS") )
			DEBUG("--SFTPGW << [%s][****]\n",com);
		else	DEBUG("--SFTPGW << [%s][%s]\n",com,arg);

		if( strcaseeq(com,"QUIT") ){
			putresp(tc,221,"Ok Bye.");
			fclose(fc);
			fclose(tc);
			fc = 0;
			tc = 0;
			if( fs == NULL ){
				DEBUG("--SFTPGW DONE (not started)\n");
				break;
			}
			gw = CC_accept("sftp",host,port,user,fileno(fs));
			if( 0 <= gw ){
				putsftp(ts,"cd .","");
				relay_resp(fs,-1,0,AVStr(sresp),"restart",1);
				if( sresp[0] == 0 ){
					sv1log("##sftp_CC NotAlive\n");
					break;
				}
				fc = fdopen(gw,"r");
				fpv[0] = fc;
				tc = fdopen(gw,"w");
				ncc++;
				DEBUG("--SFTPGW SFTPCC restart #%d\n",ncc);
				putresp(tc,220,"Ok (reusing)");
				continue;
			}
			DEBUG("--SFTPGW DONE\n");
			break;
		}else
		if( strcaseeq(com,"NOOP") ){
			putresp(tc,200,"Ok");
		}else
		if( strcaseeq(com,"USER") ){
			strcpy(user,arg);
			putresp(tc,331,"Send password or passphrase for '%s'",
				arg);
		}else
		if( strcaseeq(com,"PASS") ){
			if( ts != NULL ){
				toMD5(arg,md5);
				DEBUG("--SFTP reusing user[%s]pass[%s][%s]\n",
					user,passMD5,md5);
				if( !streq(md5,passMD5) ){
					putresp(tc,530,"No");
					continue;
				}else	putresp(tc,230,"Ok");
				putsftp(ts,"cd %s",logindir);
				relay_resp(fs,-1,0,AVStr(sresp),"restart",1);
				continue;
			}
			/*
			if( forkSftp(host,port,user,arg,tofrom_sftp) != 0 ){
			*/
			if( forkSftp(host,port,user,arg,tofrom_sftp,AVStr(sresp)) != 0 ){
				IStr(prompt,1024);
				lineScan(sresp,prompt);
				DEBUG("--SFTP login failed\n");
				/*
				putresp(tc,530,"No (Login failed)");
				*/
				putresp(tc,530,"No (Login failed:'%s')",prompt);
if( lGATEWAY() )
sv1log("####@@@@ LOGIN FAILURE\n");
continue; /* to return normal resp. for following commands... */
				break;
			}
			toMD5(arg,passMD5);
			fs = fdopen(tofrom_sftp[0],"r");
			ts = fdopen(tofrom_sftp[1],"w");
			fpv[1] = fs;
			nfc = 2;
			putresp(tc,230,"Ok");

			putsftp(ts,"pwd");
			relay_resp(fs,-1,0,AVStr(sresp),com,1);
			/*
			if( strneq(sresp,"Remote working directory: ",26) ){
				CStr(path,1024);
				lineScan(sresp+26,path);
			*/
			if( scanresp(sresp,"Remote working directory:",
			    AVStr(path),sizeof(path)) ){
				strcpy(logindir,path);
			}
		}else
		if( strcaseeq(com,"TYPE") ){
			putresp(tc,200,"Ok");
		}else
		if( strcaseeq(com,"PASV") ){
			PASV(tc,&vsock);
#if 0
			VSAddr ba;
			int balen;
			CStr(mport,128);
			vsock = server_open("SftpGW",VStrNULL,0,1);
			if( 0 <= vsock ){
				balen = sizeof(ba);
				getsockname(vsock,(SAP)&ba,&balen);
#if defined(__CYGWIN__)
				if( VSA_addrisANY(&ba) ){
				    /*connection to 0.0.0.0 fails on CYGWIN?*/
				    VSA_atosa(&ba,VSA_port(&ba),"127.0.0.1");
				}
#endif
				VSA_prftp(&ba,AVStr(mport));
			putresp(tc,227,"Enterning Passive Mode (%s)",mport);
			}else{
				putresp(tc,500,"No");
			}
#endif
		}else
		if( ts == NULL ){
			sv1log("Not Logged In: %s",req);
			putresp(tc,530,"Please login with USER and PASS.");
		}else
		if( strcaseeq(com,"PWD") ){
			putsftp(ts,"pwd");
			relay_resp(fs,-1,0,AVStr(sresp),com,1);
			/*
			if( strneq(sresp,"Remote working directory: ",26) ){
				CStr(path,1024);
				lineScan(sresp+26,path);
			*/
			if( scanresp(sresp,"Remote working directory:",
			    AVStr(path),sizeof(path)) ){
				putresp(tc,257,"\"%s\"",path);
			}else{
				putresp(tc,257,"\"/\"");
			}
		}else
		if( strcaseeq(com,"CWD") ){
			putsftp(ts,"cd %s",arg);
			relay_resp(fs,-1,0,AVStr(sresp),com,1);
			/*
			if( strneq(sresp,"Couldn't",8)
			 || strneq(sresp,"Can't",4) ){
			*/
			if( linehead(sresp,"Couldn't",0)
			 || linehead(sresp,"Can't",0) ){
				if( strstr(sresp,BadPath) )
					putresp(tc,550,BadPath);
				else
				putresp(tc,550,"No");
			}else	putresp(tc,250,"Ok");
		}else
		/*
		if( strcaseeq(com,"SIZE") ){
			putsftp(ts,"ls -ld %s",arg);
			relay_resp(fs,-1,0,AVStr(sresp),com,1);
			if( *sresp == '-' ){
				int sz = 0;
				sscanf(sresp,"%*s %*s %*s %*s %d",&sz);
				putresp(tc,213,"%d",sz);
			}else{
				putresp(tc,550,"Not a plain file");
			}
		}else
		*/
		if( strcaseeq(com,"STOR") ){
			if( vsock < 0 ){
				putresp(tc,500,"No");
				continue;
			}
			dsock = ACCEPT(vsock,1,-1,10);
			if( 0 <= dsock ){
				CStr(tmpf,1024);
				FILE *dfp;
				FILE *tmp;
				/*
				int bytes;
				*/
				FileSize Bytes;
				int isbin;
				double St;

				dfp = fdopen(dsock,"r");
				if( dfp == NULL ){
					putresp(tc,500,"No-1");
					continue;
				}
				tmp = getfile(AVStr(tmpf),"w",0);
				if( tmp == NULL ){
					putresp(tc,500,"No-2");
					fclose(dfp);
					continue;
				}
				putresp(tc,150,"Ok");
				St = Time();
				/*
				bytes = file_copy(dfp,tmp,NULL,DATA_MAX,&isbin);
				DEBUG("--SFTPGW bin=%d,%d bytes upload\n",
					isbin,bytes);
				*/
				Bytes = file_copy(dfp,tmp,NULL,datamax,&isbin);
				DEBUG("--SFTPGW bin=%d,%lld bytes upload\n",
					isbin,Bytes);
				fclose(tmp);
				fclose(dfp);

				DEBUG("--SFTPGW put %s (%lld %lld)\n",tmpf,
					Bytes,File_sizeX(tmpf));
				putsftp(ts,"put %s %s",tmpf,arg);
				/*
				relay_resp(fs,-1,15*1000,AVStr(sresp),com,1);
				*/
				relay_resp(fs,-1,5*1000,AVStr(sresp),com,1);

				if( strneq(sresp,"Uploading ",10)
				 && strstr(sresp,"sftp>") == 0 ){
					waitUploaded(com,AVStr(sresp),fs,fc,tc,
						Time()-St,&vsock);
				}else
				if( strncmp(sresp,"Could",5) == 0 )
					putresp(tc,550,"No");
				else	putresp(tc,226,"Ok");
				unlink(tmpf);
				dsock = -1;
			}else{
				putresp(tc,500,"accept error");
			}
			vsock = -1;
		}else
		if( strcaseeq(com,"RETR") ){
			if( vsock < 0 ){
				putresp(tc,500,"No");
				continue;
			}
			dsock = ACCEPT(vsock,1,-1,10);
			if( arg[0]==0 ||streq(arg,".") ||strtailstr(arg,"/") ){
				putresp(tc,550,"RETR for dir [%s]",arg);
				if( 0 <= dsock ){
					close(dsock);
					dsock = -1;
				}
			}else
			if( 0 <= dsock ){
				CStr(rpath,1024);
				FILE *rfp;
				int pid;

				truncVStr(rpath);
				getfile(AVStr(fifo),NULL,1);
				if( SFTP_WITH_SEEK ){
					/* newer sftp with output seeking */
					sprintf(rpath,"%sr",fifo);
					rfp = fopen(rpath,"w+");
					if( rfp ){
					  pid = Fork("SFTP-DATA");
					  if( pid == 0 ){
						/*
						relayFile2Fifo(rfp,rpath,fifo);
						*/
						relayFile2Fifo(fs,rfp,rpath,fifo);
						_exit(0);
					  }
					  else{
						fclose(rfp); /* 9.9.8 */
					  }
					}
					putsftp(ts,"get %s %s",arg,rpath);
				}else{
				putsftp(ts,"get %s %s",arg,fifo);
				}
				/*
				if( relay_fifo(fs,tc,fifo,dsock,com)==0 )
				*/
				leng = relay_fifo(fs,tc,fifo,dsock,com,AVStr(sresp));
				if( leng <= 0 ){
					sv1log("RETR ERROR: %s\n",sresp);
				}
				if( leng == 0 && strstr(sresp,BadPath) )
					putresp(tc,550,BadPath);
				else
				if( 0 < leng )
					putresp(tc,226,"Ok");
				else	putresp(tc,550,"No");
				relay_resp(fs,-1,1,AVStr(sresp),com,1);
				if( rpath[0] ){
					unlink(rpath);
					xpid = NoHangWait();
					DEBUG("--SFTP-DATA finished, pid=%d\n",
						xpid);
				}
				close(dsock);
				dsock = -1;
				unlink(fifo);
			}else{
				putresp(tc,500,"accept error");
			}
			if( 0 <= vsock ){
				close(vsock); /* 9.9.8 */
			}
			vsock = -1;
		}else
		if( strcaseeq(com,"NLST") || strcaseeq(com,"LIST") ){
			if( vsock < 0 ){
				putresp(tc,500,"No");
				continue;
			}
			dsock = ACCEPT(vsock,1,-1,10);
			if( 0 <= dsock ){
				putresp(tc,150,"Ok");
				if( arg[0] == '-' ){
					char *op;
					for( op = arg+1; *op; ){
						if( strchr(" \t\r\n",*op) )
							break;
						if( strchr("L",*op) ){
							ovstrcpy(op,op+1);
						}else	op++;
					}
				}
				/*
				if( streq(com,"NLST") || strstr(arg,"-l") )
					putsftp(ts,"ls %s",arg);
				else	putsftp(ts,"ls -l %s",arg);
				relay_resp(fs,dsock,0,VStrNULL,com,0);
				*/
				if( streq(com,"NLST") || strstr(arg,"-l") )
					sprintf(scom,"ls %s",arg);
				else	sprintf(scom,"ls -l %s",arg);
				putsftp(ts,"%s",scom);
				relay_list(fs,dsock,scom);
				close(dsock);
				dsock = -1;
				putresp(tc,226,"Ok");
			}else{
				putresp(tc,500,"accept error");
			}
			vsock = -1;
		}else
		if( ucom[0]==0xFF && ucom[1]==0xF4 /* IAC+IP */
		 && ucom[2]==0xF2 /* SYNC */
		 && strcaseeq(com+3,"ABOR") ){
			sv1log("--SFTPGW ABOR\n");
		}else
		if( strcaseeq(com,"RNFR") ){
			strcpy(rnfr,arg);
			putresp(tc,350,"Ok");
		}else
		if( strcaseeq(com,"RNTO") ){
			putsftp(ts,"rename %s %s",rnfr,arg);
			relay_resp(fs,-1,0,AVStr(sresp),com,1);
			if( dp = strstr(sresp,"Couldn't") ){
				lineScan(dp,resp1);
				putresp(tc,550,"No %s",resp1);
			}else	putresp(tc,250,"Ok");
		}else
		if( strcaseeq(com,"MKD") || strcaseeq(com,"RMD")
		 || strcaseeq(com,"DELE")
		){ 
			Bad = 550;
			if( strcaseeq(com,"MKD") ){
				Ok = 257;
				putsftp(ts,"mkdir %s",arg);
			}else
			if( strcaseeq(com,"RMD") ){
				Ok = 250;
				putsftp(ts,"rmdir %s",arg);
			}else{
				Ok = 250;
				putsftp(ts,"rm %s",arg);
			}
			relay_resp(fs,-1,0,AVStr(sresp),com,1);
			if( dp = strstr(sresp,"Couldn't") ){
				lineScan(dp,resp1);
				putresp(tc,Bad,"No %s",resp1);
			}else	putresp(tc,Ok,"Ok");
		}else
		{
			putresp(tc,502,"No not supported");
		}
	}
	if( fs != NULL && !feof(fs) ){
		putsftp(ts,"quit");
		relay_resp(fs,-1,0,AVStr(sresp),com,1);
	}
	xpid = NoHangWait();
	DEBUG("--SFTPGW finished, pid=%d\n",xpid);
}