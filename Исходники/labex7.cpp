int main(){
    Queue a = Queue();
    a.add("a");
    cout << a.getUsed() << endl;
    a.add("b");
    a.add("c");
    a.add("d");
    cout << a.remove() << endl;
    cout << a.remove() << endl;
    cout << a.getUsed() << endl;
    a.add("e");
    a.add("f");
    a.add("break");
    cout << a.getUsed() << endl;
    cout << a.remove() << endl;
    cout << a.remove() << endl;
    cout << a.remove() << endl;
    a.add("fake");
    cout << a.getUsed() << endl;
    cout << a.remove() << endl;
    cout << a.remove() << endl;
    cout << a.remove() << endl;
    cout << a.getUsed() << endl;
    
    //system("pause");
    return 0;
} //main()