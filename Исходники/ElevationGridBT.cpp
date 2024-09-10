/**
 * Writes the grid to a BT (Binary Terrain) file.
 * The current BT format version (1.3) is written.
 *
 * \param szFileName		The file name to write to.
 * \param progress_callback If supplied, this function will be called back
 *				with a value of 0 to 100 as the operation progresses.
 * \param bGZip			If true, the data will be compressed with gzip.
 *				If true, you should Use a filename ending with ".gz".
 */
bool vtElevationGrid::SaveToBT(const char *szFileName,
							   bool progress_callback(int), bool bGZip)
{
	int w = m_iColumns;
	int h = m_iRows;
	short zone = (short) m_proj.GetUTMZone();
	short datum = (short) m_proj.GetDatum();
	short isfloat = (short) IsFloatMode();
	short external = 1;		// always true: we always write an external .prj file

	LinearUnits units = m_proj.GetUnits();
	int hunits = (int) units;

	// Latest header, version 1.2
	short datasize = m_bFloatMode ? 4 : 2;
	DataType datatype = m_bFloatMode ? DT_FLOAT : DT_SHORT;

	if (bGZip == false)
	{
		// Use conventional IO
		FILE *fp = vtFileOpen(szFileName, "wb");
		if (!fp)
			return false;

		fwrite("binterr1.3", 10, 1, fp);
		FWrite(&w, DT_INT, 1, fp, BO_LITTLE_ENDIAN);
		FWrite(&h, DT_INT, 1, fp, BO_LITTLE_ENDIAN);
		FWrite(&datasize, DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);
		FWrite(&isfloat, DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);
		FWrite(&hunits,	DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);	// Horizontal Units (0, 1, 2, 3)
		FWrite(&zone,	DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);		// UTM zone
		FWrite(&datum,	DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);	// Datum

		// coordinate extents
		FWrite(&m_EarthExtents.left,	DT_DOUBLE, 1, fp, BO_LITTLE_ENDIAN);
		FWrite(&m_EarthExtents.right,	DT_DOUBLE, 1, fp, BO_LITTLE_ENDIAN);
		FWrite(&m_EarthExtents.bottom,	DT_DOUBLE, 1, fp, BO_LITTLE_ENDIAN);
		FWrite(&m_EarthExtents.top,		DT_DOUBLE, 1, fp, BO_LITTLE_ENDIAN);

		FWrite(&external, DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);		// External projection specification
		FWrite(&m_fVMeters, DT_FLOAT, 1, fp, BO_LITTLE_ENDIAN);	// Vertical scale factor (meters/units)

		// now write the data: always starts at offset 256
		fseek(fp, 256, SEEK_SET);

#if 0
		// slow way, one heixel at a time
		for (int i = 0; i < w; i++)
		{
			if (progress_callback != NULL) progress_callback(i * 100 / w);
			for (j = 0; j < h; j++)
			{
				if (m_bFloatMode) {
					fvalue = GetFValue(i, j);
					FWrite(&fvalue, datatype, 1, fp, BO_LITTLE_ENDIAN);
				} else {
					svalue = GetValue(i, j);
					FWrite(&svalue, datatype, 1, fp, BO_LITTLE_ENDIAN);
				}
			}
		}
#else
		// fast way, with the assumption that the data is stored column-first in memory
		if (m_bFloatMode)
		{
			for (int i = 0; i < w; i++)
			{
				if (progress_callback != NULL)
				{
					if (progress_callback(i * 100 / w))
					{ fclose(fp); return false; }
				}
				FWrite(m_pFData + (i * m_iRows), DT_FLOAT, m_iRows, fp, BO_LITTLE_ENDIAN);
			}
		}
		else
		{
			for (int i = 0; i < w; i++)
			{
				if (progress_callback != NULL)
				{
					if (progress_callback(i * 100 / w))
					{ fclose(fp); return false; }
				}
				FWrite(m_pData + (i * m_iRows), DT_SHORT, m_iRows, fp, BO_LITTLE_ENDIAN);
			}
		}
#endif
		fclose(fp);
	}
	else
	{
		// Use GZip IO
		gzFile fp = vtGZOpen(szFileName, "wb");
		if (!fp)
			return false;

		gzwrite(fp, (void *)"binterr1.3", 10);
		GZFWrite(&w, DT_INT, 1, fp, BO_LITTLE_ENDIAN);
		GZFWrite(&h, DT_INT, 1, fp, BO_LITTLE_ENDIAN);
		GZFWrite(&datasize,	DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);
		GZFWrite(&isfloat,	DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);
		GZFWrite(&hunits,	DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);		// Horizontal Units (0, 1, 2, 3)
		GZFWrite(&zone,		DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);		// UTM zone
		GZFWrite(&datum,	DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);		// Datum

		// coordinate extents
		GZFWrite(&m_EarthExtents.left,		DT_DOUBLE, 1, fp, BO_LITTLE_ENDIAN);
		GZFWrite(&m_EarthExtents.right,		DT_DOUBLE, 1, fp, BO_LITTLE_ENDIAN);
		GZFWrite(&m_EarthExtents.bottom,	DT_DOUBLE, 1, fp, BO_LITTLE_ENDIAN);
		GZFWrite(&m_EarthExtents.top,		DT_DOUBLE, 1, fp, BO_LITTLE_ENDIAN);

		GZFWrite(&external,		DT_SHORT, 1, fp, BO_LITTLE_ENDIAN);	// External projection specification
		GZFWrite(&m_fVMeters,	DT_FLOAT, 1, fp, BO_LITTLE_ENDIAN);	// Vertical scale factor (meters/units)

		// now write the data: always starts at offset 256
		gzseek(fp, 256, SEEK_SET);

		// fast way, with the assumption that the data is stored column-first in memory
		if (m_bFloatMode)
		{
			for (int i = 0; i < w; i++)
			{
				if (progress_callback != NULL)
				{
					if (progress_callback(i * 100 / w))
					{ gzclose(fp); return false; }
				}
				GZFWrite(m_pFData + (i * m_iRows), DT_FLOAT, m_iRows, fp, BO_LITTLE_ENDIAN);
			}
		}
		else
		{
			for (int i = 0; i < w; i++)
			{
				if (progress_callback != NULL)
				{
					if (progress_callback(i * 100 / w))
					{ gzclose(fp); return false; }
				}
				GZFWrite(m_pData + (i * m_iRows), DT_SHORT, m_iRows, fp, BO_LITTLE_ENDIAN);
			}
		}
		gzclose(fp);
	}

	if (external)
	{
		// Write external projection file (.prj)
		char prj_name[256];
		strcpy(prj_name, szFileName);
		int len = strlen(prj_name);
		if (bGZip)
			strcpy(prj_name + len - 6, ".prj"); // overwrite the .bt.gz
		else
			strcpy(prj_name + len - 3, ".prj"); // overwrite the .bt
		m_proj.WriteProjFile(prj_name);
	}

	return true;
}