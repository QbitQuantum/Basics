void Operator::Register(uint16_t opcode, bool (*o)(const Context &, uint16_t &index))
{
    if (Operators[opcode]._operator) {
        Operators[opcode].setOverload(o);
    } else {
        Operators[opcode] = Operator(o);
    }
}