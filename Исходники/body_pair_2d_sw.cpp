bool BodyPair2DSW::setup(float p_step) {


    //cannot collide
    if ((A->get_layer_mask()&B->get_layer_mask())==0 || A->has_exception(B->get_self()) || B->has_exception(A->get_self()) || (A->get_mode()<=Physics2DServer::BODY_MODE_KINEMATIC && B->get_mode()<=Physics2DServer::BODY_MODE_KINEMATIC && A->get_max_contacts_reported()==0 && B->get_max_contacts_reported()==0)) {
        collided=false;
        return false;
    }

    //use local A coordinates to avoid numerical issues on collision detection
    offset_B = B->get_transform().get_origin() - A->get_transform().get_origin();

    _validate_contacts();

    Vector2 offset_A = A->get_transform().get_origin();
    Matrix32 xform_Au = A->get_transform().untranslated();
    Matrix32 xform_A = xform_Au * A->get_shape_transform(shape_A);

    Matrix32 xform_Bu = B->get_transform();
    xform_Bu.elements[2]-=A->get_transform().get_origin();
    Matrix32 xform_B = xform_Bu * B->get_shape_transform(shape_B);

    Shape2DSW *shape_A_ptr=A->get_shape(shape_A);
    Shape2DSW *shape_B_ptr=B->get_shape(shape_B);

    Vector2 motion_A,motion_B;

    if (A->get_continuous_collision_detection_mode()==Physics2DServer::CCD_MODE_CAST_SHAPE) {
        motion_A=A->get_motion();
    }
    if (B->get_continuous_collision_detection_mode()==Physics2DServer::CCD_MODE_CAST_SHAPE) {
        motion_B=B->get_motion();
    }
    //faster to set than to check..

    collided = CollisionSolver2DSW::solve(shape_A_ptr,xform_A,motion_A,shape_B_ptr,xform_B,motion_B,_add_contact,this,&sep_axis);
    if (!collided) {

        //test ccd (currently just a raycast)

        if (A->get_continuous_collision_detection_mode()==Physics2DServer::CCD_MODE_CAST_RAY && A->get_mode()>Physics2DServer::BODY_MODE_KINEMATIC) {
            if (_test_ccd(p_step,A,shape_A,xform_A,B,shape_B,xform_B))
                collided=true;
        }

        if (B->get_continuous_collision_detection_mode()==Physics2DServer::CCD_MODE_CAST_RAY && B->get_mode()>Physics2DServer::BODY_MODE_KINEMATIC) {
            if (_test_ccd(p_step,B,shape_B,xform_B,A,shape_A,xform_A,true))
                collided=true;
        }

        if (!collided)
            return false;

    }

    real_t max_penetration = space->get_contact_max_allowed_penetration();

    float bias = 0.3f;
    if (shape_A_ptr->get_custom_bias() || shape_B_ptr->get_custom_bias()) {

        if (shape_A_ptr->get_custom_bias()==0)
            bias=shape_B_ptr->get_custom_bias();
        else if (shape_B_ptr->get_custom_bias()==0)
            bias=shape_A_ptr->get_custom_bias();
        else
            bias=(shape_B_ptr->get_custom_bias()+shape_A_ptr->get_custom_bias())*0.5;
    }


    cc=0;


    real_t inv_dt = 1.0/p_step;
    for (int i = 0; i < contact_count; i++) {

        Contact& c = contacts[i];

        Vector2 global_A = xform_Au.xform(c.local_A);
        Vector2 global_B = xform_Bu.xform(c.local_B);

        real_t depth = c.normal.dot(global_A - global_B);

        if (depth<=0 || !c.reused) {
            c.active=false;
            continue;
        }

        c.active=true;

        int gather_A = A->can_report_contacts();
        int gather_B = B->can_report_contacts();

        c.rA = global_A;
        c.rB = global_B-offset_B;

        if (gather_A | gather_B) {

            //Vector2 crB( -B->get_angular_velocity() * c.rB.y, B->get_angular_velocity() * c.rB.x );

            global_A+=offset_A;
            global_B+=offset_A;

            if (gather_A) {
                Vector2 crB( -B->get_angular_velocity() * c.rB.y, B->get_angular_velocity() * c.rB.x );
                A->add_contact(global_A,-c.normal,depth,shape_A,global_B,shape_B,B->get_instance_id(),B->get_self(),crB+B->get_linear_velocity());
            }
            if (gather_B) {

                Vector2 crA( -A->get_angular_velocity() * c.rA.y, A->get_angular_velocity() * c.rA.x );
                B->add_contact(global_B,c.normal,depth,shape_B,global_A,shape_A,A->get_instance_id(),A->get_self(),crA+A->get_linear_velocity());
            }
        }

        if (A->is_shape_set_as_trigger(shape_A) || B->is_shape_set_as_trigger(shape_B) || (A->get_mode()<=Physics2DServer::BODY_MODE_KINEMATIC && B->get_mode()<=Physics2DServer::BODY_MODE_KINEMATIC)) {
            c.active=false;
            collided=false;
            continue;

        }

        // Precompute normal mass, tangent mass, and bias.
        real_t rnA = c.rA.dot(c.normal);
        real_t rnB = c.rB.dot(c.normal);
        real_t kNormal = A->get_inv_mass() + B->get_inv_mass();
        kNormal += A->get_inv_inertia() * (c.rA.dot(c.rA) - rnA * rnA) + B->get_inv_inertia() * (c.rB.dot(c.rB) - rnB * rnB);
        c.mass_normal = 1.0f / kNormal;

        Vector2 tangent = c.normal.tangent();
        real_t rtA = c.rA.dot(tangent);
        real_t rtB = c.rB.dot(tangent);
        real_t kTangent = A->get_inv_mass() + B->get_inv_mass();
        kTangent += A->get_inv_inertia() * (c.rA.dot(c.rA) - rtA * rtA) + B->get_inv_inertia() * (c.rB.dot(c.rB) - rtB * rtB);
        c.mass_tangent = 1.0f /  kTangent;



        c.bias = -bias * inv_dt * MIN(0.0f, -depth + max_penetration);
        c.depth=depth;
        //c.acc_bias_impulse=0;


#ifdef ACCUMULATE_IMPULSES
        {
            // Apply normal + friction impulse
            Vector2 P = c.acc_normal_impulse * c.normal + c.acc_tangent_impulse * tangent;


            A->apply_impulse(c.rA,-P);
            B->apply_impulse(c.rB, P);
        }

#endif


        c.bounce=MAX(A->get_bounce(),B->get_bounce());
        if (c.bounce) {

            Vector2 crA( -A->get_angular_velocity() * c.rA.y, A->get_angular_velocity() * c.rA.x );
            Vector2 crB( -B->get_angular_velocity() * c.rB.y, B->get_angular_velocity() * c.rB.x );
            Vector2 dv = B->get_linear_velocity() + crB - A->get_linear_velocity() - crA;
            c.bounce = c.bounce * dv.dot(c.normal);
        }


    }

    return true;
}