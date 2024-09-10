    inline void step_dt(const base::Time& dt){
        if(mode == base::JointState::POSITION)
        {
            j_state.position = j_setpoint.position;
            j_state.speed = j_setpoint.speed;
            j_state.effort = j_setpoint.effort;

            trunc_to_limit(base::JointState::POSITION);
            trunc_to_limit(base::JointState::SPEED);
            trunc_to_limit(base::JointState::EFFORT);
        }
        else if(mode == base::JointState::SPEED)
        {
            j_state.speed = j_setpoint.speed;
            j_state.effort = j_setpoint.effort;


            trunc_to_limit(base::JointState::SPEED);
            trunc_to_limit(base::JointState::EFFORT);

            j_state.position += j_setpoint.speed*dt.toSeconds();

            trunc_to_limit(base::JointState::POSITION);
        }
        else if(mode == base::JointState::EFFORT)
        {
            j_state.effort = j_setpoint.effort;

            trunc_to_limit(base::JointState::EFFORT);

            j_state.speed += j_setpoint.effort*dt.toSeconds();
            j_state.position += j_setpoint.speed*dt.toSeconds();

            trunc_to_limit(base::JointState::POSITION);
            trunc_to_limit(base::JointState::SPEED);
        }

        perturb(dt.toSeconds());
    }