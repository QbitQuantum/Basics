//起始乱序分牌
void GameServer::mixedOrder(int x[], int n)
{
    srand(static_cast<unsigned int>(time(0)));
    int index1,index2,tmp;
    for(int i=0;i<n;i++){
        index1=rand()%54;
        index2=rand()%54;
        tmp=x[index1];
        x[index1]=x[index2];
        x[index2]=tmp;
    }
}