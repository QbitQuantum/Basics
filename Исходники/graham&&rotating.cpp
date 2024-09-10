double PToL(Point a, Point b, Point c) {
        Point e = (b-c).rot();
        if( sign(e.cross(c-a)*e.cross(b-a)) <= 0 ) {
                return fabs( e.dot(c-a)/e.abs() );
        }
        return min( (b-a).abs(), (c-a).abs() );
}