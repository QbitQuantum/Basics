int carryOutInstruction(struct Processor *processor) {
  uint32_t instruction = getInstructionAtPC(processor);
  uint8_t opcode = getOpcode(instruction);
  uint32_t backupPC = processor->pc;
  int32_t temp;
  div_t division;

  switch (opcode)  {
    case HALT : return 0;
    case ADD  : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) + 
                  getRegisterValue(processor, getR3(instruction));
                break;
                
    case ADDI : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) + 
                  getImmediateValue(instruction);
                break;
               
    case SUB  : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) - 
                  getRegisterValue(processor, getR3(instruction));
                break;
                
    case SUBI : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) - 
                   getImmediateValue(instruction);
                 break;
                  
    case MUL  : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) * 
                  getRegisterValue(processor, getR3(instruction));
                break;
                  
    case MULI : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction)) * 
                  getImmediateValue(instruction);
                break;
                
    case LW   : processor->gpr[getR1(instruction)] = 
                getMemory(processor, 
                          getRegisterValue(processor, getR2(instruction)) + 
                                            getImmediateValue(instruction));
                break;
                  
    case SW   : setMemory(processor, getRegisterValue
                  (processor, getR2(instruction)) + 
                  getImmediateValue(instruction), 
                  getRegisterValue(processor, getR1(instruction)));
                break;
                
    case BEQ  : if (processor->gpr[getR1(instruction)] == 
                    processor->gpr[getR2(instruction)]) 
                  { processor->pc += getImmediateValue(instruction) * 4;};
                break;
                  
      case BNE  : if (processor->gpr[getR1(instruction)] != 
                      processor->gpr[getR2(instruction)]) 
                    { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BLT  : if (processor->gpr[getR1(instruction)] <
                      processor->gpr[getR2(instruction)])
                    { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BGT  : if (processor->gpr[getR1(instruction)] >
                     processor->gpr[getR2(instruction)]) 
                   { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BLE  : if (processor->gpr[getR1(instruction)] <= 
                      processor->gpr[getR2(instruction)]) 
                  { processor->pc += getImmediateValue(instruction) * 4;};
                  break;
                  
      case BGE  : if (processor->gpr[getR1(instruction)] >= 
                      processor->gpr[getR2(instruction)]) 
                    { processor->pc += (getImmediateValue(instruction) * 4);};
                  break;
                  
      case JMP  : processor->pc = getAddress(instruction);
                  break;
                  
      case JR   : processor->pc = getRegisterValue
                    (processor, getR1(instruction));
                  break;
                  
      case JAL  : processor->gpr[31] = processor->pc + sizeof(uint32_t); 
                  processor->pc = getAddress(instruction);
                  break;
                  
      case OUT  : printf("%c", (char)getRegisterValue
                    (processor, getR1(instruction)));
                  break;
                  
      case DIV  : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getRegisterValue(processor,getR3(instruction)));
                  processor->gpr[getR1(instruction)] = division.quot;
      
      case DIVI : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getImmediateValue(instruction));
                  processor->gpr[getR1(instruction)] = division.quot;
      
      case MOD  : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getRegisterValue(processor,getR3(instruction)));
                  processor->gpr[getR1(instruction)] = division.rem;
      
      case MODI : division = div(getRegisterValue(processor,getR2(instruction))
                              ,getImmediateValue(instruction));
                  processor->gpr[getR1(instruction)] = division.rem;
      
      case FACT : processor->gpr[getR1(instruction)] = 
                  getRegisterValue(processor, getR2(instruction));
                  for(int i = 1; i<processor->gpr[getR2(instruction)] ; i++) {
                    processor->gpr[getR1(instruction)] = 
                      (getRegisterValue(processor, getR1(instruction)))*
                      (getRegisterValue(processor, getR2(instruction))-i);};
                  break;
      
      case FACTI: processor->gpr[getR1(instruction)] = 
                  getImmediateValue(instruction);
                  for(int i = 1; i<getImmediateValue(instruction) ; i++) {
                    processor->gpr[getR1(instruction)] = 
                      (getRegisterValue(processor, getR1(instruction)))*
                      (getImmediateValue(instruction)-i);};
                  break;
      
      case SWAP : temp = 
                    getRegisterValue(processor, getR1(instruction));
                  processor->gpr[getR1(instruction)] = 
                    getRegisterValue(processor, getR2(instruction));
                  processor->gpr[getR2(instruction)] = temp;
                  break;
                  
      default   : printf("invalid opcode\n");
                  break;
    }
    
    if(processor->pc == backupPC)  processor->pc += sizeof(uint32_t);
    return 1;
}