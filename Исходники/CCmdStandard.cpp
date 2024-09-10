TInt CCmdExit::ProcessL(const TDesC &aCommand)
{
// Complete the test machine - will then get the next cmd
Machine()->CompleteRequest();

TPtrC param;
TRAPD(error, param.Set(ParamsL(aCommand)));
if (error != KErrNone )
	return Error(error, TFR_KFmtErrBadCmd, &Keyphrase());

TLex parse( param );
if (!parse.Eos() && !parse.Peek().IsSpace())
	return Error( error, TFR_KFmtErrBadCmd, &Keyphrase());

// Print out param if any and stop.
param.Set( TfrLex::Peel(param));
if (param.Length() > 0) 
	Print(param);

Machine()->StopEngine();
return error;
}