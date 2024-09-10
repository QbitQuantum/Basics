 inline void close(){
     switch(current_file){
     case  FILE_MODE_ERR:{                   return;}
     case  FILE_MODE_RAW:{ closeFile(file1);  break;}
     case  FILE_MODE_BZ2:{ closeFile(file2);  break;}
     default:{ Perror("Unown type"); }
     }
     //printf("%d\n", current_file);
     current_file = FILE_MODE_ERR;
 }