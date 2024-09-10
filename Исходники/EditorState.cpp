void EditorState::keyDown(ci::app::KeyEvent event)
{
    // XXX duplicate raycast
    Vec2f pos = GG.mouse.getPos();
    Vec3f planeHit = GG.hexRender.raycastHexPlane(pos.x, pos.y);
    HexCoord selectedHex = GG.hexGrid.WorldToHex(planeHit);

    int keycode = event.getCode();

    Vec3f& cameraTo = GG.hexRender.getCameraTo();
    if (keycode == app::KeyEvent::KEY_ESCAPE) {
        mManager.setActiveState("title");
    }
    else if (keycode == app::KeyEvent::KEY_UP) {
        cameraTo += Vec3f(0, 2.0f, 0);
    }
    else if (keycode == app::KeyEvent::KEY_DOWN) {
        cameraTo += Vec3f(0, -2.0f, 0);
    }   
    else if (keycode == app::KeyEvent::KEY_LEFT) {
        cameraTo += Vec3f(-2.0f, 0, 0);
    }
    else if (keycode == app::KeyEvent::KEY_RIGHT) {
        cameraTo += Vec3f(2.0f, 0, 0);
    }
    else if (keycode == app::KeyEvent::KEY_g) {
        //  Generate hex colors
        Vec2i mapSize = GG.hexMap.getSize();
        for (int iy=0; iy < mapSize.y; ++iy) {
            for (int ix=0; ix < mapSize.x; ++ix) {
                HexCell& cell = GG.hexMap.at(HexCoord(ix, iy));
                if (cell.getLand()) {
                    int playerID = random.nextInt(0, 5);
                    cell.setOwner(playerID);
                    cell.setColor(GG.warGame.getPlayers()[playerID].getColor());
                }
            }
        }
    }
    else if (keycode == app::KeyEvent::KEY_DELETE) {
        GG.hexMap.at(selectedHex).setLand(0);
    }
    else if (keycode == app::KeyEvent::KEY_SPACE) {
        mManager.setActiveState(string("game"));
    }
    else if (keycode == app::KeyEvent::KEY_c) {
        vector<HexCoord> connected = GG.hexMap.connected(selectedHex);
        for (vector<HexCoord>::iterator it = connected.begin(); it != connected.end(); ++it) {
            HexCell& cell = GG.hexMap.at(*it);
            Color cellColor = cell.getColor();
            cellColor.r = 0.5f * cellColor.r;
            cellColor.g = 0.5f * cellColor.g;
            cellColor.b = 0.5f * cellColor.b;
            cell.setColor(cellColor);
        }
    }
}