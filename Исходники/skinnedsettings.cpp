void SkinnedSettings::on_resetFontsButton_clicked()
{
    QSettings settings (Qmmp::configFile(), QSettings::IniFormat);
    settings.remove("Skinned/pl_font");
    settings.remove("Skinned/pl_header_font");
    settings.remove("Skinned/mw_font");
    loadFonts();
}