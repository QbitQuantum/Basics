//-----------------------------------------------------------------------------
// <OnNotification>
// Callback that is triggered when a value, group or node changes
//-----------------------------------------------------------------------------
void OnNotification
(
	Notification const* _notification,
	void* _context
)
{
	qpid::types::Variant::Map eventmap;
	// Must do this inside a critical section to avoid conflicts with the main thread
	pthread_mutex_lock( &g_criticalSection );

	switch( _notification->GetType() )
	{
		case Notification::Type_ValueAdded:
		{
			if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
			{
				// Add the new value to our list
				nodeInfo->m_values.push_back( _notification->GetValueID() );
				uint8 basic = Manager::Get()->GetNodeBasic(_notification->GetHomeId(),_notification->GetNodeId());
				uint8 generic = Manager::Get()->GetNodeGeneric(_notification->GetHomeId(),_notification->GetNodeId());
				uint8 specific = Manager::Get()->GetNodeSpecific(_notification->GetHomeId(),_notification->GetNodeId());
				ValueID id = _notification->GetValueID();
				string label = Manager::Get()->GetValueLabel(id);
				stringstream tempstream;
				tempstream << (int) _notification->GetNodeId();
				tempstream << "/";
				tempstream << (int) id.GetInstance();
				string nodeinstance = tempstream.str();
				tempstream << "-";
				tempstream << label;
				string tempstring = tempstream.str();
				ZWaveNode *device;
				if (basic == BASIC_TYPE_CONTROLLER) {
					if ((device = devices.findId(nodeinstance)) != NULL) {
						device->addValue(label, id);
						device->setDevicetype("remote");
					} else {
						device = new ZWaveNode(nodeinstance, "remote");	
						device->addValue(label, id);
						devices.add(device);
						agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
					}
				} else
				switch(id.GetCommandClassId()) {
					case COMMAND_CLASS_SWITCH_MULTILEVEL:
						if (label == "Level") {
							if ((device = devices.findId(nodeinstance)) != NULL) {
								device->addValue(label, id);
								device->setDevicetype("dimmer");
							} else {
								device = new ZWaveNode(nodeinstance, "dimmer");	
								device->addValue(label, id);
								devices.add(device);
								agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
							}
							// Manager::Get()->EnablePoll(id);
						}
					break;
					case COMMAND_CLASS_SWITCH_BINARY:
						if (label == "Switch") {
							if ((device = devices.findId(nodeinstance)) != NULL) {
								device->addValue(label, id);
							} else {
								device = new ZWaveNode(nodeinstance, "switch");	
								device->addValue(label, id);
								devices.add(device);
								agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
							}
							// Manager::Get()->EnablePoll(id);
						}
					break;
					case COMMAND_CLASS_SENSOR_BINARY:
						if (label == "Sensor") {
							if ((device = devices.findId(tempstring)) != NULL) {
								device->addValue(label, id);
							} else {
								device = new ZWaveNode(tempstring, "binarysensor");	
								device->addValue(label, id);
								devices.add(device);
								agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
							}
							// Manager::Get()->EnablePoll(id);
						}
					break;
					case COMMAND_CLASS_SENSOR_MULTILEVEL:
						if (label == "Luminance") {
							device = new ZWaveNode(tempstring, "brightnesssensor");	
							device->addValue(label, id);
							devices.add(device);
							agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
						} else if (label == "Temperature") {
							if (generic == GENERIC_TYPE_THERMOSTAT) {
								if ((device = devices.findId(nodeinstance)) != NULL) {
									device->addValue(label, id);
								} else {
									device = new ZWaveNode(nodeinstance, "thermostat");	
									device->addValue(label, id);
									devices.add(device);
									agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
								}
							} else {
								device = new ZWaveNode(tempstring, "temperaturesensor");	
								device->addValue(label, id);
								devices.add(device);
								agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
							}
						} else {
							printf("WARNING: unhandled label for SENSOR_MULTILEVEL: %s - adding generic multilevelsensor\n",label.c_str());
							if ((device = devices.findId(nodeinstance)) != NULL) {
								device->addValue(label, id);
							} else {
								device = new ZWaveNode(nodeinstance, "multilevelsensor");	
								device->addValue(label, id);
								devices.add(device);
								agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
							}
						}
						// Manager::Get()->EnablePoll(id);
					break;
					case COMMAND_CLASS_METER:
						if (label == "Power") {
							device = new ZWaveNode(tempstring, "powermeter");	
							device->addValue(label, id);
							devices.add(device);
							agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
						} else if (label == "Energy") {
							device = new ZWaveNode(tempstring, "energymeter");	
							device->addValue(label, id);
							devices.add(device);
							agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
						} else {
							printf("WARNING: unhandled label for CLASS_METER: %s - adding generic multilevelsensor\n",label.c_str());
							if ((device = devices.findId(nodeinstance)) != NULL) {
								device->addValue(label, id);
							} else {
								device = new ZWaveNode(nodeinstance, "multilevelsensor");	
								device->addValue(label, id);
								devices.add(device);
								agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
							}
						}
						// Manager::Get()->EnablePoll(id);
					break;
					case COMMAND_CLASS_BASIC_WINDOW_COVERING:
						// if (label == "Open") {
							if ((device = devices.findId(nodeinstance)) != NULL) {
								device->addValue(label, id);
								device->setDevicetype("drapes");
							} else {
								device = new ZWaveNode(nodeinstance, "drapes");	
								device->addValue(label, id);
								devices.add(device);
								agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
							}
							// Manager::Get()->EnablePoll(id);
					//	}
					break;
					case COMMAND_CLASS_THERMOSTAT_SETPOINT:
						if (polling) Manager::Get()->EnablePoll(id);
					case COMMAND_CLASS_THERMOSTAT_MODE:
					case COMMAND_CLASS_THERMOSTAT_FAN_MODE:
					case COMMAND_CLASS_THERMOSTAT_FAN_STATE:
					case COMMAND_CLASS_THERMOSTAT_OPERATING_STATE:
						cout << "adding thermostat label: " << label << endl;
						if ((device = devices.findId(nodeinstance)) != NULL) {
							device->addValue(label, id);
							device->setDevicetype("thermostat");
						} else {
							device = new ZWaveNode(nodeinstance, "thermostat");	
							device->addValue(label, id);
							devices.add(device);
							agoConnection->addDevice(device->getId().c_str(), device->getDevicetype().c_str());
						}
					break;
					default:
						printf("Notification: Unassigned Value Added Home 0x%08x Node %d Genre %d Class %x Instance %d Index %d Type %d - Label: %s\n", _notification->GetHomeId(), _notification->GetNodeId(), id.GetGenre(), id.GetCommandClassId(), id.GetInstance(), id.GetIndex(), id.GetType(),label.c_str());
						// printf("Notification: Unassigned Value Added Home 0x%08x Node %d Genre %d Class %x Instance %d Index %d Type %d - ID: %" PRIu64 "\n", _notification->GetHomeId(), _notification->GetNodeId(), id.GetGenre(), id.GetCommandClassId(), id.GetInstance(), id.GetIndex(), id.GetType(),id.GetId());

				}
			}
			break;
		}
		case Notification::Type_ValueRemoved:
		{
			if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
			{
				// Remove the value from out list
				for( list<ValueID>::iterator it = nodeInfo->m_values.begin(); it != nodeInfo->m_values.end(); ++it )
				{
					if( (*it) == _notification->GetValueID() )
					{
						nodeInfo->m_values.erase( it );
						break;
					}
				}
			}
			break;
		}

		case Notification::Type_ValueChanged:
		{
			if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
			{
				// One of the node values has changed
				// TBD...
				// nodeInfo = nodeInfo;
				ValueID id = _notification->GetValueID();
				string str;
				printf("Notification: Value Changed Home 0x%08x Node %d Genre %d Class %d Instance %d Index %d Type %d\n", _notification->GetHomeId(), _notification->GetNodeId(), id.GetGenre(), id.GetCommandClassId(), id.GetInstance(), id.GetIndex(), id.GetType());
			      if (Manager::Get()->GetValueAsString(id, &str)) {
					qpid::types::Variant cachedValue;
					cachedValue.parse(str);
					valueCache[id] = cachedValue;
					string label = Manager::Get()->GetValueLabel(id);
					string units = Manager::Get()->GetValueUnits(id);

					// TODO: send proper types and don't convert everything to string
					string level = str;
					string eventtype = "";
					if (str == "True") level="255";
					if (str == "False") level="0";
					printf("Value: %s Label: %s Unit: %s\n",str.c_str(),label.c_str(),units.c_str());
					if ((label == "Basic") || (label == "Switch") || (label == "Level")) {
						eventtype="event.device.statechanged";
					}
					if (label == "Luminance") {
						eventtype="event.environment.brightnesschanged";
					}
					if (label == "Temperature") {
						eventtype="event.environment.temperaturechanged";
						if (units=="F" && unitsystem==0) {
							units="C";
							str = float2str((atof(str.c_str())-32)*5/9);
							level = str;
						} else if (units =="C" && unitsystem==1) {
							units="F";
							str = float2str(atof(str.c_str())*9/5 + 32);
							level = str;
						}
					}
					if (label == "Relative Humidity") {
						eventtype="event.environment.humiditychanged";
					}
					if (label == "Battery Level") {
						eventtype="event.device.batterylevelchanged";
					}
					if (label == "Alarm Level") {
						eventtype="event.security.alarmlevelchanged";
					}
					if (label == "Alarm Type") {
						eventtype="event.security.alarmtypechanged";
					}
					if (label == "Sensor") {
						eventtype="event.security.sensortriggered";
					}
					if (label == "Energy") {
						eventtype="event.environment.energychanged";
					}
					if (label == "Power") {
						eventtype="event.environment.powerchanged";
					}
					if (label == "Mode") {
						eventtype="event.environment.modechanged";
					}
					if (label == "Fan Mode") {
						eventtype="event.environment.fanmodechanged";
					}
					if (label == "Fan State") {
						eventtype="event.environment.fanstatechanged";
					}
					if (label == "Operating State") {
						eventtype="event.environment.operatingstatechanged";
					}
					if (label == "Cooling 1") {
						eventtype="event.environment.coolsetpointchanged";
					}
					if (label == "Heating 1") {
						eventtype="event.environment.heatsetpointchanged";
					}
					if (label == "Fan State") {
						eventtype="event.environment.fanstatechanged";
					}
					if (eventtype != "") {	
						ZWaveNode *device = devices.findValue(id);
						if (device != NULL) {
							if (debug) printf("Sending %s event from child %s\n",eventtype.c_str(), device->getId().c_str());
							agoConnection->emitEvent(device->getId().c_str(), eventtype.c_str(), level.c_str(), units.c_str());	
						}
					}
				}
			}
			break;
		}
		case Notification::Type_Group:
		{
			if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
			{
				// One of the node's association groups has changed
				// TBD...
				nodeInfo = nodeInfo;
				eventmap["description"]="Node association added";
				eventmap["state"]="associationchanged";
				eventmap["nodeid"] = _notification->GetNodeId();
				eventmap["homeid"] = _notification->GetHomeId();
				agoConnection->emitEvent("zwavecontroller", "event.zwave.associationchanged", eventmap);
			}
			break;
		}

		case Notification::Type_NodeAdded:
		{
			// Add the new node to our list
			NodeInfo* nodeInfo = new NodeInfo();
			nodeInfo->m_homeId = _notification->GetHomeId();
			nodeInfo->m_nodeId = _notification->GetNodeId();
			nodeInfo->m_polled = false;		
			g_nodes.push_back( nodeInfo );

			// todo: announce node
			eventmap["description"]="Node added";
			eventmap["state"]="nodeadded";
			eventmap["nodeid"] = _notification->GetNodeId();
			eventmap["homeid"] = _notification->GetHomeId();
			agoConnection->emitEvent("zwavecontroller", "event.zwave.networkchanged", eventmap);
			break;
		}

		case Notification::Type_NodeRemoved:
		{
			// Remove the node from our list
			uint32 const homeId = _notification->GetHomeId();
			uint8 const nodeId = _notification->GetNodeId();
			eventmap["description"]="Node removed";
			eventmap["state"]="noderemoved";
			eventmap["nodeid"] = _notification->GetNodeId();
			eventmap["homeid"] = _notification->GetHomeId();
			agoConnection->emitEvent("zwavecontroller", "event.zwave.networkchanged", eventmap);
			for( list<NodeInfo*>::iterator it = g_nodes.begin(); it != g_nodes.end(); ++it )
			{
				NodeInfo* nodeInfo = *it;
				if( ( nodeInfo->m_homeId == homeId ) && ( nodeInfo->m_nodeId == nodeId ) )
				{
					g_nodes.erase( it );
					break;
				}
			}
			break;
		}

		case Notification::Type_NodeEvent:
		{
			if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
			{
				// We have received an event from the node, caused by a
				// basic_set or hail message.
				ValueID id = _notification->GetValueID();
				string label = Manager::Get()->GetValueLabel(id);
				stringstream level;
				level << (int) _notification->GetByte();
				string eventtype = "event.device.statechanged";
				ZWaveNode *device = devices.findValue(id);
				if (device != NULL) {
					if (debug) printf("Sending %s event from child %s\n",eventtype.c_str(), device->getId().c_str());
					agoConnection->emitEvent(device->getId().c_str(), eventtype.c_str(), level.str().c_str(), "");	
				} else {
					cout << "no agocontrol device found for node event - Label: " << label << " Level: " << level << endl;
				}

			}
			break;
		}
		case Notification::Type_SceneEvent:
		{
			if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
			{
				int scene = _notification->GetSceneId();
				ValueID id = _notification->GetValueID();
                                string label = Manager::Get()->GetValueLabel(id);
                                stringstream tempstream;
                                tempstream << (int) _notification->GetNodeId();
                                tempstream << "/1";
                                string nodeinstance = tempstream.str();
				string eventtype = "event.device.statechanged";
				ZWaveNode *device;
				if ((device = devices.findId(nodeinstance)) != NULL) {
					if (debug) printf("Sending %s for scene %d event from child %s\n",
						  eventtype.c_str(), scene, device->getId().c_str());
					agoConnection->emitEvent(device->getId().c_str(), eventtype.c_str(), scene, "");	
				} else {
					cout << "WARNING: no agocontrol device found for scene event" << endl;
					cout << "Node: " << nodeinstance << " Scene: " << scene << endl;
				}

			}
			break;
		}
		case Notification::Type_PollingDisabled:
		{
			if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
			{
				nodeInfo->m_polled = false;
			}
			break;
		}

		case Notification::Type_PollingEnabled:
		{
			if( NodeInfo* nodeInfo = GetNodeInfo( _notification ) )
			{
				nodeInfo->m_polled = true;
			}
			break;
		}

		case Notification::Type_DriverReady:
		{
			g_homeId = _notification->GetHomeId();
			break;
		}


		case Notification::Type_DriverFailed:
		{
			g_initFailed = true;
			pthread_cond_broadcast(&initCond);
			break;
		}

		case Notification::Type_AwakeNodesQueried:
		case Notification::Type_AllNodesQueried:
		case Notification::Type_AllNodesQueriedSomeDead:
		{
			pthread_cond_broadcast(&initCond);
			break;
		}
		case Notification::Type_DriverReset:
		case Notification::Type_Notification:
		case Notification::Type_NodeNaming:
		case Notification::Type_NodeProtocolInfo:
		case Notification::Type_NodeQueriesComplete:
		case Notification::Type_EssentialNodeQueriesComplete:
		{
			break;
		}
		default:
		{
			cout << "WARNING: Unhandled OpenZWave Event: " << _notification->GetType() << endl;
		}
	}

	pthread_mutex_unlock( &g_criticalSection );
}