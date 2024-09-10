 vector<string> evaluate(vector<string> &tokens) {
     stack<map<string, int>> s;
     for (auto &token : tokens) {
         switch(token.back()) {
             case '+':
             case '-': {
                 int sign = token[0] == '+' ? 1 : -1;
                 auto b = s.top(); s.pop();
                 auto a = s.top(); s.pop();
                 map<string, int> m;
                 for (auto &p : a) {
                     m[p.first] += p.second;
                 }
                 for (auto &p : b) {
                     m[p.first] += sign * p.second;
                 }
                 s.push(m);
                 break;
             }
             case '*': {
                 auto b = s.top(); s.pop();
                 auto a = s.top(); s.pop();
                 map<string, int> m;
                 for (auto &p : a) {
                     auto symbol1 = splitSymbols(p.first);
                     for (auto &q : b) {
                         istringstream sb(q.first);
                         auto symbol2 = splitSymbols(q.first);
                         string symbol;
                         if (symbol1.size() == 1 && symbol1[0] == "1") {
                             symbol = q.first;
                         } else if (symbol2.size() == 1 && symbol2[0] == "1") {
                             symbol = p.first;
                         } else {
                             for (int i = 0, j = 0; i < symbol1.size() || j < symbol2.size();) {
                                 if (symbol.size()) symbol += "*";
                                 if (i >= symbol1.size()) {
                                     symbol += symbol2[j++];
                                 } else if (j >= symbol2.size()) {
                                     symbol += symbol1[i++];
                                 } else if (symbol1[i] < symbol2[j]){
                                     symbol += symbol1[i++];
                                 } else {
                                     symbol += symbol2[j++];
                                 }
                             }
                         }
                         m[symbol] += p.second * q.second;
                     }
                 }
                 s.push(m);
                 break;
             }
             default: {
                 map<string, int> m;
                 if (isdigit(token.back())) {
                     m["1"] = stoi(token);
                 } else {
                     m[token] = 1;
                 }
                 s.push(m);
                 break;
             }
         }
     }
     vector<string> ans;
     for (auto &p : s.top()) {
         if (!p.second) continue;
         ans.push_back(to_string(p.second) + (p.first == "1" ? "" : "*" + p.first));
     }
     stable_sort(ans.begin(), ans.end(), [&](string a, string b) {
         return count(a.begin(), a.end(), '*') > count(b.begin(), b.end(), '*');
     });
     return ans;
 }