int update(void* canvas)
{
    char buffer[6];
    size_t cindex;
    uint8_t nindex;

    Client* node1;
    Client* node2;

    if(fscanf(stdin, "%s", buffer) && strcmp(buffer,"END"))
    {
        if(!strcmp(buffer, "LINK"))
        {
            if(!fscanf(stdin,"%zu", &cindex))
            {
                free(decisions);
                return 0;
            }
            if(!fscanf(stdin,"%hhu",&nindex))
            {
                free(decisions);
                return 0;
            }
            node1 = the_layout -> zones[cindex] -> buildings[nindex];
            if(!fscanf(stdin,"%hhu",&nindex))
            {
                free(decisions);
                return 0;
            }
            node2 = the_layout -> zones[cindex] -> buildings[nindex];

            struct choice c;
            c.choser = node1;
            c.chosee = node2;
            c.tinted = NULL;

            city_client_link(node1, node2);
            // node_link_print(node1, node2);
            if(node1 -> color != node2 -> color)
            {
                if(node1 -> color)
                {
                    client_paint(node2, node1 -> color);
                    c.tinted = node2;
                }
                else
                {
                    client_paint(node1, node2 -> color);
                    c.tinted = node1;
                }
            }
            decisions[decision_count++] = c;
        }
        else if(!strcmp(buffer,"UNDO"))
        {
            struct choice c = decisions[--decision_count];
            city_client_link_undo(c.choser, c.chosee);

            if(c.tinted)
            {
                client_paint(c.tinted, none);
            }
        }
        else
        {
            free(decisions);
            return 0;
        }

        /* TODO mandar a actualizar solo lo que ha cambiado */
        gtk_widget_queue_draw(canvas);

    }
    else
    {
        free(decisions);
        return 0;
    }
    return 1;
}