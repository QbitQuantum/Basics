void __fastcall TfrmMain::BroadcastMessage(AnsiString WhoFrom, AnsiString TheMessage   )
{
 int Count;
 TList* List;
 TIdPeerThread * peerthread;
 AnsiString EMote;
 AnsiString Msg;

 Msg = Trim(TheMessage);

 EMote = Trim(memEMotes->Lines->Values[Msg]);

  if (WhoFrom != "System")
    Msg = WhoFrom + ": " + Msg;

  if (EMote != "")
    Msg = Msg.sprintf(EMote.c_str(),WhoFrom.c_str());

  List = tcpServer->Threads->LockList();

  for (Count = 0;Count < List->Count ;Count++)
     {peerthread=(TIdPeerThread*)List->Items[Count];
      if (dynamic_cast <TIdPeerThread*>(peerthread))
      peerthread->Connection->WriteLn(Msg);
     }
  tcpServer->Threads->UnlockList();
}