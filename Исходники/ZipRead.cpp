//----------------------------
   virtual bool IsEof() const{
      return (curr==top && GetFileSize()==GetCurrPos());
   }