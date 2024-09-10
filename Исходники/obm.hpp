 void                    CheckForEnemyCreate()       { if(enemy_create.getElapsedTime() > sf::milliseconds(500))
                                                         {
                                                             int willThereBeEnemy = rand()%10;
                                                             if(willThereBeEnemy >= 4)
                                                                 EnemyGroup.resize(EnemyGroup.size()+1);
                                                             enemy_create.restart();
                                                         }
                                                     }