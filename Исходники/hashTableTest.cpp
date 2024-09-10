int main() {
    //Integer HashTable...default value is 0
    cout << "Integer insert, find, and remove" << endl;
    HashTable<int>* intHash = new HashTable<int>(0);

    cout << "Value of f(not in table) is: " << intHash->find("f") << endl;
    cout << endl;
    
    intHash->insert("eight", 8);
    cout << endl;
    
    intHash->insert("seven", 7);
    cout << endl;
    
    cout << "Value of seven is: " << intHash->find("seven") << endl;
    cout << endl;
    
    cout << "Value of eight is: " << intHash->find("eight") << endl;
    cout << endl;
    
    intHash->remove("eight");
    cout << endl;
    
    cout << "Find value of removed key eight: " << intHash->find("eight") << endl;
    
    //Double HashTable...default value is 0.0001
    cout << "Double insert, find, and remove" << endl;
    HashTable<double>* dHash = new HashTable<double>(0.0001);
    
    cout << "Value of f(not in table) is: " << dHash->find("f") << endl;
    cout << endl;
    
    dHash->insert("say", 8.5618);
    cout << endl;
    
    dHash->insert("what", 77.777);
    cout << endl;
    
    cout << "Value of what is: " << dHash->find("what") << endl;
    cout << endl;
    
    cout << "Value of say is: " << dHash->find("say") << endl;
    cout << endl;
    
    dHash->remove("say");
    cout << endl;
    
    cout << "Find value of removed key say: " << dHash->find("say") << endl;

    //String HashTable...default value is an empty string
    cout << "String insert, find, and remove" << endl;
    HashTable<string>* strHash = new HashTable<string>(" ");
    
    cout << "Value of f(not in table) is: " << strHash->find("f") << endl;
    cout << endl;
    
    strHash->insert("hi", "hello");
    cout << endl;
    
    strHash->insert("bye", "goodbye");
    cout << endl;
    
    cout << "Value of bye is: " << strHash->find("bye") << endl;
    cout << endl;
    
    cout << "Value of hi is: " << strHash->find("hi") << endl;
    cout << endl;
    
    strHash->remove("hi");
    cout << endl;
    
    cout << "Find value of removed key hi: " << strHash->find("hi") << endl;
    
    delete intHash;
    delete dHash;
    delete strHash;
    return 0;
}