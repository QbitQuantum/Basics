void player::consume_effects( const item &food )
{
    if( !food.is_comestible() ) {
        debugmsg( "called player::consume_effects with non-comestible" );
        return;
    }
    const auto &comest = *food.type->comestible;

    const int capacity = stomach_capacity();
    if( has_trait( trait_id( "THRESH_PLANT" ) ) && food.type->can_use( "PLANTBLECH" ) ) {
        // Just keep nutrition capped, to prevent vomiting
        cap_nutrition_thirst( *this, capacity, true, true );
        return;
    }
    if( ( has_trait( trait_id( "HERBIVORE" ) ) || has_trait( trait_id( "RUMINANT" ) ) ) &&
        food.has_any_flag( herbivore_blacklist ) ) {
        // No good can come of this.
        return;
    }

    // Rotten food causes health loss
    const float relative_rot = food.get_relative_rot();
    if( relative_rot > 1.0f && !has_trait( trait_id( "SAPROPHAGE" ) ) &&
        !has_trait( trait_id( "SAPROVORE" ) ) && !has_bionic( bio_digestion ) ) {
        const float rottedness = clamp( 2 * relative_rot - 2.0f, 0.1f, 1.0f );
        // ~-1 health per 1 nutrition at halfway-rotten-away, ~0 at "just got rotten"
        // But always round down
        int h_loss = -rottedness * comest.nutr;
        mod_healthy_mod( h_loss, -200 );
        add_msg( m_debug, "%d health from %0.2f%% rotten food", h_loss, rottedness );
    }

    const auto nutr = nutrition_for( food );
    mod_hunger( -nutr );
    mod_thirst( -comest.quench );
    mod_stomach_food( nutr );
    mod_stomach_water( comest.quench );
    if( comest.healthy != 0 ) {
        // Effectively no cap on health modifiers from food
        mod_healthy_mod( comest.healthy, ( comest.healthy >= 0 ) ? 200 : -200 );
    }

    if( comest.stim != 0 &&
        ( abs( stim ) < ( abs( comest.stim ) * 3 ) ||
          sgn( stim ) != sgn( comest.stim ) ) ) {
        if( comest.stim < 0 ) {
            stim = std::max( comest.stim * 3, stim + comest.stim );
        } else {
            stim = std::min( comest.stim * 3, stim + comest.stim );
        }
    }
    add_addiction( comest.add, comest.addict );
    if( addiction_craving( comest.add ) != MORALE_NULL ) {
        rem_morale( addiction_craving( comest.add ) );
    }

    // Morale is in minutes
    int morale_time = HOURS( 2 ) / MINUTES( 1 );
    if( food.has_flag( "HOT" ) && food.has_flag( "EATEN_HOT" ) ) {
        morale_time = HOURS( 3 ) / MINUTES( 1 );
        int clamped_nutr = std::max( 5, std::min( 20, nutr / 10 ) );
        add_morale( MORALE_FOOD_HOT, clamped_nutr, 20, morale_time, morale_time / 2 );
    }

    std::pair<int, int> fun = fun_for( food );
    if( fun.first < 0 ) {
        add_morale( MORALE_FOOD_BAD, fun.first, fun.second, morale_time, morale_time / 2, false,
                    food.type );
    } else if( fun.first > 0 ) {
        add_morale( MORALE_FOOD_GOOD, fun.first, fun.second, morale_time, morale_time / 2, false,
                    food.type );
    }

    const bool hibernate = has_active_mutation( trait_id( "HIBERNATE" ) );
    if( hibernate ) {
        if( ( nutr > 0 && get_hunger() < -60 ) || ( comest.quench > 0 && get_thirst() < -60 ) ) {
            //Tell the player what's going on
            add_msg_if_player( _( "You gorge yourself, preparing to hibernate." ) );
            if( one_in( 2 ) ) {
                //50% chance of the food tiring you
                mod_fatigue( nutr );
            }
        }
        if( ( nutr > 0 && get_hunger() < -200 ) || ( comest.quench > 0 && get_thirst() < -200 ) ) {
            //Hibernation should cut burn to 60/day
            add_msg_if_player( _( "You feel stocked for a day or two. Got your bed all ready and secured?" ) );
            if( one_in( 2 ) ) {
                //And another 50%, intended cumulative
                mod_fatigue( nutr );
            }
        }

        if( ( nutr > 0 && get_hunger() < -400 ) || ( comest.quench > 0 && get_thirst() < -400 ) ) {
            add_msg_if_player(
                _( "Mmm.  You can still fit some more in...but maybe you should get comfortable and sleep." ) );
            if( !one_in( 3 ) ) {
                //Third check, this one at 66%
                mod_fatigue( nutr );
            }
        }
        if( ( nutr > 0 && get_hunger() < -600 ) || ( comest.quench > 0 && get_thirst() < -600 ) ) {
            add_msg_if_player( _( "That filled a hole!  Time for bed..." ) );
            // At this point, you're done.  Schlaf gut.
            mod_fatigue( nutr );
        }
    }

    // Moved here and changed a bit - it was too complex
    // Incredibly minor stuff like this shouldn't require complexity
    if( !is_npc() && has_trait( trait_id( "SLIMESPAWNER" ) ) &&
        ( get_hunger() < capacity + 40 || get_thirst() < capacity + 40 ) ) {
        add_msg_if_player( m_mixed,
                           _( "You feel as though you're going to split open!  In a good way?" ) );
        mod_pain( 5 );
        std::vector<tripoint> valid;
        for( const tripoint &dest : g->m.points_in_radius( pos(), 1 ) ) {
            if( g->is_empty( dest ) ) {
                valid.push_back( dest );
            }
        }
        int numslime = 1;
        for( int i = 0; i < numslime && !valid.empty(); i++ ) {
            const tripoint target = random_entry_removed( valid );
            if( monster *const slime = g->summon_mon( mon_player_blob, target ) ) {
                slime->friendly = -1;
            }
        }
        mod_hunger( 40 );
        mod_thirst( 40 );
        //~slimespawns have *small voices* which may be the Nice equivalent
        //~of the Rat King's ALL CAPS invective.  Probably shared-brain telepathy.
        add_msg_if_player( m_good, _( "hey, you look like me! let's work together!" ) );
    }

    // Last thing that happens before capping hunger
    if( get_hunger() < capacity && has_trait( trait_id( "EATHEALTH" ) ) ) {
        int excess_food = capacity - get_hunger();
        add_msg_player_or_npc( _( "You feel the %s filling you out." ),
                               _( "<npcname> looks better after eating the %s." ),
                               food.tname().c_str() );
        // Guaranteed 1 HP healing, no matter what.  You're welcome.  ;-)
        if( excess_food <= 5 ) {
            healall( 1 );
        } else {
            // Straight conversion, except it's divided amongst all your body parts.
            healall( excess_food /= 5 );
        }

        // Note: We want this here to prevent "you can't finish this" messages
        set_hunger( capacity );
    }

    cap_nutrition_thirst( *this, capacity, nutr > 0, comest.quench > 0 );
}