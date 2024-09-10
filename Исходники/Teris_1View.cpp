void CTeris_1View::OnNewgame() 
{
	// TODO: Add your command handler code here
	killTimer();

	
	GetDocument()->tick=0;
	this->readRecord();

    switch(GetDocument()->mode){
		
	case NORMAL:
		this->StartNormal();
		break;
	case GK:
		this->StartGk();
		break;
	case QPZ:
		this->StartQPZ();
		
		break;
	case CXY:
		//
		//GetDocument()->Num=2;
		this->StartCXY();
		break;
	case REVERSE:
		this->StartReverse();
		break;
	case LIFE:
		this->StartLife();
		break;
	case XMXX:
		this->StartXmxx();
		break;
		
		
		
		
	}
	
	
}