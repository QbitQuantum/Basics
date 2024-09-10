// ---------------------------------------------------------
void test02()
{
    ArrayList<int> a;

    cout << endl << endl;
    cout << " ***************** " << endl;
    cout << " *  TEST SET #2  * " << endl;
    cout << " ***************** " << endl;

    cout << "ArrayList a" << endl;
    cout << a << endl;
    cout << "Size of a = " << a.size() << endl;

    //TEST : Inserting 8 elements to a
    cout << endl << "TEST : Inserting 8 elements to a" << endl;
    for (unsigned int k=0; k<8; k++) {
        a.insert_back(k*8);
    }
    cout << a << endl;
    cout << "Size of a = " << a.size() << endl;


    // TEST : Clearing the list
    cout << endl << "TEST : Clearing a" << endl;
    a.clear();
    cout << a << endl;
    cout << "Size of a = " << a.size() << endl;


    // TEST : Inserting 10 elements
    cout << endl << "TEST : Inserting 10 elements to a" << endl;
    for (unsigned int k=0; k<10; k++) {
        a.insert_back(k*5);
    }
    cout << a << endl;
    cout << "Size of a = " << a.size() << endl;


    // TEST : Removing Elements in the middle
    cout << endl << "TEST : Removing elements" << endl;
    a.remove(2);
    cout << a << endl;
    a.remove(4);
    cout << a << endl;
    a.remove(6);
    cout << a << endl;
    cout << "Size of a = " << a.size() << endl;


    // TEST : Removing first and last Elements
    cout << endl << "TEST : Removing last and first elements" << endl;
    cout << a << endl;
    a.remove(6);
    cout << a << endl;
    a.remove(0);
    cout << a << endl;
    cout << "Size of a = " << a.size() << endl;


    // TEST : Finding Particular elements
    cout << endl << "TEST : Finding particular elements" << endl;
    cout << a << endl;
    cout << "Size of a = " << a.size() << endl;
    cout << "15 is at location " << a.find(15) << endl;
    cout << "30 is at location " << a.find(30) << endl;
    cout << "50 is at location " << a.find(50) << endl;


    // TEST : Shrinking the underlaying array.
    cout << endl << "TEST : Shrinking the underlaying array" << endl;
    a.clear();
    for (unsigned int k=0; k<1000; k++) {
        a.insert_back(k*2);
    }
    cout << "Size of a = " << a.size() << endl;
    cout << "Capacity of a = " << a.max() << endl;
    cout << "deleting 950 elements" << endl;
    for (unsigned int k=0; k<950; k++) {
        a.remove(a.size()-1);
    }
    cout << "Size of a = " << a.size() << endl;
    cout << "Capacity of a = " << a.max() << endl;
    cout << "so ArrayList is memory efficient :-)" << endl;

} // Destructor Called Here!!