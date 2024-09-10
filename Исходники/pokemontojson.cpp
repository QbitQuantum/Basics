BattleChoice fromJson<BattleChoice>(const QVariantMap &v){
    static QStringList bchoices =  QStringList() << "cancel" << "attack" << "switch" << "rearrange" << "shiftcenter" << "tie" << "item";

    BattleChoice info;

    info.type = std::max(bchoices.indexOf(v.value("type").toString()), 0);
    info.playerSlot = v.value("slot").toInt();

    if (info.type == AttackType) {
        info.choice.attack.attackSlot = v.value("attackSlot").toInt();
        info.choice.attack.mega = v.value("mega").toBool();
        if (v.value("target").isValid()) {
            info.choice.attack.attackTarget = v.value("target").toInt();
        } else {
            info.choice.attack.attackTarget = !info.playerSlot;
        }
    } else if (info.type == SwitchType) {
        info.choice.switching.pokeSlot = v.value("pokeSlot").toInt();
    } else if (info.type == RearrangeType) {
        if (v.value("neworder").canConvert<QVariantList>()) {
            QVariantList list = v.value("neworder").toList();
            for (int i = 0; i < list.length() && i < 6; i++) {
                info.choice.rearrange.pokeIndexes[i] = list.value(i).toInt();
            }
        }
    } else if (info.type == ItemType) {
        info.choice.item.item = v.value("item").toInt();
        info.choice.item.target = v.value("target").toInt();
        info.choice.item.attack = v.value("attack").toInt();
    }

    return info;
}