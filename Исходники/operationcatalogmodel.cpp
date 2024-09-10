/**
 * Executes an operation (or workflow) and generates output
 * @param parameters the input and output parameters that the user filled in
 */
QString OperationCatalogModel::executeoperation(quint64 operationid, const QString& parameters) {
    if ( operationid == 0 || parameters == "")
        return sUNDEF;

    Resource operationresource = mastercatalog()->id2Resource(operationid);
    if ( !operationresource.isValid())
        return sUNDEF;

    em->clearList();

    QString expression;
    QStringList parms = parameters.split("|");
    bool hasInvalidParameters = false;

    for(int i = 0; i < parms.size(); ++ i){
        if (operationresource.ilwisType() & itWORKFLOW){
            int parm = i + 1;
            if (operationresource[QString("pout_%1_optional").arg(parm)] == "false" && i < operationresource["outparameters"].toInt()) {
                QString value = parms[i + operationresource["inparameters"].toInt()];

                QString output = value.split("@@")[0];
                if (output.size() == 0) {
                    em->addError(1, "Output parameter " + QString::number(i) + " is undefined with name " +  operationresource[QString("pout_%1_name").arg(parm)].toString());
                    hasInvalidParameters = true;
                } else {
                    for (const char& c : output.toStdString()) {
                        if (!isalnum(c) && c != ':' && c != '/' && c != '\\' && c != '.') {
                            em->addError(1, "Output parameter " + QString::number(i) + " is not a valid name");
                            hasInvalidParameters = true;
                            break;
                        }
                    }
                }
            }
            if (operationresource[QString("pin_%1_optional").arg(parm)] == "false" && i < operationresource["inparameters"].toInt() && parms[i].size() == 0) {
                em->addError(1, "Input parameter " + QString::number(i) + " is undefined with name " +  operationresource[QString("pin_%1_name").arg(parm)].toString());
                hasInvalidParameters = true;
            }
        }
        if(i < operationresource["inparameters"].toInt()){
            if ( expression.size() != 0)
                expression += ",";
            expression += parms[i];
        }
    }

    if (hasInvalidParameters) return sUNDEF;

    QString allOutputsString;

    bool duplicateFileNames = false;

    QStringList parts = operationresource["outparameters"].toString().split("|");
    int maxparms = parts.last().toInt();
    int count = 1;
    for(int i=(parms.size() - maxparms); i<parms.size(); ++i){
        QString output = parms[i];


        QString pout = QString("pout_%1_type").arg(count++);

        IlwisTypes outputtype = operationresource[pout].toULongLong();
        if ( output.indexOf("@@") != -1 ){
            QString format;
            QStringList parts = output.split("@@");
            output = parts[0];
            if ( output == "")
                continue;

            //Check if user didnt put the same output name in another output field
            int occurences = 0;
            for(int j=(parms.size() - maxparms); j<parms.size(); ++j){
                QString compareString = parms[j].split("@@")[0];
                if(output == compareString){
                    occurences++;
                }
            }

            //Add the duplicate name to the list of duplicate names
            if(occurences>1){
                duplicateFileNames = true;
                em->addError(1, "Workflow did not execute, multiple occurences of an output name");
            }

            QString formatName = parts[1];

            if ( operationresource.ilwisType() & itWORKFLOW) {
                QStringList existingFileNames;

                DIR *directory;

                //If not memory
                QString fileName;

                if(formatName == "Memory" ){
                    //Get all files in the internal catalog
                    QString dataLocation = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/internalcatalog";
                    directory = opendir(dataLocation.toStdString().c_str());
                }else {
                    //Get all files in the directory
                    QString dataLocation = output;
                    dataLocation.remove("file:///");

                    QStringList splitUrl = dataLocation.split("/");

                    fileName = splitUrl.last();

                    QString query = "name='" + formatName + "'";
                    std::multimap<QString, Ilwis::DataFormat>  formats = Ilwis::DataFormat::getSelectedBy(Ilwis::DataFormat::fpNAME, query);
                    if ( formats.size() == 1){
                        QString connector = (*formats.begin()).second.property(DataFormat::fpCONNECTOR).toString();
                        QString code = (*formats.begin()).second.property(DataFormat::fpCODE).toString();

                        QVariantList extensions = Ilwis::DataFormat::getFormatProperties(DataFormat::fpEXTENSION,outputtype, connector, code);

                        fileName += ".";
                        fileName += extensions[0].toString();
                    }

                    splitUrl.removeLast();

                    dataLocation = splitUrl.join("/");

                    directory = opendir(dataLocation.toStdString().c_str());
                }

                struct dirent *file;

                //Put the existing file names in a list for later use
                while ((file = readdir (directory)) != NULL) {
                    existingFileNames.push_back(file->d_name);
                }

                closedir(directory);

                //Check if a file with the same name already exist
                for(int j=0;j<existingFileNames.size();++j){
                    if(formatName == "Memory"){
                        if(existingFileNames[j] == output) {
                            duplicateFileNames = true;
                            em->addError(1, "Workflow did not execute duplicate name: " + output + ". Please change this name.");
                        }
                    }else{
                        if(existingFileNames[j] == fileName){
                            duplicateFileNames = true;
                            em->addError(1, "Workflow did not execute duplicate name: " + fileName + ". Please change this name.");
                        }
                    }
                }
            }

            if ( hasType(outputtype, itCOLUMN)){
                if ( formatName == "Memory"){
                    output = modifyTableOutputUrl(output, parms);
                }else
                    output = parms[0] + "[" + output + "]";
            }
            if ( formatName == "Keep original"){
                IIlwisObject obj;
                obj.prepare(parms[0], operationresource["pin_1_type"].toULongLong());
                if ( obj.isValid()){
                    IlwisTypes type = operationresource[pout].toULongLong();
                    QVariantList values = DataFormat::getFormatProperties(DataFormat::fpCODE,type,obj->provider());
                    if ( values.size() != 0){
                        format = "{format(" + obj->provider() + ",\"" + values[0].toString() + "\")}";
                    }else{
                        kernel()->issues()->log(QString("No valid conversion found for provider %1 and format %2").arg(obj->provider()).arg(IlwisObject::type2Name(type)));
                        return sUNDEF;
                    }
                }
            }
            //overrule the user if he wants to store things in the internalcatalog, then the format is by defintion stream
            if ( context()->workingCatalog()->source().url() == INTERNAL_OBJECT)
                formatName == "Memory";
            if ( formatName != "Memory"){ // special case
                if ( format == "") {
                    QString query = "name='" + formatName + "'";
                    std::multimap<QString, Ilwis::DataFormat>  formats = Ilwis::DataFormat::getSelectedBy(Ilwis::DataFormat::fpNAME, query);
                    if ( formats.size() == 1){
                        format = "{format(" + (*formats.begin()).second.property(DataFormat::fpCONNECTOR).toString() + ",\"" +
                                (*formats.begin()).second.property(DataFormat::fpCODE).toString() + "\")}";
                    }
                }
                // if there is no path we extend it with a path unless the output is a new column, output is than the "old" table so no new output object
                if ( output.indexOf("://") == -1 )
                    output = context()->workingCatalog()->source().url().toString() + "/" + output + format;
                else
                    output = output + format;
            }else{
                if ( hasType(outputtype,itRASTER)){
                    format = "{format(stream,\"rastercoverage\")}";
                }else if (hasType(outputtype, itFEATURE)){
                    format = "{format(stream,\"featurecoverage\")}";
                }else if (hasType(outputtype, itTABLE | itCOLUMN)){
                    format = "{format(stream,\"table\")}";
                }else if (hasType(outputtype, itCATALOG)){
                    format = "{format(stream,\"catalog\")}";
                }else if (hasType(outputtype, itDOMAIN)){
                    format = "{format(stream,\"domain\")}";
                }else if (hasType(outputtype, itCOORDSYSTEM)){
                    format = "{format(stream,\"coordinatesystem\")}";
                }else if (hasType(outputtype, itGEOREF)){
                    format = "{format(stream,\"georeference\")}";
                }

                output = output + format;
            }
        }

        if(!allOutputsString.isEmpty()){
            allOutputsString.append(",");
        }
        allOutputsString += output;
    }

    if(!duplicateFileNames){
        if ( allOutputsString == "")
            expression = QString("script %1(%2)").arg(operationresource.name()).arg(expression);
        else
            expression = QString("script %1=%2(%3)").arg(allOutputsString).arg(operationresource.name()).arg(expression);

        OperationExpression opExpr(expression);

        try {
            QThread* thread = new QThread;
            OperationWorker* worker = new OperationWorker(opExpr);
            worker->moveToThread(thread);
            thread->connect(thread, &QThread::started, worker, &OperationWorker::process);
            thread->connect(worker, &OperationWorker::finished, thread, &QThread::quit);
            thread->connect(worker, &OperationWorker::finished, worker, &OperationWorker::deleteLater);
            thread->connect(thread, &QThread::finished, thread, &QThread::deleteLater);
            thread->start();

            return "TODO";
        } catch (const ErrorObject& err){
            emit error(err.message());
        }
    }
    return sUNDEF;
}