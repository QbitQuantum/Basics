bool gcta::calcu_Vi(eigenMatrix &Vi, eigenVector &prev_varcmp, double &logdet, int &iter)
{
    int i=0, j=0, k=0;
    string errmsg="\nError: the V (variance-covariance) matrix is not invertible.";

    Vi.setZero();
    if(_r_indx.size()==0){
        Vi.diagonal()=eigenVector::Constant(_n, 1.0/prev_varcmp[_r_indx.size()]);
        logdet=_n*log(prev_varcmp[_r_indx.size()]);
    }
    else{
        Vi.diagonal()=eigenVector::Constant(_n, prev_varcmp[_r_indx.size()]);
        for(i=0; i<_r_indx.size(); i++) Vi+=(_A.block(0,_r_indx[i]*_n,_n,_n))*prev_varcmp[i];
        if(!comput_inverse_logdet_LDLT(Vi, prev_varcmp, logdet)){
            cout<<"Warning: the variance-covaraince matrix V is negative-definite."<<endl;
            bend_A();
            iter=-1;
            cout<<"Restarting iterations ..."<<endl;
            return false;
        }
    }
    return true;
}