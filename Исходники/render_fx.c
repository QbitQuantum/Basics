/*
 * Trail of particles obtained from the image frame
 * args:
 *    frame  - pointer to frame buffer (yuyv format)
 *    width  - frame width
 *    height - frame height
 *    trail_size  - trail size (in frames)
 *    particle_size - maximum size in pixels - should be even (square - size x size)
 *
 * asserts:
 *    frame is not null
 *
 * returns: void
 */
static void fx_particles(uint8_t* frame, int width, int height, int trail_size, int particle_size)
{
	/*asserts*/
	assert(frame != NULL);

	int i,j,w,h = 0;
	int part_w = width>>7;
	int part_h = height>>6;

	/*random generator setup*/
	gsl_rng_env_setup();
	const gsl_rng_type *T = gsl_rng_default;
	gsl_rng *r = gsl_rng_alloc (T);

	/*allocation*/
	if (particles == NULL)
	{
		particles = calloc(trail_size * part_w * part_h, sizeof(particle_t));
		if(particles == NULL)
		{
			fprintf(stderr,"RENDER: FATAL memory allocation failure (fx_particles): %s\n", strerror(errno));
			exit(-1);
		}
	}

	particle_t *part = particles;
	particle_t *part1 = part;

	/*move particles in trail*/
	for (i = trail_size; i > 1; --i)
	{
		part  += (i - 1) * part_w * part_h;
		part1 += (i - 2) * part_w * part_h;

		for (j= 0; j < part_w * part_h; ++j)
		{
			if(part1->decay > 0)
			{
				part->PX = part1->PX + (int) lround(3 * gsl_rng_uniform (r)); /*0  to 3*/
				part->PY = part1->PY -4 + (int) lround(5 * gsl_rng_uniform (r));/*-4 to 1*/

				if(ODD(part->PX)) part->PX++; /*make sure PX is allways even*/

				if((part->PX > (width-particle_size)) || (part->PY > (height-particle_size)) || (part->PX < 0) || (part->PY < 0))
				{
					part->PX = 0;
					part->PY = 0;
					part->decay = 0;
				}
				else
				{
					part->decay = part1->decay - 1;
				}

				part->Y = part1->Y;
				part->U = part1->U;
				part->V = part1->V;
				part->size = part1->size;
			}
			else
			{
				part->decay = 0;
			}
			part++;
			part1++;
		}
		part = particles; /*reset*/
		part1 = part;
	}

	part = particles; /*reset*/
	
	/*get particles from frame (one pixel per particle - make PX allways even)*/
	for(i =0; i < part_w * part_h; i++)
	{
		/* (2 * particle_size) to (width - 4 * particle_size)*/
		part->PX = 2 * particle_size + (int) lround( (width - 6 * particle_size) * gsl_rng_uniform (r));
		/* (2 * particle_size) to (height - 4 * particle_size)*/
		part->PY = 2 * particle_size + (int) lround( (height - 6 * particle_size) * gsl_rng_uniform (r));

		if(ODD(part->PX)) part->PX++;

		int y_pos = part->PX + (part->PY * width);
		int u_pos = (part->PX + (part->PY * width / 2)) / 2;
		int v_pos = u_pos + ((width * height) / 4);

		part->Y = frame[y_pos];
		part->U = frame[u_pos];
		part->V = frame[v_pos];

		part->size = 1 + (int) lround((particle_size -1) * gsl_rng_uniform (r));
		if(ODD(part->size)) part->size++;

		part->decay = (float) trail_size;

		part++; /*next particle*/
	}

	part = particles; /*reset*/
	int line = 0;
	float blend =0;
	float blend1 =0;
	/*render particles to frame (expand pixel to particle size)*/
	for (i = 0; i < trail_size * part_w * part_h; i++)
	{
		if(part->decay > 0)
		{
			int y_pos = part->PX + (part->PY * width);
			int u_pos = (part->PX + (part->PY * width / 2)) / 2;
			int v_pos = u_pos + ((width * height) / 4);

			blend = part->decay/trail_size;
			blend1= 1 - blend;

			//y
			for(h = 0; h <(part->size); h++)
			{
				line = h * width;
				for (w = 0; w <(part->size); w++)
				{
					frame[y_pos + line + w] = CLIP((part->Y * blend) + (frame[y_pos + line + w] * blend1));
				}
			}

			//u v
			for(h = 0; h <(part->size); h+=2)
			{
				line = (h * width) / 4;
				for (w = 0; w <(part->size); w+=2)
				{
					frame[u_pos + line + (w / 2)] = CLIP((part->U * blend) + (frame[u_pos + line + (w / 2)] * blend1));
					frame[v_pos + line + (w / 2)] = CLIP((part->V * blend) + (frame[v_pos + line + (w / 2)] * blend1));
				}
			}
		}
		part++;
	}

	/*free the random seed generator*/
	gsl_rng_free (r);
}