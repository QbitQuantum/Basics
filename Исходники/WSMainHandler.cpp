void covise::WSMainHandler::executeModule(const QString &moduleID)
{
    QStringList buffer;
    WSModule *module = getMap()->getModule(moduleID);
    if (module != 0)
    {
        buffer << "EXEC" << module->getName() << module->getInstance() << module->getHost();
        WSMessageHandler::instance()->sendMessage(covise::COVISE_MESSAGE_UI, buffer.join("\n"));
    }
}