tmp<tetFemMatrix<Type> > tetFem::laplacian
(
    GeometricField<Type, tetPolyPatchField, tetPointMesh>& vf
)
{
    elementScalarField Gamma
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

    return tetFem::laplacian(Gamma, vf);
}