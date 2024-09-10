int wmain(int argc, WCHAR* argv[])
{
	unique_winerror winerror;

#if 0
	LARGE_INTEGER frequency;
	(VOID)QueryPerformanceFrequency(&frequency);

	auto secBetween = [&](const LARGE_INTEGER& begin, const LARGE_INTEGER& end) -> double
	{
		return double(end.QuadPart - begin.QuadPart) / frequency.QuadPart;
	};
#endif

#if 0
	for (;;)
	{
		SCARDCONTEXT context = NULL;

		HANDLE waitfor[] = {SCardAccessStartedEvent()};
		ON_UNWIND_AUTO([] {SCardReleaseStartedEvent();});

		winerror = smart_card::monitor_smartcard_readers(
			[&](SCARDCONTEXT context)
			{
				context = context;
			},
			[&]()
			{
				context = NULL;
			},
			[&]() -> bool
			{
				if (WAIT_OBJECT_0 != WaitForMultipleObjects(lib::rng::size(waitfor), waitfor, FALSE, INFINITE))
				{
					// monitor_smardcard_readers will return SCARD_E_CANCELLED
					return false;
				}
				return true;
			},
			[&](lib::rng::range<SCARD_READERSTATE*> readersrange)
			{
				for (auto& state : readersrange)
				{
					auto stateChanges = (state.dwCurrentState ^ state.dwEventState) & std::numeric_limits<unsigned short>::max();
					std::wcout 
						<< L"nothread - "
						<< state.szReader
						<< L" changes: " << std::hex << std::showbase << stateChanges
						<< L"["
					;
					printSCardState(std::wcout, stateChanges)
						<< L"] state: " << std::hex << std::showbase << state.dwEventState
						<< L"["
					;
					printSCardState(std::wcout, state.dwEventState)
						<< L"]" 
						<< std::endl
					; 

					if (state.dwCurrentState != SCARD_STATE_UNAWARE && 
						((state.dwEventState & SCARD_STATE_PRESENT) != SCARD_STATE_PRESENT ||
						  stateChanges == SCARD_STATE_INUSE ||
						  stateChanges == SCARD_STATE_UNPOWERED ||
						  (state.dwEventState & (SCARD_STATE_UNPOWERED | SCARD_STATE_EMPTY | SCARD_STATE_IGNORE | SCARD_STATE_UNKNOWN | SCARD_STATE_UNAVAILABLE | SCARD_STATE_MUTE)) ||
						  state.cbAtr == 0))
					{
						// we have seen this reader before and one of:
						// no card
						// only flipped INUSE
						// only flipped UNPOWERED
						// UNPOWERED EMPTY UNKNOWN UNAVAILABLE MUTE
						// no atr
						//
						// don't try to read the card
						continue;
					}

					CardWithProvider card;
					std::tie(winerror, card) = smart_card::smartcard_name_and_provider(lib::rng::make_range_raw(state.rgbAtr));
					if (!winerror)
					{
						continue;
					}

					KeyWithCertificateVector certificates;
					std::tie(winerror, certificates) = smart_card::smartcard_certificates(card.kspname);
					if (!winerror)
					{
						continue;
					}

					std::wcout << L"nothread -"
						<< L" kspname: " << card.kspname.c_str()
						<< std::endl; 

					printCertificates(lib::rng::make_range_raw(certificates));
				}
			}
		);
		winerror.suppress();
	}
#endif

	smart_card::monitor_certificates monitor;

	for(;;)
	{
		HANDLE waitfor[] = {monitor.updates.getproducedevent()};
		if (WAIT_OBJECT_0 == WaitForMultipleObjects(lib::rng::size(waitfor), waitfor, FALSE, INFINITE))
		{
			auto update = monitor.updates.pop();

			for (auto& state : update)
			{
				unique_winerror winerror;

				std::wcout 
					<< L"Monitor #3 - "
					<< state.reader.c_str()
					<< L" changes: " << std::hex << std::showbase << state.changesinstate
					<< L"["
				;
				printSCardState(std::wcout, state.changesinstate)
					<< L"] state: " << std::hex << std::showbase << state.newstate
					<< L"["
				;
				printSCardState(std::wcout, state.newstate)
					<< L"]" 
					<< std::endl
				; 

				if (!state.card.valid())
				{
					continue;
				}

				auto card = state.card.get();

				std::wcout << L"Monitor #3 -"
					<< L" kspname: " << card.state.kspname.c_str()
					<< std::endl; 

				printCertificates(lib::rng::make_range_raw(card.certificates));
			}
			continue;
		}
	}
	return 0;
}