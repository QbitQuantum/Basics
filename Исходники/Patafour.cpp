int Patafour::Main()
{
    startTimeout.restart();
    string nick,pass;

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);

        sf::Vector2u windowsize = window.getSize();
        int width = windowsize.x;
        int height = windowsize.y;
        view.setCenter(sf::Vector2f(width/2, height/2));
        view.setSize(sf::Vector2f(width, height));

        switch(state) {
                case -3:
                return 0;
                break;
                case -2:
                static LoginDialog loginDialog;
                loginDialog.Draw(window);
                nick=loginDialog.login;
                pass=loginDialog.pass;
                break;
                case -1:
                static LoadingSplash loadingSplash;
                loadingSplash.Draw(window);
                if(startTimeout.getElapsedTime().asSeconds()>=2)
                {
                state = 0;
                loadingSplash.Stop();
                }
                break;
                case 0:
                static Opening opening(window);
                opening.Draw(window,this);
                break;
                case 1:
                static MainMenu mainmenu(window);
                mainmenu.Draw(window,this);
                break;
                case 2:
                cout << "options" << endl;
                break;
                case 3:
                cout << "Loading save" << endl;
                ///Loading here
                cout << "Loaded" << endl;
                state = 4;
                break;
                case 4:
                static Tips tipsp(this);
                if(patapolisloaded == false)
                if(tipsp.needsrefresh == true) {
                cout << "refresh'd" << endl;
                tipsp.refresh(this);
                waiting.restart();
                res.LoadAllWeapons();
                }
                if(patapolisloaded==false)
                tipsp.Draw(window,this,1);
                static int i = 0;
                if(i==0) {
                res.LoadAllWeapons();
                waiting.restart();
                i+=1;
                }
                if(waiting.getElapsedTime().asSeconds()>1) {
                if(saveloaded==false) {
                savecontainer.Synchronize(nick,pass,0);
                saveloaded=true; }
                static Patapolis patapolis(window,savecontainer);
                if(patapolisloaded==true) {
                patapolis.Draw(window,savecontainer,this); }}
                break;
                case 5:
                static NewGameIntro newgameintro;
                newgameintro.Draw(window,this);
                break;
                case 6:
                cout << "Patapon oath" << endl;
                break;
                case 7:
                static Tips tipsm(this);
                static int miau = 0;
                if(miau == 0) {
                pataponload = false;
                miau += 1;
                }

                if(missionloaded==false)
                if(tipsm.needsrefresh == true){
                cout << "refresh'd" << endl;
                tipsm.refresh(this);
                pataponload = false;
                }
                if(missionloaded==false) {
                tipsm.Draw(window,this,2);
                hatapon.x = 0;
                hatapon.action = "idle";

                }
                if(tipsm.finished==true) {
                static Mission* mission = new Mission();
                if(pataponload == false)
                {
                    cout << "creating patapons" << endl;
                    for(int i=0; i<=5; i++)
                    {
                        if(savecontainer.yaripons[i][1]!="")
                        {
                        troops[1] = true;
                        Patapon temppon;
                        temppon.PataponType = temppon.YARIPON;
                        temppon.x = (hatapon.x+100)+50*i;
                        temppon.baseposition = (hatapon.x+100)+50*i;
                        yaripons.push_back(temppon);
                        cout << "YARIPONS SIZE: " << yaripons.size() << endl;
                        }
                    }

                    for(int i=0; i<=5; i++)
                    {
                        if(savecontainer.tatepons[i][1]!="")
                        {
                        troops[2] = true;
                        Patapon temppon;
                        temppon.PataponType = temppon.TATEPON;
                        temppon.x = 300+30*i;
                        temppon.baseposition = 300+30*i;
                        tatepons.push_back(temppon);
                        }
                    }

                    for(int i=0; i<=5; i++)
                    {
                        if(savecontainer.yumipons[i][1]!="")
                        {
                        troops[3] = true;
                        Patapon temppon;
                        temppon.PataponType = temppon.YUMIPON;
                        temppon.x = 0+30*i;
                        temppon.baseposition = 0+30*i;
                        yumipons.push_back(temppon);
                        }
                    }

                    cout << "patapons created" << endl;
                    pataponload = true;
                }
                static PataponRes res;
                if(mission->loaded==false) {
                mission->Load(missionfile,window);

                cout << "loading patapons" << endl;

                for(int i=0; i<=yaripons.size(); i++)
                {
                    if(savecontainer.yaripons[i][1]!="")
                    yaripons[i].LoadResources(res);
                }

                for(int i=0; i<=tatepons.size(); i++)
                {
                    if(savecontainer.tatepons[i][1]!="")
                    tatepons[i].LoadResources(res);
                }

                for(int i=0; i<=yumipons.size(); i++)
                {
                    if(savecontainer.yumipons[i][1]!="")
                    yumipons[i].LoadResources(res);
                }

                cout << "loaded patapons" << endl;

                }
                if(missionloaded==true) {
                mission->Draw(window,commandbuffer,this);
                hatapon.WeaponID = atoi(savecontainer.hatapon[6].c_str());
                hatapon.HatID = atoi(savecontainer.hatapon[7].c_str());
                hatapon.draw(window);
                hatapon.baseposition = hatapon.x+0;

                hatapon.commandbuffer = mission->commandsystem.Play();
                hatapon.commandclock = mission->commandClock.getElapsedTime();

                mission->camera.x = hatapon.x;

                /**
                for(int i=0; i<=4; i++)
                {
                    if(troops[i]==true)
                    {
                        if(i==0)
                        {
                            cout << "hatapon" << endl;
                            int temp = window.getSize().x/2;
                            circle[i].setPosition((4+i*70)-temp+mission->camera.x,10);
                            hpoutline[i].setPosition((8+i*70)-temp+mission->camera.x,2);
                            hpbar[i].setPosition((9+i*70)-temp+mission->camera.x,3);

                            sf::Sprite Mini_Head;
                            sf::Sprite Mini_Eye;
                            sf::Sprite Mini_Arm_L;
                            sf::Sprite Mini_Arm_R;
                            sf::Sprite Mini_Leg_L;
                            sf::Sprite Mini_Leg_R;
                            sf::Sprite Mini_Hat;
                            sf::Sprite Mini_Weapon;

                            Mini_Head.setTexture(*hatapon.Head.getTexture(),true);
                            Mini_Eye.setTexture(*hatapon.Eye.getTexture(),true);
                            Mini_Arm_L.setTexture(*hatapon.Arm_L.getTexture(),true);
                            Mini_Arm_R.setTexture(*hatapon.Arm_R.getTexture(),true);
                            Mini_Leg_L.setTexture(*hatapon.Leg_L.getTexture(),true);
                            Mini_Leg_R.setTexture(*hatapon.Leg_R.getTexture(),true);
                            ///Mini_Hat.setTexture(temptex[6],true);
                            Mini_Weapon.setTexture(*hatapon.Weapon.getTexture(),true);

                            Mini_Head.setScale(0.25,0.25);
                            Mini_Eye.setScale(0.25,0.25);
                            Mini_Arm_L.setScale(0.25,0.25);
                            Mini_Arm_R.setScale(0.25,0.25);
                            Mini_Leg_L.setScale(0.25,0.25);
                            Mini_Leg_R.setScale(0.25,0.25);
                            Mini_Hat.setScale(0.25,0.25);
                            Mini_Weapon.setScale(0.25,0.25);

                            Mini_Head.setPosition((4+i*70)-temp+mission->camera.x+17,26);
                            Mini_Eye.setPosition((4+i*70)-temp+mission->camera.x+26+((hatapon.Eye.getPosition().x-hatapon.x)/2),35+((hatapon.Eye.getPosition().y-hatapon.y)/2));
                            Mini_Arm_L.setPosition((4+i*70)-temp+mission->camera.x+9+((hatapon.Arm_L.getPosition().x-hatapon.x)/2)+24,41+((hatapon.Arm_L.getPosition().y-hatapon.y)/2));
                            Mini_Arm_R.setPosition((4+i*70)-temp+mission->camera.x+9+((hatapon.Arm_R.getPosition().x-hatapon.x)/2)+20,41+((hatapon.Arm_R.getPosition().y-hatapon.y)/2));
                            Mini_Arm_L.setRotation(hatapon.Arm_L.getRotation());
                            Mini_Arm_R.setRotation(hatapon.Arm_R.getRotation());
                            Mini_Arm_L.setOrigin(hatapon.Arm_L.getOrigin().x,hatapon.Arm_L.getOrigin().y);
                            Mini_Arm_R.setOrigin(hatapon.Arm_R.getOrigin().x,hatapon.Arm_R.getOrigin().y);
                            Mini_Leg_L.setPosition((4+i*70)-temp+mission->camera.x+11+((hatapon.Leg_L.getPosition().x-hatapon.x)/2)+21,41+((hatapon.Leg_L.getPosition().y-hatapon.y)/2));
                            Mini_Leg_R.setPosition((4+i*70)-temp+mission->camera.x+11+((hatapon.Leg_R.getPosition().x-hatapon.x)/2)+21,41+((hatapon.Leg_R.getPosition().y-hatapon.y)/2));
                            Mini_Weapon.setPosition((4+i*70)-temp+mission->camera.x+11+((hatapon.Weapon.getPosition().x-hatapon.x)/2)+21,30+((hatapon.Weapon.getPosition().y-hatapon.y)/2));
                            Mini_Weapon.setRotation(hatapon.Weapon.getRotation());
                            Mini_Weapon.setOrigin(hatapon.Weapon.getOrigin().x,hatapon.Weapon.getOrigin().y);

                            window.draw(circle[i]);

                            window.draw(Mini_Head);
                            window.draw(Mini_Eye);
                            window.draw(Mini_Arm_L);
                            window.draw(Mini_Arm_R);
                            window.draw(Mini_Leg_L);
                            window.draw(Mini_Leg_R);
                            window.draw(Mini_Hat);
                            window.draw(Mini_Weapon);

                            window.draw(hpoutline[i]);
                            window.draw(hpbar[i]);
                        }


                        if(i==1)
                        {
                            cout << "yaripon" << endl;
                            int temp = window.getSize().x/2;
                            circle[i].setPosition((4+i*70)-temp+mission->camera.x,10);
                            hpoutline[i].setPosition((8+i*70)-temp+mission->camera.x,2);
                            hpbar[i].setPosition((9+i*70)-temp+mission->camera.x,3);

                            float ratio;
                            float currentsum,maxsum;

                            if(yaripons.size()!=0)
                            for(int i=0; i<yaripons.size(); i++)
                            {
                                if(savecontainer.yaripons[i][1]!="")
                                {
                                currentsum += atof(savecontainer.yaripons[i][2].c_str());
                                maxsum += atof(savecontainer.yaripons[i][3].c_str());
                                }
                            }

                            cout << "test1" << endl;
                            if(currentsum==0)
                            currentsum = 1;

                            if(maxsum==0)
                            maxsum = 1;

                            ratio = currentsum / maxsum;

                            hpbar[i].setScale(ratio,1);

                            cout << "sprites" << endl;
                            sf::Sprite Mini_Head;
                            sf::Sprite Mini_Eye;
                            sf::Sprite Mini_Arm_L;
                            sf::Sprite Mini_Arm_R;
                            sf::Sprite Mini_Leg_L;
                            sf::Sprite Mini_Leg_R;
                            sf::Sprite Mini_Hat;
                            sf::Sprite Mini_Weapon;

                            cout << "pointers (" << yaripons.size()-1 << ")" << endl;
                            Mini_Head.setTexture(*yaripons[0].Head.getTexture(),true);
                            Mini_Eye.setTexture(*yaripons[0].Eye.getTexture(),true);
                            Mini_Arm_L.setTexture(*yaripons[0].Arm_L.getTexture(),true);
                            Mini_Arm_R.setTexture(*yaripons[0].Arm_R.getTexture(),true);
                            Mini_Leg_L.setTexture(*yaripons[0].Leg_L.getTexture(),true);
                            Mini_Leg_R.setTexture(*yaripons[0].Leg_R.getTexture(),true);
                            ///Mini_Hat.setTexture(temptex[6],true);
                            ///Mini_Weapon.setTexture(hatapon.Weapon.getTexture(),true);

                            cout << "scale" << endl;
                            Mini_Head.setScale(0.25,0.25);
                            Mini_Eye.setScale(0.25,0.25);
                            Mini_Arm_L.setScale(0.25,0.25);
                            Mini_Arm_R.setScale(0.25,0.25);
                            Mini_Leg_L.setScale(0.25,0.25);
                            Mini_Leg_R.setScale(0.25,0.25);
                            Mini_Hat.setScale(0.25,0.25);

                            cout << "position" << endl;
                            Mini_Head.setPosition((4+i*70)-temp+mission->camera.x+17,26);
                            Mini_Eye.setPosition((4+i*70)-temp+mission->camera.x+26+((yaripons[yaripons.size()-1].Eye.getPosition().x-yaripons[yaripons.size()-1].x)/2),35+((yaripons[yaripons.size()-1].Eye.getPosition().y-yaripons[yaripons.size()-1].y)/2));
                            Mini_Arm_L.setPosition((4+i*70)-temp+mission->camera.x+9+((yaripons[yaripons.size()-1].Arm_L.getPosition().x-yaripons[yaripons.size()-1].x)/2)+25,39+((yaripons[yaripons.size()-1].Arm_L.getPosition().y-yaripons[yaripons.size()-1].y)/2));
                            Mini_Arm_R.setPosition((4+i*70)-temp+mission->camera.x+9+((yaripons[yaripons.size()-1].Arm_R.getPosition().x-yaripons[yaripons.size()-1].x)/2)+21,39+((yaripons[yaripons.size()-1].Arm_R.getPosition().y-yaripons[yaripons.size()-1].y)/2));
                            Mini_Leg_L.setPosition((4+i*70)-temp+mission->camera.x+11+((yaripons[yaripons.size()-1].Leg_L.getPosition().x-yaripons[yaripons.size()-1].x)/2)+21,41+((yaripons[yaripons.size()-1].Leg_L.getPosition().y-yaripons[yaripons.size()-1].y)/2));
                            Mini_Leg_R.setPosition((4+i*70)-temp+mission->camera.x+11+((yaripons[yaripons.size()-1].Leg_R.getPosition().x-yaripons[yaripons.size()-1].x)/2)+21,41+((yaripons[yaripons.size()-1].Leg_R.getPosition().y-yaripons[yaripons.size()-1].y)/2));

                            window.draw(circle[i]);

                            window.draw(Mini_Head);
                            window.draw(Mini_Eye);
                            window.draw(Mini_Arm_L);
                            window.draw(Mini_Arm_R);
                            window.draw(Mini_Leg_L);
                            window.draw(Mini_Leg_R);
                            window.draw(Mini_Hat);

                            window.draw(hpoutline[i]);
                            window.draw(hpbar[i]);
                            cout << "yaripon is done" << endl;
                        }


                        if(i==2)
                        {
                            cout << "tatepon" << endl;
                            int temp = window.getSize().x/2;

                            circle[i].setPosition((4+i*70)-temp+mission->camera.x,10);
                            hpoutline[i].setPosition((8+i*70)-temp+mission->camera.x,2);
                            hpbar[i].setPosition((9+i*70)-temp+mission->camera.x,3);

                            float ratio;
                            float currentsum,maxsum;

                            if(tatepons.size()!=0)
                            for(int i=0; i<tatepons.size(); i++)
                            {
                                if(savecontainer.tatepons[i][1]!="")
                                {
                                currentsum += atof(savecontainer.tatepons[i][2].c_str());
                                maxsum += atof(savecontainer.tatepons[i][3].c_str());
                                }
                            }

                            if(currentsum==0)
                            currentsum = 1;

                            if(maxsum==0)
                            maxsum = 1;

                            ratio = currentsum / maxsum;

                            hpbar[i].setScale(ratio,1);

                            window.draw(circle[i]);
                            window.draw(hpoutline[i]);
                            window.draw(hpbar[i]);
                        }


                        if(i==3)
                        {
                            cout << "yumipon" << endl;
                            int temp = window.getSize().x/2;

                            circle[i].setPosition((4+i*70)-temp+mission->camera.x,10);
                            hpoutline[i].setPosition((8+i*70)-temp+mission->camera.x,2);
                            hpbar[i].setPosition((9+i*70)-temp+mission->camera.x,3);

                            float ratio;
                            float currentsum,maxsum;

                            if(yumipons.size()!=0)
                            for(int i=0; i<yumipons.size(); i++)
                            {
                                if(savecontainer.yumipons[i][1]!="")
                                {
                                currentsum += atof(savecontainer.yumipons[i][2].c_str());
                                maxsum += atof(savecontainer.yumipons[i][3].c_str());
                                }
                            }

                            if(currentsum==0)
                            currentsum = 1;

                            if(maxsum==0)
                            maxsum = 1;

                            ratio = currentsum / maxsum;

                            hpbar[i].setScale(ratio,1);

                            window.draw(circle[i]);
                            window.draw(hpoutline[i]);
                            window.draw(hpbar[i]);
                        }
                    }
                }*/

                if(yaripons.size()!=0)
                for(int i=0; i<yaripons.size(); i++)
                {
                    if(savecontainer.yaripons[i][1]!="")
                    {
                    yaripons[i].commandbuffer = mission->commandsystem.Play();
                    yaripons[i].commandclock = mission->commandClock.getElapsedTime();
                    yaripons[i].baseposition = (hatapon.x+100)+50*i;
                    yaripons[i].WeaponID = atoi(savecontainer.yaripons[i][6].c_str());
                    yaripons[i].HatID = atoi(savecontainer.yaripons[i][7].c_str());
                    yaripons[i].draw(window);
                    }
                }

                if(tatepons.size()!=0)
                for(int i=0; i<=tatepons.size(); i++)
                {
                    if(savecontainer.tatepons[i][1]!="")
                    {
                    tatepons[i].commandbuffer = mission->commandsystem.Play();
                    yaripons[i].commandclock = mission->commandClock.getElapsedTime();
                    yaripons[i].WeaponID = atoi(savecontainer.tatepons[i][6].c_str());
                    yaripons[i].HatID = atoi(savecontainer.tatepons[i][7].c_str());
                    tatepons[i].draw(window);
                    }
                }

                if(yumipons.size()!=0)
                for(int i=0; i<=yumipons.size(); i++)
                {
                    if(savecontainer.yumipons[i][1]!="")
                    {
                    yumipons[i].commandbuffer = mission->commandsystem.Play();
                    yaripons[i].commandclock = mission->commandClock.getElapsedTime();
                    yaripons[i].WeaponID = atoi(savecontainer.yumipons[i][6].c_str());
                    yaripons[i].HatID = atoi(savecontainer.yumipons[i][7].c_str());
                    yumipons[i].draw(window);
                    }
                }

                cout << mission->camera.x << endl;

                for(int i=0; i<yaripons.size(); i++)
                {
                    for(int i2=0; i2<mission->entities.size(); i2++)
                    {
                        if(yaripons[i].spear.spear.getPosition().x>mission->entities[i2].GetObjectLocation().x-mission->entities[i2].objectamount*5)
                        {
                            if(yaripons[i].spear.spear.getPosition().y>mission->entities[i2].GetObjectLocation().y-mission->entities[i2].objectamount*3)
                            {
                                if(yaripons[i].spear.spear.getPosition().x<mission->entities[i2].GetObjectLocation().x+mission->entities[i2].objectamount*5)
                                {
                                    if(yaripons[i].spear.spear.getPosition().y<mission->entities[i2].GetObjectLocation().y+mission->entities[i2].objectamount*3)
                                    {
                                        yaripons[i].spear.dmg.dmgtext.setPosition(yaripons[i].spear.spear.getPosition());
                                        yaripons[i].spear.dmg.alpha = 255;
                                        yaripons[i].spear.dmg.dmg = round(res.spearmindmg[atof(savecontainer.yaripons[i][6].c_str())]+res.hatdmg[atof(savecontainer.yaripons[i][6].c_str())]+res.spearmindmg[atof(savecontainer.yaripons[i][6].c_str())]/3*res.spearmindmg[atof(savecontainer.yaripons[i][8].c_str())]+(atof(savecontainer.yaripons[i][0].c_str())-1)*2);
                                        yaripons[i].spear.spear.setPosition(0,20000);
                                        cout << "GOT HIT" << endl;
                                    }
                                }
                            }
                        }
                    }
                }

                if(hatapon.action == "move")
                {
                if(mission->entities.size()-1>=0) {
                    for(int i=0; i<=mission->entities.size()-1; i++) {
                      if(mission->entities[i].collide == true) {
                        for(int i2=0; i2<yaripons.size(); i2++) {

                        if(mission->entities[i].GetObjectLocation().x-200>yaripons[i2].x) {
                            ///mission->entities[i].Move(-1,0);

                            if(yaripons.size()!=0)
                                if(savecontainer.yaripons[i2][1]!="")
                                {
                                yaripons[i2].x += 2;
                                }

                            mission->cancameramove = true;
                            yaripons[i2].cangotobase = true;
                            } else {
                            yaripons[i2].cangotobase = false;
                            mission->cancameramove = false;
                            }
                        }

                            if(mission->entities[i].GetObjectLocation().x-200>hatapon.x) {
                            hatapon.x += 2;
                            mission->cancameramove = true;
                            hatapon.cangotobase = true;

                            for(int i=0; i<=mission->backgroundcount; i++)
                            {
                                mission->backSize[i].x-=mission->backMoveX[i];
                            }

                            } else {
                            mission->cancameramove = false;
                            hatapon.cangotobase = false;
                            }

                            for(int i2=0; i2<yaripons.size(); i2++)
                            {
                            if(mission->entities[i].GetObjectLocation().x-200>yaripons[i2].x) {
                            yaripons[i2].cangotobase = true;
                            } else {
                            yaripons[i2].cangotobase = false;
                            }}
                        } else {
                            for(int i2=0; i2<yaripons.size(); i2++) {
                            if(yaripons.size()!=0)
                                if(savecontainer.yaripons[i2][1]!="")
                                {
                                    yaripons[i2].x += 2;
                                }
                            }

                            hatapon.x += 2;

                            for(int i=0; i<=mission->backgroundcount; i++)
                            {
                                mission->backSize[i].x-=mission->backMoveX[i];
                            }

                            mission->cancameramove = true;

                            if(mission->entities[i].completeafterwalk == true)
                            if(hatapon.x>mission->entities[i].GetObjectLocation().x) {
                                m1selected = 0;
                                m2selected = 0;
                                menu2open = false;

                                mission->loaded = false;

                                dmenureset = true;
                                yaripons.clear();
                                tatepons.clear();
                                yumipons.clear();

                                state = 34;
                            }
                        }

                        }
                    }
                }

                }

                }
                break;
                case 8:
                cout << "Mission overview (Like in Patapon 2 yay)" << endl;
                break;
                case 9:
                cout << "World map biatch" << endl;
                break;
                case 13:
                static Organization organization(savecontainer);
                if(oplaysnd == true)
                if(organization.bgm.getStatus() != sf::Music::Playing)
                organization.bgm.play();
                organization.selected = oselected;
                organization.menu1selected = m1selected;
                organization.menu2selected = m2selected;
                organization.menu2open = menu2open;
                organization.selected2 = pataselected;
                organization.Draw(window,this);
                break;
                case 34:
                static DemoMenu demomenu;
                cout << "uh, hi?" << endl;
                missionloaded = false;

                if(dmenureset == true) {
                organization.bgm.stop();
                m1selected = 0;
                m2selected = 0;
                menu2open = false;
                demomenu.azito.play();
                demomenu.clock.restart();
                dmenureset = false;
                }
                demomenu.completed = savecontainer.demopass;
                demomenu.sel = dmenuselect;
                demomenu.Draw(window,this);
                break;
                case 69:
                static Client client;
                static int c = 0;
                if(c==0) {
                missionloaded = false;
                string ip;
                cout << "input ip you want to connect" << endl;
                cin >> ip;
                client.Connect(ip.c_str());
                c++;
                }
                static Tips tipsmulti(this);
                if(missionloaded==false)
                if(tipsmulti.needsrefresh == true){
                cout << "refresh'd" << endl;
                tipsmulti.refresh(this);
                }
                if(missionloaded==false)
                tipsmulti.Draw(window,this,2);
                if(tipsmulti.finished==true) {
                static Mission mission;
                if(mission.loaded==false)
                mission.Load("multimission_1.map",window);
                if(missionloaded==true) {
                mission.Draw(window,commandbuffer,this);
                client.Multiplayer();
                client.Draw(window,mission);
                }}
                break;
                case 666:
                static Server server;
                static int s = 0;
                if(s==0) {
                missionloaded = false;
                string ip;
                cout << "input ip you want to host" << endl;
                cin >> ip;
                server.Connect(ip.c_str());
                s++;
                }
                static Tips tipsmulti2(this);
                if(missionloaded==false)
                if(tipsmulti2.needsrefresh == true){
                cout << "refresh'd" << endl;
                tipsmulti2.refresh(this);
                }
                if(missionloaded==false)
                tipsmulti2.Draw(window,this,2);
                if(tipsmulti2.finished==true) {
                static Mission mission;
                if(mission.loaded==false)
                mission.Load("multimission_1.map",window);
                if(missionloaded==true) {
                mission.Draw(window,commandbuffer,this);
                server.Multiplayer();
                server.Draw(window,mission);
                }}
                break;
            }