void LevelGrid::InitializeLevel(void)
{
    // Give the level vertices some space
    this->m_LeftLevelVertices  = (hgeVector**) malloc(sizeof(hgeVector*) * this->m_NumY);
    this->m_RightLevelVertices = (hgeVector**) malloc(sizeof(hgeVector*) * this->m_NumY);

    // Create some storage for track indices
    this->m_LeftLevelIndices  = (unsigned int*) malloc(sizeof(unsigned int) * this->m_NumY);
    this->m_RightLevelIndices = (unsigned int*) malloc(sizeof(unsigned int) * this->m_NumY);

    // Retrieve the list of players to generate activators
    std::list<Player*> *p = this->m_PlayerManager->GetPlayers();

    // Constructed the grid vertices, now build the level
    for (int i = 0 ; i < this->m_NumY ; ++i)
    {
        // Construct the left and right vertexlist
        this->m_LeftLevelVertices[i]  = this->m_GridVertices[i][StartX];
        this->m_RightLevelVertices[i] = this->m_GridVertices[i][StartX + this->m_TrackWidth];

        // Store indices
        this->m_LeftLevelIndices[i]  = StartX;
        this->m_RightLevelIndices[i] = StartX + this->m_TrackWidth;

        // Only create a "turn" every 2 vertices vertical
        if (i % 2 == 0)
        {
            int lr = rand() % 3 - 1;

            if (StartX + lr < (this->m_NumX - this->m_TrackWidth) && StartX + lr > 0)
            {
                StartX += lr;
            }
        }
    }

    // Create a vector from the list, we need direct lookup
    std::vector<Player*> players(p->begin(), p->end());
    
    // Initialize the number of activators
    this->m_NumActivators = 0;

    // Only add activators whenever there are players
    if (players.size() > 0)
    {
        // Determine the vertical distribution for activators
        int verticalDistribution = this->m_NumY / (players.size() * NUM_ACTIVATORS);

        // Create the activator array
        this->m_Activators = (Activator**) malloc(sizeof(Activator*) * (this->m_NumActivators = NUM_ACTIVATORS * players.size()));

        // This feels a bit hackish...
        std::vector<std::vector<unsigned int>> activatorTypes;
        for (int i = 0 ; i < players.size() ; ++i)
        {
            std::vector<unsigned int> activators;
            for (int j = 0 ; j < NUM_ACTIVATORS ; ++j)
            {
                activators.push_back(j);
            }
            std::random_shuffle(activators.begin(), activators.end());
            activatorTypes.push_back(activators);
        }
        std::random_shuffle(activatorTypes.begin(), activatorTypes.end());

        // Retrieve viewport
        unsigned int width = this->m_Engine->GetWidth();
        unsigned int height = this->m_Engine->GetHeight();

        // Determine deltas
        float dx = width / this->m_NumX;
        float dy = height / this->m_NumY;

        // Define the activator length list
        ACTIVATOR_LENGTH_LIST;

        // Run through the players and then run though activators to make sure that
        // we're never generating two activators for one player in sequence
        int y = 0;
        int n = 0;
        std::vector<std::vector<unsigned int>>::const_iterator it;
        for (int i = 0 ; i < NUM_ACTIVATORS ; ++i)
        {
            int k = 0;
            for (it = activatorTypes.begin() ; it != activatorTypes.end() ; ++it)
            {
                // Fetch a random int between left and right on track y
                int x = (rand() % ((this->m_RightLevelIndices[y] - 2) - (this->m_LeftLevelIndices[y] + 2))) + (this->m_LeftLevelIndices[y] + 2);
        
                // Fetch the activator type pointed to by i
                unsigned int activatorType = (*it).at(i);

                // Offset y in some direction
                srand(x * y);
                int offsetY = rand() % 5;
            
                if (y + offsetY >= this->m_NumY)
                {
                    y -= offsetY;
                }
                else
                {
                    y += offsetY;
                }

                // Get the selected vertex
                hgeVector *vec = this->m_GridVertices[y][x];

                // Create a new activator instance
                Activator *activator = new Activator();

                // Set the type
                activator->ActivatorType = activatorType;

                // Set the owner
                activator->Owner = players.at(k++);

                // In case the activator type is one of type weapon (pickup), add a random weapon to the activator
                if (activatorType == ACTIVATOR_TYPE_WEAPON)
                {
                    // Get a random index
                    int index = rand() % NUM_WEAPONS;

                    switch (index)
                    {
                        case WEAPON_INDEX_NEOSHOOTER:
                            activator->Data = new Neoshooter(activator->Owner, this->m_Engine->GetWorld());
                            break;
                        case WEAPON_INDEX_TRISCEPTRE:
                            activator->Data = new Trisceptre(activator->Owner, this->m_Engine->GetWorld());
                            break;
                    }
                }
            
                // Define the vertices
                activator->Vertices[0] = *vec; activator->Vertices[1] = *vec;
                activator->Vertices[2] = *vec; activator->Vertices[3] = *vec;

                // Offset the vertices conform winding
                activator->Vertices[1].x -= dx;
                activator->Vertices[2].x -= dx; activator->Vertices[2].y -= dy * ACTIVATOR_LENGTH_LIST_NAME[activatorType];
                activator->Vertices[3].y -= dy * ACTIVATOR_LENGTH_LIST_NAME[activatorType];

                // Add the activator
                this->m_Activators[n++] = activator;
            }

            // Increase the vertical pointer
            y += verticalDistribution;
        }
    }
}