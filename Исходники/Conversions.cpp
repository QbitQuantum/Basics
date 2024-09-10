void convert(const eMatrixHom &in, eMatrixHom2d &out) {
    double yaw = extractYaw(in);
    out.setIdentity();
    out.rotate(yaw);
    out.translation() =  eVector2(in.translation()[X], in.translation()[Y]);
}