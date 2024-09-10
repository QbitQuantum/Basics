// Initialization helper -- 
//  Loads the Restores data and positions the window in its previously saved state
void cef_main_window::RestoreWindowPlacement(int showCmd)
{
    if (showCmd == SW_MAXIMIZE)
    {
        WINDOWPLACEMENT wp;
        ::ZeroMemory(&wp, sizeof (wp));

        wp.length = sizeof(WINDOWPLACEMENT);

        wp.flags            = 0;
        wp.showCmd          = SW_MAXIMIZE;
        wp.ptMinPosition.x  = -1;
        wp.ptMinPosition.y  = -1;
        wp.ptMaxPosition.x  = -1;
        wp.ptMaxPosition.y  = -1;

        wp.rcNormalPosition.left   = CW_USEDEFAULT;
        wp.rcNormalPosition.top    = CW_USEDEFAULT;
        wp.rcNormalPosition.right  = CW_USEDEFAULT;
        wp.rcNormalPosition.bottom = CW_USEDEFAULT;

        GetRegistryInt(::kWindowPostionFolder, ::kPrefRestoreLeft,   NULL, (int&)wp.rcNormalPosition.left);
        GetRegistryInt(::kWindowPostionFolder, ::kPrefRestoreTop,    NULL, (int&)wp.rcNormalPosition.top);
        GetRegistryInt(::kWindowPostionFolder, ::kPrefRestoreRight,  NULL, (int&)wp.rcNormalPosition.right);
        GetRegistryInt(::kWindowPostionFolder, ::kPrefRestoreBottom, NULL, (int&)wp.rcNormalPosition.bottom);

        // This returns FALSE on failure but not sure what we could do in that case
        SetWindowPlacement(&wp);
    }

    ShowWindow(showCmd);
}