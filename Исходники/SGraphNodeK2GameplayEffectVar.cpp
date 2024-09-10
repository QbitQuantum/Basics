TSharedRef<SWidget> SGraphNodeK2GameplayEffectVar::OpenGameplayEffectButtonContent(FText ButtonText, FText ButtonTooltipText, FString DocumentationExcerpt)
{
	TSharedPtr<SWidget> ButtonContent;

	SAssignNew(ButtonContent, SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		.Padding(0, 0, 7, 0)
		[
			SNew(SImage)
			.Image(FEditorStyle::GetBrush(TEXT("PropertyWindow.Button_Browse")))
		]
	+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Left)
		[
			SNew(STextBlock)
			.Text(ButtonText)
			.ColorAndOpacity(FLinearColor::White)
		];


	TSharedPtr<SToolTip> Tooltip;

	if (!DocumentationExcerpt.IsEmpty())
	{
		Tooltip = IDocumentation::Get()->CreateToolTip(ButtonTooltipText, NULL, GraphNode->GetDocumentationLink(), DocumentationExcerpt);
	}

	TSharedRef<SButton> OpenGameplayEffectButton = SNew(SButton)
		.ContentPadding(0.0f)
		.ButtonStyle(FEditorStyle::Get(), "NoBorder")
		.OnClicked(this, &SGraphNodeK2GameplayEffectVar::OnOpenGameplayEffect)
		.ToolTipText(ButtonTooltipText)
		.ToolTip(Tooltip)
		.Visibility(this, &SGraphNodeK2GameplayEffectVar::IsOpenGameplayEffectButtonVisible)
		[
			ButtonContent.ToSharedRef()
		];

	OpenGameplayEffectButton->SetCursor(EMouseCursor::Hand);

	return OpenGameplayEffectButton;
}