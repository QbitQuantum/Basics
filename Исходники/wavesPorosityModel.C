Foam::wavesPorosityModel::wavesPorosityModel
(
	const fvMesh& mesh
)
:
    porosity_
    (
        IOobject
        (
            "porosity",
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedScalar("NULL", dimless, 1.0),
        "zeroGradient"
    )
{
}