void LLPanelGroup::reposButton(const std::string& name)
{
    LLButton* button = findChild<LLButton>(name);
    if(!button)
        return;
    LLRect btn_rect = button->getRect();
    btn_rect.setLeftTopAndSize( btn_rect.mLeft, btn_rect.getHeight() + 2, btn_rect.getWidth(), btn_rect.getHeight());
    button->setRect(btn_rect);
}