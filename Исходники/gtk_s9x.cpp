int
S9xOpenROM (const char *rom_filename)
{
    uint32 flags;
    bool8  loaded;

    if (gui_config->rom_loaded)
    {
        S9xAutoSaveSRAM ();
    }

#ifdef NETPLAY_SUPPORT
    S9xNetplayDisconnect ();
#endif

    flags = CPU.Flags;

    loaded = FALSE;

    if (Settings.Multi)
        loaded = Memory.LoadMultiCart (Settings.CartAName, Settings.CartBName);
    else if (rom_filename)
        loaded = Memory.LoadROM (rom_filename);

    Settings.StopEmulation = !loaded;

    if (!loaded && rom_filename)
    {
        char dir [_MAX_DIR + 1];
        char drive [_MAX_DRIVE + 1];
        char name [_MAX_FNAME + 1];
        char ext [_MAX_EXT + 1];
        char fname [_MAX_PATH + 1];

        _splitpath (rom_filename, drive, dir, name, ext);
        _makepath (fname, drive, dir, name, ext);

        strcpy (fname, S9xGetDirectory (ROM_DIR));
        strcat (fname, SLASH_STR);
        strcat (fname, name);

        if (ext [0])
        {
            strcat (fname, ".");
            strcat (fname, ext);
        }

        _splitpath (fname, drive, dir, name, ext);
        _makepath (fname, drive, dir, name, ext);

        if ((Settings.StopEmulation = !Memory.LoadROM (fname)))
        {
            fprintf (stderr, _("Error opening: %s\n"), rom_filename);

            loaded = FALSE;
        }
        else
            loaded = TRUE;
    }

    if (loaded)
    {
        Memory.LoadSRAM (S9xGetFilename (".srm", SRAM_DIR));
    }
    else
    {
        CPU.Flags = flags;
        Settings.Paused = 1;

        S9xNoROMLoaded ();
        top_level->refresh ();

        return 1;
    }

    CPU.Flags = flags;

    if (stateMan.init (gui_config->rewind_buffer_size * 1024 * 1024))
    {
        printf ("Using rewind buffer of %uMB\n", gui_config->rewind_buffer_size);
    }

    S9xROMLoaded ();

    return 0;
}