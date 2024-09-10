//------------------------------------------------------------------------------
bool UnixRedBookDevice::getTrackCount(U32 * numTracks)
{
#if !defined(__FreeBSD__)
   if(!mAcquired)
   {
      setLastError("Device has not been acquired");
      return(false);
   }

   if (!updateStatus())
      return false;

   AssertFatal(mCD, "mCD is NULL");
   *numTracks = mCD->numtracks;

   return(true);
#endif	// !defined(__FreeBSD__)
}