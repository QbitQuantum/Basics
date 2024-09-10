	AssetsFoldersTree::AssetsFoldersTree():
		Widget()
	{
		if (!UIManager::IsSingletonInitialzed())
			return;

		mFoldersTree = o2UI.CreateWidget<Tree>("folders");
		*mFoldersTree->layout = WidgetLayout::BothStretch();

		mFoldersTree->SetRearrangeType(Tree::RearrangeType::OnlyReparent);
		mFoldersTree->SetMultipleSelectionAvailable(false);

		mFoldersTree->getObjectParentDelegate = THIS_FUNC(GetFoldersTreeNodeParent);
		mFoldersTree->getObjectChildrenDelegate = THIS_FUNC(GetFoldersTreeNodeChilds);
		mFoldersTree->fillNodeDataByObjectDelegate = THIS_FUNC(SetupFoldersTreeNode);
		mFoldersTree->onNodeDoubleClicked = THIS_FUNC(OnFoldersTreeNodeDblClick);
		mFoldersTree->onObjectsSelectionChanged = THIS_FUNC(OnFoldersTreeSelect);
		mFoldersTree->onNodeRightButtonClicked = THIS_FUNC(OnFoldersTreeRightClick);
		mFoldersTree->UpdateNodesView();

		AddChild(mFoldersTree);

		InitializeContext();
	}