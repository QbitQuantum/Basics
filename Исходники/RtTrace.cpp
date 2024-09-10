traceResult_t RtTrace::Trace_Exhaustive( const Vector3f & start, const Vector3f & end ) const
{
	traceResult_t result;
	result.triangleIndex = -1;
	result.fraction = 1.0f;
	result.uv = Vector2f( 0.0f );
	result.normal = Vector3f( 0.0f );

	const Vector3f rayDelta = end - start;
	const float rayLengthSqr = rayDelta.LengthSq();
	const float rayLengthRcp = RcpSqrt( rayLengthSqr );
	const float rayLength = rayLengthSqr * rayLengthRcp;
	const Vector3f rayStart = start;
	const Vector3f rayDir = rayDelta * rayLengthRcp;

	float bestDistance = rayLength;
	Vector2f uv;

	for ( int i = 0; i < header.numIndices; i += 3 )
	{
		float distance;
		float u;
		float v;

		if ( RtIntersect::RayTriangle( rayStart, rayDir,
									vertices[indices[i + 0]],
									vertices[indices[i + 1]],
									vertices[indices[i + 2]], distance, u, v ) )
		{
			if ( distance >= 0.0f && distance < bestDistance )
			{
				bestDistance = distance;

				result.triangleIndex = i;
				uv.x = u;
				uv.y = v;
			}
		}
	}

	if ( result.triangleIndex != -1 )
	{
		result.fraction = bestDistance * rayLengthRcp;
		result.uv = uvs[indices[result.triangleIndex + 0]] * ( 1.0f - uv.x - uv.y ) +
					uvs[indices[result.triangleIndex + 1]] * uv.x +
					uvs[indices[result.triangleIndex + 2]] * uv.y;
		const Vector3f d1 = vertices[indices[result.triangleIndex + 1]] - vertices[indices[result.triangleIndex + 0]];
		const Vector3f d2 = vertices[indices[result.triangleIndex + 2]] - vertices[indices[result.triangleIndex + 0]];
		result.normal = d1.Cross( d2 ).Normalized();
	}

	return result;
}