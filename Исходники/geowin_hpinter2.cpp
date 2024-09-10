  return gb;
 }

}

void hp_inter(const list<LINE>& Lin, list<rat_polygon>& Lout)
{
 if (Lin.size() < 1) return;
 int HP_NUMB=Lin.size(),i;
 array<LINE> L(HP_NUMB);
 LINE lakt;
 i=0;
 forall(lakt,Lin) { L[i]=lakt; i++; }

 POLYGON GP = halfplane_intersection(L,0,HP_NUMB-1);
 
 Lout = GP.polygons();
}

POINT get_dual(const LINE& l)
{
 POINT p1 = l.point1();
 POINT p2 = l.point2();
 POINT swp;
 
 if (p1.xcoord() > p2.xcoord()) { swp=p1; p1=p2; p2=swp; }

 NUMBER2 a,b,x1,x2,y1,y2;
 x1=p1.xcoord(); y1=p1.ycoord();
 x2=p2.xcoord(); y2=p2.ycoord();