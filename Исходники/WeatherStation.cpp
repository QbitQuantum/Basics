bool weatherStation::update()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkRequest netRequest(*apiLink);
    QNetworkReply *netReply;

    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;

    netReply = manager->get(netRequest);
    connect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

    timer.start(10000);

    loop.exec();

    QString data;
    QFile weatherTempData("weatherTempData.txt");

    weatherTempData.open(QFile::ReadWrite);

    if(timer.isActive()) {
        timer.stop();
        if(netReply->error() > 0) {
          qDebug() << "network error";
          data = weatherTempData.readAll();
          qDebug() << "read from file";
        }
        else {
          int v = netReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

          if (v >= 200 && v < 300) {  // Success
              data = netReply->readAll();
              weatherTempData.seek(0);
              QTextStream out(&weatherTempData);
              out << data;
              weatherTempData.seek(0);
              //qDebug() << weatherTempData.readAll();
          }
        }
    } else {
       // timeout
       disconnect(netReply, SIGNAL(finished()), &loop, SLOT(quit()));

       netReply->abort();
       data = weatherTempData.readAll();
       qDebug() << "read from file";
    }
    weatherTempData.close();
    QXmlStreamReader *xmlReader = new QXmlStreamReader(data);
    int weatherRecordCounter = 0;
    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
            // Read next element
            QXmlStreamReader::TokenType token = xmlReader->readNext();
            //If token is just StartDocument - go to next
            if(token == QXmlStreamReader::StartDocument) {
                    continue;
            }
            //qDebug() << xmlReader->name();


            if(token == QXmlStreamReader::EndElement)
                   if(xmlReader->name() == "time")
                   {
                        weatherRecordCounter++;
                        //qDebug() << "is end element";
                        continue;
                   }

            //
            //If token is StartElement - read it
            if(token == QXmlStreamReader::StartElement) {

                    if(xmlReader->name() == "sun") {
                        QXmlStreamAttributes att = xmlReader->attributes();
                        sunrise = sunrise.fromString(att.value("rise").toString(),"yyyy-MM-ddTHH:mm:ss");
                        sunrise.setTimeSpec(Qt::UTC);
                        sunrise = sunrise.toLocalTime();
                        sunset = sunset.fromString(att.value("set").toString(),"yyyy-MM-ddTHH:mm:ss");
                        sunset.setTimeSpec(Qt::UTC);
                        sunset = sunset.toLocalTime();
                        //qDebug() << sunrise.toString("yyyy-MM-ddTHH:mm:ss");
                        //qDebug() << sunset.toString("yyyy-MM-ddTHH:mm:ss");
                            continue;
                    }

                    if(xmlReader->name() == "time") {


                            QXmlStreamAttributes att = xmlReader->attributes();
                            weatherRecord *record = new weatherRecord();
                            record->day = record->day.fromString(att.value("day").toString(),"yyyy-MM-dd");
                            /*record->from = record->from.fromString(att.value("from").toString(),"yyyy-MM-ddTHH:mm:ss");
                            record->to = record->to.fromString(att.value("to").toString(),"yyyy-MM-ddTHH:mm:ss");
                            qDebug() << record->from.toString("yyyy-MM-ddTHH:mm:ss");
                            qDebug() << record->to.toString("yyyy-MM-ddTHH:mm:ss");*/
                            weatherRecords.append(record);
                            continue;

                    }

                    if(xmlReader->name() == "precipitation")
                    {
                        if(xmlReader->isEndElement())
                        {
                            weatherRecords.at(weatherRecordCounter)->precipitationType = "no";
                            continue;
                        }
                        else
                        {
                            QXmlStreamAttributes att = xmlReader->attributes();
                            weatherRecords.at(weatherRecordCounter)->precipitationType=att.value("type").toString();
                            weatherRecords.at(weatherRecordCounter)->precipitationValue=att.value("value").toFloat();
                            weatherRecords.at(weatherRecordCounter)->precipitationUnit=att.value("unit").toString();
                            continue;
                        }
                    }

                    if(xmlReader->name() == "windDirection")
                    {
                            QXmlStreamAttributes att = xmlReader->attributes();
                            weatherRecords.at(weatherRecordCounter)->windDirection=att.value("deg").toFloat();
                            continue;
                    }
                    if(xmlReader->name() == "windSpeed")
                    {
                            QXmlStreamAttributes att = xmlReader->attributes();
                            weatherRecords.at(weatherRecordCounter)->windSpeed=att.value("mps").toFloat();
                            weatherRecords.at(weatherRecordCounter)->windType=att.value("name").toString();
                            continue;
                    }
                    if(xmlReader->name() == "temperature")
                    {
                            QXmlStreamAttributes att = xmlReader->attributes();
                            weatherRecords.at(weatherRecordCounter)->currentTemp=att.value("day").toFloat();
                            weatherRecords.at(weatherRecordCounter)->minTemp=att.value("min").toFloat();
                            weatherRecords.at(weatherRecordCounter)->maxTemp=att.value("max").toFloat();
                            continue;
                    }
                    if(xmlReader->name() == "pressure")
                    {
                            QXmlStreamAttributes att = xmlReader->attributes();
                            weatherRecords.at(weatherRecordCounter)->pressure=att.value("value").toFloat();
                            continue;
                    }
                    if(xmlReader->name() == "humidity")
                    {
                            QXmlStreamAttributes att = xmlReader->attributes();
                            weatherRecords.at(weatherRecordCounter)->humidity=att.value("value").toFloat();
                            continue;
                    }
                    if(xmlReader->name() == "clouds")
                    {
                            QXmlStreamAttributes att = xmlReader->attributes();
                            weatherRecords.at(weatherRecordCounter)->cloudsPercent=att.value("all").toInt();
                            weatherRecords.at(weatherRecordCounter)->cloudsName=att.value("value").toString();
                            continue;
                    }
                    if(xmlReader->name() == "symbol")
                    {
                            QXmlStreamAttributes att = xmlReader->attributes();
                            weatherRecords.at(weatherRecordCounter)->icon=att.value("var").toString();

                            continue;
                    }

            }
    }
    if(xmlReader->hasError()) return false;
    return true;
}