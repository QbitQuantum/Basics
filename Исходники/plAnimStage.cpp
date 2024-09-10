void plAnimStage::ResetAtTime(double globalTime, float localTime, plArmatureMod *avMod)
{
    SetLocalTime(localTime, true);
    avMod->GetRootAnimator()->Reset(globalTime);
}