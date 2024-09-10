bool RedoBBBuilder::isCurrentTopLoop(Instruction& I) const
{
    return isCurrentTopLoop(I.getParent());
}