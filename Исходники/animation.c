void spAnimation_mix (const spAnimation* self, spSkeleton* skeleton, float lastTime, float time, int loop, spEvent** events,
		int* eventsCount, float alpha) {
	int i, n = self->timelinesCount;

	if (loop && self->duration) {
		time = FMOD(time, self->duration);
		lastTime = FMOD(lastTime, self->duration);
	}

	for (i = 0; i < n; ++i)
		spTimeline_apply(self->timelines[i], skeleton, lastTime, time, events, eventsCount, alpha);
}