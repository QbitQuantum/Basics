Boolean Groupsock::output(UsageEnvironment& env, unsigned char* buffer, unsigned bufferSize,
			  DirectedNetInterface* interfaceNotToFwdBackTo) {
  do {
    // First, do the datagram send, to each destination:
    Boolean writeSuccess = True;
    for (destRecord* dests = fDests; dests != NULL; dests = dests->fNext) {
      if (!write(dests->fGroupEId.groupAddress().s_addr, dests->fGroupEId.portNum(), dests->fGroupEId.ttl(),
		 buffer, bufferSize)) {
	writeSuccess = False;
	break;
      }
    }
    if (!writeSuccess) break;
    statsOutgoing.countPacket(bufferSize);
    statsGroupOutgoing.countPacket(bufferSize);

    // Then, forward to our members:
    int numMembers = 0;
    if (!members().IsEmpty()) {
      numMembers =
	outputToAllMembersExcept(interfaceNotToFwdBackTo,
				 ttl(), buffer, bufferSize,
				 ourIPAddress(env));
      if (numMembers < 0) break;
    }

    if (DebugLevel >= 3) {
      env << *this << ": wrote " << bufferSize << " bytes, ttl " << (unsigned)ttl();
      if (numMembers > 0) {
	env << "; relayed to " << numMembers << " members";
      }
      env << "\n";
    }
    return True;
  } while (0);

  if (DebugLevel >= 0) { // this is a fatal error
    UsageEnvironment::MsgString msg = strDup(env.getResultMsg());
    env.setResultMsg("Groupsock write failed: ", msg);
    delete[] (char*)msg;
  }
  return False;
}