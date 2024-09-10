 void ManagerServer::run()
 {
     bool running = true;
     bool *move = new bool[4] {{0}};
     bool shoot = 0;
     
     bool gift1 = 0;
     bool gift2 = 0;
     sf::Event event;
        
     gui->getWindow()->clear();
        
if(gui->drawMenu(menu))
{		
     while (running)
    {

		std::string dataServer = " ";
		std::string dataClient;
		
		std::cout << "running....\n";
		
		try
		{
			//Create the socket
			ServerSocket server ( 30000 );
			ServerSocket server_socket;
			server.accept ( server_socket );
	
			try
			{
				 
				 while(gui->getWindow()->pollEvent(event))
                        {
                                switch(event.type)
                                {
                                        case sf::Event::Closed:
                                        {
                                                gui->getWindow()->close();
                                                return;
                                        }

                                        case sf::Event::KeyPressed:
                                        {
                                                switch(event.key.code)
                                                {
                                                        case sf::Keyboard::Right:
                                                        {
                                                                move[0]=1;
                                                                break;
                                                        }
                                                        case sf::Keyboard::Up:
                                                        {
                                                                move[1]=1;
                                                                break;
                                                        }
                                                        case sf::Keyboard::Left:
                                                        {
                                                                move[2]=1;
                                                                break;
                                                        }
                                                        case sf::Keyboard::Down:
                                                        {
                                                                move[3]=1;
                                                                break;
                                                        }

                                                        case sf::Keyboard::Space:
                                                        {
                                                                shoot=1;
                                                                break;
                                                        }
                                                }
                                                break;
                                        }

                                        case sf::Event::KeyReleased:
                                        {
                                                switch(event.key.code)
                                                {
                                                        case sf::Keyboard::Right:
                                                        {
                                                                move[0]=0;
                                                                break;
                                                        }
                                                        case sf::Keyboard::Up:
                                                        {
                                                                move[1]=0;
                                                                break;
                                                        }
                                                        case sf::Keyboard::Left:
                                                        {
                                                                move[2]=0;
                                                                break;
                                                        }
                                                        case sf::Keyboard::Down:
                                                        {
                                                                move[3]=0;
                                                                break;
                                                        }
                                                        /*case sf::Keyboard::Space:
                                                        {
                                                                shoot=0;
                                                                break;
                                                        }*/

                                                }
                                                break;
                                        }
                                }
                        		
                        }
                        
                        dataServer = bomber2->move2(move ,obs , wall ,bomber1);
                                
                        if(shoot)
                        {
								dataServer = bomb2->shoot2(bomber2 , bomb2timer);
								shoot=0;
						}
								
						server_socket >> dataClient;
						server_socket << dataServer;
								
						bomber1->move1(dataClient , obs  , wall , bomber2);
						bomb1->shoot1(dataClient , bomber1 , bomb1timer);

						for(int i=0; i<6 ; i++)
						{
								if ( gift[i].getGift(bomber1) == 1)
									gift1 = 1;
									
								if ( gift[i].getGift(bomber2) == 1)
									gift2 = 1;
						}
						
						gui->drawBack();
						gui->drawBomber(bomber1,true);
						gui->drawBomber(bomber2,false);
						gui->drawWall(wall);
						gui->drawTimer(timer);
						gui->drawGift(gift);
						gui->drawObs(obs);
						
						if(bomb1timer->getSeconds()<4)
							bomb1timer->handletime();
							
						if(bomb2timer->getSeconds()<4)
						    bomb2timer->handletime();
					
						if(bomb1timer->getSeconds()>=1 && bomb1timer->getSeconds()<=3)
						{	
							gui->drawBomb(bomb1);
						}
							
						
						if(bomb1timer->getSeconds()==3)
						{
								sf::Music b;
								if (!b.openFromFile("howto.wav")) {}
								b.play();
								
								if(gift1 == 1)
								{
									bomb1->explodeGift(obs , bomber1 ,bomber2);
								}	
							
								
							bomb1->explode(obs , bomber1 ,bomber2);
						}	
						
						if(bomb2timer->getSeconds()>=1 && bomb2timer->getSeconds()<=3)
						{	
							gui->drawBomb(bomb2);
						}
							
						
						if(bomb2timer->getSeconds()==3)
						{
							
								sf::Music b;
								if (!b.openFromFile("howto.wav")) {}
								b.play();
							
								if(gift2 == 1)
								{
									bomb2->explodeGift(obs , bomber1 ,bomber2);
								}	
							
								
							bomb2->explode(obs , bomber1 ,bomber2);
						}
						
						if(bomber2->getIsExist()==0 && bomber1->getIsExist()==1){gui->drawGameover();}
							
							
						if(bomber2->getIsExist()==1 && bomber1->getIsExist()==0){gui->drawWin();}
							
					
						gui->getWindow()->display();	
						
						server_socket >> dataClient;
						server_socket << dataServer;	
			}
			   	  
			 catch ( SocketException& ) { std::cout << "error " ;}
			 
		}

		
		catch ( SocketException& e )
		{
			 //gui->drawLoading();
			 //gui->getWindow()->display();
			 std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
		}
			
                        
	}
}		
}