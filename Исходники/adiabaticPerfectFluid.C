Foam::tmp<Foam::volScalarField>
Foam::phaseEquationsOfState::adiabaticPerfectFluid::psi
(
    const volScalarField& p,
    const volScalarField& T
) const
{
    return tmp<Foam::volScalarField>
           (
               new volScalarField
               (
                   IOobject
                   (
                       "psi",
                       p.time().timeName(),
                       p.mesh(),
                       IOobject::NO_READ,
                       IOobject::NO_WRITE,
                       false
                   ),
                   (rho0_/(gamma_*(p0_ + B_)))
                   *pow((p + B_)/(p0_ + B_), 1.0/gamma_ - 1.0)
               )
           );
}