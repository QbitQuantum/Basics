void GfxRend::
LineStripRender( float *xCoordinates, float *yCoordinates, int numCoordinates, Rgba *cols,
                 float lineWidth, bool singleColor, bool useSideColors,
                 Rgba leftCol, Rgba rightCol ) {
   if( singleColor )
      cols->Select();
   else
      cols[0].Select();
   
   glDisable( GL_TEXTURE_2D );
   
   // Find the normal of the beginning of the strip //
   
   float lastX = xCoordinates[0];
   float lastY = yCoordinates[0];
   
   float lastSx = xCoordinates[1] - lastX;
   float lastSy = yCoordinates[1] - lastY;
   
   float lastSLength = sqrt( lastSx * lastSx + lastSy * lastSy );
   
   lastSx /= lastSLength;
   lastSy /= lastSLength;
   
   float lastUpperX = lastX + lastSy * lineWidth;
   float lastUpperY = lastY - lastSx * lineWidth;
   
   float lastLowerX = lastX - lastSy * lineWidth;
   float lastLowerY = lastY + lastSx * lineWidth;
   
   // Render the begin of the strip //
   
   if( !useSideColors ) {
      glBegin( GL_QUAD_STRIP );
         glVertex2f( lastUpperX, lastUpperY );
         glVertex2f( lastLowerX, lastLowerY );
   }
   
   for( int i = 1; i < numCoordinates-1; i++ ) {
      float x = xCoordinates[i];
      float y = yCoordinates[i];
      
      if( x == lastX && y == lastY ) {
         continue;
      }
      
      // Find the direction vector from the next point to the current one //
      
      float bx = x - xCoordinates[i+1];
      float by = y - yCoordinates[i+1];
      
      float bLength = sqrt( bx * bx + by * by );
      
      if( bLength > -OL_NEAR_ZERO && bLength < OL_NEAR_ZERO ) {
         continue;
      }
      
      bx /= bLength;
      by /= bLength;
      
      // Find the direction vector of the displacement //
      
      float cx = lastSx + bx;
      float cy = lastSy + by;
      
      float cLength = sqrt( cx * cx + cy * cy );
      
      float nx, ny;
      
      if( cLength > -OL_NEAR_ZERO && cLength < OL_NEAR_ZERO ) {
         nx = -by;
         ny = bx;
         
         float nRatio = lineWidth/sqrt( nx * nx + ny * ny );
         
         nx *= nRatio;
         ny *= nRatio;
      }
      else {
         cx /= cLength;
         cy /= cLength;
      
         // Make sure that the displacement happens always in the same side //
         
         float diff1 = lastSx - bx;
         float diff2 = lastSy - by;
         float diff3 = cx - bx;
         float diff4 = cy - by;
         
         if(( diff1 * diff4 ) - ( diff2 * diff3 ) > 0) {
            cx = -cx;
            cy = -cy;
         }
         
         // Find the displacement multiplicator //
         
         float s = lastSy * cx + (-lastSx) * cy;
         
         nx = cx * lineWidth / s;
         ny = cy * lineWidth / s;
      }
      
      // Find the displaced coordinates //
      
      float upperX = x + nx;
      float upperY = y + ny;
      
      float lowerX = x - nx;
      float lowerY = y - ny;
      
      
      if( !useSideColors ) {
         if( !singleColor )
            cols[i].Select();
         
         glVertex2f( upperX, upperY );
         glVertex2f( lowerX, lowerY );
      }
      else {
         glBegin( GL_QUAD_STRIP );
            // Upper side //
            leftCol.Select();
            glVertex2f( lastUpperX, lastUpperY );
            glVertex2f( upperX, upperY );
            
            // Middle //
            if( !singleColor )
               cols[i-1].Select();
            else
               cols->Select();
            
            glVertex2f( lastX, lastY );
            
            if( !singleColor )
               cols[i].Select();
            
            glVertex2f( x, y );
            
            // Lower side //
            rightCol.Select();
            glVertex2f( lastLowerX, lastLowerY );
            glVertex2f( lowerX, lowerY );
         glEnd();
      }
      
      // Store the information which can be used when calculating the next point //
      
      lastX = x;
      lastY = y;
      
      lastSx = -bx;
      lastSy = -by;
      
      lastUpperX = upperX;
      lastUpperY = upperY;
      
      lastLowerX = lowerX;
      lastLowerY = lowerY;
   }
   
   // Render the end of the strip //
   
   int lastIndex = numCoordinates-1;
   
   float x = xCoordinates[lastIndex];
   float y = yCoordinates[lastIndex];
   
   float upperX = x + lastSy * lineWidth;
   float upperY = y - lastSx * lineWidth;
   
   float lowerX = x - lastSy * lineWidth;
   float lowerY = y + lastSx * lineWidth;
   
   if( !useSideColors ) {
         if( !singleColor )
            cols[lastIndex].Select();
         
         glVertex2f( upperX, upperY );
         glVertex2f( lowerX, lowerY );
      
      glEnd();
   }
   else {
      glBegin( GL_QUAD_STRIP );
         // Upper side //
         leftCol.Select();
         glVertex2f( lastUpperX, lastUpperY );
         glVertex2f( upperX, upperY );
         
         // Middle //
         if( !singleColor )
            cols[lastIndex-1].Select();
         else
            cols->Select();
         
         glVertex2f( lastX, lastY );
         
         if( !singleColor )
            cols[lastIndex].Select();
         
         glVertex2f( x, y );
         
         // Lower side //
         rightCol.Select();
         glVertex2f( lastLowerX, lastLowerY );
         glVertex2f( lowerX, lowerY );
      glEnd();
   }
   
   if( Settings::TextureMappingUsed() )
      glEnable( GL_TEXTURE_2D );
}