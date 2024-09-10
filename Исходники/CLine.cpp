bool Line::Intersects(const Rectangle& rectangle) const {

    if(this->IsVertical()) {
        double Xr = rectangle.GetX();
        double Xrw = rectangle.GetWidth();
        double Xl = _extent_one.GetX();
        if(Xr > Xl) return false;
        double Xrb = Xr + Xrw;
        if(Xrb < Xl) return false;
        return true;
    } else if(this->IsHorizontal()) {
        double Yr = rectangle.GetY();
        double Yrh = rectangle.GetHeight();
        double Yl = _extent_one.GetY();
        if(Yr > Yl) return false;
        double Yrb = Yr + Yrh;
        if(Yrb < Yl) return false;
        return true;
    }

    double eOne_x = _extent_one.GetX();
    double eOne_y = _extent_one.GetY();
    double eTwo_x = _extent_two.GetX();
    double eTwo_y = _extent_two.GetY();
    double rTop = rectangle.GetY();
    double rLeft = rectangle.GetX();
    double rRight = rLeft + rectangle.GetWidth();
    double rBottom = rTop + rectangle.GetHeight();

    bool point_one_result = eOne_x > rLeft && eOne_x < rRight && eOne_y > rTop && eOne_y < rBottom;
    bool point_two_result = eTwo_x > rLeft && eTwo_x < rRight && eTwo_y > rTop && eTwo_y < rBottom;
    if(point_one_result || point_two_result) return true;

    bool result = Intersects(rectangle.GetTop()) ||
                  Intersects(rectangle.GetLeft()) ||
                  Intersects(rectangle.GetRight()) ||
                  Intersects(rectangle.GetBottom());
    return result;
}