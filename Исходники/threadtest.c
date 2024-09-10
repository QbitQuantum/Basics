void myFunc(void *param) {
   t *args = (t*) param;
   uint16_T *x = args->data1;
   uint16_T  *y = args->data2;
   printf("x=%d, y=%d\n", x, y);
   free(args);
   _endthreadex( 0 );
};