  // Construct from components
  IncompressibleCloud::IncompressibleCloud(
					   const volPointInterpolation& vpi,
					   const volVectorField& U
					   )
    :
    Cloud<HardBallParticle>(U.mesh()),
    runTime_(U.time()),
    time0_(runTime_.value()),
    mesh_(U.mesh()),
    volPointInterpolation_(vpi),
    U_(U),
    smoment_(mesh_.nCells(), vector::zero),
    random(666),
    cloudProperties_
    (
     IOobject
     (
      "cloudProperties",
      U.time().constant(),
      U.db(),
      IOobject::MUST_READ,
      IOobject::NO_WRITE
      )
     ),
    interpolationSchemes_(cloudProperties_.subDict("interpolationSchemes"))
  {
    g_=cloudProperties_.lookup("g");
    HardBallParticle::density=readScalar(cloudProperties_.lookup("density"));
    dragCoefficient_=readScalar(cloudProperties_.lookup("drag"));
    subCycles_=readScalar(cloudProperties_.lookup("subCycles"));
    useSourceMoment=readBool(cloudProperties_.lookup("useMomentumSource"));

    dictionary injection(cloudProperties_.subDict("injection"));
    thres=readScalar(injection.lookup("thres"));
    center=injection.lookup("center");
    r0=readScalar(injection.lookup("r0"));
    vel0=readScalar(injection.lookup("vel0"));
    vel1=injection.lookup("vel1");
    d0=readScalar(injection.lookup("d0"));
    d1=readScalar(injection.lookup("d1"));
    tStart=readScalar(injection.lookup("tStart"));
    tEnd=readScalar(injection.lookup("tEnd"));

    dictionary wall(cloudProperties_.subDict("wall"));
    wallReflect_=readBool(wall.lookup("reflect"));
    if(wallReflect_) {
      wallElasticity_=readScalar(wall.lookup("elasticity"));
    }
  }