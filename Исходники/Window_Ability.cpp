void Window_Ability::onCloseClick(){
    setTocuhEnable(false);
    m_info_bg->runAction(CCFadeOut::create(0.2f));
    m_info_bg->runAction(Sequence::create(CCMoveTo::create(0.2f, Point(-334,-58)),CallFunc::create([&](){closeWindow();}), NULL));
    m_black_block_1->runAction(ScaleTo::create(0.1f, 0.1f, 1.0f));
    m_black_block_2->runAction(ScaleTo::create(0.1f, 0.1f, 1.0f));
}