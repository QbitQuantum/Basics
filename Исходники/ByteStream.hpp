   /// writes UTF-8 encoded string
   void WriteString(const CString& csz)
   {
      if (csz.GetLength() > std::numeric_limits<unsigned short>::max())
         throw Exception(_T("string too long!"), __FILE__, __LINE__);
      Write16(static_cast<unsigned short>(csz.GetLength()));

      USES_CONVERSION;
      LPCSTR pszaText = T2CA(static_cast<LPCTSTR>(csz));

      const unsigned char* p = reinterpret_cast<const unsigned char*>(pszaText);
      WriteBlock(p, csz.GetLength());
   }