void printCreature(DFHack::Context * DF, const DFHack::t_creature & creature)
{
    uint32_t dayoflife;
    cout << "address: " << hex <<  creature.origin << dec << ", creature race: " << creature.race << "/" << Materials->raceEx[creature.race].rawname 
                << "[" << Materials->raceEx[creature.race].tile_character
                << "," << Materials->raceEx[creature.race].tilecolor.fore
                << "," << Materials->raceEx[creature.race].tilecolor.back
                << "," << Materials->raceEx[creature.race].tilecolor.bright
                << "]"
                << ", position: " << creature.x << "x " << creature.y << "y "<< creature.z << "z" << endl;
        bool addendl = false;
        if(creature.name.first_name[0])
        {
            cout << "first name: " << creature.name.first_name;
            addendl = true;
        }
        if(creature.name.nickname[0])
        {
            cout << ", nick name: " << creature.name.nickname;
            addendl = true;
        }
        
        DFHack::Translation *Tran = DF->getTranslation();
        DFHack::VersionInfo *mem = DF->getMemoryInfo();
        
        string transName = Tran->TranslateName(creature.name,false);
        if(!transName.empty())
        {
            cout << ", trans name: " << transName;
            addendl=true;
        }
        
        transName = Tran->TranslateName(creature.name,true);
        if(!transName.empty())
        {
            cout << ", last name: " << transName;
            addendl=true;
        }

        if(creature.civ)
        {
            cout << ", civilization: " << creature.civ;
            addendl = true;
        }

        /*
        cout << ", likes: ";
        for(uint32_t i = 0;i<creature.numLikes; i++)
        {
            if(printLike(creature.likes[i],mat,itemTypes))
            {
                cout << ", ";
            }
        } 
        */  
        if(addendl)
        {
            cout << endl;
            addendl = false;
        }
        cout << ", profession: " << mem->getProfession(creature.profession) << "(" << (int) creature.profession << ")";
        
        if(creature.custom_profession[0])
        {
            cout << ", custom profession: " << creature.custom_profession;
        }
        /*
        if(creature.current_job.active)
        {
            cout << ", current job: " << mem->getJob(creature.current_job.jobId);
        }
        */
        cout << endl;
        dayoflife = creature.birth_year*12*28 + creature.birth_time/1200;
        cout << "Born on the year " << creature.birth_year << ", month " << (creature.birth_time/1200/28) << ", day " << ((creature.birth_time/1200) % 28 + 1) << ", " << dayoflife << " days lived." << endl;
        cout << "Appearance : ";
        for(unsigned int i = 0; i<creature.nbcolors ; i++)
        {
            cout << Materials->raceEx[creature.race].castes[creature.caste].ColorModifier[i].part << " ";
            uint32_t color = Materials->raceEx[creature.race].castes[creature.caste].ColorModifier[i].colorlist[creature.color[i]];
            if(color<Materials->color.size())
                cout << Materials->color[color].name << "[" 
                    << (unsigned int) (Materials->color[color].r*255) << ":"
                    << (unsigned int) (Materials->color[color].v*255) << ":"
                    << (unsigned int) (Materials->color[color].b*255) << "]";
            else
                cout << Materials->alldesc[color].id;
            if( Materials->raceEx[creature.race].castes[creature.caste].ColorModifier[i].startdate > 0 )
            {
                if( (Materials->raceEx[creature.race].castes[creature.caste].ColorModifier[i].startdate <= dayoflife) &&
                    (Materials->raceEx[creature.race].castes[creature.caste].ColorModifier[i].enddate > dayoflife) )
                    cout << "[active]";
                else
                    cout << "[inactive]";
            }
            cout << " - ";

        }
        cout << endl;
        cout << "happiness: "   << creature.happiness
             << ", strength: "  << creature.strength.level 
             << ", agility: "   << creature.agility.level
             << ", toughness: " << creature.toughness.level
             << ", endurance: " << creature.endurance.level
             << ", recuperation: " << creature.recuperation.level
             << ", disease resistance: " << creature.disease_resistance.level
             //<< ", money: " << creature.money
             << ", id: " << creature.id;
        /*
        if(creature.squad_leader_id != -1)
        {
            cout << ", squad_leader_id: " << creature.squad_leader_id;
        }
        if(creature.mood != -1){
            cout << ", mood: " << creature.mood << " ";
        }*/
        cout << ", sex: ";
        if(creature.sex == 0)
        {
            cout << "Female";
        }
        else
        {
            cout <<"Male";
        }
        cout << endl;

        if((creature.mood != -1) && (creature.mood<5))
        {
            cout << "mood: " << creature.mood << ", skill: " << mem->getSkill(creature.mood_skill) << endl;
            vector<DFHack::t_material> mymat;
            if(Creatures->ReadJob(&creature, mymat))
            {
                for(unsigned int i = 0; i < mymat.size(); i++)
                {
                    printf("\t%s(%d)\t%d %d %d - %.8x\n", Materials->getDescription(mymat[i]).c_str(), mymat[i].itemType, mymat[i].subType, mymat[i].subIndex, mymat[i].index, mymat[i].flags);
                }
            }
        }

        //std::vector<uint32_t> inventory;
        // FIXME: TOO BAD...
        /*
        if( Creatures->ReadInventoryPtr(creature.origin, inventory) )
        {
            DFHack::Items * Items = DF->getItems();
            printf("\tInventory:\n");
            for(unsigned int i = 0; i < inventory.size(); i++)
            {
                printf("\t\t%s\n", Items->getItemDescription(inventory[i], Materials).c_str());
            }
        }
        */

        /*
        if(creature.pregnancy_timer > 0)
            cout << "gives birth in " << creature.pregnancy_timer/1200 << " days. ";
        cout << "Blood: " << creature.blood_current << "/" << creature.blood_max << " bleeding: " << creature.bleed_rate;
        */
        cout << endl;

        if(creature.has_default_soul)
        {
            //skills
            cout << "Skills" << endl;
            for(unsigned int i = 0; i < creature.defaultSoul.numSkills;i++)
            {
                if(i > 0)
                {
                    cout << ", ";
                }
                cout << mem->getSkill(creature.defaultSoul.skills[i].id) << ": " << creature.defaultSoul.skills[i].rating;
            }
            cout << endl;
            cout << "Traits" << endl;
            for(uint32_t i = 0; i < 30;i++)
            {
                string trait = mem->getTrait (i, creature.defaultSoul.traits[i]);
                if(!trait.empty()) cout << trait << ", ";
            }
            cout << endl;
                    
            // labors
            cout << "Labors" << endl;
            for(unsigned int i = 0; i < NUM_CREATURE_LABORS;i++)
            {
                if(!creature.labors[i])
                    continue;
                string laborname;
                try
                {
                    laborname = mem->getLabor(i);
                }
                catch(exception &)
                {
                    break;
                }
                cout << laborname << ", ";
            }
            cout << endl;
        }
        /*
         * FLAGS 1
         */
        cout << "flags1: ";
        print_bits(creature.flags1.whole, cout);
        cout << endl;
        if(creature.flags1.bits.dead)
        {
            cout << "dead ";
        }
        if(creature.flags1.bits.on_ground)
        {
            cout << "on the ground, ";
        }
        if(creature.flags1.bits.skeleton)
        {
            cout << "skeletal ";
        }
        if(creature.flags1.bits.zombie)
        {
            cout << "zombie ";
        }
        if(creature.flags1.bits.tame)
        {
            cout << "tame ";
        }
        if(creature.flags1.bits.royal_guard)
        {
            cout << "royal_guard ";
        }
        if(creature.flags1.bits.fortress_guard)
        {
            cout << "fortress_guard ";
        }
        /*
        * FLAGS 2
        */
        cout << endl << "flags2: ";
        print_bits(creature.flags2.whole, cout);
        cout << endl;
        if(creature.flags2.bits.killed)
        {
            cout << "killed by kill function, ";
        }
        if(creature.flags2.bits.resident)
        {
            cout << "resident, ";
        }
        if(creature.flags2.bits.gutted)
        {
            cout << "gutted, ";
        }
        if(creature.flags2.bits.slaughter)
        {
            cout << "marked for slaughter, ";
        }
        if(creature.flags2.bits.underworld)
        {
            cout << "from the underworld, ";
        }
        cout << endl;
        
        if(creature.flags1.bits.had_mood && (creature.mood == -1 || creature.mood == 8 ) )
        {
            string artifact_name = Tran->TranslateName(creature.artifact_name,false);
            cout << "artifact: " << artifact_name << endl;
        }


    cout << endl;
}