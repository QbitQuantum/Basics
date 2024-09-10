TSharedRef<ITableRow> SFindInMaterial::OnGenerateRow(FSearchResult InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	bool bIsACategoryWidget = false;//!bIsInFindWithinBlueprintMode && !InItem->Parent.IsValid();

	if (bIsACategoryWidget)
	{
		return SNew(STableRow< TSharedPtr<FFindInMaterialResult> >, OwnerTable)
			[
				SNew(SBorder)
				.VAlign(VAlign_Center)
				.BorderImage(FEditorStyle::GetBrush("PropertyWindow.CategoryBackground"))
				.Padding(FMargin(2.0f))
				.ForegroundColor(FEditorStyle::GetColor("PropertyWindow.CategoryForeground"))
				[
					SNew(STextBlock)
					.Text(FText::FromString(InItem->Value))
					.ToolTipText(LOCTEXT("BlueprintCatSearchToolTip", "Blueprint"))
				]
			];
	}
	else // Functions/Event/Pin widget
	{
		FString CommentText = InItem->GetCommentText();

		return SNew(STableRow< TSharedPtr<FFindInMaterialResult> >, OwnerTable)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					InItem->CreateIcon()
				]
				+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					.Padding(2, 0)
					[
						SNew(STextBlock)
						.Text(FText::FromString(InItem->Value))
						.HighlightText(HighlightText)
						.ToolTipText(FText::Format(LOCTEXT("BlueprintResultSearchToolTipFmt", "{0} : {1}"), InItem->GetCategory(), FText::FromString(InItem->Value)))
					]
				+ SHorizontalBox::Slot()
					.FillWidth(1)
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					.Padding(2, 0)
					[
						SNew(STextBlock)
						.Text(FText::FromString(InItem->GetValueText()))
						.HighlightText(HighlightText)
					]
				+ SHorizontalBox::Slot()
					.FillWidth(1)
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					.Padding(2, 0)
					[
						SNew(STextBlock)
						.Text(CommentText.IsEmpty() ? FText::GetEmpty() : FText::Format(LOCTEXT("NodeCommentFmt", "Node Comment:[{0}]"), FText::FromString(CommentText)))
						.ColorAndOpacity(FLinearColor::Yellow)
						.HighlightText(HighlightText)
					]
			];
	}
}