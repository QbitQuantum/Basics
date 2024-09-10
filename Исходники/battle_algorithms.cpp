void Game_Battle::UseSkill(Battle::Ally& ally, const RPG::Skill& skill) {

	int sp = ally.GetActor()->CalculateSkillCost(skill.ID);
	if (sp > ally.GetActor()->GetSp()) // not enough SP
		return;

	switch (skill.type) {
		case RPG::Skill::Type_teleport:
			// FIXME: teleport skill
			break;
		case RPG::Skill::Type_escape:
			Escape();
			break;
		case RPG::Skill::Type_switch:
			if (!skill.occasion_battle)
				return;
			Game_Switches[skill.switch_id] = true;
			break;
		case RPG::Skill::Type_normal:
		default:
			switch (skill.scope) {
				case RPG::Skill::Scope_enemy:
					UseSkillEnemy(ally, skill, Game_Battle::GetTargetEnemy());
					return;
				case RPG::Skill::Scope_enemies:
					for (std::vector<Battle::Enemy>::iterator it = Game_Battle::enemies.begin(); it != Game_Battle::enemies.end(); it++)
						UseSkillEnemy(ally, skill, *it);
					break;
				case RPG::Skill::Scope_self:
					UseSkillAlly(ally, skill, ally);
					break;
				case RPG::Skill::Scope_ally:
					UseSkillAlly(ally, skill, Game_Battle::GetTargetAlly());
					return;
				case RPG::Skill::Scope_party:
					for (std::vector<Battle::Ally>::iterator it = Game_Battle::allies.begin(); it != Game_Battle::allies.end(); it++)
						UseSkillAlly(ally, skill, *it);
					break;
			}
			break;
	}

	if (skill.type != RPG::Skill::Type_normal)
		Game_System::SePlay(skill.sound_effect);

	ally.GetActor()->SetSp(ally.GetActor()->GetSp() - sp);
}