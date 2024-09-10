void SGameplayTagQueryWidget::Construct(const FArguments& InArgs, const TArray<FEditableGameplayTagQueryDatum>& EditableTagQueries)
{
	ensure(EditableTagQueries.Num() > 0);
	TagQueries = EditableTagQueries;

	bReadOnly = InArgs._ReadOnly;
	OnSaveAndClose = InArgs._OnSaveAndClose;
	OnCancel = InArgs._OnCancel;

	// Tag the assets as transactional so they can support undo/redo
	for (int32 AssetIdx = 0; AssetIdx < TagQueries.Num(); ++AssetIdx)
	{
		UObject* TagQueryOwner = TagQueries[AssetIdx].TagQueryOwner.Get();
		if (TagQueryOwner)
		{
			TagQueryOwner->SetFlags(RF_Transactional);
		}
	}

	// build editable query object tree from the runtime query data
	UEditableGameplayTagQuery* const EQ = CreateEditableQuery(*TagQueries[0].TagQuery);
	EditableQuery = EQ;

	// create details view for the editable query object
	FDetailsViewArgs ViewArgs;
	ViewArgs.bAllowSearch = false;
	ViewArgs.bHideSelectionTip = true;
	ViewArgs.bShowActorLabel = false;
	
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	Details = PropertyModule.CreateDetailView(ViewArgs);
	Details->SetObject(EQ);

	ChildSlot
	[
		SNew(SScaleBox)
		.HAlign(EHorizontalAlignment::HAlign_Left)
		.VAlign(EVerticalAlignment::VAlign_Top)
		.StretchDirection(EStretchDirection::DownOnly)
		.Stretch(EStretch::ScaleToFit)
		.Content()
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.VAlign(VAlign_Top)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SButton)
						.IsEnabled(!bReadOnly)
						.OnClicked(this, &SGameplayTagQueryWidget::OnSaveAndCloseClicked)
						.Text(LOCTEXT("GameplayTagQueryWidget_SaveAndClose", "Save and Close"))
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(SButton)
						.OnClicked(this, &SGameplayTagQueryWidget::OnCancelClicked)
						.Text(LOCTEXT("GameplayTagQueryWidget_Cancel", "Close Without Saving"))
					]
				]
				// to delete!
				+ SVerticalBox::Slot()
				[
					Details.ToSharedRef()
				]
			]
		]
	];
}