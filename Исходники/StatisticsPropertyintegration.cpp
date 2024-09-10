void StatisicsPropertyintegration::setup()
{
    m_char_type = new TypeNode("char_type");

    m_char_property = new StatisticsProperty;
    m_char_property->setFlags(flag_class);
    m_char_type->addProperty("char_prop", m_char_property);

    m_char1 = new Entity("1", 1);
    m_char1->setType(m_char_type);
    m_char_property->install(m_char1, "char_prop");
    m_char_property->apply(m_char1);

    m_char2 = new Entity("2", 2);
    m_char2->setType(m_char_type);
    m_char_property->install(m_char2, "char_prop");
    m_char_property->apply(m_char2);
}