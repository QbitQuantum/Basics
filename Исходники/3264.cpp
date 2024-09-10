 /* 两圆位置关系:
  * 0: 相离
  * 1: 外切
  * 2: 相交
  * 3: 内切
  * 4: 内含
  */
 int pos_circle(const Circle& b)const
 {
     double d = center.distance(b.center);
     if (d > radius + b.radius + EPS)
     {
         return 0;
     }
     else if (fabs(d - radius - b.radius) < EPS)
     {
         return 1;
     }
     else if (d > fabs(radius - b.radius) + EPS)
     {
         return 2;
     }
     else if (fabs(d - fabs(radius - b.radius)) < EPS)
     {
         return 3;
     }
     else
     {
         return 4;
     }
 }