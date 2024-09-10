void Slash::use(Room *room, ServerPlayer *source, const QList<ServerPlayer *> &targets) const{
    if(source->getPhase() == Player::Play
            && source->hasUsed("Slash")
            && source->hasWeapon("crossbow"))
        room->setEmotion(source,"weapon/crossbow");
    else if(this->isVirtualCard() && this->skill_name == "spear")
        room->setEmotion(source,"weapon/spear");
    else if(targets.length()>1
            && source->handCards().size() == 0
            && source->hasWeapon("halberd"))
        room->setEmotion(source,"weapon/halberd");
    else if(this->isVirtualCard() && this->skill_name == "fan")
        room->setEmotion(source,"weapon/fan");

    BasicCard::use(room, source, targets);

    if(source->hasFlag("drank")){
        LogMessage log;
        log.type = "#UnsetDrank";
        log.from = source;
        room->sendLog(log);
    }
}