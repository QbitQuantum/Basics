int dogaze(void)
{
	struct monst *mtmp;
	int looked = 0;
	char qbuf[QBUFSZ];
	int i;
	uchar adtyp = 0;

	for (i = 0; i < NATTK; i++) {
	    if (youmonst.data->mattk[i].aatyp == AT_GAZE) {
		adtyp = youmonst.data->mattk[i].adtyp;
		break;
	    }
	}
	if (adtyp != AD_CONF && adtyp != AD_FIRE) {
	    impossible("gaze attack %d?", adtyp);
	    return 0;
	}


	if (Blind) {
	    pline("You can't see anything to gaze at.");
	    return 0;
	}
	if (u.uen < 15) {
	    pline("You lack the energy to use your special gaze!");
	    return 0;
	}
	u.uen -= 15;
	iflags.botl = 1;

	for (mtmp = level->monlist; mtmp; mtmp = mtmp->nmon) {
	    if (DEADMONSTER(mtmp)) continue;
	    if (canseemon(mtmp) && couldsee(mtmp->mx, mtmp->my)) {
		looked++;
		if (Invis && !perceives(mtmp->data))
		    pline("%s seems not to notice your gaze.", Monnam(mtmp));
		else if (mtmp->minvis && !See_invisible)
		    pline("You can't see where to gaze at %s.", Monnam(mtmp));
		else if (mtmp->m_ap_type == M_AP_FURNITURE
			|| mtmp->m_ap_type == M_AP_OBJECT) {
		    looked--;
		    continue;
		} else if (flags.safe_dog && !Confusion && !Hallucination
		  && mtmp->mtame) {
		    pline("You avoid gazing at %s.", y_monnam(mtmp));
		} else {
		    if (flags.confirm && mtmp->mpeaceful && !Confusion
							&& !Hallucination) {
			sprintf(qbuf, "Really %s %s?",
			    (adtyp == AD_CONF) ? "confuse" : "attack",
			    mon_nam(mtmp));
			if (yn(qbuf) != 'y') continue;
			setmangry(mtmp);
		    }
		    if (!mtmp->mcanmove || mtmp->mstun || mtmp->msleeping ||
				    !mtmp->mcansee || !haseyes(mtmp->data)) {
			looked--;
			continue;
		    }
		    /* No reflection check for consistency with when a monster
		     * gazes at *you*--only medusa gaze gets reflected then.
		     */
		    if (adtyp == AD_CONF) {
			if (!mtmp->mconf)
			    pline("Your gaze confuses %s!", mon_nam(mtmp));
			else
			    pline("%s is getting more and more confused.",
							Monnam(mtmp));
			mtmp->mconf = 1;
		    } else if (adtyp == AD_FIRE) {
			int dmg = dice(2,6);
			pline("You attack %s with a fiery gaze!", mon_nam(mtmp));
			if (resists_fire(mtmp)) {
			    pline("The fire doesn't burn %s!", mon_nam(mtmp));
			    dmg = 0;
			}
			if ((int) u.ulevel > rn2(20))
			    destroy_mitem(mtmp, SCROLL_CLASS, AD_FIRE);
			if ((int) u.ulevel > rn2(20))
			    destroy_mitem(mtmp, POTION_CLASS, AD_FIRE);
			if ((int) u.ulevel > rn2(25))
			    destroy_mitem(mtmp, SPBOOK_CLASS, AD_FIRE);
			if (dmg && !DEADMONSTER(mtmp)) mtmp->mhp -= dmg;
			if (mtmp->mhp <= 0) killed(mtmp);
		    }
		    /* For consistency with passive() in uhitm.c, this only
		     * affects you if the monster is still alive.
		     */
		    if (!DEADMONSTER(mtmp) &&
			  (mtmp->data==&mons[PM_FLOATING_EYE]) && !mtmp->mcan) {
			if (!Free_action) {
			    pline("You are frozen by %s gaze!",
					     s_suffix(mon_nam(mtmp)));
			    nomul((u.ulevel > 6 || rn2(4)) ?
				    -dice((int)mtmp->m_lev+1,
					    (int)mtmp->data->mattk[0].damd)
				    : -200, "frozen by a monster's gaze");
			    return 1;
			} else
			    pline("You stiffen momentarily under %s gaze.",
				    s_suffix(mon_nam(mtmp)));
		    }
		    /* Technically this one shouldn't affect you at all because
		     * the Medusa gaze is an active monster attack that only
		     * works on the monster's turn, but for it to *not* have an
		     * effect would be too weird.
		     */
		    if (!DEADMONSTER(mtmp) &&
			    (mtmp->data == &mons[PM_MEDUSA]) && !mtmp->mcan) {
			pline(
			 "Gazing at the awake %s is not a very good idea.",
			    l_monnam(mtmp));
			/* as if gazing at a sleeping anything is fruitful... */
			pline("You turn to stone...");
			killer_format = KILLED_BY;
			killer = "deliberately meeting Medusa's gaze";
			done(STONING);
		    }
		}
	    }
	}
	if (!looked) pline("You gaze at no place in particular.");
	return 1;
}