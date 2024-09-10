void GameLevel::AttachClusters(LevelRoom rooms[], int numRooms)
{
    std::cout << "attaching clusters..." << std::endl;
    int clusters;
    do
    {
        std::cout << "\tattachment pass" << std::endl;
        clusters = 0;
        int floodFillMap[LEVEL_WIDTH * LEVEL_HEIGHT];
        for (int c = 0; c < LEVEL_WIDTH; c++)
            for (int r = 0; r < LEVEL_HEIGHT; r++)
            {
                switch (tileMap[c][r].TileType)
                {
                    case ' ':
                        floodFillMap[c + r * LEVEL_WIDTH] = -2;
                        break;
                    case '#':
                        floodFillMap[c + r * LEVEL_WIDTH] = -1;
                        break;
                    case '+':
                    case '.':
                    case 'H':
                        floodFillMap[c + r * LEVEL_WIDTH] = 0;
                        break;
                }
            }

        std::vector<LevelRoom> floodClusters;
        for (int c = 0; c < LEVEL_WIDTH; c++)
            for (int r = 0; r < LEVEL_HEIGHT; r++)
            {
                if (floodFillMap[c + r * LEVEL_WIDTH] != 0) continue;
                else floodClusters.push_back(FloodFill(floodFillMap, c, r, ++clusters));
            }
        std::cout << "\tNumber of room clusters: " << clusters << std::endl;
        if (clusters > 1)
        {
            int numClusters = (int)floodClusters.size();
            bool attached[numClusters * numClusters];

            for (int i = 0; i < numClusters; i++)
                for (int j = 0; j < numClusters; j++)
                    attached[i + j * numClusters] = false;

            for (int i = 0; i < numRooms; i++)
                rooms[i].Cluster = floodFillMap[rooms[i].Left + rooms[i].Top * LEVEL_WIDTH];

            for (int i = 0; i < numClusters; i++)
            {
                int ia, ja;
                int j = FindClosestClusterRoom(rooms, numRooms, i + 1, ia, ja);
                std::cout << "\tClosest cluster to " << i + 1 << ": " << j << std::endl;
                if (attached[i + j * numClusters]) continue;
                attached[i + j * numClusters] = true;
                attached[j + i * numClusters] = true;
                std::cout << "\tfinding point to attached..." << std::endl;
                int aX, aY, bX, bY;
                if (rooms[ia].Right < rooms[ja].Left)
                    aX = RandomGen::GetInt(rooms[ia].GetMidPtX(), rooms[ia].Right - 1);
                else
                    aX = RandomGen::GetInt(rooms[ia].Left, rooms[ia].GetMidPtX());
                if (rooms[ia].Right < rooms[ja].Left)
                    bX = RandomGen::GetInt(rooms[ja].Left, rooms[ja].GetMidPtX());
                else
                    bX = RandomGen::GetInt(rooms[ja].GetMidPtX(), rooms[ja].Right - 1);
                aY = rooms[ia].Bottom - 1;
                bY = rooms[ja].Bottom - 1;
                std::cout << "\tcreating corridor between (" << aX << "," << aY << ") and (" << bX << ", " << bY << ")";

                while ((aX != bX) || (aY != bY))
                {
                   if (aY != bY)
                   {
                       if (aY < bY) bY--;
                       else bY++;
                       tileMap[bX][bY].TileType = 'H';
                   }
                   else if (aX != bX)
                   {
                       if (aX < bX) bX--;
                       else bX++;
                       if (tileMap[bX][bY].TileType != 'H') tileMap[bX][bY].TileType = '+';
                   }
                   std::cout << ".";
                }
                std::cout << "done." << std::endl;
            }
        }

        bool allBlanks;
        for (int r = 0; r < LEVEL_HEIGHT; r++)
        {
            allBlanks = true;
            for (int c = 0; c < LEVEL_WIDTH; c++)
                if (floodFillMap[c + r * LEVEL_WIDTH] != -2) allBlanks = false;
            if (allBlanks) continue;
            for (int c = 0; c < LEVEL_WIDTH; c++)
            {
                int floodVal = floodFillMap[c + r * LEVEL_WIDTH];
                if (floodVal == -2) std::cout << ' ';
                else if (floodVal == -1) std::cout << '#';
                else std::cout << floodVal % 10;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    } while (clusters > 1);
}