void Meter::UpdateDisplay(int numChannels, int numFrames, float *sampleData)
{
   int i, j;
   float *sptr = sampleData;
   int num = intmin(numChannels, mNumBars);
   MeterUpdateMsg msg;

   msg.numFrames = numFrames;
   for(j=0; j<mNumBars; j++) {
      msg.peak[j] = 0;
      msg.rms[j] = 0;
      msg.clipping[j] = false;
      msg.headPeakCount[j] = 0;
      msg.tailPeakCount[j] = 0;
   }

   for(i=0; i<numFrames; i++) {
      for(j=0; j<num; j++) {
         msg.peak[j] = floatMax(msg.peak[j], sptr[j]);
         msg.rms[j] += sptr[j]*sptr[j];

         // In addition to looking for mNumPeakSamplesToClip peaked
         // samples in a row, also send the number of peaked samples
         // at the head and tail, in case there's a run of 
         // Send the number of peaked samples at the head and tail,
         // in case there's a run of peaked samples that crosses
         // block boundaries
         if (fabs(sptr[j])>=MAX_AUDIO) {
            if (msg.headPeakCount[j]==i)
               msg.headPeakCount[j]++;
            msg.tailPeakCount[j]++;
            if (msg.tailPeakCount[j] > mNumPeakSamplesToClip)
               msg.clipping[j] = true;
         }
         else
            msg.tailPeakCount[j] = 0;
      }
      sptr += numChannels;
   }
   for(j=0; j<mNumBars; j++)
      msg.rms[j] = sqrt(msg.rms[j]/numFrames);

   if (mDB) {
      for(j=0; j<mNumBars; j++) {
         msg.peak[j] = ToDB(msg.peak[j], mDBRange);
         msg.rms[j] = ToDB(msg.rms[j], mDBRange);
      }
   }

   mQueue.Put(msg);
}