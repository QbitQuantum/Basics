  void Output::operator()(Ruleset* r)
  {
    Selector* s     = r->selector();
    Block*    b     = r->block();
    bool      decls = false;

    // Filter out rulesets that aren't printable (process its children though)
    if (!Util::isPrintable(r, output_style())) {
      for (size_t i = 0, L = b->length(); i < L; ++i) {
        Statement* stm = (*b)[i];
        if (dynamic_cast<Has_Block*>(stm)) {
          stm->perform(this);
        }
      }
      return;
    }

    if (b->has_non_hoistable()) {
      decls = true;
      if (output_style() == NESTED) indentation += r->tabs();
      if (opt.source_comments) {
        std::stringstream ss;
        append_indentation();
        ss << "/* line " << r->pstate().line + 1 << ", " << r->pstate().path << " */";
        append_string(ss.str());
        append_optional_linefeed();
      }
      s->perform(this);
      append_scope_opener(b);
      for (size_t i = 0, L = b->length(); i < L; ++i) {
        Statement* stm = (*b)[i];
        bool bPrintExpression = true;
        // Check print conditions
        if (typeid(*stm) == typeid(Declaration)) {
          Declaration* dec = static_cast<Declaration*>(stm);
          if (dec->value()->concrete_type() == Expression::STRING) {
            String_Constant* valConst = static_cast<String_Constant*>(dec->value());
            std::string val(valConst->value());
            if (auto qstr = dynamic_cast<String_Quoted*>(valConst)) {
              if (!qstr->quote_mark() && val.empty()) {
                bPrintExpression = false;
              }
            }
          }
          else if (dec->value()->concrete_type() == Expression::LIST) {
            List* list = static_cast<List*>(dec->value());
            bool all_invisible = true;
            for (size_t list_i = 0, list_L = list->length(); list_i < list_L; ++list_i) {
              Expression* item = (*list)[list_i];
              if (!item->is_invisible()) all_invisible = false;
            }
            if (all_invisible) bPrintExpression = false;
          }
        }
        // Print if OK
        if (!stm->is_hoistable() && bPrintExpression) {
          stm->perform(this);
        }
      }
      if (output_style() == NESTED) indentation -= r->tabs();
      append_scope_closer(b);
    }

    if (b->has_hoistable()) {
      if (decls) ++indentation;
      for (size_t i = 0, L = b->length(); i < L; ++i) {
        Statement* stm = (*b)[i];
        if (stm->is_hoistable()) {
          stm->perform(this);
        }
      }
      if (decls) --indentation;
    }
  }