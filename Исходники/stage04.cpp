void Stage04::StagePass()
{
	this->unschedule(SEL_SCHEDULE(&Stage04::createCarWithTimer));
	bus = Sprite::create("bus.png");
	bus->setPosition(winSize.width + 400, 150);
	this->addChild(bus);
	DelayTime* busdelaytime1 = DelayTime::create(1);
	MoveTo* busmoveto1 = MoveTo::create(3,ccp(winSize.width / 2, 150));
	DelayTime* busdelaytime2 = DelayTime::create(2);
	MoveTo* busmoveto2 = MoveTo::create(3,ccp(-400, 150));
	auto busaction = Sequence::create(busdelaytime1,busmoveto1, busdelaytime2, busmoveto2, NULL);
	bus->runAction(busaction);

	auto s	= getChildByTag(1);
	float o = winSize.width / 2 - s->getPosition().x;
	float a = 100 - s->getPosition().y;
	float at = (float) CC_RADIANS_TO_DEGREES( atanf( o/a) );

	if( a < 0 ) 
	{
		if(  o < 0 )
			at = 180 + fabs(at);
		else
			at = 180 - fabs(at);    
	}
	RotateTo* rotateto =  RotateTo::create(0.5, at);
	DelayTime* herodelaytime = DelayTime::create(4);
	MoveTo* heromoveto = MoveTo::create(1,ccp(winSize.width / 2, 150));
	FadeOut* herofadeout = FadeOut::create(0.5f);
	auto heroaction = Sequence::create(rotateto,herodelaytime, heromoveto, herofadeout, NULL);
	s->runAction(heroaction);

	winboard = Sprite::create("winboard.png");
	winboard->setPosition(winSize.width / 2, winSize.height + 250);
	this->addChild(winboard);
	LabelTTF* playTTF1		=	LabelTTF::create("next stage","ARNPRIOR",32);
	MenuItemLabel* item1		=	MenuItemLabel::create(playTTF1,CC_CALLBACK_1(Stage04::WinBoardNextCallBack,this));
	LabelTTF* playTTF2		=	LabelTTF::create("main menu","ARNPRIOR",32);
	MenuItemLabel* item2		=	MenuItemLabel::create(playTTF2,CC_CALLBACK_1(Stage04::WinBoardMainMenuCallBack,this));
	item1->setPositionY(item1->getPositionY() + 20);
	item2->setPositionY(item2->getPositionY() - 20);
	Menu* playMenu			=	Menu::create(item1, item2, NULL);
	playMenu->setPosition(270,130);
	winboard->addChild(playMenu);
	DelayTime* boarddelaytime = DelayTime::create(7);
	MoveTo* boardmoveto = MoveTo::create(1,ccp(winSize.width / 2, winSize.height / 2));
	auto boardaction = Sequence::create(boarddelaytime, boardmoveto, NULL);
	winboard->runAction(boardaction);
}