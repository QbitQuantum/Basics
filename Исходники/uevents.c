void uevents_process(void)
{
  OUTC(PRE "processing uevents...\n");
  while(1){
    k_l r;
    static struct k_epoll_event evts;//uevent netlink event
    do{
      u_memset(&evts,0,sizeof(evts));
      r=sysc(epoll_wait,4,ep_fd,&evts,1,UEVENTS_TIMEOUT);
    }while(r==-K_EINTR);
    if(K_ISERR(r)){
      OUT(PRE "ERROR(%ld):error epolling uevent netlink socket\n",r);
      sysc(exit_group,1,-1);
    }
	if(!r) break;//assume no more uevents
    if(evts.events&K_EPOLLIN) uevent_msg();
    else{
      OUT(PRE "ERROR:unmanaged epolling event on uevent netlink socket"
          "(events=%u)\n",evts.events);
      sysc(exit_group,1,-1);
    }
  }
  OUTC(PRE "uevents processed\n");
}