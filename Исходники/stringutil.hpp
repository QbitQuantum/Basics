inline string& Lower(string& str) {
  transform(str.begin(), str.end(), str.begin(), (int (*)(int))tolower);
  return str;
}