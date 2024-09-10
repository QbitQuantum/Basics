// shut down a monitor's filesystem-specific state 
// not much we can do if any shutdown step fails, so try them all
int udev_monitor_fs_shutdown( struct udev_monitor* monitor ) {
   
   int rc = 0;
   
   // stop tracking this monitor
   udev_monitor_unregister( monitor );
   
   if( monitor->sock >= 0 ) {
      rc = shutdown( monitor->sock, SHUT_RDWR );
      if( rc < 0 ) {
         rc = -errno;
         log_error("shutdown(socket %d) rc = %d", monitor->sock, rc );
      }
   }
      
   if( monitor->sock_fs >= 0 ) {
      rc = shutdown( monitor->sock_fs, SHUT_RDWR );
      if( rc < 0 ) {
         rc = -errno;
         log_error("shutdown(socket %d) rc = %d", monitor->sock_fs, rc );
      }
   }
   
   if( monitor->sock >= 0 ) {
      rc = close( monitor->sock );
      if( rc < 0 ) {
         rc = -errno;
         log_error("close(socket %d) rc = %d", monitor->sock, rc );
      }
      else {
         monitor->sock = -1;
      }
   }
    
   if( monitor->sock_fs >= 0 ) {
      rc = close( monitor->sock_fs );
      if( rc < 0 ) {
         rc = -errno;
         log_error("close(socket %d) rc = %d", monitor->sock_fs, rc );
      }
      else {
         monitor->sock_fs = -1;
      }
   }
   
   if( monitor->epoll_fd >= 0 ) {
      rc = close( monitor->epoll_fd );
      if( rc < 0 ) {
         rc = -errno;
         log_error("close(epoll_fd %d) rc = %d", monitor->epoll_fd, rc );
      }
      else {
         monitor->epoll_fd = -1;
      }
   }
  
   if( monitor->events_wd >= 0 ) {

      if( monitor->inotify_fd >= 0 ) {
         rc = inotify_rm_watch( monitor->inotify_fd, monitor->events_wd );
         if( rc < 0 ) {
            rc = -errno;
            log_error("close(events_wd %d) rc = %d", monitor->events_wd, rc );
         }
         else {
            monitor->events_wd = -1;
         }
      }
   } 
   if( monitor->inotify_fd >= 0 ) {
      rc = close( monitor->inotify_fd );
      if( rc < 0 ) {
         rc = -errno;
         log_error("close(inotify_fd %d) rc = %d", monitor->inotify_fd, rc );
      }
      else {
         monitor->inotify_fd = -1;
      }
   }
   
   return rc;
}