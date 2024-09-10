void Brick :: CalcData()
{
  v12 = p2 - p1;
  v13 = p3 - p1;
  v14 = p4 - p1;

  Point<3> pi[8];
  int i1, i2, i3;
  int i, j;
  
  i = 0;
  for (i3 = 0; i3 <= 1; i3++)
    for (i2 = 0; i2 <= 1; i2++)
      for (i1 = 0; i1 <= 1; i1++)
	{
	  pi[i] = p1 + (double)i1 * v12 + (double)i2 * v13 + (double)i3 * v14;
	  i++;
	}

  static int lface[6][4] =
  { { 1, 3, 2, 4 },
    { 5, 6, 7, 8 },
    { 1, 2, 5, 6 },
    { 3, 7, 4, 8 },
    { 1, 5, 3, 7 },
    { 2, 4, 6, 8 } };
  
  Array<double> data(6);
  for (i = 0; i < 6; i++)
    {
      const Point<3> lp1 = pi[lface[i][0]-1];
      const Point<3> lp2 = pi[lface[i][1]-1];
      const Point<3> lp3 = pi[lface[i][2]-1];

      Vec<3> n = Cross ((lp2-lp1), (lp3-lp1));
      n.Normalize();
      
      for (j = 0; j < 3; j++)
	{
	  data[j] = lp1(j);
	  data[j+3] = n(j);
	}
      faces[i] -> SetPrimitiveData (data);
    }
}