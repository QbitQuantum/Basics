void 
SoXipOverlayTransformBoxManip::rotate( SoHandleEventAction* action )
{
	SbVec3f projPt;
	getPoint( action, projPt );
	
	const SbVec3f* point = mControlPointsCoords->point.getValues(0);

	SbVec3f center = (point[0] + point[4]) / 2.;

	SbVec3f rotateFrom	= point[mControlPointId] - center;
	SbVec3f rotateTo	= projPt - center;

	SbVec3f normal = mViewVolume.getPlane(0).getNormal();
	
	SbRotation rotation;
	rotation.setValue( normal, angleBetweenVectors( rotateFrom, rotateTo, normal ) );
	
	SbMatrix centerMatrix;
	centerMatrix.setTranslate( center );

	SbMatrix rotationMatrix;
	rotationMatrix.setRotate( rotation );

	mTransformationMatrix = centerMatrix.inverse() * rotationMatrix * centerMatrix;
	transform( mActionNode );
}