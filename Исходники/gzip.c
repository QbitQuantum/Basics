int gzipFilterX(FILE *in,FILE *out,SyncXF syncf,void *sp,int si){
	gzFile gz;
	int len,rcc;
	CStr(buf,1024*8);
	int size;
	int gsize;
	int wcc;
	int bcc = 0;
	double Start = Time();
	double Prevf = 0;
	int ibz = sizeof(buf);
	int gi;
	int fd = -1;
	int ofd = fileno(out);
	int xfd;
	int zerr = 0;
	/*
	int rready = -1;
	*/

	errno = 0;
	fd = dup(fileno(out));
	if( fd < 0 ){
		syslog_ERROR("--gzipFilter[%d]<-[%d] errno=%d\n",fd,ofd,errno);
		return -1;
	}

	/*
	if( 0 <= GZIPready )
		rready = dup(GZIPready);
	*/
	len = 0;
	/*
	if( gz = GZdopen(dup(fileno(out)),"w") ){
	*/
	if( file_isSOCKET(ofd) || file_ISSOCK(ofd) )
	if( !IsConnected(ofd,NULL) || !IsAlive(ofd) ){

fprintf(stderr,"[%d.%X] gzip DISCONN\n",getpid(),getthreadid());
fprintf(stderr,"[%d.%X] gzip DISCONN fd[%d] con=%d isSOCK=%d,%d,%d\n",
getpid(),getthreadid(),ofd,IsConnected(ofd,NULL),
file_isSOCKET(ofd),file_ISSOCK(ofd),file_issock(ofd));

		sendsync(rready,1);
		close(fd);
		return -1;
	}
	gz = GZdopen(fd,"w");
	if( file_isSOCKET(ofd) || file_ISSOCK(ofd) )
	if( !IsConnected(ofd,NULL) || !IsAlive(ofd) ){

fprintf(stderr,"[%d.%X] gzip DISCONN gx=%d\n",getpid(),getthreadid(),p2i(gz));
fprintf(stderr,"[%d.%X] gzip DISCONN fd[%d] con=%d isSOCK=%d,%d,%d\n",
getpid(),getthreadid(),ofd,IsConnected(ofd,NULL),
file_isSOCKET(ofd),file_ISSOCK(ofd),file_issock(ofd));

		close(fd);
		sendsync(rready,2);
		close(fd);
		return -1;
	}

	if( gz ){
		LOGX_gzip++;
		if( Gzip_NoFlush ){
			GZDBG(stderr,"-- %X gzip flush disabled(%d)\n",
				TID,Gzip_NoFlush);
		}
		Prevf = Time();

		sendsync(rready,0);
		setCloseOnFork("GZIPstart",fd);
		/*
		while( rcc = fread(buf,1,sizeof(buf),in) ){
		*/
		for( gi = 0;; gi++ ){
			if( gotsigTERM("gzip gi=%d",gi) ){
				if( numthreads() && !ismainthread() ){
					thread_exit(0);
				}
				break;
			}
			if( !Gzip_NoFlush )
			if( bcc )
			if( 0 < len && finputReady(in,NULL) == 0 ){
				zerr =
				gzflush(gz,Z_SYNC_FLUSH);
if( zerr ){
porting_dbg("+++EPIPE[%d] gzflush() zerr=%d %d SIG*%d",fd,zerr,len,gotSIGPIPE());
}
				bcc = 0;
			}
			if( lSINGLEP() ) /* could be generic */
			{
				if( 0 < len )
				if( !Gzip_NoFlush
				 || 4 < gi && 5 < Time()-Prevf
				){
				GZDBG(stderr,"-- %X gzip flush %d(%f) %d/%d\n",
				TID,Gzip_NoFlush,Time()-Start,len,gi);
					Prevf = Time();
					zerr = gzflush(gz,Z_SYNC_FLUSH);
					bcc = 0;
					if( zerr ){
				GZDBG(stderr,"-- %X gzip gzflush()%d err=%d\n",
				TID,len,zerr);
						break;
					}
				}
			}
			/*
			rcc = fread(buf,1,sizeof(buf),in);
			*/
			rcc = xread(in,AVStr(buf),QVSSize(buf,ibz));

			if( rcc <= 0 ){
				break;
			}
			wcc =
			gzwrite(gz,buf,rcc);

//fprintf(stderr,"[%d] Gzwrite %d/%d / %d\n",getpid(),wcc,rcc,len);

if( wcc <= 0 ){
porting_dbg("+++EPIPE[%d] gzwrite() %d/%d %d SIG*%d",fd,wcc,rcc,len,gotSIGPIPE());
fprintf(stderr,"[%d] Gzwrite %d/%d / %d\n",getpid(),wcc,rcc,len);
break;
}

			if( wcc != rcc ){
				syslog_ERROR("gzwrite %d/%d\n",wcc,rcc);
			}
			if( 0 < wcc ){
				bcc += wcc;
			}
			if( sizeof(buf) <= len ){
				ibz = sizeof(buf);
			}
			if( !Gzip_NoFlush )
			if( bcc )
			if( sizeof(buf) <= bcc || len < 16*1024 ){
				zerr =
				gzflush(gz,Z_SYNC_FLUSH);
				bcc = 0;
			}
			if( zerr || gotSIGPIPE() ){
porting_dbg("+++EPIPE[%d] gzflush() zerr=%d %d SIG*%d",fd,zerr,len,gotSIGPIPE());
				break;
			}
			len += rcc;
		}
		if( len == 0 ){
			const char *em;
			int en;
			int ef;
			em = gzerror(gz,&en);
			ef = gzeof(gz);
			if( en == -1 /* see errno */ && errno == 0 ){
				/* no error */
			}else{
			daemonlog("F","FATAL: gzwrite(%d)=%d/%d eof=%d %d %s\n",
				fd,len,bcc,ef,en,em);
			porting_dbg("FATAL: gzwrite(%d)=%d/%d eof=%d %d %s",
				fd,len,bcc,ef,en,em);
			}
		}
		clearCloseOnFork("GZIPend",fd);
		gzflush(gz,Z_SYNC_FLUSH);
		xfd = dup(fd);
		gsize = GZtell(gz);
		GZclose(gz);
		if( isWindowsCE() || lMULTIST() ){
			/* duplicated close of fd is harmful */
		}else
		if( isWindows() ) close(fd); /* to clear osf-handle mapping */
		Lseek(xfd,0,2);
		size = Lseek(xfd,0,1);
		Lseek(xfd,0,0);
		close(xfd);
		syslog_DEBUG("(%f)gzipFilter %d -> %d / %d\n",Time()-Start,
			len,gsize,size);
		return len;
	}
	sendsync(rready,3);
	close(fd);
	return 0;
}