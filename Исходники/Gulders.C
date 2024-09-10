Foam::tmp<Foam::volScalarField> Foam::laminarFlameSpeedModels::Gulders::Su0pTphi
(
    const volScalarField& p,
    const volScalarField& Tu,
    scalar phi
) const
{
    tmp<volScalarField> tSu0
    (
        new volScalarField
        (
            IOobject
            (
                "Su0",
                p.time().timeName(),
                p.db(),
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            p.mesh(),
            dimensionedScalar("Su0", dimVelocity, 0.0)
        )
    );

    volScalarField& Su0 = tSu0();

    forAll(Su0, celli)
    {
        Su0[celli] = Su0pTphi(p[celli], Tu[celli], phi, 0.0);
    }