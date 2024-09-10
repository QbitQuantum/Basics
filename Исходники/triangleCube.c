long point_triangle_intersection(Point3 p, Triangle3 t)
{
long sign12,sign23,sign31;
Point3 vect12,vect23,vect31,vect1h,vect2h,vect3h;
Point3 cross12_1p,cross23_2p,cross31_3p;

/* First, a quick bounding-box test:                               */
/* If P is outside triangle bbox, there cannot be an intersection. */

   if (p.x > MAX3(t.v1.x, t.v2.x, t.v3.x)) return(OUTSIDE);  
   if (p.y > MAX3(t.v1.y, t.v2.y, t.v3.y)) return(OUTSIDE);
   if (p.z > MAX3(t.v1.z, t.v2.z, t.v3.z)) return(OUTSIDE);
   if (p.x < MIN3(t.v1.x, t.v2.x, t.v3.x)) return(OUTSIDE);
   if (p.y < MIN3(t.v1.y, t.v2.y, t.v3.y)) return(OUTSIDE);
   if (p.z < MIN3(t.v1.z, t.v2.z, t.v3.z)) return(OUTSIDE);

/* For each triangle side, make a vector out of it by subtracting vertexes; */
/* make another vector from one vertex to point P.                          */
/* The crossproduct of these two vectors is orthogonal to both and the      */
/* signs of its X,Y,Z components indicate whether P was to the inside or    */
/* to the outside of this triangle side.                                    */

   SUB(t.v1, t.v2, vect12)
   SUB(t.v1,    p, vect1h);
   CROSS(vect12, vect1h, cross12_1p)
   sign12 = SIGN3(cross12_1p);      /* Extract X,Y,Z signs as 0..7 or 0...63 integer */

   SUB(t.v2, t.v3, vect23)
   SUB(t.v2,    p, vect2h);
   CROSS(vect23, vect2h, cross23_2p)
   sign23 = SIGN3(cross23_2p);

   SUB(t.v3, t.v1, vect31)
   SUB(t.v3,    p, vect3h);
   CROSS(vect31, vect3h, cross31_3p)
   sign31 = SIGN3(cross31_3p);

/* If all three crossproduct vectors agree in their component signs,  */
/* then the point must be inside all three.                           */
/* P cannot be OUTSIDE all three sides simultaneously.                */

   /* this is the old test; with the revised SIGN3() macro, the test
    * needs to be revised. */
#ifdef OLD_TEST
   if ((sign12 == sign23) && (sign23 == sign31))
      return(INSIDE);
   else
      return(OUTSIDE);
#else
   return ((sign12 & sign23 & sign31) == 0) ? OUTSIDE : INSIDE;
#endif
}