void World::ResetCanalsTunnels()
{
    while (g_tunnel_list)
    {
        Old_Cont_Node * oldFirst    = g_tunnel_list;
        g_tunnel_list               = g_tunnel_list->m_next;
        delete oldFirst;
    }

    MapPoint pos;

    for (pos.x=0; pos.x<m_size.x; pos.x++) {
       for (pos.y=0; pos.y<m_size.y; pos.y++) {

           Cell * c = GetCell(pos);
           uint32 e = c->GetEnv();

           if ((e & k_BIT_MOVEMENT_TYPE_WATER) || (e & k_BIT_MOVEMENT_TYPE_SHALLOW_WATER))
           {
               if (e & k_MASK_ENV_CANAL_TUNNEL)
               {

                   sint32  old_cont_val = c->GetContinent();
                   if ((0 <= old_cont_val) && IsWater(pos))
                   {
                       g_tunnel_list = new Old_Cont_Node(pos, g_tunnel_list, old_cont_val);
                   }

                   c->SetContinent(INVALID_CONTINENT);
               }
           }
           else if ((e & k_BIT_MOVEMENT_TYPE_LAND) || (e & k_BIT_MOVEMENT_TYPE_MOUNTAIN))
           {
               c->SetContinent(INVALID_CONTINENT);
           }
       }
    }
}