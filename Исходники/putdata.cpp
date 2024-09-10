int receive_4d (char *fifo, char *path, int dimx, int dimy, int dimz, int dimt, int datatype)
{
	char fifo_from_idl [PATH_MAX];
	char fifo_to_idl [PATH_MAX];
	char line[200];
	int i;

	strcpy (fifo_from_idl, fifo );
	strcpy (fifo_to_idl, fifo );
	strcat (fifo_from_idl, "-");

#ifdef DEBUG
	fprintf (stderr, "Entered receive_4d, fifo_from_idl=%s\n", fifo_from_idl);
	fflush (stderr);
#endif

	FILE *f = fopen (fifo_from_idl, "rb");
	if (!f) 
		complain(BADPATH);

	//----------------------------------------------
	// Check params
	//
	if (dimx <= 0 || dimy <= 0 || dimz <= 0 || dimt <= 0)
		complain(ERROR_BADDIMS);
	if (datatype < 0)
		complain(ERROR_BADTYPE);

	//----------------------------------------------
	// Convert type
	//
	VB_datatype dt2;
	int datasize=0;
	switch (datatype) {
	case 1:	dt2 = vb_byte; datasize=1; break;
	case 2:	dt2 = vb_short; datasize=2; break;
	case 3:	dt2 = vb_long; datasize=4; break;
	case 4:	dt2 = vb_float; datasize=sizeof(float); break;
	case 5:	dt2 = vb_double; datasize=sizeof(double); break;
	default:
                return ERROR_BADTYPE;
	}

	//----------------------------------------------
	// Get the user-header info.
	//
	vector<string> user_header;
	if (0 > readline(f, line, 199))
		complain(ERROR_EOF);
	int total_header_items = atoi(line);
	if (total_header_items < 0)
		complain(ERROR_BADHEADER);
	for (i=0; i < total_header_items; i++) {
		if (0 > readline(f, line, 199))
			complain(ERROR_EOF);
		user_header.push_back (string(line));
	}

	//----------------------------------------------
	// Get the data
	//
	ulong chunk_size = dimx * dimy * dimz * dimt * datasize;
	unsigned char *chunk = (unsigned char*) malloc (chunk_size);
	if (!chunk) 
		complain(ERROR_NOMEM);
	if (chunk_size != fread (chunk,1,chunk_size,f))
		complain(ERROR_READFAIL);
	fclose (f);

	//----------------------------------------------
	// Create the Tes
	//
	Tes *t = new Tes(dimx,dimy,dimz,dimt,dt2);
	if (!t)
		complain(ERROR_NOMEM);

	//----------------------------------------------
	// Store the user header into the Tes object.
	//
	for (i=0; i < total_header_items; i++) {
		t->header.push_back (user_header[i]);
	}

	//----------------------------------------------
	// Now we process specific user header data
	// that we know have equivalents in the Tes object.
	//
	for (i=0; i < total_header_items; i++) {
		const char *s = user_header[i].c_str();
		char *s2 = s ? strchr(s, ':') : NULL;
		if (s2 && '*' == *s2)
			continue;
		if (!s2) s2 = s ? strchr (s, '=') : NULL;
		if (s2) {
			*s2++ = 0;
			if (!strcasecmp (s, "VoxSizes(xyz)")) {
				double x,y,z;
				if (3 == sscanf (s2, "%lg %lg %lg", &x,&y,&z)) {
					t->voxsize[0] = x;
					t->voxsize[1] = y;
					t->voxsize[2] = z;
				} else {
					WARNING("invalid voxsizes from user header.");
				}
			}
			else
			if (!strcasecmp (s, "Origin(xyz)")) {
				int x,y,z;
				if (3 == sscanf (s2, "%d %d %d", &x,&y,&z)) {
					t->origin[0] = x;
					t->origin[1] = y;
					t->origin[2] = z;
				} else {
					WARNING("invalid origin from user header.");
				}
			}
			else
			if (!strcasecmp (s, "Orientation")) {
				t->orient = s2;
			} 
			else
			if (!strcasecmp (s, "Scale")) {
				// float f = atof(s2);
				// t->scalefactor = f ? f : 1.0;
			} 
			else
			if (!strcasecmp (s, "ByteOrder")) {
				t->filebyteorder = atoi(s2)? ENDIAN_BIG : ENDIAN_LITTLE;
			} 
		} 
	}

#ifdef DEBUG
	time_t t0 = time(NULL);
#endif

	//----------------------------------------------
	// Store the data into the Tes.
	//
	int x,y,z,t2;
	//unsigned dimxy = dimx*dimy;
	//unsigned dimxyz = dimxy * dimz;
	for (x=0; x<dimx; x++) {
		for (y=0; y<dimy; y++) {
			for (z=0; z<dimz; z++) {
				for (t2=0; t2<dimt; t2++) {
					double value=0.0;
					unsigned long ix = t2 + x*dimt + y*dimt*dimx + z*dimt*dimx*dimy;

					switch (datatype) {
					case 1: 
						value = chunk[ix]; 
						break;
					case 2: 
						value = ((short*)chunk)[ix]; 
						break;
					case 3: 
						value = ((long*)chunk)[ix]; 
						break;
					case 4: 
						value = ((float*)chunk)[ix]; 
						break;
					case 5: 
						value = ((double*)chunk)[ix]; 
						break;
					}
					t->SetValue (x,y,z,t2, value);
				}
			}
		}
	}

#ifdef DEBUG
	t0 -= time(NULL);
	fprintf(stderr, "Time to write data into Tes object: %ld seconds\n", (long)-t0);
	fflush(stderr);
#endif

	//----------------------------------------------
	// Write the Tes to the file.
	//
	t->SetFileName (path);
#ifdef DEBUG
	fprintf(stderr, "Writing Tes file to %s\n", path);
#endif
	t->WriteFile ();

	//----------------------------------------------
	// Return the success code
	//
	f = fopen (fifo_to_idl, "wb");
	if (!f)
		return 0;
	fprintf (f, "1\n");
	fflush(f);
	fclose(f);

	delete t;

	return 0;
}