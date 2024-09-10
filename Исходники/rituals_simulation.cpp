void sim_update(Simulator* sim, Tilemap* map, real dt)
{
	Sim_Body *a, *b;
	for(isize times = 0; times < Sim_Iter_i; ++times) {
//#if 0
		if(sim->sort_axis == 0) {
			body_sort_on_x(sim->bodies, sim->bodies_count);
		} else if(sim->sort_axis == 1) {
			body_sort_on_y(sim->bodies, sim->bodies_count);
		}

//#endif 
		Vec2 center_sum1 = v2(0, 0);
		Vec2 center_sum2 = v2(0, 0);
		Vec2 variance = v2(0, 0);
		for(isize i = 0; i < sim->bodies_count; ++i) {
			a = sim->bodies + i;

			//sweep and prune stuff
			center_sum1 += a->shape.center;
			for(isize q = 0; q < 2; ++q) {
				center_sum2.e[q] += a->shape.center.e[q] * a->shape.center.e[q];
			}

			//if(a->is_static) continue;

			for(isize j = i + 1; j < sim->bodies_count; ++j) {
				b = sim->bodies + j;

				uint64 a_is_static = Has_Flag(a->flags, Body_Flag_Static);
				uint64 b_is_static = Has_Flag(b->flags, Body_Flag_Static);
				if(a_is_static && b_is_static) continue;

//#if 0
				if(sim->sort_axis == 0) {
					if(AABB_x1(b->shape) > AABB_x2(a->shape)) {
						break;
					}
				} else if(sim->sort_axis == 1) {
					if(AABB_y1(b->shape) > AABB_y2(a->shape)) {
						break;
					}
				}
//#endif 
			
				if(aabb_intersect(&a->shape, &b->shape)) {
					Vec2 overlap;
					aabb_overlap(&a->shape, &b->shape, &overlap);
					real ovl_mag = sqrtf(v2_dot(overlap, overlap));
					if (ovl_mag < 0.0001f) continue;
					Vec2 normal = overlap * (1.0f / ovl_mag);

					if(a->id == 0 || b->id  == 0) {
						aabb_intersect(&a->shape, &b->shape);
					}
					

					#define _collision_slop (0.8f)
					if(a_is_static && !b_is_static) {
						b->shape.center += overlap;
						Vec2 relative_velocity = b->velocity;
						real velocity_on_normal = v2_dot(relative_velocity, normal);
						if(velocity_on_normal > 0) continue;

						real e = Min(a->restitution, b->restitution);
						real mag = -1.0f * (1.0f + e) * velocity_on_normal;
						mag /= b->inv_mass;
						Vec2 impulse = mag * normal;
						b->collision_vel += b->inv_mass * impulse;
					} else if(!a_is_static && b_is_static) {
						a->shape.center -= overlap;

						Vec2 relative_velocity = -a->velocity;
						real velocity_on_normal = v2_dot(relative_velocity, normal);
						if(velocity_on_normal > 0) continue;

						real e = Min(a->restitution, b->restitution);
						real mag = -1.0f * (1.0f + e) * velocity_on_normal;
						mag /= a->inv_mass + 0;
						Vec2 impulse = mag * normal;
						a->collision_vel -= a->inv_mass * impulse;
					} else {
						Vec2 separation = Max(ovl_mag - _collision_slop, 0) 
							* (1.0f / (a->inv_mass + b->inv_mass)) * 0.5f * normal;
						a->shape.center -= a->inv_mass * separation;
						b->shape.center += b->inv_mass * separation;

						Vec2 relative_velocity = b->velocity - a->velocity;
						real velocity_on_normal = v2_dot(relative_velocity, normal);
						if(velocity_on_normal > 0) continue;

						real e = Min(a->restitution, b->restitution);
						real mag = -1.0f * (1.0f + e) * velocity_on_normal;
						mag /= a->inv_mass + b->inv_mass;
						Vec2 impulse = mag * normal;
						a->collision_vel -= a->inv_mass * impulse;
						b->collision_vel += b->inv_mass * impulse;
					}
				}
			}
		}

		for(isize i = 0; i < 2; ++i) {
			variance.e[i] = center_sum2.e[i] - center_sum1.e[i] * center_sum1.e[i] / 
				sim->bodies_count;
		}
		
		if(variance.x > variance.y) {
			sim->sort_axis = 0;
		} else {
			sim->sort_axis = 1;
		}

		for(isize i = 0; i < sim->bodies_count; ++i) {
			a = sim->bodies + i;
			if(Has_Flag(a->flags, Body_Flag_Static)) continue;
			Vec2 iter_acl = (a->force * a->inv_mass) / Sim_Iter;
			Vec2 new_vel = a->velocity + (dt * iter_acl);
			Vec2 dpos = (a->velocity + new_vel) * 0.5f;
			dpos *= 1.0f / Sim_Iter;
			a->shape.center += dpos * dt;
			a->shape.center += a->collision_vel / Sim_Iter * dt;
			a->velocity = new_vel;
			Tile_Info* tile = map->info + tilemap_get_at(map, a->shape.center);
			real damping = 1.0f;
			if(Has_Flag(a->flags, Body_Flag_No_Friction)) {
				damping = a->damping;
			} else {
				damping = sqrtf(a->damping * a->damping + 
					tile->friction * tile->friction) * Math_InvSqrt2;
			}
			a->velocity *= powf(damping, Sim_Iter);
			a->velocity += a->collision_vel;
			a->collision_vel = v2(0, 0);
		}

	}
	body_sort_on_id(sim->bodies, sim->bodies_count);
}