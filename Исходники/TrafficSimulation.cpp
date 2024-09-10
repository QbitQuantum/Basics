void TrafficSimulation::update() {

    networkDataMutex.lock();

    // Update the position of the player to be send to the server
    if (player != NULL) {

        // Move the vehicle
        Value vehicle;
        vehicle["id"] = 0;

        Value pos;

        Vec3f worldPosition = player->getFrom();
        pos[0u] = worldPosition[0];
        pos[1]  = worldPosition[1];
        pos[2]  = worldPosition[2];
        vehicle["pos"] = pos;

        // Pack as the requested array entry
        dataToSend["moveVehicles"][0] = vehicle;
    }

    if (!receivedData.isNull()) {
        //cout << "Received data\n";

        // New data received per network. Update the positions of vehicles and the states of traffic lights

        // A set which contains the IDs of the currently existing vehicles.
        // If data for one of those is received, the entry in the set will be removed.
        // All vehicles that are in the set after the loop finished are no longer in the
        // area and can be deleted.
        set<uint> vehicleIDs;
        for (auto iter : vehicles) vehicleIDs.insert(iter.first);

        if (!receivedData["vehicles"].isNull() && receivedData["vehicles"].isArray()) {
            // Update the vehicles

            //cout << "Received vehicles " << receivedData["vehicles"].size();

            // A set for possible collisions
            // Add them all to the set and resolve them later on to avoid doubled checks
            set< pair<unsigned int, unsigned int> > collisions;

            // Sleeps for 10ms each tick, but the send deltas are for one second
            // Use only a part of them to avoid moving too fast
            static const float partDelta = 10 / 1000;

            for (auto vehicleIter : receivedData["vehicles"]) {
                // Check if the values have valid types
                if (!vehicleIter["id"].isConvertibleTo(uintValue)
                 || !vehicleIter["pos"].isConvertibleTo(arrayValue)
                 || !vehicleIter["pos"][0].isConvertibleTo(realValue)
                 || !vehicleIter["pos"][1].isConvertibleTo(realValue)
                 || !vehicleIter["pos"][2].isConvertibleTo(realValue)
                 || !vehicleIter["dPos"].isConvertibleTo(arrayValue)
                 || !vehicleIter["dPos"][0].isConvertibleTo(realValue)
                 || !vehicleIter["dPos"][1].isConvertibleTo(realValue)
                 || !vehicleIter["dPos"][2].isConvertibleTo(realValue)
                 || !vehicleIter["angle"].isConvertibleTo(arrayValue)
                 || !vehicleIter["angle"][0].isConvertibleTo(realValue)
                 || !vehicleIter["angle"][1].isConvertibleTo(realValue)
                 || !vehicleIter["angle"][2].isConvertibleTo(realValue)
                 || !vehicleIter["dAngle"].isConvertibleTo(arrayValue)
                 || !vehicleIter["dAngle"][0].isConvertibleTo(realValue)
                 || !vehicleIter["dAngle"][1].isConvertibleTo(realValue)
                 || !vehicleIter["dAngle"][2].isConvertibleTo(realValue)) {
                    cout << "TrafficSimulation: Warning: Received invalid vehicle data.\n";
                    continue;
                }

                uint ID = vehicleIter["id"].asUInt();

                if (vehicles.count(ID) == 0) { // The vehicle is new, create it
                    if (!vehicleIter["vehicle"].isConvertibleTo(uintValue)
                     || !vehicleIter["driver"].isConvertibleTo(uintValue)) {
                        cout << "TrafficSimulation: Warning: Received invalid vehicle data.\n";
                        continue;
                    }

                    uint vID = vehicleIter["vehicle"].asUInt();
                    if (meshes.count(vID) == 0) {
                        // If it is bigger than 500 it is our user-controlled vehicle
                        if (vID < 500) cout << "TrafficSimulation: Warning: Received unknown vehicle type " << vID << ".\n";
                        continue;
                    }

                    Vehicle v;

                    v.id = ID;
                    v.vehicleTypeId = vID;
                    v.driverTypeId = vehicleIter["driver"].asUInt();

                    if (meshes.count(v.vehicleTypeId) == 0) v.vehicleTypeId = 404;
                    v.geometry = (VRGeometry*)meshes[v.vehicleTypeId]->duplicate(true);
                    v.geometry->addAttachment("dynamicaly_generated", 0);

                    // Add it to the map
                    vehicles.insert(make_pair(v.id, v));

                } else vehicleIDs.erase(ID); // Already (and still) exists, remove its ID from the vehicle-id-set

                // Now the vehicle exists, update its position and state

                Vehicle& v = vehicles[ID];

                v.pos = Vec3f(vehicleIter["pos"][0].asFloat(), vehicleIter["pos"][1].asFloat(), vehicleIter["pos"][2].asFloat());
                v.deltaPos = Vec3f(vehicleIter["dPos"][0].asFloat(), vehicleIter["dPos"][1].asFloat(), vehicleIter["dPos"][2].asFloat());
                v.deltaPos *= partDelta;
                v.orientation = Vec3f(vehicleIter["angle"][0].asFloat(), vehicleIter["angle"][1].asFloat(), vehicleIter["angle"][2].asFloat());
                v.deltaOrientation = Vec3f(vehicleIter["dAngle"][0].asFloat(), vehicleIter["dAngle"][1].asFloat(), vehicleIter["dAngle"][2].asFloat());
                v.deltaOrientation *= partDelta;

                if (!vehicleIter["state"].isNull() && vehicleIter["state"].isArray()) {
                    v.state = Vehicle::NONE;

                    for (auto state : vehicleIter["state"]) {
                        if (!state.isConvertibleTo(stringValue)) continue;

                        if(state.asString() == "rightIndicator") {
                            v.state |= Vehicle::RIGHT_INDICATOR;
                        } else if(state.asString() == "leftIndicator") {
                            v.state |= Vehicle::LEFT_INDICATOR;
                        } else if(state.asString() == "accelerating") {
                            v.state |= Vehicle::ACCELERATING;
                        } else if(state.asString() == "braking") {
                            v.state |= Vehicle::BRAKING;
                        } else if(state.asString() == "waiting") {
                            v.state |= Vehicle::WAITING;
                        } else if(state.asString() == "blocked") {
                            v.state |= Vehicle::BLOCKED;
                        } else if(state.asString() == "collision") {
                            v.state |= Vehicle::COLLIDED;
                        }
                    }
                }

                if (!vehicleIter["colliding"].isNull() && vehicleIter["colliding"].isArray()) {
                    for (auto collisionIter : vehicleIter["colliding"]) {
                        if (!collisionIter.isConvertibleTo(uintValue)) continue;

                        uint other = collisionIter.asUInt();
                        if (other < v.id) collisions.insert(make_pair(other, v.id));
                        else collisions.insert(make_pair(v.id, other));
                    }
                }
            } // End vehicle iteration

            // Okay, all vehicles are updated now

            // Resolve collisions
            if (collisionHandler != NULL) {
                for (auto c : collisions) {
                    if (collisionHandler(vehicles[c.first], vehicles[c.second])) {
                        dataToSend["collision"].append(c.first);
                        dataToSend["collision"].append(c.second);
                    }
                }
            }

        } // End vehicle updates

        // Remove vehicles which are no longer on the map
        for (auto v : vehicleIDs) {
            vehicles[v].geometry->destroy();
            vehicles.erase(v);
        }


        // Get traffic light updates
        if (!receivedData["trafficlights"].isNull() && receivedData["trafficlights"].isArray()) {

            // The light bulbs in the array will be moved around arbitrary whichever light posts are given
            // If there are not enough bulbs in the array, more are added
            // If there are too many bulbs, they are deleted
            size_t bulbIndex = 0;
            static const double postHeight = 2;
            static const double bulbSize   = 1; // Note: If you change this value from 2, change the value further down in new VRGeometry(), too.

            for (auto lightpost : receivedData["trafficlights"]) {
                if (!lightpost.isObject()) continue;

                if (!lightpost["at"].isConvertibleTo(uintValue)
                 || !lightpost["to"].isConvertibleTo(uintValue)
                 ||  lightpost["state"].isNull()
                 || !lightpost["state"].isArray()) {
                    cout << "TrafficSimulation: Warning: Received invalid light post data.\n";
                    continue;
                }

                // Calculate the vector of the street

                // Get the node positions
                Vec2f atPos, toPos;
                string atId = lexical_cast<string>(lightpost["at"].asUInt());
                string toId = lexical_cast<string>(lightpost["to"].asUInt());
                bool foundAt = false, foundTo = false;
                for (auto mapIter : loadedMaps) {
                    for (auto nodeIter : mapIter->osmNodes) {

                        if (!foundAt && nodeIter->id == atId) {
                            atPos = mapCoordinator->realToWorld(Vec2f(nodeIter->lat, nodeIter->lon));
                            foundAt = true;
                        }

                        if (!foundTo && nodeIter->id == toId) {
                            toPos = mapCoordinator->realToWorld(Vec2f(nodeIter->lat, nodeIter->lon));
                            foundTo = true;
                        }

                        if (foundAt && foundTo)
                            break;
                    }
                    if (foundAt && foundTo)
                        break;
                }

                Vec2f streetOffset = toPos - atPos;
                const float prevLength = streetOffset.length();
                streetOffset.normalize();
                streetOffset *= min(prevLength / 2, Config::get()->STREET_WIDTH);

                Vec2f normal(-streetOffset[1], streetOffset[0]);
                normal.normalize();
                normal *= Config::get()->STREET_WIDTH;

                streetOffset += atPos;

                // streetOffset now contains a position in the center of a street a bit away from the crossing
                // normal is a vector that is orthogonal to the street

                // Now iterate over the lanes and hang up the lights
                double lane = -0.5;
                for (auto light : lightpost["state"]) {
                    lane += 1;

                    if (!light.isConvertibleTo(stringValue)) continue;

                    while (bulbIndex+1 >= lightBulbs.size()) {
                        if (VRSceneManager::get()->getActiveScene() == NULL) break;

                        // Create a new light
                        VRGeometry* geo = new VRGeometry("ampel");
                        geo->addAttachment("dynamicaly_generated", 0);
                        geo->setPrimitive("Sphere", "0.5 2"); // The first value has to be half of bulbSize
                        geo->setMaterial(a_red);

                        VRSceneManager::get()->getActiveScene()->add(geo);
                        lightBulbs.push_back(geo);
                    }

                    // color switch
                    VRGeometry* bulb = lightBulbs[bulbIndex++];
                    Vec3f p = Vec3f(streetOffset[0] + lane * normal[0], postHeight, streetOffset[1] + lane * normal[1]);
                    string lcol = light.asString();
                    if (lcol == "red") {
                        bulb->setWorldPosition(p+Vec3f(0,3 * bulbSize,0));
                        bulb->setMaterial(a_red);

                    } else if (lcol == "redamber") {
                        bulb->setWorldPosition(p+Vec3f(0,3 * bulbSize,0));
                        bulb->setMaterial(a_red);

                        bulb = lightBulbs[bulbIndex++];
                        bulb->setWorldPosition(p+Vec3f(0,2 * bulbSize,0));
                        bulb->setMaterial(a_orange);
                    } else if (lcol == "amber") {
                        bulb->setWorldPosition(p+Vec3f(0,2 * bulbSize,0));
                        bulb->setMaterial(a_orange);
                    } else if (lcol == "green") {
                        bulb->setWorldPosition(p+Vec3f(0,bulbSize,0));
                        bulb->setMaterial(a_green);
                    }
                }
            }

            // Remove unused lightbulbs
            while (bulbIndex < lightBulbs.size()) {
                lightBulbs.back()->destroy();
                lightBulbs.pop_back();
            }
        }
    }

    networkDataMutex.unlock();

        // Advance the vehicles a bit
    //cout << "Update " << vehicles.size() << " vehicles\n";
    for (auto v : vehicles) {
        Vec3f p = v.second.pos;
        p[1] = -1.2;//TODO: get right street height
        v.second.geometry->setFrom(p);
        v.second.geometry->setDir(v.second.pos - v.second.orientation);
        v.second.pos += v.second.deltaPos;
        v.second.orientation += v.second.deltaOrientation;
    }

}