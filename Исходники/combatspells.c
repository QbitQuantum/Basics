/* Generischer Kampfzauber */
int sp_kampfzauber(struct castorder * co)
{
  fighter * fi = co->magician.fig;
  int level = co->level;
  double power = co->force;
  const spell * sp = co->sp;
  battle *b = fi->side->battle;
  troop at, dt;
  message *m;
  /* Immer aus der ersten Reihe nehmen */
  int force, enemies;
  int killed = 0;
  const char *damage;

  if (power <= 0)
    return 0;
  at.fighter = fi;
  at.index = 0;

  switch (sp->id) {
      /* lovar halbiert im Schnitt! */
    case SPL_FIREBALL:
      damage = spell_damage(0);
      force = lovar(get_force(power, 0));
      break;
    case SPL_HAGEL:
      damage = spell_damage(2);
      force = lovar(get_force(power, 4));
      break;
    case SPL_METEORRAIN:
      damage = spell_damage(1);
      force = lovar(get_force(power, 1));
      break;
    default:
      damage = spell_damage(10);
      force = lovar(get_force(power, 10));
  }

  enemies = count_enemies(b, fi, FIGHT_ROW, BEHIND_ROW - 1, SELECT_ADVANCE);
  if (enemies == 0) {
    message *m =
      msg_message("battle::out_of_range", "mage spell", fi->unit, sp);
    message_all(b, m);
    msg_release(m);
    return 0;
  }

  while (force > 0 && killed < enemies) {
    dt = select_enemy(fi, FIGHT_ROW, BEHIND_ROW - 1, SELECT_ADVANCE);
    assert(dt.fighter);
    --force;
    killed += terminate(dt, at, AT_COMBATSPELL, damage, false);
  }

  m = msg_message("battle::combatspell", "mage spell dead",
    fi->unit, sp, killed);
  message_all(b, m);
  msg_release(m);

  return level;
}