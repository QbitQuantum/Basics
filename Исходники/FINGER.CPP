/*****指纹收集构造函数******/
Finger_Gather::Finger_Gather(QObject *parent) :
    QObject(parent)
{
    globalData = GlobalData::getGlobalData();

   // usbComTool = new UsbComTool;
   // usbComTool->GetUsbCom();

    QVector<QString>::size_type size;
   //const char **temp_finger = usbComTool->GetComNameFromFile(size);
   qDebug()<<"size:"<<size;
    //qDebug()<<"data"<<temp_finger[0];
  // fprintf(stderr,"data0:%s\n",temp_finger[0]);
 //  fprintf(stderr,"data1:%s\n",temp_finger[1]);
 //  fprintf(stderr,"data2:%s\n",temp_finger[2]);

    if ( ( fd = openPort( FINGER_COM,0) ) < 0 )
  // if((fd = usbComTool->dynamicOpenPort(temp_finger ,size-1 , size))<0)
    {      //打开串口,如果打开失败，会返回-1
        qDebug() << "Open Finger Serial port failed";

    }

    if (setComConfig( fd , 57600 , 8 , 'N' , 1 ) < 0 ){//打开端口错误，返回-1
        qDebug() << "Set COM failed";

    }
}