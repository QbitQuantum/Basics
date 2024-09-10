//
//#############################################################################
//#############################################################################
//
UnitQuaternion&
	UnitQuaternion::Subtract(
		const UnitVector3D &end,
		const UnitVector3D &start
	)
{
	Check_Pointer(this);
	Check_Object(&start);
	Check_Object(&end);

	Vector3D
		axis;
	SinCosPair
		delta;
	delta.cosine = start*end;

	//
	//----------------------------------------------------------------------
	// See if the vectors point in the same direction.  If so, return a null
	// rotation
	//----------------------------------------------------------------------
	//
	if (Close_Enough(delta.cosine, 1.0f))
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 1.0f;
	}

	//
	//-------------------------------------------------------------------------
	// See if the vectors directly oppose each other.  If so, pick the smallest
	// axis coordinate and generate a vector along it.  Project this onto the
	// base vector and subtract it out, leaving a perpendicular projection.
	// Extend that out to unit length, then set the angle to PI
	//-------------------------------------------------------------------------
	//
	else if (Close_Enough(delta.cosine, -1.0f))
	{
		//
		//---------------------------
		// Pick out the smallest axis
		//---------------------------
		//
		int
			smallest=0;
		Scalar
			value=2.0f;
		for (int i=X_Axis; i<=Z_Axis; ++i)
		{
			if (Abs(start[i]) < value)
			{
				smallest = i;
				value = Abs(start[i]);
			}
		}

		//
		//----------------------------------------
		// Set up a vector along the selected axis
		//----------------------------------------
		//
		axis.x = 0.0f;
		axis.y = 0.0f;
		axis.z = 0.0f;
		axis[smallest] = 1.0f;

		//
		//-------------------------------------------------------------------
		// If the value on that axis wasn't zero, subtract out the projection
		//-------------------------------------------------------------------
		//
		if (!Small_Enough(value))
		{
			Vector3D t;
			t.Multiply(start, start*axis);
			axis.Subtract(axis, t);
			axis.Normalize(axis);
		}

		//
		//----------------------
		// Convert to quaternion
		//----------------------
		//
		x = axis.x;
		y = axis.y;
		z = axis.z;
		w = 0.0f;
	}

	//
	//--------------------------------------------------
	// Otherwise, generate the cross product and unitize
	//--------------------------------------------------
	//
	else
	{
		axis.Cross(start, end);
		delta.sine = axis.GetLength();
		axis /= delta.sine;

		//
		//---------------------------------------------------------------
		// Now compute sine and cosine of half the angle and generate the
		// quaternion
		//---------------------------------------------------------------
		//
		delta.sine = Sqrt((1.0f - delta.cosine)*0.5f);
		x = axis.x * delta.sine;
		y = axis.y * delta.sine;
		z = axis.z * delta.sine;
		w = Sqrt((1.0f + delta.cosine)*0.5f);
	}
	return *this;
}