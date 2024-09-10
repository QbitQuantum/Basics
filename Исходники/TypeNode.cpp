void TypeNode::addProperties(const MapType & attributes)
{
    MapType::const_iterator J = attributes.begin();
    MapType::const_iterator Jend = attributes.end();
    PropertyBase * p;
    for (; J != Jend; ++J) {
        p = PropertyManager::instance()->addProperty(J->first,
                                                     J->second.getType());
        assert(p != 0);
        p->set(J->second);
        p->setFlags(flag_class);
        m_defaults[J->first] = p;
    }
}