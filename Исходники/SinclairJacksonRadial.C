Foam::tmp<Foam::volScalarField>
Foam::kineticTheoryModels::radialModels::SinclairJackson::g0prime
(
    const phaseModel& phase1,
 const phaseModel& phase2
) const
{
    volScalarField aByaMax
    (
        cbrt
        (
            min
            (
                max(phase1, scalar(1e-3)),
                alphaMinFriction_
            )/phase1.alphaMax()
        )
    );

    return (1.0/(3*phase1.alphaMax()))/sqr(aByaMax - sqr(aByaMax));
}