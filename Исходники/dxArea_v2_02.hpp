	virtual int draw(Pint _pos,bool _active=true,dxDMode _mode=dxDMode()){
//		if(status<0)return 0;
//		else if(status==0)_mode+=Passive;
		if(!_active)_mode+=Passive;
		dx::drawBox(_pos,_pos+size,Clr,1,_mode+In);
		dx::drawBox(_pos,_pos+size,Clr,0,_mode+Out);
		dx::TmpDrawArea DA(dxDArea(Rint(_pos,_pos+size))&dx::getDrawArea());
//		dxO dxo(_pos,_mode,status>0,this);
		dxO dxo(_pos,_active,_mode,this);
		return drawIn(dxo,pDrawFunc);
	}