void TrackerLinearFresnel::Evaluate( Vector3D sunVectorW, Transform parentWT0 )
{
	Vector3D i = parentWT0( sunVectorW );

	Vector3D localAxis;
	Point3D focusPoint;
	if( activeAxis.getValue() == 0 )
	{
		localAxis  =  Vector3D( 1.0, 0.0, 0.0 ) ;
		focusPoint = Point3D( 0.0, axisOrigin.getValue()[0], axisOrigin.getValue()[1] ) ;
	}
	else if( activeAxis.getValue() == 1 )
	{
		localAxis =  Vector3D( 0.0, 1.0, 0.0 );
		focusPoint = Point3D( axisOrigin.getValue()[0], 0.0, axisOrigin.getValue()[1] ) ;
	}
	else
	{
		localAxis  = Vector3D( 0.0, 0.0, 1.0 ) ;
		focusPoint = Point3D( axisOrigin.getValue()[0], axisOrigin.getValue()[1], 0.0 ) ;
	}

	Vector3D focus = Vector3D( focusPoint );
	if (typeOfAimingPoint.getValue() == 0 ) //Absolute
	{
		localAxis  = parentWT0( localAxis );
		focus = Vector3D( parentWT0( focusPoint ) );
	}


	double angle = 0.0;
	//Dawann : in a Fresnel concentrator we use the project of the sun vector on the normal plan of the axis
	//it= the projection of the sun on the normal plan of the axis...
	if( localAxis == Vector3D( 1.0, 0.0, 0.0 ) )
	{
		Vector3D r = Normalize( Vector3D( 0.0, focus.y, focus.z ) );
		Vector3D it = Normalize( Vector3D( 0.0, i.y, i.z ) );
		Vector3D n = Normalize( it + r );
		if( fabs( n.z ) > 0.0  )	angle = atan2( n.z, n.y );
	}
	else if( localAxis == Vector3D( 0.0, 1.0, 0.0 ) )
	{
		Vector3D r = Normalize( Vector3D( focus.x, 0.0, focus.z ) );
		Vector3D it = Normalize( Vector3D( i.x, 0.0, i.z ) );
		Vector3D n = Normalize( it + r );
		if( fabs( n.z ) > 0.0  )	angle = - atan2( n.z, n.x );
	}
	else
	{
		Vector3D r = Normalize( Vector3D( focus.x, focus.y, 0.0 ) );
		Vector3D it = Normalize( Vector3D( i.x, i.y, 0.0 ) );
		Vector3D n = Normalize( it + r );
		if( fabs( n.x ) > 0.0  )	angle = -atan2( n.x, n.y );
	}

	SbVec3f axis = SbVec3f( localAxis.x, localAxis.y, localAxis.z );

	SoTransform* newTransform = new SoTransform();
	newTransform->rotation.setValue( axis, angle );

	SetEngineOutput(newTransform);
}