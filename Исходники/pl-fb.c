/*
  DoFile - process UNIX plot file

  This routine reads UNIX plot records from the specified file
  and controls the entry of the strokes into the descriptor lists.
  Strokes are limited (not clipped) to fit the frame.

  Upon end of file, erase, or flush, plot data is copied to the device.
  Returns status code:
  < 0	=> catastrophe
  = 0	=> complete success
  > 0	=> line limit hit
*/
static int
DoFile(void)	/* returns vpl status code */
{
    register bool	plotted;	/* false => empty frame image */
    register int	c;		/* input character */
    static coords	newpos; 	/* current input coordinates */
    static coords	virpos; 	/* virtual pen position */
    static unsigned char buf3[6*2];
    static unsigned char buf2[4*2];
    static	bool	firsterase = true;

    /* process each frame into a raster image file */

    for (;;)			/* for each frame */
    {
	InitDesc();		/* empty descriptor lists */

	virpos.x = virpos.y = 0;
	plotted = false;

	for (;;)		/* read until EOF*/
	{
	    c = getc( pfin );
	    if ( debug > 1 )  fprintf(stderr, "%c\n", c);
	    switch ( c )
	    {
		/* record type */
		case EOF:
		    if ( debug ) fprintf( stderr, "EOF\n");

		    if ( plotted )  {
			/* flush strokes */
			if ( debug ) fprintf( stderr, "flushing\n");
			if ( !OutBuild() )
			    return Foo( -6 );
		    }
		    return Foo( 0 );/* success */

		case 'e':	/* erase */
		    if ( debug )  fprintf( stderr, "Erase\n");

		    if ( plotted )  {
			/* flush strokes */
			if ( debug ) fprintf( stderr, "flushing\n");
			if ( !OutBuild() )
			    return Foo( -6 );
		    }
		    if ( !firsterase ) {
			if ( immediate )
			    fb_clear( fbp, RGBPIXEL_NULL );
			over = 0;
		    }
		    firsterase = false;
		    break;	/* next frame */

		case 'F':	/* flush */
		    if ( debug )  fprintf( stderr, "Flush\n");

		    if ( plotted )  {
			/* flush strokes */
			if ( debug ) fprintf( stderr, "flushing\n");
			if ( !OutBuild() )
			    return Foo( -6 );
			if ( !immediate )
			    over = 1;
		    }
		    firsterase = false;
		    break;	/* next frame */

		case 'f':	/* linemod */
		    if (debug)
			fprintf( stderr, "linemod\n");
		    /* ignore for time being */
		    while ( (c = getc( pfin )) != EOF
			    && c != '\n'
			)
			;	/* eat string */
		    continue;

		case 'L':
		case 'M':
		    if ( !Get3Coords( &newpos ) )
			return Foo( -8 );
		    virpos = newpos;
		    if ( c == 'M'  )  {
			if ( debug )
			    fprintf( stderr, "Move3\n");
			continue;
		    }
		    if ( debug )
			fprintf( stderr, "Line3\n");

		case 'N':	/* continue3 */
		case 'P':	/* point3 */
		    if ( !Get3Coords( &newpos ) )
			return Foo( -9 );
		    if ( c == 'P' )  {
			if ( debug )
			    fprintf( stderr, "point3\n");
			virpos = newpos;
		    } else
			if ( debug )
			    fprintf( stderr, "cont3\n");

		    if ( !BuildStr( &virpos, &newpos ) )
			return Foo( -10 );
		    plotted = true;
		    virpos = newpos;
		    continue;

		case 'l':	/* line */
		case 'm':	/* move */
		    if ( !GetCoords( &newpos ) )
			return Foo( -8 );
		    virpos = newpos;
		    if ( c == 'm' )  {
			if ( debug )
			    fprintf( stderr, "move\n");
			continue;
		    }
		    /* line: fall through */
		    if ( debug )
			fprintf( stderr, "line\n");

		case 'n':	/* cont */
		case 'p':	/* point */
		    if ( !GetCoords( &newpos ) )
			return Foo( -9 );
		    if ( c == 'p' )  {
			if ( debug )
			    fprintf( stderr, "point\n");
			virpos = newpos;
		    } else
			if ( debug )
			    fprintf( stderr, "cont\n");

		    if ( !BuildStr( &virpos, &newpos ) )
			return Foo( -10 );
		    plotted = true;
		    virpos = newpos;
		    continue;

		    /* IEEE */
		case 'V':
		case 'O':
		    if ( !Get3DCoords( &newpos ) )
			return Foo( -8 );
		    virpos = newpos;
		    if ( c == 'O'  )  {
			if ( debug )
			    fprintf( stderr, "dMove3\n");
			continue;
		    }
		    if ( debug )
			fprintf( stderr, "dLine3\n");

		case 'Q':	/* continue3 */
		case 'X':	/* point3 */
		    if ( !Get3DCoords( &newpos ) )
			return Foo( -9 );
		    if ( c == 'X' )  {
			if ( debug )
			    fprintf( stderr, "dpoint3\n");
			virpos = newpos;
		    } else
			if ( debug )
			    fprintf( stderr, "dcont3\n");

		    if ( !BuildStr( &virpos, &newpos ) )
			return Foo( -10 );
		    plotted = true;
		    virpos = newpos;
		    continue;

		case 'v':	/* line */
		case 'o':	/* move */
		    if ( !GetDCoords( &newpos ) )
			return Foo( -8 );
		    virpos = newpos;
		    if ( c == 'o' )  {
			if ( debug )
			    fprintf( stderr, "dmove\n");
			continue;
		    }
		    /* line: fall through */
		    if ( debug )
			fprintf( stderr, "dline\n");

		case 'q':	/* cont */
		case 'x':	/* point */
		    if ( !GetDCoords( &newpos ) )
			return Foo( -9 );
		    if ( c == 'x' )  {
			if ( debug )
			    fprintf( stderr, "dpoint\n");
			virpos = newpos;
		    } else
			if ( debug )
			    fprintf( stderr, "dcont\n");

		    if ( !BuildStr( &virpos, &newpos ) )
			return Foo( -10 );
		    plotted = true;
		    virpos = newpos;
		    continue;

		case 'W':
		{
		    unsigned char	in[6*8];
		    double	out[6];
		    if ( debug )
			fprintf( stderr, "dspace3\n");
		    if ( fread( in, sizeof(in), 1, pfin) != 1 )
			return Foo( -11 );
		    ntohd( (unsigned char *)out, in, 5 );
		    /* Only need X and Y, ignore Z */
		    space.left  = out[0]; /* x1 */
		    space.bottom= out[1]; /* y1 */
		    /* z1 */
		    space.right = out[3]; /* x2 */
		    space.top   = out[4]; /* y2 */
		    /* z2 */
		    goto spacend;
		}

		case 'w':	/* space */
		{
		    unsigned char	in[4*8];
		    double	out[4];
		    if ( debug )
			fprintf( stderr, "dspace\n");
		    if ( fread( in, sizeof(in), 1, pfin) != 1 )
			return Foo( -11 );
		    ntohd( (unsigned char *)out, in, 4 );
		    space.left  = out[0]; /* x1 */
		    space.bottom= out[1]; /* y1 */
		    space.right = out[2]; /* x2 */
		    space.top   = out[3]; /* y2 */
		    goto spacend;
		}

		case 'S':
		{
		    if ( debug )
			fprintf( stderr, "space3\n");
		    if ( fread( (char *)buf3,
				(int)sizeof buf3, 1, pfin)
			 != 1
			)
			return Foo( -11 );
		    /* Only need X and Y, ignore Z */
		    space.left  = sxt16((long)(buf3[1]<<8) | buf3[0]); /* x1 */
		    space.bottom= sxt16((long)(buf3[3]<<8) | buf3[2]); /* y1 */
		    /* z1 */
		    space.right = sxt16((long)(buf3[7]<<8) | buf3[6]); /* x2 */
		    space.top   = sxt16((long)(buf3[9]<<8) | buf3[8]); /* y2 */
		    /* z2 */
		    goto spacend;
		}

		case 's':	/* space */
		    if ( debug )
			fprintf( stderr, "space\n");
		    {
			if ( fread( (char *)buf2,
				    (int)sizeof buf2, 1, pfin
				 ) != 1
			    )
			    return Foo( -11 );
			space.left  = sxt16((long)(buf2[1]<<8) | buf2[0]); /* x1 */
			space.bottom= sxt16((long)(buf2[3]<<8) | buf2[2]); /* y1 */
			space.right = sxt16((long)(buf2[5]<<8) | buf2[4]); /* x2 */
			space.top   = sxt16((long)(buf2[7]<<8) | buf2[6]); /* y2 */
		    }

	    spacend:
		    delta = space.right - space.left;
		    deltao2 = space.top - space.bottom;
		    if ( deltao2 > delta )
			delta = deltao2;
		    if ( delta <= 0 )  {
			fprintf( stderr, "pl-fb: delta = %g, bad space()\n", delta );
			return Foo( -42 );
		    }
		    deltao2 = delta / 2.0;
		    if ( debug )
			fprintf( stderr, "Space: X=(%g,%g) Y=(%g,%g) delta=%g\n",
				 space.left, space.right,
				 space.bottom, space.top,
				 delta );
		    continue;

		case 'C':	/* color */
		    if ( fread( cur_color, 1, 3, pfin) != 3 )
			return Foo( -11 );
		    if ( debug )
			fprintf( stderr, "Color is R%d G%d B%d\n",
				 cur_color[RED],
				 cur_color[GRN],
				 cur_color[BLU]);
		    continue;

		case 't':	/* label */
		    if ( debug )
			fprintf( stderr, "label: ");

		    newpos = virpos;
		    while ( (c = getc( pfin )) != EOF && c != '\n'
			)  {
			/* vectorize the characters */
			put_vector_char( c, &newpos);

			if ( debug )
			    putc( c, stderr );
		    }

		    plotted = true;
		    virpos = newpos;
		    continue;

		    /* discard the deadwood */
		case 'c':
		{
		    char buf[3*2];
		    if ( fread(buf, sizeof(buf), 1, pfin) != 1 )
			return Foo( -11 );
		    if ( debug )
			fprintf( stderr, "circle ignored\n" );
		    continue;
		}
		case 'i':
		{
		    char buf[3*8];
		    if ( fread(buf, sizeof(buf), 1, pfin) != 1 )
			return Foo( -11 );
		    if ( debug )
			fprintf( stderr, "d_circle ignored\n" );
		    continue;
		}
		case 'a':
		{
		    char buf[6*2];
		    if ( fread(buf, sizeof(buf), 1, pfin) != 1 )
			return Foo( -11 );
		    if ( debug )
			fprintf( stderr, "arc ignored\n" );
		    continue;
		}
		case 'r':
		{
		    char buf[6*8];
		    if ( fread(buf, sizeof(buf), 1, pfin) != 1 )
			return Foo( -11 );
		    if ( debug )
			fprintf( stderr, "d_arc ignored\n" );
		    continue;
		}

		default:
		    fprintf( stderr, "bad command '%c' (0x%02x)\n", c, c );

		    return Foo( -12 );	/* bad input */
	    }
	    break;
	}		/* next input record */
    }			/* next frame */
}