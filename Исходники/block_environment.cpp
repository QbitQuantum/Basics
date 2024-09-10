  // Installed by default in BlockEnvironment::execute, it runs the bytecodes
  // for the block in the interpreter.
  //
  // Future code will detect hot blocks and queue them in the JIT, whereby the
  // JIT will install a newly minted machine function into ::execute.
  Object* BlockEnvironment::execute_interpreter(STATE, CallFrame* previous,
                            BlockEnvironment* const env, Arguments& args,
                            BlockInvocation& invocation)
  {
    VMMethod* const vmm = env->vmmethod(state);

    if(!vmm) {
      Exception::internal_error(state, previous, "invalid bytecode method");
      return 0;
    }

#ifdef ENABLE_LLVM
    if(vmm->call_count >= 0) {
      if(vmm->call_count >= state->shared.config.jit_call_til_compile) {
        LLVMState* ls = LLVMState::get(state);

        ls->compile_soon(state, env->code(), env);

      } else {
        vmm->call_count++;
      }
    }
#endif

    size_t scope_size = sizeof(StackVariables) +
      (vmm->number_of_locals * sizeof(Object*));
    StackVariables* scope =
      reinterpret_cast<StackVariables*>(alloca(scope_size));

    Module* mod = invocation.module;
    if(!mod) mod = env->module();
    scope->initialize(invocation.self, env->top_scope_->block(),
                      mod, vmm->number_of_locals);
    scope->set_parent(env->scope_);

    InterpreterCallFrame* frame = ALLOCA_CALLFRAME(vmm->stack_size);
    frame->prepare(vmm->stack_size);

    frame->previous = previous;
    frame->static_scope_ = invocation.static_scope;

    frame->arguments = &args;
    frame->dispatch_data = reinterpret_cast<BlockEnvironment*>(env);
    frame->cm =       env->code_;
    frame->scope =    scope;
    frame->top_scope_ = env->top_scope_;
    frame->flags =    invocation.flags | CallFrame::cCustomStaticScope
                     | CallFrame::cMultipleScopes
                     | CallFrame::cBlock;

    // Check the stack and interrupts here rather than in the interpreter
    // loop itself.

    if(state->detect_stack_condition(frame)) {
      if(!state->check_interrupts(frame, frame)) return NULL;
    }

    state->global_lock().checkpoint(state, frame);

    if(unlikely(state->interrupts.check)) {
      state->interrupts.checked();
      if(state->interrupts.perform_gc) {
        state->interrupts.perform_gc = false;
        state->collect_maybe(frame);
      }
    }

#ifdef RBX_PROFILER
    if(unlikely(state->tooling())) {
      Module* mod = scope->module();
      if(SingletonClass* sc = try_as<SingletonClass>(mod)) {
        if(Module* ma = try_as<Module>(sc->attached_instance())) {
          mod = ma;
        }
      }

      tooling::BlockEntry method(state, env, mod);
      return (*vmm->run)(state, vmm, frame);
    } else {
      return (*vmm->run)(state, vmm, frame);
    }
#else
    return (*vmm->run)(state, vmm, frame);
#endif
  }