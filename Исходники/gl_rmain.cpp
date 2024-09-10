/*
=============
R_SetupGL
=============
*/
void R_SetupGL (void)
{
	float	screenaspect;
	float	yfov;
	int		i;
	extern	int glwidth, glheight;
	int		x, x2, y2, y, w, h;

	//
	// set up viewpoint
	//
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity ();
	x = r_refdef.vrect.x * glwidth/vid.width;
	x2 = (r_refdef.vrect.x + r_refdef.vrect.width) * glwidth/vid.width;
	y = (vid.height-r_refdef.vrect.y) * glheight/vid.height;
	y2 = (vid.height - (r_refdef.vrect.y + r_refdef.vrect.height)) * glheight/vid.height;

	// fudge around because of frac screen scale
	if (x > 0)
		x--;
	if (x2 < glwidth)
		x2++;
	if (y2 < 0)
		y2--;
	if (y < glheight)
		y++;

	w = x2 - x;
	h = y - y2;

	if (envmap)
	{
		x = y2 = 0;
		w = h = 256;
	}

	glViewport (glx + x, gly + y2, w, h);
    screenaspect = (float)r_refdef.vrect.width/r_refdef.vrect.height;
//	yfov = 2*atan((float)r_refdef.vrect.height/r_refdef.vrect.width)*180/M_PI;
    MYgluPerspective (r_refdef.fov_y,  screenaspect,  4,  4096);

	if (mirror)
	{
		if (mirror_plane->normal[2])
			glScalef (1, -1, 1);
		else
			glScalef (-1, 1, 1);
		glCullFace(GL_BACK);
	}
	else
		glCullFace(GL_FRONT);

	glMatrixMode(GL_MODELVIEW);

#ifdef DO_OWN_MATRIX_MATH

	float mv[16];
    setIdentityM(mv, 0);

    rotateM(mv, -90,  1, 0, 0);	    // put Z going up
    rotateM(mv, 90,  0, 0, 1);	    // put Z going up
    rotateM(mv, -r_refdef.viewangles[2],  1, 0, 0);
    rotateM(mv, -r_refdef.viewangles[0],  0, 1, 0);
    rotateM(mv, -r_refdef.viewangles[1],  0, 0, 1);
    translateM(mv, 0, -r_refdef.vieworg[0],  -r_refdef.vieworg[1],  -r_refdef.vieworg[2]);

    glLoadMatrixf(mv);

    memcpy(r_world_matrix, mv, sizeof(r_world_matrix));

#else
    glLoadIdentity ();

    glRotatef (-90,  1, 0, 0);	    // put Z going up
    glRotatef (90,  0, 0, 1);	    // put Z going up
    glRotatef (-r_refdef.viewangles[2],  1, 0, 0);
    glRotatef (-r_refdef.viewangles[0],  0, 1, 0);
    glRotatef (-r_refdef.viewangles[1],  0, 0, 1);
    glTranslatef (-r_refdef.vieworg[0],  -r_refdef.vieworg[1],  -r_refdef.vieworg[2]);

#ifdef USE_OPENGLES

    static qboolean initialized;
    static qboolean haveGL_OES_matrix_get;
    static qboolean haveGL_OES_query_matrix;

#if 0
    if (! initialized) {
        const char* extensions = (const char*) glGetString(GL_EXTENSIONS);
        haveGL_OES_matrix_get =
            strstr(extensions, "GL_OES_matrix_get") != NULL;
        haveGL_OES_query_matrix =
            strstr(extensions, "GL_OES_query_matrix") != NULL;
        initialized = true;
    }
    if (haveGL_OES_query_matrix) {
        GLfixed mantissa[16];
        GLint exponent[16];
        glQueryMatrixxOES( mantissa, exponent );
        for(int i = 0; i < 16; i++) {
            r_world_matrix[i] = scalbnf(mantissa[i], exponent[i]-16);
        }
    }
    else if (haveGL_OES_matrix_get) {
        glGetIntegerv (MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES,
                (GLint*) r_world_matrix);
    }
    else
#endif
    	{
        // No way to get the world matix, set to identity
        memset(r_world_matrix, 0, sizeof(r_world_matrix));
        for(i = 0; i < 16; i += 5) {
            r_world_matrix[i] = 1.0f;
        }
    }
#else
	glGetFloatv (GL_MODELVIEW_MATRIX, r_world_matrix);
#endif
#endif // DO_OWN_MATRIX_MATH
	//
	// set drawing parms
	//
	if (gl_cull.value)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
}