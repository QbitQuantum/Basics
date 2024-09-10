/*
 * We get the volume name from the SD
 */
char *get_volume_name_from_SD(UAContext *ua, int Slot, int drive)
{
   BSOCK *sd;
   STORERES *store = ua->jcr->res.wstore;
   char dev_name[MAX_NAME_LENGTH];
   char *VolName = NULL;
   int rtn_slot;

   if (!(sd = open_sd_bsock(ua))) {
      ua->error_msg(_("Could not open SD socket.\n"));
      return NULL;
   }
   bstrncpy(dev_name, store->dev_name(), sizeof(dev_name));
   bash_spaces(dev_name);

   /*
    * Ask storage daemon to read the label of the volume in a
    * specific slot of the autochanger using the drive number given.
    * This could change the loaded volume in the drive.
    */
   sd->fsend(readlabelcmd, dev_name, Slot, drive);
   Dmsg1(100, "Sent: %s", sd->msg);

   /*
    * Get Volume name in this Slot
    */
   while (sd->recv() >= 0) {
      ua->send_msg("%s", sd->msg);
      Dmsg1(100, "Got: %s", sd->msg);
      if (strncmp(sd->msg, NT_("3001 Volume="), 12) == 0) {
         VolName = (char *)malloc(sd->msglen);
         if (sscanf(sd->msg, readlabelresponse, VolName, &rtn_slot) == 2) {
            break;
         }
         free(VolName);
         VolName = NULL;
      }
   }
   close_sd_bsock(ua);
   Dmsg1(100, "get_vol_name=%s\n", NPRT(VolName));
   return VolName;
}