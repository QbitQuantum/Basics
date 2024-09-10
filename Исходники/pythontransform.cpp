bool PythonTransform::setModuleFile(const QString &fileName)
{
    if (type == ModulesManagement::AUTO) {
        Q_EMIT error(tr("Not allowed to change the module for auto loaded modules"),id);
        return false;
    }
    if (fileName == moduleFileName) {
        qDebug() << "nothing to be done here, filename already set";
        return true; // nothing to be done here
    }

    QString val = moduleManagement->addModule(fileName, type);
    if (!val.isEmpty()) {
        PyGILState_STATE lgstate;
        lgstate = PyGILState_Ensure();
        Py_XDECREF(pModule);
        pModule = nullptr;
        moduleName = val;
        moduleFileName = fileName;

        if  (!loadModule()) {
           Q_EMIT error(tr("Error while loading module"),id);
        } else {
            qDebug() << "Module appeared to have been loaded successfully";
        }
        PyGILState_Release(lgstate);
        return true;
    }
    return false;
}