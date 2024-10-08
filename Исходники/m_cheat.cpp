void cht_DoCheat (player_t *player, int cheat)
{
    static const char * const BeholdPowers[9] =
    {
        "PowerInvulnerable",
        "PowerStrength",
        "PowerInvisibility",
        "PowerIronFeet",
        "MapRevealer",
        "PowerLightAmp",
        "PowerShadow",
        "PowerMask",
        "PowerTargeter",
    };
    PClassActor *type;
    AInventory *item;
    const char *msg = "";
    char msgbuild[32];
    int i;

    switch (cheat)
    {
    case CHT_IDDQD:
        if (!(player->cheats & CF_GODMODE) && player->playerstate == PST_LIVE)
        {
            if (player->mo)
                player->mo->health = deh.GodHealth;

            player->health = deh.GodHealth;
        }
    // fall through to CHT_GOD
    case CHT_GOD:
        player->cheats ^= CF_GODMODE;
        if (player->cheats & CF_GODMODE)
            msg = GStrings("STSTR_DQDON");
        else
            msg = GStrings("STSTR_DQDOFF");
        ST_SetNeedRefresh();
        break;

    case CHT_BUDDHA:
        player->cheats ^= CF_BUDDHA;
        if (player->cheats & CF_BUDDHA)
            msg = GStrings("TXT_BUDDHAON");
        else
            msg = GStrings("TXT_BUDDHAOFF");
        break;

    case CHT_GOD2:
        player->cheats ^= CF_GODMODE2;
        if (player->cheats & CF_GODMODE2)
            msg = GStrings("STSTR_DQD2ON");
        else
            msg = GStrings("STSTR_DQD2OFF");
        ST_SetNeedRefresh();
        break;

    case CHT_BUDDHA2:
        player->cheats ^= CF_BUDDHA2;
        if (player->cheats & CF_BUDDHA2)
            msg = GStrings("TXT_BUDDHA2ON");
        else
            msg = GStrings("TXT_BUDDHA2OFF");
        break;

    case CHT_NOCLIP:
        player->cheats ^= CF_NOCLIP;
        if (player->cheats & CF_NOCLIP)
            msg = GStrings("STSTR_NCON");
        else
            msg = GStrings("STSTR_NCOFF");
        break;

    case CHT_NOCLIP2:
        player->cheats ^= CF_NOCLIP2;
        if (player->cheats & CF_NOCLIP2)
        {
            player->cheats |= CF_NOCLIP;
            msg = GStrings("STSTR_NC2ON");
        }
        else
        {
            player->cheats &= ~CF_NOCLIP;
            msg = GStrings("STSTR_NCOFF");
        }
        if (player->mo->Vel.X == 0) player->mo->Vel.X = MinVel;	// force some lateral movement so that internal variables are up to date
        break;

    case CHT_NOVELOCITY:
        player->cheats ^= CF_NOVELOCITY;
        if (player->cheats & CF_NOVELOCITY)
            msg = GStrings("TXT_LEADBOOTSON");
        else
            msg = GStrings("TXT_LEADBOOTSOFF");
        break;

    case CHT_FLY:
        if (player->mo != NULL)
        {
            player->mo->flags7 ^= MF7_FLYCHEAT;
            if (player->mo->flags7 & MF7_FLYCHEAT)
            {
                player->mo->flags |= MF_NOGRAVITY;
                player->mo->flags2 |= MF2_FLY;
                msg = GStrings("TXT_LIGHTER");
            }
            else
            {
                player->mo->flags &= ~MF_NOGRAVITY;
                player->mo->flags2 &= ~MF2_FLY;
                msg = GStrings("TXT_GRAVITY");
            }
        }
        break;

    case CHT_MORPH:
        msg = cht_Morph (player, static_cast<PClassPlayerPawn *>(PClass::FindClass (gameinfo.gametype == GAME_Heretic ? NAME_ChickenPlayer : NAME_PigPlayer)), true);
        break;

    case CHT_NOTARGET:
        player->cheats ^= CF_NOTARGET;
        if (player->cheats & CF_NOTARGET)
            msg = "notarget ON";
        else
            msg = "notarget OFF";
        break;

    case CHT_ANUBIS:
        player->cheats ^= CF_FRIGHTENING;
        if (player->cheats & CF_FRIGHTENING)
            msg = "\"Quake with fear!\"";
        else
            msg = "No more ogre armor";
        break;

    case CHT_CHASECAM:
        player->cheats ^= CF_CHASECAM;
        if (player->cheats & CF_CHASECAM)
            msg = "chasecam ON";
        else
            msg = "chasecam OFF";
        R_ResetViewInterpolation ();
        break;

    case CHT_CHAINSAW:
        if (player->mo != NULL && player->health >= 0)
        {
            type = PClass::FindActor("Chainsaw");
            if (player->mo->FindInventory (type) == NULL)
            {
                player->mo->GiveInventoryType (type);
            }
            msg = GStrings("STSTR_CHOPPERS");
        }
        // [RH] The original cheat also set powers[pw_invulnerability] to true.
        // Since this is a timer and not a boolean, it effectively turned off
        // the invulnerability powerup, although it looks like it was meant to
        // turn it on.
        break;

    case CHT_POWER:
        if (player->mo != NULL && player->health >= 0)
        {
            item = player->mo->FindInventory (RUNTIME_CLASS(APowerWeaponLevel2), true);
            if (item != NULL)
            {
                item->Destroy ();
                msg = GStrings("TXT_CHEATPOWEROFF");
            }
            else
            {
                player->mo->GiveInventoryType (RUNTIME_CLASS(APowerWeaponLevel2));
                msg = GStrings("TXT_CHEATPOWERON");
            }
        }
        break;

    case CHT_IDKFA:
        cht_Give (player, "backpack");
        cht_Give (player, "weapons");
        cht_Give (player, "ammo");
        cht_Give (player, "keys");
        cht_Give (player, "armor");
        msg = GStrings("STSTR_KFAADDED");
        break;

    case CHT_IDFA:
        cht_Give (player, "backpack");
        cht_Give (player, "weapons");
        cht_Give (player, "ammo");
        cht_Give (player, "armor");
        msg = GStrings("STSTR_FAADDED");
        break;

    case CHT_BEHOLDV:
    case CHT_BEHOLDS:
    case CHT_BEHOLDI:
    case CHT_BEHOLDR:
    case CHT_BEHOLDA:
    case CHT_BEHOLDL:
    case CHT_PUMPUPI:
    case CHT_PUMPUPM:
    case CHT_PUMPUPT:
        i = cheat - CHT_BEHOLDV;

        if (i == 4)
        {
            level.flags2 ^= LEVEL2_ALLMAP;
        }
        else if (player->mo != NULL && player->health >= 0)
        {
            item = player->mo->FindInventory(PClass::FindActor(BeholdPowers[i]));
            if (item == NULL)
            {
                if (i != 0)
                {
                    cht_Give(player, BeholdPowers[i]);
                    if (cheat == CHT_BEHOLDS)
                    {
                        P_GiveBody (player->mo, -100);
                    }
                }
                else
                {
                    // Let's give the item here so that the power doesn't need colormap information.
                    cht_Give(player, "InvulnerabilitySphere");
                }
            }
            else
            {
                item->Destroy ();
            }
        }
        msg = GStrings("STSTR_BEHOLDX");
        break;

    case CHT_MASSACRE:
    {
        int killcount = P_Massacre ();
        // killough 3/22/98: make more intelligent about plural
        // Ty 03/27/98 - string(s) *not* externalized
        mysnprintf (msgbuild, countof(msgbuild), "%d Monster%s Killed", killcount, killcount==1 ? "" : "s");
        msg = msgbuild;
    }
    break;

    case CHT_HEALTH:
        if (player->mo != NULL && player->playerstate == PST_LIVE)
        {
            player->health = player->mo->health = player->mo->GetDefault()->health;
            msg = GStrings("TXT_CHEATHEALTH");
        }
        break;

    case CHT_KEYS:
        cht_Give (player, "keys");
        msg = GStrings("TXT_CHEATKEYS");
        break;

    // [GRB]
    case CHT_RESSURECT:
        if (player->playerstate != PST_LIVE && player->mo != nullptr)
        {
            if (player->mo->IsKindOf(RUNTIME_CLASS(APlayerChunk)))
            {
                Printf("Unable to resurrect. Player is no longer connected to its body.\n");
            }
            else
            {
                player->playerstate = PST_LIVE;
                player->health = player->mo->health = player->mo->GetDefault()->health;
                player->viewheight = ((APlayerPawn *)player->mo->GetDefault())->ViewHeight;
                player->mo->flags = player->mo->GetDefault()->flags;
                player->mo->flags2 = player->mo->GetDefault()->flags2;
                player->mo->flags3 = player->mo->GetDefault()->flags3;
                player->mo->flags4 = player->mo->GetDefault()->flags4;
                player->mo->flags5 = player->mo->GetDefault()->flags5;
                player->mo->flags6 = player->mo->GetDefault()->flags6;
                player->mo->flags7 = player->mo->GetDefault()->flags7;
                player->mo->renderflags &= ~RF_INVISIBLE;
                player->mo->Height = player->mo->GetDefault()->Height;
                player->mo->radius = player->mo->GetDefault()->radius;
                player->mo->special1 = 0;	// required for the Hexen fighter's fist attack.
                // This gets set by AActor::Die as flag for the wimpy death and must be reset here.
                player->mo->SetState (player->mo->SpawnState);
                if (!(player->mo->flags2 & MF2_DONTTRANSLATE))
                {
                    player->mo->Translation = TRANSLATION(TRANSLATION_Players, BYTE(player-players));
                }
                player->mo->DamageType = NAME_None;
                if (player->ReadyWeapon != nullptr)
                {
                    P_SetPsprite(player, PSP_WEAPON, player->ReadyWeapon->GetUpState());
                }

                if (player->morphTics > 0)
                {
                    P_UndoPlayerMorph(player, player);
                }

            }
        }
        break;

    case CHT_GIMMIEA:
        cht_Give (player, "ArtiInvulnerability");
        msg = "Valador's Ring of Invunerability";
        break;

    case CHT_GIMMIEB:
        cht_Give (player, "ArtiInvisibility");
        msg = "Shadowsphere";
        break;

    case CHT_GIMMIEC:
        cht_Give (player, "ArtiHealth");
        msg = "Quartz Flask";
        break;

    case CHT_GIMMIED:
        cht_Give (player, "ArtiSuperHealth");
        msg = "Mystic Urn";
        break;

    case CHT_GIMMIEE:
        cht_Give (player, "ArtiTomeOfPower");
        msg = "Tyketto's Tome of Power";
        break;

    case CHT_GIMMIEF:
        cht_Give (player, "ArtiTorch");
        msg = "Torch";
        break;

    case CHT_GIMMIEG:
        cht_Give (player, "ArtiTimeBomb");
        msg = "Delmintalintar's Time Bomb of the Ancients";
        break;

    case CHT_GIMMIEH:
        cht_Give (player, "ArtiEgg");
        msg = "Torpol's Morph Ovum";
        break;

    case CHT_GIMMIEI:
        cht_Give (player, "ArtiFly");
        msg = "Inhilicon's Wings of Wrath";
        break;

    case CHT_GIMMIEJ:
        cht_Give (player, "ArtiTeleport");
        msg = "Darchala's Chaos Device";
        break;

    case CHT_GIMMIEZ:
        for (int i=0; i<16; i++)
        {
            cht_Give (player, "artifacts");
        }
        msg = "All artifacts!";
        break;

    case CHT_TAKEWEAPS:
        if (player->morphTics || player->mo == NULL || player->mo->health <= 0)
        {
            return;
        }
        {
            // Take away all weapons that are either non-wimpy or use ammo.
            AInventory **invp = &player->mo->Inventory, **lastinvp;
            for (item = *invp; item != NULL; item = *invp)
            {
                lastinvp = invp;
                invp = &(*invp)->Inventory;
                if (item->IsKindOf (RUNTIME_CLASS(AWeapon)))
                {
                    AWeapon *weap = static_cast<AWeapon *> (item);
                    if (!(weap->WeaponFlags & WIF_WIMPY_WEAPON) ||
                            weap->AmmoType1 != NULL)
                    {
                        item->Destroy ();
                        invp = lastinvp;
                    }
                }
            }
        }
        msg = GStrings("TXT_CHEATIDKFA");
        break;

    case CHT_NOWUDIE:
        cht_Suicide (player);
        msg = GStrings("TXT_CHEATIDDQD");
        break;

    case CHT_ALLARTI:
        for (int i=0; i<25; i++)
        {
            cht_Give (player, "artifacts");
        }
        msg = GStrings("TXT_CHEATARTIFACTS3");
        break;

    case CHT_PUZZLE:
        cht_Give (player, "puzzlepieces");
        msg = GStrings("TXT_CHEATARTIFACTS3");
        break;

    case CHT_MDK:
        if (player->mo == NULL)
        {
            Printf ("What do you want to kill outside of a game?\n");
        }
        else if (!deathmatch)
        {
            // Don't allow this in deathmatch even with cheats enabled, because it's
            // a very very cheap kill.
            P_LineAttack (player->mo, player->mo->Angles.Yaw, PLAYERMISSILERANGE,
                          P_AimLineAttack (player->mo, player->mo->Angles.Yaw, PLAYERMISSILERANGE), TELEFRAG_DAMAGE,
                          NAME_MDK, NAME_BulletPuff);
        }
        break;

    case CHT_DONNYTRUMP:
        cht_Give (player, "HealthTraining");
        msg = GStrings("TXT_MIDASTOUCH");
        break;

    case CHT_LEGO:
        if (player->mo != NULL && player->health >= 0)
        {
            int oldpieces = ASigil::GiveSigilPiece (player->mo);
            item = player->mo->FindInventory (RUNTIME_CLASS(ASigil));

            if (item != NULL)
            {
                if (oldpieces == 5)
                {
                    item->Destroy ();
                }
                else
                {
                    player->PendingWeapon = static_cast<AWeapon *> (item);
                }
            }
        }
        break;

    case CHT_PUMPUPH:
        cht_Give (player, "MedPatch");
        cht_Give (player, "MedicalKit");
        cht_Give (player, "SurgeryKit");
        msg = GStrings("TXT_GOTSTUFF");
        break;

    case CHT_PUMPUPP:
        cht_Give (player, "AmmoSatchel");
        msg = GStrings("TXT_GOTSTUFF");
        break;

    case CHT_PUMPUPS:
        cht_Give (player, "UpgradeStamina", 10);
        cht_Give (player, "UpgradeAccuracy");
        msg = GStrings("TXT_GOTSTUFF");
        break;

    case CHT_CLEARFROZENPROPS:
        player->cheats &= ~(CF_FROZEN|CF_TOTALLYFROZEN);
        msg = "Frozen player properties turned off";
        break;

    case CHT_FREEZE:
        bglobal.changefreeze ^= 1;
        if (bglobal.freeze ^ bglobal.changefreeze)
        {
            msg = GStrings("TXT_FREEZEON");
        }
        else
        {
            msg = GStrings("TXT_FREEZEOFF");
        }
        break;
    }

    if (!*msg)              // [SO] Don't print blank lines!
        return;

    if (player == &players[consoleplayer])
        Printf ("%s\n", msg);
    else if (cheat != CHT_CHASECAM)
        Printf ("%s cheats: %s\n", player->userinfo.GetName(), msg);
}