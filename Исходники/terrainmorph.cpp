BridgeMorph::BridgeMorph( float width, float originX, float originY, float destX, float destY ) : TerrainMorph()
{
	float a = ( destX - originX );
	float b = ( destY - originY );
	float half = width / 2.0f;
	Vector3F at;
	bool inWater;
	Lilith3D* lilith = Lilith3D::Instance();

	float originH = lilith->GetTerrainMesh()->CalcHeight( originX, originY, &at, &inWater );
	float destH   = lilith->GetTerrainMesh()->CalcHeight( destX, destY, &at, &inWater );

	Vector3F widthNormal = { -b, a };
	widthNormal.Normalize();

	LineLoop loop;
	loop.AddAtEnd( new LineNode( originX + widthNormal.x*half, originY + widthNormal.y*half, originH ) );
	loop.AddAtEnd( new LineNode( originX - widthNormal.x*half, originY - widthNormal.y*half, originH ) );
	loop.AddAtEnd( new LineNode( destX - widthNormal.x*half,   destY - widthNormal.y*half, destH ) );
	loop.AddAtEnd( new LineNode( destX + widthNormal.x*half,   destY + widthNormal.y*half, destH ) );
	GenerateHeightMap( &loop, 1.0f, 1.0f, &maxDelta );
	startTime = Lilith3D::GetTimeClock()->Msec();
}