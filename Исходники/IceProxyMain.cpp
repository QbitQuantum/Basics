//---------------------------------------------------------------------------
__fastcall TQRigSyncMain::TQRigSyncMain(TComponent* Owner)
   : TForm(Owner), muted(false)
{
   enableTrace( ".\\TraceLog\\QS1RProxy_" );
   try
   {
      int args = 0;
      ic = Ice::initialize(args, _argv);
      Ice::ObjectPrx base = ic->stringToProxy(
            "RadioCommander:default -t 2000 -h opti -p 43065");
      qs1r = QS1R::RadioCommanderPrx::checkedCast(base);
      if (!qs1r)
         throw "Invalid proxy";
      Timer1->Enabled = true;
   }
   catch (const Ice::Exception& ex)
   {
      ShowMessage(ex.what());
   }
   catch (const char* msg)
   {
      ShowMessage(msg);
   }
}