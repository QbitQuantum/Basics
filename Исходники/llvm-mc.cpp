static int AsLexInput(SourceMgr &SrcMgr, MCAsmInfo &MAI, tool_output_file *Out) {

  AsmLexer Lexer(MAI);
  Lexer.setBuffer(SrcMgr.getMemoryBuffer(0));

  bool Error = false;
  while (Lexer.Lex().isNot(AsmToken::Eof)) {
    AsmToken Tok = Lexer.getTok();

    switch (Tok.getKind()) {
    default:
      SrcMgr.PrintMessage(Lexer.getLoc(), SourceMgr::DK_Warning,
                          "unknown token");
      Error = true;
      break;
    case AsmToken::Error:
      Error = true; // error already printed.
      break;
    case AsmToken::Identifier:
      Out->os() << "identifier: " << Lexer.getTok().getString();
      break;
    case AsmToken::Integer:
      Out->os() << "int: " << Lexer.getTok().getString();
      break;
    case AsmToken::Real:
      Out->os() << "real: " << Lexer.getTok().getString();
      break;
    case AsmToken::String:
      Out->os() << "string: " << Lexer.getTok().getString();
      break;

    case AsmToken::Amp:            Out->os() << "Amp"; break;
    case AsmToken::AmpAmp:         Out->os() << "AmpAmp"; break;
    case AsmToken::At:             Out->os() << "At"; break;
    case AsmToken::Caret:          Out->os() << "Caret"; break;
    case AsmToken::Colon:          Out->os() << "Colon"; break;
    case AsmToken::Comma:          Out->os() << "Comma"; break;
    case AsmToken::Dollar:         Out->os() << "Dollar"; break;
    case AsmToken::Dot:            Out->os() << "Dot"; break;
    case AsmToken::EndOfStatement: Out->os() << "EndOfStatement"; break;
    case AsmToken::Eof:            Out->os() << "Eof"; break;
    case AsmToken::Equal:          Out->os() << "Equal"; break;
    case AsmToken::EqualEqual:     Out->os() << "EqualEqual"; break;
    case AsmToken::Exclaim:        Out->os() << "Exclaim"; break;
    case AsmToken::ExclaimEqual:   Out->os() << "ExclaimEqual"; break;
    case AsmToken::Greater:        Out->os() << "Greater"; break;
    case AsmToken::GreaterEqual:   Out->os() << "GreaterEqual"; break;
    case AsmToken::GreaterGreater: Out->os() << "GreaterGreater"; break;
    case AsmToken::Hash:           Out->os() << "Hash"; break;
    case AsmToken::LBrac:          Out->os() << "LBrac"; break;
    case AsmToken::LCurly:         Out->os() << "LCurly"; break;
    case AsmToken::LParen:         Out->os() << "LParen"; break;
    case AsmToken::Less:           Out->os() << "Less"; break;
    case AsmToken::LessEqual:      Out->os() << "LessEqual"; break;
    case AsmToken::LessGreater:    Out->os() << "LessGreater"; break;
    case AsmToken::LessLess:       Out->os() << "LessLess"; break;
    case AsmToken::Minus:          Out->os() << "Minus"; break;
    case AsmToken::Percent:        Out->os() << "Percent"; break;
    case AsmToken::Pipe:           Out->os() << "Pipe"; break;
    case AsmToken::PipePipe:       Out->os() << "PipePipe"; break;
    case AsmToken::Plus:           Out->os() << "Plus"; break;
    case AsmToken::RBrac:          Out->os() << "RBrac"; break;
    case AsmToken::RCurly:         Out->os() << "RCurly"; break;
    case AsmToken::RParen:         Out->os() << "RParen"; break;
    case AsmToken::Slash:          Out->os() << "Slash"; break;
    case AsmToken::Star:           Out->os() << "Star"; break;
    case AsmToken::Tilde:          Out->os() << "Tilde"; break;
    }

    // Print the token string.
    Out->os() << " (\"";
    Out->os().write_escaped(Tok.getString());
    Out->os() << "\")\n";
  }

  return Error;
}