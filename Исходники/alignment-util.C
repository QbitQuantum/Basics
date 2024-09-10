/// Replace each letter with its position in its sequence
ublas::matrix<int> M(const alignment& A1) 
{
  ublas::matrix<int> A2(A1.length(),A1.n_sequences());
  for(int i=0;i<A2.size2();i++) {
    int pos=0;
    for(int column=0;column<A2.size1();column++) {
      if (A1.character(column,i)) {
	A2(column,i) = pos;
	pos++;
      }
      else
	A2(column,i) = A1(column,i);
    }

    assert(pos == A1.seqlength(i));
  }
  return A2;
}