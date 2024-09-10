int main(int argc, char **argv)
{

float coordinates[8];
double parm[13];
double radius, lat, lon, dl, ds;
double corner[2];
int i, l, s, ret;
int zonecode, sphercode, rows, cols;
float orientationangle, pixelsize, upperleftx, upperlefty;
double arg2, arg3;

int LSsphdz(float coordinates[8], double *parm, double *radius, double corner[2]);
int LSutminv(double s, double l, double *lon, double *lat);
int LSutmfor(double *s, double *l, double lon, double lat);
int get_data(char *filename, int *zonecode, int *sphercode, float *orientationangle, float *pixelsize, 
             float *upperleftx, float *upperlefty, int *rows, int *cols);

if (argc < 4) {
#ifdef INV
   printf("usage: %s <file> <sample> <line>\n", argv[0]);
#else
   printf("usage: %s <file> <longitude> <latitude>\n", argv[0]);
#endif
   printf("Jim Ray, SSAI, %s\n\n", __DATE__);
   exit(0);
   }

if ( (ret = get_data(argv[1], &zonecode, &sphercode, &orientationangle, &pixelsize, 
         &upperleftx, &upperlefty, &rows, &cols)) != 0) {
   printf("Error reading file %s, cannot continue\n", argv[1]);
   exit(1);
      } 

arg2 = atof(argv[2]);
arg3 = atof(argv[3]);

coordinates[4] = (double)zonecode;
coordinates[5] = (double)sphercode;
coordinates[6] = (double)orientationangle;
coordinates[7] = (double)pixelsize;
for(i=0;i<13;i++) parm[i] = 0.0;
corner[0] = (double)upperleftx;
corner[1] = (double)upperlefty;

LSsphdz(coordinates, parm, &radius, corner);


#ifdef INV
ds = arg2;
dl = arg3;

if (ds > (double)cols) {
   printf("Sample argument (%s) exceeds number of columns in file (%d): will use %d\n", 
               argv[2], cols, cols);
   ds = (double)cols;
   }

if (dl > (double)rows) {
   printf("Sample argument (%s) exceeds number of rows in file (%d): will use %d\n", 
               argv[3], rows, rows);
   dl = (double)rows;   
   }

ret = LSutminv(ds, dl, &lon, &lat);
printf("line   %5.1f  samp   %5.1f  => long %f lat %f\n", dl, ds, lon, lat);
#else
lon = arg2;
lat = arg3;

/* We need sanity checks on these as well */

ret = LSutmfor(&ds, &dl, lon, lat);
printf("long %f lat %f => line   %f  samp   %f  \n",  lon, lat, dl, ds);
#endif
}