MatrixXd Warp::readsLm(const QString &electrodeFileName)
{
    MatrixXd electrodes;
    QFile file(electrodeFileName);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Error opening file";
//        return false;
    }

    //Start reading from file
    double numberElectrodes;
    QTextStream in(&file);
    int i=0;

    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(QRegExp("\\s+"));

        //Delete last element if it is a blank character
        if(fields.at(fields.size()-1) == "")
            fields.removeLast();

        //Read number of electrodes
        if(i == 0){
            numberElectrodes = fields.at(fields.size()-1).toDouble();
            electrodes = MatrixXd::Zero(numberElectrodes, 3);
        }
        //Read actual electrode positions
        else{
            Vector3d x;
            x << fields.at(fields.size()-3).toDouble(),fields.at(fields.size()-2).toDouble(),fields.at(fields.size()-1).toDouble();
            electrodes.row(i-1)=x.transpose();
        }
        i++;
    }
    return electrodes;
}