Inst parseMnemoGcnMem(unsigned opCode, Scanner& scanner, Brigantine& bw, int* vx) 
{
    OptionalU const vector  = scanner.tryEatToken(EMVector);
    string    const segment = scanner.scan().text();

    if (segment != AMD_GCN_SEGMENT_SUFF) scanner.syntaxError("missing or invalid segment name");

    int vx2 = -1;
    InstMem res = parseMnemoMem(opCode, scanner, bw, &vx2);
    if (res.segment() != BRIG_SEGMENT_FLAT) scanner.syntaxError("invalid segment");
    if (vx2 != 1) scanner.syntaxError("invalid vX suffix");

    res.segment() = BRIG_SEGMENT_AMD_GCN;
    if (vx) *vx = vector.isInitialized() ? vector.value() : 1;

    return res;
}