void JWidgetGameInfo::setGameInfo(const JGameInfo& gameinfo)
{
    ui->labi_name->setText( gameinfo.getName() );
    ui->labi_version->setText( gameinfo.getVersion().toString() );
    ui->labi_intro->setText( gameinfo.getIntroduction() );
}