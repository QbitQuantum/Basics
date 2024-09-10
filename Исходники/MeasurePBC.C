void get_transform_to_orthonormal_cell(const float *cell, const float *center, Matrix4 &transform) {
  // Orthogonalize system:
  // Find an orthonormal basis of the cell (in cartesian coords).
  // If the cell vectors from VMD/NAMD are used this should actually always
  // return the identity matrix due to the way the cell vectors A, B and C
  // are defined (i.e. A || x; B lies in the x,y-plane; A, B, C form a right
  // hand system).
  float obase[3*3];
  orthonormal_basis(cell, obase);

  // Get orthonormal base in cartesian coordinates (it is the inverse of the
  // obase->cartesian transformation):
  float identity[3*3] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  float obase_cartcoor[3*3];
  basis_change(obase, identity, obase_cartcoor, 3);


  // Transform 3x3 into 4x4 matrix:
  Matrix4 obase2cartinv;
  trans_from_rotate(obase_cartcoor, &obase2cartinv);

  // This is the matrix for the obase->cartesian transformation:
  Matrix4 obase2cart = obase2cartinv;
  obase2cart.inverse();

  // Get coordinates of cell in terms of obase
  float m[3*3]; 
  basis_change(cell, obase, m, 3);
  Matrix4 rotmat;
  trans_from_rotate(m, &rotmat);
  rotmat.inverse();

  
  // Actually we have:
  // transform = translation * obase2cart * obase2cartinv * rotmat * obase2cart
  //                           `------------v------------'
  //                                       = 1
  transform = obase2cart;
  transform.multmatrix(rotmat); // pre-multiplication

  // Finally we need to apply the translation of the origin
  float origin[3];
  vec_copy(origin, center);
  vec_scaled_add(origin, -0.5, &cell[0]);
  vec_scaled_add(origin, -0.5, &cell[3]);
  vec_scaled_add(origin, -0.5, &cell[6]);
  vec_negate(origin, origin);
  //printf("origin={%g %g %g}\n", origin[0], origin[1], origin[2]);
  transform.translate(origin);
}