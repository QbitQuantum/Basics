/*
	* autoPlay()
	*
	* Simulates a game of Red Rover and notifies the user of the winning team.
	*
	* Selects a random player from one team to attempt to break through a random player from the other team until one team has won.
	*
	* Starting with Team A, teams take turns attempting to break through.
	*
	* When the function ends, both teams should be emptied.
	*
	* this function returns nothing, but it MUST print out
	* 		the name of the runner
	* 		the name of the defender and
	* 		the players on each team
	* after each attempt to break through.
	*
	* At the end of the game, print out the name of the winning team and the players on both teams.
	*/
void RedRover::autoPlay()
{
    srand(time(0));
    int rand_index_runner = 0, rand_index_defender = 0, i = 0;
    
    PlayerInterface* runner = NULL;
    PlayerInterface* defender = NULL;
    
    bool playing = true;
    if (roster.size() < 4)
    {
        cout << "INSUFFICIENT PLAYERS\n\n";
        return;
    }
    
    createTeams();
    
    //cout << "TEAM A: " << getTeamA() << endl;
    //cout << "TEAM B: " << getTeamB() << endl << endl;
    
    while (playing)
    {
        if (i % 2 == 0)
        {   //cout << "I: " << i << "rand: " << rand() % 6 << endl;
            //team a turn

            rand_index_runner = rand() % getTeamASize(); // grab random player from A as runner
            runner = teamA.at(rand_index_runner);
            
            rand_index_defender = rand() % getTeamBSize(); // grab random player from B As Defender
            defender = teamB.at(rand_index_defender);
            
        }
        else if (i % 2 == 1)
        {
            //team b turn
            rand_index_runner = rand() % getTeamBSize(); // grab random player from B as runner
            runner = teamB.at(rand_index_runner);
            
            rand_index_defender = rand() % getTeamASize(); // grab random player from A As Defender
            defender = teamA.at(rand_index_defender);
        }
        
        cout << "RUNNER: " << runner->getName() << endl;
        cout << "DEFENDER: " << defender->getName() << endl << endl;
        
        sendSomeoneOver(runner, defender);
        
        if (teamA.size() > 1 && teamB.size() > 1)
        {
            cout << "TEAM A: " << getTeamA() << endl;
            cout << "TEAM B: " << getTeamB() << endl << endl;
        }
        else if (teamA.size() == 1 || teamB.size() == 1)
        {
            if (teamA.size() == 1)
            {
                cout << "Team A lost! " << getTeamA() << endl << endl;
            }
            else if (teamB.size() == 1)
            {
                cout << "Team B lost! " << getTeamB() << endl << endl;
            }
            playing = false;
        }
        i++;
    }
    
    teamReset();

}