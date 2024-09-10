void activity_handlers::butcher_finish( player_activity *act, player *p )
{
    // Corpses can disappear (rezzing!), so check for that
    auto items_here = g->m.i_at( p->pos() );
    if( static_cast<int>( items_here.size() ) <= act->index ||
        !( items_here[act->index].is_corpse() ) ) {
        add_msg(m_info, _("There's no corpse to butcher!"));
        return;
    }

    item &corpse_item = items_here[act->index];
    const mtype *corpse = corpse_item.get_mtype();
    std::vector<item> contents = corpse_item.contents;
    const int age = corpse_item.bday;
    g->m.i_rem( p->pos(), act->index );

    const int factor = p->butcher_factor();
    int pieces = 0;
    int skins = 0;
    int bones = 0;
    int fats = 0;
    int sinews = 0;
    int feathers = 0;
    int wool = 0;
    bool stomach = false;

    switch (corpse->size) {
    case MS_TINY:
        pieces = 1;
        skins = 1;
        bones = 1;
        fats = 1;
        sinews = 1;
        feathers = 2;
        wool = 1;
        break;
    case MS_SMALL:
        pieces = 2;
        skins = 2;
        bones = 4;
        fats = 2;
        sinews = 4;
        feathers = 6;
        wool = 2;
        break;
    case MS_MEDIUM:
        pieces = 4;
        skins = 4;
        bones = 9;
        fats = 4;
        sinews = 9;
        feathers = 11;
        wool = 4;
        break;
    case MS_LARGE:
        pieces = 8;
        skins = 8;
        bones = 14;
        fats = 8;
        sinews = 14;
        feathers = 17;
        wool = 8;
        break;
    case MS_HUGE:
        pieces = 16;
        skins = 16;
        bones = 21;
        fats = 16;
        sinews = 21;
        feathers = 24;
        wool = 16;
        break;
    }

    const int skill_level = p->skillLevel( skill_survival );

    auto roll_butchery = [&] () {
        double skill_shift = 0.0;
        ///\xrefitem Skill_Effects_Survival "" "" Survival above 3 randomly increases Butcher rolls, below 3 decreases
        skill_shift += rng_float( 0, skill_level - 3 );
        ///\xrefitem Stat_Effects_Dexterity "" "" Dexterity above 8 randomly increases Butcher rolls, slightly, below 8 decreases
        skill_shift += rng_float( 0, p->dex_cur - 8 ) / 4.0;
        ///\xrefitem Stat_Effects_Strength "" "" Strength below 4 randomly decreases Butcher rolls, slightly
        if( p->str_cur < 4 ) {
            skill_shift -= rng_float( 0, 5 * ( 4 - p->str_cur ) ) / 4.0;
        }

        if( factor < 0 ) {
            skill_shift -= rng_float( 0, -factor / 5.0 );
        }

        return static_cast<int>( round( skill_shift ) );
    };

    int practice = std::max( 0, 4 + pieces + roll_butchery());

    p->practice( skill_survival, practice );

    // Lose some meat, skins, etc if the rolls are low
    pieces +=   std::min( 0, roll_butchery() );
    skins +=    std::min( 0, roll_butchery() - 4 );
    bones +=    std::min( 0, roll_butchery() - 2 );
    fats +=     std::min( 0, roll_butchery() - 4 );
    sinews +=   std::min( 0, roll_butchery() - 8 );
    feathers += std::min( 0, roll_butchery() - 1 );
    wool +=     std::min( 0, roll_butchery() );
    stomach = roll_butchery() >= 0;

    if( bones > 0 ) {
        if( corpse->has_material("veggy") ) {
            g->m.spawn_item(p->pos(), "plant_sac", bones, 0, age);
            add_msg(m_good, _("You harvest some fluid bladders!"));
        } else if( corpse->has_flag(MF_BONES) && corpse->has_flag(MF_POISON) ) {
            g->m.spawn_item(p->pos(), "bone_tainted", bones / 2, 0, age);
            add_msg(m_good, _("You harvest some salvageable bones!"));
        } else if( corpse->has_flag(MF_BONES) && corpse->has_flag(MF_HUMAN) ) {
            g->m.spawn_item(p->pos(), "bone_human", bones, 0, age);
            add_msg(m_good, _("You harvest some salvageable bones!"));
        } else if( corpse->has_flag(MF_BONES) ) {
            g->m.spawn_item(p->pos(), "bone", bones, 0, age);
            add_msg(m_good, _("You harvest some usable bones!"));
        }
    }

    if( sinews > 0 ) {
        if( corpse->has_flag(MF_BONES) && !corpse->has_flag(MF_POISON) ) {
            g->m.spawn_item(p->pos(), "sinew", sinews, 0, age);
            add_msg(m_good, _("You harvest some usable sinews!"));
        } else if( corpse->has_material("veggy") ) {
            g->m.spawn_item(p->pos(), "plant_fibre", sinews, 0, age);
            add_msg(m_good, _("You harvest some plant fibers!"));
        }
    }

    if( stomach ) {
        const itype_id meat = corpse->get_meat_itype();
        if( meat == "meat" ) {
            if( corpse->size == MS_SMALL || corpse->size == MS_MEDIUM ) {
                g->m.spawn_item(p->pos(), "stomach", 1, 0, age);
                add_msg(m_good, _("You harvest the stomach!"));
            } else if( corpse->size == MS_LARGE || corpse->size == MS_HUGE ) {
                g->m.spawn_item(p->pos(), "stomach_large", 1, 0, age);
                add_msg(m_good, _("You harvest the stomach!"));
            }
        } else if( meat == "human_flesh" ) {
            if( corpse->size == MS_SMALL || corpse->size == MS_MEDIUM ) {
                g->m.spawn_item(p->pos(), "hstomach", 1, 0, age);
                add_msg(m_good, _("You harvest the stomach!"));
            } else if( corpse->size == MS_LARGE || corpse->size == MS_HUGE ) {
                g->m.spawn_item(p->pos(), "hstomach_large", 1, 0, age);
                add_msg(m_good, _("You harvest the stomach!"));
            }
        }
    }

    if( (corpse->has_flag(MF_FUR) || corpse->has_flag(MF_LEATHER) ||
         corpse->has_flag(MF_CHITIN)) && skins > 0 ) {
        add_msg(m_good, _("You manage to skin the %s!"), corpse->nname().c_str());
        int fur = 0;
        int leather = 0;
        int human_leather = 0;
        int chitin = 0;

        while (skins > 0 ) {
            if( corpse->has_flag(MF_CHITIN) ) {
                chitin = rng(0, skins);
                skins -= chitin;
                skins = std::max(skins, 0);
            }
            if( corpse->has_flag(MF_FUR) ) {
                fur = rng(0, skins);
                skins -= fur;
                skins = std::max(skins, 0);
            }
            if( corpse->has_flag(MF_LEATHER) ) {
                if( corpse->has_flag(MF_HUMAN) ) {
                    human_leather = rng(0, skins);
                    skins -= human_leather;
                } else {
                    leather = rng(0, skins);
                    skins -= leather;
                }
                skins = std::max(skins, 0);
            }
        }

        if( chitin > 0 ) {
            g->m.spawn_item(p->pos(), "chitin_piece", chitin, 0, age);
        }
        if( fur > 0 ) {
            g->m.spawn_item(p->pos(), "raw_fur", fur, 0, age);
        }
        if( leather > 0 ) {
            g->m.spawn_item(p->pos(), "raw_leather", leather, 0, age);
        }
        if( human_leather ) {
            g->m.spawn_item(p->pos(), "raw_hleather", leather, 0, age);
        }
    }

    if( feathers > 0 ) {
        if( corpse->has_flag(MF_FEATHER) ) {
            g->m.spawn_item(p->pos(), "feather", feathers, 0, age);
            add_msg(m_good, _("You harvest some feathers!"));
        }
    }

    if( wool > 0 ) {
        if( corpse->has_flag(MF_WOOL) ) {
            g->m.spawn_item(p->pos(), "wool_staple", wool, 0, age);
            add_msg(m_good, _("You harvest some wool staples!"));
        }
    }

    if( fats > 0 ) {
        if( corpse->has_flag(MF_FAT) && corpse->has_flag(MF_POISON) ) {
            g->m.spawn_item(p->pos(), "fat_tainted", fats, 0, age);
            add_msg(m_good, _("You harvest some gooey fat!"));
        } else if( corpse->has_flag(MF_FAT) ) {
            g->m.spawn_item(p->pos(), "fat", fats, 0, age);
            add_msg(m_good, _("You harvest some fat!"));
        }
    }

    //Add a chance of CBM recovery. For shocker and cyborg corpses.
    //As long as the factor is above -4 (the sinew cutoff), you will be able to extract cbms
    if( corpse->has_flag(MF_CBM_CIV) ) {
        butcher_cbm_item( "bio_power_storage", p->pos(), age, roll_butchery() );
        butcher_cbm_group( "bionics_common", p->pos(), age, roll_butchery() );
    }

    // Zombie scientist bionics
    if( corpse->has_flag(MF_CBM_SCI) ) {
        butcher_cbm_item( "bio_power_storage", p->pos(), age, roll_butchery() );
        butcher_cbm_group( "bionics_sci", p->pos(), age, roll_butchery() );
    }

    // Zombie technician bionics
    if( corpse->has_flag(MF_CBM_TECH) ) {
        butcher_cbm_item( "bio_power_storage", p->pos(), age, roll_butchery() );
        butcher_cbm_group( "bionics_tech", p->pos(), age, roll_butchery() );
    }

    // Substation mini-boss bionics
    if( corpse->has_flag(MF_CBM_SUBS) ) {
        butcher_cbm_item( "bio_power_storage", p->pos(), age, roll_butchery() );
        butcher_cbm_group( "bionics_subs", p->pos(), age, roll_butchery() );
        butcher_cbm_group( "bionics_subs", p->pos(), age, roll_butchery() );
    }

    // Payoff for butchering the zombie bio-op
    if( corpse->has_flag(MF_CBM_OP) ) {
        butcher_cbm_item( "bio_power_storage_mkII", p->pos(), age, roll_butchery() );
        butcher_cbm_group( "bionics_op", p->pos(), age, roll_butchery() );
    }

    //Add a chance of CBM power storage recovery.
    if( corpse->has_flag(MF_CBM_POWER) ) {
        butcher_cbm_item( "bio_power_storage", p->pos(), age, roll_butchery() );
    }


    // Recover hidden items
    for( auto &content : contents  ) {
        if( ( roll_butchery() + 10 ) * 5 > rng( 0, 100 ) ) {
            //~ %1$s - item name, %2$s - monster name
            add_msg( m_good, _( "You discover a %1$s in the %2$s!" ), content.tname().c_str(),
                     corpse->nname().c_str() );
            g->m.add_item_or_charges( p->pos(), content );
        } else if( content.is_bionic()  ) {
            g->m.spawn_item(p->pos(), "burnt_out_bionic", 1, 0, age);
        }
    }

    if( pieces <= 0 ) {
        add_msg(m_bad, _("Your clumsy butchering destroys the meat!"));
    } else {
        add_msg(m_good, _("You butcher the corpse."));
        const itype_id meat = corpse->get_meat_itype();
        if( meat == "null" ) {
            return;
        }
        item tmpitem(meat, age);
        tmpitem.set_mtype( corpse );
        while ( pieces > 0 ) {
            pieces--;
            g->m.add_item_or_charges(p->pos(), tmpitem);
        }
    }
}