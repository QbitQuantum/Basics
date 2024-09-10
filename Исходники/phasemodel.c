Foam::phaseModel::phaseModel
(
    const fvMesh& mesh,
    const dictionary& transportProperties,
    const word& phaseName
)
:
    dict_
    (
        transportProperties.subDict("phase" + phaseName)
    ),
    name_(phaseName),
    d_
    (
        dict_.lookup("d")
    ),
    nu_
    (
        dict_.lookup("nu")
    ),
    rho_
    (
        dict_.lookup("rho")
    ),
    U_
    (
        IOobject
        (
            "U" + phaseName,
            mesh.time().timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    )
{
    const word phiName = "phi" + phaseName;

    IOobject phiHeader
    (
        phiName,
        mesh.time().timeName(),
        mesh,
        IOobject::NO_READ
    );

    if (phiHeader.headerOk())
    {
        Info<< "Reading face flux field " << phiName << endl;

        phiPtr_.reset
        (
            new surfaceScalarField
            (
                IOobject
                (
                    phiName,
                    mesh.time().timeName(),
                    mesh,
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                mesh
            )
        );
    }
    else
    {
        Info<< "Calculating face flux field " << phiName << endl;

        wordList phiTypes
        (
            U_.boundaryField().size(),
            calculatedFvPatchScalarField::typeName
        );

        for (label i=0; i<U_.boundaryField().size(); i++)
        {
            if (isType<fixedValueFvPatchVectorField>(U_.boundaryField()[i]))
            {
                phiTypes[i] = fixedValueFvPatchScalarField::typeName;
            }
        }

        phiPtr_.reset
        (
            new surfaceScalarField
            (
                IOobject
                (
                    phiName,
                    mesh.time().timeName(),
                    mesh,
                    IOobject::NO_READ,
                    IOobject::AUTO_WRITE
                ),
                fvc::interpolate(U_) & mesh.Sf(),
                phiTypes
            )
        );
    }
}