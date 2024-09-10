void CFruchtermanReingold::CalculateForces() {
       //Coulomb force
       for(int i = 0; i < vgc_nodes_num; ++i) {
              QVector2D force;
              if(!vgc_graph->vertice_exists(i)) continue;
              for(int j = 0; j < vgc_nodes_num; ++j) {
                     if(i == j || !vgc_graph->vertice_exists(j)) continue;
                     force += CoulombForce(i, j);
              }
              vgc_vertices[i].v_force = force;
       }

       //Hooke force
       for(int i = 0; i < vgc_nodes_num; ++i) {
              QVector2D force;
              for(int j = 0; j < vgc_nodes_num; ++j) {
                     if(i == j) continue;
                     else if(vgc_graph->edge_exists(i, j)) force += HookeForce(i, j);             //TODO: oriented graph?
              }
              vgc_vertices[i].v_force += force;
       }

       //Barrier force
       for(int i = 0; i < vgc_nodes_num; ++i) Reflect(i);
}