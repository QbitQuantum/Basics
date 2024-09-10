// Construct from components
Foam::spray::spray
(
    const volVectorField& U,
    const volScalarField& rho,
    const volScalarField& p,
    const volScalarField& T,
    const basicMultiComponentMixture& composition,
    const PtrList<gasThermoPhysics>& gasProperties,
    const dictionary&,
    const dimensionedVector& g,
    bool readFields
)
:
    Cloud<parcel>(U.mesh(), false), // suppress className checking on positions
    runTime_(U.time()),
    time0_(runTime_.value()),
    mesh_(U.mesh()),
    rndGen_(label(0)),
    g_(g.value()),

    U_(U),
    rho_(rho),
    p_(p),
    T_(T),

    sprayProperties_
    (
        IOobject
        (
            "sprayProperties",
            U.time().constant(),
            U.db(),
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    ),

    ambientPressure_(p_.average().value()),
    ambientTemperature_(T_.average().value()),

    injectors_
    (
        IOobject
        (
            "injectorProperties",
            U.time().constant(),
            U.db(),
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        ),
        injector::iNew(U.time())
    ),
    atomization_
    (
        atomizationModel::New
        (
            sprayProperties_,
            *this
        )
    ),
    drag_
    (
        dragModel::New
        (
            sprayProperties_
        )
    ),
    evaporation_
    (
        evaporationModel::New
        (
            sprayProperties_
        )
    ),
    heatTransfer_
    (
        heatTransferModel::New
        (
            sprayProperties_
        )
    ),
    wall_
    (
        wallModel::New
        (
            sprayProperties_,
            U,
            *this
        )
    ),
    breakupModel_
    (
        breakupModel::New
        (
            sprayProperties_,
            *this
        )
    ),
    collisionModel_
    (
        collisionModel::New
        (
            sprayProperties_,
            *this,
            rndGen_
        )
    ),
    dispersionModel_
    (
        dispersionModel::New
        (
            sprayProperties_,
            *this
        )
    ),

    fuels_
    (
        liquidMixture::New
        (
            mesh_.lookupObject<dictionary>("thermophysicalProperties")
        )
    ),
    injectorModel_
    (
        injectorModel::New
        (
            sprayProperties_,
            *this
        )
    ),

    sprayIteration_(sprayProperties_.subDict("sprayIteration")),
    sprayIterate_(readLabel(sprayIteration_.lookup("sprayIterate"))),
    sprayRelaxFactor_(readScalar(sprayIteration_.lookup("sprayRelaxFactor"))),
    minimumParcelMass_
    (
        readScalar(sprayIteration_.lookup("minimumParcelMass"))
    ),

    subCycles_(readLabel(sprayProperties_.lookup("subCycles"))),

    gasProperties_(gasProperties),
    composition_(composition),

    liquidToGasIndex_(fuels_->components().size(), -1),
    gasToLiquidIndex_(composition.Y().size(), -1),
    isLiquidFuel_(composition.Y().size(), false),

    twoD_(0),
    axisOfSymmetry_(vector::zero),
    axisOfWedge_(vector(0,0,0)),
    axisOfWedgeNormal_(vector(0,0,0)),
    angleOfWedge_(0.0),

    interpolationSchemes_(sprayProperties_.subDict("interpolationSchemes")),
    UInterpolator_(NULL),
    rhoInterpolator_(NULL),
    pInterpolator_(NULL),
    TInterpolator_(NULL),

    sms_(mesh_.nCells(), vector::zero),
    shs_(mesh_.nCells(), 0.0),
    srhos_(fuels_->components().size()),

    totalInjectedLiquidMass_(0.0),
    injectedLiquidKE_(0.0)

{
    // create the evaporation source fields
    forAll(srhos_, i)
    {
        srhos_.set(i, new scalarField(mesh_.nCells(), 0.0));
    }