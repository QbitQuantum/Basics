void RotatePointList (g3sPoint *dest, vmsVector *src, g3sNormal *norms, int n, int o)
{
	fVector	*pfv = gameData.models.fPolyModelVerts + o;
	float		fScale;
#if PROFILING
	time_t	t = clock ();
#endif

dest += o;
if (norms)
	norms += o;
while (n--) {
	dest->p3_key = (short) o;
#if 1
	if (norms) {
		if (norms->nFaces > 1) {
			norms->vNormal.p.x /= norms->nFaces;
			norms->vNormal.p.y /= norms->nFaces;
			norms->vNormal.p.z /= norms->nFaces;
			norms->nFaces = 1;
			VmVecNormalizef (&norms->vNormal, &norms->vNormal);
			}
		dest->p3_normal = *norms++;
		}
	else
#endif
		dest->p3_normal.nFaces = 0;
	fScale = (gameData.models.nScale ? f2fl (gameData.models.nScale) : 1) / 65536.0f;
	if (gameStates.ogl.bUseTransform) {
		pfv->p.x = src->p.x * fScale;
		pfv->p.y = src->p.y * fScale;
		pfv->p.z = src->p.z * fScale;
		}
	else {
		if (gameData.models.nScale) {
			vmsVector v = *src;
			VmVecScale (&v, gameData.models.nScale);
#if 1
			G3TransformPoint (&dest->p3_vec, &v, 0);
#else
			G3TransformAndEncodePoint (dest, &v);
#endif
			}
		else {
#if 1
			G3TransformPoint (&dest->p3_vec, src, 0);
#else
			G3TransformAndEncodePoint (dest, src);
#endif
			}
		pfv->p.x = (float) dest->p3_vec.p.x / 65536.0f;
		pfv->p.y = (float) dest->p3_vec.p.y / 65536.0f;
		pfv->p.z = (float) dest->p3_vec.p.z / 65536.0f;
		}
	dest->p3_index = o++;
	dest->p3_src = *src++;
	dest++;
	pfv++;
	}
#if PROFILING
tTransform += clock () - t;
#endif
}