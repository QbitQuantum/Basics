Foam::autoPtr<Foam::SRF::SRFModel> Foam::SRF::SRFModel::New
(
    const volVectorField& Urel
)
{
    // get model name, but do not register the dictionary
    // otherwise it is registered in the database twice
    const word modelType
    (
        IOdictionary
        (
            IOobject
            (
                "SRFProperties",
                Urel.time().constant(),
                Urel.db(),
                IOobject::MUST_READ_IF_MODIFIED,
                IOobject::NO_WRITE,
                false
            )
        ).lookup("SRFModel")
    );

    Info<< "Selecting SRFModel " << modelType << endl;

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(modelType);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorIn
        (
            "SRFModel::New(const fvMesh&)"
        )   << "Unknown SRFModel type "
            << modelType << nl << nl
            << "Valid SRFModel types are :" << nl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<SRFModel>(cstrIter()(Urel));
}