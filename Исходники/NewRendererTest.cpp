//---- NewRendererTest ----------------------------------------------------------------
void NewRendererTest::TestCases() {
	StartTrace(NewRendererTest.TestCases);

	if (t_assertm( !GetTestCaseConfig().IsNull(), "no Tests configured!" )) {
		Server *theServer = Server::FindServer("Server");
		t_assert(theServer != NULL);
		Context ctx;
		Session theSession("TestSession");
		Page *thePage = Page::FindPage("TestPage");
		t_assert(thePage != NULL);
		Role *theRole = Role::FindRole("TestRole");
		t_assert(theRole != NULL);
		theSession.Init("TestSession", ctx);

		AnyExtensions::Iterator<ROAnything, ROAnything, TString> aEntryIterator(GetTestCaseConfig());
		ROAnything roaCaseConfig;
		t_assertm( GetConfig()["RunOnly"].GetSize() == 0L, "running only subset of tests");
		TraceAny(GetConfig()["RunOnly"], "run only config")
		while (aEntryIterator.Next(roaCaseConfig)) {
			TString slotToCheck;
			aEntryIterator.SlotName(slotToCheck);
			Trace("current testslot [" << slotToCheck << "]");
			if ((GetConfig()["RunOnly"].GetSize() == 0L) || GetConfig()["RunOnly"].Contains((const char *) slotToCheck)) {
				std::cerr << ".";
				TString message;
				message << getConfigFileName() << ".any:0 at " << name();
				if (slotToCheck.Length()) {
					message << "." << slotToCheck;
				} else {
					message << ":" << aEntryIterator.Index();
				}
				Context c(GetConfig()["EnvForAllCases"].DeepClone(), roaCaseConfig["Env"].DeepClone(), theServer, &theSession, theRole,
						thePage);
				coast::testframework::PutInStore(roaCaseConfig["TmpStore"], c.GetTmpStore());
				coast::testframework::PutInStore(roaCaseConfig["SessionStore"], c.GetSessionStore());
				TraceAny(roaCaseConfig["Renderer"], "running renderer at [" << slotToCheck << "]");
				String result("[");
				String expected("[");
				expected << roaCaseConfig["Expected"].AsCharPtr("") << "]";
				{
					OStringStream reply(result);
					Renderer::Render(reply, c, roaCaseConfig["Renderer"]);
					reply.flush();
				}
				result.Append(']');
				// message << ":\n" << result;
				assertEqualm(expected, result, message);
			}
		}
	}