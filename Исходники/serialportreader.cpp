bool SerialPortReader::checkSerialPortAvailable(){
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();

    for(int i = 0;i<list.length();i++){

       if(list.at(i).portName().contains("usbmodem")){

           if(list.at(i).isBusy()){
               emit status(Status::usb_busy);
               return false;
           }

           this->serialPort.setPortName(list.at(i).portName());

           return true;
       }

    }

    emit status(Status::usb_not_found);

    return false;
}