Foam::functionObjects::regionFunctionObject::regionFunctionObject
(
    const word& name,
    const objectRegistry& obr,
    const dictionary& dict
)
:
    functionObject(name),
    time_(obr.time()),
    obr_(obr)
{}