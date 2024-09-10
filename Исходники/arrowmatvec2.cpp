void Atimesx(const Matrix & d, const Matrix & a, const Matrix & x, Matrix & Ax)
{
    int n=d.size();
    Ax=(d.array()*x.array()).matrix();
    VectorXd Axcut=Ax.head(n-1);
    VectorXd acut = a.head(n-1);
    VectorXd xcut = x.head(n-1);
    
    Ax << Axcut + x(n-1)*acut, Ax(n-1)+ acut.transpose()*xcut;
}