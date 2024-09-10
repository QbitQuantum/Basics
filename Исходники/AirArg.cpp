void Arg::dump(PrintStream& out) const
{
    switch (m_kind) {
    case Invalid:
        out.print("<invalid>");
        return;
    case Tmp:
        out.print(tmp());
        return;
    case Imm:
        out.print("$", m_offset);
        return;
    case Imm64:
        out.printf("$0x%llx", static_cast<long long unsigned>(m_offset));
        return;
    case Addr:
        if (offset())
            out.print(offset());
        out.print("(", base(), ")");
        return;
    case Index:
        if (offset())
            out.print(offset());
        out.print("(", base(), ",", index());
        if (scale() != 1)
            out.print(",", scale());
        out.print(")");
        return;
    case Stack:
        if (offset())
            out.print(offset());
        out.print("(", pointerDump(stackSlot()), ")");
        return;
    case CallArg:
        if (offset())
            out.print(offset());
        out.print("(callArg)");
        return;
    case RelCond:
        out.print(asRelationalCondition());
        return;
    case ResCond:
        out.print(asResultCondition());
        return;
    case DoubleCond:
        out.print(asDoubleCondition());
        return;
    case Special:
        out.print(pointerDump(special()));
        return;
    }

    RELEASE_ASSERT_NOT_REACHED();
}