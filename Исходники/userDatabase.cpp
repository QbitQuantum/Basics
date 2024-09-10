//功能读入窗口，中枢函数，返回false的时候读入结束
bool userDatabase::userRead(){
    cout << endl << username << ">" << endl;
    switch(mySql.read()){
        case 0: return false;
        case 1:
            if(!CreateTable())  cout << "[Error] Create table error!" << endl;
                break;
        case 2:
            if(!CreateView())   cout << "[Error] Create view error!" << endl;
            break;
        case 3:
            if(!CreateIndex())  cout << "[Error] Create index error!" << endl;
            break;
        case 10:
            if(!InsertTable())  cout << "[Error] Insert error!" << endl;
                break;
        case 11:
            if(!SelectTable())  cout << "[Error] Select error!" << endl;
                break;
        case 12:
            if(!DeleteTable())  cout << "[Error] Drop table error!" << endl;
                break;
        case 13:
            if(!UpdateTable())  cout << "[Error] Update table error!" << endl;
                break;
        case 14:
            if(!DeleteData())   cout << "[Error] Delete data error!" << endl;
                break;
        case 15:
            if(!DeleteView())   cout << "[Error] Delete view error!" << endl;
                break;
        case 16:
            if(!GrantToUser())  cout << "[Error] Grant to user error!" << endl;
            break;
        case 20:
            readme.createHelp();
            break;
        case 21:
            readme.selectHelp();
            break;
        case 22:
            readme.insertHelp();
            break;
        case 23:
            readme.dropHelp();
            break;
        case 24:
            readme.updateHelp();
            break;
        case 25:
            InputAllTable();
            InputAllView();
            InputAllIndex();
            break;
        case 26:
            InputAllTable();
            break;
        case 27:
            InputAllView();
            break;
        case 28:
            InputAllIndex();
            break;
        default :
            printf("[Error] SQL input error!\n");
            break;
    }
    return true;
};