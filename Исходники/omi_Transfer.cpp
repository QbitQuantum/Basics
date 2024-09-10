/**
 * Generates a simulation result message containing all variables and parameters from the filter mask
 * and sends the string to a server via message parsing and tcp/ip
 */
int sendMessageToClientGUI(long nStates, long nAlgebraic, long nParameters) {

  bool retValue = true;

  string resultMessage = createResultMessageWithNames(nStates, nAlgebraic, nParameters);

  if (debugTransfer)
  {
         cout << resultMessage << endl; fflush(stdout);
  }

  /*
   * Sends the simulation result data string to a server
   */
  transfer_client_socket.send(resultMessage);

  return retValue;
}