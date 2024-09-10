Real Quad4::volume () const
{
  // The A,B,C,D naming scheme here corresponds exactly to the
  // libmesh counter-clockwise numbering scheme.

  //        3           2        D           C
  // QUAD4: o-----------o	 o-----------o
  //        |           |	 |           |
  //        |           |	 |           |
  //        |           | 	 |           |
  //        |           |	 |           |
  //        |           |	 |           |
  //        o-----------o	 o-----------o
  //        0           1	 A           B

  // Vector pointing from A to C
  Point AC ( this->point(2) - this->point(0) );

  // Vector pointing from A to B
  Point AB ( this->point(1) - this->point(0) );

  // Vector pointing from A to D
  Point AD ( this->point(3) - this->point(0) );

  // The diagonal vector minus the side vectors
  Point AC_AB_AD (AC - AB - AD);

  // Check for quick return for planar QUAD4.  This will
  // be the most common case, occuring for all purely 2D meshes.
  if (AC_AB_AD == Point(0.,0.,0.))
    return AB.cross(AD).size();

  else
    {
      // Use 2x2 quadrature to approximate the surface area.  (The
      // true integral is too difficult to compute analytically.)  The
      // accuracy here is exactly the same as would be obtained via a
      // call to Elem::volume(), however it is a bit more optimized to
      // do it this way.  The technique used is to integrate the magnitude
      // of the normal vector over the whole area.  See for example,
      //
      // Y. Zhang, C. Bajaj, G. Xu. Surface Smoothing and Quality
      // Improvement of Quadrilateral/Hexahedral Meshes with Geometric
      // Flow. The special issue of the Journal Communications in
      // Numerical Methods in Engineering (CNME), submitted as an
      // invited paper, 2006.
      // http://www.ices.utexas.edu/~jessica/paper/quadhexgf/quadhex_geomflow_CNM.pdf

      // 4-point rule
      const Real q[2] = {0.5 - std::sqrt(3.) / 6.,
			 0.5 + std::sqrt(3.) / 6.};

      Real vol=0.;
      for (unsigned int i=0; i<2; ++i)
	for (unsigned int j=0; j<2; ++j)
	  vol += (AB + q[i]*AC_AB_AD).cross(AD + q[j]*AC_AB_AD).size();

      return 0.25*vol;
    }
}