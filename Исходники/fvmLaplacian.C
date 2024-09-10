tmp<fvMatrix<Type> >
laplacian
(
    GeometricField<Type, fvPatchField, volMesh>& vf
)
{
    surfaceScalarField Gamma
    (
        IOobject
        (
            "1",
            vf.time().constant(),
            vf.mesh(),
            IOobject::NO_READ
        ),
        vf.mesh(),
        dimensionedScalar("1", dimless, 1.0)
    );

    return fvm::laplacian
    (
        Gamma,
        vf,
        "laplacian(" + vf.name() + ')'
    );
}