void printCreature(DFHack::Context * DF, const DFHack::t_creature & creature, int index)
{


    DFHack::Translation *Tran = DF->getTranslation();
    DFHack::VersionInfo *mem = DF->getMemoryInfo();

    string type="(no type)";
    if (Materials->raceEx[creature.race].rawname[0])
    {
        type = toCaps(Materials->raceEx[creature.race].rawname);
    }

    string name="(no name)";
    if(creature.name.nickname[0])
    {
        name = creature.name.nickname;
    }
    else
    {
        if(creature.name.first_name[0])
        {
            name = toCaps(creature.name.first_name);

            string transName = Tran->TranslateName(creature.name,false);
            if(!transName.empty())
            {
                name += " " + toCaps(transName);
            }
        }
    }

    string profession="";
    try {
        profession = mem->getProfession(creature.profession);
    }
    catch (exception& e)
    {
        cout << "Error retrieving creature profession: " << e.what() << endl;
    }
    if(creature.custom_profession[0])
    {
        profession = creature.custom_profession;
    }


    string job="No Job";
    if(creature.current_job.active)
    {
        job=mem->getJob(creature.current_job.jobId);
        int p=job.size();
        while (p>0 && (job[p]==' ' || job[p]=='\t'))
            p--;
        if (p <= 1)
        {
            stringstream ss;
            ss << creature.current_job.jobId;
            job = ss.str();
        }
    }

    if (showfirstlineonly)
    {
        printf("%3d", index);
        printf(" %-17s", type.c_str());
        printf(" %-32s", name.c_str());
        printf(" %-16s", toCaps(profession).c_str());
        printf(" %-30s", job.c_str());
        printf(" %5d", creature.happiness);
        if (showdead)
        {
            printf(" %-5s", creature.flags1.bits.dead ? "Dead" : "Alive");
        }

        printf("\n");

        return;
    }
    else
    {
        printf("ID: %d", index);
        printf(", %s", type.c_str());
        printf(", %s", name.c_str());
        printf(", %s", toCaps(profession).c_str());
        printf(", Job: %s", job.c_str());
        printf(", Happiness: %d", creature.happiness);
        printf("\n");
    }

    if((creature.mood != NO_MOOD) && (creature.mood<=MAX_MOOD))
    {
        cout << "Creature is in a strange mood (mood=" << creature.mood << "), skill: " << mem->getSkill(creature.mood_skill) << endl;
        vector<DFHack::t_material> mymat;
        if(Creatures->ReadJob(&creature, mymat))
        {
            for(unsigned int i = 0; i < mymat.size(); i++)
            {
                printf("\t%s(%d)\t%d %d %d - %.8x\n", Materials->getDescription(mymat[i]).c_str(), mymat[i].itemType, mymat[i].subType, mymat[i].subIndex, mymat[i].index, mymat[i].flags);
            }
        }
    }

    if(creature.has_default_soul)
    {
        // Print out skills
        int skillid;
        int skillrating;
        int skillexperience;
        string skillname;

        cout << setiosflags(ios::left);

        for(unsigned int i = 0; i < creature.defaultSoul.numSkills; i++)
        {
            skillid = creature.defaultSoul.skills[i].id;
            bool is_social = is_in(skillid, social_skills, sizeof(social_skills)/sizeof(social_skills[0]));
            if (!is_social || (is_social && showsocial))
            {
                skillrating = creature.defaultSoul.skills[i].rating;
                skillexperience = creature.defaultSoul.skills[i].experience;
                try
                {
                    skillname = mem->getSkill(skillid);
                }
                catch(DFHack::Error::AllMemdef &e)
                {
                    skillname = "Unknown skill";
                    cout << e.what() << endl;
                }
                if (skillrating > 0 || skillexperience > 0)
                {
                    cout << "(Skill " << int(skillid) << ") " << setw(16) << skillname << ": "
                         << skillrating << "/" << skillexperience << endl;
                }
            }
        }

        for(unsigned int i = 0; i < NUM_CREATURE_LABORS; i++)
        {
            if(!creature.labors[i])
                continue;
            string laborname;
            try
            {
                laborname = mem->getLabor(i);
            }
            catch(exception &e)
            {
                laborname = "(Undefined)";
            }
            bool is_labor = is_in(i, hauler_labors, sizeof(hauler_labors)/sizeof(hauler_labors[0]));
            if (!is_labor || (is_labor && showhauler))
                cout << "(Labor " << i << ") " << setw(16) << laborname << endl;
        }
    }
    if (showallflags)
    {
        DFHack::t_creaturflags1 f1 = creature.flags1;
        DFHack::t_creaturflags2 f2 = creature.flags2;

        if(f1.bits.had_mood) {
            cout<<toCaps("Flag: had_mood") << endl;
        }
        if(f1.bits.marauder) {
            cout<<toCaps("Flag: marauder") << endl;
        }
        if(f1.bits.drowning) {
            cout<<toCaps("Flag: drowning") << endl;
        }
        if(f1.bits.merchant) {
            cout<<toCaps("Flag: merchant") << endl;
        }
        if(f1.bits.forest) {
            cout<<toCaps("Flag: forest") << endl;
        }
        if(f1.bits.left) {
            cout<<toCaps("Flag: left") << endl;
        }
        if(f1.bits.rider) {
            cout<<toCaps("Flag: rider") << endl;
        }
        if(f1.bits.incoming) {
            cout<<toCaps("Flag: incoming") << endl;
        }
        if(f1.bits.diplomat) {
            cout<<toCaps("Flag: diplomat") << endl;
        }
        if(f1.bits.zombie) {
            cout<<toCaps("Flag: zombie") << endl;
        }
        if(f1.bits.skeleton) {
            cout<<toCaps("Flag: skeleton") << endl;
        }
        if(f1.bits.can_swap) {
            cout<<toCaps("Flag: can_swap") << endl;
        }
        if(f1.bits.on_ground) {
            cout<<toCaps("Flag: on_ground") << endl;
        }
        if(f1.bits.projectile) {
            cout<<toCaps("Flag: projectile") << endl;
        }
        if(f1.bits.active_invader) {
            cout<<toCaps("Flag: active_invader") << endl;
        }
        if(f1.bits.hidden_in_ambush) {
            cout<<toCaps("Flag: hidden_in_ambush") << endl;
        }
        if(f1.bits.invader_origin) {
            cout<<toCaps("Flag: invader_origin") << endl;
        }
        if(f1.bits.coward) {
            cout<<toCaps("Flag: coward") << endl;
        }
        if(f1.bits.hidden_ambusher) {
            cout<<toCaps("Flag: hidden_ambusher") << endl;
        }
        if(f1.bits.invades) {
            cout<<toCaps("Flag: invades") << endl;
        }
        if(f1.bits.check_flows) {
            cout<<toCaps("Flag: check_flows") << endl;
        }
        if(f1.bits.ridden) {
            cout<<toCaps("Flag: ridden") << endl;
        }
        if(f1.bits.caged) {
            cout<<toCaps("Flag: caged") << endl;
        }
        if(f1.bits.tame) {
            cout<<toCaps("Flag: tame") << endl;
        }
        if(f1.bits.chained) {
            cout<<toCaps("Flag: chained") << endl;
        }
        if(f1.bits.royal_guard) {
            cout<<toCaps("Flag: royal_guard") << endl;
        }
        if(f1.bits.fortress_guard) {
            cout<<toCaps("Flag: fortress_guard") << endl;
        }
        if(f1.bits.suppress_wield) {
            cout<<toCaps("Flag: suppress_wield") << endl;
        }
        if(f1.bits.important_historical_figure) {
            cout<<toCaps("Flag: important_historical_figure") << endl;
        }

        if(f2.bits.swimming) {
            cout<<toCaps("Flag: swimming") << endl;
        }
        if(f2.bits.sparring) {
            cout<<toCaps("Flag: sparring") << endl;
        }
        if(f2.bits.no_notify) {
            cout<<toCaps("Flag: no_notify") << endl;
        }
        if(f2.bits.unused) {
            cout<<toCaps("Flag: unused") << endl;
        }
        if(f2.bits.calculated_nerves) {
            cout<<toCaps("Flag: calculated_nerves") << endl;
        }
        if(f2.bits.calculated_bodyparts) {
            cout<<toCaps("Flag: calculated_bodyparts") << endl;
        }
        if(f2.bits.important_historical_figure) {
            cout<<toCaps("Flag: important_historical_figure") << endl;
        }
        if(f2.bits.killed) {
            cout<<toCaps("Flag: killed") << endl;
        }
        if(f2.bits.cleanup_1) {
            cout<<toCaps("Flag: cleanup_1") << endl;
        }
        if(f2.bits.cleanup_2) {
            cout<<toCaps("Flag: cleanup_2") << endl;
        }
        if(f2.bits.cleanup_3) {
            cout<<toCaps("Flag: cleanup_3") << endl;
        }
        if(f2.bits.for_trade) {
            cout<<toCaps("Flag: for_trade") << endl;
        }
        if(f2.bits.trade_resolved) {
            cout<<toCaps("Flag: trade_resolved") << endl;
        }
        if(f2.bits.has_breaks) {
            cout<<toCaps("Flag: has_breaks") << endl;
        }
        if(f2.bits.gutted) {
            cout<<toCaps("Flag: gutted") << endl;
        }
        if(f2.bits.circulatory_spray) {
            cout<<toCaps("Flag: circulatory_spray") << endl;
        }
        if(f2.bits.locked_in_for_trading) {
            cout<<toCaps("Flag: locked_in_for_trading") << endl;
        }
        if(f2.bits.slaughter) {
            cout<<toCaps("Flag: slaughter") << endl;
        }
        if(f2.bits.underworld) {
            cout<<toCaps("Flag: underworld") << endl;
        }
        if(f2.bits.resident) {
            cout<<toCaps("Flag: resident") << endl;
        }
        if(f2.bits.cleanup_4) {
            cout<<toCaps("Flag: cleanup_4") << endl;
        }
        if(f2.bits.calculated_insulation) {
            cout<<toCaps("Flag: calculated_insulation") << endl;
        }
        if(f2.bits.visitor_uninvited) {
            cout<<toCaps("Flag: visitor_uninvited") << endl;
        }
        if(f2.bits.visitor) {
            cout<<toCaps("Flag: visitor") << endl;
        }
        if(f2.bits.calculated_inventory) {
            cout<<toCaps("Flag: calculated_inventory") << endl;
        }
        if(f2.bits.vision_good) {
            cout<<toCaps("Flag: vision_good") << endl;
        }
        if(f2.bits.vision_damaged) {
            cout<<toCaps("Flag: vision_damaged") << endl;
        }
        if(f2.bits.vision_missing) {
            cout<<toCaps("Flag: vision_missing") << endl;
        }
        if(f2.bits.breathing_good) {
            cout<<toCaps("Flag: breathing_good") << endl;
        }
        if(f2.bits.breathing_problem) {
            cout<<toCaps("Flag: breathing_problem") << endl;
        }
        if(f2.bits.roaming_wilderness_population_source) {
            cout<<toCaps("Flag: roaming_wilderness_population_source") << endl;
        }
        if(f2.bits.roaming_wilderness_population_source_not_a_map_feature) {
            cout<<toCaps("Flag: roaming_wilderness_population_source_not_a_map_feature") << endl;
        }
    }
    else
    {
        /* FLAGS 1 */
        if(creature.flags1.bits.dead)       	{
            cout << "Flag: Dead" << endl;
        }
        if(creature.flags1.bits.on_ground)  	{
            cout << "Flag: On the ground" << endl;
        }
        if(creature.flags1.bits.tame)       	{
            cout << "Flag: Tame" << endl;
        }
        if(creature.flags1.bits.royal_guard)	{
            cout << "Flag: Royal guard" << endl;
        }
        if(creature.flags1.bits.fortress_guard)	{
            cout << "Flag: Fortress guard" << endl;
        }

        /* FLAGS 2 */
        if(creature.flags2.bits.killed)     {
            cout << "Flag: Killed by kill function" << endl;
        }
        if(creature.flags2.bits.resident)   {
            cout << "Flag: Resident" << endl;
        }
        if(creature.flags2.bits.gutted)     {
            cout << "Flag: Gutted" << endl;
        }
        if(creature.flags2.bits.slaughter)  {
            cout << "Flag: Marked for slaughter" << endl;
        }
        if(creature.flags2.bits.underworld) {
            cout << "Flag: From the underworld" << endl;
        }

        if(creature.flags1.bits.had_mood && (creature.mood == -1 || creature.mood == 8 ) )
        {
            string artifact_name = Tran->TranslateName(creature.artifact_name,false);
            cout << "Artifact: " << artifact_name << endl;
        }
    }
    cout << endl;
}