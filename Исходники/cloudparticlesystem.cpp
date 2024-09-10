		void gen(Vector& v) {
			v.x = (float)(-RAND_MAX) + 2.0f * (float)(rand() % RAND_MAX);
			v.y = (float)(-RAND_MAX) + 2.0f * (float)(rand() % RAND_MAX);
			v.z = (float)(-RAND_MAX) + 2.0f * (float)(rand() % RAND_MAX);
			v.Normalize();
			v *= (innerRadius + outerRadius * (float)(rand() % RAND_MAX) / (float)RAND_MAX);
		}