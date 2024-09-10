void drawCircle(float x, float y, float r, int segments) 
{ 
	float xi = x;
	float yi = y;

	double angle = 2*3.1415/segments;  
    glBegin(GL_POLYGON);  
     {  
         for (int i=1; i<=segments; i++)  
         {  
			 xi= x + r*cos(i * angle);  

             yi= y + r*sin(i * angle);     

				 
                 cvs.lineTo(xi, yi);  
             
         }  
     }  
     glEnd();  
} 