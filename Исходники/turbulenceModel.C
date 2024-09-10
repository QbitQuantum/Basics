autoPtr<turbulenceModel> turbulenceModel::New
(
    const volVectorField& U,
    const surfaceScalarField& phi,
    transportModel& transport,
    const word& turbulenceModelName
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
                "turbulenceProperties",
                U.time().constant(),
                U.db(),
                IOobject::MUST_READ_IF_MODIFIED,
                IOobject::NO_WRITE,
                false
            )
        ).lookup("simulationType")
    );

    Info<< "Selecting turbulence model type " << modelType << endl;

    turbulenceModelConstructorTable::iterator cstrIter =
        turbulenceModelConstructorTablePtr_->find(modelType);

    if (cstrIter == turbulenceModelConstructorTablePtr_->end())
    {
        FatalErrorIn
        (
            "turbulenceModel::New(const volVectorField&, "
            "const surfaceScalarField&, transportModel&, const word&)"
        )   << "Unknown turbulenceModel type "
            << modelType << nl << nl
            << "Valid turbulenceModel types:" << endl
            << turbulenceModelConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<turbulenceModel>
    (
        cstrIter()(U, phi, transport, turbulenceModelName)
    );
}