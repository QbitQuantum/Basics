int main(int argc, char * argv[]) {

    // gets the hash table size from the command line

    int hashSize = Table::HASH_SIZE;
    
    Table * grades;  // Table is dynamically allocated below, so we can call
    // different constructors depending on input from the user.
    
    if (argc > 1) {
        hashSize = atoi(argv[1]);  // atoi converts c-string to int
        
        if (hashSize < 1) {
            cout << "Command line argument (hashSize) must be a positive number"
            << endl;
            return 1;
        }
        
        grades = new Table(hashSize);
        
    }
    else {   // no command line args given -- use default table size
        grades = new Table();
    }
    
    
    grades->hashStats(cout);
    
    // add more code here
    // Reminder: use -> when calling Table methods, since grades is type Table*
    printCmdSummary();//print out command lines
    //initialize some data
    char c;
    string name;
    int score;
    bool isValid=true;
    //while isvalid it will keep going ask client to enter untill quit
    do{
        cout<<"\n Please enter the command shows above [i , c , l , r , p , s , h , t , q]: ";
        cin>>c;
        
        if(cin.fail()){//if cin fail promt fail info and quit
            cout<<"exit"<<endl;
            cout<<"ERROR: invalid command!"<<endl;
            isValid=false;
        }
        else{
            switch (c){//switch method provide client to choose
                case 'i':
                cout<<"You are now in the insert method: "<<endl;
                cout<<"here is the example: "<<endl;
                cout<<"---Name: James ---"<<endl;
                cout<<"---Score: 86   ---"<<endl;;
                do{
                    cout<<"Please enter name: "<<endl;
                    cin>>name;
                }while(isValidString(name)==false);//check valid or not
                do{
                    cout<<"Please enter score: "<<endl;
                    cin>>score;
                }while(isValidInt(score)==false);//check valid or not
                
                if(grades->insert(name,score)==true){//if no same key existed then record entry
                    cout<<"Entry recorded!"<<endl;
                }else{
                    cout<<"Entry has already existed, Nothing changes!"<<endl;
                }
                break;
                
                case 'c':
                cout<<"You are now in the change method: "<<endl;
                cout<<"here is the example: "<<endl;
                cout<<"---Name: James ---"<<endl;
                cout<<"---Score: 86   ---"<<endl;;
                do{
                    cout<<"Please enter name: "<<endl;
                    cin>>name;
                }while(isValidString(name)==false);
                do{
                    cout<<"Please enter new score: "<<endl;
                    cin>>score;
                }while(isValidInt(score)==false);
                if(grades->lookup(name)!=NULL){//if found
                    grades->remove(name);//remove
                    grades->insert(name,score);//then insert again
                    cout<<"Record changed!"<<endl;
                }else{
                    cout<<"No such entry"<<endl;
                }
                break;
                
                case 'l':
                cout<<"You are now in the lookup method: "<<endl;
                cout<<"here is the example: "<<endl;
                cout<<"---Name: James ---"<<endl;
                do{
                    cout<<"Please enter name you want to lookup: "<<endl;
                    cin>>name;
                }while(isValidString(name)==false);
                if(grades->lookup(name)!=NULL){//if found
                    int* address=grades->lookup(name);//assign address to it
                    cout<<"Record found!"<<endl;
                    cout<<"the address is :"<<address<<endl;
                }else{
                    cout<<"No such entry"<<endl;
                }
                break;
                
                case 'r':
                cout<<"You are now in the remove method: "<<endl;
                cout<<"here is the example: "<<endl;
                cout<<"---Name: James ---"<<endl;
                do{
                    cout<<"Please enter name: "<<endl;
                    cin>>name;
                }while(isValidString(name)==false);
                
                if(grades->remove(name)==true){//if found
                    cout<<"Entry removed!"<<endl;//target removed
                }else{
                    cout<<"No such entry!"<<endl;
                }
                break;
                
                case 'p':
                cout<<"You are now in the print method: "<<endl;
                cout<<"here is the table: "<<endl;
                if(grades->numEntries()==0){
                    cout<<"<empty>"<<endl;
                }else{
                    grades->printAll();//print out all the entries
                }
                break;
                
                case 's':
                cout<<"You are now in the size method: "<<endl;
                cout<<"here is the total number of entries: "<<endl;
                cout<<grades->numEntries();//print out entries numbers
                break;
                
                case 'h':
                cout<<"You are now in the help method: "<<endl;
                cout<<"here is the comands: "<<endl;
                printCmdSummary();//print summary
                break;
                
                case 't':
                cout<<"You are now in the stats method: "<<endl;
                cout<<"here is the stats of this table: "<<endl;
                grades->hashStats(cout);//print out hashstats
                break;
                
                case 'q':
                cout<<"quitting this program"<<endl;
                isValid=false;//end the loop and quit 
                break;

                default:
                cout<<"Invalid Command,Please try again."<<endl;
                break;
            }
        }
    }while(isValid);
    
    return 0;
}