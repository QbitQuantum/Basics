 WorldPackets::Chat::Chat* operator()(LocaleConstant locale) const
 {
     std::string const& text = sCreatureTextMgr->GetLocalizedChatString(_source->GetEntry(), _gender, _textGroup, _textId, locale);
     WorldPackets::Chat::Chat* chat = new WorldPackets::Chat::Chat();
     chat->Initialize(_msgType, Language(_language), _talker, _target, text, 0, "", locale);
     return chat;
 }