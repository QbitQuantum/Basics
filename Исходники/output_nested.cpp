  void Output_Nested::operator()(Ruleset* r)
  {
    Selector* s     = r->selector();
    Block*    b     = r->block();
    bool      decls = false;

    if (s->has_placeholder()) return;

    if (b->has_non_hoistable()) {
      decls = true;
      indent();
      if (source_comments) {
        stringstream ss;
        ss << "/* line " << r->line() << ", " << r->path() << " */" << endl;
        buffer += ss.str();
        indent();
      }
      s->perform(this);
      buffer += " {\n";
      ++indentation;
      for (size_t i = 0, L = b->length(); i < L; ++i) {
        Statement* stm = (*b)[i];
        if (!stm->is_hoistable()) {
          if (!stm->block()) indent();
          stm->perform(this);
          buffer += '\n';
        }
      }
      --indentation;
      buffer.erase(buffer.length()-1);
      buffer += " }\n";
    }

    if (b->has_hoistable()) {
      if (decls) ++indentation;
      // indent();
      for (size_t i = 0, L = b->length(); i < L; ++i) {
        Statement* stm = (*b)[i];
        if (stm->is_hoistable()) {
          stm->perform(this);
        }
      }
      if (decls) --indentation;
    }
  }