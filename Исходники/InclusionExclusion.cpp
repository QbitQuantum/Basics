ll incexc(vector<int> v, int i, int left, int lcmt){
    if(left==0) return div(lcmt);
    if(i==v.size()) return 0;
    return (incexc(v, i+1, left, lcmt)+
           ((left>0)? incexc(v, i+1, left-1, lcm(lcmt, v[i])) :0)) % MOD;
}