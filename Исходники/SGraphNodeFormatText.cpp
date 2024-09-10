void SGraphNodeFormatText::UpdateGraphNode()
{
	SGraphNodeK2Base::UpdateGraphNode();

	TSharedRef<SButton> AddPinButton = SNew(SButton)
		.ContentPadding(0.0f)
		.ButtonStyle( FEditorStyle::Get(), "NoBorder" )
		.OnClicked( this, &SGraphNodeFormatText::OnAddPin )
		.ToolTipText(NSLOCTEXT("FormatTextNode", "FormatTextNodeAddPinButton_Tooltip", "Adds an argument to the node"))
		.Visibility(this, &SGraphNodeFormatText::IsAddPinButtonVisible)
		[
			FAddPinButtonHelper::AddPinButtonContent(false)
		];	
		
	AddPinButton->SetCursor( EMouseCursor::Hand );

	//Add buttons to the format text node.
	LeftNodeBox->AddSlot()
	.AutoHeight()
	.VAlign(VAlign_Center)
	.Padding(10,10,10,4)
	[
		AddPinButton
	];
}