Foam::autoPtr<Foam::dynamicFvMesh> Foam::dynamicFvMesh::New
(
    const IOobject& io,
    const dictionary& dict,
    const word& defaultMeshTypeName
)
{
    word dynamicFvMeshTypeName(defaultMeshTypeName);
    if (dict.readIfPresent("dynamicFvMesh", dynamicFvMeshTypeName))
    {
        Info<< "Selecting dynamicFvMesh " << dynamicFvMeshTypeName << endl;
    }

    const_cast<Time&>(io.time()).libs().open
    (
        dict,
        "dynamicFvMeshLibs",
        IOobjectConstructorTablePtr_
    );

    if (!IOobjectConstructorTablePtr_)
    {
        FatalErrorInFunction
            << "dynamicFvMesh table is empty"
            << exit(FatalError);
    }

    IOobjectConstructorTable::iterator cstrIter =
        IOobjectConstructorTablePtr_->find(dynamicFvMeshTypeName);

    if (cstrIter == IOobjectConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown dynamicFvMesh type "
            << dynamicFvMeshTypeName << nl << nl
            << "Valid dynamicFvMesh types are :" << endl
            << IOobjectConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<dynamicFvMesh>(cstrIter()(io));
}