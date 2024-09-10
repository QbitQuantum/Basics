void game_state::periodic_team_broadcast()
{
    static sf::Clock clk;

    ///once per second
    float broadcast_every_ms = 1000.f;

    if(clk.getElapsedTime().asMicroseconds() / 1000.f < broadcast_every_ms)
        return;

    clk.restart();

    for(auto& i : player_list)
    {
        ///network
        byte_vector vec;
        vec.push_back(canary_start);
        vec.push_back(message::TEAMASSIGNMENT);
        vec.push_back<int32_t>(i.id);
        vec.push_back<int32_t>(i.team);
        vec.push_back(canary_end);

        //printf("Team ass %i team player %i\n", i.team, i.id);

        int no_player = -1;

        broadcast(vec.ptr, no_player);
    }
}