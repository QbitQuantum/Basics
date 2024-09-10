ublas::matrix<int> get_path_counts(const alignment& A,int node1, int node2) 
{
  using namespace A2;

  int state1 = states::S;

  ublas::matrix<int> counts(5,5);
  counts.clear();

  for(int column=0;column<A.length();column++) 
  {
    int state2 = -1;
    if (A.gap(column,node1)) {
      if (A.gap(column,node2)) 
       continue;
      else
       state2 = states::G1;
    }
    else {
      if (A.gap(column,node2))
       state2 = states::G2;
      else
       state2 = states::M;
    }

    counts(state1,state2)++;
    state1 = state2;
  }

  counts(state1,states::E)++;

  return counts;
}