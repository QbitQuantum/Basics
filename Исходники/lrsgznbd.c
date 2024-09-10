int main(int argc, char **argv)
{
  int pr[2];
  int sk;
  int nbd;
  int blocksize = 1024;

  char chunk[CHUNK];
  struct nbd_request request;
  struct nbd_reply reply;

  u64 size;
  u64 from;
  u32 len;
  /*  */
  int file, oldfile = -1;
  u32 offset;
  unsigned char *ptr = NULL;

  if(argc<3){
    printf("Usage: %s nbdevice gzfile\n",argv[0]);
    exit(1);
  }

  /* memory for one decompressed block */
  all = malloc(1024*88064);

  if(argc == 3){
    int nb, fid;
    char buf[512];

    /* find an approximate size */
    for (nb = 0; ; nb++) {
      sprintf(buf, "%s%03d", argv[2], nb);
      if ((fid=open(buf, O_RDONLY)) == -1) {
        break;
      }
      close(fid);
    }
    if (nb == 0) {
      fprintf(stderr,"%s: unable open compressed file %s\n",argv[0], buf);
      exit(1);
    }
    size = (u64)88064*(u64)1024*nb;
  } else {
    exit(1);
  }

  if(socketpair(AF_UNIX, SOCK_STREAM, 0, pr)){
    fprintf(stderr,"%s: unable to create socketpair: %s\n",argv[0],strerror(errno));
    exit(1);
  }

  switch(fork()){
  case -1 :
    fprintf(stderr,"%s: unable to fork: %s\n",argv[0],strerror(errno));
    exit(1);
    break;

  case 0 : /* child */
    close(pr[0]);

    sk=pr[1];

    nbd=open(argv[1], O_RDWR);
    if(nbd<0){
      fprintf(stderr,"%s: unable to open %s: %s\n",argv[0],argv[1],strerror(errno));
      exit(1);
    }

    if (ioctl(nbd, NBD_SET_BLKSIZE, (unsigned long)blocksize) < 0) {
      fprintf(stderr, "NBD_SET_BLKSIZE failed\n");
      exit(1);
    }

    if ((ioctl(nbd, NBD_SET_SIZE_BLOCKS, (unsigned long)(size/blocksize))) < 0) {
      fprintf(stderr, "NBD_SET_SIZE_BLOKS failed\n");
      exit(1);
    }

    ioctl(nbd, NBD_CLEAR_SOCK);

    if(ioctl(nbd,NBD_SET_SOCK,sk)<0){
      fprintf(stderr,"%s: failed to set socket for %s: %s\n",argv[0],argv[1],strerror(errno));
      exit(1);
    }

    if(ioctl(nbd,NBD_DO_IT)<0){
      fprintf(stderr,"%s: block device %s terminated: %s\n",argv[0],argv[1],strerror(errno));
    }

    ioctl(nbd, NBD_CLEAR_QUE);
    ioctl(nbd, NBD_CLEAR_SOCK);

    exit(0);

    break;
  }

  /* only parent here, child always exits */

  close(pr[1]);
  sk=pr[0];

  reply.magic=htonl(NBD_REPLY_MAGIC);
  reply.error=htonl(0);

  BUFFER = malloc(24064);
  Bitmap = malloc(24064 - 2048);
  IN = malloc(INSIZE);

  sleep(1);

  while(1){

    if(read(sk,&request,sizeof(request))!=sizeof(request)){
      fprintf(stderr,"%s: incomplete request\n",argv[0]);
    }

    memcpy(reply.handle,request.handle,sizeof(reply.handle));

    len=ntohl(request.len);
    from=ntohll(request.from);

#ifdef TRACE
    fprintf(stderr,"%s: len=%d, from=%Ld\n",argv[0],len,from);
#endif

    if(request.magic!=htonl(NBD_REQUEST_MAGIC)){
      fprintf(stderr,"%s: bad magic\n",argv[0]);
      reply.error=htonl(EIO); /* is that the right way of doing things ? */
    }

    /* write resquest */
    if(ntohl(request.type) == 1){
      // fprintf(stderr,"%s: unsupported write request (len=%d)\n",argv[0], len);
      readit(sk, chunk, len);
      /* fake write */
      reply.error=htonl(0);
      len = 0;
      memcpy(chunk,&reply,sizeof(struct nbd_reply));
      if(write(sk,chunk,len+sizeof(struct nbd_reply))!=(len+sizeof(struct nbd_reply))){
        fprintf(stderr,"%s: write failed: %s\n",argv[0],strerror(errno));
      }
      continue;
    }

    /* disc request */
    if(ntohl(request.type) == 2){
      fprintf(stderr,"%s: unsupported disc request\n",argv[0]);
      reply.error=htonl(EROFS);
    }

    if(len+sizeof(struct nbd_reply)>CHUNK){
      fprintf(stderr,"%s: request too long (%d)\n",argv[0], len+sizeof(struct nbd_reply));
      //reply.error=htonl(EIO);
    }

    /* read request */
    if(reply.error==htonl(0)){
      int remain = len;
      int offset2 = 0;

      /* which chunk to open */
      file = from / (88064*1024);
      offset = from % (88064*1024);

      while (remain > 0) {
        u32 cpylen;

        if (oldfile != file) {
          decompress_file(argv[2], file, offset);
          oldfile = file;
        }

        ptr = &all[offset];

        if (offset + remain >= 88064*1024) {
          /* request on a block boundary */
          cpylen = (88064*1024)-offset;
          remain -= cpylen;
          file++;
          offset = 0;
        } else {
          /* request within a block */
          cpylen = remain;
          remain = 0;
        }

        /* copy the data */
        memcpy(chunk+sizeof(struct nbd_reply)+offset2, ptr, cpylen);
        offset2 += cpylen;
      }
    } else {
      len=0;
    }

    /* copy the reply header */
    memcpy(chunk,&reply,sizeof(struct nbd_reply));
    /* send data to kernel */
    if(write(sk,chunk,len+sizeof(struct nbd_reply))!=(len+sizeof(struct nbd_reply))){
      fprintf(stderr,"%s: write failed: %s\n",argv[0],strerror(errno));
    }
  }

  exit(0);
}