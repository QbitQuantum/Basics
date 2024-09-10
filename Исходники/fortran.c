int system2_(char *format, char*path, int len1,int len2)
{
   char  c_name1[200],c_name2[200];
   int res;
   fName2c(format,c_name1,len1);
   fName2c(path,c_name2,len2);
   res=System(c_name1,c_name2);
   ferror_.ferror=FError;
   return res;        
}