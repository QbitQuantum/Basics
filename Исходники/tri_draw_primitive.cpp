void drawSegment(
    const Segment& Segment,
    const Color& color,
    const float width
) {
    
    const Vec3* a = Segment.getPointA();
    const Vec3* b = Segment.getPointB();
    
    Vec3 ba = *b - *a;
    Vec3 cross(0,1,0);
    if (isZeroFloat(ba.x_) && isZeroFloat(ba.z_)) {
        //  完全に垂直
        cross = Vec3(1,0,0);
    }

    Vec3 offset = ba.crossProduct(cross);
    offset.normalize();
    
    offset *= width;
//    Vec3 c = *a + offset;
//    Vec3 d = *b + offset;
    
}