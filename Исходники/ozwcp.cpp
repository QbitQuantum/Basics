//-----------------------------------------------------------------------------
// <OnNotification>
// Callback that is triggered when a value, group or node changes
//-----------------------------------------------------------------------------
void OnNotification (Notification const* _notification, void* _context)
{
	ValueID id = _notification->GetValueID();
	switch (_notification->GetType()) {
		case Notification::Type_ValueAdded:
			Log::Write(LogLevel_Info, "Notification: Value Added Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			pthread_mutex_lock(&nlock);
			nodes[_notification->GetNodeId()]->addValue(id);
			nodes[_notification->GetNodeId()]->setTime(time(NULL));
			nodes[_notification->GetNodeId()]->setChanged(true);
			pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_ValueRemoved:
			Log::Write(LogLevel_Info, "Notification: Value Removed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			pthread_mutex_lock(&nlock);
			nodes[_notification->GetNodeId()]->removeValue(id);
			nodes[_notification->GetNodeId()]->setTime(time(NULL));
			nodes[_notification->GetNodeId()]->setChanged(true);
			pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_ValueChanged:
			Log::Write(LogLevel_Info, "Notification: Value Changed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			pthread_mutex_lock(&nlock);
			nodes[_notification->GetNodeId()]->saveValue(id);
			pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_ValueRefreshed:
			Log::Write(LogLevel_Info, "Notification: Value Refreshed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			pthread_mutex_lock(&nlock);
			nodes[_notification->GetNodeId()]->setTime(time(NULL));
			nodes[_notification->GetNodeId()]->setChanged(true);
			pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_Group:
		{
			Log::Write(LogLevel_Info, "Notification: Group Home 0x%08x Node %d Group %d",
					_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetGroupIdx());
			uint8 *v = NULL;
			int8 n = Manager::Get()->GetAssociations(homeId, _notification->GetNodeId(), _notification->GetGroupIdx(), &v);
			pthread_mutex_lock(&nlock);
			nodes[_notification->GetNodeId()]->addGroup(_notification->GetNodeId(), _notification->GetGroupIdx(), n, v);
			pthread_mutex_unlock(&nlock);
			if (v != NULL)
				delete [] v;
		}
		break;
		case Notification::Type_NodeNew:
			Log::Write(LogLevel_Info, "Notification: Node New Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			pthread_mutex_lock(&glock);
			needsave = true;
			pthread_mutex_unlock(&glock);
			break;
		case Notification::Type_NodeAdded:
			Log::Write(LogLevel_Info, "Notification: Node Added Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			pthread_mutex_lock(&nlock);
			new MyNode(_notification->GetNodeId());
			pthread_mutex_unlock(&nlock);
			pthread_mutex_lock(&glock);
			needsave = true;
			pthread_mutex_unlock(&glock);
			break;
		case Notification::Type_NodeRemoved:
			Log::Write(LogLevel_Info, "Notification: Node Removed Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			pthread_mutex_lock(&nlock);
			MyNode::remove(_notification->GetNodeId());
			pthread_mutex_unlock(&nlock);
			pthread_mutex_lock(&glock);
			needsave = true;
			pthread_mutex_unlock(&glock);
			break;
		case Notification::Type_NodeProtocolInfo:
			Log::Write(LogLevel_Info, "Notification: Node Protocol Info Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			pthread_mutex_lock(&nlock);
			nodes[_notification->GetNodeId()]->saveValue(id);
			pthread_mutex_unlock(&nlock);
			pthread_mutex_lock(&glock);
			needsave = true;
			pthread_mutex_unlock(&glock);
			break;
		case Notification::Type_NodeNaming:
			Log::Write(LogLevel_Info, "Notification: Node Naming Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			pthread_mutex_lock(&nlock);
			nodes[_notification->GetNodeId()]->saveValue(id);
			pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_NodeEvent:
			Log::Write(LogLevel_Info, "Notification: Node Event Home %08x Node %d Status %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetEvent(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			pthread_mutex_lock(&nlock);
			nodes[_notification->GetNodeId()]->saveValue(id);
			pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_PollingDisabled:
			Log::Write(LogLevel_Info, "Notification: Polling Disabled Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			//pthread_mutex_lock(&nlock);
			//nodes[_notification->GetNodeId()]->setPolled(false);
			//pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_PollingEnabled:
			Log::Write(LogLevel_Info, "Notification: Polling Enabled Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()));
			//pthread_mutex_lock(&nlock);
			//nodes[_notification->GetNodeId()]->setPolled(true);
			//pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_SceneEvent:
			Log::Write(LogLevel_Info, "Notification: Scene Event Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s Scene Id %d",
					_notification->GetHomeId(), _notification->GetNodeId(),
					valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
					id.GetIndex(), valueTypeStr(id.GetType()), _notification->GetSceneId());
			break;
		case Notification::Type_CreateButton:
			Log::Write(LogLevel_Info, "Notification: Create button Home %08x Node %d Button %d",
					_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetButtonId());
			break;
		case Notification::Type_DeleteButton:
			Log::Write(LogLevel_Info, "Notification: Delete button Home %08x Node %d Button %d",
					_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetButtonId());
			break;
		case Notification::Type_ButtonOn:
			Log::Write(LogLevel_Info, "Notification: Button On Home %08x Node %d Button %d",
					_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetButtonId());
			break;
		case Notification::Type_ButtonOff:
			Log::Write(LogLevel_Info, "Notification: Button Off Home %08x Node %d Button %d",
					_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetButtonId());
			break;
		case Notification::Type_DriverReady:
			Log::Write(LogLevel_Info, "Notification: Driver Ready, homeId %08x, nodeId %d", _notification->GetHomeId(),
					_notification->GetNodeId());
			pthread_mutex_lock(&glock);
			homeId = _notification->GetHomeId();
			nodeId = _notification->GetNodeId();
			if (Manager::Get()->IsStaticUpdateController(homeId)) {
				cmode = "SUC";
				SUCnodeId = Manager::Get()->GetSUCNodeId(homeId);
			} else if (Manager::Get()->IsPrimaryController(homeId))
				cmode = "Primary";
			else
				cmode = "Slave";
			pthread_mutex_unlock(&glock);
			break;
		case Notification::Type_DriverFailed:
			Log::Write(LogLevel_Info, "Notification: Driver Failed, homeId %08x", _notification->GetHomeId());
			pthread_mutex_lock(&glock);
			done = false;
			needsave = false;
			homeId = 0;
			cmode = "";
			pthread_mutex_unlock(&glock);
			pthread_mutex_lock(&nlock);
			for (int i = 1; i < MAX_NODES; i++)
				MyNode::remove(i);
			pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_DriverReset:
			Log::Write(LogLevel_Info, "Notification: Driver Reset, homeId %08x", _notification->GetHomeId());
			pthread_mutex_lock(&glock);
			done = false;
			needsave = true;
			homeId = _notification->GetHomeId();
			if (Manager::Get()->IsStaticUpdateController(homeId)) {
				cmode = "SUC";
				SUCnodeId = Manager::Get()->GetSUCNodeId(homeId);
			} else if (Manager::Get()->IsPrimaryController(homeId))
				cmode = "Primary";
			else
				cmode = "Slave";
			pthread_mutex_unlock(&glock);
			pthread_mutex_lock(&nlock);
			for (int i = 1; i < MAX_NODES; i++)
				MyNode::remove(i);
			pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_EssentialNodeQueriesComplete:
			Log::Write(LogLevel_Info, "Notification: Essential Node %d Queries Complete", _notification->GetNodeId());
			pthread_mutex_lock(&nlock);
			nodes[_notification->GetNodeId()]->setTime(time(NULL));
			nodes[_notification->GetNodeId()]->setChanged(true);
			pthread_mutex_unlock(&nlock);
			break;
		case Notification::Type_NodeQueriesComplete:
			Log::Write(LogLevel_Info, "Notification: Node %d Queries Complete", _notification->GetNodeId());
			pthread_mutex_lock(&nlock);
			nodes[_notification->GetNodeId()]->sortValues();
			nodes[_notification->GetNodeId()]->setTime(time(NULL));
			nodes[_notification->GetNodeId()]->setChanged(true);
			pthread_mutex_unlock(&nlock);
			pthread_mutex_lock(&glock);
			needsave = true;
			pthread_mutex_unlock(&glock);
			break;
		case Notification::Type_AwakeNodesQueried:
			Log::Write(LogLevel_Info, "Notification: Awake Nodes Queried");
			break;
		case Notification::Type_AllNodesQueriedSomeDead:
			Log::Write(LogLevel_Info, "Notification: Awake Nodes Queried Some Dead");
			break;
		case Notification::Type_AllNodesQueried:
			Log::Write(LogLevel_Info, "Notification: All Nodes Queried");
			break;
		case Notification::Type_Notification:
			switch (_notification->GetNotification()) {
				case Notification::Code_MsgComplete:
					Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Message Complete",
							_notification->GetHomeId(), _notification->GetNodeId());
					break;
				case Notification::Code_Timeout:
					Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Timeout",
							_notification->GetHomeId(), _notification->GetNodeId());
					break;
				case Notification::Code_NoOperation:
					Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d No Operation Message Complete",
							_notification->GetHomeId(), _notification->GetNodeId());
					pthread_mutex_lock(&glock);
					noop = true;
					pthread_mutex_unlock(&glock);
					break;
				case Notification::Code_Awake:
					Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Awake",
							_notification->GetHomeId(), _notification->GetNodeId());
					pthread_mutex_lock(&nlock);
					nodes[_notification->GetNodeId()]->setTime(time(NULL));
					nodes[_notification->GetNodeId()]->setChanged(true);
					pthread_mutex_unlock(&nlock);
					break;
				case Notification::Code_Sleep:
					Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Sleep",
							_notification->GetHomeId(), _notification->GetNodeId());
					pthread_mutex_lock(&nlock);
					nodes[_notification->GetNodeId()]->setTime(time(NULL));
					nodes[_notification->GetNodeId()]->setChanged(true);
					pthread_mutex_unlock(&nlock);
					break;
				case Notification::Code_Dead:
					Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Dead",
							_notification->GetHomeId(), _notification->GetNodeId());
					pthread_mutex_lock(&nlock);
					nodes[_notification->GetNodeId()]->setTime(time(NULL));
					nodes[_notification->GetNodeId()]->setChanged(true);
					pthread_mutex_unlock(&nlock);
					break;
				default:
					Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Unknown %d",
							_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
					break;
			}
			break;
			case Notification::Type_ControllerCommand:
				Log::Write(LogLevel_Info, "Notification: ControllerCommand home %08x Event %d Error %d",
						_notification->GetHomeId(), _notification->GetEvent(), _notification->GetNotification());
				pthread_mutex_lock(&nlock);
				web_controller_update((OpenZWave::Driver::ControllerState)_notification->GetEvent(), (OpenZWave::Driver::ControllerError)_notification->GetNotification(), (void *)_context);
				pthread_mutex_unlock(&nlock);
				break;
			default:
					Log::Write(LogLevel_Info, "Notification: type %d home %08x node %d genre %d class %d instance %d index %d type %d",
							_notification->GetType(), _notification->GetHomeId(),
							_notification->GetNodeId(), id.GetGenre(), id.GetCommandClassId(),
							id.GetInstance(), id.GetIndex(), id.GetType());
					break;
	}
}