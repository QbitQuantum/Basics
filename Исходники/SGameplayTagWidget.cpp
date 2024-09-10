void SGameplayTagWidget::Construct(const FArguments& InArgs, const TArray<FEditableGameplayTagContainerDatum>& EditableTagContainers)
{
	ensure(EditableTagContainers.Num() > 0);
	TagContainers = EditableTagContainers;

	OnTagChanged = InArgs._OnTagChanged;
	bReadOnly = InArgs._ReadOnly;
	TagContainerName = InArgs._TagContainerName;
	bMultiSelect = InArgs._MultiSelect;
	PropertyHandle = InArgs._PropertyHandle;
	bIsAddingNewTag = false;
	RootFilterString = InArgs._Filter;

	IGameplayTagsModule::Get().GetGameplayTagsManager().GetFilteredGameplayRootTags(InArgs._Filter, TagItems);
	bool CanAddFromINI = UGameplayTagsManager::ShouldImportTagsFromINI(); // We only support adding new tags to the ini files.

	// Tag the assets as transactional so they can support undo/redo
	for (int32 AssetIdx = 0; AssetIdx < TagContainers.Num(); ++AssetIdx)
	{
		UObject* TagContainerOwner = TagContainers[AssetIdx].TagContainerOwner.Get();
		if (TagContainerOwner)
		{
			TagContainerOwner->SetFlags(RF_Transactional);
		}
	}

	ChildSlot
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			.VAlign(VAlign_Top)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(2.0f, 2.0f)
				.AutoWidth()
				[
					SAssignNew(NewTagTextBox, SEditableTextBox)
					.MinDesiredWidth(210.0f)
					.HintText(LOCTEXT("NewTag", "X.Y.Z"))
					.OnTextCommitted(this, &SGameplayTagWidget::OnNewGameplayTagCommited)
					.Visibility(CanAddFromINI ? EVisibility::Visible : EVisibility::Collapsed)
				]
				+ SHorizontalBox::Slot()
				.Padding(2.0f, 2.0f)
				.AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("AddNew", "Add New"))
					.OnClicked(this, &SGameplayTagWidget::OnNewGameplayTagButtonPressed)
					.Visibility(CanAddFromINI ? EVisibility::Visible : EVisibility::Collapsed)
				]
			]

			+SVerticalBox::Slot()
			.AutoHeight()
			.VAlign(VAlign_Top)
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.OnClicked(this, &SGameplayTagWidget::OnExpandAllClicked)
					.Text(LOCTEXT("GameplayTagWidget_ExpandAll", "Expand All"))
				]
				+SHorizontalBox::Slot()
				.AutoWidth()

				[
					SNew(SButton)
					.OnClicked(this, &SGameplayTagWidget::OnCollapseAllClicked)
					.Text(LOCTEXT("GameplayTagWidget_CollapseAll", "Collapse All"))
				]
				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.IsEnabled(!bReadOnly)
					.OnClicked(this, &SGameplayTagWidget::OnClearAllClicked)
					.Text(LOCTEXT("GameplayTagWidget_ClearAll", "Clear All"))
				]
				+SHorizontalBox::Slot()
				.VAlign( VAlign_Center )
				.FillWidth(1.f)
				.Padding(5,1,5,1)
				[
					SAssignNew(SearchTagBox, SSearchBox)
					.HintText(LOCTEXT("GameplayTagWidget_SearchBoxHint", "Search Gameplay Tags"))
					.OnTextChanged( this, &SGameplayTagWidget::OnFilterTextChanged )
				]
			]
			+SVerticalBox::Slot()
			[
				SNew(SBorder)
				.Padding(FMargin(4.f))
				[
					SAssignNew(TagTreeWidget, STreeView< TSharedPtr<FGameplayTagNode> >)
					.TreeItemsSource(&TagItems)
					.OnGenerateRow(this, &SGameplayTagWidget::OnGenerateRow)
					.OnGetChildren(this, &SGameplayTagWidget::OnGetChildren)
					.OnExpansionChanged( this, &SGameplayTagWidget::OnExpansionChanged)
					.SelectionMode(ESelectionMode::Multi)
				]
			]
		]
	];

	// Force the entire tree collapsed to start
	SetTagTreeItemExpansion(false);
	 
	LoadSettings();

	// Strip any invalid tags from the assets being edited
	VerifyAssetTagValidity();
}