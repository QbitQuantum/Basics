tmp<faMatrix<Type> >
laplacian
(
    GeometricField<Type, faPatchField, areaMesh>& vf
)
{
    edgeScalarField Gamma
    (
        IOobject
        (
            "gamma",
            vf.time().constant(),
            vf.db(),
            IOobject::NO_READ
        ),
        vf.mesh(),
        dimensionedScalar("1", dimless, 1.0)
    );

    return fam::laplacian(Gamma, vf);
}