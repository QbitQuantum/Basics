/*
 * Prepare for projecting.
 */
void CPerspectiveProjection3D::Prepare(void)
{
  FLOATmatrix3D t3dObjectStretch;   // matrix for object stretch
  FLOATmatrix3D t3dObjectRotation;  // matrix for object angles

  // calc. matrices for viewer and object angles and stretch
  MakeRotationMatrixFast(
    t3dObjectRotation, pr_ObjectPlacement.pl_OrientationAngle);
  MakeInverseRotationMatrixFast(
    pr_ViewerRotationMatrix, pr_ViewerPlacement.pl_OrientationAngle);
  t3dObjectStretch.Diagonal(pr_ObjectStretch);
  pr_vViewerPosition = pr_ViewerPlacement.pl_PositionVector;
  BOOL bXInverted = pr_ObjectStretch(1)<0;
  BOOL bYInverted = pr_ObjectStretch(2)<0;
  BOOL bZInverted = pr_ObjectStretch(3)<0;

  pr_bInverted = (bXInverted != bYInverted) != bZInverted;

  // if the projection is mirrored
  if (pr_bMirror) {
    // reflect viewer
    ReflectPositionVectorByPlane(pr_plMirror, pr_vViewerPosition);
    ReflectRotationMatrixByPlane_rows(pr_plMirror, pr_ViewerRotationMatrix);
    // get mirror plane in view space
    pr_plMirrorView = pr_plMirror;
    pr_plMirrorView -= pr_vViewerPosition;
    pr_plMirrorView *= pr_ViewerRotationMatrix;
    // invert inversion
    pr_bInverted = !pr_bInverted;
  } else if (pr_bWarp) {
    // get mirror plane in view space
    pr_plMirrorView = pr_plMirror;
  }

  // if the object is face-forward
  if (pr_bFaceForward) {
    // if it turns only heading
    if (pr_bHalfFaceForward) {
      // get the y-axis vector of object rotation
      FLOAT3D vY(t3dObjectRotation(1,2), t3dObjectRotation(2,2), t3dObjectRotation(3,2));
      // find z axis of viewer
      FLOAT3D vViewerZ(
        pr_ViewerRotationMatrix(3,1),
        pr_ViewerRotationMatrix(3,2),
        pr_ViewerRotationMatrix(3,3));
      // calculate x and z axis vectors to make object head towards viewer
      FLOAT3D vX = (-vViewerZ)*vY;
      vX.Normalize();
      FLOAT3D vZ = vY*vX;
      // compose the rotation matrix back from those angles
      t3dObjectRotation(1,1) = vX(1); t3dObjectRotation(1,2) = vY(1); t3dObjectRotation(1,3) = vZ(1);
      t3dObjectRotation(2,1) = vX(2); t3dObjectRotation(2,2) = vY(2); t3dObjectRotation(2,3) = vZ(2);
      t3dObjectRotation(3,1) = vX(3); t3dObjectRotation(3,2) = vY(3); t3dObjectRotation(3,3) = vZ(3);

      // first apply object stretch then object rotation and then viewer rotation
      pr_mDirectionRotation = pr_ViewerRotationMatrix*t3dObjectRotation;
      pr_RotationMatrix = pr_mDirectionRotation*t3dObjectStretch;
    // if it is fully face forward
    } else {
      // apply object stretch and banking only
      FLOATmatrix3D mBanking;
      MakeRotationMatrixFast(
        mBanking, ANGLE3D(0,0, pr_ObjectPlacement.pl_OrientationAngle(3)));
      pr_mDirectionRotation = mBanking;
      pr_RotationMatrix = mBanking*t3dObjectStretch;
    }
  } else {
    // first apply object stretch then object rotation and then viewer rotation
    pr_mDirectionRotation = pr_ViewerRotationMatrix*t3dObjectRotation;
    pr_RotationMatrix = pr_mDirectionRotation*t3dObjectStretch;
  }

  // calc. offset of object from viewer
  pr_TranslationVector = pr_ObjectPlacement.pl_PositionVector - pr_vViewerPosition;
  // rotate offset only by viewer angles
  pr_TranslationVector = pr_TranslationVector*pr_ViewerRotationMatrix;
  // transform handle from object space to viewer space and add it to the offset
  pr_TranslationVector -= pr_vObjectHandle*pr_RotationMatrix;

  FLOAT2D vMin, vMax;
  // if using a shadow projection
  if (ppr_fMetersPerPixel>0) {
    // caclulate factors
    FLOAT fFactor = ppr_fViewerDistance/ppr_fMetersPerPixel;
    ppr_PerspectiveRatios(1) = -fFactor;
    ppr_PerspectiveRatios(2) = -fFactor;
    pr_ScreenCenter = -pr_ScreenBBox.Min();

    vMin = pr_ScreenBBox.Min();
    vMax = pr_ScreenBBox.Max();
  // if using normal projection
  } else if (ppr_boxSubScreen.IsEmpty()) {
    // calculate perspective constants
    FLOAT2D v2dScreenSize = pr_ScreenBBox.Size();
    pr_ScreenCenter = pr_ScreenBBox.Center();
    /* calculate FOVHeight from FOVWidth by formula:
       halfanglej = atan( tan(halfanglei)*jsize*aspect/isize ) */
    ANGLE aHalfI = ppr_FOVWidth/2;
    ANGLE aHalfJ = ATan(TanFast(aHalfI)*v2dScreenSize(2)*pr_AspectRatio/v2dScreenSize(1));

    /* calc. perspective ratios by formulae:
       xratio = isize/(2*tan(anglei/2))
       yratio = jsize/(2*tan(anglej/2))
      sign is negative since viewer is looking down the -z axis
    */
    ppr_PerspectiveRatios(1) = -v2dScreenSize(1)/(2.0f*TanFast(aHalfI))*pr_fViewStretch;
    ppr_PerspectiveRatios(2) = -v2dScreenSize(2)/(2.0f*TanFast(aHalfJ))*pr_fViewStretch;

    vMin = pr_ScreenBBox.Min()-pr_ScreenCenter;
    vMax = pr_ScreenBBox.Max()-pr_ScreenCenter;
  // if using sub-drawport projection
  } else {
    // calculate perspective constants
    FLOAT2D v2dScreenSize = pr_ScreenBBox.Size();
    pr_ScreenCenter = pr_ScreenBBox.Center();
    /* calculate FOVHeight from FOVWidth by formula:
       halfanglej = atan( tan(halfanglei)*jsize*aspect/isize ) */
    ANGLE aHalfI = ppr_FOVWidth/2;
    ANGLE aHalfJ = ATan(TanFast(aHalfI)*v2dScreenSize(2)*pr_AspectRatio/v2dScreenSize(1));

    /* calc. perspective ratios by formulae:
       xratio = isize/(2*tan(anglei/2))
       yratio = jsize/(2*tan(anglej/2))
      sign is negative since viewer is looking down the -z axis
    */
    ppr_PerspectiveRatios(1) = -v2dScreenSize(1)/(2.0f*TanFast(aHalfI))*pr_fViewStretch;
    ppr_PerspectiveRatios(2) = -v2dScreenSize(2)/(2.0f*TanFast(aHalfJ))*pr_fViewStretch;

    vMin = ppr_boxSubScreen.Min()-pr_ScreenCenter;
    vMax = ppr_boxSubScreen.Max()-pr_ScreenCenter;

    pr_ScreenCenter -= ppr_boxSubScreen.Min();
  }
  // find factors for left, right, up and down clipping

  FLOAT fMinI = vMin(1); FLOAT fMinJ = vMin(2);
  FLOAT fMaxI = vMax(1); FLOAT fMaxJ = vMax(2);
  FLOAT fRatioX = ppr_PerspectiveRatios(1);
  FLOAT fRatioY = ppr_PerspectiveRatios(2);

#define MySgn(x) ((x)>=0?1:-1)

  FLOAT fDZ = -1.0f;
  FLOAT fDXL = fDZ*fMinI/fRatioX;
  FLOAT fDXR = fDZ*fMaxI/fRatioX;
  FLOAT fDYU = -fDZ*fMinJ/fRatioY;
  FLOAT fDYD = -fDZ*fMaxJ/fRatioY;

  FLOAT fNLX = -fDZ;
  FLOAT fNLZ = +fDXL;
  FLOAT fOoNL = 1.0f/(FLOAT)sqrt(fNLX*fNLX+fNLZ*fNLZ);
  fNLX*=fOoNL; fNLZ*=fOoNL;

  FLOAT fNRX = +fDZ;
  FLOAT fNRZ = -fDXR;
  FLOAT fOoNR = 1.0f/(FLOAT)sqrt(fNRX*fNRX+fNRZ*fNRZ);
  fNRX*=fOoNR; fNRZ*=fOoNR;

  FLOAT fNDY = -fDZ;
  FLOAT fNDZ = +fDYD;
  FLOAT fOoND = 1.0f/(FLOAT)sqrt(fNDY*fNDY+fNDZ*fNDZ);
  fNDY*=fOoND; fNDZ*=fOoND;

  FLOAT fNUY = +fDZ;
  FLOAT fNUZ = -fDYU;
  FLOAT fOoNU = 1.0f/(FLOAT)sqrt(fNUY*fNUY+fNUZ*fNUZ);
  fNUY*=fOoNU; fNUZ*=fOoNU;

  // make clip planes
  pr_plClipU = FLOATplane3D(FLOAT3D(   0,fNUY,fNUZ), 0.0f);
  pr_plClipD = FLOATplane3D(FLOAT3D(   0,fNDY,fNDZ), 0.0f);
  pr_plClipL = FLOATplane3D(FLOAT3D(fNLX,   0,fNLZ), 0.0f);
  pr_plClipR = FLOATplane3D(FLOAT3D(fNRX,   0,fNRZ), 0.0f);

  // mark as prepared
  pr_Prepared = TRUE;

  // calculate constant value used for calculating z-buffer k-value from vertex's z coordinate
  pr_fDepthBufferFactor = -pr_NearClipDistance;
  pr_fDepthBufferMul = pr_fDepthBufferFar-pr_fDepthBufferNear;
  pr_fDepthBufferAdd = pr_fDepthBufferNear;

  // calculate ratio for mip factor calculation
  ppr_fMipRatio = pr_ScreenBBox.Size()(1)/(ppr_PerspectiveRatios(1)*640.0f);
}