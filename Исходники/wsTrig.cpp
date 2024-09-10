f32 wsArcCos(f32 val) {
    WS_PROFILE();
    f32 my = acosf(val)*RAD_TO_DEG;

    return my;
}