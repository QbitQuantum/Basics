void fountain(unsigned int stone_tex,
	          unsigned int water_tex) {

  const double pi2 = M_PI * 2;
  const double delta = pi2 / 103;
  const double radius = .74;
  double i;

  float white[] = {221.0/255.0,213.0/255.0,242.0/255.0,1};
  float shinyvec[1];
  shinyvec[0] = 64.0;
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);

  glPushMatrix();

  // Transforms
  glScaled(.15,.15,.15);

  // Color of polys
  glColor3f(0.3,0.3,0.3);

  // Cylinder for base
  cylinder(0,0,0,
  	       0,0,
  	       .2,1,
  	       103,stone_tex,
  	       water_tex,
           0);

  // Bowl at base
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,stone_tex);

  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0,1,0);
  glTexCoord2f(.5,.5);
  glVertex3f(0,0,0);
  for (i=0.0;i<=pi2;i+=delta) {
    double x = 1.1 * cos(i);
    double z = 1.1 * sin(i);
    glTexCoord2f(cos(i),sin(i));
    glVertex3f(x,.2,z);
  }
  glEnd();

  glDisable(GL_TEXTURE_2D);

  // Weird shape for body
  for(i=0.0;i<=360;i+=2) {
  	fountain_side(i,stone_tex);
  }

  //water on top
  shinyvec[0] = 4.0;
  glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,water_tex);

  glColor3f(.055,.055,.055);
  glBegin(GL_TRIANGLE_FAN);
  glNormal3f(0,1,0);
  glTexCoord2f(.5,.5);
  glVertex3f(0,1.2,0);
  for (i=0.0;i<=pi2;i+=delta) {
  	double x = radius * cos(i);
  	double z = radius * sin(i);
  	glTexCoord2f(cos(i),sin(i));
    glVertex3f(x,1.27,z);
  }
  glEnd();

  glDisable(GL_TEXTURE_2D);

  // Lotus at the particle emitter
  // big blades
  grass_blade(.25,1.25,.25,
  	          .5,.1666666,.33333333,
  	          90,0,0,
  	          stone_tex);
  grass_blade(-.3,1.25,.25,
  	          .5,.1666666,.33333333,
  	          0,0,0,
  	          stone_tex);
  grass_blade(-.25,1.25,-.3,
  	          .5,.1666666,.33333333,
  	          270,0,0,
  	          stone_tex);
  grass_blade(.3,1.25,-.25,
  	          .5,.1666666,.33333333,
  	          180,0,0,
  	          stone_tex);

  // smaller blades
  grass_blade(.3*Cos(45),1.25,.3*Sin(45),
  	          .3,.1,.2,
  	          45,-20,0,
  	          stone_tex);
  grass_blade(.3*Cos(135)-.2,1.25,.3*Sin(135)-.2,
  	          .3,.1,.2,
  	          -45,-20,0,
  	          stone_tex);
  grass_blade(.3*Cos(225)+.1,1.25,.3*Sin(225)-.1,
  	          .3,.1,.2,
  	          -135,-20,0,
  	          stone_tex);
  grass_blade(.3*Cos(315)+.2,1.25,.3*Sin(315)+.1,
  	          .3,.1,.2,
  	          135,-20,0,
  	          stone_tex);


  glPopMatrix();

}