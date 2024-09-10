 // Angle (in radians) between two adjacent face normals
 // (or 0, if < 2 faces):
 // XXX - name problem: it is not actually the dihedral angle!
 double dihedral_angle() const { return Acos(dot()); }