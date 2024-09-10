int main()
{
   using std::cin;
   using std::cout;
   using std::endl;
   using std::strchr;

   QueueTP<Worker *> lolas(SIZE);
   

    int ct;
    Worker * pwk;
    for (ct = 0; ct < SIZE; ct++)
    {
        char choice;
        cout << "Enter the employee category:\n"
            << "w: waiter  s: singer  "
            << "t: singing waiter  q: quit\n";
        cin >> choice;
        while (strchr("wstq", choice) == NULL)
        {
            cout << "Please enter a w, s, t, or q: ";
            cin >> choice;
        }
        if (choice == 'q')
            break;
        switch(choice)
        {
            case 'w':   pwk = new Waiter;
                        break;
            case 's':   pwk = new Singer;
                        break;
            case 't':   pwk = new SingingWaiter;
                        break;
        }
        cin.get();
        pwk->Set();
        lolas.enqueue(*pwk);
        delete pwk;
    }

    cout << "\nHere is your staff:\n";
    while (!lolas.isempty())
    {
        cout << endl;
        lolas.dequeue(*pwk);
        pwk->Show();        
    }
    cout << "Total call of base constructor:" << Worker::num_of_constructors_ << endl;
    cout << "Bye.\n";
    return 0; 
}