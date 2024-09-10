string toUpper(const string& str) {
  string up(str);
  for (size_t i=0; i<up.size(); ++i) up[i] = toupper(str[i]);
  return up;
}