int doDispelMagic(Creature* player, cmd* cmnd, SpellData* spellData, const char* spell, int numDispel) {
    Creature* target=0;
    int     chance=0;

    if(spellData->how == CastType::CAST &&
        player->getClass() !=  CreatureClass::MAGE &&
        player->getClass() !=  CreatureClass::LICH &&
        player->getClass() !=  CreatureClass::CLERIC &&
        player->getClass() !=  CreatureClass::DRUID &&
        !player->isStaff()
    ) {
        player->print("Only mages, liches, clerics, and druids may cast that spell.\n");
        return(0);
    }

    if(cmnd->num == 2) {
        target = player;
        broadcast(player->getSock(), player->getParent(), "%M casts a %s spell on %sself.", player, spell, player->himHer());


        player->print("You cast a %s spell on yourself.\n", spell);
        player->print("Your spells begin to dissolve away.\n");


        player->doDispelMagic(numDispel);
    } else {
        if(player->noPotion( spellData))
            return(0);

        cmnd->str[2][0] = up(cmnd->str[2][0]);
        target = player->getParent()->findPlayer(player, cmnd, 2);
        if(!target) {
            // dispel-magic on an exit
            cmnd->str[2][0] = low(cmnd->str[2][0]);
            Exit* exit = findExit(player, cmnd, 2);

            if(exit) {
                player->printColor("You cast a %s spell on the %s^x.\n", spell, exit->getCName());
                broadcast(player->getSock(), player->getParent(), "%M casts a %s spell on the %s^x.", player, spell, exit->getCName());

                if(exit->flagIsSet(X_PORTAL))
                    Move::deletePortal(player->getRoomParent(), exit);
                else
                    exit->doDispelMagic(player->getRoomParent());
                return(0);
            }

            player->print("You don't see that player here.\n");
            return(0);
        }

        if(player->isPlayer() && player->getRoomParent()->isPkSafe() && (!player->isCt()) && !target->flagIsSet(P_OUTLAW)) {
            player->print("That spell is not allowed here.\n");
            return(0);
        }

        if(!target->isEffected("petrification")) {
            if(!player->canAttack(target))
                return(0);
        } else {
            player->print("You cast a %s spell on %N.\n%s body returns to flesh.\n",
                spell, target, target->upHisHer());
            if(mrand(1,100) < 50) {

                target->print("%M casts a %s spell on you.\nYour body returns to flesh.\n", player, spell);
                broadcast(player->getSock(), target->getSock(), player->getParent(),
                    "%M casts a %s spell on %N.\n%s body returns to flesh.\n",
                    player, spell, target, target->upHisHer());
                target->removeEffect("petrification");
                return(1);
            } else {
                target->print("%M casts a dispel-magic spell on you.\n", player);
                broadcast(player->getSock(), target->getSock(), player->getParent(), "%M casts a dispel-magic spell on %N.\n",player, target);
                return(0);
            }


        }


        chance = 50 - (10*(bonus((int) player->intelligence.getCur()) -
            bonus((int) target->intelligence.getCur())));

        chance += (spellData->level - target->getLevel())*10;

        chance = MIN(chance, 90);

        if((target->isEffected("resist-magic")) && target->isPlayer())
            chance /=2;




        if( player->isCt() ||
            (mrand(1,100) <= chance && !target->chkSave(SPL, player, 0)))
        {
            player->print("You cast a %s spell on %N.\n", spell, target);

            logCast(player, target, spell);

            broadcast(player->getSock(), target->getSock(), player->getParent(), "%M casts a %s spell on %N.", player, spell, target);
            target->print("%M casts a %s spell on you.\n", player, spell);
            target->print("Your spells begin to dissolve away.\n");


            target->doDispelMagic(numDispel);

            for(Monster* pet : target->pets) {
                if(pet) {
                    if(player->isCt() || !pet->chkSave(SPL, player, 0)) {
                        player->print("Your spell bansished %N's %s!\n", target, pet->getCName());
                        target->print("%M's spell banished your %s!\n%M fades away.\n", player, pet->getCName(), pet);
                        gServer->delActive(pet);
                        pet->die(pet->getMaster());
                    }
                }
            }
        } else {
            player->printColor("^yYour spell fails against %N.\n", target);
            target->print("%M tried to cast a dispel-magic spell on you.\n", player);
            broadcast(player->getSock(), target->getSock(), player->getParent(), "%M tried to cast a dispel-magic spell on %N.", player, target);
            return(0);
        }
    }
    return(1);
}