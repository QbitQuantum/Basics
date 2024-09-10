void BlockIterator::advance()
{
    ca_assert(!finished());
    if (_skipNextBlock) {
        _skipNextBlock = false;
        advanceSkippingBlock();
        return;
    }

    Term* term = current();

    // Check to start an inner block.
    if (term && term->nestedContents && term->contents()->length() > 0) {
        Block* contents = nested_contents(term);
        int firstIndex = _backwards ? contents->length() - 1 : 0;
        _stack.push_back(IteratorFrame(contents, firstIndex));
        return;
    }

    // Otherwise, just advance. PS, it's not really accurate to say that we are "skipping"
    // any blocks, because we just checked if there was one.
    advanceSkippingBlock();
}