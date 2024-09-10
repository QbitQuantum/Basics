void replaceAll(string& source, const string& from, const string& to) {
  string newString;
  newString.reserve(source.length());
  string::size_type lastPos = 0;
  string::size_type findPos;
  while(string::npos != (findPos = source.find(from, lastPos))) {
    newString.append( source, lastPos, findPos - lastPos );
    newString += to;
    lastPos = findPos + from.length();
  }
  newString += source.substr( lastPos );
  source.swap( newString );
}