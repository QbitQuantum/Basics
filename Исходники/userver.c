/* ---------------------------------------------------------------------- */
void
print_extra_info()
{
  int rc = 0;
#ifdef HAVE_IFCONFIG
  printf("ifconfig output:\n");
  fflush(stdout);
  fflush(stderr);
  rc = system("/sbin/ifconfig");
  fflush(stdout);
  fflush(stderr);
  printf("-----------------------------------------------\n");
#endif /* HAVE_IFCONFIG */

#ifdef HAVE_PROC_FILE_INFO
  do_proc_info("/proc/version");
  do_proc_info("/proc/sys/kernel/rtsig-max");
  do_proc_info("/proc/sys/fs/file-max");
  do_proc_info("/proc/sys/net/ipv4/tcp_max_syn_backlog");
  do_proc_info("/proc/sys/net/ipv4/ip_local_port_range");
  do_proc_info("/proc/sys/net/ipv4/tcp_tw_recycle");
  do_proc_info("/proc/sys/net/ipv4/tcp_max_tw_buckets");
  do_proc_info("/proc/sys/net/ipv4/tcp_fin_timeout");
  do_proc_info("/proc/sys/net/ipv4/tcp_abort_on_overflow");
  do_proc_info("/proc/sys/net/core/somaxconn");

  fflush(stdout);
  fflush(stderr);
  printf("From /proc/cpuinfo:\n");
  fflush(stdout);
  fflush(stderr);
  rc = system("egrep 'model name|processor|MHz|cache|_id' /proc/cpuinfo");
  fflush(stdout);
  fflush(stderr);

  printf("From /proc/interrupts (before):\n");
  rc = system("grep 'eth' /proc/interrupts");

#endif /* HAVE_PROC_FILE_INFO */

#ifdef HAVE_LIMITS
  printf("-----------------------------------------------\n");
  printf("Limits:\n");
  fflush(stdout);
  fflush(stderr);
  rc = system("csh -c limit");
  fflush(stdout);
  fflush(stderr);
  printf("-----------------------------------------------\n");
  fflush(stdout);
  fflush(stderr);
#endif /* HAVE_LIMITS */
}