void VR_ShowCrosshair ()
{
	vec3_t forward, up, right;
	vec3_t start, end, impact;
	float size;
	if( (sv_player && (int)(sv_player->v.weapon) == IT_AXE) )
		return;

	// setup gl
	glDisable (GL_DEPTH_TEST);
	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
	GL_PolygonOffset (OFFSET_SHOWTRIS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable (GL_TEXTURE_2D);
	glDisable (GL_CULL_FACE);

	// calc the line and draw
	VectorCopy (cl.viewent.origin, start);
	start[2] -= cl.viewheight - 10;
	AngleVectors (cl.aimangles, forward, right, up);

	size = CLAMP (1.0, vr_crosshair_size.value, 5.0);

	switch((int) vr_crosshair.value)
	{	
		default:
		case VR_CROSSHAIR_POINT:
			if (vr_crosshair_depth.value <= 0) {
				 // trace to first wall
				VectorMA (start, 4096, forward, end);
				TraceLine (start, end, impact);
			} else {
				// fix crosshair to specific depth
				VectorMA (start, vr_crosshair_depth.value * meters_to_units, forward, impact);
			}

			glEnable(GL_POINT_SMOOTH);
			glColor4f (1, 0, 0, 0.5);
			glPointSize( size * glwidth / 1280.0f );

			glBegin(GL_POINTS);
			glVertex3f (impact[0], impact[1], impact[2]);
			glEnd();
			glDisable(GL_POINT_SMOOTH);
			break;

		case VR_CROSSHAIR_LINE:
			// trace to first entity
			VectorMA (start, 4096, forward, end);
			TraceLineToEntity (start, end, impact, sv_player);

			glColor4f (1, 0, 0, 0.4);
			glLineWidth( size * glwidth / (1280.0f) );
			glBegin (GL_LINES);
			glVertex3f (start[0], start[1], start[2]);
			glVertex3f (impact[0], impact[1], impact[2]);
			glEnd ();
			break;
	}

	// cleanup gl
	glColor3f (1,1,1);
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_CULL_FACE);
	glDisable(GL_BLEND);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	GL_PolygonOffset (OFFSET_NONE);
	glEnable (GL_DEPTH_TEST);
}