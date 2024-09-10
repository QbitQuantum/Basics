/*.BE*/
int spltrans                                      /* transformiert-parametr. kub. Polynomspline .......*/
/*.BA*/
/*.IX{spltrans}*/
/*.BE*/
(
int  m,                                           /* Anzahl der Stuetzpunkte ..............*/
REAL x[],                                         /* Stuetzstellen ........................*/
REAL y[],                                         /* Stuetzwerte ..........................*/
int  mv,                                          /* Art der Koordinatenverschiebung ......*/
REAL px[],                                        /* Koordinaten des ......................*/
REAL py[],                                        /* Verschiebepunktes P ..................*/
REAL a[],                                         /* Splinekoeff. von (phi-phin[i])^0 .....*/
REAL b[],                                         /* Splinekoeff. von (phi-phin[i]) .......*/
REAL c[],                                         /* Splinekoeff. von (phi-phin[i])^2 .....*/
REAL d[],                                         /* Splinekoeff. von (phi-phin[i])^3 .....*/
REAL phin[],                                      /* Winkelkoordinaten der Stuetzpunkte ...*/
REAL *phid                                        /* Drehwinkel des Koordinatensystems ....*/
)                                                 /* Fehlercode ...........................*/
/*.BA*/

/***********************************************************************
 * die Koeffizienten einer transformiert-parametrischen interpolieren-  *
 * den kubischen Splinefunktion fuer eine geschlossene, ueberall glatte *
 * Kurve berechnen.                                                     *
.BE*)
* Eine transformiert-parametrische kubische Splinefunktion ist eine    *
* periodische kubische Splinefunktion wie in der Funktion spline(),    *
* jedoch in Polarkoordinatendarstellung. Dies ermoeglicht in vielen    *
* Faellen die Interpolation von Daten, deren Stuetzstellen nicht mono- *
* ton steigend angeordnet sind, ohne echte parametrische Splines (wie  *
* in der Funktion parspl()) berechnen zu muessen.                      *
* Hierzu transformiert die Funktion die eingegebenen Punkte zunaechst  *
* auf Polarkoordinaten (phin[i],a[i]), wobei phin[i] der Winkel und    *
* a[i] die Laenge des Ortsvektors von (x[i],y[i]) ist, i=0(1)m-1. Dies *
* muss so moeglich sein, dass die Winkelwerte phin[i] streng monoton   *
 * steigen, andernfalls ist das transformiert-parametrische Verfahren   *
 * nicht anwendbar. Dann wird eine periodische kubische Splinefunktion  *
 * mit den Winkeln phin[i] als Stuetzstellen berechnet, die die Vektor- *
 * laengen a[i] interpoliert. Um die Monotonie der phin[i] zu errei-    *
 * chen, kann es notwendig sein, den Koordinatenursprung auf einen      *
 * Punkt  P = (px, py)  zu verschieben und das Koordinatensystem um ei- *
 * nen Winkel phid zu drehen. (px, py) muss so in der durch die         *
 * (x[i], y[i])  beschriebenen Flaeche liegen, dass jeder von P ausge-  *
 * hende Polarstrahl die Randkurve der Flaeche nur einmal schneidet.    *
 * P kann sowohl vom Benutzer vorgegeben als auch von der Funktion be-  *
 * rechnet werden. Der hier berechnete Wert ist allerdings nur als Vor- *
 * schlagswert aufzufassen, der in unguenstigen Faellen nicht immer die *
 * Bedingungen erfuellt. Ausserdem muessen die (x[i],y[i]) in der Rei-  *
 * henfolge angeordnet sein, die sich ergibt, wenn man die Randkurve    *
 * der Flaeche, beginnend bei i = 1, im mathematisch positiven Sinn     *
 * durchlaeuft. Da die Kurve geschlossen ist, muss  x[m-1] = x[0]  und  *
 * y[m-1] = y[0]  sein.                                                 *
 *                                                                      *
 * Eingabeparameter:                                                    *
 * =================                                                    *
 * m:    Anzahl der Stuetzstellen (mindestens 3)                        *
 * x:    [0..m-1]-Vektor mit den Stuetzstellen                          *
 * y:    [0..m-1]-Vektor mit den zu interpolierenden Stuetzwerten       *
 * mv:   Marke fuer die Verschiebung des Koordinatenursprungs.          *
 *       mv > 0: Der Benutzer gibt die Koordinaten px, py vor.          *
 *       mv = 0: keine Verschiebung (d.h. px = py = 0)                  *
 *       mv < 0: px und py werden hier berechnet.                       *
 *               Es wird gesetzt:                                       *
 *               px = (xmax + xmin) / 2                                 *
 *               py = (ymax + ymin) / 2                                 *
 *               mit xmax = max(x[i]), xmin = min(x[i]),                *
 *                   ymax = max(y[i]), ymin = min(y[i]), i=0(1)m-1.     *
 *               Zur Beachtung: Hierdurch ist nicht notwendigerweise    *
 *               sichergestellt, dass P die oben genannten Bedingungen  *
 *               erfuellt. Falls die Funktion mit dem Fehlercode -3     *
 *               endet, muss P vom Benutzer vorgegeben werden.          *
 *                                                                      *
 * px: \ fuer mv > 0: vorgegebene Koordinaten des Punktes P             *
 * py: /                                                                *
 *                                                                      *
 * Ausgabeparameter:                                                    *
 * =================                                                    *
 * a: \  [0..m-1]-Vektoren mit Splinekoeffizienten in der Darstellung   *
 * b:  \     S(phi)  =  a[i] + b[i] * (phi - phin[i])                   *
 * c:  /                     + c[i] * (phi - phin[i]) ^ 2               *
 * d: /                      + d[i] * (phi - phin[i]) ^ 3               *
 *       fuer  phin[i] <= phi <= phin[i+1],   i=0(1)m-2 .               *
 *       Die a[i] sind die Vektorlaengen der (x[i],y[i]) in der Polar-  *
 *       koordinatendarstellung. b, c und d werden auch noch fuer       *
 *       Zwischenergebnisse missbraucht.                                *
 * phin: [0..m-1]-Vektor mit den Winkelkoordinaten der (x[i],y[i]) in   *
 *       der Polarkoordinatendarstellung.                               *
 *       Es ist phin[0]   = 0,                                          *
 *              phin[i]   = arctan((y[i] - py) / (x[i] - px)) - phid,   *
 *                          i=1(1)m-2                                   *
 *              phin[m-1] = 2 * Pi                                      *
 *                                                                      *
 * px: \ Koordinaten des Verschiebungspunktes P                         *
 * py: /                                                                *
 * phid: Winkel, um den das Koordinatensystem eventuell gedreht wurde.  *
 *       Es ist phid = arctan(y[0] / x[0]).                             *
 *                                                                      *
 * Funktionswert:                                                       *
 * ==============                                                       *
 *  0: kein Fehler                                                      *
 * -1: m < 3                                                            *
 * -3: Die phin[i] sind nicht streng monoton steigend.                  *
 * -4: x[m-1] != x[0]  oder  y[m-1] != y[0]                             *
 * >0: Fehler in spline()                                               *
 *                                                                      *
 * benutzte globale Namen:                                              *
 * =======================                                              *
 * spline, REAL, PI, sqr, SQRT, ACOS, ZERO, TWO                         *
.BA*)
***********************************************************************/
/*.BE*/

{
   REAL xmin,                                     /* Minimum der x[i]                      */
      xmax,                                       /* Maximum der x[i]                      */
      ymin,                                       /* Minimum der y[i]                      */
      ymax,                                       /* Maximum der y[i]                      */
      sa,                                         /* sin(-phid)                            */
      ca;                                         /* cos(-phid)                            */
   int  n,                                        /* m - 1, Index der letzten Stuetzstelle */
      i;                                          /* Laufvariable                          */

   n = m - 1;

   /* ---------------- die Vorbedingungen ueberpruefen --------------- */
   if (n < 2)
      return -1;
   if (x[0] != x[n] || y[0] != y[n])
      return -4;

   /* ---------------- die Koordinaten transformieren ---------------- */
   if (mv == 0)                                   /* das Koordinatensystem  nicht verschieben? */
   {
      *px = *py = ZERO;
      for (i = 0; i <= n; i++)
         b[i] = x[i],
            c[i] = y[i];
   }
   else                                           /* den Koordinatenursprung nach (px, py) verschieben? */
   {
      if (mv < 0)                                 /* Sollen py und py berechnet werden? */
      {
         xmax = x[0];
         xmin = x[0];
         ymax = y[0];
         ymin = y[0];
         for (i = 1; i <= n; i++)
         {
            if (x[i] > xmax)
               xmax = x[i];
            if (x[i] < xmin)
               xmin = x[i];
            if (y[i] > ymax)
               ymax = y[i];
            if (y[i] < ymin)
               ymin = y[i];
         }
         *px = (xmax + xmin) / TWO;
         *py = (ymax + ymin) / TWO;
      }

      for (i = 0; i <= n; i++)                    /* die verschoben Punkte (x[i],y[i]) */
         b[i] = x[i] - *px,                       /* in (b[i],c[i]) aufgewahren        */
            c[i] = y[i] - *py;
   }

   /* ---- die transformierten Stuetzstellen berechnen:           ---- */
   /* ---- 1. die a[i] berechnen. Abbruch, wenn  a[i] = 0, d. h.  ---- */
   /* ----    wenn (px, py) mit einer Stuetzstelle zusammenfaellt ---- */
   for (i = 0; i <= n; i++)
   {
      a[i] = SQRT(sqr(b[i]) + sqr(c[i]));
      if (a[i] == ZERO)
         return -3;
   }

   /*------------------------------------------------------------------*/
   /* 2. die um alpha gedrehten Koordinaten X1, Y1 berechnen           */
   /*    nach den Gleichungen:                                         */
   /*                                                                  */
   /*  (X1)   ( cos(alpha)   -sin(alpha) ) (X)                         */
   /*  (  ) = (                          ) ( )                         */
   /*  (Y1)   ( sin(alpha)    cos(alpha) ) (Y)                         */
   /*                                                                  */
   /*  mit alpha = -phid                                               */
   /*------------------------------------------------------------------*/

   *phid = ACOS(b[0] / a[0]);
   if (c[0] < ZERO)
      *phid = TWO * PI - *phid;
   ca = b[0] / a[0];
   sa = -c[0] / a[0];
   for (i = 0; i <= n; i++)                       /* die gedrehten Koordinaten */
      d[i] = b[i] * ca - c[i] * sa,               /* (b[i],c[i]) in            */
         c[i] = b[i] * sa + c[i] * ca;            /* (d[i],c[i] ablegen        */

   /* ------ die Winkelkoordinaten phin[i] berechnen. Abbruch,  ------ */
   /* ------ wenn die Winkel nicht streng monoton steigend sind ------ */
   phin[0] = ZERO;
   for (i = 1; i < n; i++)
   {
      phin[i] = ACOS(d[i] / a[i]);
      if (c[i] < ZERO)
         phin[i] = TWO * PI - phin[i];
      if (phin[i] <= phin[i - 1])
         return -3;
   }
   phin[n] = TWO * PI;

   /* --------------- die Splinekoeffizienten berechnen -------------- */
   return spline(n + 1, phin, a, 4, ZERO, ZERO, 0, b, c, d);
}