void Surfel::BuildFromVertices (
    const Vertex&       iA,
    const Vertex&       iB,
    const Vertex&       iC,
    const Vec3Df&       iTranslation
) {
    // Edge eX is opposed to vertex X.
    Vec3Df eA = iC.getPos () - iB.getPos ();
    Vec3Df eB = iC.getPos () - iA.getPos ();
    Vec3Df eC = iA.getPos () - iB.getPos ();

    float a = eA.getLength ();
    float b = eB.getLength ();
    float c = eC.getLength ();
    
    eA.normalize ();
    eB.normalize ();
    eC.normalize ();
   
    // The perimeter of the triangle.
    float p = (a + b + c);
    // The semiperimeter of the triangle.
    float s = 0.5f * p;
    // The area of the triangle.
    float k = sqrt ( s * ( s - a ) * ( s - b ) * ( s - c ) );
    
    // The surfel radius equals the radius of the circle inscribed
    // in the triangle defined by vertices iA, iB and iC.
    m_radius = k / s;

    // The surfel's position is defined by the center of the inscribed
    // circle, which is subsequently defined by the intersection point
    // of the angle bisections.
    m_position  = a * iA.getPos () 
                + b * iB.getPos () 
                + c * iC.getPos ();
    m_position /= p;
    m_position += iTranslation;

    // We interpolate the normals the same way.
    m_normal    = a * iA.getNormal () 
                + b * iB.getNormal () 
                + c * iC.getNormal ();
    m_normal   /= p;
}