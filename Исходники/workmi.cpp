int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::strchr;

    Worker * lolas[SIZE];
    int ct;
    for (ct = 0; ct < SIZE; ct++)
    {
        char choice;
        cout << "Zadejte kategorii zamestnance:\n"
             << "c: cisnik p: pevec "
             << "t: zpivajici cisnik k: konec\n";
        cin >> choice;
        while (strchr("cptk", choice) == NULL)
        {
            cout << "Zadejte prosim c, p, t nebo k: ";
            cin >> choice;
        }
        if (choice == 'k')
            break;
        switch(choice)
        {
        case 'c':
            lolas[ct] = new Waiter;
            break;
        case 'p':
            lolas[ct] = new Singer;
            break;
        case 't':
            lolas[ct] = new SingingWaiter;
            break;
        }
        cin.get();
        lolas[ct]->Set();
    }

    cout << "\nZde je vas tym:\n";
    int i;
    for (i = 0; i < ct; i++)
    {
        cout << endl;
        lolas[i]->Show();
    }
    for (i = 0; i < ct; i++)
        delete lolas[i];
    cout << "Nashledanou.\n";
    return 0;
}