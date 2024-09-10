void QemuSescReader::readInst() { 

  if (fread(qst, sizeof(QemuSescTrace), 1, trace) !=1){
    MSG("Size of each structure is %lu", sizeof(qst));
    if (feof(trace))
      tracEof = true;
    else {
      MSG("QemuSescReader: Error while reading TraceFile");
      exit(1);
    }
  } 

  PC = qst->pc;

  MSG("PC 0x%x r%d <- r%d %u r%d",PC, qst->dest, qst->src1, qst->opc, qst->src2);

  if (feof(trace)) {
    tracEof = true; 
    closeTrace();
  }
      
}