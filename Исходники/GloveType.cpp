// GetSecondAngleAxis looks for the axis defined by the pointer finger
// And the left base
bool GloveType::GetBothAxes(int i) {
    if (!GetFirstAxis(i)) return false;
    if (axis_points2_.size() == 2) {
        // Check the first Axis validity
        if (base_left_->current_ == 0 || base_right_->current_ == 0) {
            return false;
        }
        /*check second axis*/
        Point u;
        if (fore_->current_ == 0) {
            return false;
        } else {
            u = fore_->Sub(*base_left_);
        }
        Point v = fore_->Sub(*base_left_);
        axis2_ = u.Sub(v.Normalize().Times(u.Dot(v))).Normalize();
        // Now find the normal component
        return true;
    } else {
        if (base_left_->current_ == 0 || fore_->current_ == 0) return false;
        axis_points2_.push_back(fore_);
        axis_points2_.push_back(base_left_);
        Point v = fore_->Sub(*base_left_);
        axis2_ =  v.Sub(axis1_.Times(v.Dot(axis1_))).Normalize();
        Point y_axis;
        y_axis.Init(0, 1, 0);
        original_axis2_ = y_axis;
        return true;
    }
}