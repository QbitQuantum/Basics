int main()
{
    // print my name and this assignment's title
    cout << "Lab 5A, Static Array Program \n";
    cout << "Programmer: Haris Hanif\n";
    cout << "Editor(s) used: Xcode\n";
    cout << "Compiler(s) used: Xcode\n";
    cout << "File: " << __FILE__ << endl;
    cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
    int num;
    int arraysize=0;
    string buf;
    StaticArray<int,200> sArray;
    
    for (int i=0; i < sArray.getCapacity(); i++)
    {
        cout << "Enter " ;
        cout<< i+1;
        cout<< " number  or 'q' || 'Q' to exit: ";
        cin >> buf;

        if (buf =="Q"||buf=="q")
        {
            cout<<endl << "Here is the output datastructure size: ";
            cout<<arraysize <<endl;
            break;
        }
        else
        {
            num = atof (buf.c_str());
            cin.ignore (1000,10);
            sArray[i] = num;
        }

        cout << "\nList of entered values: " << endl;
        for (int j=0; j<=i; j++)
        {
            cout << sArray[j] << ' ';
        }
        arraysize++;
        cout << endl << endl;
    }

    cout << "Implementing Linear Search"<<endl;
    cout << "\nEnter number to search or 'q' || 'Q' to exit:";
    
    while (true)
    {
        cin >> buf;

        if (buf == "Q" || buf == "q")
            break;
        else
        {
            num = atof (buf.c_str());
            cin.ignore (1000,10);
            cout << "\nNumber ";
            cout<<num;
            cout<<" in array location is in :";
            cout<< sArray.lsearch(num);
            cout<<" element" << endl;
            cout << "\nenter  a number to search or 'q' || 'Q' to exit: ";
        }
    }
}