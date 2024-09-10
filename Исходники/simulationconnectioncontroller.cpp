void SimulationConnectionController::SimulationDataReceived(QByteArray data)
{
    DATA_HEADER_SET header;

    if(data.length()> sizeof(DATA_HEADER_SET))
    {
        memcpy(&header,data.data(),sizeof(DATA_HEADER_SET));
        data.remove(0,sizeof(DATA_HEADER_SET));
        if(header.type == IMAGE_JPEG)
        {
            if(data.length() >= header.length)
            {
                _simulationViewImageRAW = data;

                QImage img;
                try {
                    img = QImage::fromData(_simulationViewImageRAW,"JPEG");//the second param is format name
                } catch (...) {
                    qDebug() << "SimulationDataReceived -> ImageFailed.";
                }
                emit imageReceived(img);
            }
        }
        else if(header.type == SIMULATION_OUTPUT)
        {
            emit dataReceived(data);
        }
    }
}