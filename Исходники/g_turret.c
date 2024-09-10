void turret_breach_think(edict_t * self)
{
    edict_t *ent;
    vec3_t current_angles;
    vec3_t delta;

    VectorCopy(self->s.angles, current_angles);
    AnglesNormalize(current_angles);

    AnglesNormalize(self->move_angles);
    if (self->move_angles[PITCH] > 180)
        self->move_angles[PITCH] -= 360;

    // clamp angles to mins & maxs
    if (self->move_angles[PITCH] > self->pos1[PITCH])
        self->move_angles[PITCH] = self->pos1[PITCH];
    else if (self->move_angles[PITCH] < self->pos2[PITCH])
        self->move_angles[PITCH] = self->pos2[PITCH];

    if ((self->move_angles[YAW] < self->pos1[YAW])
            || (self->move_angles[YAW] > self->pos2[YAW])) {
        float dmin, dmax;

        dmin = fabs(self->pos1[YAW] - self->move_angles[YAW]);
        if (dmin < -180)
            dmin += 360;
        else if (dmin > 180)
            dmin -= 360;
        dmax = fabs(self->pos2[YAW] - self->move_angles[YAW]);
        if (dmax < -180)
            dmax += 360;
        else if (dmax > 180)
            dmax -= 360;
        if (fabs(dmin) < fabs(dmax))
            self->move_angles[YAW] = self->pos1[YAW];
        else
            self->move_angles[YAW] = self->pos2[YAW];
    }

    VectorSubtract(self->move_angles, current_angles, delta);
    if (delta[0] < -180)
        delta[0] += 360;
    else if (delta[0] > 180)
        delta[0] -= 360;
    if (delta[1] < -180)
        delta[1] += 360;
    else if (delta[1] > 180)
        delta[1] -= 360;
    delta[2] = 0;

    if (delta[0] > self->speed * FRAMETIME)
        delta[0] = self->speed * FRAMETIME;
    if (delta[0] < -1 * self->speed * FRAMETIME)
        delta[0] = -1 * self->speed * FRAMETIME;
    if (delta[1] > self->speed * FRAMETIME)
        delta[1] = self->speed * FRAMETIME;
    if (delta[1] < -1 * self->speed * FRAMETIME)
        delta[1] = -1 * self->speed * FRAMETIME;

    VectorScale(delta, 1.0 / FRAMETIME, self->avelocity);

    self->nextthink = level.time + FRAMETIME;

    for (ent = self->teammaster; ent; ent = ent->teamchain)
        ent->avelocity[1] = self->avelocity[1];

    // if we have adriver, adjust his velocities
    if (self->owner) {
        float angle;
        float target_z;
        float diff;
        vec3_t target;
        vec3_t dir;

        // angular is easy, just copy ours
        self->owner->avelocity[0] = self->avelocity[0];
        self->owner->avelocity[1] = self->avelocity[1];

        // x & y
        angle = self->s.angles[1] + self->owner->move_origin[1];
        angle *= (M_PI * 2 / 360);
        target[0] =
            SnapToEights(self->s.origin[0] +
                         cos(angle) * self->owner->move_origin[0]);
        target[1] =
            SnapToEights(self->s.origin[1] +
                         sin(angle) * self->owner->move_origin[0]);
        target[2] = self->owner->s.origin[2];

        VectorSubtract(target, self->owner->s.origin, dir);
        self->owner->velocity[0] = dir[0] * 1.0 / FRAMETIME;
        self->owner->velocity[1] = dir[1] * 1.0 / FRAMETIME;

        // z
        angle = self->s.angles[PITCH] * (M_PI * 2 / 360);
        target_z =
            SnapToEights(self->s.origin[2] +
                         self->owner->move_origin[0] * tan(angle) +
                         self->owner->move_origin[2]);

        diff = target_z - self->owner->s.origin[2];
        self->owner->velocity[2] = diff * 1.0 / FRAMETIME;

        if (self->spawnflags & 65536) {
            turret_breach_fire(self);
            self->spawnflags &= ~65536;
        }
    }
}