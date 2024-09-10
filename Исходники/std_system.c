 struct hostent *Gethostbyname(const char *name) {
    struct hostent *hp;
    if((hp = gethostbyname(name)) == NULL) {
       switch(h_errno) {
         case TRY_AGAIN:      fprintf(stdout," Warning: Gethostbyname returned TRY_AGAIN.\n");
                              fflush(stdout);  return Gethostbyname(name); break;
         case NO_DATA:        fprintf(stdout," Error: Gethostbyname(%s) returned NO_DATA.\n",name); break;
         case NO_RECOVERY:    fprintf(stdout," Error: Gethostbyname(%s) returned NO_RECOVERY.\n",name); break;
         case HOST_NOT_FOUND: fprintf(stdout," Error: Gethostbyname(%s) returned HOST_NOT_FOUND.\n",name); break;
         default:             fprintf(stdout," Error: Gethostbyname(%s) returned an unknown error (%s).\n",name,DDI_Id()); break;
       } 
       Fatal_error(911);
    }
    return hp;
 }