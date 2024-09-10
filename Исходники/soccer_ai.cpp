/** Used in \ref determineOvertakePosition to adjust the overtake position
 *  which is calculated by slope of line if it's too close.
 *  \param old_slope Old slope calculated.
 *  \param rotate_up If adjust the slope upwards.
 *  \return A newly calculated slope.
 */
float SoccerAI::rotateSlope(float old_slope, bool rotate_up)
{
    const float theta = atanf(old_slope) + (old_slope < 0 ? M_PI : 0);
    float new_theta = theta + (rotate_up ? M_PI / 6 : -M_PI /6);
    if (new_theta > ((M_PI / 2) - 0.02f) && new_theta < ((M_PI / 2) + 0.02f))
    {
        // Avoid almost tan 90
        new_theta = (M_PI / 2) - 0.02f;
    }
    // Check if over-rotated
    if (new_theta > M_PI)
        new_theta = M_PI - 0.1f;
    else if (new_theta < 0)
        new_theta = 0.1f;

    return tanf(new_theta);
}   // rotateSlope