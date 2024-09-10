// this function calculates the normal using the local coordinates;
SbVec3f Sphere::calculate_normal(SbVec3f *starting_position, SbVec3f *ray_direction, float t) {
    SbVec3f normal;
    SbVec3f sp = *starting_position ;
    SbVec3f rd = *ray_direction;
    SbVec3f origin(0.0,0.0,0.0);

    sp = multiply_with_inverse(sp);
    rd = multiply_with_inverse(rd);
    origin = multiply_with_inverse(origin);
    rd = rd - origin;
    rd.normalize();

    normal = (sp + (t *(rd))); //ntc
    //normal += nn;
    //normal = multiply_with_transformation(normal) - multiply_with_transformation(origin);
    //normal.normalize();
    // normal = offset_normal(normal, 0.31f);
    normal.normalize();
    return normal;
}