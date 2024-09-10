 FileToString() {
   pipe(FD);
   input = fdopen(FD[1], "w");
 }