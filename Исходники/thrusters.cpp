void des_thrusters::step(double delta)
{
    bool softkilled;
    shm_get(switches, soft_kill, softkilled);
    shm_getg(settings_control, shm_settings);

    if (softkilled || !shm_settings.enabled) {
        f -= f;
        t -= t;
        return;
    }
    
    // Read PID settings & desires.
    // (would switching to watchers improve performance?)

    SHM_GET_PID(settings_heading, shm_hp, hp)
    SHM_GET_PID(settings_pitch, shm_pp, pp)
    SHM_GET_PID(settings_roll, shm_rp, rp)
    SHM_GET_PID(settings_velx, shm_xp, xp)
    SHM_GET_PID(settings_vely, shm_yp, yp)
    SHM_GET_PID(settings_depth, shm_dp, dp)

    shm_getg(desires, shm_desires);

    // Read current orientation, velocity & position (in the model frame).

    // Orientation quaternion in the model frame.
    Eigen::Quaterniond qm = q * mtob_rq;
    Eigen::Vector3d rph = quat_to_euler(qm);

    // Component of the model quaternion about the z-axis (heading-only rotation).
    Eigen::Quaterniond qh = euler_to_quat(rph[2], 0, 0);

    // Velocity in heading modified world space.
    Eigen::Vector3d vp = qh.conjugate() * v;
    
    // Step the PID loops.

    Eigen::Vector3d desires = quat_to_euler(euler_to_quat(shm_desires.heading * DEG_TO_RAD,
                                                          shm_desires.pitch * DEG_TO_RAD,
                                                          shm_desires.roll * DEG_TO_RAD)) * RAD_TO_DEG;
    
    double ho = hp.step(delta, desires[2], rph[2] * RAD_TO_DEG);
    double po = pp.step(delta, desires[1], rph[1] * RAD_TO_DEG);
    double ro = rp.step(delta, desires[0], rph[0] * RAD_TO_DEG);

    double xo = xp.step(delta, shm_desires.speed, vp[0]);
    double yo = yp.step(delta, shm_desires.sway_speed, vp[1]);
    double zo = dp.step(delta, shm_desires.depth, x[2]);

    // f is in the heading modified world frame.
    // t is in the model frame.
    // We will work with f and b in the model frame until the end of this
    // function.

    f[0] = shm_settings.velx_active ? xo : 0;
    f[1] = shm_settings.vely_active ? yo : 0;
    f[2] = shm_settings.depth_active ? zo : 0;

    f *= m;

    Eigen::Vector3d w_in;
    w_in[0] = shm_settings.roll_active ? ro : 0;
    w_in[1] = shm_settings.pitch_active ? po : 0;
    w_in[2] = shm_settings.heading_active ? ho : 0;

    // TODO Avoid this roundabout conversion from hpr frame
    // to world frame and back to model frame.
    Eigen::Quaterniond qhp = euler_to_quat(rph[2], rph[1], 0);
    Eigen::Vector3d w = qm.conjugate() * (Eigen::Vector3d(0, 0, w_in[2]) +
                                     qh * Eigen::Vector3d(0, w_in[1], 0) +
                                    qhp * Eigen::Vector3d(w_in[0], 0, 0));

    t = btom_rm * q.conjugate() * I * q * mtob_rm * w;

    // Output diagnostic information. Shown by auv-control-helm.

    SHM_PUT_PID(control_internal_heading, ho)
    SHM_PUT_PID(control_internal_pitch, po)
    SHM_PUT_PID(control_internal_roll, ro)
    SHM_PUT_PID(control_internal_velx, xo)
    SHM_PUT_PID(control_internal_vely, yo)
    SHM_PUT_PID(control_internal_depth, zo)

    // Subtract passive forces.
    // (this implementation does not support discrimination!)
    if (shm_settings.buoyancy_forces || shm_settings.drag_forces) {
        // pff is in the body frame.
        screw ps = pff();
        f -= qh.conjugate() * q * ps.first;
        t -= btom_rm * ps.second;
    }

    // Hyper-ellipsoid clamping. Sort of limiting to the maximum amount of
    // energy the sub can output (e.g. can't move forward at full speed
    // and pitch at full speed at the same time).
    // Doesn't really account for real-world thruster configurations (e.g.
    // it might be possible to move forward at full speed and ascend at
    // full speed at the same time) but it's just an approximation.
    for (int i = 0; i < 3; i++) {
        f[i] /= axes[i];
    }

    for (int i = 0; i < 3; i++) {
        t[i] /= axes[3 + i];
    }

    double m = f.dot(f) + t.dot(t);
    if (m > 1) {
        double sm = sqrt(m);
        f /= sm;
        t /= sm;
    }

    for (int i = 0; i < 3; i++) {
        f[i] *= axes[i];
    }

    for (int i = 0; i < 3; i++) {
        t[i] *= axes[3 + i];
    }

    // Regular min/max clamping.
    clamp(f, fa, fb, 3);
    clamp(t, ta, tb, 3);

    f = q.conjugate() * qh * f;
    t = mtob_rm * t;
}