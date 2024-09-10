void wl_shm_req_create_pool(k_u32 shm,k_u32 shm_pool,k_i fd,k_u32 sz)
{
  k_u32 req[REQ_PAYLOAD_CREATE_POOL_DWS];
  req[0]=shm;
  req[1]=(REQ_PAYLOAD_CREATE_POOL_DWS*sizeof(k_u32))<<16|WL_SHM_CREATE_POOL;
  req[2]=shm_pool;
  req[3]=sz;

  struct k_io_vec iov;
  iov.base=&req;
  iov.len=REQ_PAYLOAD_CREATE_POOL_DWS*sizeof(k_u32);

  struct k_msg_hdr msg;
  k_u8 cmsg_buf[K_CMSG_SPACE(sizeof(fd))];
  u_memset(&msg,0,sizeof(msg));
  u_memset(cmsg_buf,0,sizeof(cmsg_buf));

  msg.ctl=cmsg_buf;
  msg.ctl_len=sizeof(cmsg_buf);

  struct k_cmsg_hdr *cmsg=K_CMSG_FIRSTHDR(&msg);
  cmsg->lvl=K_SOL_SOCKET;
  cmsg->type=K_SCM_RIGHTS;
  cmsg->len=K_CMSG_LEN(sizeof(fd));

  msg.iov=&iov;
  msg.iov_len=1;
  *((k_i*)(K_CMSG_DATA(K_CMSG_FIRSTHDR(&msg))))=fd;

  k_l r;
  do r=sysc(sendmsg,3,srv_so,&msg,0);while(r==-K_EINTR);

  if(K_ISERR(r)){
    PERR("FATAL(%ld):unable to send the shm create_pool request\n",r);
    sysc(exit_group,1,-1);
  }
  if(r!=REQ_PAYLOAD_CREATE_POOL_DWS*sizeof(k_u32)){
    PERR("FATAL:shm::create_pool request only %ld/%ld was sent\n",r,
                                     REQ_PAYLOAD_CREATE_POOL_DWS*sizeof(k_u32));
    sysc(exit_group,1,-1);
  }
  if(!r) sysc(exit_group,1,0);//server is gone
}