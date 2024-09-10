  int rbx_destructure_args(STATE, CallFrame* call_frame, Arguments& args) {
    Object* obj = args.get_argument(0);
    Array* ary = 0;

    if(!(ary = try_as<Array>(obj))) {
      if(CBOOL(obj->respond_to(state, G(sym_to_ary), cFalse))) {
        if(!(obj = obj->send(state, call_frame, G(sym_to_ary)))) {
          return -1;
        }

        if(!(ary = try_as<Array>(obj)) && !obj->nil_p()) {
          Exception::type_error(state, "to_ary must return an Array", call_frame);
          return -1;
        }
      }
    }

    if(ary) {
      args.use_array(ary);
    }

    return args.total();
  }