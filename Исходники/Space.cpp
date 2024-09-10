static void hitCallback(CollisionContact *c)
{
    //printf("OUCH! %x (depth %f)\n", SDL_GetTicks(), c->depth);

    Object *po1 = static_cast<Object*>(c->userData1);
    Object *po2 = static_cast<Object*>(c->userData2);

    const bool po1_isDynBody = po1->IsType(Object::DYNAMICBODY);
    const bool po2_isDynBody = po2->IsType(Object::DYNAMICBODY);
    // collision response
    assert(po1_isDynBody || po2_isDynBody);

    if (po1_isDynBody && po2_isDynBody) {
        DynamicBody *b1 = static_cast<DynamicBody*>(po1);
        DynamicBody *b2 = static_cast<DynamicBody*>(po2);
        const vector3d linVel1 = b1->GetVelocity();
        const vector3d linVel2 = b2->GetVelocity();
        const vector3d angVel1 = b1->GetAngVelocity();
        const vector3d angVel2 = b2->GetAngVelocity();

        const double coeff_rest = 0.5;
        // step back
//		mover->UndoTimestep();

        const double invMass1 = 1.0 / b1->GetMass();
        const double invMass2 = 1.0 / b2->GetMass();
        const vector3d hitPos1 = c->pos - b1->GetPosition();
        const vector3d hitPos2 = c->pos - b2->GetPosition();
        const vector3d hitVel1 = linVel1 + angVel1.Cross(hitPos1);
        const vector3d hitVel2 = linVel2 + angVel2.Cross(hitPos2);
        const double relVel = (hitVel1 - hitVel2).Dot(c->normal);
        // moving away so no collision
        if (relVel > 0) return;
        if (!OnCollision(po1, po2, c, -relVel)) return;
        const double invAngInert1 = 1.0 / b1->GetAngularInertia();
        const double invAngInert2 = 1.0 / b2->GetAngularInertia();
        const double numerator = -(1.0 + coeff_rest) * relVel;
        const double term1 = invMass1;
        const double term2 = invMass2;
        const double term3 = c->normal.Dot((hitPos1.Cross(c->normal)*invAngInert1).Cross(hitPos1));
        const double term4 = c->normal.Dot((hitPos2.Cross(c->normal)*invAngInert2).Cross(hitPos2));

        const double j = numerator / (term1 + term2 + term3 + term4);
        const vector3d force = j * c->normal;

        b1->SetVelocity(linVel1 + force*invMass1);
        b1->SetAngVelocity(angVel1 + hitPos1.Cross(force)*invAngInert1);
        b2->SetVelocity(linVel2 - force*invMass2);
        b2->SetAngVelocity(angVel2 - hitPos2.Cross(force)*invAngInert2);
    } else {
        // one body is static
        vector3d hitNormal;
        DynamicBody *mover;

        if (po1_isDynBody) {
            mover = static_cast<DynamicBody*>(po1);
            hitNormal = c->normal;
        } else {
            mover = static_cast<DynamicBody*>(po2);
            hitNormal = -c->normal;
        }

        const double coeff_rest = 0.5;
        const vector3d linVel1 = mover->GetVelocity();
        const vector3d angVel1 = mover->GetAngVelocity();

        // step back
//		mover->UndoTimestep();

        const double invMass1 = 1.0 / mover->GetMass();
        const vector3d hitPos1 = c->pos - mover->GetPosition();
        const vector3d hitVel1 = linVel1 + angVel1.Cross(hitPos1);
        const double relVel = hitVel1.Dot(c->normal);
        // moving away so no collision
        if (relVel > 0 && !c->geomFlag) return;
        if (!OnCollision(po1, po2, c, -relVel)) return;
        const double invAngInert = 1.0 / mover->GetAngularInertia();
        const double numerator = -(1.0 + coeff_rest) * relVel;
        const double term1 = invMass1;
        const double term3 = c->normal.Dot((hitPos1.Cross(c->normal)*invAngInert).Cross(hitPos1));

        const double j = numerator / (term1 + term3);
        const vector3d force = j * c->normal;

        mover->SetVelocity(linVel1 + force*invMass1);
        mover->SetAngVelocity(angVel1 + hitPos1.Cross(force)*invAngInert);
    }
}