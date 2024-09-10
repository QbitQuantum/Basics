inline Transform TCBSplineMultiply( const Transform& p1, const Transform& p2, const Transform& incoming_tangent, const Transform& outgoing_tangent, const Vector4& hS )
{
	Quaternion q = TCBSplineMultiply( p1.qRotation, p2.qRotation, incoming_tangent.qRotation, outgoing_tangent.qRotation, hS );
	q.Normalize();
	Vector3 t    = TCBSplineMultiply( p1.vTranslation, p2.vTranslation, incoming_tangent.vTranslation, outgoing_tangent.vTranslation, hS );

	return Transform( q, t );
}