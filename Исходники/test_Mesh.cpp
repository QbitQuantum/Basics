void TestAppMesh::eventHandling ( const SDL_Event& event  ){
    //printf( "NonInert_seats::eventHandling() \n" );
    switch( event.type ){
        case SDL_KEYDOWN :
            switch( event.key.keysym.sym ){
                case SDLK_p:  first_person = !first_person; break;
                case SDLK_o:  perspective  = !perspective; break;
                //case SDLK_r:  world.fireProjectile( warrior1 ); break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch( event.button.button ){
                case SDL_BUTTON_LEFT:
                    Vec3d ray0;
                    ray0.set_lincomb( 1, mouse_begin_x, mouse_begin_y, camPos, camMat.a, camMat.b );
                    //glColor3f(1,1,1); Draw3D::drawPointCross( ray0, 0.2 );
                    ipicked= mesh.pickVertex( ray0, camMat.c );
                    mouse0.set(mouse_begin_x, mouse_begin_y);
                    dragging=true;
                    break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch( event.button.button ){
                case SDL_BUTTON_LEFT:
                    if(dragging){
                        Vec3d d;
                        d.set_lincomb( 1, mouse_begin_x, mouse_begin_y, camPos, camMat.a, camMat.b );
                        d.sub(mesh.points[ipicked]);
                        double c = d.dot(camMat.c);  d.add_mul(camMat.c, -c);
                        mesh.points[ipicked].add(d);

                        glDeleteLists(mesh.rendered_shape, 1);
                        mesh.rendered_shape = glGenLists(1);
                        glNewList( mesh.rendered_shape , GL_COMPILE );
                            glEnable( GL_LIGHTING );
                            glColor3f( 0.8f, 0.8f, 0.8f );
                            Draw3D::drawMesh( mesh );
                            mesh.tris2normals(true);
                            glColor3f(0.0f,0.0f,0.9f);
                            for(int i=0; i<mesh.points.size(); i++){
                                Draw3D::drawVecInPos( mesh.normals[i], mesh.points[i] );
                            }
                        glEndList();
                    }
                    dragging=false;
                    break;
            }
    };
    AppSDL2OGL::eventHandling( event );
}