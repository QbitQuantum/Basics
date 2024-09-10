static bool is_clockwise(const SkVector& before, const SkVector& after) {
    return before.cross(after) > 0;
}