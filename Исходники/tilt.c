static void
tilt_sanitize_args(TiltArgs *args)
{
    args->dx = CLAMP(args->dx, -100, 100);
    args->dy = CLAMP(args->dy, -100, 100);
}