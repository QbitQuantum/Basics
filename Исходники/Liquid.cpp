// Calculate drag force
Vec2f Liquid::drag( const Mover &m ) {
    // Magnitude is coefficient * speed squared
    float speed = m.mVelocity.length();
    float dragMagnitude = mC * speed * speed;
	
    // Direction is inverse of velocity
    Vec2f dragForce = Vec2f( m.mVelocity );
    dragForce *= -1;
    
    // Scale according to magnitude
    // dragForce.setMag(dragMagnitude);
    dragForce.normalize();
    dragForce *= dragMagnitude;
    return dragForce;
}