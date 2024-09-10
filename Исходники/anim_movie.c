static void free_anim_avi(struct anim *anim)
{
#if defined(_WIN32) && !defined(FREE_WINDOWS)
	int i;
#endif

	if (anim == NULL) return;
	if (anim->avi == NULL) return;

	AVI_close(anim->avi);
	MEM_freeN(anim->avi);
	anim->avi = NULL;

#if defined(_WIN32) && !defined(FREE_WINDOWS)

	if (anim->pgf) {
		AVIStreamGetFrameClose(anim->pgf);
		anim->pgf = NULL;
	}

	for (i = 0; i < anim->avistreams; i++) {
		AVIStreamRelease(anim->pavi[i]);
	}
	anim->avistreams = 0;

	if (anim->pfileopen) {
		AVIFileRelease(anim->pfile);
		anim->pfileopen = 0;
		AVIFileExit();
	}
#endif

	anim->duration = 0;
}