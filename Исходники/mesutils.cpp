void splitwordsR(string s, string sep, int m, vector<string>& resultat) {
    int j = 0, j0;
    while (s.find(sep) == 0) s = s.substr(1);
    int k = 0;
    string s0, s1;
    if (s.length() == 0) {
        resultat.resize(0);
        return;
    }
    s.append(sep);
    s1 = string();
    for (int i = 0; i < (int)s.length(); i++) {
        s0 = s.substr(i, 1);
        if (s0 == sep) {
            j++;
            if (j == 1) {
                s1.append(s0);
                if (j == 1) k++;
                //cout <<" j=1  k="<<*k<<"\n";
            }
        } else {
            s1.append(s0);
            j = 0;
        }
        if (k == m) break;
    }
    vector<string> sb(k);
    for (int i = 0; i < k; i++) {
        j0 = s1.find(sep);
        sb[i] = s1.substr(0, j0);
        s1 = s1.substr(j0 + 1, s.length());
    }
    resultat.swap(sb);
    //cout <<"k="<<*k<<"\n";
}