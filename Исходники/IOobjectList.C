Foam::IOobjectList::IOobjectList
(
    const objectRegistry& db,
    const fileName& instance,
    const fileName& local
)
:
    HashPtrTable<IOobject>()
{
    word newInstance = instance;

    if (!isDir(db.path(instance)))
    {
        newInstance = db.time().findInstancePath(instant(instance));

        if (newInstance.empty())
        {
            return;
        }
    }

    // Create list file names in directory
    fileNameList ObjectNames =
        readDir(db.path(newInstance, db.dbDir()/local), fileName::FILE);

    forAll(ObjectNames, i)
    {
        IOobject* objectPtr = new IOobject
        (
            ObjectNames[i],
            newInstance,
            local,
            db,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        );

        if (objectPtr->headerOk())
        {
            insert(ObjectNames[i], objectPtr);
        }
        else
        {
            delete objectPtr;
        }
    }