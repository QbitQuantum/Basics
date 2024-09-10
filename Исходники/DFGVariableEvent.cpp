void VariableEvent::dump(PrintStream& out) const
{
    switch (kind()) {
    case Reset:
        out.printf("Reset");
        break;
    case BirthToFill:
        dumpFillInfo("BirthToFill", out);
        break;
    case BirthToSpill:
        dumpSpillInfo("BirthToSpill", out);
        break;
    case Fill:
        dumpFillInfo("Fill", out);
        break;
    case Spill:
        dumpSpillInfo("Spill", out);
        break;
    case Death:
        out.print("Death(", id(), ")");
        break;
    case MovHintEvent:
        out.print("MovHint(", id(), ", ", bytecodeRegister(), ")");
        break;
    case SetLocalEvent:
        out.print(
            "SetLocal(machine:", machineRegister(), " -> bytecode:", bytecodeRegister(),
            ", ", dataFormatToString(dataFormat()), ")");
        break;
    default:
        RELEASE_ASSERT_NOT_REACHED();
        break;
    }
}