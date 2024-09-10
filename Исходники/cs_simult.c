float cs_svd_1( int nn , int mm , float *xx , float *evec )
{
   register int ii,jj,n,m ; register float sum1,sum2,sum3 , *av ;
   float *xmat , *u1,*u2,*u3 , *v1,*v2,*v3 , *z1,*z2,*z3 ;
   int nite ;
   float g11,g21,g22,g31,g32,g33 ;

   if( nn < 3 || mm < 3 || xx == NULL ) return -1.0f ;

   n = nn ; m = mm ;

#undef  X
#define X(i,j) xmat[(i)+(j)*n]
   xmat = xx ;

   u1 = (float *)calloc(sizeof(float),n) ;
   u2 = (float *)malloc(sizeof(float)*n) ;
   u3 = (float *)malloc(sizeof(float)*n) ;
   v1 = (float *)malloc(sizeof(float)*n) ;
   v2 = (float *)malloc(sizeof(float)*n) ;
   v3 = (float *)malloc(sizeof(float)*n) ;

   z1 = (float *)malloc(sizeof(float)*m) ;
   z2 = (float *)malloc(sizeof(float)*m) ;
   z3 = (float *)malloc(sizeof(float)*m) ;

   /** initialize trial eigvevectors in u1,u2,u3 **/

   for( jj=0 ; jj < m ; jj++ ){
     av = xmat + jj*n ;
     for( ii=0 ; ii < n ; ii++ ) u1[ii] += av[ii] ;
   }
   for( ii=0 ; ii < n ; ii++ ){
     u2[ii] = drand48()-0.5 ; u3[ii] = drand48()-0.5 ;
   }

#undef  NORMALIZE
#define NORMALIZE(vec)                                    \
 do{ register float sss ; register int qq ;               \
     sss = 0.0f ;                                         \
     for( qq=0 ; qq < n ; qq++ ) sss += vec[qq]*vec[qq] ; \
     sss = 1.0f / sqrtf(sss) ;                            \
     for( qq=0 ; qq < n ; qq++ ) vec[qq] *= sss ;         \
 } while(0)

   NORMALIZE(u1) ; NORMALIZE(u2) ; NORMALIZE(u3) ;

   /*----- iteration -----*/

   for( nite=1 ; nite < 999 ; nite++ ){

     /** G = U' U = 3x3 matrix **/

     sum1 = sum2 = sum3 = 0.0f ;
     for( ii=0 ;ii < n ; ii++ ){
       sum1 += u1[ii]*u2[ii] ; sum2 += u1[ii]*u3[ii] ; sum3 += u2[ii]*u3[ii] ;
     }
     g21 = sum1 ; g31 = sum2 ; g32 = sum3 ;
     g11 =        g22 =        g33 = 1.0f ;  /* columns are normalized */

     /** Choleski factor G = L L' **/

     g21 = g21 / g11 ;
     g22 = sqrtf(g22 - g21*g21) ;
     g31 = g31 / g11 ;
     g32 = (g32 - g31*g21) / g22 ;
     g33 = sqrtf(g33 - g31*g31 - g32*g32) ;

     /** V = A U = X X' U = n x 3 matrix **/

     for( jj=0 ; jj < m ; jj++ ){
       sum1 = sum2 = sum3 = 0.0f ; av = xmat + jj*n ;
       for( ii=0 ; ii < n ; ii++ ){
         sum1 += av[ii] * u1[ii] ;
         sum2 += av[ii] * u2[ii] ;
         sum3 += av[ii] * u3[ii] ;
       }
       z1[jj] = sum1 ; z2[jj] = sum2 ; z3[jj] = sum3 ;
     }

     memset(v1,0,sizeof(float)*n) ;
     memset(v2,0,sizeof(float)*n) ;
     memset(v3,0,sizeof(float)*n) ;
     for( jj=0 ; jj < m ; jj++ ){
       sum1 = z1[jj] ; sum2 = z2[jj] ; sum3 = z3[jj] ; av = xmat + jj*n ;
       for( ii=0 ; ii < n ; ii++ ){
         v1[ii] += av[ii] * sum1 ;
         v2[ii] += av[ii] * sum2 ;
         v3[ii] += av[ii] * sum3 ;
       }
     }

     /** H = U' V = 3x3 matrix (symmetric) **/

     sum1 = sum2 = sum3 = 0.0f ;
     for( ii=0 ; ii < n ; ii++ ){
       sum1 += u1[ii] * v1[ii] ;
       sum2 += u1[ii] * v2[ii] ;
       sum3 += u1[ii] * v3[ii] ;
     }
     h11 = sum1 ; h12 = h21 = sum2 ; h13 = h31 = sum3 ;

     sum1 = sum2 = sum3 = 0.0f ;
     for( ii=0 ; ii < n ; ii++ ){
       sum1 += u2[ii] * v2[ii] ;
       sum2 += u2[ii] * v3[ii] ;
       sum3 += u3[ii] * v3[ii] ;
     }
     h22 = sum1 ; h23 = h32 = sum2 ; h33 = sum3 ;