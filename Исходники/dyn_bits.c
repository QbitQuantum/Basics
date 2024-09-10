int
dynBitCount(const short          *quantSpectrum,
            const unsigned short   *maxValueInSfb,
            const signed short     *scalefac,
            const int             blockType,
            const int             sfbCnt,
            const int             maxSfbPerGroup,
            const int             sfbPerGroup,
            const int            *sfbOffset,
            SECTION_DATA         *sectionData)
{
  int bitLookUp[MAX_SFB_LONG][CODE_BOOK_ESC_NDX + 1];
  int mergeGainLookUp[MAX_SFB_LONG];

  COUNT_sub_start("dynBitCount");

  INDIRECT(3); MOVE(3);
  sectionData->blockType      = blockType;
  sectionData->sfbCnt         = sfbCnt;
  sectionData->sfbPerGroup    = sfbPerGroup;

  INDIRECT(1); DIV(1); STORE(1);
  sectionData->noOfGroups     = sfbCnt / sfbPerGroup;

  MOVE(1);
  sectionData->maxSfbPerGroup = maxSfbPerGroup;

  FUNC(7);
  noiselessCounter(sectionData,
                   mergeGainLookUp,
                   bitLookUp,
                   quantSpectrum,
                   maxValueInSfb,
                   sfbOffset,
                   blockType);

  FUNC(3);
  scfCount(scalefac,
           maxValueInSfb,
           sectionData);

  INDIRECT(3); ADD(2); /* counting post-operations */

  COUNT_sub_end();

  return (sectionData->huffmanBits +
          sectionData->sideInfoBits +
          sectionData->scalefacBits);
}