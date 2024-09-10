int Bubble::Collides(R3Mesh* mesh, R3Vector offset) {
  R3Box box = mesh -> bbox;

  R3Vector SepAxis = pos - (box.Centroid() + offset);

  double dist = SepAxis.Length();
  SepAxis.Normalize();

  double x = SepAxis.X();
  double y = SepAxis.Y();
  double z = SepAxis.Z();

  if (x >= y && x >= z && x != 0)
    SepAxis /= x;
  else if (y >= x && y >= z != 0)
    SepAxis /= y;
  else if (z != 0)
    SepAxis /= z;

  double x_len = box.XLength();
  double y_len = box.YLength();
  double z_len = box.ZLength();

  //effective radius
  SepAxis.SetX(x * x_len/2.0);
  SepAxis.SetY(y * y_len/2.0);
  SepAxis.SetZ(z * z_len/2.0);

  if (dist <= (size + SepAxis.Length()))
    return 1;	
  return 0;
}