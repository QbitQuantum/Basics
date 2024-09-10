thermalModel::thermalModel(const volScalarField& T)
    :
    IOdictionary
    (
       IOobject
       (
           "thermalProperties",
           T.time().constant(),
           T.db(),
           IOobject::MUST_READ,
           IOobject::NO_WRITE
       )
    ),
    T_(T),
    lawPtr_(thermalLaw::New("law", T_, subDict("thermal")))
{}