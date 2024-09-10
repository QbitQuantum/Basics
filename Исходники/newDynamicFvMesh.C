Foam::autoPtr<Foam::dynamicFvMesh> Foam::dynamicFvMesh::New(const IOobject& io)
{
    wordList libNames(1);
    libNames[0]=word("mesquiteMotionSolver");

    forAll(libNames,i) {
        const word libName("lib"+libNames[i]+".so");

        bool ok=dlLibraryTable::open(libName);
        if(!ok) {
            WarningIn("dynamicFvMesh::New(const IOobject& io)")
                << "Loading of dynamic mesh library " << libName
                    << " unsuccesful. Some dynamic mesh  methods may not be "
                    << " available"
                    << endl;
        }
    }

    // Enclose the creation of the dynamicMesh to ensure it is
    // deleted before the dynamicFvMesh is created otherwise the dictionary
    // is entered in the database twice
    IOdictionary dynamicMeshDict
    (
        IOobject
        (
            "dynamicMeshDict",
            io.time().constant(),
            (io.name() == dynamicFvMesh::defaultRegion ? "" : io.name() ),
            io.db(),
            IOobject::MUST_READ,
            IOobject::NO_WRITE,
            false
        )
    );

    word dynamicFvMeshTypeName(dynamicMeshDict.lookup("dynamicFvMesh"));

    Info<< "Selecting dynamicFvMesh " << dynamicFvMeshTypeName << endl;

    dlLibraryTable::open
    (
        dynamicMeshDict,
        "dynamicFvMeshLibs",
        IOobjectConstructorTablePtr_
    );

    if (!IOobjectConstructorTablePtr_)
    {
        FatalErrorIn
        (
            "dynamicFvMesh::New(const IOobject&)"
        )   << "dynamicFvMesh table is empty"
            << exit(FatalError);
    }

    IOobjectConstructorTable::iterator cstrIter =
        IOobjectConstructorTablePtr_->find(dynamicFvMeshTypeName);

    if (cstrIter == IOobjectConstructorTablePtr_->end())
    {
        FatalErrorIn
        (
            "dynamicFvMesh::New(const IOobject&)"
        )   << "Unknown dynamicFvMesh type " << dynamicFvMeshTypeName
            << endl << endl
            << "Valid dynamicFvMesh types are :" << endl
            << IOobjectConstructorTablePtr_->toc()
            << exit(FatalError);
    }

    return autoPtr<dynamicFvMesh>(cstrIter()(io));
}