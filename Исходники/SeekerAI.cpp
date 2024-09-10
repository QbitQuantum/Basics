void
SeekerAI::FindObjective()
{
    if (!shot || !target) return;

    if (target->Life() == 0) {
        if (target != orig_target)
        SetTarget(orig_target,0);
        else
        SetTarget(0,0);

        return;
    }

    Point tloc = target->Location();
    tloc = Transform(tloc);

    // seeker head limit of 45 degrees:
    if (tloc.z < 0 || tloc.z < fabs(tloc.x) || tloc.z < fabs(tloc.y)) {
        overshot = true;
        SetTarget(0,0);
        return;
    }

    // distance from self to target:
    distance = Point(target->Location() - self->Location()).length();

    // are we being spoofed?
    CheckDecoys(distance);

    Point cv = ClosingVelocity();

    // time to reach target:
    double time    = distance / cv.length();
    double predict = time;
    if (predict > 15)
    predict = 15;

    // pure pursuit:
    if (pursuit == 1 || time < 0.1) {
        obj_w = target->Location();
    }

    // lead pursuit:
    else {
        // where the target will be when we reach it:
        Point run_vec = target->Velocity();
        obj_w   = target->Location() + (run_vec * predict);
    }

    // subsystem offset:
    if (subtarget) {
        Point offset = target->Location() - subtarget->MountLocation();
        obj_w -= offset;
    }
    else if (target->Type() == SimObject::SIM_SHIP) {
        Ship* tgt_ship = (Ship*) target;

        if (tgt_ship->IsGroundUnit())
        obj_w += Point(0,150,0);
    }


    distance = Point(obj_w - self->Location()).length();
    time     = distance / cv.length();

    // where we will be when the target gets there:
    if (predict > 0.1 && predict < 15) {
        Point self_dest = self->Location() + cv * predict;
        Point err = obj_w - self_dest;

        obj_w += err;
    }

    // transform into camera coords:
    objective = Transform(obj_w);
    objective.Normalize();

    shot->SetEta((int) time);

    if (shot->Owner())
    ((Ship*) shot->Owner())->SetMissileEta(shot->Identity(), (int) time);
}