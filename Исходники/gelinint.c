        DBstatus GE706(
        DBAny  *pstr1,
        DBAny  *pstr2,
        short  *noint,
        DBfloat u1[],
        DBfloat u2[])

/*      Compute intersect between line and arc/circle in 2D.
 *
 *      In: pstr1  => First entity
 *          pstr2  => Second entity
 *          noint  => Requested solution +/-
 *
 *      Out: *noint => Number of solutions
 *           *u1    => Parametric values related to the line
 *           *u2    => Parameteric values related to the arc
 *
 *      (C)microform ab  5/8/85 R. Svedin efter IVAR
 *
 *       12/8/85  Anpassning till v3, J.Kjellander
 *       3/1/86   Tangering, J. Kjellander
 *       15/1/86  Bug lodrät linje, J. Kjellander
 *       13/4/86  Bytt TOL1 mot TOL2, J. Kjellander
 *       19/4/86  Horisontell linje, J. Kjellander
 *       26/11/89 Neg intnr, J. Kjellander
 *       1999-05-10 Rewritten, J.Kjellander
 *
 ******************************************************************!*/

  {
   DBLine *linpek;
   DBArc  *arcpek;
   DBfloat k,k2,p,q,dx,dy;
   DBfloat x1,y1,x2,y2,tt,tmp;
   DBfloat t1[2],t2[2];
   short   i;

/*
***Which is which ?
*/
   if ( pstr1->hed_un.type == LINTYP )
      {
      linpek = (GMLIN *)pstr1;
      arcpek = (GMARC *)pstr2;
      }
   else
      {
      linpek = (GMLIN *)pstr2;
      arcpek = (GMARC *)pstr1;
      }
/*
***Some init.
*/
   dx = linpek->crd2_l.x_gm - linpek->crd1_l.x_gm;
   dy = linpek->crd2_l.y_gm - linpek->crd1_l.y_gm;
/*
***Vertical, horisontal or sloping line ?
*
***Horisontal.
*/
   if ( ABS(dx) > 1000.0*ABS(dy) )
      {
      if ( ABS(linpek->crd1_l.y_gm-arcpek->y_a)-arcpek->r_a  > TOL2 )
         {
         *noint = 0;
         return(0);
         }

      y1 = y2 = linpek->crd1_l.y_gm;

      if ( arcpek->r_a > ABS(linpek->crd1_l.y_gm-arcpek->y_a) )
        {
        x1 = arcpek->x_a + arcpek->r_a*COS(ASIN((linpek->
             crd1_l.y_gm-arcpek->y_a)/arcpek->r_a));
        x2 = 2.0*arcpek->x_a - x1;
        }
      else
        {
        x1 = x2 = arcpek->x_a;
        }

      t1[0] = 1.0 + (x1 - linpek->crd1_l.x_gm) / dx;
      t1[1] = 1.0 + (x2 - linpek->crd1_l.x_gm) / dx;
      }
/*
***Vertical.
*/
   else if ( ABS(dy) > 1000.0*ABS(dx) )
      {
      if ( ABS(linpek->crd1_l.x_gm-arcpek->x_a)-arcpek->r_a  > TOL2 )
         {
         *noint = 0;
         return(0);
         }

      x1 = x2 = linpek->crd1_l.x_gm;

      if ( arcpek->r_a > ABS(linpek->crd1_l.x_gm-arcpek->x_a) )
        {
        y1 = arcpek->y_a + arcpek->r_a*SIN(ACOS((linpek->
             crd1_l.x_gm-arcpek->x_a)/arcpek->r_a));
        y2 = 2.0*arcpek->y_a - y1;
        }
      else
        {
        y1 = y2 = arcpek->y_a;
        }

      t1[0] = 1.0 + (y1 - linpek->crd1_l.y_gm) / dy;
      t1[1] = 1.0 + (y2 - linpek->crd1_l.y_gm) / dy;
      }
/*
***Sloping.
*/
   else
      {
      k  = dy/dx;
      k2 = k*k;

      p = (arcpek->x_a + k2 * linpek->crd1_l.x_gm - k *
          (linpek->crd1_l.y_gm - arcpek->y_a)) / (1.0 + k2);

      q = (arcpek->x_a * arcpek->x_a + k2 * linpek->crd1_l.x_gm *
          linpek->crd1_l.x_gm + 2.0 * k * linpek->crd1_l.x_gm * 
          (arcpek->y_a - linpek->crd1_l.y_gm) + (linpek->crd1_l.y_gm - 
          arcpek->y_a) * (linpek->crd1_l.y_gm - arcpek->y_a) - 
          arcpek->r_a * arcpek->r_a) / (1.0 + k2);
/*
***Do they intersect ?
*/
      if ( (tt=p*p-q) < 0.0 && tt > -TOL2 ) tt = 0.0;
      if ( tt >= 0.0 )
        {
/*
***Yes, analytical solution.
*/
        x1 = p+SQRT(tt);
        y1 = k*(x1-linpek->crd1_l.x_gm) + linpek->crd1_l.y_gm;
        x2 = p-SQRT(tt);     
        y2 = k*(x2-linpek->crd1_l.x_gm) + linpek->crd1_l.y_gm;
        }
/*
***No intersect.
*/
      else
        {
        *noint = 0;
        return(0);
        }
/*
***Compute line parametric values.
*/
      t1[0] = 1.0 + (x1 - linpek->crd1_l.x_gm) / dx;
      t1[1] = 1.0 + (x2 - linpek->crd1_l.x_gm) / dx;
      }
/*
***Compute arc parametric values.
*/
   dx = x1 - arcpek->x_a;
   dy = y1 - arcpek->y_a;
   GE315(arcpek,dx,dy,&t2[0]);

   dx = x2 - arcpek->x_a;
   dy = y2 - arcpek->y_a;
   GE315(arcpek,dx,dy,&t2[1]);
/*
***If *noint > 0, remove intersects outside actual length of entity.
*/
   if ( *noint > 0 )
     {
     *noint = 2;
     if ( t1[0] < 1.0-TOL4 || t1[0] > 2.0+TOL4 ||
          t2[0] < 1.0-TOL4 || t2[0] > 2.0+TOL4 )
       {
       t1[0] = t1[1];
       t2[0] = t2[1];
       *noint = 1;
       }

     if ( t1[1] < 1.0-TOL4 || t1[1] > 2.0+TOL4 ||
          t2[1] < 1.0-TOL4 || t2[1] > 2.0+TOL4 )
       {
       *noint = *noint - 1;
       }
     }
   else *noint = 2;
/*
***Copy remaining solutions to u1 and u2.
*/
   for ( i=0; i<*noint; ++i )
      {
      if ( pstr1->hed_un.type == LINTYP ) 
         {
         u1[i] = t1[i];
         u2[i] = t2[i];
         }
      else
         {
         u1[i] = t2[i];
         u2[i] = t1[i];
         }
      }
/*
***If more than one solution left sort in increasing order
***with respect of the first entity.
*/
   if ( *noint > 1 && u1[0] > u1[1] )
      {
      tmp = u1[0];
      u1[0] = u1[1];
      u1[1] = tmp;

      tmp = u2[0];
      u2[0] = u2[1];
      u2[1] = tmp;
      }

   return(0);
  }