void
Mass_spring_viewer::compute_forces()
{
    // clear forces
    for (unsigned int i=0; i<body_.particles.size(); ++i)
        body_.particles[i].force = vec2(0,0);


    /** \todo (Part 1) Implement center force
     */
    if (external_force_ == Center)
    {
      float c = 10.f;
      for (std::vector<Particle>::iterator p_it = body_.particles.begin (); p_it != body_.particles.end (); ++p_it)
        p_it->force += c * (vec2 (0.f, 0.f) - p_it->position);
    }


    /** \todo (Part 1) Implement damping force
     \li The damping coefficient is given as member damping_
     */
    /// Do damping only for explicit methods
    if (integration_ != Implicit)
      for (std::vector<Particle>::iterator p_it = body_.particles.begin (); p_it != body_.particles.end (); ++p_it)
        p_it->force -= damping_ * p_it->velocity;


    /** \todo (Part 1) Implement gravitation force
     \li Particle mass available as particle_mass_
     */
    if (external_force_ == Gravitation)
    {
      for (std::vector<Particle>::iterator p_it = body_.particles.begin (); p_it != body_.particles.end (); ++p_it)
        p_it->force += 9.81 * p_it->mass * vec2 (0.f, -1.f);
    }


    /** \todo (Part 1) Implement force based boundary collisions
     \li Collision coefficient given as collision_stiffness_
     */
    // collision forces
    if (collisions_ == Force_based)
    {
        float planes[4][3] = {
            {  0.0,  1.0, 1.0 },
            {  0.0, -1.0, 1.0 },
            {  1.0,  0.0, 1.0 },
            { -1.0,  0.0, 1.0 }
        };

        for (std::vector<Particle>::iterator p_it = body_.particles.begin (); p_it != body_.particles.end (); ++p_it)
        {
          for (size_t plane_i = 0; plane_i < 4; ++plane_i)
          {
            float d = planes[plane_i][0] * p_it->position[0] +
                      planes[plane_i][1] * p_it->position[1] +
                      planes[plane_i][2] - particle_radius_;

            if (d < 0.f)
              p_it->force += collision_stiffness_ * (-d) * vec2 (planes[plane_i][0],
                                                                 planes[plane_i][1]);
          }
        }
    }


    /** \todo (Part 1) Compute force of the interactive mass spring
     \li Required coefficients are given as spring_stiffness_ and spring_damping_
     */
    if (mouse_spring_.active)
    {
        Particle& particle = body_.particles[ mouse_spring_.particle_index ];

        vec2 pos0 = particle.position;
        vec2 pos1 = mouse_spring_.mouse_position;

        particle.force += -(spring_stiffness_ * norm (pos0 - pos1) +
                            spring_damping_ * dot (particle.velocity, pos0 - pos1) / norm (pos0 - pos1)) * (pos0 - pos1) / norm (pos0 - pos1);
    }


    /** \todo (Part 1) Compute spring forces
     \li Required information about springs in the scene are found in body_.springs
     \li Required coefficients are given as spring_stiffness_ and spring_damping_
     */

    for (std::vector<Spring>::iterator s_it = body_.springs.begin (); s_it != body_.springs.end (); ++s_it)
    {
      const vec2 &pos0 = s_it->particle0->position;
      const vec2 &pos1 = s_it->particle1->position;
      const vec2 &vel0 = s_it->particle0->velocity;
      const vec2 &vel1 = s_it->particle1->velocity;

      vec2 force = -(spring_stiffness_ * (norm (pos0 - pos1) - s_it->rest_length) +
                     spring_damping_ * dot (vel0 - vel1, pos0 - pos1) / norm (pos0 - pos1)) * (pos0 - pos1) / norm (pos0 - pos1);
      s_it->particle0->force += force;
      s_it->particle1->force += -force;
    }



    /** \todo (Part 2) Compute more forces in part 2 of the exercise: triangle-area forces, binding forces, etc.
     */
    if (area_forces_) {
        for (std::vector<Triangle>::iterator t_it = body_.triangles.begin (); t_it != body_.triangles.end (); ++t_it)
        {
            /*
            F_i = - k_A * (area - A) * d_area/d_i


            */

            const vec2& p0 = t_it->particle0->position;
            const vec2& p1 = t_it->particle1->position;
            const vec2& p2 = t_it->particle2->position;
            vec2 d_area_0 = perp(0.5 * (p1 - p2));
            vec2 d_area_1 = perp(0.5 * (p2 - p0));
            vec2 d_area_2 = perp(0.5 * (p0 - p1));

            float tmp = - area_stiffness_ * (t_it->area() - t_it->rest_area);

            t_it->particle0->force += tmp * d_area_0;
            t_it->particle1->force += tmp * d_area_1;
            t_it->particle2->force += tmp * d_area_2;
        }
    }


    if (equilibrium_forces_) {
        for (std::vector<Particle>::iterator p_it1 = body_.particles.begin (); p_it1 != body_.particles.end (); ++p_it1) {
            for (std::vector<Particle>::iterator p_it2 = p_it1+1; p_it2 != body_.particles.end (); ++p_it2) {
                const vec2 &p1 = p_it1->position;
                const vec2 &p2 = p_it2->position;
                float dist = distance(p1, p2);
                vec2 d = p1 - p2;
                float f = 0.1f / (dist*dist);

                p_it1->force += f*d;
                p_it2->force += -f*d;
            }
        }

    }
}