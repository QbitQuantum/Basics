void add_implicit_placeholders(Term* forTerm)
{
    Block* contents = nested_contents(forTerm);
    std::string listName = forTerm->input(0)->name;
    Term* iterator = for_loop_get_iterator(contents);
    std::string iteratorName = iterator->name;

    std::vector<std::string> reboundNames;
    list_names_that_this_block_rebinds(contents, reboundNames);

    int inputIndex = 1;

    for (size_t i=0; i < reboundNames.size(); i++) {
        std::string const& name = reboundNames[i];
        if (name == listName)
            continue;
        if (name == iteratorName)
            continue;

        Term* original = find_name_at(forTerm, name.c_str());

        // The name might not be found, for certain parser errors.
        if (original == NULL)
            continue;

        Term* result = contents->get(name);

        // Create input_placeholder
        Term* input = apply(contents, FUNCS.input, TermList(), name_from_string(name));
        Type* type = find_common_type(original->type, result->type);
        change_declared_type(input, type);
        contents->move(input, inputIndex);

        set_input(forTerm, inputIndex, original);

        // Repoint terms to use our new input_placeholder
        for (BlockIterator it(contents); it.unfinished(); it.advance())
            remap_pointers_quick(*it, original, input);

        // Create output_placeholder
        Term* term = apply(contents, FUNCS.output, TermList(result), name_from_string(name));

        // Move output into the correct output slot
        contents->move(term, contents->length() - 1 - inputIndex);

        inputIndex++;
    }
}