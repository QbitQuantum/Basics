bool vtTin::ReadADF(const char *fname, bool progress_callback(int))
{
	const vtString tnxy_name = fname;
	if (tnxy_name.Right(6) != "xy.adf")
		return false;

	vtString base = tnxy_name.Left(tnxy_name.GetLength()-6);
	vtString tnz_name = base + "z.adf";
	vtString tnod_name = base + "od.adf";

	FILE *fp1 = vtFileOpen(tnxy_name, "rb");
	FILE *fp2 = vtFileOpen(tnz_name, "rb");
	FILE *fp3 = vtFileOpen(tnod_name, "rb");
	if (!fp1 || !fp2 || !fp3)
		return false;

	fseek(fp1, 0, SEEK_END);
	const int length_xy = ftell(fp1);
	rewind(fp1);	// go back again
	uint num_points = length_xy / 16;	// X and Y, each 8 byte doubles

	fseek(fp2, 0, SEEK_END);
	const int length_z = ftell(fp2);
	rewind(fp2);	// go back again
	uint num_heights = length_z / 4;		// Z is a 4 byte float

	DPoint2 p;
	float z;
	for (uint i = 0; i < num_points; i++)
	{
		if ((i%200) == 0 && progress_callback != NULL)
			progress_callback(i * 40 / num_points);

		FRead(&p.x, DT_DOUBLE, 2, fp1, BO_BIG_ENDIAN, BO_LITTLE_ENDIAN);
		FRead(&z, DT_FLOAT, 1, fp2, BO_BIG_ENDIAN, BO_LITTLE_ENDIAN);
		AddVert(p, z);
	}

	fseek(fp3, 0, SEEK_END);
	const int length_od = ftell(fp3);
	rewind(fp3);	// go back again
	const uint num_faces = length_od / 12;		// A B C as 4-byte ints

	int v[3];
	for (uint i = 0; i < num_faces; i++)
	{
		if ((i%200) == 0 && progress_callback != NULL)
			progress_callback(40 + i * 40 / num_faces);

		FRead(v, DT_INT, 3, fp3, BO_BIG_ENDIAN, BO_LITTLE_ENDIAN);
		AddTri(v[0]-1, v[1]-1, v[2]-1);
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	// Cleanup: the ESRI TIN contains four "boundary" point far outside the
	//  extents (directly North, South, East, and West).  We should ignore
	//  those four points and the triangles connected to them.
	// It seems we can assume the four 'extra' vertices are the first four.
	m_vert.RemoveAt(0, 4);
	m_z.erase(m_z.begin(), m_z.begin() + 4);
	m_vert_normal.RemoveAt(0, 4);

	// Re-index the triangles
	uint total = m_tri.size()/3;
	for (uint i = 0; i < total; i++)
	{
		if ((i%200) == 0 && progress_callback != NULL)
			progress_callback(80 + i * 20 / total);

		// Remove any triangles which referenced this vertex
		if (m_tri[i*3 + 0] < 4 ||
			m_tri[i*3 + 1] < 4 ||
			m_tri[i*3 + 2] < 4)
		{
			m_tri.erase(m_tri.begin() + i*3, m_tri.begin() + i*3 + 3);
			i--;
			total--;
			continue;
		}
	}
	// For all other triangles, adjust the indices to reflect the removal
	for (uint i = 0; i < m_tri.size(); i++)
		m_tri[i] = m_tri[i] - 4;

	// Test each triangle for clockwisdom, fix if needed
	CleanupClockwisdom();

	ComputeExtents();

	return true;
}