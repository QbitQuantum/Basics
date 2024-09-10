int
main(int argc, char* argv[])
{
    if (argc == 0)
    {
        OId* t = new OId();
        BLOBTile b(*t);
        r_Minterval c();
        TypeFactory::instance();
    }
    AdminIf* myAdmin;
    DatabaseIf database;
    TransactionIf ta;

    myAdmin = AdminIf::instance();
    database.open("RMAN");
    ta.begin(&database);

    if (argc >= 2)
    {
        DBMDDCollOIdEntry* mycoll1 = 0;
        OId* id = 0;
        switch(atoi(argv[1]))
        {
        case 1:
            cout << "Creating Entry: " << argv[2] << endl;
            DBMDDCollEntry::newDBMDDCollEntry(argv[2], TypeFactory::mapSetType("MySet2"));
            cout << "aborting" << endl;
            ta.abort();
            break;
        case 2:
            cout << "Creating Entry: " << argv[2] << endl;
            DBMDDCollEntry::newDBMDDCollEntry(argv[2], TypeFactory::mapSetType("MySet2"));
            cout << "commiting" << endl;
            ta.commit();
            break;
        case 3:
            cout << "Reading Entry with OId: " << argv[2] << endl;
            id = new OId(atol(argv[2]), OId::MDDCOLLOID);
            mycoll1 = MDDInit::mapMDDCollOIdEntry(*id);

            cout << "Collection Name\t:" << mycoll1->getCollName() << endl;
            cout << "Collection OId\t:" << mycoll1->getOId() << endl;
            cout << "Collection SetType\t:" << mycoll1->getCollType()->getTypeName() << endl;
            cout << "aborting" << endl;
            ta.abort();
            break;
        default:
            cout << "DONT KNOW WHAT TO DO!" << endl;
        }
    }
    else	{
        cout << "Usage: 1 write abort, 2 write commit, 3 read" << endl << "\t1: name" << endl << "\t2: name" << endl << "\t3: id" << endl;
    }
}