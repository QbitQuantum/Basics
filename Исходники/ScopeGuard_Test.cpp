void test_scope_guard()
{
	{
		int *pi = new int;
		ZL::ScopeGuard onExit([&] { delete pi; pi = nullptr; });
	}
	{
		SC *sc = new SC;
		ZL::ON_SCOPE_EXIT([&sc]{ delete sc; sc = nullptr; }); // Ok
		//ON_SCOPE_EXIT([&sc]{ Safe_Delete(sc) }); // Ok		
	}
	std::cout << "===================\n";
	{
		SC *sc = new SC;
		//ON_SCOPE_EXIT([&sc]{ Safe_Delete(sc) });
		ZL::ScopeGuard rollbackIfFail([&]{ sc->RollBack(); });
		do
		{
			//do something.....
			if (sc->Fail())
			{
				break;
			}
			rollbackIfFail.dismiss(); //上面if失败，走不到这里，因此会导致ScopeGuard执行sc的RollBack函数
		} while (0);
	}
	std::cout << "===================\n";
	{
		SC *sc = new SC(1);
		ZL::ON_SCOPE_EXIT([&sc]{ Safe_Delete(sc) });
		ZL::ScopeGuard rollbackIfFail([&]{ sc->RollBack(); });
		do
		{
			//do something.....
			if (!sc->Success())
			{
				break;
			}
			rollbackIfFail.dismiss(); //执行到这里，设置取消rollback机制，执行成功
		} while (0);
	}