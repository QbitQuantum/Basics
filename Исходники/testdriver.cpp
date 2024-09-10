int main()
{
	Creature *player1Creatures = NULL;
	Creature *player2Creatures = NULL;

	Queue player1Lineup;
	Queue player2Lineup;

	Stack player1Loserpile;
	Stack player2Loserpile;

	Queue allPile;
	Queue tmpQueue;

	int player1Points = 0;
	int player2Points = 0;

	int numofFighters;
	bool viewtop3 = false;

	cout << "How many fighters do you want both players to have? (Must have at least 3) " << endl;
	cin >> numofFighters;

	while (numofFighters < 3)
	{
		cout << "Must have at least 3 fighters for both players! " << endl;
		cin >> numofFighters;

		// make sure that users don't accidently type characters
		while (!cin)
		{
			cout << "Error. Integers only. " << endl;
			cin.clear();
			cin.ignore();

			cin >> numofFighters;
		}
		cin.ignore();

	}

	while(true)
	{
		int choice;

		cout << endl;
		cout << "1. Player 1 selections " << endl;
		cout << "2. Player 2 selections " << endl;
		cout << "3. View line up " << endl;
		cout << "4. View loser's pile " << endl;
		cout << "5. Fight " << endl;
		cout << "6. Top 3 Finishers " << endl;
		cout << "7. View final order of all fighters " << endl;
		cout << "8. Exit " << endl;

		cin >> choice;

		// make sure that users don't accidently type characters
		while (!cin)
		{
			cout << "Error. Integers only. " << endl;
			cin.clear();
			cin.ignore();

			cin >> choice;
		}
		cin.ignore();

		switch (choice)
		{

		case 1:
		{
			if (player1Lineup.isEmpty() == false)
			{
				cout << "\nLine up has already been created! " << endl;
				break;
			}

			for (int i = 0; i < numofFighters; i++)
			{

				string selection;
				cout << "\nPlease select fighter " << i+1 << "." << endl;
				cout << "(1)Barbarian, (2)Goblin, (3)ReptilePeople, (4)BlueMen, (5)Shadow " << endl;
				cin >> selection;

				while (!(selection == "1" || selection == "2" || selection == "3" || selection == "4" || selection == "5"))
				{
					cout << "That creature does not exist! Try again " << endl;
					cin >> selection;
				}

				cin.ignore();

				if (selection == "1")
				{
					string name;
					string team1 = "Team 1: ";
					Barbarian *barb = NULL;
					player1Creatures = new Barbarian();

					cout << "Please enter the name for the fighter" << endl;
					getline(cin, name);

					team1.append(name);

					player1Creatures->setrealName(team1);

					player1Lineup.add(player1Creatures);
				}

				if (selection == "2")
				{
					string name;
					string team1 = "Team 1: ";
					Goblin *gob = NULL;
					player1Creatures = new Goblin();

					cout << "Please enter the name for the fighter" << endl;
					getline(cin, name);

					team1.append(name);

					player1Creatures->setrealName(team1);

					player1Lineup.add(player1Creatures);
				}

				if (selection == "3")
				{
					string name;
					string team1 = "Team 1: ";
					ReptilePeople *reptile = NULL;
					player1Creatures = new ReptilePeople();

					cout << "Please enter the name for the fighter" << endl;
					getline(cin, name);

					team1.append(name);

					player1Creatures->setrealName(team1);

					player1Lineup.add(player1Creatures);
				}

				if (selection == "4")
				{
					string name;
					string team1 = "Team 1: ";
					BlueMen *blue = NULL;
					player1Creatures = new BlueMen();

					cout << "Please enter the name for the fighter" << endl;
					getline(cin, name);

					team1.append(name);

					player1Creatures->setrealName(team1);

					player1Lineup.add(player1Creatures);
				}

				if (selection == "5")
				{
					string name;
					string team1 = "Team 1: ";
					Shadow *shade = NULL;
					player1Creatures = new Shadow();

					cout << "Please enter the name for the fighter" << endl;
					getline(cin, name);

					team1.append(name);

					player1Creatures->setrealName(team1);

					player1Lineup.add(player1Creatures);
				}

			} 

			break;
		}

		case 2:
		{

			if (player2Lineup.isEmpty() == false)
			{
				cout << "\nLine up has already been created! " << endl;
				break;
			}

			for (int i = 0; i < numofFighters; i++)
			{

				string selection;
				cout << "\nPlease select fighter " << i + 1 << "." << endl;
				cout << "(1)Barbarian, (2)Goblin, (3)ReptilePeople, (4)BlueMen, (5)Shadow " << endl;
				cin >> selection;


				while (!(selection == "1" || selection == "2" || selection == "3" || selection == "4" || selection == "5"	))
				{
					cout << "That creature does not exist! Try again " << endl;
					cin >> selection;
				}

				cin.ignore();

				if (selection == "1")
				{
					string name;
					string team2 = "Team 2: ";
					Barbarian *barb = NULL;
					player2Creatures = new Barbarian();

					cout << "Please enter the name for the fighter" << endl;
					getline(cin, name);

					team2.append(name);

					player2Creatures->setrealName(team2);

					player2Lineup.add(player2Creatures);
				}

				if (selection == "2")
				{
					string name;
					string team2 = "Team 2: ";
					Goblin *gob = NULL;
					player2Creatures = new Goblin();

					cout << "Please enter the name for the fighter" << endl;
					getline(cin, name);

					team2.append(name);

					player2Creatures->setrealName(team2);

					player2Lineup.add(player2Creatures);
				}

				if (selection == "3")
				{
					string name;
					string team2 = "Team 2: ";
					ReptilePeople *reptile = NULL;
					player2Creatures = new ReptilePeople();

					cout << "Please enter the name for the fighter" << endl;
					getline(cin, name);

					team2.append(name);

					player2Creatures->setrealName(team2);

					player2Lineup.add(player2Creatures);
				}

				if (selection == "4")
				{
					string name;
					string team2 = "Team 2: ";
					BlueMen *blue = NULL;
					player2Creatures = new BlueMen();

					cout << "Please enter the name for the fighter" << endl;
					getline(cin, name);

					team2.append(name);

					player2Creatures->setrealName(team2);

					player2Lineup.add(player2Creatures);
				}

				if (selection == "5")
				{
					string name;
					string team2 = "Team 2: ";
					Shadow *shade = NULL;
					player2Creatures = new Shadow();

					cout << "Please enter the name for the fighter" << endl;
					getline(cin, name);

					team2.append(name);

					player2Creatures->setrealName(team2);

					player2Lineup.add(player2Creatures);
				}

			}
			break;
		}

		case 3:
		{

			// view line up

			string number;


			do
			{

				cout << "Which line up do you wish to view? (1)Player1 or (2)Player2? " << endl;
				cin >> number;

				if (number == "1")
				{

					if (player1Lineup.isEmpty() == true)
					{
						cout << "The lineup for player 1 is empty! " << endl;
						break;
					}

					else
					{
						player1Lineup.view();
						cout << endl;
					}

				}

				else if (number == "2")
				{

					if (player2Lineup.isEmpty() == true)
					{
						cout << "The lineup for player 2 is empty! " << endl;
					}

					else
					{
						player2Lineup.view();
						cout << endl;
					}

				}

				else
				{
					cout << "Must select (1)Player1 or (2)Player2. " << endl << endl;
				}

			} while (!(number == "1" || number == "2"));

			break;
		}



		case 4:
		{

			// view pile

			int number;

			cout << "Which pile do you wish to view? (1)Player1 or (2)Player2? " << endl;
			cin >> number;

			if (number == 1)
			{

				while (player1Loserpile.isEmpty() == true)
				{
					cout << "The pile for player 1 is empty! " << endl;
					break;
				}


				player1Loserpile.view();
				cout << endl;
				
			}

			else if (number == 2)
			{

				while (player2Loserpile.isEmpty()==true)
				{
					cout << "The pile for player 2 is empty! " << endl;
					break;
				}

				player2Loserpile.view();
				cout << endl;
				
			}


			else
			{
				cout << "Must select (1)Player1 or (2)Player2. " << endl;
			}

			break;
		}


		case 5:
		{
			// fight section

			if (player1Lineup.isEmpty() == true)
			{
				cout << "\nYou didn't create a team for player 1!! Create one first. " << endl;
				break;
			}

			else if (player2Lineup.isEmpty() == true)
			{
				cout << "\nYou didn't create a team for player 2!! Create one first. " << endl;
				break;
			}

			else
			{
				while (player1Lineup.isEmpty() == false  && player2Lineup.isEmpty() == false)
				{
					cout << "\nThe fight has begun.. " << endl;

					fightSimulator(player1Lineup.getCreature(), player2Lineup.getCreature());

					if (player1Lineup.getCreature()->liveCreature() == true)
					{
						// move the loser to loser's pile
						cout << player1Lineup.getCreature()->getrealName() << " has won." << endl;
						player2Loserpile.add(player2Lineup.getCreature());
						player2Lineup.remove();

						// give winner some healing and move it to end of line
						Creature *tempCreature = player1Lineup.getCreature();
						tempCreature->addPoint();
						tempCreature->replenish();

						player1Lineup.remove();
						player1Lineup.add(tempCreature);

						// give player 1 points for winning
						player1Points++;
					}

					else if (player2Lineup.getCreature()->liveCreature() == true)
					{
						// move the loser to loser's pile
						cout << player2Lineup.getCreature()->getrealName() << " has won." << endl;
						player1Loserpile.add(player1Lineup.getCreature());
						player1Lineup.remove();

						// give winner some healing and move it to end of line
						Creature *tempCreature = player2Lineup.getCreature();
						tempCreature->addPoint();
						tempCreature->replenish();

						player2Lineup.remove();
						player2Lineup.add(tempCreature);
						
						// give player 2 points for winning
						player2Points++;

				
					}

					if (player1Lineup.isEmpty() == true || player2Lineup.isEmpty() == true)
					{

						cout << "\nThe fight has finished.. " << endl;
						break;
					}

				}

				cout << endl;

				if (player1Points > player2Points)
				{
					cout << "Player 1 has won with " << player1Points << " points." << endl;
					cout << "Player 2 has lost with " << player2Points << " points." << endl;
				}

				else if (player2Points > player1Points)
				{
					cout << "Player 2 has won with " << player2Points << " points." << endl;
					cout << "Player 1 has lost with " << player1Points << " points." << endl;
				}
				
			}

			break;
		}

		case 6:
		{

			if (player1Points == 0 && player2Points == 0)
			{
				cout << "The fight hasn't happened yet! " << endl;
				break;
			}

			if (player1Lineup.isEmpty() == true && player2Lineup.isEmpty() == true)
			{
				cout << "There's no team! All sides are empty. " << endl;
				break;
			}

			int currentplaceFinish = 1;
			int currentfinisherScore;
			

			Queue *newPile = new Queue;
			
			// removing all combatants from every lineup and queue
			// and putting them into one big queue with sorted order
			for (int i = 0; player1Lineup.isEmpty()== false; i++)
			{

				Creature *tempCreature = player1Lineup.getCreature();
			
				player1Lineup.remove();
				newPile->addSort(tempCreature);
			}

			for (int i = 0;  player2Lineup.isEmpty() == false; i++)
			{
				Creature *tempCreature = player2Lineup.getCreature();

				player2Lineup.remove();
				newPile->addSort(tempCreature);
			}

			for (int i = 0; player1Loserpile.isEmpty() == false; i++)
			{
				Creature *tempCreature = player1Loserpile.getCreature();

				player1Loserpile.remove();
				newPile->addSort(tempCreature);
				
			}

			for (int i = 0; player2Loserpile.isEmpty() == false; i++)
			{
				Creature *tempCreature = player2Loserpile.getCreature();

				player2Loserpile.remove();
				newPile->addSort(tempCreature);
			}


			while(!(newPile->isEmpty()==true))
			{
				allPile.addSort(newPile->getCreature());
				newPile->remove();
			}

			// determining the top 3 
			while (currentplaceFinish <= 3 && (!(allPile.isEmpty() == true)))
			{
				
				Creature* tempCreature = allPile.getCreature();
				currentfinisherScore = tempCreature->getPoints();

				cout << "In place " << currentplaceFinish << " with " << currentfinisherScore << " points is " << allPile.getCreature()->getrealName() << endl;
				allPile.remove();

				currentplaceFinish++;
				tmpQueue.add(tempCreature);  // add top 3 back to temporary queue

			}


			// add top 3 from temporary queue back to allPile
			while (tmpQueue.isEmpty() == false)
			{
				allPile.addSort(tmpQueue.getCreature());
				tmpQueue.remove();
			}

			viewtop3 = true;
			delete newPile;

			break;
		}

		case 7:
		{
			if (allPile.isEmpty() == true)
			{
				cout << "Currently emptied or has been viewed already!" << endl;
			}

			else if (viewtop3 == false)
			{
				cout << "Top 3 has not been decided yet to view all orders of fighters " << endl;
				break;
			}

			else
			{
				cout << "\nThe final order of all the fighters after displaying the top 3 finishers are: " << endl;

				allPile.view();

			}

			break;
		}

		case 8:
		{
			exit(0);
		}

		default:
		{
			cout << endl;
			cout << "Not a choice, please enter a value between 1 and 8. " << endl;
			break;
		}
	
		} // end of switch statement

	} 

	
	delete player1Creatures;
	delete player2Creatures;

	return 0;

}