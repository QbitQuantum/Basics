void 
display(void)
{
    static int time = 0;
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
#define RAD(x) (((x)*M_PI)/180.)
    gluLookAt(-sinf(RAD(rotx)) * 5.5, transy, cosf(RAD(rotx)) * 5.5, 0., 0., 0., 0., 1., 0.);

    /*
     * floor 
     */
    glColor4f(0.f, .2f, 0.f, 1.f);
    glBegin(GL_POLYGON);
    glVertex3f(-4.0, -1.0, -4.0);
    glVertex3f(4.0, -1.0, -4.0);
    glVertex3f(4.0, -1.0, 4.0);
    glVertex3f(-4.0, -1.0, 4.0);
    glEnd();

    glEnable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(.3f, .3f, .3f);
    glPushMatrix();
    glTranslatef(-1.f, -1.f + .2f, -1.5f);
    glScalef(.2f, .2f, .2f);

    /*
     * the box 
     */
    for (i = 0; i < 10; i++) {
	float ax = (corners[3 * i][0] + corners[3 * i + 1][0] + corners[3 * i + 2][0]) / 3,
	      ay = (corners[3 * i][1] + corners[3 * i + 1][1] + corners[3 * i + 2][1]) / 3,
	      az = (corners[3 * i][2] + corners[3 * i + 1][2] + corners[3 * i + 2][2]) / 3;

	glPushMatrix();
	glTranslatef(ax, ay, az);
	glRotatef(omega[i] * delta, axes[i][0], axes[i][1], axes[i][2]);
	glTranslatef(-ax, -ay, -az);

	glBegin(GL_TRIANGLES);
	glNormal3fv(normals[i]);
	glVertex3fv(corners[3 * i]);
	glVertex3fv(corners[3 * i + 1]);
	glVertex3fv(corners[3 * i + 2]);
	glEnd();

	glPopMatrix();
    }

    /*
     * base of the box (stays there) 
     */
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();
    glPopMatrix();
    glDisable(GL_LIGHTING);


    glTranslatef(-1.f, -1.f, -1.5f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texnames[1]);
    glDepthMask(0);

#if 0
    for (i = smokes - 1; i >= 0; i--) {
	int t = smoke[i];

	glPushMatrix();
	glTranslatef(0.05 * sin(M_PI * (t + time) / 64.0), 0.02 * t, 0.05 * cos(M_PI * (t + time) / 64.0));

	glScalef((t + 60) / MAX_TIME, (t + 60) / MAX_TIME, 1.0);

	glColor4f(0.2, 0.2, 0.2, 10.0 / t);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1.0, 0.0, -1.0);
	glTexCoord2f(1, 0);
	glVertex3f(1.0, 0.0, -1.0);
	glTexCoord2f(1, 1);
	glVertex3f(1.0, 0.0, 1.0);
	glTexCoord2f(0, 1);
	glVertex3f(-1.0, 0.0, 1.0);
	glEnd();
	glPopMatrix();

	smoke[i]++;
    }
#endif
    time++;
    glDisable(GL_TEXTURE_2D);

    glDisable(GL_DEPTH_TEST);
    exploder(0.f, 0.f, 0.f, size, intensity, opacity, 0.f, 3.f);

    exploder(0.f, 0.f, 1.f, size, intensity, opacity, .2f, 1.4f);

    exploder(0.f, .8f, 1.4f, size, intensity, opacity, .4f, 1.6f);

    exploder(0.f, 1.2f, 0.f, size - .4f, intensity, opacity, .4f, 2.f);

    exploder(1.6f, .3f, 0.f, size - 1.f, intensity, opacity, .5f, 3.f);
    glEnable(GL_DEPTH_TEST);


    glDepthMask(1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}