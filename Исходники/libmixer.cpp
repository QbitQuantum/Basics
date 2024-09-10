s32 cellSurMixerGetTimestamp(u64 tag, vm::ptr<u64> stamp)
{
	libmixer.Log("cellSurMixerGetTimestamp(tag=0x%llx, stamp=*0x%x)", tag, stamp);

	*stamp = g_audio.start_time + (tag) * 256000000 / 48000; // ???
	return CELL_OK;
}