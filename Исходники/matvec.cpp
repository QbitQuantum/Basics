// Compute inverse matrices of the given matrix vector.
matvec inverse (matvec a) {
  matvec res (a.getSize (), a.getRows (), a.getCols ());
  for (int i = 0; i < a.getSize (); i++) res.set (inverse (a.get (i)), i);
  return res;
}