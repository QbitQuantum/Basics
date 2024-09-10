DMDModel<Type>::DMDModel
(
    const fvMesh& mesh,
    const word& DMDModelName
)
:
    IOdictionary
    (
        IOobject
        (
            "DMDProperties",
            mesh.time().constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE,
            false
        )
    ),
    mesh_(mesh),
    coeffDict_(subOrEmptyDict(DMDModelName + "Coeffs"))
{}