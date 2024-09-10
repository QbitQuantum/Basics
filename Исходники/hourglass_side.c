void hourglass_side(float thy,unsigned int glass_tex) {
  // Materials
  float white[] = {221.0/255.0,213.0/255.0,242.0/255.0,1};
  float shinyvec[1];
  shinyvec[0] = 16.0;
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);

  glPushMatrix();

  // Transforms
  glRotated(thy,0,1,0);

  // Texture
  glEnable(GL_TEXTURE_2D);
  glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
  glBindTexture(GL_TEXTURE_2D,glass_tex);

  // Color
  glColor4f(.1,.1,.1,.8);

  // Enable blend for transparency
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_SRC_ALPHA);

  const double pi2 = M_PI;
  const double costhy = Cos(thy);
  const double costhyp = Cos(thy+1);
  const double sinthy = Sin(thy);
  const double sinthyp = Sin(thy);

  double i;
  double delta = pi2 / 51.5;
  glBegin(GL_QUADS);
  for (i=0.0;i<=pi2;i+=delta) {
  	double x0 = cos(i);
  	double x1 = cos(i+delta);
  	double ny0 = -sin(i);
  	double ny1 = -sin(i+delta);
    // Upper left
    glNormal3f(costhy,ny1,sinthy);
    glTexCoord2f(costhy,(i+delta)/pi2);
    glVertex3f(x1,(i+delta)/pi2,.03);
    // Upper right
    glNormal3f(costhyp,ny1,sinthyp);
    glTexCoord2f(costhyp,(i+delta)/pi2);
    glVertex3f(x1,(i+delta)/pi2,-.03);
    // Lower Right
    glNormal3f(costhyp,ny0,sinthyp);
    glTexCoord2f(costhyp,i/pi2);
    glVertex3f(x0,i/pi2,-.03);
    // Lower left
    glNormal3f(costhy,ny0,sinthy);
    glTexCoord2f(costhy,i/pi2);
    glVertex3f(x0,i/pi2,.03);
  }
  glEnd();

  glDisable(GL_BLEND);

  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}