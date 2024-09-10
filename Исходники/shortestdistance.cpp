vector<Vertex*> ShortestDistance::shortestDistance(string &airport1, string &airport2)
{
    toUpper(airport1);
    toUpper(airport2);
    vector<Vertex*> vec;
    Vertex* u;
    set<Vertex*, Prioritize> Q;
    int starting_airport = -1, destination_airport = -1;
    for(map<int,Vertex*>::const_iterator mt = table.begin(); mt != table.end(); ++mt)
        if(!mt->second->airport_iata.empty())
        {
            if(!mt->second->airport_iata.compare(airport1))
                starting_airport = mt->second->airport_id;
            else if(!mt->second->airport_iata.compare(airport2))
                destination_airport = mt->second->airport_id;
        }
    if(starting_airport == -1)
    {
        cout << "Starting airport not found." << endl;
        return vec;
    }
    else if(destination_airport == -1)
    {
        cout << "Destination airport not found." << endl;
        return vec;
    }
    table[starting_airport]->cost = 0;
    Q.insert(table[starting_airport]);
    while(!Q.empty())
    {
        u = *Q.begin();
        if(u->airport_id == destination_airport)
        {
            while(table[u->airport_id]->prev)
            {
                vec.insert(vec.begin(), table[u->airport_id]->prev);
                u = table[u->airport_id]->prev;
            }
            vec.push_back(table[destination_airport]);
            return vec;
        }
        Q.erase(Q.begin());
        for(vector<Routes*>::iterator neighbor = u->routes.begin(); neighbor != u->routes.end(); ++neighbor)
        {
            double alt = u->cost + (*neighbor)->distance;
            if(alt < table[(*neighbor)->nextAirport]->cost)
            {
                table[(*neighbor)->nextAirport]->cost = alt;
                table[(*neighbor)->nextAirport]->prev = u;
                if(Q.find(table[(*neighbor)->nextAirport]) == Q.end())
                    Q.insert(table[(*neighbor)->nextAirport]);
            }
        }
    }
    return vec;
}