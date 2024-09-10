Camera InterpolationFunction<Camera>::interpolate(Camera startvalue, Camera endvalue, float time) const {
    Vec3LinearInterpolationFunction* intfunc = new Vec3LinearInterpolationFunction();
    Vec3SphericalLinearInterpolationFunction* intfunc2 = new Vec3SphericalLinearInterpolationFunction();
    tgt::vec3 posvec = intfunc->interpolate(startvalue.getPosition(), endvalue.getPosition(), time);
    tgt::vec3 focvec = intfunc->interpolate(startvalue.getFocus(), endvalue.getFocus(), time);
    tgt::vec3 upvec = normalize(intfunc2->interpolate(startvalue.getUpVector(), endvalue.getUpVector(), time));
    /*            tgt::vec3 direction = intfunc2->interpolate(startvalue->getDirection(), endvalue->getDirection(), time);
                return new CameraNode(posvec, focvec, upvec, direction); */
    Camera cam(startvalue);
    cam.positionCamera(posvec, focvec, upvec);
    return cam;
}