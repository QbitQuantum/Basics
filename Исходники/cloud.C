Foam::cloud::cloud(const objectRegistry& obr, const word& cloudName)
:
    objectRegistry
    (
        IOobject
        (
            ( cloudName.size() ? cloudName : defaultName ),
            obr.time().timeName(),
            prefix,
            obr,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        )
    )
{}