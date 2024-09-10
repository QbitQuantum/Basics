int CompareDoubles2 (double A, double B)
{
    if ((nearbyint(A*1000000.0)-nearbyint(B*1000000.0))>0.0) {
        return 1;
    }else if ((nearbyint(A*1000000.0)-nearbyint(B*1000000.0))==0.0){
        return 0;
    }else{
        return -1;
    }
    
}