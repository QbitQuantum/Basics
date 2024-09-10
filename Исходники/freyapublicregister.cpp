bool FreyaPublicRegister::ConfigModifyRecursion(QVariantMap &varMap, const QStringList &configPath, const ConfModType &type, const QVariant &var)
{
    if(configPath.size() > 0)
    {
        const QString &key = configPath.at(0);

        if(configPath.size() == 1)
        {
            switch (type)
            {
            case eCMADD:
            {
                varMap.insert(key, var);
                return varMap.contains(key);
            }
            case eCMDEL:
            {
                varMap.remove(key);
                return !varMap.contains(key);
            }
            case eCMMOD:
            {
                if(varMap.contains(key))
                {
                    varMap.insert(key, var);
                    return (varMap.value(key) == var);
                }
            }
            default:
                return false;
            }
        }
        else
        {
            QVariant newVar = varMap.value(key);
            if(newVar.type() == QVariant::Map || eCMADD == type)
            {
                QStringList newConfigPath = configPath;
                newConfigPath.removeAt(0);
                QVariantMap tempVarMap = newVar.toMap();
                if(ConfigModifyRecursion(tempVarMap, newConfigPath, type, var))
                {
                    varMap.insert(key, tempVarMap);
                    return true;
                }
            }
        }
    }
    return false;
}