unsigned int user_remove(Table &t) {
    unsigned int key;
    cout << "Enter key to remove:\n";
    cin >> key;
    if (key != 0) {
        unsigned int start = Entry::access_count();
        if (t.remove(key))
            cout << "removed key: " << key << endl;
        else
            cout << "did not find key: " << key << endl;
        cout << "(accesses: "
            << Entry::access_count() - start << ")\n";
    }
    return key;
}