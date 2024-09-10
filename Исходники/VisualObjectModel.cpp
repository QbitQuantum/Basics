	VisualObjectModel::~VisualObjectModel()
	{
		assert(refCount == 0);

		if (filename != NULL) delete [] filename;

		if (sharedModel != NULL)
		{
			delete sharedModel;
			sharedModel = NULL;
		}

		visual_object_model_allocations--;
		assert(visual_object_model_allocations >= 0);
		visualObjectModelList.remove(this);
	}