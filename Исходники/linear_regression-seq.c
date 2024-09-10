int main(int argc, char *argv[]) {

   int fd;
   char * fdata;
   char * fname;
   struct stat finfo;
   long i;


   // Make sure a filename is specified
   if (argv[1] == NULL)
   {
      printf("USAGE: %s <filename>\n", argv[0]);
      exit(1);
   }
   
   fname = argv[1];

   printf("Linear Regression Serial: Running...\n");
   
   // Read in the file
   CHECK_ERROR((fd = open(fname, O_RDONLY)) < 0);
   // Get the file info (for file length)
   CHECK_ERROR(fstat(fd, &finfo) < 0);
   // Memory map the file
   CHECK_ERROR((fdata = mmap(0, finfo.st_size + 1, 
      PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == NULL);


   POINT_T *points = (POINT_T*)fdata;
   long long n = (long long) finfo.st_size / sizeof(POINT_T);
   long long SX_ll = 0, SY_ll = 0, SXX_ll = 0, SYY_ll = 0, SXY_ll = 0;
   
   // ADD UP RESULTS
   for (i = 0; i < n; i++)
   {
      //Compute SX, SY, SYY, SXX, SXY
      SX_ll  += points[i].x;
      SXX_ll += points[i].x*points[i].x;
      SY_ll  += points[i].y;
      SYY_ll += points[i].y*points[i].y;
      SXY_ll += points[i].x*points[i].y;
   }

   double a, b, xbar, ybar, r2;
   double SX = (double)SX_ll;
   double SY = (double)SY_ll;
   double SXX= (double)SXX_ll;
   double SYY= (double)SYY_ll;
   double SXY= (double)SXY_ll;

   b = (double)(n*SXY - SX*SY) / (n*SXX - SX*SX);
   a = (SY_ll - b*SX_ll) / n;
   xbar = (double)SX_ll / n;
   ybar = (double)SY_ll / n;
   r2 = (double)(n*SXY - SX*SY) * (n*SXY - SX*SY) / ((n*SXX - SX*SX)*(n*SYY - SY*SY));


   printf("Linear Regression Serial Results:\n");
   printf("\ta    = %lf\n", a);
   printf("\tb    = %lf\n", b);
   printf("\txbar = %lf\n", xbar);
   printf("\tybar = %lf\n", ybar);
   printf("\tr2   = %lf\n", r2);
   printf("\tSX   = %lld\n", SX_ll);
   printf("\tSY   = %lld\n", SY_ll);
   printf("\tSXX  = %lld\n", SXX_ll);
   printf("\tSYY  = %lld\n", SYY_ll);
   printf("\tSXY  = %lld\n", SXY_ll);

   CHECK_ERROR(munmap(fdata, finfo.st_size + 1) < 0);
   CHECK_ERROR(close(fd) < 0);

   return 0;
}