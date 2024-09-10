bool bBoard::create()
{
	guard(bBoard::create);

	ball_size = BALL_COUNT;
	ball = new bBall*[ball_size];

	ball[0] = new bBall( bVector( ball_data[0].x, ball_data[0].y ), bVector( 0, 0 ), bVector( 0, 0 ), 0.3, 1.0, 1.0f, 1.0f, 1.0f );

	for( int i=1; i<BALL_COUNT; ++i ) {
		ball[i] = new bBall( bVector( ball_data[i].x, ball_data[i].y ), bVector( 0, 0 ), bVector( 0, 0 ), 0.3, 1.0, 
				0.5f+((float)(rand()%10))/20.0f, 0.5f+((float)(rand()%10))/20.0f, 0.5f+((float)(rand()%10))/20.0f );
	}

	band_size = BOARD_SEGMENTS;
	band = new bBand*[band_size];

	for( int i=0; i<BOARD_SEGMENTS-1; ++i ) {
		band[i] = new bBand( 
				bVector( board_data[i].x, board_data[i].y ), 
				bVector( board_data[i+1].x, board_data[i+1].y ) 
				);
	}
	band[BOARD_SEGMENTS-1] = new bBand( 
			bVector( board_data[BOARD_SEGMENTS-1].x, board_data[BOARD_SEGMENTS-1].y ), 
			bVector( board_data[0].x, board_data[0].y ) 
			);

	luball.create( ball_size );
	luband.create( ball_size, band_size, false );

	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP );

	if( !ball_tex.load( GETPATH("../../tex/ball.bmp") ) ) {
		if( !ball_tex.load( GETPATH("../tex/ball.bmp") ) ) {
        		BLOG( "!! Error loading ball texture!\n" );
		}
	}

	if( !ball_num.load( GETPATH("../../tex/xball.bmp") ) ) {
		if( !ball_num.load( GETPATH("../tex/xball.bmp") ) ) {
		        BLOG( "!! Error loading ball texture!\n" );
		}
	}

	if( !desk.load( GETPATH("../../tex/desk.bmp") ) ) {
		if( !desk.load( GETPATH("../tex/desk.bmp") ) ) {
        		BLOG( "!! Error loading desk texture!\n" );
		}
	}

	if( !band_tex.load( GETPATH("../../tex/band.bmp") ) ) {
		if( !band_tex.load( GETPATH("../tex/band.bmp") ) ) {
			BLOG( "!! Error loading band texture!\n" );
		}
	}

	if( !shadow.load( GETPATH("../../tex/shadow.bmp") ) ) {
		if( !shadow.load( GETPATH("../tex/shadow.bmp") ) ) {
			BLOG( "!! Error loading shadow texture!\n" );
		}
	}

	if( bShader::is_supported() ) {
		if( !ball_shader.load_fragment( GETPATH("../../shaders/ball_frag.cg") ) ) {
			if( !ball_shader.load_fragment( GETPATH("../shaders/ball_frag.cg") ) ) {
				BLOG( "!! Error loading ball shader!\n" );   
			}
		}
		if( !ball_shader.load_vertex( GETPATH("../../shaders/ball_vert.cg") ) ) {
			if( !ball_shader.load_vertex( GETPATH("../shaders/ball_vert.cg") ) ) {
				BLOG( "!! Error loading ball shader!\n" );   
			}
		}
		if( !board_shader.load_fragment( GETPATH("../../shaders/board_frag.cg") ) ) {
			if( !board_shader.load_fragment( GETPATH("../shaders/board_frag.cg") ) ) {
				BLOG( "!! Error loading board shader!\n" );   
			}
		}
	} else {
		BLOG( "!! Shaders are not supported!\n" );   
	}

	if( !glewIsSupported("GL_ARB_multitexture") )
	{
		BLOG( "!! Multitexturing is not supported!\n" );
	}

	return true;

	unguard;
}