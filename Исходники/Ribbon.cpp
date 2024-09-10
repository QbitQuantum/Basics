void Ribbon::draw()
{
	Vec2i	normPos1, normPos2;
	normPos1 = Vec2f::zero();
	normPos2 = Vec2f::zero();
	
	for(list<RibbonParticle *>::iterator p = mParticles.begin(); p != mParticles.end(); ++p){
		
		int x1 = (*p)->mPos.x - (*p)->mVel.x;
		int x2 = (*p)->mPos.x;
		int y1 = (*p)->mPos.y - (*p)->mVel.y;
		int y2 = (*p)->mPos.y;
		
		// Capture the previous normal positions
		Vec2i prevNormPos1(normPos1);
		Vec2i prevNormPos2(normPos2);
		
		// If this is the first segment, make the normals the 
		// same as the position (we want it to taper in)		
		if(prevNormPos1 == Vec2i::zero() &&
		   prevNormPos2 == Vec2i::zero()){
			
			normPos1 = Vec2i(x1, y1);
			normPos2 = Vec2i(x2, y2);
			
			prevNormPos1 = normPos1;
			prevNormPos2 = normPos2;
			
		}else{
			
			int normX1 = (*p)->mPos.x - ((*p)->mVelNormal.x * 0.5);
			int normX2 = (*p)->mPos.x + ((*p)->mVelNormal.x * 0.5);
			int normY1 = (*p)->mPos.y - ((*p)->mVelNormal.y * 0.5);
			int normY2 = (*p)->mPos.y + ((*p)->mVelNormal.y * 0.5);
			normPos1 = Vec2i(normX1,normY1);
			normPos2 = Vec2i(normX2,normY2);			
			
		}
		
		// Draw the shape between the normals
		Path2d path;		
		path.moveTo(prevNormPos1.x, prevNormPos1.y);
		path.lineTo(normPos1.x, normPos1.y);
		path.lineTo(normPos2.x, normPos2.y);
		path.lineTo(prevNormPos2.x, prevNormPos2.y);
		path.close();
		
		//		float value = ((*p)->mAge / 200.0);
		
		// Draw the filled ribbon
        // Defaults to yellow
        float red = 1.0;
        float green = 1.0;
        float blue = 0.5;
        if(mAgeConnectedAt > 0){
            int lastConnected = mAge - mAgeConnectedAt;
            if(lastConnected < 20){
				if(mCapturedGoal){
					red = lastConnected * 0.05;
				}else{
					green = lastConnected * 0.05;
				}
				blue = lastConnected * 0.025;
            }
        }
		gl::color(Color(red,green,blue));
		gl::drawSolid(path);
		
        /*
		 // Draw the surface normal
		 gl::color(Color(1.0-value,0,0));
		 gl::drawLine(normPos1, normPos2);
		 
		 // Draw a line indicating it's position w/ velocity
		 gl::color(Color::black());
		 gl::drawLine(Vec2i(x1,y1), Vec2i(x2, y2));		
		 */
		
	}
}