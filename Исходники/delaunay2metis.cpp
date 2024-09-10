static void output_vertices (vertex_db & vertices)
{
    std::string tmp_file_name = "tmpidmap";
    boost::shared_ptr<SpatialIndex::IStorageManager>
        tmp_file (SpatialIndex::StorageManager::createNewDiskStorageManager (
                      tmp_file_name,page_size));
    idmap_t idmap (tmp_file, page_size);

    vertex_db::iterator v_start = vertices.begin ();
    vertex_db::iterator v_ptr = v_start;

    ofstream myfile;
    myfile.open ("example.txt");

    long v_id = 1;
    long edges = 0;
//    map<vertex_id,long> idmap;

    while (v_ptr != vertices.end ())
    {
        edges += ((vertex_info)v_ptr->second).neighbours.size ();

//	idmap.insert(pair<vertex_id,long>((vertex_id)v_ptr->first,v_id));
        idmap.insert (v_ptr->first, v_id);
	v_id++;
        v_ptr++;
    }
   
    v_id--; 
    ldiv_t divresult = ldiv(edges,2);
    myfile << v_id << " " << divresult.quot << " 0\n";

    v_start = vertices.begin ();
    v_ptr = v_start;
    v_id = 1;
  
    while (v_ptr != vertices.end ())
    {
        std::vector<vertex_id> n = ((vertex_info)v_ptr->second).neighbours;
        vertex_id id = (vertex_id)v_ptr->first;

//                map<vertex_id,long>::iterator it;

//        it = idmap.find(id);
        std::cout << get_remapped_vertex (idmap, id) << " : ";
        //std::cout << it->second << " : ";

        BOOST_FOREACH (vertex_id n_id, n)
        {
//                it = idmap.find(n_id);
                myfile << get_remapped_vertex (idmap, n_id) << " ";
        }

        myfile << endl;

        v_id++;
        v_ptr++;
    }