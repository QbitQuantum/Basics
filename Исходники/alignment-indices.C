std::pair<vector<int>,vector<int> > find_major_character(const alignment& A,int allowed_differences)
{
  const alphabet& a = A.get_alphabet();

  vector<int> majority(A.length(), alphabet::unknown);

  vector<int> safe(A.length(), 0);

  for(int c=0;c<majority.size();c++) 
  {
    vector<int> count = column_count(A,c);
    
    int max_letter = argmax(count);
    majority[c] = max_letter;
    
    // NOTE! Major character is gap if there is more than 1 gap!
    if (count[a.size()] > 1)
      majority[c] = alphabet::gap;
    else if (A.n_sequences() - count[max_letter] <= allowed_differences)
      safe[c] = 1;
    
    /*
      if (safe[c] == 1) {
      std::cerr<<"Column "<<c+1<<" is safe: "<<a.lookup(max_letter)<<"\n";
      }
    */
  }
  
  return std::pair<vector<int>,vector<int> >(majority,safe);
}