void Nori(int rs,int rt,int C){
    int RS;
    if(for_ex == 1)RS = wbrsd;
    else if(for_id == 1)RS = wbrs;
    else RS = registers[rs];
    unsigned int A1 = C;
    unsigned int A2 = RS;
    int i;
    wbad = rt;
    wbrs = 0;
    for(i = 0;i < 32;i++){
        wbrs = wbrs + (!((A1%2)||(A2%2)))*(int)(Pow(2,i)+0.01);
        A1 = A1/2;
        A2 = A2/2;
    }
}