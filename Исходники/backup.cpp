void GL_render()
{
    glClear( GL_COLOR_BUFFER_BIT );
    
    // For each pixel,
    for( int i = 0; i < WINDOW_WIDTH; ++i )
    {
      for( int j = 0; j < WINDOW_HEIGHT; ++j )
      {
		//cout << i << " " << j << " ";
		// Check if there is an intersection between ray and a triangle
		int which_triangle = pixelOn( i, 800 - j );
	
		if( which_triangle >= 0 )
		{
		  Point3D viewer(i, j, 1.0);
	  
		  // We now find the illumination
		  float sum = 0;
	  
		  // For all light sources
		  for( int x = 0; x < 1; ++x )
		  {
		    // We determine if there is a shadow. If so, only add ambient light
		    
		    // If there isn't, add diffuse and specular as well
		    
		    // Phong Illumination Model
		    // L = kd * Ld * cos(theta) + ks * Ls * cos( phi ) + ka * La
		    // cos( theta ) = N * l / (||N|| || L || ), where N = normal vector, L = light
		    
		    // First we find the normal vector of that triangle
		    Point3D p1 = cartesian_points.at( triangles.at( which_triangle ).p1 );  // Get x, y, z
		    Point3D p2 = cartesian_points.at( triangles.at( which_triangle ).p2 );
		    Point3D p3 = cartesian_points.at( triangles.at( which_triangle ).p3 );
		    
		    Point3D vector1 = Point3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);       // Get 2 vectors from pts
		    Point3D vector2 = Point3D(p1.x - p3.x, p1.y - p3.y, p1.z - p3.z);
		    
		    Point3D normal = vector1.cross( vector2 );                        // Find normal from cross
		    
		    // Using the normal, we calculate the diffuse component as Kd * Ld * ( N * l )/(|N||L|)
		    float diffuse = (normal.dot( lights[x] ) / ( normal.magnitude() * lights[x].magnitude() ))*Kd*Ld;
		    
		    // We then find our specular component using the reflected vector from the light source
		    Point3D reflector = normal * 2 * ( normal.dot( (lights[x] / lights[x].magnitude()) ) ) - lights[x];
		    float specular = (reflector.dot( viewer ) / ( reflector.magnitude() * viewer.magnitude() ))*Ks*Ls;
		    
		    // Finally, the ambient component
		    float ambient = Ka * La;
		    
		    // Find the total illumination
		    sum += diffuse + specular + ambient;
	
		  }
	  
	  	// After looping through all light sources, we then render the pixel
	    clr colour = triangles.at( which_triangle ).Color;	  	  
	    renderPixel( i, 800 - j,/*colour.R**/sum, /*colour.G**/sum, /*colour.B**/sum);

	}
      
      }
    }

    // Project 1 way of rendering triangles
    /*// Traverse through points in all polygons
    for( int i = 0; i < triangles.size(); ++i )
    {
        // Grab the 2D projected points and push them to points container
        Point3D temp;
        temp = cartesian_points[ triangles[i].p1 ]; // First point
        points.push_back( Point2D( temp.x, temp.y ) );
        
        temp = cartesian_points[ triangles[i].p2 ]; // Second point
        points.push_back( Point2D( temp.x, temp.y ) );
        
        temp = cartesian_points[ triangles[i].p3 ]; // Third point
        points.push_back( Point2D( temp.x, temp.y ) );
    }
    
    // Go through points container and output pixels
    for( int i = 0; i < points.size()/3; ++i)
    renderTPolygon(i); // Render triangle polygons, based on zbuffer depth as well*/
    
    glutSwapBuffers();
}