    void UIGameOptions::setEvent()
    {
        IButton* pButton = getLayout()->getButton("button_exit");
        pButton->getWidget()->setMouseButtonClickEvent(onClickExit);
        getLayout()->getButton("button_rlogin")->getWidget()->setMouseButtonClickEvent(onClickRlogin);
		getLayout()->getButton("button_return")->getWidget()->setMouseButtonClickEvent(onClickReturn);
		
		getLayout()->getButton("button_func")->getWidget()->setMouseButtonClickEvent(onClickFuncSet);
		getLayout()->getButton("button_video")->getWidget()->setMouseButtonClickEvent(onClickVideoSet);
		getLayout()->getButton("button_audio")->getWidget()->setMouseButtonClickEvent(onClickAudioSet);
		getLayout()->getButton("button_network")->getWidget()->setMouseButtonClickEvent(onClickNetworkSet);
    }