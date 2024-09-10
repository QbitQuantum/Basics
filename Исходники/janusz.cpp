/**
 * body()
 *
 * Creates a display list for the body of a person.
 */
void body()
{
   GLfloat fan_angle;   //angle for a triangle fan
   int sections = 40;   //number of triangles in a triangle fan

   //generate a display list for a body
   body_list_id = glGenLists(1);
   //compile the new display list
   glNewList(body_list_id, GL_COMPILE);

   glPushMatrix();
      glTranslatef(0.0f, 5.05f, 0.0f);
      glRotatef(90, 1.0, 0.0, 0.0);

      //create a torso with a cylinder
      glPushMatrix();
         GLUquadricObj * torso;
         torso = gluNewQuadric();
         gluQuadricDrawStyle(torso, GLU_FILL);
         gluCylinder(torso, 1.0f, 1.0f, 2.25f, 25, 25);
      glPopMatrix();

      //triangle fan for top of body
      glPushMatrix();
         glRotatef(180.0, 0.0, 1.0, 0.0);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(cosf(fan_angle), sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //triangle fan for bottom of torso
      glPushMatrix();
         glTranslatef(0.0, 0.0, 2.25);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(cosf(fan_angle), sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //arm 1
      glPushMatrix();
         glTranslatef(1.25f, 0.0f, 0.0f);
         GLUquadricObj * arm1;
         arm1 = gluNewQuadric();
         gluQuadricDrawStyle(arm1, GLU_FILL);
         gluCylinder(arm1, 0.25f, 0.25f, 2.5f, 12, 12);
      glPopMatrix();

      //triangle fan for top of arm 1
      glPushMatrix();
         glTranslatef(1.25, 0.0, 0.0);
         glRotatef(180.0, 0.0, 1.0, 0.0);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.25*cosf(fan_angle), 0.25*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //triangle fan for bottom of arm 1
      glPushMatrix();
         glTranslatef(1.25, 0.0, 2.5);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.25*cosf(fan_angle), 0.25*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //arm 2
      glPushMatrix();
         glTranslatef(-1.25f, 0.0f, 0.0f);
         GLUquadricObj * arm2;
         arm2 = gluNewQuadric();
         gluQuadricDrawStyle(arm2, GLU_FILL);
         gluCylinder(arm2, 0.25f, 0.25f, 2.5f, 12, 12);
      glPopMatrix();

      //triangle fan for top of arm 2
      glPushMatrix();
         glTranslatef(-1.25, 0.0, 0.0);
         glRotatef(180.0, 0.0, 1.0, 0.0);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.25*cosf(fan_angle), 0.25*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //triangle fan for bottom of arm 2
      glPushMatrix();
         glTranslatef(-1.25, 0.0, 2.5);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.25*cosf(fan_angle), 0.25*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //leg 1
      glPushMatrix();
         glTranslatef(0.5f, 0.0f, 2.25f);
         GLUquadricObj * leg1;
         leg1 = gluNewQuadric();
         gluQuadricDrawStyle(leg1, GLU_FILL);
         gluCylinder(leg1, 0.5f, 0.2f, 2.8f, 12, 12);
      glPopMatrix();

      //triangle fan for bottom of leg 1
      glPushMatrix();
         glTranslatef(0.5, 0.0, 5.05);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.2*cosf(fan_angle), 0.2*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

      //leg 2
      glPushMatrix();
         glTranslatef(-0.5f, 0.0f, 2.25f);
         GLUquadricObj * leg2;
         leg2 = gluNewQuadric();
         gluQuadricDrawStyle(leg2, GLU_FILL);
         gluCylinder(leg2, 0.5f, 0.2f, 2.8f, 12, 12);
      glPopMatrix();

      //triangle fan for bottom of leg 2
      glPushMatrix();
         glTranslatef(-0.5, 0.0, 5.05);
         glBegin(GL_TRIANGLE_FAN);
         glNormal3f(0.0f, 0.0f, 1.0f);
         glVertex3f(0.0f, 0.0f, 0.0f);
         sections = 12;
         for(int i = 0; i <= sections; ++i) {
            fan_angle = (GLfloat) i * 2 * PI / sections;
            glVertex3f(0.2*cosf(fan_angle), 0.2*sinf(fan_angle), 0.0f);
         }
         glEnd();
      glPopMatrix();

   glPopMatrix();

   glEndList();
}