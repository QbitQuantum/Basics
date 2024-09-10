char* platform::save_file_dialog()
{
    const int32 file_nameSize = MAX_PATH;
    char* file_name = (char*)malloc(file_nameSize);

    OPENFILENAME dialog_params = {};
    dialog_params.lStructSize = sizeof(OPENFILENAME);
    dialog_params.hwndOwner = GetActiveWindow();
    dialog_params.lpstrFilter = "PNG\0*.png\0";
    dialog_params.nFilterIndex = 2;
    dialog_params.lpstrFile = file_name;
    dialog_params.lpstrFile[0] = '\0';
    dialog_params.nMaxFile = file_nameSize;
    dialog_params.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

    BOOL result = GetSaveFileNameA(&dialog_params); // TODO: Unicode support?

    // Suffix .png if required
    {
        size_t len = strlen(file_name);
        if (len <= file_nameSize - 4 &&                                   //
            !((file_name[len-4] == '.') &&                                // Ugh.
              (file_name[len-3] == 'p' || file_name[len-3] == 'P') &&     // TODO: Write some string utility functions
              (file_name[len-2] == 'n' || file_name[len-2] == 'N') &&     //       and clean this up.
              (file_name[len-1] == 'g' || file_name[len-1] == 'G'))) {    //       Also, support for more than just PNGs.
            strcat(file_name, ".png");
        }
    }

    char buffer[256];
    sprintf(buffer, "%s\n", file_name);
    OutputDebugStringA(buffer);

    if (result) {
        return file_name;
    } else {
        free(file_name);
        return 0;
    }
}