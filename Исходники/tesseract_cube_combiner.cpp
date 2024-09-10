// Compares 2 strings optionally ignoring punctuation
int TesseractCubeCombiner::CompareStrings(const string &str1,
                                          const string &str2,
                                          bool ignore_punc,
                                          bool ignore_case) {
  if (!ignore_punc && !ignore_case) {
    return str1.compare(str2);
  }
  string norm_str1 = NormalizeString(str1, ignore_punc, ignore_case);
  string norm_str2 = NormalizeString(str2, ignore_punc, ignore_case);
  return norm_str1.compare(norm_str2);
}