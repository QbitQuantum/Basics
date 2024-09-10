 void concatenate(string &s, unordered_set<string> &dict,
                  vector<vector<int> > &match, int cur_index, string cur_s) {
   for (int i = 0; i < match[cur_index].size(); i++) {
     int start = match[cur_index][i];
     if (start == 0) {
       r.push_back(s.substr(0, cur_index + 1) + cur_s);
     } else {
       concatenate(s, dict, match, start - 1,
                   " " + s.substr(start, cur_index - start + 1) + cur_s);
     }
   }
 }