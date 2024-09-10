static void
_draw_track (RendererSimTraffic *self, const lcmtypes_track_t *vd)
{
    // generate a stable non-black, non-white color from object ID
    srand(vd->id);
    GLfloat rgb[4];
    rand_color(rgb);

    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, rgb);
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, rgb);

    // assumes viewing, modeling matrices, etc. set up for local frame
    // leaves these matrices as they were before invocation
    glMatrixMode (GL_MODELVIEW);
    glPushMatrix();

    glTranslated (vd->pos[0], vd->pos[1], 0);

// rotate basis to body coords of vehicle (rotate by theta about Z axis)
    glRotated (to_degrees(vd->theta), 0.0, 0.0, 1.0); // convert rad to deg

    if (self->ehandler.hovering && 
            self->selected_vehicle_id == vd->id) {
        glColor4f (1, 1, 1, 0.6);
    } else {
        glColor4fv(rgb);
    }

//    int use_model =  gtku_param_widget_get_bool(self->pw, PARAM_PRETTY);
//
//    if (use_model) {
//
//        glRotated(90, 0, 0, 1);
//        glRotated(90, 1, 0, 0);
//        
//        double s = 4.5;
//        glScalef(s,s,s);
//        
//        glTranslated(0,.115,0); // car height
//        glTranslated(0,0,.1); // front-to-back offset
//        glBegin(GL_TRIANGLES);
//        for (int i = 0; i < numChevy_vanFaces; i++) {
//            int *vs = Chevy_vanFaces[i];
//            for (int j = 0; j < 3; j++) {
//                glNormal3fv(Chevy_vanVertNorms[vs[j]]);
//                glVertex3fv(Chevy_vanVerts[vs[j]]);
//            }
//            
//        }
//        glEnd();
//    } else {

    glTranslated ( 0, 0, VEHICLE_HEIGHT / 2);

    glScalef (vd->size[0], vd->size[1], VEHICLE_HEIGHT);
    glutil_draw_cube();
//    }

    // restore matrix state
    glPopMatrix();

    if (self->ehandler.picking && self->selected_vehicle_id == vd->id) {
        glColor4f (1, 1, 1, 0.6);
        glPushMatrix ();
        glTranslatef (self->last_xy[0], self->last_xy[1], 0);
        glRotated (to_degrees(vd->theta), 0.0, 0.0, 1.0); // convert rad to deg
        glScalef (vd->size[0], vd->size[1], VEHICLE_HEIGHT);
        glutil_draw_cube_frame ();
        glPopMatrix ();
    }
}