bool RARExecuteProgram(RARVirtualMachine *vm, RARProgram *prog)
{
    RAROpcode *opcode = prog->opcodes;
    uint32_t flags = 0;
    uint32_t op1, op2, carry, i;
    uint32_t counter = 0;

    if (!RARIsProgramTerminated(prog))
        return false;

    while ((uint32_t)(opcode - prog->opcodes) < prog->length && counter++ < RARRuntimeMaxInstructions) {
        switch (opcode->instruction) {
        case RARMovInstruction:
            SetOperand1(GetOperand2());
            NextInstruction();

        case RARCmpInstruction:
            op1 = GetOperand1();
            SetFlagsWithCarry(op1 - GetOperand2(), result > op1);
            NextInstruction();

        case RARAddInstruction:
            op1 = GetOperand1();
            if (opcode->bytemode)
                SetOperand1AndByteFlagsWithCarry((op1 + GetOperand2()) & 0xFF, result < op1);
            else
                SetOperand1AndFlagsWithCarry(op1 + GetOperand2(), result < op1);
            NextInstruction();

        case RARSubInstruction:
            op1 = GetOperand1();
#if 0 /* apparently not correctly implemented in the RAR VM */
            if (opcode->bytemode)
                SetOperand1AndByteFlagsWithCarry((op1 - GetOperand2()) & 0xFF, result > op1);
            else
#endif
            SetOperand1AndFlagsWithCarry(op1 - GetOperand2(), result > op1);
            NextInstruction();

        case RARJzInstruction:
            if ((flags & ZeroFlag))
                Jump(GetOperand1());
            NextInstruction();

        case RARJnzInstruction:
            if (!(flags & ZeroFlag))
                Jump(GetOperand1());
            NextInstruction();

        case RARIncInstruction:
            if (opcode->bytemode)
                SetOperand1AndFlags((GetOperand1() + 1) & 0xFF);
            else
                SetOperand1AndFlags(GetOperand1() + 1);
            NextInstruction();

        case RARDecInstruction:
            if (opcode->bytemode)
                SetOperand1AndFlags((GetOperand1() - 1) & 0xFF);
            else
                SetOperand1AndFlags(GetOperand1() - 1);
            NextInstruction();

        case RARJmpInstruction:
            Jump(GetOperand1());

        case RARXorInstruction:
            SetOperand1AndFlags(GetOperand1() ^ GetOperand2());
            NextInstruction();

        case RARAndInstruction:
            SetOperand1AndFlags(GetOperand1() & GetOperand2());
            NextInstruction();

        case RAROrInstruction:
            SetOperand1AndFlags(GetOperand1() | GetOperand2());
            NextInstruction();

        case RARTestInstruction:
            SetFlags(GetOperand1() & GetOperand2());
            NextInstruction();

        case RARJsInstruction:
            if ((flags & SignFlag))
                Jump(GetOperand1());
            NextInstruction();

        case RARJnsInstruction:
            if (!(flags & SignFlag))
                Jump(GetOperand1());
            NextInstruction();

        case RARJbInstruction:
            if ((flags & CarryFlag))
                Jump(GetOperand1());
            NextInstruction();

        case RARJbeInstruction:
            if ((flags & (CarryFlag | ZeroFlag)))
                Jump(GetOperand1());
            NextInstruction();

        case RARJaInstruction:
            if (!(flags & (CarryFlag | ZeroFlag)))
                Jump(GetOperand1());
            NextInstruction();

        case RARJaeInstruction:
            if (!(flags & CarryFlag))
                Jump(GetOperand1());
            NextInstruction();

        case RARPushInstruction:
            vm->registers[7] -= 4;
            RARVirtualMachineWrite32(vm, vm->registers[7], GetOperand1());
            NextInstruction();

        case RARPopInstruction:
            SetOperand1(RARVirtualMachineRead32(vm, vm->registers[7]));
            vm->registers[7] += 4;
            NextInstruction();

        case RARCallInstruction:
            vm->registers[7] -= 4;
            RARVirtualMachineWrite32(vm, vm->registers[7], (uint32_t)(opcode - prog->opcodes + 1));
            Jump(GetOperand1());

        case RARRetInstruction:
            if (vm->registers[7] >= RARProgramMemorySize)
                return true;
            i = RARVirtualMachineRead32(vm, vm->registers[7]);
            vm->registers[7] += 4;
            Jump(i);

        case RARNotInstruction:
            SetOperand1(~GetOperand1());
            NextInstruction();

        case RARShlInstruction:
            op1 = GetOperand1();
            op2 = GetOperand2();
            SetOperand1AndFlagsWithCarry(op1 << op2, ((op1 << (op2 - 1)) & 0x80000000) != 0);
            NextInstruction();

        case RARShrInstruction:
            op1 = GetOperand1();
            op2 = GetOperand2();
            SetOperand1AndFlagsWithCarry(op1 >> op2, ((op1 >> (op2 - 1)) & 1) != 0);
            NextInstruction();

        case RARSarInstruction:
            op1 = GetOperand1();
            op2 = GetOperand2();
            SetOperand1AndFlagsWithCarry(((int32_t)op1) >> op2, ((op1 >> (op2 - 1)) & 1) != 0);
            NextInstruction();

        case RARNegInstruction:
            SetOperand1AndFlagsWithCarry(-(int32_t)GetOperand1(), result != 0);
            NextInstruction();

        case RARPushaInstruction:
            vm->registers[7] -= 32;
            for (i = 0; i < 8; i++)
                RARVirtualMachineWrite32(vm, vm->registers[7] + (7 - i) * 4, vm->registers[i]);
            NextInstruction();

        case RARPopaInstruction:
            for (i = 0; i < 8; i++)
                vm->registers[i] = RARVirtualMachineRead32(vm, vm->registers[7] + (7 - i) * 4);
            vm->registers[7] += 32;
            NextInstruction();

        case RARPushfInstruction:
            vm->registers[7] -= 4;
            RARVirtualMachineWrite32(vm, vm->registers[7], flags);
            NextInstruction();

        case RARPopfInstruction:
            flags = RARVirtualMachineRead32(vm, vm->registers[7]);
            vm->registers[7] += 4;
            NextInstruction();

        case RARMovzxInstruction:
            SetOperand1(GetOperand2());
            NextInstruction();

        case RARMovsxInstruction:
            SetOperand1(SignExtend(GetOperand2()));
            NextInstruction();

        case RARXchgInstruction:
            op1 = GetOperand1();
            op2 = GetOperand2();
            SetOperand1(op2);
            SetOperand2(op1);
            NextInstruction();

        case RARMulInstruction:
            SetOperand1(GetOperand1() * GetOperand2());
            NextInstruction();

        case RARDivInstruction:
            op2 = GetOperand2();
            if (op2 != 0)
                SetOperand1(GetOperand1() / op2);
            NextInstruction();

        case RARAdcInstruction:
            op1 = GetOperand1();
            carry = (flags & CarryFlag);
            if (opcode->bytemode)
                SetOperand1AndFlagsWithCarry((op1 + GetOperand2() + carry) & 0xFF, result < op1 || (result == op1 && carry)); /* does not correctly set sign bit */
            else
                SetOperand1AndFlagsWithCarry(op1 + GetOperand2() + carry, result < op1 || (result == op1 && carry));
            NextInstruction();

        case RARSbbInstruction:
            op1 = GetOperand1();
            carry = (flags & CarryFlag);
            if (opcode->bytemode)
                SetOperand1AndFlagsWithCarry((op1 - GetOperand2() - carry) & 0xFF, result > op1 || (result == op1 && carry)); /* does not correctly set sign bit */
            else
                SetOperand1AndFlagsWithCarry(op1 - GetOperand2() - carry, result > op1 || (result == op1 && carry));
            NextInstruction();

        case RARPrintInstruction:
            /* TODO: ??? */
            NextInstruction();
        }
    }

    return false;
}