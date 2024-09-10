Foam::quadratureNode<weightType, abscissaType>::quadratureNode
(
    const word& name,
    const label nSecondaryNodes,
    const fvMesh& mesh,
    const dimensionSet& weightDimensions,
    const dimensionSet& abscissaDimensions
)
:
    name_(name),
    nSecondaryNodes_(nSecondaryNodes),
    primaryWeight_
    (
        IOobject
        (
            IOobject::groupName(name_, "primaryWeight"),
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedScalar("zeroWeight", weightDimensions, 0.0)
    ),
    primaryAbscissa_
    (
        IOobject
        (
            IOobject::groupName(name_, "primaryAbscissa"),
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedScalar("zeroAbscissa", abscissaDimensions, 0.0)
    ),
    secondaryWeights_(nSecondaryNodes_),
    secondaryAbscissae_(nSecondaryNodes_),
    sigma_
    (
        IOobject
        (
            IOobject::groupName(name_, "sigma"),
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::NO_WRITE
        ),
        mesh,
        dimensionedScalar("zeroSigma", dimless, 0.0)
    ),
    extended_(true)
{
    forAll(secondaryWeights_, nodeI)
    {
        secondaryWeights_.set
        (
            nodeI,
            new weightType
            (
                IOobject
                (
                    IOobject::groupName
                    (
                        name_,
                        "secondaryWeight." + Foam::name(nodeI)
                    ),
                    mesh.time().timeName(),
                    mesh,
                    IOobject::NO_READ,
                    IOobject::NO_WRITE
                ),
                mesh,
                dimensionedScalar("zeroWeight", dimless, 0.0)
            )
        );

        secondaryAbscissae_.set
        (
            nodeI,
            new abscissaType
            (
                IOobject
                (
                    IOobject::groupName
                    (
                        name_,
                        "secondaryAbscissa." + Foam::name(nodeI)
                    ),
                    mesh.time().timeName(),
                    mesh,
                    IOobject::NO_READ,
                    IOobject::NO_WRITE
                ),
                mesh,
                dimensionedScalar("zeroAbscissa", abscissaDimensions, 0.0)            
            )
        );
    }