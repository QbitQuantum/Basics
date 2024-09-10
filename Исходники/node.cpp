void Node::lookAt( const math::Vector3& target, const math::Vector3& up )
{
	assert( Math::abs(up.length()-1.f) < 1e-3f ); // Up direction must be normalized

	// src parent->world space
	Matrix4x4 parentToWorld = Matrix4x4(1);
	const Node* parent = this->parent();
	while ( parent )
	{
		parentToWorld = parent->transform() * parentToWorld;
		parent = parent->parent();
	}

	// src->world space
	Matrix4x4 sourceToWorld = parentToWorld * transform();

	// src -> target (world space)
	Vector3 sourceRotZ = target - sourceToWorld.translation();
	if ( sourceRotZ.lengthSquared() > Float::MIN_VALUE )
	{
		// src->target direction (world space)
		sourceRotZ = sourceRotZ.normalize();

		// src rotation (world space)
		Vector3 sourceRotX = up.cross( sourceRotZ );
		if ( sourceRotX.lengthSquared() > Float::MIN_VALUE )
			sourceRotX = sourceRotX.normalize();
		else
			sourceRotX = Vector3(1,0,0);
		Vector3 sourceRotY = sourceRotZ.cross( sourceRotX );
		Matrix3x3 sourceRot;
		sourceRot.setColumn( 0, sourceRotX );
		sourceRot.setColumn( 1, sourceRotY );
		sourceRot.setColumn( 2, sourceRotZ );

		// src world space rotation back to src parent space
		Matrix3x3 parentToWorldRot = parentToWorld.rotation();
		Matrix3x3 rot = sourceRot * parentToWorldRot.inverse();
		setRotation( rot );
	}
}