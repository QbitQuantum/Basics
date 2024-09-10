void ReviewDialog::setSkillValue(ESM::Skill::SkillEnum skillId, const MWMechanics::Stat<float>& value)
{
    mSkillValues[skillId] = value;
    MyGUI::TextBox* widget = mSkillWidgetMap[skillId];
    if (widget)
    {
        float modified = value.getModified(), base = value.getBase();
        std::string text = boost::lexical_cast<std::string>(std::floor(modified));
        std::string state = "normal";
        if (modified > base)
            state = "increased";
        else if (modified < base)
            state = "decreased";

        widget->setCaption(text);
        widget->_setWidgetState(state);
    }

}