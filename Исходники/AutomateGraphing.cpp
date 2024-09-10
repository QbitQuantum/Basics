void CAutomateGraphingApp::Process(void)
   {
   // prepare variables
   CString sTempName;
   if(m_sData->bJpeg)
      sTempName.Format("%s.tif", _tempnam("c:\\tmp", "steg"));
   // read parameters
   ReadParameters();
   // write file header
   WriteHeader();
   // main processing loop
   libbase::timer tDuration;
   for(double dStrength = m_sData->dStrengthMin; dStrength <= m_sData->dStrengthMax; dStrength += m_sData->dStrengthStep)
      {
      PlayeventFilterEmbed(/*embedding*/ 0, 1, dStrength, \
                           /*interleaver*/ true, 0, 1, \
                           /*source*/ 2, 1, "", \
                           /*codec*/ "", "");
      if(m_sData->bJpeg)
         {
         for(int nJpegQ = m_sData->nJpegMin; nJpegQ <= m_sData->nJpegMax; nJpegQ += m_sData->nJpegStep)
            {
            // write row header
            std::ofstream file(m_sData->sResults, std::ios::out | std::ios::app);
            file << dStrength << "\t" << nJpegQ << "\t";
            file.close();
            // simulate JPEG channel
            PlayeventSaveJPEG(nJpegQ, sTempName, true);
            PlayeventOpen(sTempName);
            remove(sTempName);
            // main processing
            DoExtract(dStrength);
            PlayeventClose(false);
            }
         }
      else
         {
         // write row header
         std::ofstream file(m_sData->sResults, std::ios::out | std::ios::app);
         file << dStrength << "\t";
         file.close();
         // main processing
         DoExtract(dStrength);
         PlayeventSelectState(-3);
         }
      PlayeventSelectState(-1);
      }
   // tell the user how long it took
   tDuration.stop();
   CString sTemp;
   sTemp.Format("Time taken: %s", std::string(tDuration).c_str());
   MessageBox(NULL, sTemp, "Automate Graphing", MB_OK);
   }