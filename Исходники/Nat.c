// Management thread
void NiAdminThread(THREAD *thread, void *param)
{
	NAT_ADMIN *a = (NAT_ADMIN *)param;
	NAT *n;
	SOCK *s;
	UCHAR random[SHA1_SIZE];
	UINT err;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	// Random number generation
	Rand(random, sizeof(random));

	a->Thread = thread;
	AddRef(a->Thread->ref);
	s = a->Sock;
	AddRef(s->ref);

	n = a->Nat;

	LockList(n->AdminList);
	{
		Add(n->AdminList, a);
	}
	UnlockList(n->AdminList);

	NoticeThreadInit(thread);

	err = ERR_AUTH_FAILED;

	if (StartSSL(s, n->AdminX, n->AdminK))
	{
		PACK *p;

		// Send the random number
		p = NewPack();
		PackAddData(p, "auth_random", random, sizeof(random));

		if (HttpServerSend(s, p))
		{
			PACK *p;
			// Receive a password
			p = HttpServerRecv(s);
			if (p != NULL)
			{
				UCHAR secure_password[SHA1_SIZE];
				UCHAR secure_check[SHA1_SIZE];

				if (PackGetData2(p, "secure_password", secure_password, sizeof(secure_password)))
				{
					SecurePassword(secure_check, n->HashedPassword, random);

					if (Cmp(secure_check, secure_password, SHA1_SIZE) == 0)
					{
						UCHAR test[SHA1_SIZE];
						// Password match
						Hash(test, "", 0, true);
						SecurePassword(test, test, random);

#if	0
						if (Cmp(test, secure_check, SHA1_SIZE) == 0 && s->RemoteIP.addr[0] != 127)
						{
							// A client can not connect from the outside with blank password
							err = ERR_NULL_PASSWORD_LOCAL_ONLY;
						}
						else
#endif

						{
							// Successful connection
							err = ERR_NO_ERROR;
							NiAdminMain(n, s);
						}
					}
				}

				FreePack(p);
			}
		}

		FreePack(p);

		if (err != ERR_NO_ERROR)
		{
			p = PackError(err);
			HttpServerSend(s, p);
			FreePack(p);
		}
	}

	Disconnect(s);
	ReleaseSock(s);
}