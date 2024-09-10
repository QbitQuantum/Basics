DFhackCExport command_result df_cleanowned (Core * c, vector <string> & parameters)
{
    bool dump_scattered = false;
    bool confiscate_all = false;
    bool dry_run = false;
    int wear_dump_level = 65536;

    for(std::size_t i = 0; i < parameters.size(); i++)
    {
        string & param = parameters[i];
        if(param == "dryrun")
            dry_run = true;
        else if(param == "scattered")
            dump_scattered = true;
        else if(param == "all")
            confiscate_all = true;
        else if(param == "x")
            wear_dump_level = 1;
        else if(param == "X")
            wear_dump_level = 2;
        else if(param == "?" || param == "help")
        {
            c->con.print("This tool lets you confiscate and dump all the garbage\n"
                         "dwarves ultimately accumulate.\n"
                         "By default, only rotten and dropped food is confiscated.\n"
                         "Options:\n"
                         "  dryrun    - don't actually do anything, just print what would be done.\n"
                         "  scattered - confiscate owned items on the ground\n"
                         "  all       - confiscate everything\n"
                         "  x         - confiscate & dump 'x' and worse damaged items\n"
                         "  X         - confiscate & dump 'X' and worse damaged items\n"
                         "  ?         - this help\n"
                         "Example:\n"
                         "  confiscate scattered X\n"
                         "  This will confiscate rotten and dropped food, garbage on the floors\n"
                         "  and any worn items wit 'X' damage and above.\n"
            );
            return CR_OK;
        }
        else
        {
            c->con.printerr("Parameter '%s' is not valid. See 'cleanowned help'.\n",param.c_str());
            return CR_FAILURE;
        }
    }
    c->Suspend();
    DFHack::Materials *Materials = c->getMaterials();
    DFHack::Items *Items = c->getItems();
    DFHack::Units *Creatures = c->getUnits();
    DFHack::Translation *Tran = c->getTranslation();

    uint32_t num_creatures;
    bool ok = true;
    ok &= Materials->ReadAllMaterials();
    ok &= Creatures->Start(num_creatures);
    ok &= Tran->Start();

    vector<df_item *> p_items;
    ok &= Items->readItemVector(p_items);
    if(!ok)
    {
        c->con.printerr("Can't continue due to offset errors.\n");
        c->Resume();
        return CR_FAILURE;
    }
    c->con.print("Found total %d items.\n", p_items.size());

    for (std::size_t i=0; i < p_items.size(); i++)
    {
        df_item * item = p_items[i];
        bool confiscate = false;
        bool dump = false;

        if (!item->flags.owned)
        {
            int32_t owner = Items->getItemOwnerID(item);
            if (owner >= 0)
            {
                c->con.print("Fixing a misflagged item: \t");
                confiscate = true;
            }
            else
            {
                continue;
            }
        }

        std::string name = Items->getItemClass(item);

        if (item->flags.rotten)
        {
            c->con.print("Confiscating a rotten item: \t");
            confiscate = true;
        }
        else if (item->flags.on_ground)
        {
            int32_t type = item->getType();
            if(type == Items::MEAT ||
               type == Items::FISH ||
               type == Items::VERMIN ||
               type == Items::PET ||
               type == Items::PLANT ||
               type == Items::CHEESE ||
               type == Items::FOOD
            )
            {
                confiscate = true;
                if(dump_scattered)
                {
                    c->con.print("Dumping a dropped item: \t");
                    dump = true;
                }
                else
                {
                    c->con.print("Confiscating a dropped item: \t");
                }
            }
            else if(dump_scattered)
            {
                c->con.print("Confiscating and dumping litter: \t");
                confiscate = true;
                dump = true;
            }
        }
        else if (item->getWear() >= wear_dump_level)
        {
            c->con.print("Confiscating and dumping a worn item: \t");
            confiscate = true;
            dump = true;
        }
        else if (confiscate_all)
        {
            c->con.print("Confiscating: \t");
            confiscate = true;
        }

        if (confiscate)
        {
            std::string description;
            item->getItemDescription(&description, 0);
            c->con.print(
                "0x%x %s (wear %d)",
                item,
                description.c_str(),
                item->getWear()
            );

            int32_t owner = Items->getItemOwnerID(item);
            int32_t owner_index = Creatures->FindIndexById(owner);
            std::string info;

            if (owner_index >= 0)
            {
                DFHack::df_unit * temp = Creatures->GetCreature(owner_index);
                info = temp->name.first_name;
                if (!temp->name.nick_name.empty())
                    info += std::string(" '") + temp->name.nick_name + "'";
                info += " ";
                info += Tran->TranslateName(&temp->name,false);
                c->con.print(", owner %s", info.c_str());
            }

            if (!dry_run)
            {
                if (!Items->removeItemOwner(item, Creatures))
                    c->con.print("(unsuccessfully) ");
                if (dump)
                    item->flags.dump = 1;
            }
            c->con.print("\n");
        }
    }
    c->Resume();
    return CR_OK;
}