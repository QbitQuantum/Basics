/*
=================
ParsePatch

Creates a mapDrawSurface_t from the patch text
=================
*/
void ParsePatch( void ) {
	vec_t		info[5];
	int			i, j;
	parseMesh_t	*pm;
	char		texture[MAX_QPATH];
	char		shader[MAX_QPATH];
	mesh_t		m;
	drawVert_t	*verts;
  epair_t *ep;

	MatchToken( "{" );

	// get texture
	GetToken (qtrue);
	strcpy( texture, token );

	// save the shader name for retexturing
	if ( numMapIndexedShaders == MAX_MAP_BRUSHSIDES ) {
		Error( "MAX_MAP_BRUSHSIDES" );
	}
	strcpy( mapIndexedShaders[numMapIndexedShaders], texture );
	numMapIndexedShaders++;


	Parse1DMatrix( 5, info );
	m.width = info[0];
	m.height = info[1];
	m.verts = verts = malloc( m.width * m.height * sizeof( m.verts[0] ) );

	if ( m.width < 0 || m.width > MAX_PATCH_SIZE
		|| m.height < 0 || m.height > MAX_PATCH_SIZE ) {
		Error("ParsePatch: bad size");
	}

	MatchToken( "(" );
	for ( j = 0 ; j < m.width ; j++ ) {
		MatchToken( "(" );
		for ( i = 0 ; i < m.height ; i++ ) {
			Parse1DMatrix( 5, verts[i*m.width+j].xyz );
		}
		MatchToken( ")" );
	}
	MatchToken( ")" );

  // if brush primitives format, we may have some epairs to ignore here
  GetToken(qtrue);
  if (g_bBrushPrimit!=BPRIMIT_OLDBRUSHES && strcmp(token,"}"))
  {
    // NOTE: we leak that!
    ep = ParseEpair();
  }
  else
    UnGetToken();

	MatchToken( "}" );
	MatchToken( "}" );

	if ( noCurveBrushes ) {
		return;
	}

	// find default flags and values
	pm = malloc( sizeof( *pm ) );
	memset( pm, 0, sizeof( *pm ) );

	sprintf( shader, "textures/%s", texture );
	pm->shaderInfo = ShaderInfoForShader( shader ); 
	pm->mesh = m;

	// link to the entity
	pm->next = mapent->patches;
	mapent->patches = pm;
}