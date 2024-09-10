//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InsertUIKey
//Author		Jim Taylor
//Date			Tue 30 Jan 1996
//
//Description	insert a key press/release event into the key queue
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	keytests::InsertUIKey(UIKeyNoMouse& keyfake)
{
UIKeyQueue*
	keyqueue=(UIKeyQueue*)	hitqueueui.flat;
	{	_disable();
int		oldadd=keyqueue->addref;
int		addref=oldadd+1;

		if (addref==keyqueue->queuesize)
		{
			addref=0;
		}
		if (addref==keyqueue->takeref)
		{
			_enable();											//JIM 21Oct96
			return;
		}
		keyqueue->keyqueue[oldadd].keycode=keyfake.keycode;
		keyqueue->keyqueue[oldadd].keyhit=keyfake.keyhit;
		if (keyfake.keyshifts)
			keyqueue->keyqueue[oldadd].keyshifts=keyfake.keyshifts;
		else
			keyqueue->keyqueue[oldadd].keyshifts=keyqueue->currshifts;
		keyqueue->keyqueue[oldadd].mousecoords=keyqueue->currmouse;
		keyqueue->addref=addref;
	}	_enable();
}