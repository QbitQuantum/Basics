void check_raindrops()
{
	if (random(100) < 50) {
		create_raindrop(ndrops);
	}
	//
	//move rain droplets
	Raindrop *node = ihead;
	while(node) {
		//force is toward the ground
		node->vel[1] += gravity;
		VecCopy(node->pos, node->lastpos);
		if (node->pos[1] > node->lower_boundry) {
			node->pos[0] += node->vel[0] * timeslice;
			node->pos[1] += node->vel[1] * timeslice;
		}
		if (fabs(node->vel[1]) > node->maxvel[1])
			node->vel[1] *= 0.96;
		node->vel[0] *= 0.999;
		//
		node = node->next;
	}
	//}
	//
	//check rain droplets
	int n=0;
	node = ihead;
	while(node) {
		n++;
		#ifdef USE_SOUND
		if (node->pos[1] < 0.0f) {
			//raindrop hit ground
			if (!node->sound && play_sounds) {
				//small chance that a sound will play
				int r = random(50);
				if (r==1)
					fmod_playsound(0);
				//if (r==2)
				//	fmod_playsound(1);
				//sound plays once per raindrop
				node->sound=1;
			}
		}
		#endif //USE_SOUND
		#ifdef USE_UMBRELLA
		//collision detection for raindrop on umbrella
		if (show_umbrella) {
			if (umbrella.shape == UMBRELLA_FLAT) {
				if (node->pos[0] >= (umbrella.pos[0] - umbrella.width2) &&
					node->pos[0] <= (umbrella.pos[0] + umbrella.width2)) {
					if (node->lastpos[1] > umbrella.lastpos[1] ||
						node->lastpos[1] > umbrella.pos[1]) {
						if (node->pos[1] <= umbrella.pos[1] ||
							node->pos[1] <= umbrella.lastpos[1]) {
							if (node->linewidth > 1) {
								Raindrop *savenode = node->next;
								delete_rain(node);
								node = savenode;
								continue;
							}
						}
					}
				}
			}
			if (umbrella.shape == UMBRELLA_ROUND) {
				float d0 = node->pos[0] - umbrella.pos[0];
				float d1 = node->pos[1] - umbrella.pos[1];
				float distance = sqrt((d0*d0)+(d1*d1));
				//Log("distance: %f  umbrella.radius: %f\n",
				//							distance,umbrella.radius);
				if (distance <= umbrella.radius &&
										node->pos[1] > umbrella.pos[1]) {
					if (node->linewidth > 1) {
						if (deflection) {
							//deflect raindrop
							double dot;
							Vec v, up = {0,1,0};
							VecSub(node->pos, umbrella.pos, v);
							normalize(v);
							node->pos[0] =
								umbrella.pos[0] + v[0] * umbrella.radius;
							node->pos[1] =
								umbrella.pos[1] + v[1] * umbrella.radius;
							dot = VecDot(v,up);
							dot += 1.0;
							node->vel[0] += v[0] * dot * 1.0;
							node->vel[1] += v[1] * dot * 1.0;
						} else {
							Raindrop *savenode = node->next;
							delete_rain(node);
							node = savenode;
							continue;
						}
					}
				}
			}
			//VecCopy(umbrella.pos, umbrella.lastpos);
		}
		#endif //USE_UMBRELLA
		if (node->pos[1] < -20.0f || node->pos[1] <= node->lower_boundry) {
			//rain drop is below the visible area
			Raindrop *savenode = node->next;
			delete_rain(node);
			node = savenode;
			continue;
		}
		//if (node->next == NULL) break;
		node = node->next;
	}
	if (maxrain < n)
		maxrain = n;
	//}
}