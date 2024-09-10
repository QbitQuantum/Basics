    void PrefabSystem::updateComponentInPrefab(const QString& path, const QString& component, const QVariantMap& values, bool updateInstances)
    {
        EntitySystem* es = entityManager()->system(component);
        Q_ASSERT(es);

        auto i = _prefabs.find(path);
        if(i == _prefabs.end())
        {
            return;
        }
        Prefab* prefab = i.value().data();
        QVariantMap current = prefab->components()[component].toMap();
        for(QString param : values.keys())
        {
            current[param] = values[param];
        }

        for(QString param : prefab->parameters())
        {
            current.remove(param);
        }
        prefab->_components[component] = current;


        if(updateInstances)
        {
            for(auto k = this->begin(); k != this->end(); ++k)
            {
                if(es->component(k->first))
                {
                    es->fromVariantMap(k->first, values);
                }
            }
        }
    }