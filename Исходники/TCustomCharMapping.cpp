/**
@SYMTestCaseID SYSLIB-FORM-CT-0148
@SYMTestCaseDesc Test behaviour without custom remapper installed
@SYMTestPriority High
@SYMTestActions  Test behaviour without custom remapper installed
@SYMTestExpectedResults The test must not fail.
@SYMPREQ 1128 Placeholders for invisible characers in rich text shall be customizable
*/
void CTCustomCharMappingStep::RunDefaultBehaviourTestsL()
{
    INFO_PRINTF1(_L(" @SYMTestCaseID:SYSLIB-FORM-CT-0148 "));
    CActiveScheduler* scheduler = new(ELeave) CActiveScheduler;
    CleanupStack::PushL(scheduler);
    CActiveScheduler::Install(scheduler);
    TBuf<100> text;
    TDocModel docModel(text);
    TRect displayRect(0, 0, KDisplayWidth, KDisplayHeight);
    CTextLayout* layout = CTextLayout::NewL(&docModel, displayRect.Width());
    CleanupStack::PushL(layout);
    CTestGraphicsDevice* device = CTestGraphicsDevice::NewL(displayRect.Size(), 0);
    CleanupStack::PushL(device);
    CTextView* view = CTextView::NewL(layout, displayRect, device, device, 0, 0, 0);
    CleanupStack::PushL(view);
    // This is used to force the use of CTestGraphicsContext instead of a normal one
    CWindowGc* offScreenContext;
    User::LeaveIfError(device->CreateContext(offScreenContext));
    CleanupStack::PushL(offScreenContext);
    CTestTextView::SetContextForFlickerFreeRedraw(view, offScreenContext);

    // Start by making sure no custom remapper is installed
    MFormCustomInvisibleCharacterRemapper* remapper;
    remapper = layout->GetCustomInvisibleCharacterRemapper();
    TEST(remapper == NULL);

    // Set all invisible characters to be invisible
    TNonPrintingCharVisibility visibility;
    visibility.SetNoneVisible();
    layout->SetNonPrintingCharsVisibility(visibility);

    // Test remapping with no custom remapper and flags set to invisible
    INFO_PRINTF1(_L("Test uninstalled behaviour - flags invisible"));
    DoTestL(text, layout, device, view, EDefaultBehaviourInvisible);

    // Now set all invisible characters to be visible
    visibility.SetAllVisible();
    layout->SetNonPrintingCharsVisibility(visibility);

    // Test remapping with no custom remapper and flags set to visible
    INFO_PRINTF1(_L("Test uninstalled behaviour - flags visible"));
    DoTestL(text, layout, device, view, EDefaultBehaviourVisible);

    // Test remapping with no custom remapper and some flags explicitly set to invisible
    INFO_PRINTF1(_L("Test uninstalled behaviour - some flags invisible"));
    //Set all invisible characters to be visible
    visibility.SetAllVisible();
    //Set some attributes explicitly to be invisible
    visibility.SetSpacesVisible(EFalse);
    visibility.SetTabsVisible(EFalse);
    visibility.SetPotentialHyphensVisible(EFalse);
    visibility.SetParagraphDelimitersVisible(EFalse);
    visibility.SetPageBreaksVisible(EFalse);
    visibility.SetNonBreakingSpacesVisible(EFalse);
    visibility.SetNonBreakingHyphensVisible(EFalse);
    visibility.SetLineBreaksVisible(EFalse);
    layout->SetNonPrintingCharsVisibility(visibility);
    //Test if the visibility is set accordingly
    DoTestL(text, layout, device, view, ENewTest);

    CleanupStack::PopAndDestroy(offScreenContext);
    CleanupStack::PopAndDestroy(view);
    CleanupStack::PopAndDestroy(device);
    CleanupStack::PopAndDestroy(layout);
    CleanupStack::PopAndDestroy(scheduler);
}