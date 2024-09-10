/* constants that do not change during successive pe calculations */
void prepareSfbPe(PE_CHANNEL_DATA *peChanData,
                  const float *sfbEnergy,
                  const float *sfbThreshold,
                  const float *sfbFormFactor,
                  const int     *sfbOffset,
                  const int     sfbCnt,
                  const int     sfbPerGroup,
                  const int     maxSfbPerGroup)
{
   int sfbGrp,sfb;
   int sfbWidth;
   float avgFormFactor;

   COUNT_sub_start("prepareSfbPe");

   LOOP(1);
   for(sfbGrp = 0;sfbGrp < sfbCnt;sfbGrp+=sfbPerGroup){

    PTR_INIT(6); /* pointers for sfbEnergy[],
                                 sfbThreshold[],
                                 sfbOffset[],
                                 sfbFormFactor[],
                                 peChanData->sfbNLines[],
                                 peChanData->sfbLdEnergy[]
                 */
    LOOP(1);
    for (sfb=0; sfb<maxSfbPerGroup; sfb++) {

      ADD(1); BRANCH(1);
      if (sfbEnergy[sfbGrp+sfb] > sfbThreshold[sfbGrp+sfb]) {

         ADD(1);
         sfbWidth = sfbOffset[sfbGrp+sfb+1] - sfbOffset[sfbGrp+sfb];

         /* estimate number of active lines */
         DIV(1); TRANS(1);
         avgFormFactor = (float) pow(sfbEnergy[sfbGrp+sfb]/(float)sfbWidth, 0.25f);

         DIV(1); STORE(1);
         peChanData->sfbNLines[sfbGrp+sfb] =

         sfbFormFactor[sfbGrp+sfb]/avgFormFactor;

          /* ld(sfbEn) */
         TRANS(1); MULT(1); STORE(1);
         peChanData->sfbLdEnergy[sfbGrp+sfb] = (float) (log(sfbEnergy[sfbGrp+sfb]) * LOG2_1);
      }
      else {

         MOVE(2);
         peChanData->sfbNLines[sfbGrp+sfb] = 0.0f;
         peChanData->sfbLdEnergy[sfbGrp+sfb] = 0.0f;
      }
    }
   }

   COUNT_sub_end();
}