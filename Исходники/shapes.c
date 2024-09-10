/*
 *  cylinder
 *  ------
 *  Draw a cylinder
 *     at (x, y, z)
 *     with radius r and height h
 */
void cylinder(double x,double y,double z,
	      double r,double h)
{
  int i,k;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,currentTexture);
  glPushMatrix();

  /*  Transformation */
  glTranslated(x,y,z);
  glScaled(r,h,r);
  /*  sides */
  glBegin(GL_QUAD_STRIP);
  for (k=0;k<=360;k+=DEF_D) {
    glNormal3f(Cos(k),0,Sin(k));
    // TODO: fix these textures
    glTexCoord2f(-Cos(k),Sin(k));
    glVertex3f(Cos(k),+1,Sin(k));

    glTexCoord2f(Cos(k),Sin(k));
    glVertex3f(Cos(k),-1,Sin(k));
  }
  glEnd();

  /* top and bottom circles */
  /* reuse the currentTexture on top and bottom) */
  for (i=1;i>=-1;i-=2) {
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,i,0);
    glTexCoord2f(0.5,0.5);
    glVertex3f(0,i,0);
    for (k=0;k<=360;k+=DEF_D) {
      glTexCoord2f(0.5*Cos(k)+0.5,0.5*Sin(k)+0.5);
      glVertex3f(i*Cos(k),i,Sin(k));
    }
    glEnd();
  }

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}