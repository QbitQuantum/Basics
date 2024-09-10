int main ( int argc, char * argv[] )
/* main: handle options, open files */
{
    double tg, pr, l, crr, fa, tl, hl, t;
    char * scale;
    char * desc;
    double a10, a11, a20, a21;
    coOrd q0, q1, q2, q3, q1c, q2c;

	char *buffer = malloc( BUFSIZE );
	FILE *fIn, *fOut;

    q0.x = q0.y = 0.0;

	if( argc != 3 )
	{
		fprintf( stderr, 
			     "Usage: %1 nmraturnoutdata paramfile\n\n"
				 "The data file is read line by line and turnout defimitions\n"
				 "are created in the param file.\n\n",
				 argv[ 0 ] );
		exit( 1 );
	}

	fIn = fopen( argv[ 1 ], "r" );
	if( !fIn ) {
		fprintf( stderr, "Could not open the definition %s\n", argv[ 1 ] );
		exit( 1 );
	}

	fOut = fopen( argv[ 2 ], "w" );
	if( !fOut ) {
		fprintf( stderr, "Could not create the structures in %s\n", argv[ 2 ] );
		exit( 1 );
	}

	if( fgets( buffer, BUFSIZE, fIn ))
	{
		printf( "Creating %s\n", buffer + strlen("CONTENTS " ) );
		fputs( buffer, fOut );
	}
	while(fgets(buffer, BUFSIZE, fIn ))
	{
		if( buffer[ 0 ] == '#' ) {
			fputs( buffer, fOut );
			continue;
		}

	    scale = strtok( buffer, DELIMITER );
		desc = strtok( NULL, DELIMITER );
		tg = atof(strtok( NULL, DELIMITER ));
		q1.x = getval(strtok( NULL, DELIMITER ));
		q1.y = getval(strtok( NULL, DELIMITER ));
		pr = getval(strtok( NULL, DELIMITER ));
		l = getval(strtok( NULL, DELIMITER ));
		crr = getval(strtok( NULL, DELIMITER ));
		fa = getval(strtok( NULL, DELIMITER ));
		tl = getval(strtok( NULL, DELIMITER ));
		hl = getval(strtok( NULL, DELIMITER ));

		t = floor(fa);
		fa = t + (fa-t)/60*100;

		q2.x = l-tl;
		q2.y = tg-tl*TAN(fa);
		q3.x = l+hl;
		q3.y = tg+hl*SIN(fa);
		computeCurve( q0, q1, -pr, &q1c, &a10, &a11 );
		computeCurve( q1, q2, -crr, &q2c, &a20, &a21 );

		fprintf( fOut, "#NMRA-Std TO %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f\n",
			q1.x, q1.y, pr, l, crr, fa, tl, hl );

		fprintf( fOut, "TURNOUT %s \"NMRA %s\t#%s Right\t%sR\"\n", scale, scale, desc, desc);
		fprintf( fOut, "\tP \"Normal\" 1\n");
		fprintf( fOut, "\tP \"Reverse\" 2 3 4\n");
		fprintf( fOut, "\tE 0.000000 0.000000 270.000000\n");
		fprintf( fOut, "\tE %0.6f 0.000000 90.000000\n", l+hl);
		fprintf( fOut, "\tE %0.6f %0.6f %0.6f\n", q3.x, -q3.y, 90.0+fa);
		fprintf( fOut, "\tS 0 0 0.000000 0.000000 %0.6f 0.000000\n", l+hl);
		fprintf( fOut, "\tC 0 0 %0.6f %0.6f %0.6f %0.6f %0.6f\n", pr, q1c.x, -q1c.y, normalizeAngle(180-a10-a11), a11 );
		fprintf( fOut, "\tC 0 0 %0.6f %0.6f %0.6f %0.6f %0.6f\n", crr, q2c.x, -q2c.y, normalizeAngle(180-a20-a21), a21 );
		fprintf( fOut, "\tS 0 0 %0.6f %0.6f %0.6f %0.6f\n", q2.x, -q2.y, q3.x, -q3.y );
		fprintf( fOut, "\tEND\n");

		fprintf( fOut, "TURNOUT %s \"NMRA %s\t#%s Left\t%sL\"\n", scale, scale, desc, desc);
		fprintf( fOut, "\tP \"Normal\" 1\n");
		fprintf( fOut, "\tP \"Reverse\" 2 3 4\n");
		fprintf( fOut, "\tE 0.000000 0.000000 270.000000\n");
		fprintf( fOut, "\tE %0.6f 0.000000 90.000000\n", l+hl);
		fprintf( fOut, "\tE %0.6f %0.6f %0.6f\n", q3.x, q3.y, 90.0-fa);
		fprintf( fOut, "\tS 0 0 0.000000 0.000000 %0.6f 0.000000\n", l+hl);
		fprintf( fOut, "\tC 0 0 %0.6f %0.6f %0.6f %0.6f %0.6f\n", -pr, q1c.x, q1c.y, a10, a11 );
		fprintf( fOut, "\tC 0 0 %0.6f %0.6f %0.6f %0.6f %0.6f\n", -crr, q2c.x, q2c.y, a20, a21 );
		fprintf( fOut, "\tS 0 0 %0.6f %0.6f %0.6f %0.6f\n", q2.x, q2.y, q3.x, q3.y );
		fprintf( fOut, "\tEND\n");
	}
    exit(0);
}