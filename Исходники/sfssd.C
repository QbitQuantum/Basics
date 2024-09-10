static void
restart ()
{
  if (hup_lock)
    return;
  hup_lock = true;

  warn ("version %s, pid %d, restarted with SIGHUP\n", VERSION,
	int (getpid ()));
  server *s, *ns;
  for (s = serverlist.first; s; s = ns) {
    ns = serverlist.next (s);
    serverlist.remove (s);
    delete s;
  }
  for (sfssrv *nsp, *sp = services.first; sp; sp = nsp) {
    nsp = services.next (sp);
    delete sp;
  }

  for (sockaddr **sap = listenaddrs.base (); sap < listenaddrs.lim (); sap++)
    xfree (*sap);
  listenaddrs.clear ();
  listeners.clear ();

  parseconfig ();
  delaycb (0, 100000000, wrap (launchservers));
}