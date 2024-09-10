int main()
{
    string stream = "";
    Connection connection;
    SenderThread senderThread;
    senderThread.start();
    cout << "Connecting" << endl;
    if (connection.connect("127.0.0.1", 8080, 3))
    {
        cout << "Connected" << endl;
        stream = connection.getData();
        if (stream != "")
        {
            cout << stream << endl;
        }
        else
        {
            cout << "No data sent." << endl;
        }
        exit(0);
    }
    else
    {
        cout << "Failed to connect." << endl;
    }
}