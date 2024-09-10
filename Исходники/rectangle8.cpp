MatrixXd Rectangle8::Give_N()
{
    MatrixXd N;
    N.setZero(ngauss,nnode);

    for (int i1=0;i1<ngauss;i1++)
    {
               N(i1,0) = -0.25*(1.-xi(0,i1))*(1.-xi(1,i1))*(1.+xi(0,i1)+xi(1,i1));
               N(i1,1) = 0.25*(1.+xi(0,i1))*(1.-xi(1,i1))*(xi(0,i1)-xi(1,i1)-1.);
               N(i1,2) = 0.25*(1.+xi(0,i1))*(1.+xi(1,i1))*(xi(0,i1)+xi(1,i1)-1.);
               N(i1,3) = 0.25*(1.-xi(0,i1))*(1.+xi(1,i1))*(xi(1,i1)-xi(0,i1)-1.);
               N(i1,4) = 0.5*(1.-xi(0,i1)*xi(0,i1))*(1.-xi(1,i1));
               N(i1,5) = 0.5*(1.+xi(0,i1))*(1.-xi(1,i1)*xi(1,i1));
               N(i1,6) = 0.5*(1.-xi(0,i1)*xi(0,i1))*(1.+xi(1,i1));
               N(i1,7) = 0.5*(1.-xi(0,i1))*(1.-xi(1,i1)*xi(1,i1));
    }

    return N;

}