bool ixion::regex<T>::quantifier::match(backref_stack &brstack,T const &candidate,TIndex at) {
  // this routine does speculative matching, so it must pay close attention
  // to rewind the backref stack appropriately.
  // NB: matchNext does the rewinding automatically, whereas speculative
  // matches of the quantified portion must be rewound.
  
  // There should be at least one character in each match, we'd
  // run to Baghdad otherwise.
  
  if (!Quantified) 
    return matchNext(brstack,candidate,at);
  
  // calculate accurate maximum match count
  TSize quant_min = Quantified->minimumSubsequentMatchLength();
  if (quant_min == 0) quant_min = 1;
  
  TSize max_count = candidate.size() - at;
  if (this->Next) max_count -= this->Next->minimumSubsequentMatchLength();
  max_count = max_count/quant_min + 1;
  
  if (MaxValid) max_count = NUM_MIN(max_count,MaxCount);
  
  // check that at least MinCount matches take place (non-speculative)
  TIndex idx = at;
  for (TSize c = 1;c <= MinCount;c++)
    if (Quantified->match(brstack,candidate,idx))
      idx += Quantified->subsequentMatchLength();
    else 
      return false;
  
  // determine number of remaining matches
  TSize remcount = max_count-MinCount;
  
  // test for the remaining matches in a way that depends on Greedy flag
  if (Greedy) {
    // try to gobble up as many matches of quantified part as possible
    // (speculative)
    
    std::stack<backtrack_stack_entry> successful_indices;
    { backtrack_stack_entry entry = { idx,brstack.getRewindInfo() };
      successful_indices.push(entry);
      }
    
    while (Quantified->match(brstack,candidate,idx) && successful_indices.size()-1 < remcount) {
      idx += Quantified->subsequentMatchLength();
      backtrack_stack_entry entry = { idx,brstack.getRewindInfo() };
      successful_indices.push(entry);
      }
    
    // backtrack until rest of sequence also matches
    while (successful_indices.size() && !matchNext(brstack,candidate,successful_indices.top().Index)) {
      brstack.rewind(successful_indices.top().RewindInfo);
      successful_indices.pop();
      }
    
    if (successful_indices.size()) {
      this->MatchLength = successful_indices.top().Index - at;
      return true;
      }
    else return false;
    }
  else {
    for (TSize c = 0;c <= remcount;c++) {
      if (matchNext(brstack,candidate,idx)) {
        this->MatchLength = idx-at;
        return true;
        }
      // following part runs once too much, effectively: 
      // if c == remcount, idx may be increased, but the search fails anyway
      // => no problem
      if (Quantified->match(brstack,candidate,idx))
        idx += Quantified->subsequentMatchLength();
      else 
        return false;
      }
    return false;
    }
  }