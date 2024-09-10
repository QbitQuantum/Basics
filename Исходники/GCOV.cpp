/// readGCNO - Read a function from the GCNO buffer. Return false if an error
/// occurs.
bool GCOVFunction::readGCNO(GCOVBuffer &Buff, GCOV::GCOVVersion Version) {
  uint32_t Dummy;
  if (!Buff.readInt(Dummy)) return false; // Function header length
  if (!Buff.readInt(Ident)) return false;
  if (!Buff.readInt(Checksum)) return false;
  if (Version != GCOV::V402) {
    uint32_t CfgChecksum;
    if (!Buff.readInt(CfgChecksum)) return false;
    if (Parent.getChecksum() != CfgChecksum) {
      errs() << "File checksums do not match: " << Parent.getChecksum()
             << " != " << CfgChecksum << " in (" << Name << ").\n";
      return false;
    }
  }
  if (!Buff.readString(Name)) return false;
  if (!Buff.readString(Filename)) return false;
  if (!Buff.readInt(LineNumber)) return false;

  // read blocks.
  if (!Buff.readBlockTag()) {
    errs() << "Block tag not found.\n";
    return false;
  }
  uint32_t BlockCount;
  if (!Buff.readInt(BlockCount)) return false;
  for (uint32_t i = 0, e = BlockCount; i != e; ++i) {
    if (!Buff.readInt(Dummy)) return false; // Block flags;
    Blocks.push_back(make_unique<GCOVBlock>(*this, i));
  }

  // read edges.
  while (Buff.readEdgeTag()) {
    uint32_t EdgeCount;
    if (!Buff.readInt(EdgeCount)) return false;
    EdgeCount = (EdgeCount - 1) / 2;
    uint32_t BlockNo;
    if (!Buff.readInt(BlockNo)) return false;
    if (BlockNo >= BlockCount) {
      errs() << "Unexpected block number: " << BlockNo << " (in " << Name
             << ").\n";
      return false;
    }
    for (uint32_t i = 0, e = EdgeCount; i != e; ++i) {
      uint32_t Dst;
      if (!Buff.readInt(Dst)) return false;
      Edges.push_back(make_unique<GCOVEdge>(*Blocks[BlockNo], *Blocks[Dst]));
      GCOVEdge *Edge = Edges.back().get();
      Blocks[BlockNo]->addDstEdge(Edge);
      Blocks[Dst]->addSrcEdge(Edge);
      if (!Buff.readInt(Dummy)) return false; // Edge flag
    }
  }

  // read line table.
  while (Buff.readLineTag()) {
    uint32_t LineTableLength;
    // Read the length of this line table.
    if (!Buff.readInt(LineTableLength)) return false;
    uint32_t EndPos = Buff.getCursor() + LineTableLength*4;
    uint32_t BlockNo;
    // Read the block number this table is associated with.
    if (!Buff.readInt(BlockNo)) return false;
    if (BlockNo >= BlockCount) {
      errs() << "Unexpected block number: " << BlockNo << " (in " << Name
             << ").\n";
      return false;
    }
    GCOVBlock &Block = *Blocks[BlockNo];
    // Read the word that pads the beginning of the line table. This may be a
    // flag of some sort, but seems to always be zero.
    if (!Buff.readInt(Dummy)) return false;

    // Line information starts here and continues up until the last word.
    if (Buff.getCursor() != (EndPos - sizeof(uint32_t))) {
      StringRef F;
      // Read the source file name.
      if (!Buff.readString(F)) return false;
      if (Filename != F) {
        errs() << "Multiple sources for a single basic block: " << Filename
               << " != " << F << " (in " << Name << ").\n";
        return false;
      }
      // Read lines up to, but not including, the null terminator.
      while (Buff.getCursor() < (EndPos - 2 * sizeof(uint32_t))) {
        uint32_t Line;
        if (!Buff.readInt(Line)) return false;
        // Line 0 means this instruction was injected by the compiler. Skip it.
        if (!Line) continue;
        Block.addLine(Line);
      }
      // Read the null terminator.
      if (!Buff.readInt(Dummy)) return false;
    }
    // The last word is either a flag or padding, it isn't clear which. Skip
    // over it.
    if (!Buff.readInt(Dummy)) return false;
  }
  return true;
}