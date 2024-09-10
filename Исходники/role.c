/* Record the breaking of a roleplay-conduct. */
void violated(int cdt)
{
	switch (cdt) {
	case CONDUCT_PACIFISM:
	    u.uconduct.killer++;
	    if (u.roleplay.pacifist) {
		pline("你感到狂暴！");
		if (yn("你确定要退出吗？") == 'y') {
		    killer_format = NO_KILLER_PREFIX;
		    killer = "在一阵狂暴之后退出";
		    done(QUIT);
		}
		if (u.uconduct.killer >= 10) u.roleplay.pacifist = FALSE;
	    }
	    break;

	case CONDUCT_NUDISM:
	    u.uconduct.armoruses++;
	    if (u.roleplay.nudist) {
		pline("你意识到你光着身子。");
		makemon(&mons[PM_COBRA], level, u.ux, u.uy, NO_MM_FLAGS);
		mksobj_at(APPLE, level, u.ux, u.uy, FALSE, FALSE);
		u.roleplay.nudist = FALSE;
	    }
	    break;

	case CONDUCT_BLINDFOLDED:
	    u.uconduct.unblinded++;
	    if (u.roleplay.blindfolded) {
		pline("禅之精神，离开你的身体。");
		makemon(mkclass(&level->z, S_ZOMBIE, 0),
			level, u.ux, u.uy, NO_MM_FLAGS);	/* Z */
		makemon(mkclass(&level->z, S_EYE, 0),
			level, u.ux, u.uy, NO_MM_FLAGS);	/* e */
		makemon(mkclass(&level->z, S_NYMPH, 0),
			level, u.ux, u.uy, NO_MM_FLAGS);	/* n */
		u.roleplay.blindfolded = FALSE;
	    }
	    break;

	case CONDUCT_VEGETARIAN:	/* replaces violated_vegetarian() */
	    if (u.roleplay.vegetarian)
		pline("你感到内疚。");
	    if (Role_if(PM_MONK))
		adjalign(-1);
	    u.uconduct.unvegetarian++;
	    u.uconduct.unvegan++;
	    u.uconduct.food++;
	    if (u.uconduct.unvegetarian >= 30) u.roleplay.vegetarian = FALSE;
	    if (u.uconduct.unvegan >= 20) u.roleplay.vegan = FALSE;
	    if (u.uconduct.food >= 10) u.roleplay.ascet = FALSE;
	    break;

	case CONDUCT_VEGAN:
	    if (u.roleplay.vegan)
		pline("你感到有点内疚。");
	    u.uconduct.unvegan++;
	    u.uconduct.food++;
	    if (u.uconduct.unvegan >= 20) u.roleplay.vegan = FALSE;
	    if (u.uconduct.food >= 10) u.roleplay.ascet = FALSE;
	    break;

	case CONDUCT_FOODLESS:
	    if (u.roleplay.ascet)
		pline("你略微感到内疚。");
	    u.uconduct.food++;
	    if (u.uconduct.food >= 10) u.roleplay.ascet = FALSE;
	    break;

	case CONDUCT_ILLITERACY:
	    u.uconduct.literate++;
	    if (u.roleplay.illiterate) {
		/* should be impossible */
		pline("Literatally literature for literate illiterates!");
		exercise(A_WIS, TRUE);
	    }
	    break;

	case CONDUCT_THIEVERY:
	    u.uconduct.robbed++;
	    if (Role_if(PM_ROGUE))
		pline("你感觉自己像一个强盗。");
	    break;

	default:
	    impossible("violated: unknown conduct");
	}
}