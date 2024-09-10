static int rule_goal_avoid(BoidRule *rule, BoidBrainData *bbd, BoidValues *val, ParticleData *pa)
{
	BoidRuleGoalAvoid *gabr = (BoidRuleGoalAvoid*) rule;
	BoidSettings *boids = bbd->part->boids;
	BoidParticle *bpa = pa->boid;
	EffectedPoint epoint;
	ListBase *effectors = bbd->sim->psys->effectors;
	EffectorCache *cur, *eff = NULL;
	EffectorCache temp_eff;
	EffectorData efd, cur_efd;
	float mul = (rule->type == eBoidRuleType_Avoid ? 1.0 : -1.0);
	float priority = 0.0f, len = 0.0f;
	int ret = 0;

	pd_point_from_particle(bbd->sim, pa, &pa->state, &epoint);

	/* first find out goal/predator with highest priority */
	if(effectors) for(cur = effectors->first; cur; cur=cur->next) {
		Object *eob = cur->ob;
		PartDeflect *pd = cur->pd;

		if(gabr->ob && (rule->type != eBoidRuleType_Goal || gabr->ob != bpa->ground)) {
			if(gabr->ob == eob) {
				/* TODO: effectors with multiple points */
				if(get_effector_data(cur, &efd, &epoint, 0)) {
					if(cur->pd && cur->pd->forcefield == PFIELD_BOID)
						priority = mul * pd->f_strength * effector_falloff(cur, &efd, &epoint, bbd->part->effector_weights);
					else
						priority = 1.0;

					eff = cur;
				}
				break;
			}
		}
		else if(rule->type == eBoidRuleType_Goal && eob == bpa->ground)
			; /* skip current object */
		else if(pd->forcefield == PFIELD_BOID && mul * pd->f_strength > 0.0f && get_effector_data(cur, &cur_efd, &epoint, 0)) {
			float temp = mul * pd->f_strength * effector_falloff(cur, &cur_efd, &epoint, bbd->part->effector_weights);

			if(temp == 0.0f)
				; /* do nothing */
			else if(temp > priority) {
				priority = temp;
				eff = cur;
				efd = cur_efd;
				len = efd.distance;
			}
			/* choose closest object with same priority */
			else if(temp == priority && efd.distance < len) {
				eff = cur;
				efd = cur_efd;
				len = efd.distance;
			}
		}
	}

	/* if the object doesn't have effector data we have to fake it */
	if(eff == NULL && gabr->ob) {
		memset(&temp_eff, 0, sizeof(EffectorCache));
		temp_eff.ob = gabr->ob;
		temp_eff.scene = bbd->sim->scene;
		eff = &temp_eff;
		get_effector_data(eff, &efd, &epoint, 0);
		priority = 1.0f;
	}

	/* then use that effector */
	if(priority > (rule->type==eBoidRuleType_Avoid ? gabr->fear_factor : 0.0f)) { /* with avoid, factor is "fear factor" */
		Object *eob = eff->ob;
		PartDeflect *pd = eff->pd;
		float surface = (pd && pd->shape == PFIELD_SHAPE_SURFACE) ? 1.0f : 0.0f;

		if(gabr->options & BRULE_GOAL_AVOID_PREDICT) {
			/* estimate future location of target */
			get_effector_data(eff, &efd, &epoint, 1);

			mul_v3_fl(efd.vel, efd.distance / (val->max_speed * bbd->timestep));
			add_v3_v3(efd.loc, efd.vel);
			sub_v3_v3v3(efd.vec_to_point, pa->prev_state.co, efd.loc);
			efd.distance = len_v3(efd.vec_to_point);
		}

		if(rule->type == eBoidRuleType_Goal && boids->options & BOID_ALLOW_CLIMB && surface!=0.0f) {
			if(!bbd->goal_ob || bbd->goal_priority < priority) {
				bbd->goal_ob = eob;
				copy_v3_v3(bbd->goal_co, efd.loc);
				copy_v3_v3(bbd->goal_nor, efd.nor);
			}
		}
		else if(rule->type == eBoidRuleType_Avoid && bpa->data.mode == eBoidMode_Climbing &&
			priority > 2.0f * gabr->fear_factor) {
			/* detach from surface and try to fly away from danger */
			negate_v3_v3(efd.vec_to_point, bpa->gravity);
		}

		copy_v3_v3(bbd->wanted_co, efd.vec_to_point);
		mul_v3_fl(bbd->wanted_co, mul);

		bbd->wanted_speed = val->max_speed * priority;

		/* with goals factor is approach velocity factor */
		if(rule->type == eBoidRuleType_Goal && boids->landing_smoothness > 0.0f) {
			float len2 = 2.0f*len_v3(pa->prev_state.vel);

			surface *= pa->size * boids->height;

			if(len2 > 0.0f && efd.distance - surface < len2) {
				len2 = (efd.distance - surface)/len2;
				bbd->wanted_speed *= powf(len2, boids->landing_smoothness);
			}
		}

		ret = 1;
	}

	return ret;
}