MStatus SwirlDeformer::deform( MDataBlock& block, MItGeometry &iter,
												const MMatrix &localToWorld, unsigned int geomIndex )
{
MStatus stat;
	
MDataHandle envData = block.inputValue( envelope );
float env = envData.asFloat();	
if( env == 0.0 ) // Deformer has no effect
	return MS::kSuccess;

MDataHandle matData = block.inputValue( deformSpace );
MMatrix mat = matData.asMatrix();
MMatrix invMat = mat.inverse();

MDataHandle startDistHnd = block.inputValue( startDist );
double startDist = startDistHnd.asDouble();	

MDataHandle endDistHnd = block.inputValue( endDist );
double endDist = endDistHnd.asDouble();	

MPoint pt;
float weight;
double dist;
double ang;
double cosAng;
double sinAng;
double x;
double distFactor;
for( iter.reset(); !iter.isDone(); iter.next() ) 
	{
	weight = weightValue( block, geomIndex, iter.index() );
	if( weight == 0.0f )
		continue;

	pt = iter.position();
	pt *= invMat;

	dist = sqrt( pt.x * pt.x + pt.z * pt.z );
	if( dist < startDist || dist > endDist )
		continue;

	distFactor = 1 - ((dist - startDist) / (endDist - startDist));

	ang = distFactor * M_PI * 2.0 * env * weight;
	if( ang == 0.0 )
		continue;

	cosAng = cos( ang );
	sinAng = sin( ang );
	x = pt.x * cosAng - pt.z * sinAng;
	pt.z = pt.x * sinAng + pt.z * cosAng;
	pt.x = x;

	pt *= mat;
	
	iter.setPosition( pt );
	}

return stat;
}