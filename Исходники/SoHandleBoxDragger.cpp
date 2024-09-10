/*! \COININTERNAL
  Called when dragger is selected (picked) by the user.
*/
void
SoHandleBoxDragger::dragStart(void)
{
  SoHandleBoxDragger_invalidate_surroundscale(this);

  static const char translatorname[] = "translator";
  static const char extrudername[] = "extruder";
  static const char uniformname[] = "uniform";

  const SoPath *pickpath = this->getPickPath();

  SbBool found = FALSE;
  this->whatkind = WHATKIND_NONE;
  this->whatnum = 0;

  int i;
  SbString str;
  if (!found) {
    for (i = 1; i <= 6; i++) {
      str.sprintf("%s%d", translatorname, i);
      if (pickpath->findNode(this->getNodeFieldNode(str.getString())) >= 0||
          this->getSurrogatePartPickedName() == str.getString()) break;
    }
    if (i <= 6) {
      found = TRUE;
      this->whatkind = WHATKIND_TRANSLATOR;
      this->whatnum = i;
    }
  }

  if (!found) {
    for (i = 1; i <= 6; i++) {
      str.sprintf("%s%d", extrudername, i);
      if (pickpath->findNode(this->getNodeFieldNode(str.getString()))>= 0 ||
          this->getSurrogatePartPickedName() == str.getString()) break;
    }
    if (i <= 6) {
      found = TRUE;
      this->whatkind = WHATKIND_EXTRUDER;
      this->whatnum = i;
    }
  }
  if (!found) {
    for (i = 1; i <= 8; i++) {
      str.sprintf("%s%d", uniformname, i);
      if (pickpath->findNode(this->getNodeFieldNode(str.getString()))>= 0 ||
          this->getSurrogatePartPickedName() == str.getString()) break;
    }
    if (i <= 8) {
      found = TRUE;
      this->whatkind = WHATKIND_UNIFORM;
      this->whatnum = i;
    }
  }
  assert(found);
  if (!found) return;

  SbVec3f startPt = this->getLocalStartingPoint();

  switch(this->whatkind) {
  case WHATKIND_TRANSLATOR:
    {
      SbVec3f n;
      if (this->whatnum <= 2) {
        n = SbVec3f(0.0f, 1.0f, 0.0f);
      }
      else if (this->whatnum <= 4) {
        n = SbVec3f(1.0f, 0.0f, 0.0f);
      }
      else {
        n = SbVec3f(0.0f, 0.0f, 1.0f);
      }
      SbVec3f localPt;
      {
        SbMatrix mat, inv;
        this->getSurroundScaleMatrices(mat, inv);
        inv.multVecMatrix(startPt, localPt);
      }
      this->planeProj->setPlane(SbPlane(n, startPt));
      SbLine myline(SbVec3f(0.0f, 0.0f, 0.0f), n);
      SoTranslation *t = SO_GET_ANY_PART(this, "arrowTranslation", SoTranslation);
      t->translation = myline.getClosestPoint(localPt);
      if (this->getEvent()->wasShiftDown()) {
        this->getLocalToWorldMatrix().multVecMatrix(startPt, this->worldRestartPt);
        this->constraintState = CONSTRAINT_WAIT;
      }
    }
    break;
  case WHATKIND_EXTRUDER:
    this->lineProj->setLine(SbLine(this->getDraggerCenter(), startPt));
    this->ctrlOffset = this->calcCtrlOffset(startPt);
    break;
  case WHATKIND_UNIFORM:
    this->lineProj->setLine(SbLine(this->getDraggerCenter(), startPt));
    this->ctrlOffset = this->calcCtrlOffset(startPt);
    break;
  }
  this->ctrlDown = this->getEvent()->wasCtrlDown();
  this->updateSwitches();
}