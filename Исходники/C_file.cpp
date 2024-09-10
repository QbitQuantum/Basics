   virtual bool Read(void *mem, dword len){

      dword left = top - curr;
      if(len > left)
         //THROW(FILE_ERR_EOF);
         return false;
      MemCpy(mem, curr, len);
      curr += len;
      return true;
   }