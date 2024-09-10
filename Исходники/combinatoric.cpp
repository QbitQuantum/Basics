TCombo M_th_Permut(int M, int k)
{
    if(k==0)
        return TCombo();
    int m0 =  M / (factorial(k-1));
    int m1 =  M % (factorial(k-1));
    TCombo ret;
    ret.push_back(m0);
    TCombo sub = M_th_Permut(m1, k-1);
    transform(sub.begin(),sub.end(), back_inserter(ret), 
                [m0] (int n) { return n<m0 ? n : n+1;} );
    return ret;
    
}