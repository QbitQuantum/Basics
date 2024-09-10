void wl_display_req_sync(k_u32 callback_id)
{
  k_u32 req[REQ_SYNC_DWS];
  req[0]=WL_DISPLAY_ID;
  req[1]=((REQ_SYNC_DWS*sizeof(k_u32))<<16)|WL_DISPLAY_SYNC;
  req[2]=callback_id;

  struct k_io_vec iov;
  iov.base=&req;
  iov.len=sizeof(req);

  struct k_msg_hdr msg;
  u_memset(&msg,0,sizeof(msg));
  msg.iov=&iov;
  msg.iov_len=1;

  k_l r;
  do r=sysc(sendmsg,3,srv_so,&msg,0);while(r==-K_EINTR);

  if(K_ISERR(r)){
    PERR("FATAL(%d):unable to send the sync request\n",r);
    sysc(exit_group,1,-1);
  }
  if(!r) sysc(exit_group,1,0);//server is gone
}