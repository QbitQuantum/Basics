Foam::autoPtr<Foam::radiation::radiationModel>
Foam::radiation::radiationModel::New
(
    const volScalarField& T
)
{
    IOobject radIO
    (
        "radiationProperties",
        T.time().constant(),
        T.mesh(),
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE,
        false
    );

    word modelType("none");
    if (radIO.typeHeaderOk<IOdictionary>(false))
    {
        IOdictionary(radIO).lookup("radiationModel") >> modelType;
    }