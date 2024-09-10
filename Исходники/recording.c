void AssertFreeDiskSpace(int Priority, bool Force)
{
  static cMutex Mutex;
  cMutexLock MutexLock(&Mutex);
  // With every call to this function we try to actually remove
  // a file, or mark a file for removal ("delete" it), so that
  // it will get removed during the next call.
  static time_t LastFreeDiskCheck = 0;
  int Factor = (Priority == -1) ? 10 : 1;
  if (Force || time(NULL) - LastFreeDiskCheck > DISKCHECKDELTA / Factor) {
     if (!VideoFileSpaceAvailable(MINDISKSPACE)) {
        // Make sure only one instance of VDR does this:
        cLockFile LockFile(VideoDirectory);
        if (!LockFile.Lock())
           return;
        // Remove the oldest file that has been "deleted":
        isyslog("low disk space while recording, trying to remove a deleted recording...");
        cThreadLock DeletedRecordingsLock(&DeletedRecordings);
        if (DeletedRecordings.Count()) {
           cRecording *r = DeletedRecordings.First();
           cRecording *r0 = NULL;
           while (r) {
                 if (IsOnVideoDirectoryFileSystem(r->FileName())) { // only remove recordings that will actually increase the free video disk space
                    if (!r0 || r->start < r0->start)
                       r0 = r;
                    }
                 r = DeletedRecordings.Next(r);
                 }
           if (r0 && r0->Remove()) {
              DeletedRecordings.Del(r0);
              LastFreeDiskCheck += REMOVELATENCY / Factor;
              return;
              }
           }
        else {
           // DeletedRecordings was empty, so to be absolutely sure there are no
           // deleted recordings we need to double check:
           DeletedRecordings.Update(true);
           if (DeletedRecordings.Count())
              return; // the next call will actually remove it
           }
        // No "deleted" files to remove, so let's see if we can delete a recording:
        isyslog("...no deleted recording found, trying to delete an old recording...");
        cThreadLock RecordingsLock(&Recordings);
        if (Recordings.Count()) {
           cRecording *r = Recordings.First();
           cRecording *r0 = NULL;
           while (r) {
                 if (IsOnVideoDirectoryFileSystem(r->FileName())) { // only delete recordings that will actually increase the free video disk space
                    if (!r->IsEdited() && r->lifetime < MAXLIFETIME) { // edited recordings and recordings with MAXLIFETIME live forever
                       if ((r->lifetime == 0 && Priority > r->priority) || // the recording has no guaranteed lifetime and the new recording has higher priority
                           (r->lifetime > 0 && (time(NULL) - r->start) / SECSINDAY >= r->lifetime)) { // the recording's guaranteed lifetime has expired
                          if (r0) {
                             if (r->priority < r0->priority || (r->priority == r0->priority && r->start < r0->start))
                                r0 = r; // in any case we delete the one with the lowest priority (or the older one in case of equal priorities)
                             }
                          else
                             r0 = r;
                          }
                       }
                    }
                 r = Recordings.Next(r);
                 }
           if (r0 && r0->Delete()) {
              Recordings.Del(r0);
              return;
              }
           }
        // Unable to free disk space, but there's nothing we can do about that...
        isyslog("...no old recording found, giving up");
        Skins.QueueMessage(mtWarning, tr("Low disk space!"), 5, -1);
        }
     LastFreeDiskCheck = time(NULL);
     }
}