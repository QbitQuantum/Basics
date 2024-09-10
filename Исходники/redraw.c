static void auto_features(void)
{
    struct player *pl;
    struct planet *pln;
    u_char course;
    int troop_capacity=0;
    static int sd_time_last = -1;
    int sd_time;

    check_observs();
    if (!living) return;

    if (me->p_flags & PFSELFDEST) {
        sd_time = (me->p_selfdest - me->p_updates) / 10;
        if (sd_time != sd_time_last) {
            sd_time_last = sd_time;
            switch (sd_time) {
            case 4:
            case 5:
              new_warning(UNDEF, "You notice everyone on the bridge is staring at you.");
              break;
            default:
              new_warning(UNDEF, "Stand By ... Self Destruct in %d seconds", sd_time);
              break;
            }
        }
    } else {
        sd_time_last = -1;
    }

    /* provide a refit countdown 4/6/92 TC */

    if (me->p_flags & PFREFITTING) {
	static int lastRefitValue = 0; /* for smooth display */
	if (lastRefitValue != (rdelay - me->p_updates)/10) {
	    lastRefitValue = (rdelay - me->p_updates)/10; /* CSE to the rescue? */
	    switch (lastRefitValue) {
	      case 3:
	      case 2:
		new_warning(UNDEF, "Engineering:  Energizing transporters in %d seconds", lastRefitValue);
		break;
	      case 1:
		new_warning(UNDEF, "Engineering:  Energize. [ SFX: chimes ]");
		break;
	      case 0:
		switch (random()%5) {
		  case 0:
		    new_warning(UNDEF,"Wait, you forgot your toothbrush!");
		    break;
		  case 1:
		    new_warning(UNDEF,"Nothing like turning in a used ship for a new one.");
		    break;
		  case 2:
		    new_warning(UNDEF,"First officer:  Oh no, not you again... we're doomed!");
		    break;
		  case 3:
		    new_warning(UNDEF,"First officer:  Uh, I'd better run diagnostics on the escape pods.");
		    break;
		  case 4:
		    new_warning(UNDEF,"Shipyard controller:  This time, *please* be more careful, okay?");
		    break;
		}
		break;
	    }
	}
    }

    /* provide a war declaration countdown 4/6/92 TC */

    if (me->p_flags & PFWAR) {
	static int lastWarValue = 0;
	if (lastWarValue != (delay - me->p_updates)/10) {
	    lastWarValue = (delay - me->p_updates)/10; /* CSE to the rescue? */
	    switch (lastWarValue) {
	      case 9:
		new_warning(UNDEF,"Weapons officer:  Not again!  This is absurd...");
		break;
	      case 8:
		break;
	      case 7:
		new_warning(UNDEF,"Weapons officer:  ... the whole ship's computer is down?");
		break;
	      case 6:
		break;
	      case 5:
		new_warning(UNDEF,"Weapons officer:  Just to twiddle a few bits of the ship's memory?");
		break;
	      case 4:
		break;
	      case 3:
		new_warning(UNDEF,"Weapons officer:  Bah! [ bangs fist on inoperative console ]");
		break;
	      case 2:
		break;
	      case 1:
		new_warning(UNDEF,"First Officer:  Easy, big guy... it's just one of those mysterious");
		break;
	      case 0:
		switch (random()%5) {
		  case 0:
		    new_warning(UNDEF,"First Officer:  laws of the universe, like 'tires on the ether'.");
		    break;
		  case 1:
		    new_warning(UNDEF,"First Officer:  laws of the universe, like 'Klingon bitmaps are ugly'.");
		    break;
		  case 2:
		    new_warning(UNDEF,"First Officer:  laws of the universe, like 'all admirals have scummed'.");
		    break;
		  case 3:
		    new_warning(UNDEF,"First Officer:  laws of the universe, like 'Mucus Pig exists'.");
		    break;
		  case 4:
		    new_warning(UNDEF,"First Officer:  laws of the universe, like 'guests advance 5x faster'.");
		    break;
		}
		break;
	    }
	}
    }

    /* give certain information about bombing or beaming */
    if (me->p_flags & PFBOMB) {
	if (planets[me->p_planet].pl_armies < 5) {
	    new_warning(UNDEF, "Weapons Officer: Bombarding %s... Ineffective, %d armies left.",
			planets[me->p_planet].pl_name,    /* Planet name for stats 10/20/96 [007] */
		    planets[me->p_planet].pl_armies); /* nifty info feature 2/14/92 TMC */
	    me->p_flags &= ~PFBOMB;
	}
	else {
	    new_warning(UNDEF, "Weapons Officer: Bombarding %s...  Sensors read %d armies left.",
		planets[me->p_planet].pl_name,
		planets[me->p_planet].pl_armies);
	}
    }

    /* Use person observed for kills if we are an observer */
    if (Observer && (me->p_flags & PFPLOCK))
        pl = &players[me->p_playerl];
    else
        pl = me;	/* Not observer, just use my kills */

    troop_capacity = (int)((float)((int)(pl->p_kills*100)/100.0) * (myship->s_type == ASSAULT?3:2));
    if (myship->s_type == STARBASE || troop_capacity > myship->s_maxarmies)
    	troop_capacity = myship->s_maxarmies;

    if (me->p_flags & PFBEAMUP) {
        /* Messages rewritten for stats 10/20/96 [007] */
        char *txt;
	if (me->p_flags & PFORBIT) {
	  if (planets[me->p_planet].pl_armies < 5) {
	    txt = "Too few armies to beam up";
	    me->p_flags &= ~PFBEAMUP;
	  } else if (me->p_armies == troop_capacity) {
	    txt = "No more room on board for armies";
	    me->p_flags &= ~PFBEAMUP;
	  } else {
	    txt = "Beaming up";
	  }
	  new_warning(UNDEF, "%s: (%d/%d) %s has %d armies left",
		      txt,
		      me->p_armies,
		      troop_capacity,
		      planets[me->p_planet].pl_name,	
		      planets[me->p_planet].pl_armies);
	    
	} else if (me->p_flags & PFDOCK) {
	    struct player *base = bay_owner(me);
	    if (base->p_armies <= 0) {
		txt = "Too few armies to beam up";
		me->p_flags &= ~PFBEAMUP;
	    } else if (me->p_armies >= troop_capacity) {
		txt = "No more room on board for armies";
		me->p_flags &= ~PFBEAMUP;
	    } else {
	        txt = "Beaming up";
	    }
	    new_warning(UNDEF, "%s: (%d/%d) Starbase %s has %d armies left",
			txt,
			me->p_armies,
			troop_capacity,
			base->p_name,
			base->p_armies);
	}
    }

    if (me->p_flags & PFBEAMDOWN) {
        /* Messages rewritten for stats 10/20/96 [007] */
        char *txt;
	if (me->p_flags & PFORBIT) {
	  if (me->p_armies == 0) {
	    txt = "No more armies to beam down";
	    me->p_flags &= ~PFBEAMDOWN;
	  } else {
	    txt = "Beaming down";
	  }
	  new_warning(UNDEF, "%s: (%d/%d) %s has %d armies left",
		      txt,
		      me->p_armies,
		      troop_capacity,
		      planets[me->p_planet].pl_name,	
		      planets[me->p_planet].pl_armies);

	} else if (me->p_flags & PFDOCK) {
	    struct player *base = bay_owner(me);
	    if (me->p_armies <= 0) {
		txt = "No more armies to beam down";
		me->p_flags &= ~PFBEAMDOWN;
	    } else if (base->p_armies >= base->p_ship.s_maxarmies) {
	        txt = "All troop bunkers are full";
	        me->p_flags &= ~PFBEAMDOWN;
	    } else {
	        txt = "Transfering ground units";
	    }
	    new_warning(UNDEF, "%s: (%d/%d) Starbase %s has %d armies left",
			txt,
			me->p_armies,
			troop_capacity,
			base->p_name,
			base->p_armies);
	}
    }

    if (me->p_flags & PFREPAIR) {
	if ((me->p_damage == 0) && (me->p_shield == me->p_ship.s_maxshield))
	    me->p_flags &= ~PFREPAIR;
    }
    if ((me->p_flags & PFPLOCK) && (!Observer)) { /* set course to player x */
	int dist;

	pl = &players[me->p_playerl];
	if (pl->p_status != PALIVE)
	    me->p_flags &= ~PFPLOCK;
	if (me->p_flags & PFTWARP){
	  if (pl->p_status != PALIVE){
	     new_warning(UNDEF, "Starbase is dead; Transwarp aborted!", -1);
	     me->p_flags &= ~PFTWARP;
	     me->p_speed = 3;
	     set_speed(0);
	  }
	  if (pl->p_ship.s_type != STARBASE){
	     new_warning(UNDEF, "Starbase has been turned in; Transwarp aborted!", -1);
	     me->p_flags &= ~PFTWARP;
	     me->p_speed = 3;
	     set_speed(0);
	  }
	  if(me->p_etemp > me->p_ship.s_maxegntemp - 10){
	     new_warning(UNDEF,"Warp drive reaching critical temperature!", -1);
	     me->p_flags &= ~PFTWARP;
	     me->p_speed = 3;
	     set_speed(0);
	  }
 	  else
	  if (me->p_fuel < (int) (me->p_ship.s_maxfuel/8)){
	     new_warning(UNDEF, "Not enough fuel to continue transwarp!", -1);
	     me->p_flags &= ~PFTWARP;
	     me->p_speed = 3;
	     set_speed(0);
	  }
	  else if(!(me->p_flags & PFPLOCK)){
	     new_warning(UNDEF, "Lost player lock!", -1);
	     me->p_flags &= ~PFTWARP;
	     me->p_speed = 3;
	     set_speed(0);
	  }
	}
	if (pl->p_ship.s_type == STARBASE) {
	    dist = hypot((double) (me->p_x - pl->p_x),
		(double) (me->p_y - pl->p_y));
	    if (!(me->p_flags & PFTWARP)) {
	        if (dist-(DOCKDIST/2) < (11500 * me->p_speed * me->p_speed) /
		        me->p_ship.s_decint) {
		    if (me->p_desspeed > 2) {
		        set_speed(me->p_desspeed-1);
		    }
	        }
	    }

	    if ((dist < 2*DOCKDIST) && (me->p_flags & PFTWARP)){
	        p_x_y_join(me, pl);
	        me->p_flags &= ~(PFPLOCK);
	        me->p_flags &= ~(PFTWARP);
#ifdef SB_CALVINWARP
                if (!(pl->p_flags & PFDOCKOK) ||
                    ((pl->p_flags & PFPRESS) &&
                     (pl->p_tractor == me->p_no))) ;
                else {
#endif

	            me->p_speed=2;
	            orbit();
#ifdef SB_CALVINWARP
                }
#endif
	    } else {
	        if ((dist < DOCKDIST) && (me->p_speed <= 2))  {
		    me->p_flags &= ~PFPLOCK;
		    orbit();
	        }
	    }
	}
	if (me->p_flags & PFPLOCK) {
	    course = newcourse(pl->p_x, pl->p_y);
	    if (me->p_flags & PFTWARP)
		me->p_dir = course;
	    else
	        set_course(course);
	}
    }
    if ((me->p_flags & PFPLLOCK) && (!Observer) ) { /* set course to planet */
	int dist;

	pln = &planets[me->p_planet];
	dist = hypot((double) (me->p_x - pln->pl_x),
	    (double) (me->p_y - pln->pl_y));

	/* This is magic.  It should be based on defines, but it slows
	   the ship down to warp two an appropriate distance from the
	   planet for orbit */

	if (dist-(ORBDIST/2) < (11500 * me->p_speed * me->p_speed) /
	        me->p_ship.s_decint) {
	    if (me->p_desspeed > 2) {
		set_speed(2);
	    }
	}

	if ((dist < ENTORBDIST) && (me->p_speed <= 2))  {
	    me->p_flags &= ~PFPLLOCK;
	    orbit();
	}
	else {
	    int ax, ay, ad, missing;
	    extern int nowobble;

	    /* calculate course to planet from current coordinates */
	    course = newcourse(pln->pl_x, pln->pl_y);

            /* avoid superfluous midflight wobble */
	    if (nowobble) {
	      /* test case; at 6 o'clock on earth, lock on altair, warp 8 */
	      /* calculate arrival point at current course */
	      ax = (double) (me->p_x + Cos[me->p_desdir] * dist);
	      ay = (double) (me->p_y + Sin[me->p_desdir] * dist);
	      ad = hypot((double) (ax - pln->pl_x),
			 (double) (ay - pln->pl_y));
	      
	      /* change to the corrected course if the expected error
		 exceeds the remaining distance divided by the nowobble
		 factor (25 works well) */
	      missing = (ad > dist / nowobble);
	      if (missing)
		set_course(course);
	    } else {
	      /* classical behaviour */
	      if ( (ABS(course-me->p_desdir) > 2) || (dist < ENTORBDIST*10) )
		set_course(course);
	    }
	}
    }
    /* Send ship cap if necessary */
    sndShipCap();

#ifdef STURGEON
    /* Check if eligible for free upgrade */
    if (sturgeon) {
        if (me->p_free_upgrade) {
            me->p_upgrades += baseupgradecost[me->p_free_upgrade] + me->p_upgradelist[me->p_free_upgrade]*adderupgradecost[me->p_free_upgrade];
            me->p_upgradelist[me->p_free_upgrade]++;
            sturgeon_apply_upgrade(me->p_free_upgrade, me, 1);
            me->p_free_upgrade = 0;
        }
    }
#endif
}