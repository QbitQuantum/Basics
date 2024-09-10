/*****************************************************************************************************
 *  show -> debug
 *
 ****************************************************************************************************/
void Syntactic::show(){
    TokenType *token = ast->getRoot();
    Attrib *attrib;
    TList *list;
    Operator *op;
    IFElse *__ift;
    Each *each;

    while( token ){
        switch(token->getClasse()){
            case ASSIGN:
                attrib = (Attrib *)token;
                cout<<attrib->getIdentificador()->getToken()<<endl;
                cout<<attrib->getToken()<<endl;
                switch(attrib->getExpression()->getClasse()){
                    case LIST:
                        list = (TList *) attrib->getExpression();
                        list->showItens();
                        break;
                    case OPERATOR:
                        op = (Operator *) attrib->getExpression();
                        cout<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<endl;
                        break;
                    case INTEGER:
                    case FLOAT:
                    case STRING:
                        cout<<attrib->getExpression()->getToken()<<endl;
                        break;
                }
                break;
            case RESERVADO:
                if(token->getToken() == "if"){
                    __ift = (IFElse *) token;
                    op = (Operator *) __ift->getExpression();

                    cout<<"if("<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<")"<<endl;

                    switch(__ift->getBlockIF()->getClasse()){
                        case ASSIGN:
                            attrib = (Attrib *) __ift->getBlockIF();
                            cout<<"{"<<attrib->getIdentificador()->getToken()<<attrib->getToken();
                            switch(attrib->getExpression()->getClasse()){
                                case LIST:
                                    list = (TList *) attrib->getExpression();
                                    cout<<"~(";
                                    list->showItens();
                                    cout<<")}"<<endl;
                                    break;
                                case OPERATOR:
                                    op = (Operator *) attrib->getExpression();
                                    cout<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<"}"<<endl;
                                    break;
                                case INTEGER:
                                case FLOAT:
                                case STRING:
                                    cout<<attrib->getExpression()->getToken()<<"}"<<endl;
                                    break;
                            }
                    }

                    if(__ift->getElseBlock()){
                        switch(__ift->getElseBlock()->getClasse()){
                            case ASSIGN:
                                attrib = (Attrib *) __ift->getElseBlock();
                                cout<<"{"<<attrib->getIdentificador()->getToken()<<attrib->getToken();
                                switch(attrib->getExpression()->getClasse()){
                                    case LIST:
                                        list = (TList *) attrib->getExpression();
                                        cout<<"~(";
                                        list->showItens();
                                        cout<<")}"<<endl;
                                        break;
                                    case OPERATOR:
                                        op = (Operator *) attrib->getExpression();
                                        cout<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<"}"<<endl;
                                        break;
                                    case INTEGER:
                                    case FLOAT:
                                    case STRING:
                                        cout<<attrib->getExpression()->getToken()<<"}"<<endl;
                                        break;
                                }
                        }
                    }
                }
                else{
                    each = (Each *) token;
                    op = (Operator *) each->getExpression();
                    __ift = (IFElse *) each->getBlock();

                    cout<<"each("<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<")"<<endl;
                    cout<<"{"<<__ift->getToken();

                    op = (Operator *) __ift->getExpression();

                    cout<<"("<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<")"<<endl;

                    attrib = (Attrib *) __ift->getBlockIF();

                    cout<<"{"<<attrib->getIdentificador()->getToken()<<attrib->getToken();

                    op = (Operator *) attrib->getExpression();

                    cout<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<"}"<<endl;

                    attrib = (Attrib *) __ift->getElseBlock();

                    cout<<"else{"<<attrib->getIdentificador()->getToken()<<attrib->getToken();

                    op = (Operator *) attrib->getExpression();

                    cout<<op->getLeft()->getToken()<<op->getToken()<<op->getRight()->getToken()<<"}}";
                }

        }

        token = token->getNext();
    }

}