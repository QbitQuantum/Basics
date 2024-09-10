unsigned n_with_identity(const alignment& A,int s1,int s2,double I)
{
  // Get matches
  vector<int> F(A.length()+1);

  unsigned L=0;
  unsigned T = 0;
  F[0]=0;
  for(int i=0;i<A.length();i++) 
  {
    if (not A.character(i,s1) and not A.character(i,s2)) continue;

    L++;
    
    if (A(i,s1) == A(i,s2))
      T++;

    F[L] = T;
  }
  F.resize(L+1);

  // Get positions
  vector<int> FI(T+1);
  FI[0]=0;
  for(int i=0;i<L;i++)
    if (F[i+1] > F[i])
      FI[F[i+1]] = i+1;

  // tag positions that 
  vector<int> tagged(L,0);

  const unsigned w = 4;
  for(int i=1;i<=T;i++) {
    for(int j=20;j>=w;j--) {
      int i2 = i+j;
      if (i2 > T) continue;
      assert(FI[i]  > 0 and FI[i]  <=L);
      assert(FI[i2] > 0 and FI[i2] <=L);
      assert(FI[i2] > FI[i]);

      if (double(i2-i+1)/(FI[i2]-FI[i]+1) > I) {
	for(int k=FI[i];k<=FI[i2];k++)
	  tagged[k-1]=1;
	break;
      }
    }
  }

  return sum(tagged);
}