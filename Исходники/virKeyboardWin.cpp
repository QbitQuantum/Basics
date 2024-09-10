void virKeyboardWin::keyBoardInit()
{
	char* keyb[] ={"`~","1!","2@","3#","4$","5%","6^","7&","8*","9(","0)","-_","=+","delete",
	 "tab" ,"q","w","e","r","t","y","u","i","o","p","[{","]}","\\|",
		"caps lock" ,"a","s","d","f","g","h","j","k","l",";:","'\"", "return" ,
	 "shift" ,"z","x","c","v","b","n","m",",<",".>","/?","shift",
	 "ctrl" , "alt" ,"space", "alt" ,"ctrl" };
	int i,j,temp;
	setRwNum(60);
	comboBoxInit();
	uint16_t w = (getWinWidth()- getWinWidth()/29)/14;
	uint16_t h = getWinHigh()/6;
	uint8_t n ;//中间按键数量
	uint16_t x;//x的位置
	uint16_t wt;
	for(i=0;i<4;i++) //1-3 line
	{
		wt = w ;
		switch(i)
		{
			case 0:{n = 12;temp = 0;}break;
			case 1:{
				wt += w/2;
				n = 12;
			} ;break;
			case 2:{
				wt += w*3/4;
				n = 11;
			}break;
			case 3:{
				wt += w+w/4;
				n = 10;
			}break;
			default:break;
		}	
		getRwList()[temp] = new buttonWin(0,i*h,wt,h,keyb[temp],this,getQueue());
		((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
		((controlWin*)getRwList()[temp])->setBackColor(getBackColor());
		getRwList()[temp]->setWinProc(keyboardProc);
		getRwList()[temp]->registerWin();
		for(j=0;j<n;j++)
		{
			temp ++;
			getRwList()[temp] = new buttonWin(wt,i*h,w,h,keyb[temp],this,getQueue());
			((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
			((controlWin*)getRwList()[temp])->setBackColor(getBackColor());
			getRwList()[temp]->setWinProc(keyboardProc);
			getRwList()[temp]->registerWin();
			wt += w;	
		}
		x = wt;
		temp ++;//每一行最后一个
		wt = w;
		switch(i)
		{
			case 0:{wt += w/2;}break;
			case 1:{wt = w;}break;
			case 2:{wt += w*3/4;}break;
			case 3:{wt += w+w/4;}break;
			default:break;
		}	
		getRwList()[temp] = new buttonWin(x,i*h,wt,h,keyb[temp],this,getQueue());
		((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
		((controlWin*)getRwList()[temp])->setBackColor(getBackColor());
		getRwList()[temp]->setWinProc(keyboardProc);
		getRwList()[temp]->registerWin();
		temp ++;
	}
	//line 4
	x = 2*w;
	for(i=0;i<5;i++)
	{
		if(i==2)
		{
			getRwList()[temp] = new buttonWin(x,4*h,w*5,h,keyb[temp],this,getQueue());
			((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
			((controlWin*)getRwList()[temp]) ->setBackColor(getBackColor());
			getRwList()[temp]->setWinProc(keyboardProc);
			getRwList()[temp]->registerWin();
			x+=w*5;
		}else{
			getRwList()[temp] = new buttonWin(x,4*h,w,h,keyb[temp],this,getQueue());
			((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
			((controlWin*)getRwList()[temp]) ->setBackColor(getBackColor());
			getRwList()[temp]->setWinProc(keyboardProc);
			getRwList()[temp]->registerWin();
			x += w;
		}
		temp++;
	}
	getRwList()[temp] = new buttonWin(0,4*h,2*w,h,"V",this,getQueue());
	((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
	((controlWin*)getRwList()[temp]) ->setBackColor(getBackColor());
	getRwList()[temp]->setWinProc(keyboardProc);
	getRwList()[temp]->registerWin();
	temp++;
	getRwList()[temp] = new buttonWin(x,4*h,3*w+w/2,h,"V",this,getQueue());
	((controlWin*)getRwList()[temp])->setTextColor(getTextColor());
	((controlWin*)getRwList()[temp]) ->setBackColor(getBackColor());
	getRwList()[temp]->setWinProc(keyboardProc);
	getRwList()[temp]->registerWin();
	temp++;
		
}