void depthtree_find_blobs(Blobtree *blob, const unsigned char *data, const unsigned int w, const unsigned int h, const BlobtreeRect roi, const unsigned char *depth_map, DepthtreeWorkspace *workspace ){
	// Avoid hard crash for null data.
	if( data == NULL ){
		VPRINTF("Runtime error: Input data is NULL! threshtree_filter_blobs aborts.\n");
	}
	//clear old tree
	if( blob->tree != NULL){
		tree_destroy(&blob->tree);
		blob->tree = NULL;
	}
	if( blob->tree_data != NULL){
		free(blob->tree_data);
		blob->tree_data = NULL;
	}
	//get new blob tree structure.
	/*
		 if( blob->grid.height == 11 ){
		 blob->tree = find_depthtree11(data, w, h, roi, depth_map, 
		 workspace, &blob->tree_data);
		 }else{
		 blob->tree = find_depthtree(data, w, h, roi, depth_map, 
		 blob->grid.width,
		 workspace, &blob->tree_data);
		 }*/

	if( blob->grid.width == 1 ){
		blob->tree = find_depthtree(data, w, h, roi, depth_map, 1, workspace, &blob->tree_data);
	}else if( blob->grid.width == 2 ){
		blob->tree = find_depthtree(data, w, h, roi, depth_map, 2, workspace, &blob->tree_data);
	}else if( blob->grid.width == 3 ){
		blob->tree = find_depthtree(data, w, h, roi, depth_map, 3, workspace, &blob->tree_data);
	}else if( blob->grid.width == 4 ){
		blob->tree = find_depthtree(data, w, h, roi, depth_map, 4, workspace, &blob->tree_data);
		/*
			 }else if( blob->grid.width == 5 ){
			 blob->tree = find_depthtree(data, w, h, roi, depth_map, 5, workspace, &blob->tree_data);
			 }else if( blob->grid.width == 6 ){
			 blob->tree = find_depthtree(data, w, h, roi, depth_map, 6, workspace, &blob->tree_data);
			 }else if( blob->grid.width == 7 ){
			 blob->tree = find_depthtree(data, w, h, roi, depth_map, 7, workspace, &blob->tree_data);
			 }else if( blob->grid.width == 8 ){
			 blob->tree = find_depthtree(data, w, h, roi, depth_map, 8, workspace, &blob->tree_data);
			 }else if( blob->grid.width == 9 ){
			 blob->tree = find_depthtree(data, w, h, roi, depth_map, 9, workspace, &blob->tree_data);
			 }else if( blob->grid.width == 10 ){
			 blob->tree = find_depthtree(data, w, h, roi, depth_map, 10, workspace, &blob->tree_data);
			 }else if( blob->grid.width == 11 ){
			 blob->tree = find_depthtree(data, w, h, roi, depth_map, 11, workspace, &blob->tree_data);
			 */
	}else{
		blob->tree = find_depthtree(data, w, h, roi, depth_map, blob->grid.width, workspace, &blob->tree_data);
	}







}