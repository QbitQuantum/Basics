static void
equalizerwin_read_winamp_eqf(VFSFile * file)
{
    Index * presets = aud_import_winamp_presets (file);

    if (! presets)
    {
        SPRINTF (error, _("Error importing Winamp EQF file '%s'"), vfs_get_filename (file));
        aud_interface_show_error (error);
        return;
    }

    if (! index_count (presets))
        goto DONE;

    /* just get the first preset --asphyx */
    EqualizerPreset * preset = index_get (presets, 0);
    equalizerwin_set_preamp(preset->preamp);

    for (int i = 0; i < AUD_EQUALIZER_NBANDS; i ++)
        equalizerwin_set_band(i, preset->bands[i]);

    equalizerwin_eq_changed();

DONE:
    index_free_full (presets, (IndexFreeFunc) aud_equalizer_preset_free);
}