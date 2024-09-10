void
RCMcpy(RCMapObj *dest, RCMapObj *orig)
{
     STRcpy(dest->view, orig->view);
     STRcpy(dest->displaycmd, orig->displaycmd);
     STRcpy(dest->printcmd, orig->printcmd);
}