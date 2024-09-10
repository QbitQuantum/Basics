void Babai (int kappa, F_mpz_mat_t B, double **mu, double **r, double *s, 
       double **appB, int *expo, double **appSP, 
       int a, int zeros, int kappamax, int n)
{
   int i, j, k, test, aa, exponent;
   signed long xx;
   double tmp, rtmp;
   
   aa = (a > zeros) ? a : zeros + 1;
  
   do
   {
      test = 0;
      
#ifdef DEBUG
      if (loops++ > LOOPS_BABAI) 
      {
	      printf("INFINITE LOOP?\n"); 
	      abort();
      }
#endif 
      
      /* ************************************** */
      /* Step2: compute the GSO for stage kappa */
      /* ************************************** */
      
      for (j = aa; j < kappa; j++)
	   {	  
	      if (appSP[kappa][j] != appSP[kappa][j]) // if appSP[kappa][j] == NAN
	      {
	         appSP[kappa][j] = d_vec_scalar_product(appB[kappa], appB[j], n);
	      }
	  	  
         if (j > zeros + 2)
	      {
	         tmp = mu[j][zeros+1] * r[kappa][zeros+1];
	         rtmp = appSP[kappa][j] - tmp;
	         for (k = zeros + 2; k < j - 1; k++)
		      {
		         tmp = mu[j][k] * r[kappa][k];
		         rtmp = rtmp - tmp;
		      }
	         tmp = mu[j][j-1] * r[kappa][j-1];
	         r[kappa][j] = rtmp - tmp;
         } else if (j == zeros+2)
	      {
	         tmp = mu[j][zeros+1] * r[kappa][zeros+1];
	         r[kappa][j] = appSP[kappa][j] - tmp;
	      } else r[kappa][j] = appSP[kappa][j];

	      mu[kappa][j] = r[kappa][j] / r[j][j];
      }
      
      /* **************************** */
      /* Step3--5: compute the X_j's  */
      /* **************************** */
      
      for (j = kappa - 1; j > zeros; j--)
	   {

	      /* test of the relaxed size-reduction condition */
	      tmp = fabs(mu[kappa][j]);
	      tmp = ldexp(tmp, expo[kappa] - expo[j]);
	  
	      if (tmp > halfplus) 
	      {
	         test = 1; 
	         exponent = expo[j] - expo[kappa];
	      
	         /* we consider separately the cases X = +-1 */     
	         if (tmp <= onedothalfplus)   
		      {		  
		         if (mu[kappa][j] >= 0)   /* in this case, X is 1 */
               {
		            for (k = zeros + 1; k < j; k++)
			         {
			            tmp = ldexp (mu[j][k], exponent);
			            mu[kappa][k] =  mu[kappa][k] - tmp; 
			         }
		      
		            F_mpz_mat_row_sub(B, kappa, B, kappa, B, j, 0, n);
		  
		         } else          /* otherwise X is -1 */ 
               {
                  for (k=zeros+1; k<j; k++)
			         {
			            tmp = ldexp (mu[j][k], exponent);
			            mu[kappa][k] = mu[kappa][k] + tmp;
			         }
		      
                  F_mpz_mat_row_add(B, kappa, B, kappa, B, j, 0, n); 
               }
		      } else   /* we must have |X| >= 2 */
		      {
		         tmp = ldexp (mu[kappa][j] , -exponent);

	            if ((tmp < (double) MAX_LONG) &&(tmp > (double) -MAX_LONG))  
		         {
		            tmp = rint (tmp); 
		      
		            for (k = zeros + 1; k < j; k++)
			         {
			            rtmp = tmp * mu[j][k];
			            rtmp = ldexp (rtmp, exponent);
			            mu[kappa][k] = mu[kappa][k] - rtmp;
			         }

		            xx = (long) tmp;
		      
                  if (xx > 0L)
                  { 
                     F_mpz_mat_row_submul_ui(B, kappa, B, j, 0, n, (ulong) xx);  
                  } else
                  {
                     F_mpz_mat_row_addmul_ui(B, kappa, B, j, 0, n, (ulong) -xx);  
                  } 
               } else
		         {
		            tmp = frexp(mu[kappa][j], &exponent); 
		            tmp = tmp * MAX_LONG;
		            xx = (long) tmp;
		            exponent += expo[kappa] - expo[j] - CPU_SIZE_1;

		            /* This case is extremely rare: never happened for me */
		            if (exponent <= 0) 
			         {
			            xx = xx << -exponent;
			            exponent = 0;
			  
			            if (xx > 0)
                     {
                        F_mpz_mat_row_submul_ui(B, kappa, B, j, 0, n, xx);  
                     } else
                     {
                        F_mpz_mat_row_addmul_ui(B, kappa, B, j, 0, n, -xx);  
                     }
              			    
			            for (k = zeros + 1; k < j; k++)
			            {
                        rtmp = ((double) xx) * mu[j][k];
			               rtmp = ldexp (rtmp, expo[j] - expo[kappa]);
			               mu[kappa][k] = mu[kappa][k] - rtmp;
			            }
			         } else
			         {
			            if (xx > 0)
                     {
                        F_mpz_mat_row_submul_2exp_ui(B, kappa, B, j, 0, n, (ulong) xx, exponent);  
                     } else
                     {
                        F_mpz_mat_row_addmul_2exp_ui(B, kappa, B, j, 0, n, (ulong) -xx, exponent);  
                     }
			            for (k = zeros + 1; k < j; k++)
			            {
			               rtmp = ((double) xx) * mu[j][k];
			               rtmp = ldexp (rtmp, exponent + expo[j] - expo[kappa]);
			               mu[kappa][k] = mu[kappa][k] - rtmp;
					      }
				      }	    
			      }
		      }
		   }
	   }

      if (test)   /* Anything happened? */
	   {
	      expo[kappa] = F_mpz_mat_set_line_d(appB[kappa], B, kappa, n);
	      aa = zeros + 1;
	      for (i = zeros + 1; i <= kappa; i++) 
	         appSP[kappa][i] = NAN;//0.0/0.0;
	      for (i = kappa + 1; i <= kappamax; i++) 
	         appSP[i][kappa] = NAN;//0.0/0.0;
	   }
   } while (test);

   if (appSP[kappa][kappa] != appSP[kappa][kappa]) 
   {
      appSP[kappa][kappa] = d_vec_norm(appB[kappa], n);
   }
   s[zeros + 1] = appSP[kappa][kappa];
  
   for (k = zeros + 1; k < kappa - 1; k++)
   {
      tmp = mu[kappa][k] * r[kappa][k];
      s[k+1] = s[k] - tmp;
   }
}