// DSPInstrInfo::expandPostRAPseudo
/// Expand Pseudo instructions into real backend instructions
bool DSPSEInstrInfo::expandPostRAPseudo(MachineBasicBlock::iterator MI) const {
    MachineBasicBlock &MBB = *MI->getParent();
    switch (MI->getDesc().getOpcode()) {
    default:
        return false;
    case DSP::RetLR:
        ExpandRetLR(MBB, MI, DSP::Ret);
        break;
    case DSP::MovVR:
        ExpandMovVR(MBB, MI, DSP::MovG2V40);
        break;
    case DSP::MovGR:
        ExpandMovGR(MBB, MI, DSP::MovIGH, DSP::MovIGL);
        break;
    }
    MBB.erase(MI);
    return true;
}