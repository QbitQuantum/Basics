private func DoDirControl(int iDir)
  {
  // Abbruch, wenn das Zielobjekt weg ist
  if (!pTargetObject) return(Abort());
  // Richtungsänderung?
  if (iDir != GetDir(pTargetObject))
    {
    iAngle=-iAngle;
    pTargetObject->SetDir(iDir);
    pArrow->UpdateAngle(iAngle);
    pTargetObject->~AimingAngle(iAngle);
    }
  else
    // Tastendruck in Zielrichtung: Zaubern! - nicht bei tumble!
    if(!(GetAction(pTargetObject) S= "Tumble"))
     DoEnter();
  return(1);
  }