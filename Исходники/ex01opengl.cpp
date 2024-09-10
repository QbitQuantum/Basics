//
//  Draw the window
//
void Ex01opengl::paintGL()
{
   //  Wall time (seconds)
   float t = 0.001*time.elapsed();

   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //  Set view
   glLoadIdentity();
   if (fov) glTranslated(0,0,-2*dim);
   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);

   //  Enable lighting
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]  = {0.3,0.3,0.3,1.0};
      float Diffuse[]  = {0.8,0.8,0.8,1.0};
      float Specular[] = {1.0,1.0,1.0,1.0};
      float Position[] = {(float)(3*Cos(90*t)),3.0,(float)(3*Sin(90*t)),1.0};
      //  Draw light position (no lighting yet)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }

   //  Apply shader
   if (mode)
   {
      shader.bind();
      shader.setUniformValue("time",t);
   }

   //  Draw scene
   if (obj) obj->display();

   //  Release shader
   if (mode) shader.release();

   //  Disable lighting
   glDisable(GL_LIGHTING);
   
   //  Draw Axes
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3d(0,0,0);
   glVertex3d(1,0,0);
   glVertex3d(0,0,0);
   glVertex3d(0,1,0);
   glVertex3d(0,0,0);
   glVertex3d(0,0,1);
   glEnd();

   //  Emit angles to display
   emit angles(QString::number(th)+","+QString::number(ph));
}