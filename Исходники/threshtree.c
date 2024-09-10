bool threshtree_realloc_workspace(
		const unsigned int max_comp,
		ThreshtreeWorkspace **pworkspace
		){

	ThreshtreeWorkspace *r = *pworkspace;
	r->max_comp = max_comp;
	if(
			( r->comp_same = (unsigned int*) realloc(r->comp_same, max_comp*sizeof(unsigned int) ) ) == NULL ||
			( r->prob_parent = (unsigned int*) realloc(r->prob_parent, max_comp*sizeof(unsigned int) ) ) == NULL ||
#ifdef BLOB_COUNT_PIXEL
			( r->comp_size = (unsigned int*) realloc(r->comp_size, max_comp*sizeof(unsigned int) ) ) == NULL ||
#endif
#ifdef BLOB_DIMENSION
			( r->top_index = (unsigned int*) realloc(r->top_index, max_comp*sizeof(unsigned int) ) ) == NULL ||
			( r->left_index = (unsigned int*) realloc(r->left_index, max_comp*sizeof(unsigned int) ) ) == NULL ||
			( r->right_index = (unsigned int*) realloc(r->right_index, max_comp*sizeof(unsigned int) ) ) == NULL ||
			( r->bottom_index = (unsigned int*) realloc(r->bottom_index, max_comp*sizeof(unsigned int) ) ) == NULL ||
#endif
#ifdef BLOB_BARYCENTER_TYPE
			( r->pixel_sum_X = (BLOB_BARYCENTER_TYPE*) realloc(r->pixel_sum_X, max_comp*sizeof(BLOB_BARYCENTER_TYPE) ) ) == NULL ||
			( r->pixel_sum_Y = (BLOB_BARYCENTER_TYPE*) realloc(r->pixel_sum_Y, max_comp*sizeof(BLOB_BARYCENTER_TYPE) ) ) == NULL ||
#endif
			0 ){
		// realloc failed
		VPRINTF("Critical error: Reallocation of workspace failed!\n");
		threshtree_destroy_workspace( pworkspace );
		return false;
	}

	free(r->blob_id_filtered);//omit unnessecary reallocation and omit wrong/low size
	r->blob_id_filtered = NULL;//should be allocated later if needed.

	return true;
}