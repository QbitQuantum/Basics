bool Compass::consistent() const
{
    Vector3f primary_mag_field = get_field();
    Vector3f primary_mag_field_norm;

    if (!primary_mag_field.is_zero()) {
        primary_mag_field_norm = primary_mag_field.normalized();
    } else {
        return false;
    }

    Vector2f primary_mag_field_xy = Vector2f(primary_mag_field.x,primary_mag_field.y);
    Vector2f primary_mag_field_xy_norm;

    if (!primary_mag_field_xy.is_zero()) {
        primary_mag_field_xy_norm = primary_mag_field_xy.normalized();
    } else {
        return false;
    }

    for (uint8_t i=0; i<get_count(); i++) {
        if (use_for_yaw(i)) {
            Vector3f mag_field = get_field(i);
            Vector3f mag_field_norm;

            if (!mag_field.is_zero()) {
                mag_field_norm = mag_field.normalized();
            } else {
                return false;
            }

            Vector2f mag_field_xy = Vector2f(mag_field.x,mag_field.y);
            Vector2f mag_field_xy_norm;

            if (!mag_field_xy.is_zero()) {
                mag_field_xy_norm = mag_field_xy.normalized();
            } else {
                return false;
            }

            float xyz_ang_diff = acosf(constrain_float(mag_field_norm * primary_mag_field_norm,-1.0f,1.0f));
            float xy_ang_diff  = acosf(constrain_float(mag_field_xy_norm*primary_mag_field_xy_norm,-1.0f,1.0f));
            float xy_len_diff  = (primary_mag_field_xy-mag_field_xy).length();

            // check for gross misalignment on all axes
            bool xyz_ang_diff_large = xyz_ang_diff > AP_COMPASS_MAX_XYZ_ANG_DIFF;

            // check for an unacceptable angle difference on the xy plane
            bool xy_ang_diff_large = xy_ang_diff > AP_COMPASS_MAX_XY_ANG_DIFF;

            // check for an unacceptable length difference on the xy plane
            bool xy_length_diff_large = xy_len_diff > AP_COMPASS_MAX_XY_LENGTH_DIFF;

            // check for inconsistency in the XY plane
            if (xyz_ang_diff_large || xy_ang_diff_large || xy_length_diff_large) {
                return false;
            }
        }
    }
    return true;
}