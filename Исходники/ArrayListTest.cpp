void random_insert_delete_entrys(double insertFactor) {
    cout << "random_insert_delete_entrys start   insertFactor : " << insertFactor <<  endl;
    
    srand((unsigned long) time(NULL));
    
    ArrayList<int> list;
    vector<int> vec;
    
    
    int numOfOp = 100000;
    
    for (int i = 0; i < numOfOp; ++i) {
        int op = random() % 10;
        if (op <= insertFactor) {
            int num = rand() % 1000000;
            list.add(num);
            vec.push_back(num);
        } else {
            if (vec.size() > 0) {
                int num = random() % vec.size();
                
                erase(vec, num);
                list.remove(num);
            }
        }
        assert(vec.size() == list.size());
    }
    
    assert(vec.size() == list.size());
    for (int i = 0; i < vec.size(); ++i) {
        assert(vec[i] == list.get(i));
    }
    
    cout << "random_insert_delete_entrys end." << endl;
}