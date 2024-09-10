Foam::tmp<Foam::volScalarField> Foam::consumptionSpeed::omega0Sigma
(
    const volScalarField& sigma
)
{
    tmp<volScalarField> tomega0
    (
        new volScalarField
        (
            IOobject
            (
                "omega0",
                sigma.time().timeName(),
                sigma.db(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            sigma.mesh(),
            dimensionedScalar
            (
                "omega0",
                dimensionSet(1, -2, -1, 0, 0, 0, 0),
                0
            )
        )
    );

    volScalarField& omega0 = tomega0();

    volScalarField::InternalField& iomega0 = omega0.internalField();

    forAll(iomega0, celli)
    {
        iomega0[celli] = omega0Sigma(sigma[celli], 1.0);
    }