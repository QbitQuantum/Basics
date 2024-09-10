static void DrawShips(void)
{
  register struct player *j;
  register struct phaser *php;

  char    idbuf[10];
  const int view = SCALE * TWINSIDE / 2;
  int     dx, dy, px, py, wx, wy, tx, ty, lx, ly;

#ifndef DYNAMIC_BITMAPS
  W_Icon(*ship_bits)[VIEWS];
#endif



  /* Kludge to try to fix missing ID chars on tactical (short range) display.
   *
   */

  idbuf[0] = '0';
  idbuf[1] = '\0';

  for (j = players + MAXPLAYER - 1; j >= players; --j)
    {

#ifdef HAVE_XPM
      void   *sprite = S_Ship(j->p_no);

#else

      if ((j->p_status != PALIVE) && (j->p_status != PEXPLODE))
  continue;

      if (j->p_flags & PFOBSERV)
  {
    /* observer and NOT locked onto a player (ie. locked onto planet or
     * * * vacuum) */

    if (!(j->p_flags & PFPLOCK))
      continue;

    /* observer and NOT cloaked - don't display ship but do tractors *
     * * phasers and torps are done for that ship already */

    if (!(j->p_flags & PFCLOAK))
      continue;
  }
#endif /* HAVE_XPM */

      /* jmn - observer support.. tried to diplay tractors but no works */

      if (j->p_flags & PFCLOAK)
  {
    if (j->p_cloakphase < (CLOAK_PHASES - 1))
      {

#ifdef SOUND
        if (myPlayer(j) && (j->p_cloakphase == 0)) {
#if defined(HAVE_SDL)
    Play_Sound(CLOAKED_WAV);
#else
    Play_Sound(CLOAK_SOUND);
#endif
        }
#endif

        j->p_cloakphase++;
      }
  }
      else
  {
    if (j->p_cloakphase)
      {

#ifdef SOUND
        if (myPlayer(j))
    if (j->p_cloakphase == CLOAK_PHASES - 1) {
#if defined(HAVE_SDL)
      Play_Sound(UNCLOAK_WAV);
#else
      Play_Sound(UNCLOAK_SOUND);
    } else {
      Abort_Sound(CLOAK_SOUND);
#endif
    }
#endif

        j->p_cloakphase--;
      }
  }
      dx = j->p_x - me->p_x;
      dy = j->p_y - me->p_y;

#ifdef HAVE_XPM
      if ((sprite == NULL) && (dx > view || dx < -view || dy > view || dy < -view))
#else
      if (dx > view || dx < -view || dy > view || dy < -view)
#endif

  continue;

      dx = dx / SCALE + TWINSIDE / 2;
      dy = dy / SCALE + TWINSIDE / 2;


#ifdef HAVE_XPM
      if ((sprite == NULL) || (pixFlags & NO_CLK_PIX))
#endif

  if (j->p_flags & PFCLOAK && (j->p_cloakphase == (CLOAK_PHASES - 1)))
    {
      if (myPlayer(j)

#ifdef RECORDGAME
    || playback
#endif

    )
        {
    W_WriteBitmap(dx - (cloak_width / 2), dy - (cloak_height / 2),
            cloakicon, myColor);

#ifdef VARY_HULL
    clearzone[0][clearcount] = dx - (shield_width / 2 + 1);
    clearzone[1][clearcount] = dy - (shield_height / 2 + 1);
    clearzone[2][clearcount] = shield_width + 3;
    clearzone[3][clearcount] = shield_height + 3;
    clearcount++;
#else
    clearzone[0][clearcount] = dx - (shield_width / 2);
    clearzone[1][clearcount] = dy - (shield_height / 2);
    clearzone[2][clearcount] = shield_width;
    clearzone[3][clearcount] = shield_height;
    clearcount++;
#endif

    goto shieldlabel;    /* draw the shield even when
              * * * cloaked */
        }
      continue;
    }
      if (j->p_status == PALIVE)
  {

#ifndef DYNAMIC_BITMAPS
    switch (j->p_team)
      {
      case FED:

#ifdef TNG_FED_BITMAPS
        if (use_tng_fed_bitmaps)
    ship_bits = tng_fed_bitmaps;
        else
#endif

    ship_bits = fed_bitmaps;
        break;
      case ROM:
        ship_bits = rom_bitmaps;
        break;
      case KLI:
        ship_bits = kli_bitmaps;
        break;
      case ORI:
        ship_bits = ori_bitmaps;
        break;
      default:
        ship_bits = ind_bitmaps;
        break;
      }
#endif

#if defined (VARY_HULL) || defined (BEEPLITE)
    clearzone[0][clearcount] = dx - (shield_width / 2 + 6);
    clearzone[1][clearcount] = dy - (shield_height / 2 + 6);
    clearzone[2][clearcount] = shield_width + 12;
    clearzone[3][clearcount] = shield_height + 12;
    clearcount++;
#else
    clearzone[0][clearcount] = dx - (shield_width / 2);
    clearzone[1][clearcount] = dy - (shield_height / 2);
    clearzone[2][clearcount] = shield_width;
    clearzone[3][clearcount] = shield_height;
    clearcount++;
#endif

#ifdef HAVE_XPM
    if (sprite != NULL)
      {
        clearsize = W_DrawSprite(sprite, dx, dy, TWINSIDE);

#if defined (VARY_HULL)
        if (clearsize > shield_width + 12)
#else
        if (clearsize > shield_width)
#endif

    {
      clearcount--;
      clearzone[0][clearcount] = dx - (clearsize / 2);
      clearzone[1][clearcount] = dy - (clearsize / 2);
      clearzone[2][clearcount] = clearsize;
      clearzone[3][clearcount] = clearsize;
      clearcount++;
    }
      }
    else
#endif /* HAVE_XPM */

      if (j->p_team == ROM && j->p_ship.s_type == CRUISER &&
    ROMVLVS)
      W_WriteBitmap(dx - (j->p_ship.s_width / 2),
      dy - (j->p_ship.s_height / 2), ROMVLVS_bitmap[rosette(j->p_dir)],
        playerColor(j));
    else
      W_WriteBitmap(dx - (j->p_ship.s_width / 2),
        dy - (j->p_ship.s_height / 2),

#ifndef DYNAMIC_BITMAPS
        ship_bits[j->p_ship.s_type][rosette(j->p_dir)],
#else
        ship_bitmaps[PlayerBitmap(j)][rosette(j->p_dir)],
#endif

        playerColor(j));

    if (j->p_cloakphase > 0)
      {

#ifdef HAVE_XPM
        if (sprite == NULL)
#endif

    W_WriteBitmap(dx - (cloak_width / 2),
      dy - (cloak_height / 2), cloakicon, playerColor(j));
      if (!myPlayer(j))      /* if myplayer draw the shield */
        continue;
      }

  shieldlabel:

#ifdef BEEPLITE
    if ((UseLite && emph_player_seq_n[j->p_no] > 0)
        && (liteflag & LITE_PLAYERS_LOCAL))
      {
        int     seq_n = emph_player_seq_n[j->p_no] % emph_player_seql_frames;

        W_WriteBitmap(dx - (emph_player_seql_width / 2),
          dy - (emph_player_seql_height / 2),
          emph_player_seql[seq_n],
          W_White);
      }
#endif

#ifdef VARY_HULL
    if (j == me && vary_hull)
      {
        int     hull_left = (100 * (me->p_ship.s_maxdamage -
          me->p_damage)) / me->p_ship.s_maxdamage, hull_num = 7;
        int     hull_color;

        if (hull_left <= 16)
    {
      hull_num = 0;
      hull_color = W_Red;
    }
        else if (hull_left <= 28)
    {
      hull_num = 1;
      hull_color = W_Yellow;
    }
        else if (hull_left <= 40)
    {
      hull_num = 2;
      hull_color = W_Green;
    }
        else if (hull_left <= 52)
    {
      hull_num = 3;
      hull_color = W_Green;
    }
        else if (hull_left <= 64)
    {
      hull_num = 4;
      hull_color = W_Green;
    }
        else if (hull_left <= 76)
    {
      hull_num = 5;
      hull_color = W_White;
    }
        else if (hull_left <= 88)
    {
      hull_num = 6;
      hull_color = W_White;
    }
        else
    hull_color = playerColor(j);

        W_WriteBitmap(dx - (shield_width / 2 + 1),
          dy - (shield_height / 2 + 1),
          hull[hull_num], hull_color);
      }
#endif

#ifdef SOUND
    if (j->p_no == me->p_no)
      {
        if ((sound_flags & PFSHIELD) && !(j->p_flags & PFSHIELD)) {
#if defined(HAVE_SDL)
    Play_Sound(SHIELD_DOWN_WAV);
#else
    Play_Sound(SHIELD_DOWN_SOUND);
#endif
        }
        if (!(sound_flags & PFSHIELD) && (j->p_flags & PFSHIELD)) {
#if defined(HAVE_SDL)
    Play_Sound(SHIELD_UP_WAV);
#else
    Play_Sound(SHIELD_UP_SOUND);
#endif
        }
      }
#endif

    /* It used to be that if "showShields" was false, shields were not
     * * * shown.  COW has already stopped accepting showShields flags
     * * from * the server, now stop using showShields altogether.
     * James * Soutter * (Zork)     4 Jan 95 */

    if (j->p_flags & PFSHIELD)
      {
        int     color = playerColor(j);

#ifdef VSHIELD_BITMAPS
        int     shieldnum;

        if (j == me && VShieldBitmaps)
    {
      shieldnum = SHIELD_FRAMES * me->p_shield / me->p_ship.s_maxshield;
      if (shieldnum >= SHIELD_FRAMES)
        shieldnum = SHIELD_FRAMES - 1;
      color = gColor;
      if (shieldnum < SHIELD_FRAMES * 2 / 3)
        {
          color = yColor;
          if (shieldnum < SHIELD_FRAMES * 2 / 3)
      {
        color = rColor;
      }
        }
    }
        else
    {
      color = playerColor(j);
      shieldnum = 2;
    }
#endif

        if (warnShields && j == me)
    {
      switch (me->p_flags & (PFGREEN | PFYELLOW | PFRED))
        {
        case PFGREEN:
          color = gColor;
          break;
        case PFYELLOW:
          color = yColor;
          break;
        case PFRED:
          color = rColor;
          break;
        }
    }

#ifdef VSHIELD_BITMAPS
        W_WriteBitmap(dx - (shield_width / 2),
      dy - (shield_height / 2), shield[shieldnum], color);
#else

        W_WriteBitmap(dx - (shield_width / 2),
          dy - (shield_height / 2), shield, color);
#endif
      }
    /* Det circle */
    if (detCircle)
            {
        if (myPlayer(j) || isObsLockPlayer(j))
              {
      int dcr = DETDIST*2/SCALE;
      int dcx = dx - (dcr/2);
      int dcy = dy - (dcr/2);
      W_WriteCircle(w, dcy, dcy, dcr, W_Red);
      clearzone[0][clearcount] = dcx;
      clearzone[1][clearcount] = dcy;
      clearzone[2][clearcount] = dcr + dcr;
      clearzone[3][clearcount] = dcr + dcr;
      clearcount++;
      detCircle--;
                }
            }
    if (j->p_flags & PFCLOAK)    /* when cloaked stop here */
      continue;

    {
      int     color = playerColor(j);

      idbuf[0] = *(shipnos + j->p_no);

      if (myPlayer(j) || isObsLockPlayer(j))
        {
    switch (me->p_flags & (PFGREEN | PFYELLOW | PFRED))
      {
      case PFGREEN:
        color = gColor;
        break;
      case PFYELLOW:
        color = yColor;
        break;
      case PFRED:
        color = rColor;
        break;
      }
        }
      W_MaskText(w, dx + (j->p_ship.s_width / 2),
           dy - (j->p_ship.s_height / 2), color,
           idbuf, 1, shipFont(j));

      clearzone[0][clearcount] = dx + (j->p_ship.s_width / 2);
      clearzone[1][clearcount] = dy - (j->p_ship.s_height / 2);
      clearzone[2][clearcount] = W_Textwidth;
      clearzone[3][clearcount] = W_Textheight;
      clearcount++;
    }

  }
      else if (j->p_status == PEXPLODE)
  {
    int     i;

    i = j->p_explode;

#ifdef SOUND
    if (i == 1)
#if defined(HAVE_SDL)
      Play_Sound(j == me ? EXPLOSION_WAV : EXPLOSION_OTHER_WAV);
#else
      Play_Sound(j == me ? EXPLOSION_SOUND : OTHER_EXPLOSION_SOUND);
#endif
#endif

#ifdef HAVE_XPM
    if (sprite != NULL)
      {
        clearsize = W_DrawSprite(sprite, dx, dy, TWINSIDE);
        clearzone[0][clearcount] = dx - (clearsize / 2);
        clearzone[1][clearcount] = dy - (clearsize / 2);
        clearzone[2][clearcount] = clearsize;
        clearzone[3][clearcount] = clearsize;
        clearcount++;
      }
    else
#endif

      if (i < EX_FRAMES ||
    (i < SBEXPVIEWS && j->p_ship.s_type == STARBASE))
      {

        if (j->p_ship.s_type == STARBASE)
    {
      W_WriteBitmap(dx - (sbexp_width / 2),
        dy - (sbexp_height / 2), sbexpview[i],
        playerColor(j));
      clearzone[0][clearcount] = dx - (sbexp_width / 2);
      clearzone[1][clearcount] = dy - (sbexp_height / 2);
      clearzone[2][clearcount] = sbexp_width;
      clearzone[3][clearcount] = sbexp_height;
    }
        else
    {
      W_WriteBitmap(dx - (ex_width / 2), dy - (ex_height / 2),
        expview[i], playerColor(j));
      clearzone[0][clearcount] = dx - (ex_width / 2);
      clearzone[1][clearcount] = dy - (ex_height / 2);
      clearzone[2][clearcount] = ex_width;
      clearzone[3][clearcount] = ex_height;
    }
        clearcount++;
        j->p_explode++;
      }
  }

      /* Now draw his phaser (if it exists) */
      php = &phasers[j->p_no];

      if (php->ph_status != PHFREE)
  {

#ifdef SOUND
    if (!sound_phaser)
      {
#if defined(HAVE_SDL)
        Play_Sound(j == me ? PHASER_WAV : PHASER_OTHER_WAV);
#else
        Play_Sound(j == me ? PHASER_SOUND : OTHER_PHASER_SOUND);
#endif
        sound_phaser++;
      }
#endif

    if ((php->ph_updateFuse -= weaponUpdate) == 0)
      {
        /* Expire the phaser */

#if 0
        fputs("[phaser]", stderr);
        fflush(stderr);
#endif

        php->ph_status = PHFREE;
      }
    else
      {
        if (php->ph_status == PHMISS)
    {
      /* Here I will have to compute end coordinate */
      tx = PHASEDIST * j->p_ship.s_phaserdamage / 100 *
          Cos[php->ph_dir];

      ty = PHASEDIST * j->p_ship.s_phaserdamage / 100 *
          Sin[php->ph_dir];

      tx = (j->p_x + tx - me->p_x) / SCALE + TWINSIDE / 2;
      ty = (j->p_y + ty - me->p_y) / SCALE + TWINSIDE / 2;
      php->ph_fuse = 0;

    }
        else if (php->ph_status == PHHIT2)
    {
      tx = (php->ph_x - me->p_x) / SCALE + TWINSIDE / 2;
      ty = (php->ph_y - me->p_y) / SCALE + TWINSIDE / 2;
    }
        else
    {        /* Start point is dx, dy */
      tx = (players[php->ph_target].p_x - me->p_x) /
          SCALE + TWINSIDE / 2;
      ty = (players[php->ph_target].p_y - me->p_y) /
          SCALE + TWINSIDE / 2;
    }


        /* Shrink the phasers if necessary: * * Measure length in 16ths
         *
         * * to make the maths a little * easier for the computer (div
         * 16  * is a 4 bit shift). *  * Add 8 to each sum to round
         * properly.  */

        if (shrinkPhaserOnMiss || php->ph_status != PHMISS)
    {
      if (j == me)
        {
          px = (dx * (16 - phaserShrink) + tx * phaserShrink + 8)
        / 16;
          py = (dy * (16 - phaserShrink) + ty * phaserShrink + 8)
        / 16;
        }
      else
        {
          px = (dx * (16 - theirPhaserShrink) +
          tx * theirPhaserShrink + 8) / 16;

          py = (dy * (16 - theirPhaserShrink) +
          ty * theirPhaserShrink + 8) / 16;
        }
    }
        else
    {
      px = dx;
      py = dy;
    }


        /* Now draw the phasers */

        if (friendlyPlayer(j))
    {
      if (highlightFriendlyPhasers && (php->ph_status == PHHIT))
        W_CacheLine(w, px, py, tx, ty, foreColor);
      else
        {
          if ((php->ph_fuse % 2) == 1)
      W_CacheLine(w, px, py, tx, ty, foreColor);
          else
      W_CacheLine(w, px, py, tx, ty, shipCol[remap[j->p_team]]);
        }
      php->ph_fuse++;

      clearline[0][clearlcount] = px;
      clearline[1][clearlcount] = py;
      clearline[2][clearlcount] = tx;
      clearline[3][clearlcount] = ty;
      clearlcount++;
    }
        else
    {
      if ((enemyPhasers > 0) && (enemyPhasers <= 10))
        {
          unsigned char dir;

          if (tx == px && ty == py)
      continue;

#ifdef SHORT_PACKETS
          if (php->ph_status != PHMISS) /* KOC 10/20/95  */
      {      /* hack for SP_2 */
#define XPI     3.1415926
        dir = (unsigned char) nint(atan2((double) (ty - py),
           (double) (tx - px)) / XPI * 128.0);
#undef XPI
      }
          else
#endif

      {
        dir = NORMALIZE(php->ph_dir + 64);
      }

          wx = px + enemyPhasers * Cos[dir];
          wy = py + enemyPhasers * Sin[dir];
          lx = px - enemyPhasers * Cos[dir];
          ly = py - enemyPhasers * Sin[dir];

          W_MakePhaserLine(w, wx, wy, tx, ty,
               shipCol[remap[j->p_team]]);
          W_MakePhaserLine(w, lx, ly, tx, ty,
               shipCol[remap[j->p_team]]);

          php->ph_fuse++;

          clearline[0][clearlcount] = wx;
          clearline[1][clearlcount] = wy;
          clearline[2][clearlcount] = tx;
          clearline[3][clearlcount] = ty;
          clearlcount++;

          clearline[0][clearlcount] = lx;
          clearline[1][clearlcount] = ly;
          clearline[2][clearlcount] = tx;
          clearline[3][clearlcount] = ty;
          clearlcount++;
        }
      else
        {
          W_MakePhaserLine(w, px, py, tx, ty,
               shipCol[remap[j->p_team]]);

          php->ph_fuse++;

          clearline[0][clearlcount] = px;
          clearline[1][clearlcount] = py;
          clearline[2][clearlcount] = tx;
          clearline[3][clearlcount] = ty;
          clearlcount++;
        }
    }
      }
  }

#ifdef SOUND
      else if (j->p_no == me->p_no)
  sound_phaser = 0;
#endif

      /* ATM - show tractor/pressor beams (modified by James Collins) */
      /* showTractorPressor is a variable set by xtrekrc. */

      if (showTractorPressor)
  {
    if (myPlayer(j) && isAlive(me) && (j->p_flags & PFTRACT || j->p_flags & PFPRESS))
      {
        double  theta;
        unsigned char dir;
        int     lx[2], ly[2], target_width;

        struct player *tractee;

        if (me->p_tractor < 0 || me->p_tractor >= MAXPLAYER)
    continue;
        tractee = &players[me->p_tractor];

        if (tractee->p_status != PALIVE ||
      ((tractee->p_flags & PFCLOAK) &&
       (tractee->p_cloakphase == (CLOAK_PHASES - 1))))
    {
      continue;
    }

        if (tcounter >= 2)
    {        /* continue tractor stuff */
      if (!continuetractor)
        tcounter--;
      px = (players[me->p_tractor].p_x - me->p_x)
          / SCALE + TWINSIDE / 2;
      py = (players[me->p_tractor].p_y - me->p_y)
          / SCALE + TWINSIDE / 2;
      if (px == dx && py == dy)
        continue;      /* this had better be last *
              *
              * * in for(..) */
#define XPI     3.1415926
      theta = atan2((double) (px - dx),
        (double) (dy - py)) + XPI / 2.0;
      dir = (unsigned char) nint(theta / XPI * 128.0);
      if (tractee->p_flags & PFSHIELD)
        target_width = shield_width;
      else
        {
          target_width = tractee->p_ship.s_width / 2;
        }
      lx[0] = px + (Cos[dir] * (target_width / 2));
      ly[0] = py + (Sin[dir] * (target_width / 2));
      lx[1] = px - (Cos[dir] * (target_width / 2));
      ly[1] = py - (Sin[dir] * (target_width / 2));
#undef XPI
      if (j->p_flags & PFPRESS)
        {
          W_MakeTractLine(w, dx, dy, lx[0], ly[0], W_Yellow);
          W_MakeTractLine(w, dx, dy, lx[1], ly[1], W_Yellow);
        }
      else
        {
          W_MakeTractLine(w, dx, dy, lx[0], ly[0], W_Green);
          W_MakeTractLine(w, dx, dy, lx[1], ly[1], W_Green);
        }

#ifdef WIN32
      /* Fixup for minor inconsistencies between SAC's interger *
       *
       * * linedraw and Win32 LineTo() */
      tpline = clearlcount;
#endif

      clearline[0][clearlcount] = dx;
      clearline[1][clearlcount] = dy;
      clearline[2][clearlcount] = lx[0];
      clearline[3][clearlcount] = ly[0];
      clearlcount++;
      clearline[0][clearlcount] = dx;
      clearline[1][clearlcount] = dy;
      clearline[2][clearlcount] = lx[1];
      clearline[3][clearlcount] = ly[1];
      clearlcount++;
    }
      }
    else if (!(me->p_flags & PFPRESS || me->p_flags & PFTRACT))
      tcounter = 2;
  }
    }
}