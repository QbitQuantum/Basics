void MyAppli::onExec () {
    if (getClock("RequestTime").getElapsedTime().asSeconds() >= timeBtwnTwoReq.asSeconds()) {
        std::string request = "GETCARPOS";
        sf::Packet packet;
        packet<<request;
        Network::sendUdpPacket(packet);
        getClock("RequestTime").restart();
        received = false;
    }
    std::string response;
    if (Network::getResponse("STOPCARMOVE", response)) {
        std::vector<std::string> infos = split(response, "*");
        int id = conversionStringInt(infos[0]);
        Vec3f newPos (conversionStringFloat(infos[1]), conversionStringFloat(infos[2]), 0);
        Caracter* caracter = static_cast<Caracter*>(World::getEntity(id));
        Vec3f actualPos = Vec3f(caracter->getCenter().x, caracter->getCenter().y, 0);
        if (hero->getId() == id) {
            for (unsigned int i = 0; i < getRenderComponentManager().getNbComponents(); i++) {
                View view = getRenderComponentManager().getRenderComponent(i)->getView();
                Vec3f d = newPos - view.getPosition();
                view.move(d.x, d.y, d.y);
                getRenderComponentManager().getRenderComponent(i)->setView(view);
            }
            Vec3f d = newPos - getView().getPosition();
            getView().move(d.x, d.y, d.y);
        }
        Vec3f d = newPos - actualPos;
        World::moveEntity(caracter, d.x, d.y, d.y);
        caracter->setMoving(false);
        World::update();
    }
    if (Network::getResponse("MONSTERONMOUSE", response)) {
        std::cout<<"monster on mouse!"<<std::endl;
    }
    if (Network::getResponse("NEWPATH", response)) {
        std::vector<std::string> infos = split(response, "*");
        std::vector<Vec2f> path;
        int size = conversionStringInt(infos[0]);
        int id = conversionStringInt(infos[1]);
        Caracter* caracter = static_cast<Caracter*>(World::getEntity(id));
        Vec2f actualPos (conversionStringFloat(infos[2]), conversionStringFloat(infos[3]));
        Vec2f newPos = Computer::getPosOnPathFromTime(actualPos, caracter->getPath(),ping,caracter->getSpeed());
        for (int i = 0; i < size; i++) {
            path.push_back(Vec2f(conversionStringFloat(infos[i*2+4]), conversionStringFloat(infos[i*2+5])));
        }
        Vec2f d = newPos - actualPos;
        Vec2f dir = d.normalize();
        if (dir != caracter->getDir())
            caracter->setDir(dir);
        World::moveEntity(caracter, d.x, d.y, d.y);
        caracter->setPath(path);
        caracter->setMoving(true);
        caracter->interpolation.first = caracter->getCenter();
        caracter->interpolation.second = Computer::getPosOnPathFromTime(caracter->interpolation.first, caracter->getPath(),ping + timeBtwnTwoReq.asMicroseconds(),caracter->getSpeed());
        caracter->getClkTransfertTime().restart();
    }
    if (Network::getResponse("NEWPOS", response)) {
        std::vector<std::string> infos = split(response, "*");
        if (infos.size() == 4) {
            int id = conversionStringInt(infos[0]);
            ping = conversionStringLong(infos[1]);
            Caracter* caracter = static_cast<Caracter*>(World::getEntity(id));
            Vec3f actualPos = Vec3f(caracter->getCenter().x, caracter->getCenter().y, 0);
            Vec3f newPos (conversionStringFloat(infos[2]), conversionStringFloat(infos[3]), 0);
            Vec3f d = newPos - actualPos;
            if (id == hero->getId()) {
                for (unsigned int i = 0; i < getRenderComponentManager().getNbComponents(); i++) {
                    View view = getRenderComponentManager().getRenderComponent(i)->getView();
                    view.move(d.x, d.y, d.y);
                    getRenderComponentManager().getRenderComponent(i)->setView(view);
                }
                getView().move (d.x, d.y, d.y);
            }
            World::moveEntity(caracter, d.x, d.y, d.y);
            World::update();
            caracter->interpolation.first = Vec3f(caracter->getCenter().x, caracter->getCenter().y, 0);
            if (caracter->isMoving()) {
                if (caracter->isMovingFromKeyboard()) {
                    caracter->interpolation.second = caracter->interpolation.first + Vec3f(caracter->getDir().x,caracter->getDir().y,0)  * caracter->getSpeed() * (ping + timeBtwnTwoReq.asMicroseconds());
                } else {
                    caracter->interpolation.second = Computer::getPosOnPathFromTime(caracter->interpolation.first, caracter->getPath(),ping + timeBtwnTwoReq.asMicroseconds(),caracter->getSpeed());
                }
            } else {
                caracter->interpolation.second = caracter->interpolation.first;
            }
            caracter->getClkTransfertTime().restart();
        }

   } else {
       std::vector<Entity*> caracters = World::getEntities("E_MONSTER+E_HERO");
       for (unsigned int i = 0; i < caracters.size(); i++) {
            Caracter* caracter = static_cast<Caracter*>(caracters[i]);
            if (caracter->isMoving()) {
                if (caracter->isMovingFromKeyboard()) {
                    Vec3f actualPos = Vec3f(caracter->getCenter().x, caracter->getCenter().y, 0);
                    sf::Int64 elapsedTime = caracter->getClkTransfertTime().getElapsedTime().asMicroseconds();
                    Vec3f newPos = caracter->interpolation.first + (caracter->interpolation.second - caracter->interpolation.first) * ((float) elapsedTime / (float) (ping + timeBtwnTwoReq.asMicroseconds()));
                    Ray ray(actualPos, newPos);
                    if (World::collide(caracter, ray)) {
                        newPos = actualPos;
                    }
                    for (unsigned int i = 0; i < getRenderComponentManager().getNbComponents(); i++) {
                        View view = getRenderComponentManager().getRenderComponent(i)->getView();
                        Vec3f d = newPos - view.getPosition();
                        view.move(d.x, d.y, d.y);
                        getRenderComponentManager().getRenderComponent(i)->setView(view);
                    }
                    Vec3f d = newPos - actualPos;
                    World::moveEntity(caracter, d.x, d.y, d.y);
                    getView().move(d.x, d.y, d.y);
                    World::update();
                } else {
                    Vec3f actualPos (caracter->getCenter().x, caracter->getCenter().y, 0);
                    sf::Int64 elapsedTime = caracter->getClkTransfertTime().getElapsedTime().asMicroseconds();
                    Vec3f newPos = caracter->interpolation.first + (caracter->interpolation.second - caracter->interpolation.first) * ((float) elapsedTime / (float) (ping + timeBtwnTwoReq.asMicroseconds()));
                    Vec3f d = newPos - actualPos;
                    if (newPos.computeDist(caracter->getPath()[caracter->getPath().size() - 1]) <= PATH_ERROR_MARGIN) {
                        caracter->setMoving(false);
                        newPos = caracter->getPath()[caracter->getPath().size() - 1];
                    }
                    if (caracter->getId() == hero->getId()) {
                        for (unsigned int i = 0; i < getRenderComponentManager().getNbComponents(); i++) {
                            View view = getRenderComponentManager().getRenderComponent(i)->getView();
                            view.move(d.x, d.y, d.y);
                            getRenderComponentManager().getRenderComponent(i)->setView(view);
                        }
                        getView().move(d.x, d.y, d.y);
                    }
                    Vec2f dir = d.normalize();
                    if (dir != caracter->getDir())
                        caracter->setDir(dir);
                    World::moveEntity(caracter, d.x, d.y, d.y);
                    World::update();
                }
           }
       }
    }
    if (hero->isInFightingMode()) {
        if (hero->getFocusedCaracter() != nullptr) {
            int distToEnnemi = hero->getCenter().computeDist(hero->getFocusedCaracter()->getCenter());
            if (distToEnnemi <= hero->getRange()) {
                if (hero->isMoving())
                    hero->setMoving(false);
                hero->setAttacking(true);
                hero->attackFocusedCaracter();
            } else {
                hero->setAttacking(false);
            }
        }
    }
}