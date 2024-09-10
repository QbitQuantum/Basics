void GL_draw_frame( void * vp )
{
    static float rot;
    static int t0;
    float s;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    

    glLineWidth(1.f);

    set_camera_view();



    if ( t0 == 0 ) {
        init_VBO();
        t0 = 1;
    }

    int now = get_milliseconds();

/*
    while ( now - t0 > 20 ) {
        rot += 1.0f;
        t0 += 20;
        if ( rot > 360.f ) 
            rot -= 360.f;
        if ( rot < 0.f ) 
            rot += 360.f;
    }
*/


    // hack to get rotation timer right
    const float p180            =   0.017453126f;
    const float c180p           =   57.295776f;
    const float c2pi            =   6.2831854f;
    const int   ms_per_frame    =   20;                      // milliseconds per frame 
    const float rot_per_frame   =   1.0f * p180;
    
/*
    while ( now - t0 > ms_per_frame ) {
        rot += 1.0f;
        t0 += ms_per_frame;
    } */

    static int set = 0;

    if ( t0 <= 0 )
        t0 = 1;

    if ( now - t0 > 0 ) 
    {
        int diff = now - t0;

        /* the rotation is incremented 1 rot_per_frame each 1 ms_per_frame */
        float newrot = rot + (rot_per_frame/(float)ms_per_frame) * ((float)diff);

        if ( set < 20 ) 
            core.printf( "hiccup > 2pi: before: %f, %f ", rot, sinf(rot) );
        
        rot = newrot;

        // catch it up
        t0 = now;

        if ( set < 20 )
            core.printf( "after: %f, %f\n", rot, sinf( rot ) );

        // clamp
        if ( rot > c2pi ) {
            rot = rot - c2pi;

            set = 1; // no more print

            core.printf( " --> MARK <-- \n" );
        }
        
        if ( set != 0 )
            ++set;
        
    }

    const float rotdeg = rot * c180p;



    /// -- DRAW --- 
    
    // rotating wire spiral
    glColor4ub( 255,255,255,255 );
    glPushMatrix();
    glRotatef( rotdeg, 0, 1, 0 );
    draw_spiral( 24.0f, 10.f, 0.05f );
    glPopMatrix();


    // rotating circle
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, core.materials.findByName( "jr_bob" )->img->texhandle );
    glPushMatrix();
    glTranslatef( 60.f, 60.f, -60.f );
    glRotatef( rotdeg, 0, 1, 0 );
    draw_circle( 0, 0, 10.f );
    GL_TEX_SQUARE( -10.f, 30.f, 0.f, 20.f );
    glRotatef( 180, 0, 1, 0 );
    draw_circle( 0, 0, 10.f );
    GL_TEX_SQUARE( -10.f, 30.f, 0.f, 20.f );
    glBegin(GL_LINES); glVertex3f( 0, -30.f, 0 ); glVertex3f( 0, 30.f, 0 ); glEnd();
    glPopMatrix();
    glDisable( GL_TEXTURE_2D );


    // FIXME : obviously move, later.
    tessellatedPlane_t& tes = *(tessellatedPlane_t*)vp;

    // heightmap triangles
    glInterleavedArrays( GL_C3F_V3F, 0, tes.array );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, tes.num_verts );
    //glDrawArrays( GL_LINE_STRIP, 0, tes->num_verts );


    // gazillion boxes
    core.drawer.drawLists();

    // serpinski
    glColor4ub( 255,255,0,255 ); 
    glPushMatrix();
    glTranslatef( 250.f, 100.f, -250.f );
    glRotatef( rotdeg * 1.618f, 0, 1, 0 );
    glRotatef( rotdeg , 0.707, 0, -0.707 );
    glDisable( GL_CULL_FACE );
    draw_serpinski( 3, 40.f );
    glEnable( GL_CULL_FACE );
    glPopMatrix();
    glColor4ub( 255,255,255,255 );

    // icosahedron
    glPushMatrix();    
    glTranslatef( 500.f, 100.f, -250.f );
    trans_spiral_f( rot, 50.f /*radius*/, 1.0f/*rot rate*/, 1.0f/*climb rate*/, 50.f /*ceiling*/ );
    s = 14.f;
    s = (sinf( rot * 2.718f ) + 1.1f) * 14.f;
    glScalef( s, s, s );
    glRotatef( rotdeg * 5.f, 0, 1, 0 );
    glRotatef( rotdeg * 3.f , 0.707, 0, -0.707 );
    glColor4ub( 230, 100, 0, 255 );
    draw_icosahedron();
    glColor4ub( 255, 255, 255, 255 );
    draw_icosahedron_wire();
    glPopMatrix();


    // axis marker
    float l = 100.f;
    glColor3f( 1.f, 0.f, 1.f );
    glLineWidth(2.f);
    glBegin( GL_LINES );
    glVertex3i( 0,0,0 );
    glVertex3i( 0,l,0);
    glVertex3i( 0,0,0 );
    glVertex3i( l,0,0 );
    glVertex3i( 0,0,0 );
    glVertex3i( 0,0,-l );
    glEnd();

    
    // 4-sided
    glPushMatrix();
    glTranslatef( 300, 100, 0 );
    s = 20.f;
    glScalef( s, s, s );
    glRotatef( rotdeg, 0, 1, 0 );
    glColor4ub( 0, 255, 255, 128 );
    draw_triangle4(0);
    glColor4ub( 255, 255, 255, 255 );
    draw_triangle4(1);
    glPopMatrix();

    // 4-sided, 2nd type
    glPushMatrix();
    glTranslatef( 340, 100, 0 );
    s = 20.f;
    glScalef( s, s, s );
    glRotatef( rotdeg, 0, 1, 0 );
    glColor4ub( 100, 0, 100, 128 );
    draw_triangle4_2(0);
    glColor4ub( 255, 255, 255, 255 );
    draw_triangle4(1); // inner lines don't draw right, so use first form
    glPopMatrix();

    // 5-sided
    glPushMatrix();
    glTranslatef( 100, 100, -50 );
    s = 20.f;
    glScalef( s, s, s );
    glRotatef( rotdeg, 1, 0, 0 );
    glColor4ub( 100, 50, 0, 200 );
    draw_triangle5(0);
    glColor4ub( 255, 255, 255, 255 );
    draw_triangle5(1);
    glPopMatrix();

    // unit-cube w/ tri
    glPushMatrix();
    glTranslatef( 150.f, 130.f, -800.f );
    glTranslatef( 0.f, 0.f, sinf(rot)*1600.f );
    s = 20.f;
    glScalef( s, s, s );
    glRotatef( 90, 1, 0, 0 );
    glRotatef( sinf(rotdeg*0.03f)*180.f, 0, 1, 0 );
    glColor4ub( 128,128,128,255 );
    draw_unitcube(0);
    glColor4ub( 255,255,255,255 );
    draw_unitcube(1);
    glTranslatef( 0, 1.f, 0.f );
    glColor4ub( 128,128,128,255 );
    draw_triangle5(0);
    glColor4ub( 255,255,255,255 );
    draw_triangle5(1);
    glPopMatrix();
    
    // test model
    //glEnable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef( 300.f, 75.f, 200.f );
    glRotatef( 315.f, 0,1,0 );
    glEnable(GL_LIGHT0);
    s = 550.f;
    glScalef( s, s, s );
    glColor4ub( 255,255,255,255);
    //draw_test_model_Vertex_Arrays();
    draw_test_model_VBO();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4ub( 128,128,168,255 );
    //draw_test_model_Vertex_Arrays();
    draw_test_model_VBO();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPopMatrix();
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);


    glFlush();                                                    
    SDL_GL_SwapBuffers();
}