EngineMeter::EngineMeter(QString name, QString title, QMeter::Type type,QWidget *parent)
	: QBaseMeter(name,title,type,parent)
{
	m_runtime = 0;
	
    m_minValue = 0;
    m_maxValue = 40; 
	m_value = m_minValue;
	m_laValue = 25;
	m_haValue = 40;
	m_lwValue = 15;
	m_hwValue = 25;

	m_startAngle =60;
	m_endAngle =60;

	m_scaleMajor = 10;
	m_scaleMiddle = 2;
    m_scaleMinor = 4;

	m_units = QStringLiteral("RPM"); 
	//m_title = QStringLiteral("×ªËÙ±í");
	m_compoment =0x0C0E;
	m_precision = 2;
	QTimer *timer = new QTimer(this);
	//timer->connect(timer,SIGNAL(timeout()),this,SLOT(changeValue()));
	timer->connect(timer,SIGNAL(timeout()),this,SLOT(setRuntime()));
	timer->start(1000);
}