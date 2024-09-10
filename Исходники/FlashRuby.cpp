FREObject FlashRuby_eval(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[])
{
  uint32_t length = 0;
  const uint8_t* fl_str = NULL;
  FREGetObjectAsUTF8(argv[0], &length, &fl_str);
  
  
  
  
  
  InterpreterCallFrame* frame = ALLOCA_CALLFRAME(0);
  frame->prepare(0);
  frame->previous = NULL;
  frame->dispatch_data = NULL;
  frame->flags = 0;
  
  CompiledMethod* cm = CompiledMethod::create(state);
  cm->metadata(state, state->symbol("__script__"));
  cm->name(state, state->symbol("__script__"));
  frame->cm = cm;
  
  StackVariables* scope = ALLOCA_STACKVARIABLES(0);
  scope->initialize(G(main), cNil, G(object), 0);
  scope->on_heap_ = VariableScope::synthesize(state, cm, G(object), cNil, G(main), cNil, state->new_object<Tuple>(G(tuple)));
  frame->scope = scope;
  
  Arguments* arguments = new Arguments(state->symbol("script"), G(main), cNil, 0, 0);
  frame->arguments = arguments;
  
  state->set_call_frame(frame);
  
  
  
  
  String* str = String::create(state, (const char*)fl_str);
  Array* eval_args = Array::create(state, 1);
  eval_args->append(state, str);
  
  
  Object* result_obj = G(main)->send(state, frame, state->symbol("instance_eval"), eval_args);
  const char* result_c_str = result_obj->to_s(state)->c_str_null_safe(state);

  
  FREObject result_str;
  FRENewObjectFromUTF8(strlen(result_c_str), (const uint8_t*)result_c_str, &result_str);
  return result_str;
}