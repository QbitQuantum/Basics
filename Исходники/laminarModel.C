Foam::autoPtr<Foam::laminarModel<BasicTurbulenceModel>>
Foam::laminarModel<BasicTurbulenceModel>::New
(
    const alphaField& alpha,
    const rhoField& rho,
    const volVectorField& U,
    const surfaceScalarField& alphaRhoPhi,
    const surfaceScalarField& phi,
    const transportModel& transport,
    const word& propertiesName
)
{
    IOdictionary modelDict
    (
        IOobject
        (
            IOobject::groupName(propertiesName, U.group()),
            U.time().constant(),
            U.db(),
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE,
            false
        )
    );

    if (modelDict.found("laminar"))
    {
        // get model name, but do not register the dictionary
        // otherwise it is registered in the database twice
        const word modelType
        (
            modelDict.subDict("laminar").lookup("laminarModel")
        );

        Info<< "Selecting laminar stress model " << modelType << endl;

        typename dictionaryConstructorTable::iterator cstrIter =
            dictionaryConstructorTablePtr_->find(modelType);

        if (cstrIter == dictionaryConstructorTablePtr_->end())
        {
            FatalErrorInFunction
                << "Unknown laminarModel type "
                << modelType << nl << nl
                << "Valid laminarModel types:" << endl
                << dictionaryConstructorTablePtr_->sortedToc()
                << exit(FatalError);
        }

        return autoPtr<laminarModel>
        (
            cstrIter()
            (
                alpha,
                rho,
                U,
                alphaRhoPhi,
                phi,
                transport, propertiesName)
        );
    }
    else
    {
        Info<< "Selecting laminar stress model "
            << laminarModels::Stokes<BasicTurbulenceModel>::typeName << endl;

        return autoPtr<laminarModel>
        (
            new laminarModels::Stokes<BasicTurbulenceModel>
            (
                alpha,
                rho,
                U,
                alphaRhoPhi,
                phi,
                transport,
                propertiesName
            )
        );
    }
}