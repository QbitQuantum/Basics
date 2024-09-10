/// Compute the number of times each letter of the alphabet occurs in \a A.
valarray<double> letter_counts(const alignment& A) 
{
  const alphabet& a = A.get_alphabet();

  // Count the occurrence of the different letters
  valarray<double> counts(0.0, a.size());
  for(int i=0;i<A.length();i++) {
    for(int j=0;j<A.n_sequences();j++) {
      if (a.is_letter(A(i,j)))
	counts[A(i,j)]++;
    }
  }

  return counts;
}