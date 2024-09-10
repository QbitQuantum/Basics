CoordinateFrame CoordinateFrame::lerp(
    const CoordinateFrame&  other,
    float                   alpha) const {
    if(alpha == 1.0f) {
        return other;
    } else if(alpha == 0.0f) {
        return *this;
    } else {
        const Quat q1(this->rotation);
        const Quat q2(other.rotation);

        return CoordinateFrame(
            q1.slerp(q2, alpha).toRotationMatrix(),
            translation * (1 - alpha) + other.translation * alpha);
    }
}