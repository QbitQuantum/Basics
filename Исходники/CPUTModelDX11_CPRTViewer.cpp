bool CPUTModel_CPRT::IntersectFace(	const XMVECTOR &rayOrigin, const XMVECTOR &rayDirection,
					const XMVECTOR &vertexOne, const XMVECTOR &vertexTwo, const XMVECTOR &vertexThree,
					const XMVECTOR &vertexFour)
{
	for(int i = 0; i < 2; ++i)
	{
		XMVECTOR edge1 = (i==0) ? vertexOne-vertexTwo : vertexOne-vertexFour;
		XMVECTOR edge2 = (i==0) ? vertexThree-vertexTwo : vertexThree-vertexFour;

		XMVECTOR crossWithPickRay = XMVector3Cross(rayDirection, edge2);

		float otherEdgeProjection = XMVectorGetX( XMVector3Dot(edge1, crossWithPickRay) );

		XMVECTOR tvec = (otherEdgeProjection > 0) ? (i==0 ? rayOrigin - vertexTwo : rayOrigin - vertexFour) : (i==0 ? vertexTwo - rayOrigin : vertexFour - rayOrigin);
		otherEdgeProjection = (otherEdgeProjection > 0) ? otherEdgeProjection : - otherEdgeProjection;
		if(otherEdgeProjection < 0.0001f)
			continue;

		float u = XMVectorGetX( XMVector3Dot( tvec, crossWithPickRay ) );
		if( u < 0.0f || u > otherEdgeProjection )
			continue;

		XMVECTOR qvec = XMVector3Cross( tvec, edge1 );

		float v = XMVectorGetX( XMVector3Dot( rayDirection, qvec ) );
		if ( v < 0.0f || u + v > otherEdgeProjection )
			continue;
		return true;
	}
	return false;
}