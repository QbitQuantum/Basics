// COMPUTE ======================================
MStatus gear_curveCns::deform( MDataBlock& data, MItGeometry& iter, const MMatrix &mat, unsigned int mIndex )
{
    MStatus returnStatus;

	MArrayDataHandle adh = data.inputArrayValue( inputs );
	int deformer_count = adh.elementCount( &returnStatus );

	// Process
	while (! iter.isDone()){
		if (iter.index() < deformer_count){
			adh.jumpToElement(iter.index());
			MTransformationMatrix m(adh.inputValue().asMatrix() * mat.inverse());
			MVector v = m.getTranslation(MSpace::kWorld, &returnStatus );
			MPoint pt(v);
			iter.setPosition(pt);
		}
		iter.next();
	}
 
    return MS::kSuccess;
}