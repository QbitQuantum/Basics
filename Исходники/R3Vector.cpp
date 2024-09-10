R3Vector 
operator%(const R3Vector& vector1, const R3Vector& vector2)
{
  // Return cross product of two vectors
  R3Vector v = vector1;
  v.Cross(vector2);
  return v;
}