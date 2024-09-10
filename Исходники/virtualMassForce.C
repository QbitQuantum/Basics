virtualMassForce::virtualMassForce
(
    const dictionary& multiphaseSurfaceForcesDict,
    const multiphase::transport& mtm,
    const PtrList<volScalarField>& alpha,
    const volScalarField& beta
)
:
	multiphaseSurfaceForcesDict_(multiphaseSurfaceForcesDict),
    alpha_(alpha),
    beta_(beta),
    mtm_(mtm),
    virtualMassForce_
	(
		IOobject
		(
			"virtualMassForce",
			beta.time().timeName(),
			beta.mesh(),
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
        beta.mesh(),
        dimensionedVector("zero", dimensionSet(0, 0, 0, 0, 0), vector(0.0, 0.0, 0.0))
    )
{}