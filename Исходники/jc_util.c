bool allInBrackets( const TString& in, char opening_bracket = '(', char closing_bracket = ')' ) 
{
  int n_in = 0;
  for( int ii = 0; ii<in.Length(); ++ii) {
    char c = in[ii]; 
    if( c == opening_bracket ) {
      ++n_in; 
    } else if( c == closing_bracket ) {
      --n_in;
    } else if( c != ' ' && n_in <= 0 ) {
      return false;
    }
  }
  return true;
}