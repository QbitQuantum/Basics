float Dot::whichSide(Dot a, Dot b){
    float xa = a.getX();
    float ya = a.getY();
    float xb = b.getX();
    float yb = b.getY();

    return (xa*yb - ya*xb + y*(xb-xa) + x*(ya-yb));
}