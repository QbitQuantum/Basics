// RAGE AGAINST THE VIRTUAL MACHINE =)
gmThread::State gmThread::Sys_Execute(gmVariable * a_return)
{
  register union
  {
    const gmuint8 * instruction;
    const gmuint32 * instruction32;
  };
  register gmVariable * top;
  gmVariable * base;
  gmVariable * operand;
  const gmuint8 * code;

  if(m_state != RUNNING) return m_state;

#if GMDEBUG_SUPPORT

  if(m_debugFlags && m_machine->GetDebugMode() && m_machine->m_isBroken)
  {
    if(m_machine->m_isBroken(this)) 
      return RUNNING;
  }

#endif // GMDEBUG_SUPPORT

  // make sure we have a stack frame
  GM_ASSERT(m_frame);
  GM_ASSERT(GetFunction()->m_type == GM_FUNCTION);

  // cache our "registers"
  gmFunctionObject * fn = (gmFunctionObject *) GM_MOBJECT(m_machine, GetFunction()->m_value.m_ref);
  code = (const gmuint8 *) fn->GetByteCode();
  if(m_instruction == NULL) instruction = code;
  else instruction = m_instruction;
  top = GetTop();
  base = GetBase();

  //
  // start byte code execution
  //
  for(;;)
  {

#ifdef GM_CHECK_USER_BREAK_CALLBACK // This may be defined in gmConfig_p.h
    // Check external source to break execution with exception eg. Check for CTRL-BREAK
    // Endless loop protection could be implemented with this, or in a similar manner.
    if( gmMachine::s_userBreakCallback && gmMachine::s_userBreakCallback(this) )
    {
      GMTHREAD_LOG("User break. Execution halted.");
      goto LabelException;
    }
#endif //GM_CHECK_USER_BREAK_CALLBACK 

    switch(*(instruction32++))
    {
      //
      // unary operator
      //

#if GM_USE_INCDECOPERATORS
      case BC_OP_INC :
      case BC_OP_DEC :
#endif
      case BC_BIT_INV :
      case BC_OP_NEG :
      case BC_OP_POS :
      case BC_OP_NOT :
      {
        operand = top - 1; 
        gmOperatorFunction op = OPERATOR(operand->m_type, (gmOperator) instruction32[-1]); 
        if(op) 
        { 
          op(this, operand); 
        } 
        else if((fn = CALLOPERATOR(operand->m_type, (gmOperator) instruction32[-1]))) 
        { 
          operand[2] = operand[0]; 
          operand[0] = gmVariable(GM_NULL, 0); 
          operand[1] = gmVariable(GM_FUNCTION, fn->GetRef()); 
          SetTop(operand + 3); 
          State res = PushStackFrame(1, &instruction, &code); 
          top = GetTop();
          base = GetBase();
          if(res == RUNNING) break;
          if(res == SYS_YIELD) return RUNNING;
          if(res == SYS_EXCEPTION) goto LabelException;
          if(res == KILLED) { m_machine->Sys_SwitchState(this, KILLED); GM_ASSERT(0); } // operator should not kill a thread
          return res;
        } 
        else 
        { 
          GMTHREAD_LOG("unary operator %s undefined for type %s", gmGetOperatorName((gmOperator) instruction32[-1]), m_machine->GetTypeName(operand->m_type)); 
          goto LabelException; 
        } 
        break;
      }

      //
      // operator
      //

      case BC_OP_ADD :
      case BC_OP_SUB :
      case BC_OP_MUL :
      case BC_OP_DIV :
      case BC_OP_REM :
      case BC_BIT_OR :
      case BC_BIT_XOR :
      case BC_BIT_AND :
      case BC_BIT_SHL :
      case BC_BIT_SHR :
      case BC_OP_LT :
      case BC_OP_GT :
      case BC_OP_LTE :
      case BC_OP_GTE :
      case BC_OP_EQ :
      case BC_OP_NEQ :
      {
        operand = top - 2; 
        --top; 
        
        // NOTE: Classic logic for operators.  Higher type processes the operation.
        register gmType t1 = operand[1].m_type; 
        if(operand->m_type > t1) t1 = operand->m_type; 
        
        gmOperatorFunction op = OPERATOR(t1, (gmOperator) instruction32[-1]); 
        if(op) 
        { 
          op(this, operand); 
        } 
        else if((fn = CALLOPERATOR(t1, (gmOperator) instruction32[-1]))) 
        { 
          operand[2] = operand[0]; 
          operand[3] = operand[1]; 
          operand[0] = gmVariable(GM_NULL, 0); 
          operand[1] = gmVariable(GM_FUNCTION, fn->GetRef()); 
          SetTop(operand + 4); 
          State res = PushStackFrame(2, &instruction, &code); 
          top = GetTop(); 
          base = GetBase();
          if(res == RUNNING) break;
          if(res == SYS_YIELD) return RUNNING;
          if(res == SYS_EXCEPTION) goto LabelException;
          if(res == KILLED) { m_machine->Sys_SwitchState(this, KILLED); GM_ASSERT(0); } // operator should not kill a thread
          return res;
        } 
        else 
        { 
          GMTHREAD_LOG("operator %s undefined for type %s and %s", gmGetOperatorName((gmOperator) instruction32[-1]), m_machine->GetTypeName(operand->m_type), m_machine->GetTypeName((operand + 1)->m_type)); 
          goto LabelException; 
        } 

        break;
      }
      case BC_GETIND :
      {
        operand = top - 2; 
        --top; 
        gmOperatorFunction op = OPERATOR(operand->m_type, (gmOperator) instruction32[-1]); 
        if(op) 
        { 
          op(this, operand); 
        } 
        else if((fn = CALLOPERATOR(operand->m_type, (gmOperator) instruction32[-1]))) 
        { 
          operand[2] = operand[0]; 
          operand[3] = operand[1]; 
          operand[0] = gmVariable(GM_NULL, 0); 
          operand[1] = gmVariable(GM_FUNCTION, fn->GetRef()); 
          SetTop(operand + 4); 
          State res = PushStackFrame(2, &instruction, &code); 
          top = GetTop(); 
          base = GetBase();
          if(res == RUNNING) break;
          if(res == SYS_YIELD) return RUNNING;
          if(res == SYS_EXCEPTION) goto LabelException;
          if(res == KILLED) { m_machine->Sys_SwitchState(this, KILLED); GM_ASSERT(0); } // operator should not kill a thread
          return res;
        } 
        else 
        { 
          GMTHREAD_LOG("operator %s undefined for type %s and %s", gmGetOperatorName((gmOperator) instruction32[-1]), m_machine->GetTypeName(operand->m_type), m_machine->GetTypeName((operand + 1)->m_type)); 
          goto LabelException; 
        } 

        break;
      }
      case BC_SETIND : 
      { 
        operand = top - 3; 
        top -= 3; 
        gmOperatorFunction op = OPERATOR(operand->m_type, O_SETIND); 
        if(op) 
        { 
          op(this, operand); 
        } 
        else if((fn = CALLOPERATOR(operand->m_type, O_SETIND))) 
        { 
          operand[4] = operand[2]; 
          operand[3] = operand[1]; 
          operand[2] = operand[0]; 
          operand[0] = gmVariable(GM_NULL, 0); 
          operand[1] = gmVariable(GM_FUNCTION, fn->GetRef()); 
          SetTop(operand + 5); 
          State res = PushStackFrame(3, &instruction, &code); 
          top = GetTop(); 
          base = GetBase(); 
          if(res == RUNNING) break; 
          if(res == SYS_YIELD) return RUNNING; 
          if(res == SYS_EXCEPTION) goto LabelException; 
          if(res == KILLED) { m_machine->Sys_SwitchState(this, KILLED); GM_ASSERT(0); } // operator should not kill a thread 
          return res; 
        } 
        else 
        { 
          GMTHREAD_LOG("setind failed."); 
          goto LabelException; 
        } 
        break; 
      } 
      case BC_NOP :
      {
        break;
      }
      case BC_LINE :
      {

#if GMDEBUG_SUPPORT

        if(m_machine->GetDebugMode() && m_machine->m_line)
        {
          SetTop(top);
          m_instruction = instruction;
          if(m_machine->m_line(this)) return RUNNING;
        }

#endif // GMDEBUG_SUPPORT

        break;
      }
      case BC_GETDOT :
      {
        operand = top - 1;
        gmptr member = OPCODE_PTR(instruction);
        top->m_type = GM_STRING;
        top->m_value.m_ref = member;
        gmType t1 = operand->m_type;
        gmOperatorFunction op = OPERATOR(t1, O_GETDOT);
        if(op)
        {
          op(this, operand);
          if(operand->m_type) break;
        }
        if(t1 == GM_NULL)
        {
          GMTHREAD_LOG("getdot failed.");
          goto LabelException;
        }
        *operand = m_machine->GetTypeVariable(t1, gmVariable(GM_STRING, member));
        break;
      }
      case BC_SETDOT :
      {
        operand = top - 2;
        gmptr member = OPCODE_PTR(instruction);
        top->m_type = GM_STRING;
        top->m_value.m_ref = member;
        top -= 2;
        gmOperatorFunction op = OPERATOR(operand->m_type, O_SETDOT);
        if(op)
        {
          op(this, operand);
        }
        else
        {
          GMTHREAD_LOG("setdot failed.");
          goto LabelException;
        }
        break;
      }
      case BC_BRA :
      {
        instruction = code + OPCODE_PTR_NI(instruction);
        break;
      }
      case BC_BRZ :
      {
#if GM_BOOL_OP
        operand = top - 1;
        --top;
        if (operand->m_type > GM_USER)
        {
          // Look for overridden operator.
          gmOperatorFunction op = OPERATOR(operand->m_type, O_BOOL);

          if (op)
          {
            op(this, operand);
          }
          else if ((fn = CALLOPERATOR(operand->m_type, O_BOOL)))
          {
            operand[2] = operand[0];
            operand[0] = gmVariable(GM_NULL, 0);
            operand[1] = gmVariable(GM_FUNCTION, fn->GetRef());
            SetTop(operand + 3);
            // Return to the same instruction after making the call but it will be testing the results of the call.
            --instruction32;
            State res = PushStackFrame(1, &instruction, &code);
            top = GetTop();
            base = GetBase();
            if(res == RUNNING) break;
            if(res == SYS_YIELD) return RUNNING;
            if(res == SYS_EXCEPTION) goto LabelException;
            if(res == KILLED) { m_machine->Sys_SwitchState(this, KILLED); GM_ASSERT(0); } // operator should not kill a thread
            return res;
          }
        }

        if(operand->m_value.m_int == 0)
        {
          instruction = code + OPCODE_PTR_NI(instruction);
        }
        else instruction += sizeof(gmptr);
#else // !GM_BOOL_OP
        --top;
        if(top->m_value.m_int == 0)
        {
          instruction = code + OPCODE_PTR_NI(instruction);
        }
        else instruction += sizeof(gmptr);
#endif // !GM_BOOL_OP
        break;
      }
      case BC_BRNZ :
      {
#if GM_BOOL_OP
        operand = top - 1;
        --top;
        if (operand->m_type > GM_USER)
        {
          // Look for overridden operator.
          gmOperatorFunction op = OPERATOR(operand->m_type, O_BOOL);

          if (op)
          {
            op(this, operand);
          }
          else if ((fn = CALLOPERATOR(operand->m_type, O_BOOL)))
          {
            operand[2] = operand[0];
            operand[0] = gmVariable(GM_NULL, 0);
            operand[1] = gmVariable(GM_FUNCTION, fn->GetRef());
            SetTop(operand + 3);
            // Return to the same instruction after making the call but it will be testing the results of the call.
            --instruction32;
            State res = PushStackFrame(1, &instruction, &code);
            top = GetTop();
            base = GetBase();
            if(res == RUNNING) break;
            if(res == SYS_YIELD) return RUNNING;
            if(res == SYS_EXCEPTION) goto LabelException;
            if(res == KILLED) { m_machine->Sys_SwitchState(this, KILLED); GM_ASSERT(0); } // operator should not kill a thread
            return res;
          }
        }

        if(operand->m_value.m_int != 0)
        {
          instruction = code + OPCODE_PTR_NI(instruction);
        }
        else instruction += sizeof(gmptr);
#else // !GM_BOOL_OP
        --top;
        if(top->m_value.m_int != 0)
        {
          instruction = code + OPCODE_PTR_NI(instruction);
        }
        else instruction += sizeof(gmptr);
#endif // !GM_BOOL_OP
        break;
      }
      case BC_BRZK :
      {
#if GM_BOOL_OP
        operand = top - 1;
        if (operand->m_type > GM_USER)
        {
          // Look for overridden operator.
          gmOperatorFunction op = OPERATOR(operand->m_type, O_BOOL);

          if (op)
          {
            op(this, operand);
          }
          else if ((fn = CALLOPERATOR(operand->m_type, O_BOOL)))
          {
            operand[2] = operand[0];
            operand[0] = gmVariable(GM_NULL, 0);
            operand[1] = gmVariable(GM_FUNCTION, fn->GetRef());
            SetTop(operand + 3);
            // Return to the same instruction after making the call but it will be testing the results of the call.
            --instruction32;
            State res = PushStackFrame(1, &instruction, &code);
            top = GetTop();
            base = GetBase();
            if(res == RUNNING) break;
            if(res == SYS_YIELD) return RUNNING;
            if(res == SYS_EXCEPTION) goto LabelException;
            if(res == KILLED) { m_machine->Sys_SwitchState(this, KILLED); GM_ASSERT(0); } // operator should not kill a thread
            return res;
          }
        }

        if(operand->m_value.m_int == 0)
        {
          instruction = code + OPCODE_PTR_NI(instruction);
        }
        else instruction += sizeof(gmptr);
#else // !GM_BOOL_OP
        if(top[-1].m_value.m_int == 0)
        {
          instruction = code + OPCODE_PTR_NI(instruction);
        }
        else instruction += sizeof(gmptr);
#endif // !GM_BOOL_OP
        break;
      }
      case BC_BRNZK :
      {
#if GM_BOOL_OP
        operand = top - 1;
        if (operand->m_type > GM_USER)
        {
          // Look for overridden operator.
          gmOperatorFunction op = OPERATOR(operand->m_type, O_BOOL);

          if (op)
          {
            op(this, operand);
          }
          else if ((fn = CALLOPERATOR(operand->m_type, O_BOOL)))
          {
            operand[2] = operand[0];
            operand[0] = gmVariable(GM_NULL, 0);
            operand[1] = gmVariable(GM_FUNCTION, fn->GetRef());
            SetTop(operand + 3);
            // Return to the same instruction after making the call but it will be testing the results of the call.
            --instruction32;
            State res = PushStackFrame(1, &instruction, &code);
            top = GetTop();
            base = GetBase();
            if(res == RUNNING) break;
            if(res == SYS_YIELD) return RUNNING;
            if(res == SYS_EXCEPTION) goto LabelException;
            if(res == KILLED) { m_machine->Sys_SwitchState(this, KILLED); GM_ASSERT(0); } // operator should not kill a thread
            return res;
          }
        }

        if(operand->m_value.m_int != 0)
        {
          instruction = code + OPCODE_PTR_NI(instruction);
        }
        else instruction += sizeof(gmptr);
#else // !GM_BOOL_OP
        if(top[-1].m_value.m_int != 0)
        {
          instruction = code + OPCODE_PTR_NI(instruction);
        }
        else instruction += sizeof(gmptr);
#endif // !GM_BOOL_OP
        break;
      }
      case BC_CALL :
      {
        SetTop(top);
        
        int numParams = (int) OPCODE_INT(instruction);

        State res = PushStackFrame(numParams, &instruction, &code);
        top = GetTop(); 
        base = GetBase();

        if(res == RUNNING)
        {

#if GMDEBUG_SUPPORT

          if(m_debugFlags && m_machine->GetDebugMode() && m_machine->m_call)
          {
            m_instruction = instruction;
            if(m_machine->m_call(this)) return RUNNING;
          }

#endif // GMDEBUG_SUPPORT

          break;
        }
        if(res == SYS_YIELD) return RUNNING;
        if(res == SYS_EXCEPTION) goto LabelException;
        if(res == KILLED)
        {
          if(a_return) *a_return = m_stack[m_top - 1];
          m_machine->Sys_SwitchState(this, KILLED);
        }
        return res;
      }
      case BC_RET :
      {
        PUSHNULL;
      }
      case BC_RETV :
      {
        SetTop(top);
        int res = Sys_PopStackFrame(instruction, code);
        top = GetTop();
        base = GetBase();

        if(res == RUNNING) 
        {

#if GMDEBUG_SUPPORT

          if(m_debugFlags && m_machine->GetDebugMode() && m_machine->m_return)
          {
            m_instruction = instruction;
            if(m_machine->m_return(this)) return RUNNING;
          }

#endif // GMDEBUG_SUPPORT

          break;
        }
        if(res == KILLED)
        {
          if(a_return) *a_return = *(top - 1);
          m_machine->Sys_SwitchState(this, KILLED);
          return KILLED;
        }
        if(res == SYS_EXCEPTION) goto LabelException;
        break;
      }
#if GM_USE_FORK
    // duplicates the current thread and just the local stack frame
    // and branches around the forked section of code
     case BC_FORK :
     {
        int id;
        gmThread* newthr = GetMachine()->CreateThread(&id);
        GM_ASSERT( newthr );

        // make sure there is enough room
        newthr->Touch( m_size - m_base + 2 - GMTHREAD_SLACKSPACE);
        // copy stack and vars
        memcpy( newthr->m_stack, &m_stack[ m_base - 2 ], sizeof( gmVariable ) * (m_top - m_base + 2 ) );

        newthr->m_top = m_top - m_base + 2;
        newthr->m_frame = m_machine->Sys_AllocStackFrame();
        newthr->m_frame->m_prev = 0;
        newthr->m_frame->m_returnAddress = 0;
        newthr->m_frame->m_returnBase = 0;

        newthr->m_base = 2;
        newthr->m_instruction = instruction + sizeof(gmptr); // skip branch on other thread
        newthr->PushInt( GetId() );

        instruction = code + OPCODE_PTR_NI( instruction );   // branch

        top->m_type = GM_INT;
        top->m_value.m_int = newthr->GetId();
        ++top;
        break;
     }
#endif //GM_USE_FORK
      case BC_FOREACH :
      {
        gmuint32 localvalue = OPCODE_INT(instruction);
        gmuint32 localkey = localvalue >> 16;
        localvalue &= 0xffff;

        // iterator is at tos-1, table is at tos -2, push int 1 if continuing loop. write key and value into localkey and localvalue
        if(top[-2].m_type != GM_TABLE)
        {
#if GM_USER_FOREACH
          gmTypeIteratorCallback itrfunc = m_machine->GetUserTypeIteratorCallback(top[-2].m_type);
          if (!itrfunc)
          {
            GMTHREAD_LOG("foreach expression has no iterator function");
            goto LabelException;
          }

          gmTypeIterator it = (gmTypeIterator) top[-1].m_value.m_int;
          gmUserObject *obj = (gmUserObject*)GM_MOBJECT(m_machine, top[-2].m_value.m_ref);
          // Do callback for getnext
          gmVariable localvar;
          gmVariable localkeyvar;
          itrfunc(this, obj, it, &localkeyvar, &localvar);
          if (it != GM_TYPE_ITR_NULL)
          {
            base[localkey] = localkeyvar;
            base[localvalue] = localvar;
            top->m_type = GM_INT; top->m_value.m_int = 1;
          }
          else
          {
            top->m_type = GM_INT; top->m_value.m_int = 0;
          }
          top[-1].m_value.m_int = it;
          ++top;
#else //GM_USER_FOREACH (original)
          GMTHREAD_LOG("foreach expression is not table type");
          goto LabelException;
#endif //GM_USER_FOREACH
        }
        else
        {
          GM_ASSERT(top[-1].m_type == GM_INT);
          gmTableIterator it = (gmTableIterator) top[-1].m_value.m_int;
          gmTableObject * table = (gmTableObject *) GM_MOBJECT(m_machine, top[-2].m_value.m_ref);
          gmTableNode * node = table->GetNext(it);
          top[-1].m_value.m_int = it;
          if(node)
          {
            base[localkey] = node->m_key;
            base[localvalue] = node->m_value;
            top->m_type = GM_INT; top->m_value.m_int = 1;
          }
          else
          {
            top->m_type = GM_INT; top->m_value.m_int = 0;
          }
          ++top;
        }
        break;
      }
      case BC_POP :
      {
        --top;
        break;
      }
      case BC_POP2 :
      {
        top -= 2;
        break;
      }
      case BC_DUP :
      {
        top[0] = top[-1]; 
        ++top;
        break;
      }
      case BC_DUP2 :
      {
        top[0] = top[-2];
        top[1] = top[-1];
        top += 2;
        break;
      }
      case BC_SWAP :
      {
        top[0] = top[-1];
        top[-1] = top[-2];
        top[-2] = top[0];
        break;
      }
      case BC_PUSHNULL :
      {
        PUSHNULL;
        break;
      }
      case BC_PUSHINT :
      {
        top->m_type = GM_INT;
        top->m_value.m_int = OPCODE_INT(instruction);
        ++top;
        break;
      }
      case BC_PUSHINT0 :
      {
        top->m_type = GM_INT;
        top->m_value.m_int = 0;
        ++top;
        break;
      }
      case BC_PUSHINT1 :
      {
        top->m_type = GM_INT;
        top->m_value.m_int = 1;
        ++top;
        break;
      }
      case BC_PUSHFP :
      {
        top->m_type = GM_FLOAT;
        top->m_value.m_float = OPCODE_FLOAT(instruction);
        ++top;
        break;
      }
      case BC_PUSHSTR :
      {
        top->m_type = GM_STRING;
        top->m_value.m_ref = OPCODE_PTR(instruction);
        ++top;
        break;
      }
      case BC_PUSHTBL :
      {
        SetTop(top);
        top->m_type = GM_TABLE;
        top->m_value.m_ref = m_machine->AllocTableObject()->GetRef();
        ++top;
        break;
      }
      case BC_PUSHFN :
      {
        top->m_type = GM_FUNCTION;
        top->m_value.m_ref = OPCODE_PTR(instruction);
        ++top;
        break;
      }
      case BC_PUSHTHIS :
      {
        *top = *GetThis();
        ++top;
        break;
      }
      case BC_GETLOCAL :
      {
        gmuint32 offset = OPCODE_INT(instruction);
        *(top++) = base[offset];
        break;
      }
      case BC_SETLOCAL :
      {
        gmuint32 offset = OPCODE_INT(instruction);

        // Write barrier old local objects
        {
          gmGarbageCollector* gc = m_machine->GetGC();
          if( !gc->IsOff() && base[offset].IsReference() )
          {
            gmObject * object = GM_MOBJECT(m_machine, base[offset].m_value.m_ref);
            gc->WriteBarrier(object);
          }
        }

        base[offset] = *(--top);
        break;
      }
      case BC_GETGLOBAL :
      {
        top->m_type = GM_STRING;
        top->m_value.m_ref = OPCODE_PTR(instruction);
        *top = m_machine->GetGlobals()->Get(*top); ++top;
        break;
      }
      case BC_SETGLOBAL :
      {
        top->m_type = GM_STRING;
        top->m_value.m_ref = OPCODE_PTR(instruction);
        m_machine->GetGlobals()->Set(m_machine, *top, *(top-1)); --top;
        break;
      }
      case BC_GETTHIS :
      {
        gmptr member = OPCODE_PTR(instruction);
        const gmVariable * thisVar = GetThis();
        *top = *thisVar;
        top[1].m_type = GM_STRING;
        top[1].m_value.m_ref = member;
        gmOperatorFunction op = OPERATOR(thisVar->m_type, O_GETDOT);
        if(op)
        {
          op(this, top);
          if(top->m_type) { ++top; break; }
        }
        if(thisVar->m_type == GM_NULL)
        {
          GMTHREAD_LOG("getthis failed. this is null");
          goto LabelException;
        }
        *top = m_machine->GetTypeVariable(thisVar->m_type, top[1]);
        ++top;
        break;
      }
      case BC_SETTHIS :
      {
        gmptr member = OPCODE_PTR(instruction);
        const gmVariable * thisVar = GetThis();
        operand = top - 1;
        *top = *operand;
        *operand = *thisVar;
        top[1].m_type = GM_STRING;
        top[1].m_value.m_ref = member;
        --top;
        gmOperatorFunction op = OPERATOR(thisVar->m_type, O_SETDOT);
        if(op)
        {
          op(this, operand);
        }
        else
        {
          GMTHREAD_LOG("setthis failed.");
          goto LabelException;
        }
        break;
      }
      default :
      {
        break;
      }
    }
  }

LabelException:

  //
  // exception handler
  //
  m_instruction = instruction;

  // spit out error info
  LogLineFile();
  LogCallStack();

  // call machine exception handler
  if(gmMachine::s_machineCallback)
  {
    if(gmMachine::s_machineCallback(m_machine, MC_THREAD_EXCEPTION, this))
    {
#if GMDEBUG_SUPPORT
      // if we are being debugged, put this thread into a limbo state, waiting for delete.
      if(m_machine->GetDebugMode() && m_machine->m_debugUser)
      {
        m_machine->Sys_SwitchState(this, EXCEPTION);
        return EXCEPTION;
      }
#endif
    }
  }

  // kill the thread
  m_machine->Sys_SwitchState(this, KILLED);
  return KILLED;
}