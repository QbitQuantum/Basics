vector<computersabstract> ComputerManipulation::sortComputers(QString& str, char& choice)
{
    //Create objects
    SQLConnect database;
    vector<computersabstract> returnvec;

    //Connect to database and get query
    database.ConnectToDB();
    QSqlQuery query = database.GetQuery();

    switch(choice)
    {
        case 1:
            query.prepare(QString("SELECT * FROM scientists ORDER BY name, year").arg(str));
            break;
        case 2:
            query.prepare(QString("SELECT * FROM scientists ORDER BY year, name").arg(str));
            break;
        case 3:
            query.prepare(QString("SELECT * FROM scientists ORDER BY type, name").arg(str));
            break;
    }
    query.exec();
    FillcsVector(query,returnvec);

    //Close the database and make sure that the vector has only values nothing empty.
    database.Disconnect();
    query.clear();

    //return vector
    return returnvec;

}