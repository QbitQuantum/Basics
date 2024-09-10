/*!

  \brief  Is SBR setting available.
  \return a flag indicating success: yes (1) or no (0)

****************************************************************************/
unsigned int
IsSbrSettingAvail (unsigned int bitrate,
                   unsigned int numOutputChannels,
                   unsigned int sampleRateInput,
                   unsigned int *sampleRateCore
                   )
{
  int idx = INVALID_TABLE_IDX;

  COUNT_sub_start("IsSbrSettingAvail");

  MOVE(1); /* counting previous operation */

  ADD(1); BRANCH(1);
  if (sampleRateInput < 32000)
  {
    COUNT_sub_end();
    return 0;
  }

  DIV(1); STORE(1);
  *sampleRateCore = sampleRateInput/2;

  FUNC(3);
  idx = getSbrTuningTableIndex(bitrate,numOutputChannels, *sampleRateCore);

  ADD(1); BRANCH(1); /* counting post-operation */

  COUNT_sub_end();

  return (idx == INVALID_TABLE_IDX) ? 0 : 1;
}