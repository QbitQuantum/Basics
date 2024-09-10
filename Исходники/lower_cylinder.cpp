void create_sloping_cylinder(GLfloat* matrix)
{
    // GLfloat h = 2.03125;
    // GLfloat length = 1;
    glLoadIdentity();
    // setEye();
    glLoadMatrixf(matrix);
    int th2, ph2, i, j, k;
    double height=0.5;
    double radius=0.40710678118;
    glBegin(GL_QUAD_STRIP);
    for (j=0;j<=360;j+=DEF_D) 
    {
         // glColor3f(0,1,0);
      if(j>=90 && j<=270)
      {
        glNormal3f(-Cos(j),0,-Sin(j));
        glVertex3f((radius)*Cos(j),0,(radius)*Sin(j));
        glVertex3f((radius)*Cos(j),-2*height,(radius)*Sin(j));
      }
      else
      {
        glNormal3f(-Cos(j),0,-Sin(j));
        glVertex3f((radius)*Cos(j),-2*height+1-Cos(j)*2*height,(radius)*Sin(j));
        glVertex3f((radius)*Cos(j),-2*height,(radius)*Sin(j));
        
      }
    }
    glEnd();
    glBegin(GL_QUAD_STRIP);
    for (k=0;k<=360;k+=DEF_D) 
    {
      
        glNormal3f(0,-1,0);   
        glVertex3f((radius)*Cos(k),-2*height,(radius)*Sin(k));
        glNormal3f(0,-1,0);   
        glVertex3f((radius-0.0625)*Cos(k),-2*height,(radius-0.0625)*Sin(k));
      
    }
    glEnd();
}