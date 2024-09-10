Real Hex8::volume () const
{
  // Compute the volume of the tri-linear hex by splitting it
  // into 6 sub-pyramids and applying the formula in:
  // "Calculation of the Volume of a General Hexahedron
  // for Flow Predictions", AIAA Journal v.23, no.6, 1984, p.954-

  static const unsigned char sub_pyr[6][4] =
    {
      {0, 3, 2, 1},
      {6, 7, 4, 5},
      {0, 1, 5, 4},
      {3, 7, 6, 2},
      {0, 4, 7, 3},
      {1, 2, 6, 5}
    };

  // The centroid is a convenient point to use
  // for the apex of all the pyramids.
  const Point R = this->centroid();
  Node* pyr_base[4];

  Real vol=0.;

  // Compute the volume using 6 sub-pyramids
  for (unsigned int n=0; n<6; ++n)
    {
      // Set the nodes of the pyramid base
      for (unsigned int i=0; i<4; ++i)
	pyr_base[i] = this->_nodes[sub_pyr[n][i]];

      // Compute diff vectors
      Point a ( *pyr_base[0] - R );
      Point b ( *pyr_base[1] - *pyr_base[3] );
      Point c ( *pyr_base[2] - *pyr_base[0] );
      Point d ( *pyr_base[3] - *pyr_base[0] );
      Point e ( *pyr_base[1] - *pyr_base[0] );

      // Compute pyramid volume
      Real sub_vol = (1./6.)*(a*(b.cross(c))) + (1./12.)*(c*(d.cross(e)));

      libmesh_assert (sub_vol>0.);

      vol += sub_vol;
    }

  return vol;
}