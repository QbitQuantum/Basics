nIcon::nIcon(RECT prect, char * ptip, HICON phicon, UINT pid)
{
   rect = prect;
   strncpy(tip, ptip, sizeof(tip));
   hicon = CopyIcon(phicon);
   id = pid;
   modify_calls = 0;
   deb("new nIcon: %d", id);
   balloon_icon = 0;
   calls=0;
}