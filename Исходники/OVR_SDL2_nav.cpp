void OVR_SDL2_nav::game_axis(int device, int axis, float value)
{
    float k = copysignf(value * value, value);

    switch (axis)
    {
        case SDL_CONTROLLER_AXIS_LEFTX:
            dposition[0] = (fabsf(k) > 0.1f) ? k : 0.0f;
            break;
        case SDL_CONTROLLER_AXIS_LEFTY:
            dposition[2] = (fabsf(k) > 0.1f) ? k : 0.0f;
            break;
        case SDL_CONTROLLER_AXIS_RIGHTX:
            drotation    = (fabsf(k) > 0.1f) ? k : 0.0f;
            break;
    }
}