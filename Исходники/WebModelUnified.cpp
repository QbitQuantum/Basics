Connection* WebModelUnified::connect()
{
    Connection* conn;
    try {
        conn = new Connection(false);
        conn->connect(mysql_database, mysql_host, mysql_username, mysql_password);
        return conn;
    } catch (BadQuery er){
        cerr << "Error: " << er.what() << endl;
        return NULL;
    }
}