void SkillEditor::_LoadSkills()
{
    string path = string("dat/skills/");
    ReadScriptDescriptor script;
    script.OpenFile(path + "defense.lua", true);
    script.CloseFile();
    script.OpenFile(path + "support.lua", true);
    script.CloseFile();
    vector<GlobalSkill *> skills;
    if(script.OpenFile(path + "attack.lua", true) != false)
        _LoadSkills(script, skills, GLOBAL_SKILL_ATTACK);
    // Now clean up the skills script (due to the way we're storing the scripts in lua, they're all actually in one big table in lua
    // regardless of the file split on disk
    vector<GlobalSkill *>::iterator i = skills.begin();
    for(; i != skills.end(); ++i) {
        if((*i)->GetType() == GLOBAL_SKILL_ATTACK)
            _attack_skills.push_back(*i);
        else if((*i)->GetType() == GLOBAL_SKILL_DEFEND)
            _defense_skills.push_back(*i);
        else if((*i)->GetType() == GLOBAL_SKILL_SUPPORT)
            _support_skills.push_back(*i);
    }
    if(_attack_skills.size() > 0)
        _current_skill_index[GLOBAL_SKILL_ATTACK] = 0;
    if(_defense_skills.size() > 0)
        _current_skill_index[GLOBAL_SKILL_DEFEND] = 0;
    if(_support_skills.size() > 0)
        _current_skill_index[GLOBAL_SKILL_SUPPORT] = 0;

} // _LoadSkills()