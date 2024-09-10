// inverse kinematics
// helper functions, calculates angle theta1 (for YZ-pane)
int RotaryDeltaSolution::delta_calcAngleYZ(float x0, float y0, float z0, float &theta)
{
    float y1 = -0.5F * tan30 * delta_f; // f/2 * tan 30
    y0      -=  0.5F * tan30 * delta_e; // shift center to edge
    // z = a + b*y
    float a = (x0 * x0 + y0 * y0 + z0 * z0 + delta_rf * delta_rf - delta_re * delta_re - y1 * y1) / (2.0F * z0);
    float b = (y1 - y0) / z0;

    float d = -(a + b * y1) * (a + b * y1) + delta_rf * (b * b * delta_rf + delta_rf); // discriminant
    if (d < 0.0F) return -1;                                            // non-existing point

    float yj = (y1 - a * b - sqrtf(d)) / (b * b + 1.0F);               // choosing outer point
    float zj = a + b * yj;

    theta = 180.0F * atanf(-zj / (y1 - yj)) / pi + ((yj > y1) ? 180.0F : 0.0F);
    return 0;
}