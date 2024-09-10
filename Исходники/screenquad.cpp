 virtual void render() {
   shd->bind();
   glBindBuffer(GL_ARRAY_BUFFER,buf);
   glVertexAttribPointer(BUFIDX_VERTICES,3,GL_FLOAT,0,0,0);
   glEnableVertexAttribArray(BUFIDX_VERTICES);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glDrawArrays(GL_TRIANGLES,0,sizeof(SCREEN_QUAD_VERTICES)/sizeof(float));
   glDisableVertexAttribArray(BUFIDX_VERTICES);
   
   shd->unbind();
 }