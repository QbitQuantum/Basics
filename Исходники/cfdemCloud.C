// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
Foam::cfdemCloud::cfdemCloud
(
    const fvMesh& mesh
)
:
    mesh_(mesh),
    couplingProperties_
    (
        IOobject
        (
            "couplingProperties",
            mesh_.time().constant(),
            mesh_,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    ),
    liggghtsCommandDict_
    (
        IOobject
        (
            "liggghtsCommands",
            mesh_.time().constant(),
            mesh_,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    ),
    verbose_(false),
    ignore_(false),
    modelType_(couplingProperties_.lookup("modelType")),
    positions_(NULL),
    velocities_(NULL),
    fluidVel_(NULL),
    impForces_(NULL),
    expForces_(NULL),
    DEMForces_(NULL),
    Cds_(NULL),
    radii_(NULL),
    voidfractions_(NULL),
    cellIDs_(NULL),
    particleWeights_(NULL),
    particleVolumes_(NULL),
    numberOfParticles_(0),
    numberOfParticlesChanged_(false),
    arraysReallocated_(false),
    forceModels_(couplingProperties_.lookup("forceModels")),
    momCoupleModels_(couplingProperties_.lookup("momCoupleModels")),
    liggghtsCommandModelList_(liggghtsCommandDict_.lookup("liggghtsCommandModels")),
    turbulenceModelType_(couplingProperties_.lookup("turbulenceModelType")),
    cgOK_(true),
    impDEMdrag_(false),
    useDDTvoidfraction_(false),
    ddtVoidfraction_
    (   
        IOobject
        (
            "ddtVoidfraction",
            mesh.time().timeName(),
            mesh,
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        mesh,
        dimensionedScalar("zero", dimensionSet(0,0,-1,0,0), 0)  // 1/s
    ),
    turbulence_
    (
        #if defined(version21) || defined(version16ext)
            #ifdef comp
                mesh.lookupObject<compressible::turbulenceModel>
            #else
                mesh.lookupObject<incompressible::turbulenceModel>
            #endif
        #elif defined(version15)
            mesh.lookupObject<incompressible::RASModel>
        #endif
        (
            turbulenceModelType_
        )
    ),
    locateModel_
    (
        locateModel::New
        (
            couplingProperties_,
            *this
        )
    ),
    /*momCoupleModel_
    (
        momCoupleModel::New
        (
            couplingProperties_,
            *this
        )
    ),*/
    dataExchangeModel_
    (
        dataExchangeModel::New
        (
            couplingProperties_,
            *this
        )
    ),
    IOModel_
    (
        IOModel::New
        (
            couplingProperties_,
            *this
        )
    ),
    probeModel_
    (
        probeModel::New
        (
            couplingProperties_,
            *this,
            "none",
            "none"
        )
    ),
    voidFractionModel_
    (
        voidFractionModel::New
        (
            couplingProperties_,
            *this
        )
    ),
    averagingModel_
    (
        averagingModel::New
        (
            couplingProperties_,
            *this
        )
    ),
    clockModel_
    (
        clockModel::New
        (
            couplingProperties_,
            *this
        )
    ),
    smoothingModel_
    (
        smoothingModel::New
        (
            couplingProperties_,
            *this
        )
    ),
    meshMotionModel_
    (
        meshMotionModel::New
        (
            couplingProperties_,
            *this
        )
    )
{
    #include "versionInfo.H"

    Info << "If BC are important, please provide volScalarFields -imp/expParticleForces-" << endl;

    if (couplingProperties_.found("verbose")) verbose_=true;
    if (couplingProperties_.found("ignore")) ignore_=true;
    if (turbulenceModelType_=="LESProperties")
        Info << "WARNING - LES functionality not yet tested!" << endl;

    if (couplingProperties_.found("useDDTvoidfraction"))
        useDDTvoidfraction_=true;
    else        
        Info << "ignoring ddt(voidfraction)" << endl;

    forceModel_ = new autoPtr<forceModel>[nrForceModels()];
    for (int i=0;i<nrForceModels();i++)
    {
        forceModel_[i] = forceModel::New
        (
            couplingProperties_,
            *this,
            forceModels_[i]
        );
    }

    momCoupleModel_ = new autoPtr<momCoupleModel>[momCoupleModels_.size()];
    for (int i=0;i<momCoupleModels_.size();i++)
    {
        momCoupleModel_[i] = momCoupleModel::New
        (
            couplingProperties_,
            *this,
            momCoupleModels_[i]
        );
    }

    // run liggghts commands from cfdem
    liggghtsCommand_ = new autoPtr<liggghtsCommandModel>[liggghtsCommandModelList_.size()];
    for (int i=0;i<liggghtsCommandModelList_.size();i++)
    {
        liggghtsCommand_[i] = liggghtsCommandModel::New
        (
            liggghtsCommandDict_,
            *this,
            liggghtsCommandModelList_[i],
            i
        );
    }

    dataExchangeM().setCG();
    if (!cgOK_ && forceM(0).cg() > 1) FatalError<< "at least one of your models is not fit for cg !!!"<< abort(FatalError); 
}