void do_kink(ParticleKey *state, const float par_co[3], const float par_vel[3], const float par_rot[4], float time, float freq, float shape,
             float amplitude, float flat, short type, short axis, float obmat[4][4], int smooth_start)
{
	float kink[3] = {1.f, 0.f, 0.f}, par_vec[3], q1[4] = {1.f, 0.f, 0.f, 0.f};
	float t, dt = 1.f, result[3];

	if (ELEM(type, PART_KINK_NO, PART_KINK_SPIRAL))
		return;

	CLAMP(time, 0.f, 1.f);

	if (shape != 0.0f && !ELEM(type, PART_KINK_BRAID)) {
		if (shape < 0.0f)
			time = (float)pow(time, 1.f + shape);
		else
			time = (float)pow(time, 1.f / (1.f - shape));
	}

	t = time * freq * (float)M_PI;
	
	if (smooth_start) {
		dt = fabsf(t);
		/* smooth the beginning of kink */
		CLAMP(dt, 0.f, (float)M_PI);
		dt = sinf(dt / 2.f);
	}

	if (!ELEM(type, PART_KINK_RADIAL)) {
		float temp[3];

		kink[axis] = 1.f;

		if (obmat)
			mul_mat3_m4_v3(obmat, kink);
		
		mul_qt_v3(par_rot, kink);

		/* make sure kink is normal to strand */
		project_v3_v3v3(temp, kink, par_vel);
		sub_v3_v3(kink, temp);
		normalize_v3(kink);
	}

	copy_v3_v3(result, state->co);
	sub_v3_v3v3(par_vec, par_co, state->co);

	switch (type) {
		case PART_KINK_CURL:
		{
			float curl_offset[3];
			
			/* rotate kink vector around strand tangent */
			mul_v3_v3fl(curl_offset, kink, amplitude);
			axis_angle_to_quat(q1, par_vel, t);
			mul_qt_v3(q1, curl_offset);
			
			interp_v3_v3v3(par_vec, state->co, par_co, flat);
			add_v3_v3v3(result, par_vec, curl_offset);
			break;
		}
		case PART_KINK_RADIAL:
		{
			if (flat > 0.f) {
				float proj[3];
				/* flatten along strand */
				project_v3_v3v3(proj, par_vec, par_vel);
				madd_v3_v3fl(result, proj, flat);
			}

			madd_v3_v3fl(result, par_vec, -amplitude * sinf(t));
			break;
		}
		case PART_KINK_WAVE:
		{
			madd_v3_v3fl(result, kink, amplitude * sinf(t));

			if (flat > 0.f) {
				float proj[3];
				/* flatten along wave */
				project_v3_v3v3(proj, par_vec, kink);
				madd_v3_v3fl(result, proj, flat);

				/* flatten along strand */
				project_v3_v3v3(proj, par_vec, par_vel);
				madd_v3_v3fl(result, proj, flat);
			}
			break;
		}
		case PART_KINK_BRAID:
		{
			float y_vec[3] = {0.f, 1.f, 0.f};
			float z_vec[3] = {0.f, 0.f, 1.f};
			float vec_one[3], state_co[3];
			float inp_y, inp_z, length;
		
			if (par_rot) {
				mul_qt_v3(par_rot, y_vec);
				mul_qt_v3(par_rot, z_vec);
			}

			negate_v3(par_vec);
			normalize_v3_v3(vec_one, par_vec);

			inp_y = dot_v3v3(y_vec, vec_one);
			inp_z = dot_v3v3(z_vec, vec_one);

			if (inp_y > 0.5f) {
				copy_v3_v3(state_co, y_vec);

				mul_v3_fl(y_vec, amplitude * cosf(t));
				mul_v3_fl(z_vec, amplitude / 2.f * sinf(2.f * t));
			}
			else if (inp_z > 0.0f) {
				mul_v3_v3fl(state_co, z_vec, sinf((float)M_PI / 3.f));
				madd_v3_v3fl(state_co, y_vec, -0.5f);

				mul_v3_fl(y_vec, -amplitude * cosf(t + (float)M_PI / 3.f));
				mul_v3_fl(z_vec, amplitude / 2.f * cosf(2.f * t + (float)M_PI / 6.f));
			}
			else {
				mul_v3_v3fl(state_co, z_vec, -sinf((float)M_PI / 3.f));
				madd_v3_v3fl(state_co, y_vec, -0.5f);

				mul_v3_fl(y_vec, amplitude * -sinf(t + (float)M_PI / 6.f));
				mul_v3_fl(z_vec, amplitude / 2.f * -sinf(2.f * t + (float)M_PI / 3.f));
			}

			mul_v3_fl(state_co, amplitude);
			add_v3_v3(state_co, par_co);
			sub_v3_v3v3(par_vec, state->co, state_co);

			length = normalize_v3(par_vec);
			mul_v3_fl(par_vec, MIN2(length, amplitude / 2.f));

			add_v3_v3v3(state_co, par_co, y_vec);
			add_v3_v3(state_co, z_vec);
			add_v3_v3(state_co, par_vec);

			shape = 2.f * (float)M_PI * (1.f + shape);

			if (t < shape) {
				shape = t / shape;
				shape = (float)sqrt((double)shape);
				interp_v3_v3v3(result, result, state_co, shape);
			}
			else {
				copy_v3_v3(result, state_co);
			}
			break;
		}
	}

	/* blend the start of the kink */
	if (dt < 1.f)
		interp_v3_v3v3(state->co, state->co, result, dt);
	else
		copy_v3_v3(state->co, result);
}