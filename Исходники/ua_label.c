/*
 * NOTE! This routine opens the SD socket but leaves it open
 */
static bool send_label_request(UAContext *ua, MEDIA_DBR *mr, MEDIA_DBR *omr,
                               POOL_DBR *pr, int relabel, bool media_record_exists,
                               int drive)
{
   BSOCK *sd;
   char dev_name[MAX_NAME_LENGTH];
   bool ok = false;
   bool is_dvd = false;
   uint64_t VolBytes = 0;

   if (!(sd=open_sd_bsock(ua))) {
      return false;
   }
   bstrncpy(dev_name, ua->jcr->wstore->dev_name(), sizeof(dev_name));
   bash_spaces(dev_name);
   bash_spaces(mr->VolumeName);
   bash_spaces(mr->MediaType);
   bash_spaces(pr->Name);
   if (relabel) {
      bash_spaces(omr->VolumeName);
      sd->fsend("relabel %s OldName=%s NewName=%s PoolName=%s "
                     "MediaType=%s Slot=%d drive=%d",
                 dev_name, omr->VolumeName, mr->VolumeName, pr->Name, 
                 mr->MediaType, mr->Slot, drive);
      ua->send_msg(_("Sending relabel command from \"%s\" to \"%s\" ...\n"),
         omr->VolumeName, mr->VolumeName);
   } else {
      sd->fsend("label %s VolumeName=%s PoolName=%s MediaType=%s "
                     "Slot=%d drive=%d",
                 dev_name, mr->VolumeName, pr->Name, mr->MediaType, 
                 mr->Slot, drive);
      ua->send_msg(_("Sending label command for Volume \"%s\" Slot %d ...\n"),
         mr->VolumeName, mr->Slot);
      Dmsg6(100, "label %s VolumeName=%s PoolName=%s MediaType=%s Slot=%d drive=%d\n",
         dev_name, mr->VolumeName, pr->Name, mr->MediaType, mr->Slot, drive);
   }

   while (sd->recv() >= 0) {
      int dvd;
      ua->send_msg("%s", sd->msg);
      if (sscanf(sd->msg, "3000 OK label. VolBytes=%llu DVD=%d ", &VolBytes,
                 &dvd) == 2) {
         is_dvd = dvd;
         ok = true;
      }
   }
   unbash_spaces(mr->VolumeName);
   unbash_spaces(mr->MediaType);
   unbash_spaces(pr->Name);
   mr->LabelDate = time(NULL);
   mr->set_label_date = true;
   if (is_dvd) {
      /* We know that a freshly labelled DVD has 1 VolParts */
      /* This does not apply to auto-labelled DVDs. */
      mr->VolParts = 1;
   }
   if (ok) {
      if (media_record_exists) {      /* we update it */
         mr->VolBytes = VolBytes;
         mr->InChanger = mr->Slot > 0;  /* if slot give assume in changer */
         mr->StorageId = ua->jcr->wstore->StorageId;
         if (!db_update_media_record(ua->jcr, ua->db, mr)) {
             ua->error_msg("%s", db_strerror(ua->db));
             ok = false;
         }
      } else {                        /* create the media record */
         set_pool_dbr_defaults_in_media_dbr(mr, pr);
         mr->VolBytes = VolBytes;
         mr->InChanger = mr->Slot > 0;  /* if slot give assume in changer */
         mr->StorageId = ua->jcr->wstore->StorageId;
         mr->Enabled = 1;
         if (db_create_media_record(ua->jcr, ua->db, mr)) {
            ua->info_msg(_("Catalog record for Volume \"%s\", Slot %d  successfully created.\n"),
            mr->VolumeName, mr->Slot);
            /* Update number of volumes in pool */
            pr->NumVols++;
            if (!db_update_pool_record(ua->jcr, ua->db, pr)) {
               ua->error_msg("%s", db_strerror(ua->db));
            }
         } else {
            ua->error_msg("%s", db_strerror(ua->db));
            ok = false;
         }
      }
   } else {
      ua->error_msg(_("Label command failed for Volume %s.\n"), mr->VolumeName);
   }
   return ok;
}