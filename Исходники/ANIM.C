/* Load an animation from a series of PNG files. */
AG_Anim *
AG_AnimFromPNGs(const char *pattern)
{
	AG_Anim *a = NULL;
	AG_Surface *su;
	char path[AG_PATHNAME_MAX];
	int i;

	for (i = 0; ; i++) {
		Snprintf(path, sizeof(path), pattern, i);
		if (!AG_FileExists(path)) {
			if (i == 0) {
				continue;
			} else {
				break;
			}
		}
		if ((su = AG_SurfaceFromPNG(path)) == NULL) {
			break;
		}
		if (a == NULL) {
			a = AG_AnimRGBA(su->w, su->h,
			    su->format->BitsPerPixel, 0,
			    su->format->Rmask,
			    su->format->Gmask,
			    su->format->Bmask,
			    su->format->Amask);
			if (a == NULL) {
				AG_SurfaceFree(su);
				return (NULL);
			}
		}
		if (AG_AnimFrameNew(a,su) == -1) {
			goto fail;
		}
	}
	return (a);
fail:
	AG_AnimFree(a);
	return (NULL);
}