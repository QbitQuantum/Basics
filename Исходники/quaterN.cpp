void quaterN::decomposeStitch(int discontinuity)
{
	quaterN rotY, offset;
	decompose(rotY, offset);
	rotY.c1stitch(discontinuity);
	offset.c1stitch(discontinuity);
	combine(rotY, offset);
}