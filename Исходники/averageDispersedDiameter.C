Foam::tmp<Foam::volScalarField> Foam::diameterModels::ADD::tauC() const
{
    //- Phase fraction
    const volScalarField& alpha = phase_;
    //- Turbulent kinetic energy
    const volScalarField& k = phase_.turbulence().k();

    return
    Cc_*
    (
        cbrt
        (
            constant::mathematical::pi/6.0
           *(alphaMax_ - alpha)/
            max(alpha,SMALL)
        )
       *d_/sqrt(2.0/3.0*k)
    );
}