void GBASerialize(struct GBA* gba, struct GBASerializedState* state) {
	STORE_32(GBA_SAVESTATE_MAGIC + GBA_SAVESTATE_VERSION, 0, &state->versionMagic);
	STORE_32(gba->biosChecksum, 0, &state->biosChecksum);
	STORE_32(gba->romCrc32, 0, &state->romCrc32);

	if (gba->memory.rom) {
		state->id = ((struct GBACartridge*) gba->memory.rom)->id;
		memcpy(state->title, ((struct GBACartridge*) gba->memory.rom)->title, sizeof(state->title));
	} else {
		state->id = 0;
		memset(state->title, 0, sizeof(state->title));
	}

	int i;
	for (i = 0; i < 16; ++i) {
		STORE_32(gba->cpu->gprs[i], i * sizeof(state->cpu.gprs[0]), state->cpu.gprs);
	}
	STORE_32(gba->cpu->cpsr.packed, 0, &state->cpu.cpsr.packed);
	STORE_32(gba->cpu->spsr.packed, 0, &state->cpu.spsr.packed);
	STORE_32(gba->cpu->cycles, 0, &state->cpu.cycles);
	STORE_32(gba->cpu->nextEvent, 0, &state->cpu.nextEvent);
	for (i = 0; i < 6; ++i) {
		int j;
		for (j = 0; j < 7; ++j) {
			STORE_32(gba->cpu->bankedRegisters[i][j], (i * 7 + j) * sizeof(gba->cpu->bankedRegisters[0][0]), state->cpu.bankedRegisters);
		}
		STORE_32(gba->cpu->bankedSPSRs[i], i * sizeof(gba->cpu->bankedSPSRs[0]), state->cpu.bankedSPSRs);
	}

	STORE_32(gba->memory.biosPrefetch, 0, &state->biosPrefetch);
	STORE_32(gba->cpu->prefetch[0], 0, state->cpuPrefetch);
	STORE_32(gba->cpu->prefetch[1], 4, state->cpuPrefetch);
	STORE_32(gba->memory.lastPrefetchedPc, 0, &state->lastPrefetchedPc);

	GBASerializedMiscFlags miscFlags = 0;
	miscFlags = GBASerializedMiscFlagsSetHalted(miscFlags, gba->cpu->halted);
	STORE_32(miscFlags, 0, &state->miscFlags);

	GBAMemorySerialize(&gba->memory, state);
	GBAIOSerialize(gba, state);
	GBAVideoSerialize(&gba->video, state);
	GBAAudioSerialize(&gba->audio, state);
	GBASavedataSerialize(&gba->memory.savedata, state);


#ifndef _MSC_VER
	struct timeval tv;
	if (!gettimeofday(&tv, 0)) {
		uint64_t usec = tv.tv_usec;
		usec += tv.tv_sec * 1000000LL;
		STORE_64(usec, 0, &state->creationUsec);
	}
#else
	struct timespec ts;
	if (timespec_get(&ts, TIME_UTC)) {
		uint64_t usec = ts.tv_nsec / 1000;
		usec += ts.tv_sec * 1000000LL;
		STORE_64(usec, 0, &state->creationUsec);
	}
#endif
	else {
		state->creationUsec = 0;
	}
	state->associatedStreamId = 0;
	if (gba->rr) {
		gba->rr->stateSaved(gba->rr, state);
	}
}