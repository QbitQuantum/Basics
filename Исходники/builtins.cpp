void build_vt_for_freevar(rt_h const & rt)
{
  function freevar_name = inline_<function>(
      rt.labelfun_t, ".name.freevar", {"node_p"}
    , [&] {
        value node_p = arg("node_p");
        value id = node_p.arrow(ND_AUX);
        value rv = rt.snprintf(
            &printbuffer(rt), PRINT_BUFFER_SIZE, "_x%" PRId32, id
          );
        if_(rv ==(signed_)(0)
          , [&]{
              rt.perror("Error converting free variable to string");
              rt.exit(1);
            }
          );
        return_(&printbuffer(rt));
      }
    );

  extern_(rt.vtable_t, sprite::compiler::get_vt_name("freevar"))
      .set_initializer(_t(
          &rt.Cy_NoAction
        , &rt.Cy_NoAction
        , &freevar_name
        , &rt.Cy_Sentinel()
        , sprite::compiler::FREE
        , &rt.Cy_Arity(0)
        , &rt.Cy_Succ(0)
        , &rt.CyFree_GcSucc()
        , &rt.Cy_Destroy(0)
        , nullptr // unreachable
        , nullptr
        , nullptr
        , nullptr
        , nullptr
        ))
    ;
}