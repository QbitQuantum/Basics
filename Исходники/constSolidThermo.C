Foam::constSolidThermo::constSolidThermo
(
    const fvMesh& mesh,
    const dictionary& dict
)
:
    basicSolidThermo(mesh, dict),
    dict_(dict.subDict(typeName + "Coeffs")),
    constK_(dimensionedScalar(dict_.lookup("K"))),
    K_
    (
        IOobject
        (
            "K",
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        constK_
    ),
    constRho_(dimensionedScalar(dict_.lookup("rho"))),
    constCp_(dimensionedScalar(dict_.lookup("Cp"))),
    constHf_(dimensionedScalar(dict_.lookup("Hf"))),
    constEmissivity_(dimensionedScalar(dict_.lookup("emissivity"))),
    constKappa_(dimensionedScalar(dict_.lookup("kappa"))),
    constSigmaS_(dimensionedScalar(dict_.lookup("sigmaS")))
{
    read();

    K_ = constK_;

    rho_ = constRho_;

    emissivity_ = constEmissivity_;

    kappa_ = constKappa_;

    sigmaS_ = constSigmaS_;
}