float LayerNet::conjgrad (
   TrainingSet *tptr , // Training set to use
   int maxits ,        // Maximum iterations allowed
   float reltol ,     // Relative error change tolerance
   float errtol       // Quit if error drops this low
   )
{
   int i, j, n, iter, pnum, key, retry, max_retry ;
   float gam, *g, *h, *outdelta, *hid2delta, *grad, *base ;
   float corr, error, *cptr, *gptr, *pptr, maxgrad ;
   float prev_err ;
   char msg[80];
   max_retry = 5 ;

/*
   Allocate work memory
*/

   MEMTEXT ( "CONJGRAD work" ) ;
   if (nhid2) {
      hid2delta = (float *) MALLOC ( nhid2 * sizeof(float) ) ;
      if (hid2delta == NULL)
         return -2.0 ;
      }
   else
      hid2delta = NULL ;

   outdelta = (float *) MALLOC ( nout * sizeof(float) ) ;

   if (nhid1 == 0)               // No hidden layer
      n = nout * (nin+1) ;
   else if (nhid2 == 0)          // One hidden layer
      n = nhid1 * (nin+1) + nout * (nhid1+1) ;
   else                          // Two hidden layers
      n = nhid1 * (nin+1) + nhid2 * (nhid1+1) + nout * (nhid2+1) ;

   grad = (float *) MALLOC ( n * sizeof(float) ) ;
   base = (float *) MALLOC ( n * sizeof(float) ) ;
   g = (float *) MALLOC ( n * sizeof(float) ) ;
   h = (float *) MALLOC ( n * sizeof(float) ) ;

   if ((outdelta == NULL) || (grad == NULL) ||
       (base == NULL) || (g == NULL) || (h == NULL)) {
      if (hid2delta != NULL)
         FREE ( hid2delta ) ;
      if (outdelta != NULL)
         FREE ( outdelta ) ;
      if (grad != NULL)
         FREE ( grad ) ;
      if (base != NULL)
	 FREE ( base ) ;
      if (g != NULL)
         FREE ( g ) ;
      if (h != NULL)
         FREE ( h ) ;
      return -2.0 ;   // Flags error
      }

   prev_err = 1.e30 ;
   error = find_grad ( tptr , hid2delta , outdelta , grad ) ;

   memcpy ( g , grad , n * sizeof(float) ) ;
   memcpy ( h , grad , n * sizeof(float) ) ;

/*
   Main iteration loop is here
*/

   for (iter=0 ; iter<maxits ; iter++) {  // Each iter is an epoch

/*
   Check current error against user's max.  Abort if user pressed ESCape
*/
      sprintf ( msg , "Gradient Finding...Iter Nø %d : Error = %lf %%", iter, 100.0 * error ) ;
      normal_message ( msg ) ;
      if (error <= errtol)   // If our error is within user's limit
	 break ;             // then we are done!

      if (error <= reltol)   // Generally not necessary: reltol<errtol in
         break ;             // practice, but help silly users

      if (kbhit()) {         // Was a key pressed?
         key = getch () ;    // Read it if so
         while (kbhit())     // Flush key buffer in case function key
            getch () ;       // or key was held down
         if (key == 27) {    // ESCape
            error = -error ; // Flags user that ESCape was pressed
            break ;
            }
         }

      prev_err = error ;
      error = direcmin ( tptr , error , 10 , 1.e-10 ,
                         0.5 , base , grad ) ;
      if (error < 0.0)  // Indicates user pressed ESCape
         goto CGFINISH ;

      if ((2.0 * (prev_err - error)) <=       // If this direc gave poor result
          (reltol * (prev_err + error + 1.e-10))) { // will use random direc
         prev_err = error ;                   // But first exhaust grad
         error = find_grad ( tptr , hid2delta , outdelta , grad ) ;
         error = direcmin ( tptr , error , 15 , 1.e-10 ,
                            1.e-3 , base , grad ) ;
         for (retry=0 ; retry<max_retry ; retry++) {
            for (i=0 ; i<n ; i++)
	       grad[i] = (float) (rand() - RANDMAX/2) / (RANDMAX * 10.0) ;
            error = direcmin ( tptr , error , 10 , 1.e-10 ,
                               1.e-2 , base , grad ) ;
            if (error < 0.0)  // Indicates user pressed ESCape
               goto CGFINISH ;
            if (retry < max_retry/2)
               continue ;
            if ((2.0 * (prev_err - error)) >
                (reltol * (prev_err + error + 1.e-10)))
               break ;   // Get out of retry loop if we improved enough
            } // For retry
         if (retry == max_retry)   // If we exhausted all tries
            break ;                // probably hopeless
	 memcpy ( g , grad , n * sizeof(float) ) ;
	 memcpy ( h , grad , n * sizeof(float) ) ;
         } // If this dir gave poor result

      prev_err = error ;

/*
   Setup for next iteration
*/

      error = find_grad ( tptr , hid2delta , outdelta , grad ) ;
      gam = gamma ( g , grad ) ;
      if (gam < 0.0)
         gam = 0.0 ;
      if (gam > 1.0)
         gam = 1.0 ;

      find_new_dir ( gam , g , h , grad ) ;
      }  // This is the end of the main iteration loop

/*
   Free work memory
*/

CGFINISH:
   MEMTEXT ( "CONJGRAD work" ) ;
   if (hid2delta != NULL)
      FREE ( hid2delta ) ;
   FREE ( outdelta ) ;
   FREE ( grad ) ;
   FREE ( base ) ;
   FREE ( g ) ;
   FREE ( h ) ;

   return error ;
}