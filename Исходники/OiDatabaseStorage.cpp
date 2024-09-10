/* *
* init function creates database with specified name and makes a connection
* which is stored in private variable mysqlpp::Connection connection_
*
* Second phase is to parse given file and store found data: nodes, lines, surfaces and recorded data
* into that database.
*
*/
bool DatabaseStorage::init(const string& file)
{
    if (file.empty())
    {
        std::cerr << "DatabaseStorage::init --\n";
        std::cerr << "File: is empty\n";
        return false;
    }

    // TODO: repository? argument "file" is not needed.
    string repository = Oi::stripToFileName(file);
    if (repository.empty())
    {
        std::cerr << "DatabaseStorage::init --\n";
        std::cerr << "Bad file name: " << file << "\n";
        return false;
    }

    mysqlpp::Connection con;

    // noexception is needed not to throw exception when such database exist.
    mysqlpp::NoExceptions ne(con);

    // try to create database and table
    if (!connectToDatabase(con))
    {
        std::cout << "Database: " << DATABASE << " do not exist. Creating new one!\n";
        if (!con.create_db(DATABASE))
        {
            std::cerr << "Error creating database: " << con.error() << std::endl;
            return false;
        }
        if(!createTable())
        {
            std::cerr << "Error creating table: Store.\n";
            return false;
        }
    }



    if (!existTable())
        createTable();

    return true;
}