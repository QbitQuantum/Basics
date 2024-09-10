static double noise3(int * p, double x, double y, double z)
{
  int X = (int)FASTFLOOR(x) & 255,                   /* FIND UNIT CUBE THAT */
      Y = (int)FASTFLOOR(y) & 255,                   /* CONTAINS POINT.     */
      Z = (int)FASTFLOOR(z) & 255;

  double u, v, w;

  int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z,      /* HASH COORDINATES OF */
      B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;      /* THE 8 CUBE CORNERS, */

  x -= FASTFLOOR(x);                                  /* FIND RELATIVE X,Y,Z */
  y -= FASTFLOOR(y);                                  /* OF POINT IN CUBE.   */
  z -= FASTFLOOR(z);

  u = FADE(x);                                       /* COMPUTE FADE CURVES */
  v = FADE(y);                                       /* FOR EACH OF X,Y,Z.  */
  w = FADE(z);

  return LERP(w, LERP(v, LERP(u, GRAD(p[AA  ], x    , y    , z     ),  /* AND ADD */
                                 GRAD(p[BA  ], x-1.0, y    , z     )), /* BLENDED */
                         LERP(u, GRAD(p[AB  ], x    , y-1.0, z     ),  /* RESULTS */
                                 GRAD(p[BB  ], x-1.0, y-1.0, z     ))),/* FROM  8 */
                 LERP(v, LERP(u, GRAD(p[AA+1], x    , y    , z-1.0 ),  /* CORNERS */
                                 GRAD(p[BA+1], x-1.0, y    , z-1.0 )), /* OF CUBE */
                         LERP(u, GRAD(p[AB+1], x    , y-1.0, z-1.0 ),
                                 GRAD(p[BB+1], x-1.0, y-1.0, z-1.0 ))));
}