void UIDebugSCUDSP::updateRegList()
{
   scudspregs_struct regs;
   QString str;

   if (ScuRegs == NULL)
      return;

   memset(&regs, 0, sizeof(regs));
   ScuDspGetRegisters(&regs);
   lwRegisters->clear();

   str.sprintf("PR = %d   EP = %d", regs.ProgControlPort.part.PR, regs.ProgControlPort.part.EP);
   lwRegisters->addItem(str);

   str.sprintf("T0 = %d   S =  %d", regs.ProgControlPort.part.T0, regs.ProgControlPort.part.S);
   lwRegisters->addItem(str);

   str.sprintf("Z =  %d   C =  %d", regs.ProgControlPort.part.Z, regs.ProgControlPort.part.C);
   lwRegisters->addItem(str);

   str.sprintf("V =  %d   E =  %d", regs.ProgControlPort.part.V, regs.ProgControlPort.part.E);
   lwRegisters->addItem(str);

   str.sprintf("ES = %d   EX = %d", regs.ProgControlPort.part.ES, regs.ProgControlPort.part.EX);
   lwRegisters->addItem(str);

   str.sprintf("LE =          %d", regs.ProgControlPort.part.LE);
   lwRegisters->addItem(str);

   str.sprintf("P =          %02X", regs.ProgControlPort.part.P);
   lwRegisters->addItem(str);

   str.sprintf("TOP =        %02X", regs.TOP);
   lwRegisters->addItem(str);

   str.sprintf("LOP =        %02X", regs.LOP);
   lwRegisters->addItem(str);

   str.sprintf("CT = %02X:%02X:%02X:%02X", regs.CT[0], regs.CT[1], regs.CT[2], regs.CT[3]);
   lwRegisters->addItem(str);

   str.sprintf("RA =   %08lX", regs.RA0);
   lwRegisters->addItem(str);

   str.sprintf("WA =   %08lX", regs.WA0);
   lwRegisters->addItem(str);

   str.sprintf("RX =   %08lX", regs.RX);
   lwRegisters->addItem(str);

   str.sprintf("RY =   %08lX", regs.RX);
   lwRegisters->addItem(str);

   str.sprintf("PH =       %04X", regs.P.part.H & 0xFFFF);
   lwRegisters->addItem(str);

   str.sprintf("PL =   %08X", (int)(regs.P.part.L & 0xFFFFFFFF));
   lwRegisters->addItem(str);

   str.sprintf("ACH =      %04X", regs.AC.part.H & 0xFFFF);
   lwRegisters->addItem(str);

   str.sprintf("ACL =  %08X", (int)(regs.AC.part.L & 0xFFFFFFFF));
   lwRegisters->addItem(str);
}