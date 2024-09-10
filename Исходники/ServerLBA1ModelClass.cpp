ServerLBA1ModelClass::ServerLBA1ModelClass(entitiesTableStruct* entitiesData, const std::string &bodyPath,
								const std::string &animPath, int entityNum,int bodyNum)
: bodyPtr(NULL), animPtr(NULL), m_currentSpeedX(0), m_currentSpeedY(0), m_currentSpeedZ(0),
	m_animationspeed(1), cumutime(0), rotTablePtr(rotTable)
{

	HQRHandler HQH(Lba1ModelDataPath()+"RESS.HQR");
	unsigned int paletteSize;
	m_paletteRGB = HQH.Load_HQR(0, paletteSize);

	m_animPath = animPath;
	m_softShade = true;
	m_wireFrame = 0;

	m_showSelectedPolygon=false;
	m_showBones=false;
	m_showPoint=false;
	m_showLine=false;
	m_showSphere=false;
	m_showCollisionBox=false;
	m_useAnimSteps=false;

	Points=NULL;
	Elements=NULL;
	entitiesTableEntry* localEntry;

	speed=15;
	angle=0;

	globalAngleX=0;
	globalAngleY=0;
	globalAngleZ=0;

	lightPosition[0]=0;
	lightPosition[1]=40;
	lightPosition[2]=40;

	currentBone=0;

	if(!entitiesData) // no entities data, can't load model...
	{
		LogHandler::getInstance()->LogToFile("No entity data, can not load the model...");
		return;
	}

	localEntry=&(entitiesData->entitiesTable[entityNum]);

	for(int i=0;i<localEntry->numOfBody;i++)
	{
		if(localEntry->bodyList[i].body==bodyNum)
		{
			if(bodyPtr)
				free(bodyPtr);

            filesize = loadResource(bodyPath.c_str(),localEntry->bodyList[i].index,&bodyPtr);

			if(localEntry->bodyList[i].useColBox)
			{
				X1=localEntry->bodyList[i].X1;
				Z1=localEntry->bodyList[i].Z1;
				Y1=localEntry->bodyList[i].Y1;
				X2=localEntry->bodyList[i].X2;
				Z2=localEntry->bodyList[i].Z2;
				Y2=localEntry->bodyList[i].Y2;
			}


            if(*((short int *)bodyPtr) & 0x02)
                useAnim = true;
            else
                useAnim = false;

            LoadModel(bodyPtr);

            currentEntity=entityNum;
			break;
		}
	}

	lastCurrentX =0;
	lastCurrentY =0;
	lastCurrentZ =0;
}