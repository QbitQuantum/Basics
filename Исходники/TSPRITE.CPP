/**
@SYMTestCaseID		GRAPHICS-WSERV-GCE-0700

@SYMDEF  			DEF123129

@SYMTestCaseDesc    Test activating a sprite twice does not cause the system to hang

@SYMTestPriority    High

@SYMTestStatus      Implemented

@SYMTestActions     Construct a sprite and add a member to it. Activate twice.

@SYMTestExpectedResults The test should terminate smoothly and it should not hang the system.
*/
void CTTSprite::DoubleActivateL()
	{
	RWsSession ws;
	User::LeaveIfError(ws.Connect());
	CleanupClosePushL(ws);
	
	RWindowGroup group(ws);
	User::LeaveIfError(group.Construct(890, EFalse));
	CleanupClosePushL(group);
	
	RWsSprite sprite = RWsSprite(ws);
	User::LeaveIfError(sprite.Construct(group,TPoint(),0));
	CleanupClosePushL(sprite);
	CFbsBitmap* bitmap=new(ELeave) CFbsBitmap;
	CleanupStack::PushL(bitmap);
	User::LeaveIfError(bitmap->Create(TSize(10,12),EColor256));
	TSpriteMember member;
	member.iMaskBitmap=NULL;
	member.iInvertMask=EFalse;
	member.iDrawMode=CGraphicsContext::EDrawModePEN;
	member.iOffset=TPoint();
	member.iInterval=TTimeIntervalMicroSeconds32(0);
	member.iBitmap=bitmap;
	User::LeaveIfError(sprite.AppendMember(member));
	User::LeaveIfError(sprite.Activate());
	User::LeaveIfError(sprite.Activate());
	
	sprite.Close();
	CleanupStack::PopAndDestroy(4, &ws);
	
	group.Close();
	ws.Close();
	}