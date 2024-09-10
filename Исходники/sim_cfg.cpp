VOID Config::setScenarioFile(S8* filename) throw (ErrCodeEn)
{
   if (NULL == filename || STRLEN(filename) == 0)
   {
      LOG_FATAL("Invalid Scenario file");
      throw ERR_INV_CMD_LINE_PARAM;
   }
   
   if (0 == STRNCMP(filename, "--", 2))
   {
      throw ERR_INV_CMD_LINE_PARAM;
   }

   pCfg->scnFile.assign(filename);
}