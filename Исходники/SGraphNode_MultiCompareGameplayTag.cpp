void SGraphNode_MultiCompareGameplayTag::CreateOutputSideRemoveButton(TSharedPtr<SVerticalBox> OutputBox)
{
	TSharedPtr<SWidget> ButtonContent;
	SAssignNew(ButtonContent, SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Left)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("CompareNode", "CompareNodeRemovePinButton", "Remove Case"))
			.ColorAndOpacity(FLinearColor::White)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(7, 0, 0, 0)
		[
			SNew(SImage)
			.Image(FEditorStyle::GetBrush(TEXT("PropertyWindow.Button_RemoveFromArray")))
		];

	TSharedPtr<SToolTip> Tooltip;
	Tooltip = IDocumentation::Get()->CreateToolTip(NSLOCTEXT("CompareNode", "CompareNodeRemoveCaseButton_Tooltip", "Remove last case pins"), NULL, GraphNode->GetDocumentationLink(), FString());

	TSharedRef<SButton> RemovePinButton = SNew(SButton)
		.ContentPadding(0.0f)
		.ButtonStyle(FEditorStyle::Get(), "NoBorder")
		.OnClicked(this, &SGraphNode_MultiCompareGameplayTag::OnRemovePin)
		.ToolTipText(NSLOCTEXT("CompareNode", "CompareNodeRemovePinButton_Tooltip", "Remove last pin"))
		.ToolTip(Tooltip)
		.Visibility(this, &SGraphNode_MultiCompareGameplayTag::IsRemovePinButtonVisible)
		[
			ButtonContent.ToSharedRef()
		];

	RemovePinButton->SetCursor(EMouseCursor::Hand);

	FMargin AddPinPadding = Settings->GetOutputPinPadding();
	AddPinPadding.Top += 6.0f;

	OutputBox->AddSlot()
		.AutoHeight()
		.VAlign(VAlign_Center)
		.Padding(AddPinPadding)
		[
			RemovePinButton
		];
}