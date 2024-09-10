// Construct from components
Foam::multiHoleInjector::multiHoleInjector
(
    const Foam::Time& t,
    const Foam::dictionary& dict
)
:
    injectorType(t, dict),
    propsDict_(dict.subDict(typeName + "Props")),
    centerPosition_(propsDict_.lookup("position")),
    xyAngle_(readScalar(propsDict_.lookup("xyAngle"))),
    zAngle_(readScalar(propsDict_.lookup("zAngle"))),
    nHoles_(readLabel(propsDict_.lookup("nHoles"))),
    umbrellaAngle_(readScalar(propsDict_.lookup("umbrellaAngle"))),
    nozzleTipDiameter_(readScalar(propsDict_.lookup("nozzleTipDiameter"))),
    angleSpacing_(propsDict_.lookup("angleSpacing")),
    d_(readScalar(propsDict_.lookup("diameter"))),
    Cd_(readScalar(propsDict_.lookup("Cd"))),
    mass_(readScalar(propsDict_.lookup("mass"))),
    nParcels_(readLabel(propsDict_.lookup("nParcels"))),
    X_(propsDict_.lookup("X")),
    massFlowRateProfile_(propsDict_.lookup("massFlowRateProfile")),
    velocityProfile_(massFlowRateProfile_),
    injectionPressureProfile_(massFlowRateProfile_),
    CdProfile_(massFlowRateProfile_),
    TProfile_(propsDict_.lookup("temperatureProfile")),
    averageParcelMass_(nHoles_*mass_/nParcels_),
    direction_(nHoles_),
    position_(nHoles_),
    pressureIndependentVelocity_(true),
    tangentialInjectionVector1_(nHoles_),
    tangentialInjectionVector2_(nHoles_)
{


    // check if time entries for soi and eoi match
    if (mag(massFlowRateProfile_[0][0]-TProfile_[0][0]) > SMALL)
    {
        FatalError << "multiHoleInjector::multiHoleInjector(const time& t, const dictionary dict) " << endl
            << " start-times do not match for TemperatureProfile and massFlowRateProfile."
            << abort(FatalError);
    }

    if (mag(massFlowRateProfile_[massFlowRateProfile_.size()-1][0]-TProfile_[TProfile_.size()-1][0]) > SMALL)
    {
        FatalError << "multiHoleInjector::multiHoleInjector(const time& t, const dictionary dict) " << endl
            << " end-times do not match for TemperatureProfile and massFlowRateProfile."
            << abort(FatalError);
    }

    // convert CA to real time
    forAll(massFlowRateProfile_, i)
    {
        massFlowRateProfile_[i][0] = t.userTimeToTime(massFlowRateProfile_[i][0]);
        velocityProfile_[i][0] = massFlowRateProfile_[i][0];
        injectionPressureProfile_[i][0] = massFlowRateProfile_[i][0];
    }