//准备发送的消息包，进行封装操作
QString Gprs::PreSendMessage(QString strSendMsg, QString strPhoneNumber)
{
    	char ctl_Z=0x1A;    
	
    	QString strEncodeMsg="";  
    	QString strSendTemp="";

QString addr="86"+serverNumber+"F";
QString phoneNum="86"+strPhoneNumber+"F";
QString msg="";
QString content="";

//将短信中心号奇数位和偶数位交换
addr=NumberConversion(addr);
qDebug()<<addr;

//将短信息中心号码前面加上字符91，91是国际化的意思
addr="91"+addr;
qDebug()<<addr;

//算出addr长度，结果除2，格式化成2位的16进制字符串
int al=addr.length()/2;
QString addrLength= QString::number(al, 16);
if(al<16){
addrLength="0"+addrLength;
}
qDebug()<<addrLength;
addr=addrLength+addr;

//将手机号码奇数位和偶数位交换。
phoneNum=NumberConversion(phoneNum);
qDebug()<<phoneNum;


//信息内容转字符串转换为Unicode代码
msg=ToUnicode(strSendMsg);
qDebug()<<msg;

//将 msg 长度除2，保留两位16进制数，再加上 msg
int ml=msg.length()/2;
QString msgLength= QString::number(ml, 16);
if(ml<16){
msgLength="0"+msgLength;
}
qDebug()<<msgLength;
msg=msgLength+msg;

//组合
//手机号码前加上字符串 11000D91（1100：固定，0D：手机号码的长度，不算＋号，十六进制表示，91：发送到手机为91，发送到小灵通为81）
phoneNum = "11000D91" + phoneNum;
qDebug()<<phoneNum;

//手机号码后加上 000800 和刚才的短信息内容，000800短信有效期z,再加上ctl_Z；
content = phoneNum + "000800"+msg;
qDebug()<<content;
   
//phone 长度除以2，格式化成2位的十进制数
int length=content.length()/2;
qDebug()<<length;

content =addr+content+ctl_Z;

if ( fd>0 )
    {	
	QString sendata=QString("AT+CMGS=%1").arg(length);     
	sendata+="\r\n";    
	const char *send=sendata.toLatin1().data();    
	int len=strlen(send);    		
	SerialPort::nwrite( fd, send, len);
    }
    return content;
}