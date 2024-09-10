void FSkyVertexBuffer::SkyVertex(int r, int c, bool zflip)
{
	static const FAngle maxSideAngle = 60.f;
	static const float scale = 10000.;

	FAngle topAngle = (c / (float)mColumns * 360.f);
	FAngle sideAngle = maxSideAngle * (mRows - r) / mRows;
	float height = sideAngle.Sin();
	float realRadius = scale * sideAngle.Cos();
	FVector2 pos = topAngle.ToVector(realRadius);
	float z = (!zflip) ? scale * height : -scale * height;

	FSkyVertex vert;

	vert.color = r == 0 ? 0xffffff : 0xffffffff;

	// And the texture coordinates.
	if (!zflip)	// Flipped Y is for the lower hemisphere.
	{
		vert.u = (-c / (float)mColumns);
		vert.v = (r / (float)mRows);
	}
	else
	{
		vert.u = (-c / (float)mColumns);
		vert.v = 1.0f + ((mRows - r) / (float)mRows);
	}

	if (r != 4) z += 300;
	// And finally the vertex.
	vert.x = -pos.X;	// Doom mirrors the sky vertically!
	vert.y = z - 1.f;
	vert.z = pos.Y;

	mVertices.Push(vert);
}