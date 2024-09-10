/* TODO: Perhaps work out some way to let controlled teleport in on a
   CMD_ARG_POS, but there are too many codeflow possibilities involved to make
   that easy. For now, if dotele turns into the spell, we copy the argument on
   to the spell-handling function (which currently ignores it), but the other
   possible codepaths just lose it. */
int
dotele(const struct nh_cmd_arg *arg)
{
    struct trap *trap;

    trap = t_at(level, u.ux, u.uy);
    if (trap && (!trap->tseen || trap->ttyp != TELEP_TRAP))
        trap = 0;

    if (trap) {
        if (trap->once) {
            pline("This is a vault teleport, usable once only.");
            if (yn("Jump in?") == 'n')
                trap = 0;
            else {
                deltrap(level, trap);
                newsym(u.ux, u.uy);
            }
        }
        if (trap)
            pline("You %s onto the teleportation trap.",
                  locomotion(youmonst.data, "jump"));
    }
    if (!trap) {
        boolean castit = FALSE;
        int sp_no = 0, energy = 0;

        if (!supernatural_ability_available(SPID_RLOC)) {
            /* Try to use teleport away spell. */
            if (objects[SPE_TELEPORT_AWAY].oc_name_known && !Confusion)
                for (sp_no = 0; sp_no < MAXSPELL; sp_no++)
                    if (spl_book[sp_no].sp_id == SPE_TELEPORT_AWAY) {
                        castit = TRUE;
                        break;
                    }
            if (!castit) {
                if (!Teleportation)
                    pline("You don't know that spell.");
                else
                    pline("You are not able to teleport at will.");
                return 0;
            }
        }

        if (u.uhunger <= 100 || ACURR(A_STR) < 6) {
            pline("You lack the strength %s.",
                  castit ? "for a teleport spell" : "to teleport");
            return 1;
        }

        energy = objects[SPE_TELEPORT_AWAY].oc_level * 7 / 2 - 2;
        if (u.uen <= energy) {
            pline("You lack the energy %s.",
                  castit ? "for a teleport spell" : "to teleport");
            return 1;
        }

        if (check_capacity("Your concentration falters from carrying so much."))
            return 1;

        if (castit) {
            exercise(A_WIS, TRUE);
            if (spelleffects(sp_no, TRUE, arg))
                return 1;
            else
                return 0;
        } else
            u.uen -= energy;
    }

    if (trap && trap->once) {
        if (next_to_u())
            vault_tele();
        else
            pline("You shudder for a moment.");
    } else if (!tele_impl(FALSE, TRUE))
        return 0;

    next_to_u();

    if (!trap)
        morehungry(100);
    return 1;
}