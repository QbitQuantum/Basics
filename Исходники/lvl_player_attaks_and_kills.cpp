void LVL_Player::attack(LVL_Player::AttackDirection _dir)
{
    PGE_RectF attackZone;

    switch(_dir)
    {
        case Attack_Up:
            attackZone.setRect(posCenterX()-5, top()-17, 10, 5);
        break;
        case Attack_Down:
            attackZone.setRect(posCenterX()-5, bottom(), 10, 5);
        break;
        case Attack_Forward:
            if(_direction>=0)
                attackZone.setRect(right(), bottom()-32, 10, 10);
            else
                attackZone.setRect(left()-10, bottom()-32, 10, 10);
        break;
    }


    QVector<PGE_Phys_Object*> bodies;
    LvlSceneP::s->queryItems(attackZone, &bodies);
    int contacts = 0;

    QList<LVL_Block *> target_blocks;
    QList<LVL_Npc*> target_npcs;
    for(PGE_RenderList::iterator it=bodies.begin();it!=bodies.end(); it++ )
    {
        PGE_Phys_Object*visibleBody=*it;
        contacts++;
        if(visibleBody==this) continue;
        if(visibleBody==NULL)
            continue;
        if(!visibleBody->isVisible()) //Don't whip elements from hidden layers!
            continue;
        switch(visibleBody->type)
        {
            case PGE_Phys_Object::LVLBlock:
                target_blocks.push_back(static_cast<LVL_Block*>(visibleBody));
                break;
            case PGE_Phys_Object::LVLNPC:
                target_npcs.push_back(static_cast<LVL_Npc*>(visibleBody));
                break;
            case PGE_Phys_Object::LVLPlayer:
                default:break;
        }
    }

    foreach(LVL_Block *x, target_blocks)
    {
        if(!x) continue;
        if(x->destroyed) continue;
        if(x->sizable && _dir==Attack_Forward)
            continue;
        x->hit();
        if(!x->destroyed)
        {
            LvlSceneP::s->launchStaticEffectC(69, x->posCenterX(), x->posCenterY(), 1, 0, 0, 0, 0);
            PGE_Audio::playSoundByRole(obj_sound_role::WeaponExplosion);
        }
        x->destroyed=true;
    }
    foreach(LVL_Npc *x, target_npcs)
    {
        if(!x) continue;
        if(x->isPaused()) continue; //Don't attack NPC with paused physics!
        if(x->isKilled()) continue;
        if(x->isGenerator) continue;
        x->doHarm(LVL_Npc::DAMAGE_BY_PLAYER_ATTACK);
        LvlSceneP::s->launchStaticEffectC(75, attackZone.center().x(), attackZone.center().y(), 1, 0, 0, 0, 0);
        kill_npc(x, NPC_Kicked);
    }
}