static
GF_Err gdip_surface_fill(GF_SURFACE _this, GF_STENCIL stencil)
{
	GpStatus ret;
	GpMatrix *newmat;
	struct _stencil *_sten;
	GPGRAPH();
	if (!_this) return GF_BAD_PARAM;
	if (!_graph->current) return GF_OK;
	_sten = (struct _stencil *)stencil;
	assert(_sten);

#ifdef NODRAW
	return GF_OK;
#endif


	if (_graph->clip) GdipSetClipPath(_graph->graph, _graph->clip, CombineModeReplace);

	switch (_sten->type) {
	case GF_STENCIL_SOLID:
		assert(_sten->pSolid);
		GdipFillPath(_graph->graph, _sten->pSolid, _graph->current);
		break;
	case GF_STENCIL_LINEAR_GRADIENT:
		if (_sten->pMat) {
			/*rebuild gradient*/
			gdip_recompute_line_gradient(_sten);

			GdipResetTextureTransform((GpTexture*)_sten->pLinear);
			if (_sten->pMat) {
				GdipCloneMatrix(_sten->pMat, &newmat);
			} else {
				GdipCreateMatrix(&newmat);
			}
			GdipMultiplyMatrix(newmat, _sten->pLinearMat, MatrixOrderPrepend);
			GdipSetTextureTransform((GpTexture*)_sten->pLinear, newmat);
			GdipDeleteMatrix(newmat);
		}
		GdipFillPath(_graph->graph, _sten->pLinear, _graph->current);
		break;
	case GF_STENCIL_RADIAL_GRADIENT:
		/*build gradient*/
		gdip_recompute_radial_gradient(_sten);

		GdipSetCompositingQuality(_graph->graph, CompositingQualityHighSpeed);
		GdipSetInterpolationMode(_graph->graph, InterpolationModeLowQuality);
		GdipSetSmoothingMode(_graph->graph, SmoothingModeHighSpeed);

		/*check if we need to draw solid background (GDIplus doesn't implement padded mode on path gradients)*/
		if (_sten->pSolid) {
			GpPath *tr;
			GdipClonePath(_sten->circle, &tr);
			GdipTransformPath(tr, _sten->pMat);
			GdipSetClipPath(_graph->graph, tr, CombineModeExclude);
			GdipFillPath(_graph->graph, _sten->pSolid, _graph->current);
			GdipDeletePath(tr);
			GdipResetClip(_graph->graph);
			if (_graph->clip) GdipSetClipPath(_graph->graph, _graph->clip, CombineModeReplace);
		}
		GdipFillPath(_graph->graph, _sten->pRadial, _graph->current);
		break;
	case GF_STENCIL_VERTEX_GRADIENT:
		assert(_sten->pRadial);
		if (_sten->pMat) GdipSetTextureTransform((GpTexture*)_sten->pRadial, _sten->pMat);
		ret = GdipFillPath(_graph->graph, _sten->pRadial, _graph->current);
		break;
	case GF_STENCIL_TEXTURE:
		gdip_load_texture(_sten);
		if (_sten->pTexture) {
			GpMatrix *newmat;
			GdipResetTextureTransform((GpTexture*)_sten->pTexture);
			if (_sten->pMat) {
				GdipCloneMatrix(_sten->pMat, &newmat);
			} else {
				GdipCreateMatrix(&newmat);
			}
			/*gdip flip*/
			if (_graph->center_coords && !(_sten->tiling&GF_TEXTURE_FLIP) )
				GdipScaleMatrix(newmat, 1, -1, MatrixOrderPrepend);
			else if (!_graph->center_coords && (_sten->tiling&GF_TEXTURE_FLIP) )
				GdipScaleMatrix(newmat, 1, -1, MatrixOrderPrepend);

			GdipSetTextureTransform((GpTexture*)_sten->pTexture, newmat);
			GdipDeleteMatrix(newmat);

			GdipSetInterpolationMode(_graph->graph, (_sten->tFilter==GF_TEXTURE_FILTER_HIGH_QUALITY) ? InterpolationModeHighQuality : InterpolationModeLowQuality);
			GdipFillPath(_graph->graph, _sten->pTexture, _graph->current);
		}
		break;
	}
	return GF_OK;
}