// 和甜椒的服务通讯
bool SubmitData::GetDriverInfoFromWeb(GetDriverParam param,DriverInfo &driver)
{
	QMap<QString,QString> sendData = param.toMap();

	CommSendData2Web(sendData,PackageService,GetDriver,true);

	QTextCodec *tc = QTextCodec::codecForName("UTF-8");
	QByteArray ba = http->readAll();
	QString str = tc->toUnicode(ba);

	if (http!=NULL)
		delete http;
	if (loop!=NULL)
		delete loop;
	QDomDocument document; 
	if (!document.setContent(str))
	{
		driver.Clear();
		return false;  
	}  
	QDomElement root = document.documentElement();  

	QString isSuccess=getXmlValue(root,"IsSuccess");
	if (isSuccess=="") 
	{
		driver.Clear();
		qDebug() << "network report infomation error\n\n";
		return false;
	}
	else if (isSuccess.toLower()=="false")
	{
		driver.Clear();
		driver.DriverId = -2;
		qDebug() << "backstage not set driver\n\n";
		return false;
	}
	QString deviceId=getXmlValue(root,"DeviceID");
	driver.DriverId=deviceId.toLongLong();
	driver.Url=getXmlValue(root,"Url");
	driver.MD5=getXmlValue(root,"MD5");
	QString tmpDeviceType=getXmlValue(root,"DeviceType");

	if (tmpDeviceType=="INI")
		driver.DrvierType=1;
	else
		driver.DrvierType=2;

	driver.DriverName=getXmlValue(root,"MachineName");
	driver.StartFile=getXmlValue(root,"StartFile");
	driver.Version=getXmlValue(root,"Version").toInt();
	QString s= getXmlValue(root, "IsDeviceCollect");
	driver.isDeviceCollect= s == "true" ? true : false;
	driver.deviceStatue = getXmlValue(root, "DeviceStatue").toInt();
	QString strType = getXmlValue(root, "DataType");
	bool deviceType = strType == "true" ? true : false;
	if (deviceType) 
	{
		qDebug() << "exact driver recognition\n\n";
	}
	else 
	{
		qDebug() << "general driver recognition\n\n";
	}
	driver.DataType = deviceType;

	return true;
}