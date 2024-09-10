bool initBasicVars(MemModel &M) {
    uint16_t Size = sizeof(BASin48Vars);
    bool R = M.isUnusedBlock(0x5C00, Size);
    M.memCpy(0x5C00, BASin48Vars, Size, true, true);
    return R;
}