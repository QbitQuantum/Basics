void spTransformConstraint_apply (spTransformConstraint* self) {
	float rotateMix = self->rotateMix, translateMix = self->translateMix, scaleMix = self->scaleMix, shearMix = self->shearMix;
	spBone* target = self->target;
	float ta = target->a, tb = target->b, tc = target->c, td = target->d;
	int i;
	for (i = 0; i < self->bonesCount; ++i) {
		spBone* bone = self->bones[i];

		if (rotateMix > 0) {
			float a = bone->a, b = bone->b, c = bone->c, d = bone->d;
			float r = ATAN2(tc, ta) - ATAN2(c, a) + self->data->offsetRotation * DEG_RAD;
			float cosine, sine;
			if (r > PI) r -= PI2;
			else if (r < -PI) r += PI2;
			r *= rotateMix;
			cosine = COS(r);
			sine = SIN(r);
			CONST_CAST(float, bone->a) = cosine * a - sine * c;
			CONST_CAST(float, bone->b) = cosine * b - sine * d;
			CONST_CAST(float, bone->c) = sine * a + cosine * c;
			CONST_CAST(float, bone->d) = sine * b + cosine * d;
		}

		if (translateMix > 0) {
			float x, y;
			spBone_localToWorld(target, self->data->offsetX, self->data->offsetY, &x, &y);
			CONST_CAST(float, bone->worldX) += (x - bone->worldX) * translateMix;
			CONST_CAST(float, bone->worldY) += (y - bone->worldY) * translateMix;
		}