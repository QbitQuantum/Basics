int Exp (int n, int m){
int p;  
    if (m== 1)
        p= n;
    if (m== 2)
        p= m*m;
    if ((n!=1)&&(n!=2))
        p= (Exp (n, m-1))*n;
    return p;
}