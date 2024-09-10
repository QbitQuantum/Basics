bool
RilConsumer::PostRILMessage(JSContext* aCx, unsigned aArgc, Value* aVp)
{
  CallArgs args = CallArgsFromVp(aArgc, aVp);

  if (args.length() != 2) {
    JS_ReportError(aCx, "Expecting two arguments with the RIL message");
    return false;
  }

  int clientId = args[0].toInt32();

  if ((ssize_t)sRilConsumers.Length() <= clientId || !sRilConsumers[clientId]) {
    // Probably shutting down.
    return true;
  }

  nsresult rv = sRilConsumers[clientId]->Send(aCx, args);
  if (NS_FAILED(rv)) {
    return false;
  }

  return true;
}