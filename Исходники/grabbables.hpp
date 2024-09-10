    void set_trans(cl_float4 clpos, quaternion m)
    {
        mat3f mat_diff = base_diff.get_rotation_matrix();

        mat3f current_hand = m.get_rotation_matrix();
        mat3f my_rot = current_hand * mat_diff;

        quaternion n;
        n.load_from_matrix(my_rot);


        vec3f absolute_pos = {clpos.x, clpos.y, clpos.z};

        ///current hand does not take into account the rotation offset when grabbing
        ///ie we'll double rotate
        vec3f offset_rot = current_hand * offset;

        vec3f pos = absolute_pos + offset_rot;

        btTransform newTrans;

        //rigid_body->getMotionState()->getWorldTransform(newTrans);

        newTrans.setOrigin(btVector3(pos.v[0], pos.v[1], pos.v[2]));
        newTrans.setRotation(btQuaternion(n.x(), n.y(), n.z(), n.w()));

        rigid_body->getMotionState()->setWorldTransform(newTrans);
        //rigid_body->setInterpolationWorldTransform(newTrans);

        //if(ctr)
        //    ctr->set_pos(conv_implicit<cl_float4>(pos));

        slide_parent_init = true;
        slide_saved_parent = absolute_pos;

        remote_pos = pos;
        remote_rot = n;

        kinematic_old = kinematic_current;
        kinematic_current = xyzf_to_vec(rigid_body->getWorldTransform().getOrigin());
    }