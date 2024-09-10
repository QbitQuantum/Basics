 void drawTriangle(float xSize, float ySize){
   Vector3F p[3];
   glBegin(GL_TRIANGLES);
   p[0] << 0., 0., 0.;
   p[1] << -xSize, ySize, 0.;
   p[2] << -xSize, -ySize, 0.;
   for (int i = 1; i < 2; ++i) {
     Vector3F normal = (p[i] - p[0]).cross(p[i+1] - p[0]);
     glNormal3f(normal.x(), normal.y(), normal.z());
     glVertex3f(p[0].x(), p[0].y(), p[0].z());
     glVertex3f(p[i].x(), p[i].y(), p[i].z());
     glVertex3f(p[i+1].x(), p[i+1].y(), p[i+1].z());
   }    
   glEnd();
 }