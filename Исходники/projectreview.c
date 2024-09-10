static void roadsign()
{
   glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,sky[5]);
   glPushMatrix();
   glBegin(GL_QUADS);
   {
   	glNormal3f(0,0,1);
   	glTexCoord2f(0,1); glVertex3f(-1.5,11.5,0);
   	glTexCoord2f(0,0); glVertex3f(0,10,0);
   	glTexCoord2f(1,0); glVertex3f(1.5,11.5,0);
   	glTexCoord2f(1,1); glVertex3f(0,13,0);
   }
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

   glEnable(GL_TEXTURE_2D);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glPushMatrix();
   glTranslated(0,-1,0);
   glScaled(0.1,11,0.1);
   glBegin(GL_QUAD_STRIP);
   for (th=0;th<=360;th+=15)
   {  glTexCoord2f(Sin(i),0);
      glNormal3f(Cos(th),1,Sin(th));
      glVertex3f(Cos(th),1,Sin(th));
       glTexCoord2f(Sin(i),1);
        glNormal3f(Cos(th),0,Sin(th));
      glVertex3f(Cos(th),0,Sin(th));
   }
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}