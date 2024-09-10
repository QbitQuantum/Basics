static void parseMCMarkup(StringRef Filename) {
  OwningPtr<MemoryBuffer> BufferPtr;
  if (error_code ec = MemoryBuffer::getFileOrSTDIN(Filename, BufferPtr)) {
    errs() << ToolName << ": " << ec.message() << '\n';
    return;
  }
  MemoryBuffer *Buffer = BufferPtr.take();

  SourceMgr SrcMgr;

  // Tell SrcMgr about this buffer, which is what the parser will pick up.
  SrcMgr.AddNewSourceBuffer(Buffer, SMLoc());

  StringRef InputSource = Buffer->getBuffer();
  MarkupLexer Lex(InputSource);
  MarkupParser Parser(Lex, SrcMgr);

  SmallVector<MarkupTag, 4> TagStack;

  for (int CurChar = Lex.getNextChar();
       CurChar != EOF;
       CurChar = Lex.getNextChar()) {
    switch (CurChar) {
    case '<': {
      // A "<<" is output as a literal '<' and does not start a markup tag.
      if (Lex.peekNextChar() == '<') {
        (void)Lex.getNextChar();
        break;
      }
      // Parse the markup entry.
      TagStack.push_back(Parser.parseTag());

      // Do any special handling for the start of a tag.
      processStartTag(TagStack.back());
      continue;
    }
    case '>': {
      SMLoc Loc = SMLoc::getFromPointer(Lex.getPosition() - 1);
      // A ">>" is output as a literal '>' and does not end a markup tag.
      if (Lex.peekNextChar() == '>') {
        (void)Lex.getNextChar();
        break;
      }
      // Close out the innermost tag.
      if (TagStack.empty())
        Parser.FatalError(Loc, "'>' without matching '<'");

      // Do any special handling for the end of a tag.
      processEndTag(TagStack.back());

      TagStack.pop_back();
      continue;
    }
    default:
      break;
    }
    // For anything else, just echo the character back out.
    if (!DumpTags && CurChar != EOF)
      outs() << (char)CurChar;
  }

  // If there are any unterminated markup tags, issue diagnostics for them.
  while (!TagStack.empty()) {
    MarkupTag &Tag = TagStack.back();
    SrcMgr.PrintMessage(Tag.getLoc(), SourceMgr::DK_Error,
                        "unterminated markup tag");
    TagStack.pop_back();
  }
}