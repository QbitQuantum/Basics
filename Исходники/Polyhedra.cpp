INSOLID_TYPE Polyhedra :: VecInSolid (const Point<3> & p,
				      const Vec<3> & v,
				      double eps) const
{
  ARRAY<int> point_on_faces;
  INSOLID_TYPE res(DOES_INTERSECT);

  Vec<3> vn = v;
  vn.Normalize();
  for (int i = 0; i < faces.Size(); i++)
    {
      const Point<3> & p1 = points[faces[i].pnums[0]];
      
      Vec<3> v0 = p - p1;
      double lam3 = -(faces[i].nn * v0); // n->nn 


      if (fabs (lam3) > eps) continue;
      //(*testout) << "lam3 <= eps" << endl;

      double lam1 = (faces[i].w1 * v0);
      double lam2 = (faces[i].w2 * v0);

      if (lam1 >= -eps_base1 && lam2 >= -eps_base1 && lam1+lam2 <= 1+eps_base1)
	{
	  point_on_faces.Append(i);

	  double scal = vn * faces[i].nn; // n->nn
	
	  res = DOES_INTERSECT;
	  if (scal > eps_base1) res = IS_OUTSIDE;
	  if (scal < -eps_base1) res = IS_INSIDE;
	}
    }
  
  //(*testout) << "point_on_faces.Size() " << point_on_faces.Size() 
  //	     << " res " << res << endl;

  if (point_on_faces.Size() == 0)
    return PointInSolid (p, 0);
  if (point_on_faces.Size() == 1)
    return res;



  
  double mindist(0);
  bool first = true;

  for(int i=0; i<point_on_faces.Size(); i++)
    {
      for(int j=0; j<3; j++)
	{
	  double dist = Dist(p,points[faces[point_on_faces[i]].pnums[j]]);
	  if(dist > eps && (first || dist < mindist))
	    {
	      mindist = dist;
	      first = false;
	    }
	}
    }
  
  Point<3> p2 = p + (1e-2*mindist) * vn;
  res = PointInSolid (p2, eps);

  //  (*testout) << "mindist " << mindist << " res " << res << endl;

  return res;
  
 
}