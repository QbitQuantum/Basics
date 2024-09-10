Quat slerp(const Quat& b, const Quat& e, float proportion) {
    Quat temp = b;
    Quat tempEnd = e;

    temp.slerp(tempEnd, proportion);

    return temp;
}