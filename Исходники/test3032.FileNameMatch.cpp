   void genFile()
    {
     file_len=random.select(1,Len);

     fill(Range(file,file_len),file_sym);
    }