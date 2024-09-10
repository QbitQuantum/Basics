  void Output_Compressed::operator()(Media_Block* m)
  {
    List*  q     = m->media_queries();
    Block* b     = m->block();

    ctx->source_map.add_mapping(m);
    append_singleline_part_to_buffer("@media ");
    q->perform(this);
    append_singleline_part_to_buffer("{");

    Selector* e = m->enclosing_selector();
    bool hoisted = false;
    if (e && b->has_non_hoistable()) {
      hoisted = true;
      e->perform(this);
      append_singleline_part_to_buffer("{");
    }

    for (size_t i = 0, L = b->length(); i < L; ++i) {
      Statement* stm = (*b)[i];
      if (!stm->is_hoistable()) {
        stm->perform(this);
      }
    }

    if (hoisted) {
      append_singleline_part_to_buffer("}");
    }

    for (size_t i = 0, L = b->length(); i < L; ++i) {
      Statement* stm = (*b)[i];
      if (stm->is_hoistable()) {
        stm->perform(this);
      }
    }

    append_singleline_part_to_buffer("}");
  }