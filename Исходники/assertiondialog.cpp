/**
 * Presents the user with the assertion failed dialog box, and returns the
 * action that the user chose to perform
 */
AssertionDialog::EUserAction AssertionDialog::ShowDialog() const
{
    // The buttons that will appear on the assertion dialog
    const TASKDIALOG_BUTTON cb[] =
    {
        { 0, L"Save crash information (default)\nYou can help the developers of "
             L"this program by e-mailing them this crash information after saving "
             L"it to your computer" },
        { 1, L"Fire up the debugger (advanced)\nTriggers a breakpoint in Visual "
             L"Studio and jumps to the offending line of code" },
        { 2, L"Quit the application\nOh no! We promise not to crash again :(" }
    };

    // Create a dialog to display the assertion information and configure
    // its options
    TASKDIALOGCONFIG tc = { 0 };

    tc.cbSize = sizeof(tc);
    tc.hwndParent = mWindowHandle;
    tc.hInstance = mAppInstance;
    tc.dwFlags = TDF_USE_HICON_MAIN | TDF_USE_HICON_FOOTER | TDF_EXPAND_FOOTER_AREA | TDF_USE_COMMAND_LINKS;

    LoadIconWithScaleDown(
        NULL,
        MAKEINTRESOURCE(IDI_ERROR),  /*IDI_ERROR,*/
        GetSystemMetrics(SM_CXICON),
        GetSystemMetrics(SM_CYICON),
        &tc.hMainIcon);

    LoadIconWithScaleDown(
        NULL,
        IDI_INFORMATION,
        GetSystemMetrics(SM_CXSMICON),
        GetSystemMetrics(SM_CYSMICON),
        &tc.hFooterIcon);

    tc.pszWindowTitle = L"Application Assertion";
    tc.pszContent = mMessage.c_str();
    tc.pszMainInstruction = L"An internal assertion check has failed";
    tc.pszFooter = mExpression.c_str();

    tc.cButtons = ARRAYSIZE(cb);
    tc.pButtons = cb;
    tc.nDefaultButton = 0;

    // After all that tedious set up work, we can finally show off our fancy shmancy assertion dialog!
    int buttonPressed = 0;
    int commandPressed = 0;
    BOOL verificationChecked = false;

    TaskDialogIndirect(
        &tc,
        &buttonPressed,
        &commandPressed,
        &verificationChecked);

    // Return which action was selected
    switch (buttonPressed)
    {
        case 0:
            return EUSERACTION_SAVE;
        case 1:
            return EUSERACTION_DEBUG;
        case 2:
            return EUSERACTION_QUIT;
        default:
            return EUSERACTION_QUIT;
    }
}