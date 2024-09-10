bool TabViewDesignerAction::createFile(const QString &filePath)
{
    Utils::TextFileFormat textFileFormat;
    textFileFormat.codec = Core::EditorManager::defaultTextCodec();
    QString errorMessage;

    const QString componentString("import QtQuick 2.1\nimport QtQuick.Controls 1.0\n\nItem {\n\n}");

    return textFileFormat.writeFile(filePath, componentString, &errorMessage);

}