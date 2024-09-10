JNIEXPORT void JNICALL Java_org_herac_tuxguitar_player_impl_midiport_winmm_MidiSystem_closePort(JNIEnv* env, jobject obj, jlong ptr)
{
	midi_handle_t *handle = NULL;
	memcpy(&handle, &ptr, sizeof(handle));
	if(handle != NULL && handle->out != NULL){
		midiOutClose(*handle->out);
		free( handle->out );
		handle->out = NULL;
	}
}