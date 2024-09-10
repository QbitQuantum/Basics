MissionWidget::MissionWidget(QWidget *parent, QString mName, JoystickWidget *joystick,  Ui::NautilusCommander *gui, SendAction *sa) :
    QWidget(parent)
{
     this->missionName=mName;
     this->ui=gui;

     m_sSettingsFile = QString("%1/%2/settings.ini").arg(createPath("Missions")).arg(missionName);
     loadSettings();

     //Create Mission Folder.
     QString missionFolder=QString("%1/%2").arg(createPath("Missions")).arg(missionName);
     if(!QDir(missionFolder).exists()){
         QDir().mkdir(missionFolder);
     }

    lblLightsOff=ui->label_switchOff;
    lblLightsOn=ui->label_switchOn;
    lblLightsOn->setVisible(false);
    islightsOn=false;

    righLeft=-1;
    upDown=-1;

    statusVideoOff=ui->statusVideoOff;
    statusVideoOff->setVisible(true);
    isRecording=false;

    lblScreenShot=ui->label_toastSS;
    lblScreenShot->setVisible(false);


    missionNameLabel=ui->lblMissionName;
    missionNameLabel->setText(missionName);

    batteryROVPB=ui->progressBattRov;
    panCamera=ui->panCamera;
    tiltCamera=ui->tiltCamera;

    statusErrorBox=ui->statusErrorBox;
    statusErrorBox->setVisible(false);
    lblError=ui->lblError;


    sendAction=sa;
    connect(this->sendAction,SIGNAL(offline()),this,SLOT(robotDisconnected()));
    status=checkStatus();

    if(status!=-1)
    sendAction->sendComando(START_ROBOT);  //ReEnable the robot


    /********************************  Joystick *****************************************************/
    this->joystick=joystick;
    connect(joystick,SIGNAL(updateStatus(bool)),this,SLOT(updateControlStatus(bool)));
    connect(this->joystick,SIGNAL(joystickAxisEvent(QString,int)),this,SLOT(axisEvent(QString,int)));
    connect(this->joystick,SIGNAL(joystickButtonEvent(QString, QGameControllerButtonEvent*)),this,SLOT(buttonEvent(QString,QGameControllerButtonEvent*)));

    rtsp=new openRTSP(0,missionName,numVideos);
    connect(this,SIGNAL(saveVideo()),rtsp,SLOT(saveVideo()));


    dataThread=new DataThread(ui->progressBattControl, ui->progressBattRov,ui->labelDepthValue);
    dataThread->start();



    mplayer=ui->mplayerWG;    
    //connect(mplayer,SIGNAL(stateChanged(int)),this,SLOT(updatePlayerStatus(int)));
    mplayer->start();    
    mplayer->load("rtsp://*****:*****@10.5.5.110:554");
    mplayer->setVisible(true);


    isCameraOnline=true;

    speedDial=ui->dial;
    speedDial->setNotchesVisible(false);

    speeds[0][0]=3;speeds[0][1]=10;speeds[0][2]=14;speeds[0][3]=20;//speeds[0][4]=13;//speeds[0][5]=15;speeds[0][6]=18;speeds[0][7]=22;
    speeds[1][0]=1580;speeds[1][1]=1610;speeds[1][2]=1640;speeds[1][3]=1670;//speeds[1][4]=1670;
    speeds[2][0]=1420;speeds[2][1]=1390;speeds[2][2]=1360;speeds[2][3]=1330;//speeds[2][4]=1330; y = 3000-x
    dialIndex=0;
    lastCommand="";
    speedDial->setValue(speeds[0][0]);

}