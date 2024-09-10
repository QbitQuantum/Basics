void SkillRecv::processSkillCoolDownList(Net::MessageIn &msg)
{
    int packetLen;
    if (msg.getVersion() >= 20120604)
        packetLen = 10;
    else
        packetLen = 6;
    const int count = (msg.readInt16("len") - 4) / packetLen;
    for (int f = 0; f < count; f ++)
    {
        const int skillId = msg.readInt16("skill id");
        if (msg.getVersion() >= 20120604)
            msg.readInt32("total");
        const int duration = msg.readInt32("duration");
        if (skillDialog)
        {
            skillDialog->setSkillDuration(SkillOwner::Player,
                skillId, duration);
        }
    }
}