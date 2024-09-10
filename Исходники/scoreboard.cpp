 static int groupplayers()
 {
     int numgroups = 0;
     spectators.shrink(0);
     loopv(players)
     {
         fpsent *o = players[i];
         if(!showconnecting && !o->name[0]) continue;
         if(o->state==CS_SPECTATOR) { spectators.add(o); continue; }
         const char *team = m_teammode && o->team[0] ? o->team : NULL;
         bool found = false;
         loopj(numgroups)
         {
             scoregroup &g = *groups[j];
             if(team!=g.team && (!team || !g.team || strcmp(team, g.team))) continue;
             if(team && (!cmode || !cmode->hidefrags())) g.score += o->frags;
             g.players.add(o);
             found = true;
         }
         if(found) continue;
         if(numgroups>=groups.length()) groups.add(new scoregroup);
         scoregroup &g = *groups[numgroups++];
         g.team = team;
         if(!team) g.score = 0;
         else if(cmode && cmode->hidefrags()) g.score = cmode->getteamscore(o->team);
         else g.score = o->frags;
         g.players.shrink(0);
         g.players.add(o);
     }
     loopi(numgroups) groups[i]->players.sort(playersort);
     spectators.sort(playersort);
     groups.sort(scoregroupcmp, 0, numgroups);
     return numgroups;
 }