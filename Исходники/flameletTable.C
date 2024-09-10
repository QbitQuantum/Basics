Foam::autoPtr<Foam::flameletTable>
Foam::flameletTable::New(const fvMesh& mesh, const word& tableName)
{
    const word modelName
    (
        IOdictionary
        (
            IOobject
            (
                "tableProperties",
                mesh.time().constant(),
                mesh,
                IOobject::MUST_READ,
                IOobject::NO_WRITE,
                false
            )
        ).lookup("interpolationType")
    );

    dictionaryConstructorTable::iterator cstrIter =
    dictionaryConstructorTablePtr_->find(modelName);

    return cstrIter()(mesh, tableName);
}