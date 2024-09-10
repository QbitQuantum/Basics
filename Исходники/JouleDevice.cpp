bool
JouleDevice::download( const QDir &tmpdir,
                         QList<DeviceDownloadFile> &files,
                         QString &err)
{
    if (JOULE_DEBUG) printf("download Joule 1.0, GPS or GPS+");

    if (!dev->open(err)) {
        err = tr("ERROR: open failed: ") + err;
        return false;
    }
    dev->setBaudRate(57600, err);

    JoulePacket versionResponse;
    JoulePacket systemResponse;

    if (!getUnitVersion(versionResponse, err)) {
        return false;
    }

    if (!getSystemInfo(systemResponse, err)) {
        return false;
    }

    bool isJouleGPS = getJouleType(versionResponse) == JOULE_GPS;
    bool isJouleGPSPLUS = getJouleType(versionResponse) == JOULE_GPS_PLUS;

    emit updateStatus(QString(tr("Joule %1 identified")).arg(isJouleGPS?"GPS":(isJouleGPSPLUS?"GPS+":"1.0")));

    bool isJouleGPS_GPSPLUS = isJouleGPS || isJouleGPSPLUS;

    QList<DeviceStoredRideItem> trainings;
    if (!getDownloadableRides(trainings, isJouleGPS_GPSPLUS, err))
        return false;

    for (int i=0; i<trainings.count(); i++) {
        emit updateProgress(QString(tr("Read detail for activity %1/%2")).arg(i+1).arg(trainings.count()));
        JoulePacket request(READ_RIDE_DETAIL);
        int id1 = (trainings.at(i).id>255?trainings.at(i).id-255:trainings.at(i).id);
        int id2 = (trainings.at(i).id>255?trainings.at(i).id%255:0);
        request.addToPayload((char)id1);
        request.addToPayload((char)id2);
        request.addToPayload((uint16_t)0xFFFF); // Total Ride#
        request.addToPayload((uint16_t)0x0000); // Start Page#

        if (!request.write(dev, err))
            return false;

        if(m_Cancelled)
        {
            err = tr("download cancelled");
            return false;
        }

        JoulePacket response = JoulePacket(PAGE_RIDE_DETAIL);
        if (response.read(dev, err)) {

            if (response.payload.size() < 4096)
            {
                err = tr("no data");
                return false;
            }

            int page = qByteArray2Int(response.payload.left(2));
            int data_version = qByteArray2Int(response.payload.mid(2,1));
            int firmware = qByteArray2Int(response.payload.mid(3,1));

            QString data = QString("%1 %2-%3").arg(page).arg(data_version).arg(firmware);
            qDebug() << data;

            if (page < 65535) {
                // create temporary file
                QString tmpl = tmpdir.absoluteFilePath(".joule.XXXXXX"); // temp file
                QTemporaryFile tmp(tmpl);
                tmp.setAutoRemove(false);

                if (!tmp.open()) {
                    err = tr("Failed to create temporary file ")
                        + tmpl + ": " + tmp.error();
                    return false;
                }

                // timestamp from the first training
                struct tm start;
                start.tm_sec = (isJouleGPS_GPSPLUS ? bcd2Int(response.payload.at(4))   : qByteArray2Int(response.payload.mid(4,1))   );
                start.tm_min = (isJouleGPS_GPSPLUS ? bcd2Int(response.payload.at(5))   : qByteArray2Int(response.payload.mid(5,1))   );
                start.tm_hour = (isJouleGPS_GPSPLUS ? bcd2Int(response.payload.at(6))   : qByteArray2Int(response.payload.mid(6,1))   );
                start.tm_mday = (isJouleGPS_GPSPLUS ? bcd2Int(response.payload.at(7))   : qByteArray2Int(response.payload.mid(7,1))   );
                start.tm_mon = (isJouleGPS_GPSPLUS ? bcd2Int(response.payload.at(8))-1  : qByteArray2Int(response.payload.mid(8,1))-1 );
                start.tm_year = (isJouleGPS_GPSPLUS ? bcd2Int(response.payload.at(9))+100  : qByteArray2Int(response.payload.mid(9,1))+100 );
                start.tm_isdst = -1;

                DeviceDownloadFile file;
                file.extension = "bin2";
                file.name = tmp.fileName();
                file.startTime.setTime_t( mktime( &start ));
                files.append(file);

                QTextStream os(&tmp);
                os << hex;

                qDebug() << tmp.fileName() << "-" << tmpl;
                tmp.write(versionResponse.dataArray());
                tmp.write(systemResponse.dataArray());
                tmp.write(response.dataArray());

                int _try = 1;
                while (page < 65535) {
                    if (JOULE_DEBUG) printf("page %d\n", page);

                    request = JoulePacket(PAGE_RIDE_DETAIL);
                    request.addToPayload(response.payload.left(2).data(),2);

                    if (!request.write(dev, err))
                        return false;

                    response = JoulePacket(PAGE_RIDE_DETAIL);

                    bool success = false;
                    while (!success) {
                        if (response.read(dev, err)) {
                            page = qByteArray2Int(response.payload.left(2));

                            tmp.write(response.dataArray());
                            success = true;
                        } else {
                            if (_try == 3)
                                return false;
                            else {
                                JoulePacket request(READ_RIDE_DETAIL);
                                //request.addToPayload((uint16_t)0x0200); // Ride#
                                request.addToPayload((char)i);
                                request.addToPayload((char)0x00);
                                request.addToPayload((uint16_t)0xFFFF); // Total Ride#
                                request.addToPayload((uint16_t)page); // Start Page#

                                if (!request.write(dev, err)) return false;

                                response = JoulePacket(PAGE_RIDE_DETAIL);
                                _try ++;
                            }
                        }
                    }
                }
                tmp.close();
            }


            if (JOULE_DEBUG) printf("Acknowledge\n");
            request = JoulePacket(PAGE_RIDE_DETAIL);
            request.addToPayload(response.payload.left(2).data(),2);

            if (!request.write(dev, err)) return false;


        } else
            i=99;
    }

    dev->close();

    return true;
}