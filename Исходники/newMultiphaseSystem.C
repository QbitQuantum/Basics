Foam::autoPtr<Foam::multiphaseSystem> Foam::multiphaseSystem::New
(
    const fvMesh& mesh
)
{
    const word multiphaseSystemType
    (
        IOdictionary
        (
            IOobject
            (
                propertiesName,
                mesh.time().constant(),
                mesh,
                IOobject::MUST_READ_IF_MODIFIED,
                IOobject::NO_WRITE,
                false
            )
        ).lookup("type")
    );

    Info<< "Selecting multiphaseSystem "
        << multiphaseSystemType << endl;

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(multiphaseSystemType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorInFunction
            << "Unknown multiphaseSystemType type "
            << multiphaseSystemType << endl << endl
            << "Valid multiphaseSystem types are : " << endl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return cstrIter()(mesh);
}