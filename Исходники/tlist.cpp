/*****************************************************************************************************
 *  showItens -> apenas para ver o que tem
 *
 ****************************************************************************************************/
void TList::showItens(){
    QList<TokenType*>::Iterator it;
    TokenType *t;

    for(it = list.begin(); it != list.end(); ++it){
        t = *it;
        cout<<t->getToken()<<" ";
    }
    cout<<endl;
}