void Bond::drawWireFrame(bool selected) 
{
   GLfloat radius(s_radiusWireFrame*m_scale);

   Vec a(m_begin->displacedPosition());
   Vec b(m_end  ->displacedPosition());
   GLfloat length((a-b).norm());

   glPushMatrix();
   glMultMatrixd(m_frame.matrix());

   GLboolean lightingEnabled(glIsEnabled(GL_LIGHTING));
   glDisable(GL_LIGHTING);

   if (!selected) {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_LINE_SMOOTH);
   }

   Vec normal = cross(s_cameraPosition-a, s_cameraPosition-b);
   normal.normalize();

   a.setValue(0.0, 0.0, 0.0); 
   b.setValue(0.0, 0.0, length); 
   Vec m(0.5*(a+b)); // bond midpoint

   if (selected) {

      glColor4fv(Primitive::s_selectColor);
      radius += Primitive::s_selectOffsetWireFrame;
      glLineWidth(radius);
      glBegin(GL_LINES);
         glVertex3f(a.x, a.y, a.z); 
         glVertex3f(b.x, b.y, b.z); 
      glEnd();

   }else {

      glLineWidth(radius);
   
      switch (m_order) {
         case 2: 
            normal *= 0.03;  // Governs the offset for the bond lines
            glBegin(GL_LINES);
               a -= normal;
               b -= normal;
               m -= normal;
               glColor4fv(m_begin->m_color);
               glVertex3f(a.x, a.y, a.z); 
               glVertex3f(m.x, m.y, m.z); 
               glColor4fv(m_end->m_color);
               glVertex3f(m.x, m.y, m.z); 
               glVertex3f(b.x, b.y, b.z); 

               a += 2.0*normal;
               b += 2.0*normal;
               m += 2.0*normal;
               glColor4fv(m_begin->m_color);
               glVertex3f(a.x, a.y, a.z); 
               glVertex3f(m.x, m.y, m.z); 
               glColor4fv(m_end->m_color);
               glVertex3f(m.x, m.y, m.z); 
               glVertex3f(b.x, b.y, b.z); 
            glEnd();
         break;

         case 3: 
            normal *= 0.04;  // Governs the offset for the bond lines
            glBegin(GL_LINES);
               a -= normal;
               b -= normal;
               m -= normal;
               glColor4fv(m_begin->m_color);
               glVertex3f(a.x, a.y, a.z); 
               glVertex3f(m.x, m.y, m.z); 
               glColor4fv(m_end->m_color);
               glVertex3f(m.x, m.y, m.z); 
               glVertex3f(b.x, b.y, b.z); 

               a += normal;
               b += normal;
               m += normal;
               glColor4fv(m_begin->m_color);
               glVertex3f(a.x, a.y, a.z); 
               glVertex3f(m.x, m.y, m.z); 
               glColor4fv(m_end->m_color);
               glVertex3f(m.x, m.y, m.z); 
               glVertex3f(b.x, b.y, b.z); 

               a += normal;
               b += normal;
               m += normal;
               glColor4fv(m_begin->m_color);
               glVertex3f(a.x, a.y, a.z); 
               glVertex3f(m.x, m.y, m.z); 
               glColor4fv(m_end->m_color);
               glVertex3f(m.x, m.y, m.z); 
               glVertex3f(b.x, b.y, b.z); 
            glEnd();
         break;

         default: 
            glBegin(GL_LINES);
               glColor4fv(m_begin->m_color);
               glVertex3f(a.x, a.y, a.z); 
               glVertex3f(m.x, m.y, m.z); 
               glColor4fv(m_end->m_color);
               glVertex3f(m.x, m.y, m.z); 
               glVertex3f(b.x, b.y, b.z); 
            glEnd();
         break;
      }
   }

   if (!selected) {
      glDisable(GL_BLEND);
      glDisable(GL_LINE_SMOOTH);
   }
   if (lightingEnabled) glEnable(GL_LIGHTING);

   glPopMatrix();
}