   // write extecutable
   void CodeGenProl16::WriteIex(std::wstring const& fileName)
   {
	   //os.write(reinterpret_cast<char const*>(mpBuffer), mBufPos);

      FILE *stream = _wfopen(fileName.data(), L"wb");
      if (stream != NULL)
      {
         int written = fwrite(mpBuffer, sizeof(BYTE), mBufPos, stream);
         if (written != mBufPos)
         {
			 wprintf(L"write file '%s' failed: %s", fileName, __wcserror(NULL));
         }
         fclose(stream);
      }
      else
      {
		  wprintf(L"open file '%s' failed: %s", fileName, __wcserror(NULL));
      }
   }