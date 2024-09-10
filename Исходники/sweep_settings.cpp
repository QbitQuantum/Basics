// Preset Load
bool SweepSettings::Load(QSettings &s)
{
    mode = (OperationalMode)(s.value("Mode", (int)Mode()).toInt());

    start = s.value("Sweep/Start", Start().Val()).toDouble();
    stop = s.value("Sweep/Stop", Stop().Val()).toDouble();
    center = s.value("Sweep/Center", Center().Val()).toDouble();
    span = s.value("Sweep/Span", Span().Val()).toDouble();
    step = s.value("Sweep/Step", Step().Val()).toDouble();
    rbw = s.value("Sweep/RBW", RBW().Val()).toDouble();
    vbw = s.value("Sweep/VBW", VBW().Val()).toDouble();

    auto_rbw = s.value("Sweep/AutoRBW", AutoRBW()).toBool();
    auto_vbw = s.value("Sweep/AutoVBW", AutoVBW()).toBool();
    native_rbw = s.value("Sweep/NativeRBW", NativeRBW()).toBool();

    refLevel.Load(s, "Sweep/RefLevel");
    div = s.value("Sweep/Division", Div()).toDouble();
    attenuation = s.value("Sweep/Attenuation", Atten()).toInt();
    gain = s.value("Sweep/Gain", Gain()).toInt();
    preamp = s.value("Sweep/Preamp", Preamp()).toInt();

    sweepTime = s.value("Sweep/SweepTime", SweepTime().Val()).toDouble();
    processingUnits = s.value("Sweep/ProcessingUnits", ProcessingUnits()).toInt();
    detector = s.value("Sweep/Detector", Detector()).toInt();
    rejection = s.value("Sweep/Rejection", Rejection()).toBool();

    tgSweepSize = s.value("Sweep/TgSweepSize", tgSweepSize).toInt();
    tgHighRangeSweep = s.value("Sweep/TgHighRangeSweep", tgHighRangeSweep).toBool();
    tgPassiveDevice = s.value("Sweep/TgPassiveDevice", tgPassiveDevice).toBool();

    UpdateProgram();
    return true;
}