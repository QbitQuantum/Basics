/* Evaluate spline IK for a given bone */
static void splineik_evaluate_bone(tSplineIK_Tree *tree, Scene *scene, Object *ob, bPoseChannel *pchan,
                                   int index, float ctime)
{
	bSplineIKConstraint *ikData = tree->ikData;
	float poseHead[3], poseTail[3], poseMat[4][4];
	float splineVec[3], scaleFac, radius = 1.0f;

	/* firstly, calculate the bone matrix the standard way, since this is needed for roll control */
	BKE_pose_where_is_bone(scene, ob, pchan, ctime, 1);

	copy_v3_v3(poseHead, pchan->pose_head);
	copy_v3_v3(poseTail, pchan->pose_tail);

	/* step 1: determine the positions for the endpoints of the bone */
	{
		float vec[4], dir[3], rad;
		float tailBlendFac = 1.0f;

		/* determine if the bone should still be affected by SplineIK */
		if (tree->points[index + 1] >= 1.0f) {
			/* spline doesn't affect the bone anymore, so done... */
			pchan->flag |= POSE_DONE;
			return;
		}
		else if ((tree->points[index] >= 1.0f) && (tree->points[index + 1] < 1.0f)) {
			/* blending factor depends on the amount of the bone still left on the chain */
			tailBlendFac = (1.0f - tree->points[index + 1]) / (tree->points[index] - tree->points[index + 1]);
		}

		/* tail endpoint */
		if (where_on_path(ikData->tar, tree->points[index], vec, dir, NULL, &rad, NULL)) {
			/* apply curve's object-mode transforms to the position
			 * unless the option to allow curve to be positioned elsewhere is activated (i.e. no root)
			 */
			if ((ikData->flag & CONSTRAINT_SPLINEIK_NO_ROOT) == 0)
				mul_m4_v3(ikData->tar->obmat, vec);

			/* convert the position to pose-space, then store it */
			mul_m4_v3(ob->imat, vec);
			interp_v3_v3v3(poseTail, pchan->pose_tail, vec, tailBlendFac);

			/* set the new radius */
			radius = rad;
		}

		/* head endpoint */
		if (where_on_path(ikData->tar, tree->points[index + 1], vec, dir, NULL, &rad, NULL)) {
			/* apply curve's object-mode transforms to the position
			 * unless the option to allow curve to be positioned elsewhere is activated (i.e. no root)
			 */
			if ((ikData->flag & CONSTRAINT_SPLINEIK_NO_ROOT) == 0)
				mul_m4_v3(ikData->tar->obmat, vec);

			/* store the position, and convert it to pose space */
			mul_m4_v3(ob->imat, vec);
			copy_v3_v3(poseHead, vec);

			/* set the new radius (it should be the average value) */
			radius = (radius + rad) / 2;
		}
	}

	/* step 2: determine the implied transform from these endpoints
	 *     - splineVec: the vector direction that the spline applies on the bone
	 *     - scaleFac: the factor that the bone length is scaled by to get the desired amount
	 */
	sub_v3_v3v3(splineVec, poseTail, poseHead);
	scaleFac = len_v3(splineVec) / pchan->bone->length;

	/* step 3: compute the shortest rotation needed to map from the bone rotation to the current axis
	 *      - this uses the same method as is used for the Damped Track Constraint (see the code there for details)
	 */
	{
		float dmat[3][3], rmat[3][3], tmat[3][3];
		float raxis[3], rangle;

		/* compute the raw rotation matrix from the bone's current matrix by extracting only the
		 * orientation-relevant axes, and normalizing them
		 */
		copy_v3_v3(rmat[0], pchan->pose_mat[0]);
		copy_v3_v3(rmat[1], pchan->pose_mat[1]);
		copy_v3_v3(rmat[2], pchan->pose_mat[2]);
		normalize_m3(rmat);

		/* also, normalize the orientation imposed by the bone, now that we've extracted the scale factor */
		normalize_v3(splineVec);

		/* calculate smallest axis-angle rotation necessary for getting from the
		 * current orientation of the bone, to the spline-imposed direction
		 */
		cross_v3_v3v3(raxis, rmat[1], splineVec);

		rangle = dot_v3v3(rmat[1], splineVec);
		CLAMP(rangle, -1.0f, 1.0f);
		rangle = acosf(rangle);

		/* multiply the magnitude of the angle by the influence of the constraint to
		 * control the influence of the SplineIK effect
		 */
		rangle *= tree->con->enforce;

		/* construct rotation matrix from the axis-angle rotation found above
		 *	- this call takes care to make sure that the axis provided is a unit vector first
		 */
		axis_angle_to_mat3(dmat, raxis, rangle);

		/* combine these rotations so that the y-axis of the bone is now aligned as the spline dictates,
		 * while still maintaining roll control from the existing bone animation
		 */
		mul_m3_m3m3(tmat, dmat, rmat); /* m1, m3, m2 */
		normalize_m3(tmat); /* attempt to reduce shearing, though I doubt this'll really help too much now... */
		copy_m4_m3(poseMat, tmat);
	}

	/* step 4: set the scaling factors for the axes */
	{
		/* only multiply the y-axis by the scaling factor to get nice volume-preservation */
		mul_v3_fl(poseMat[1], scaleFac);

		/* set the scaling factors of the x and z axes from... */
		switch (ikData->xzScaleMode) {
			case CONSTRAINT_SPLINEIK_XZS_ORIGINAL:
			{
				/* original scales get used */
				float scale;

				/* x-axis scale */
				scale = len_v3(pchan->pose_mat[0]);
				mul_v3_fl(poseMat[0], scale);
				/* z-axis scale */
				scale = len_v3(pchan->pose_mat[2]);
				mul_v3_fl(poseMat[2], scale);
				break;
			}
			case CONSTRAINT_SPLINEIK_XZS_INVERSE:
			{
				/* old 'volume preservation' method using the inverse scale */
				float scale;

				/* calculate volume preservation factor which is
				 * basically the inverse of the y-scaling factor
				 */
				if (fabsf(scaleFac) != 0.0f) {
					scale = 1.0f / fabsf(scaleFac);

					/* we need to clamp this within sensible values */
					/* NOTE: these should be fine for now, but should get sanitised in future */
					CLAMP(scale, 0.0001f, 100000.0f);
				}
				else
					scale = 1.0f;

				/* apply the scaling */
				mul_v3_fl(poseMat[0], scale);
				mul_v3_fl(poseMat[2], scale);
				break;
			}
			case CONSTRAINT_SPLINEIK_XZS_VOLUMETRIC:
			{
				/* improved volume preservation based on the Stretch To constraint */
				float final_scale;
				
				/* as the basis for volume preservation, we use the inverse scale factor... */
				if (fabsf(scaleFac) != 0.0f) {
					/* NOTE: The method here is taken wholesale from the Stretch To constraint */
					float bulge = powf(1.0f / fabsf(scaleFac), ikData->bulge);
					
					if (bulge > 1.0f) {
						if (ikData->flag & CONSTRAINT_SPLINEIK_USE_BULGE_MAX) {
							float bulge_max = max_ff(ikData->bulge_max, 1.0f);
							float hard = min_ff(bulge, bulge_max);
							
							float range = bulge_max - 1.0f;
							float scale = (range > 0.0f) ? 1.0f / range : 0.0f;
							float soft = 1.0f + range * atanf((bulge - 1.0f) * scale) / (float)M_PI_2;
							
							bulge = interpf(soft, hard, ikData->bulge_smooth);
						}
					}
					if (bulge < 1.0f) {
						if (ikData->flag & CONSTRAINT_SPLINEIK_USE_BULGE_MIN) {
							float bulge_min = CLAMPIS(ikData->bulge_min, 0.0f, 1.0f);
							float hard = max_ff(bulge, bulge_min);
							
							float range = 1.0f - bulge_min;
							float scale = (range > 0.0f) ? 1.0f / range : 0.0f;
							float soft = 1.0f - range * atanf((1.0f - bulge) * scale) / (float)M_PI_2;
							
							bulge = interpf(soft, hard, ikData->bulge_smooth);
						}
					}
					
					/* compute scale factor for xz axes from this value */
					final_scale = sqrtf(bulge);
				}
				else {
					/* no scaling, so scale factor is simple */
					final_scale = 1.0f;
				}
				
				/* apply the scaling (assuming normalised scale) */
				mul_v3_fl(poseMat[0], final_scale);
				mul_v3_fl(poseMat[2], final_scale);
				break;
			}
		}

		/* finally, multiply the x and z scaling by the radius of the curve too,
		 * to allow automatic scales to get tweaked still
		 */
		if ((ikData->flag & CONSTRAINT_SPLINEIK_NO_CURVERAD) == 0) {
			mul_v3_fl(poseMat[0], radius);
			mul_v3_fl(poseMat[2], radius);
		}
	}

	/* step 5: set the location of the bone in the matrix */
	if (ikData->flag & CONSTRAINT_SPLINEIK_NO_ROOT) {
		/* when the 'no-root' option is affected, the chain can retain
		 * the shape but be moved elsewhere
		 */
		copy_v3_v3(poseHead, pchan->pose_head);
	}
	else if (tree->con->enforce < 1.0f) {
		/* when the influence is too low
		 *	- blend the positions for the 'root' bone
		 *	- stick to the parent for any other
		 */
		if (pchan->parent) {
			copy_v3_v3(poseHead, pchan->pose_head);
		}
		else {
			/* FIXME: this introduces popping artifacts when we reach 0.0 */
			interp_v3_v3v3(poseHead, pchan->pose_head, poseHead, tree->con->enforce);
		}
	}
	copy_v3_v3(poseMat[3], poseHead);

	/* finally, store the new transform */
	copy_m4_m4(pchan->pose_mat, poseMat);
	copy_v3_v3(pchan->pose_head, poseHead);

	/* recalculate tail, as it's now outdated after the head gets adjusted above! */
	BKE_pose_where_is_bone_tail(pchan);

	/* done! */
	pchan->flag |= POSE_DONE;
}