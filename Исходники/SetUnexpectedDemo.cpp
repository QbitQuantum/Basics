void main()
{
    int fd;

    set_unexpected(unexpected_routine);        // This was added

    if ((fd = open("TERMS1.TXT", O_RDONLY | O_CREAT)) == -1 )  {
        cout<<"Unable to open file TERMS1.TXT"<<endl;
        return;
    }

    try {
        Vector vec1(4);

        for (int index = 0; index < 4; index++) vec1[index] = 4.0 * index;
        cout<<"Elements of vec1: "<<endl;
        vec1.Traverse();

        Create_New_Vector();
    }

    catch(char * err) {
        cout<<"Inside catch(char *) of main..."<<endl;
        cout<<err<<endl;
    }

    catch(Xception & err) {
        cout<<"Inside catch(Xception &) of main..."<<endl;
        err.Display();
    }

    catch(...) {
        cout<<"Inside the catch all handler of main..."<<endl;
    }

    cout<<"Closing file descriptor..."<<endl;

    close(fd);

    cout<<"Exiting main - program completed..."<<'\n';
}