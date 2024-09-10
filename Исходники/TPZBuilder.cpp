TPZBuilder :: TPZBuilder(const TPZString& sgmlFile)
            : m_FileName(sgmlFile),
              m_TagArray(0)
{
   m_SgmlFile = new ifstream(sgmlFile);
   if( ! m_SgmlFile->good() )
   {
      TPZString err;
      err.sprintf(ERR_TPZBLDR_001, (char*)sgmlFile);
      EXIT_PROGRAM(err);
   }
}