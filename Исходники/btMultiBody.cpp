void btMultiBody::fillContactJacobian(int link,
                                    const btVector3 &contact_point,
                                    const btVector3 &normal,
                                    btScalar *jac,
                                    btAlignedObjectArray<btScalar> &scratch_r,
                                    btAlignedObjectArray<btVector3> &scratch_v,
                                    btAlignedObjectArray<btMatrix3x3> &scratch_m) const
{
    // temporary space
	int num_links = getNumLinks();
    scratch_v.resize(2*num_links + 2);
    scratch_m.resize(num_links + 1);

    btVector3 * v_ptr = &scratch_v[0];
    btVector3 * p_minus_com = v_ptr; v_ptr += num_links + 1;
    btVector3 * n_local = v_ptr; v_ptr += num_links + 1;
    btAssert(v_ptr - &scratch_v[0] == scratch_v.size());

    scratch_r.resize(num_links);
    btScalar * results = num_links > 0 ? &scratch_r[0] : 0;

    btMatrix3x3 * rot_from_world = &scratch_m[0];

    const btVector3 p_minus_com_world = contact_point - base_pos;

    rot_from_world[0] = btMatrix3x3(base_quat);

    p_minus_com[0] = rot_from_world[0] * p_minus_com_world;
    n_local[0] = rot_from_world[0] * normal;
    
    // omega coeffients first.
    btVector3 omega_coeffs;
    omega_coeffs = p_minus_com_world.cross(normal);
	jac[0] = omega_coeffs[0];
	jac[1] = omega_coeffs[1];
	jac[2] = omega_coeffs[2];
    // then v coefficients
    jac[3] = normal[0];
    jac[4] = normal[1];
    jac[5] = normal[2];

    // Set remaining jac values to zero for now.
    for (int i = 6; i < 6 + num_links; ++i) {
        jac[i] = 0;
    }

    // Qdot coefficients, if necessary.
    if (num_links > 0 && link > -1) {

        // TODO: speed this up -- don't calculate for links we don't need.
        // (Also, we are making 3 separate calls to this function, for the normal & the 2 friction directions,
        // which is resulting in repeated work being done...)

        // calculate required normals & positions in the local frames.
        for (int i = 0; i < num_links; ++i) {

            // transform to local frame
            const int parent = links[i].parent;
            const btMatrix3x3 mtx(links[i].cached_rot_parent_to_this);
            rot_from_world[i+1] = mtx * rot_from_world[parent+1];

            n_local[i+1] = mtx * n_local[parent+1];
            p_minus_com[i+1] = mtx * p_minus_com[parent+1] - links[i].cached_r_vector;

            // calculate the jacobian entry
            if (links[i].is_revolute) {
                results[i] = n_local[i+1].dot( links[i].axis_top.cross(p_minus_com[i+1]) + links[i].axis_bottom );
            } else {
                results[i] = n_local[i+1].dot( links[i].axis_bottom );
            }
        }

        // Now copy through to output.
        while (link != -1) {
            jac[6 + link] = results[link];
            link = links[link].parent;
        }
    }
}