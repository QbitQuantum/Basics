bool AP_Arming::compass_checks(bool report)
{
    if ((checks_to_perform) & ARMING_CHECK_ALL ||
        (checks_to_perform) & ARMING_CHECK_COMPASS) {

        if (!_compass.use_for_yaw()) {
            // compass use is disabled
            return true;
        }

        if (!_compass.healthy()) {
            if (report) {
                GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, PSTR("PreArm: Compass not healthy"));
            }
            return false;
        }
        // check compass learning is on or offsets have been set
        if (!_compass.learn_offsets_enabled() && !_compass.configured()) {
            if (report) {
                GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, PSTR("PreArm: Compass not calibrated"));
            }
            return false;
        }

        //check if compass is calibrating
        if (_compass.is_calibrating()) {
            if (report) {
                GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, PSTR("Arm: Compass calibration running"));
            }
            return false;
        }

        //check if compass has calibrated and requires reboot
        if (_compass.compass_cal_requires_reboot()) {
            if (report) {
                GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, PSTR("PreArm: Compass calibrated requires reboot"));
            }
            return false;
        }

        // check for unreasonable compass offsets
        Vector3f offsets = _compass.get_offsets();
        if (offsets.length() > AP_ARMING_COMPASS_OFFSETS_MAX) {
            if (report) {
                GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, PSTR("PreArm: Compass offsets too high"));
            }
            return false;
        }

        // check for unreasonable mag field length
        float mag_field = _compass.get_field().length();
        if (mag_field > AP_ARMING_COMPASS_MAGFIELD_MAX || mag_field < AP_ARMING_COMPASS_MAGFIELD_MIN) {
            if (report) {
                GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, PSTR("PreArm: Check mag field"));
            }
            return false;
        }

        // check all compasses point in roughly same direction
        if (!_compass.consistent()) {
            if (report) {
                GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL,PSTR("PreArm: inconsistent compasses"));
    }
            return false;
        }
    }

    return true;
}