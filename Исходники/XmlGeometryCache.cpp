MStatus
XmlCacheFormat::readDoubleVectorArray( MVectorArray& array, unsigned arraySize )
{
	MStringArray value;
	if( !readXmlTagValue(doubleVectorArrayTag, value) )
	{
		return MS::kFailure;
	}

	assert( value.length() == arraySize * 3 );
	array.setLength( arraySize );
	for (unsigned i = 0; i < arraySize; i++ )
	{
		double v[3];
		v[0] = strtod( value[i*3].asChar(), NULL );
		v[1] = strtod( value[i*3+1].asChar(), NULL );
		v[2] = strtod( value[i*3+2].asChar(), NULL );

		array.set( v, i );
	}
	
	return MS::kSuccess;
}