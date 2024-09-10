Foam::surfaceRegistry::surfaceRegistry
(
    const objectRegistry& obr,
    const word& surfName
)
:
    objectRegistry
    (
        IOobject
        (
            ( surfName.size() ? surfName : defaultName ),
            obr.time().timeName(),
            prefix,
            obr,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        )
    )
{}