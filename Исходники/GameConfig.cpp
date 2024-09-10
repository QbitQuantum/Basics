void GameConfig::saveConfig()
{
    WriteFile* file = FileSystem::openWrite(configfile.c_str());

    file->writeSLE16(CONFIG_VERSION);

    file->write8(UnitColor);
    file->write8(GameMode);
    file->write8(GameType);
    file->writeSLE16(NumberPlayers);
    file->writeSLE16(NumberUnits);
    file->writeSLE16(NumberInitialUnits);

    // TODO lots of other stuff :)
    file->writeSLE32(screen_resolution);
    file->write8(screen_fullscreen);
    file->write8(display_shadows_flag);
    file->write8(display_unit_flags);

    delete file;
}