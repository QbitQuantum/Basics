void StackMaps::Constant::dump(PrintStream& out) const
{
    out.printf("0x%016llx", integer);
}