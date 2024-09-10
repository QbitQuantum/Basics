FCL_REAL kIOS::distance(const kIOS& other, Vec3f* P, Vec3f* Q) const
{
  FCL_REAL d_max = 0;
  int id_a = -1, id_b = -1;
  for(unsigned int i = 0; i < num_spheres; ++i)
  {
    for(unsigned int j = 0; j < other.num_spheres; ++j)
    {
      FCL_REAL d = (spheres[i].o - other.spheres[j].o).length() - (spheres[i].r + other.spheres[j].r);
      if(d_max < d)
      {
        d_max = d;
        if(P && Q)
        {
          id_a = i; id_b = j;
        }
      }
    }
  }

  if(P && Q)
  {
    if(id_a != -1 && id_b != -1)
    {
      Vec3f v = spheres[id_a].o - spheres[id_b].o;
      FCL_REAL len_v = v.length();
      *P = spheres[id_a].o - v * (spheres[id_a].r / len_v);
      *Q = spheres[id_b].o + v * (spheres[id_b].r / len_v);
    }
  }

  return d_max;
}