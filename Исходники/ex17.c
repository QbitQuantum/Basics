/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Length of axes
   const double len=1.2;
   //  Eye position
   double Ex = -2*dim*Cos(ph);
   double Ey = +2*dim*Sin(ph);
   double Ez = 0;
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Set perspective
   glLoadIdentity();
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   //  Draw scene
   glEnable(GL_DEPTH_TEST);
   //  Rotate Z up
   glRotated(-90,1,0,0);

   /*
    * Draw solar system
    */
   if (mode<0)
   {
      glRotated(th,0,0,1);  //  View angle
      SolarSystem();
   }
   /*
    *  Draw planet
    */
   else
   {
      glRotated(th,1,0,0);  // Declination
      glRotated(zh,0,0,1);  // Spin around axes
      DrawPlanet(mode);
   }

   /*
    *  Draw axes - no textures from here
    */
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f Object=%s",th,ph,2*dim,mode<0?"Solar System":planet[mode].name);
   if (mode<0) Print(" Magnification %d Year %.1f",mag,2000+day/365.25);
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}