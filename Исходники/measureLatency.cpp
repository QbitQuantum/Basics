void run(string router, string ns, long long start, long long range, int sleepTime) {
    DBClientConnection c;
    c.connect(router);
    c.setWriteConcern(W_NORMAL);
    
    struct timeval start_time, stop_time, delay;
    char timeStr[25];
    bool flag;
    BSONObj b;
    srand(time(NULL));
    long long user_id = -1;
    long long number = -1;
    int opSelector;
    string s;

    BSONObj insertObj;
    BSONObj query;
    BSONObj updateObj;
    BSONObj readObj;

    int numOps = 3; 
    int i = 0;

    string operation = "none";

    map<long long, int> insertedKeys;

    while( true ) {
        flag = false;
        curTimeString(timeStr);
        gettimeofday(&start_time, NULL);

        opSelector = i % numOps;
        i++;
        try {
            switch(opSelector) {
                case 0: //insert
                        operation = "insert";
                        while(true) {
                            user_id = start + (rand() % range);
                            if( insertedKeys.find(user_id) == insertedKeys.end()) { //key not been inserted previously
                                insertedKeys.insert(make_pair(user_id, 1));
                                cout<<operation<<": Info: inserting " << user_id << endl;
                                break;
                            } 
                        }
                        //insert command goes here
                        number = 2 * start + range - user_id; 
                        insertObj = BSON("user_id" << user_id << "number" << number << "name" << "name");
                        //cout<<"insert: "<<insertObj.toString()<<endl;
                        c.insert(ns, insertObj);
                        s = c.getLastError(ns, false, false, 1, 0);
                        if (s.length() > 0)
                        {
                            flag = true;
                            cout << "Error:" << s << endl;
                        }
                    break;
                case 1: //update
                        operation = "update";
                        //update command goes here
                        query = BSON("user_id" << user_id);
                        updateObj = BSON("user_id" << user_id << "number" << number << "name" << "nameUpdated");
                        //cout<<"update: "<<updateObj.toString()<<endl;
                        c.update(ns, Query(query), updateObj);
                        s = c.getLastError(ns, false, false, 1, 0);
                        if (s.length() > 0)
                        {
                            flag = true;
                            cout << "Error:" << s << endl;
                        }
                    break;
                case 2:
                        //read
                        operation = "read";
                        readObj = BSON("user_id" << user_id);
                        //cout<<"read: "<<readObj.toString()<<endl;
                        b = c.findOne(ns, Query(readObj), 0, QueryOption_SlaveOk);
                        if (b.isEmpty() <= 0)
                            flag = true;
                        s = c.getLastError(ns, false, false, 1, 0);
                        if (s.length() > 0)
                        {
                            flag = true;
                            cout << "Error:" << s << endl;
                        }
                    break;
                default:
                    cout<<"Unrecognized opSelector ! " << opSelector << endl;
                    cout<<"i : " << i << " numOps : " << numOps << endl;
                    break; 
            }
        } catch (DBException e){
            flag = true;
            cout << "Error: " << e.toString() << endl;
        }

        if (!flag) {
            gettimeofday(&stop_time, NULL);
            if (opSelector == 2)
		        cout << "Returned result:" << b.toString() << endl;
            delay = subtract(start_time, stop_time);
            cout<<operation<<": ";
            cout << timeStr << ": " << delay.tv_sec*1000 + delay.tv_usec/(double)1000 << endl;
        } else {
            cout<<operation<<": ";
		    cout << timeStr << ": -100" << endl;
        }

        usleep(sleepTime);
    }
}