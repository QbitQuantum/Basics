void Attractor::hover( const Vec2f& mouse ) {
    float d = mouse.distance( location );
    if (d < mass) {
        rollover = true;
    } else {
        rollover = false;
    }
}