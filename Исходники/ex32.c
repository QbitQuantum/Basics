/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   int i,j;
   const double len=2.0;  //  Length of axes
   //  Light position and colors
   float Ambient[]  = {0.3,0.3,0.3,1.0};
   float Diffuse[]  = {1.0,1.0,1.0,1.0};
   float Position[] = {Cos(zh),Ylight,Sin(zh),1.0};

   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (proj)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   //  Draw light position as sphere (still no lighting here)
   glColor3f(1,1,1);
   glPushMatrix();
   glTranslated(Position[0],Position[1],Position[2]);
   glutSolidSphere(0.03,10,10);
   glPopMatrix();
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
   glLightfv(GL_LIGHT0,GL_POSITION,Position);

   //  Draw floor
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   glColor3f(1,1,1);
   glNormal3f(0,1,0);
   for (j=-Dfloor;j<Dfloor;j++)
   {
      glBegin(GL_QUAD_STRIP);
      for (i=-Dfloor;i<=Dfloor;i++)
      {
         glTexCoord2f(i,j); glVertex3f(i,Yfloor,j);
         glTexCoord2f(i,j+1); glVertex3f(i,Yfloor,j+1);
      }
      glEnd();
   }
   glDisable(GL_POLYGON_OFFSET_FILL);
   glDisable(GL_TEXTURE_2D);

   //  Draw scene
   glColor3f(1,1,0);
   scene();

   //  Save what is glEnabled
   glPushAttrib(GL_ENABLE_BIT);
   //  Draw shadow
   switch (mode)
   {
      //  No shadow
      case 0:
         break;
      //  Draw flattened scene
      case 1:
         glPushMatrix();
         ShadowProjection(Position,E,N);
         scene();
         glPopMatrix();
         break;
      //  Transformation with lighting disabled
      case 2:
         glDisable(GL_LIGHTING);
         //  Draw flattened scene
         glPushMatrix();
         ShadowProjection(Position,E,N);
         scene();
         glPopMatrix();
         break;
      //  Set shadow color
      case 3:
         glDisable(GL_LIGHTING);
         glColor3f(0.3,0.3,0.3);
         //  Draw flattened scene
         glPushMatrix();
         ShadowProjection(Position,E,N);
         scene();
         glPopMatrix();
         break;
      //  Blended shadows
      case 4:
         glDisable(GL_LIGHTING);
         //  Blended color
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
         glColor4f(0,0,0,0.4);
         //  Draw flattened scene
         glPushMatrix();
         ShadowProjection(Position,E,N);
         scene();
         glPopMatrix();
         break;
      //  Blended shadows Z-buffer masked
      case 5:
         glDisable(GL_LIGHTING);
         //  Draw blended 
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
         glColor4f(0,0,0,0.4);
         //  Make Z-buffer read-only
         glDepthMask(0);
         //  Draw flattened scene
         glPushMatrix();
         ShadowProjection(Position,E,N);
         scene();
         glPopMatrix();
         //  Make Z-buffer read-write
         glDepthMask(1);
         break;
      //  Blended with stencil buffer
      case 6:
         glDisable(GL_LIGHTING);
         //  Enable stencil operations
         glEnable(GL_STENCIL_TEST);

         /*
          *  Step 1:  Set stencil buffer to 1 where there are shadows
          */
         //  Existing value of stencil buffer doesn't matter
         glStencilFunc(GL_ALWAYS,1,0xFFFFFFFF);
         //  Set the value to 1 (REF=1 in StencilFunc)
         //  only if Z-buffer would allow write
         glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
         //  Make Z-buffer and color buffer read-only
         glDepthMask(0);
         glColorMask(0,0,0,0);
         //  Draw flattened scene
         glPushMatrix();
         ShadowProjection(Position,E,N);
         scene();
         glPopMatrix();
         //  Make Z-buffer and color buffer read-write
         glDepthMask(1);
         glColorMask(1,1,1,1);

         /*
          *  Step 2:  Draw shadow masked by stencil buffer
          */
         //  Set the stencil test draw where stencil buffer is > 0
         glStencilFunc(GL_LESS,0,0xFFFFFFFF);
         //  Make the stencil buffer read-only
         glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
         //  Enable blending
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
         glColor4f(0,0,0,0.5);
         //  Draw the shadow over the entire floor
         glBegin(GL_QUADS);
         glVertex3f(-Dfloor,Yfloor,-Dfloor);
         glVertex3f(+Dfloor,Yfloor,-Dfloor);
         glVertex3f(+Dfloor,Yfloor,+Dfloor);
         glVertex3f(-Dfloor,Yfloor,+Dfloor);
         glEnd();
         break;
      default:
         break;
   }    
   //  Undo glEnables
   glPopAttrib();
   
   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
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
   Print("Angle=%d,%d  Dim=%.1f Projection=%s Light Elevation=%.1f",
     th,ph,dim,proj?"Perpective":"Orthogonal",Ylight);
   glWindowPos2i(5,25);
   Print(text[mode]);
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}