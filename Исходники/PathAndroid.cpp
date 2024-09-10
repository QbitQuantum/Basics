static float fast_mod(float angle, float max) {
    if (angle >= max || angle <= -max) {
        angle = fmodf(angle, max); 
    }
    return angle;
}