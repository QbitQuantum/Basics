void BasicQtApp::on_selectedDecoration_currentIndexChanged(const QString &text)
{
    gui->SetWindowTheme("../../../windowdecorations", text.toUtf8().data());
}