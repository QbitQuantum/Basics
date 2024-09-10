Object* ObjectFactory::create_object(const char *name,
                                     MediaDB *media,
                                     const char *type,
                                     int x, int y,
                                     int w, int h,
                                     Object::Direction dir,
                                     const Tmx::PropertySet &prop)
{
    Object *object = 0;

    if (strcmp(type, "Player") == 0) {
        TiXmlDocument doc(name);
        if (doc.LoadFile()) {
            search_nodes(&doc);
        }

        if (strcmp(priv_object_type, "knight") == 0) {
            object = new Knight(name, media, x, y, dir);
        }
        else if (strcmp(priv_object_type, "dragon") == 0) {
            object = new Dragon(name, media, x, y, dir);
        }
        else {
            object = new Player(name, media, x, y, dir);
        }
    }
    else if (strcmp(type, "Collectable") == 0) {
        TiXmlDocument doc(name);
        if (doc.LoadFile()) {
            search_nodes(&doc);
        }

        if (strcmp(priv_object_type, "coin") == 0) {
            object = new Coin(name, media, x, y);
        }
    }
    else if (strcmp(type, "Item") == 0) {
        TiXmlDocument doc(name);
        if (doc.LoadFile()) {
            search_nodes(&doc);
        }

        if (strcmp(priv_object_type, "key") == 0) {
            object = new Key(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "arm") == 0) {
            object = new Arm(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "shield") == 0) {
            object = new Shield(name, media, x, y);
        }
        else if (strcmp(priv_object_type, "armour") == 0) {
            object = new Armour(name, media, x, y);
        }
    }
    else if (strcmp(type, "Walker") == 0) {
        object = new Walker(name, media, x, y, dir);
    }
    else if (strcmp(type, "Crawler") == 0) {
        object = new Crawler(name, media, x, y, dir);
    }
    else if (strcmp(type, "Erupter") == 0) {
        object = new Erupter(name, media, x, y, dir);
    }
    else if (strcmp(type, "Guardian") == 0) {
        object = new Guardian(name, media, x, y, dir);
    }
    else if (strcmp(type, "LockFlyer") == 0) {
        object = new LockFlyer(name, media, x, y, dir);
    }
    else if (strcmp(type, "Dancer") == 0) {
        object = new Dancer(name, media, x, y, dir);
    }
    else if (strcmp(type, "Falling") == 0) {
        object = new Falling(name, media, x, y, dir);
    }
    else if (strcmp(type, "MekaDragon") == 0) {
        object = new MekaDragon(name, media, x, y, dir);
    }
    else if (strcmp(type, "Area") == 0) {
        std::string tn = prop.GetLiteralProperty(std::string("type"));
        object = new Area(name, media, tn.c_str(), x, y, w, h);
    }
    else if (strcmp(type, "Chest") == 0) {
        object = new Chest(name, media, x, y);
    }

    if (object) {
#ifdef TODO
        // Causes error now for areas
        if (!object->get_loaded()) {
            delete object;
            object = 0;
        }
#endif
        std::map<std::string, std::string> pmap = prop.GetList();
        for (std::map<std::string, std::string>::const_iterator it = pmap.begin();
             it != pmap.end();
             ++it) {
            std::string attr_name = it->first;
            if (attr_name != std::string("direction") &&
                attr_name != std::string("music")) {
                object->set_attribute(attr_name.c_str(),
                                      atoi(it->second.c_str()));
            }
        }
        object->initialize();
    }

    return object;
}