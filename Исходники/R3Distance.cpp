double R3Distance(const R3Line& line1, const R3Line& line2)
{
  // Return distance from line to line (Riddle p. 905)
  R3Vector v = line1.Vector();
  v.Cross(line2.Vector());
  return v.Dot(line1.Point() - line2.Point());
}