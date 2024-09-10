void sparql_parser::remove_header(vector<string>& token_vec){
    vector<string> new_vec;
    int iter=0;
    while(token_vec.size()>iter && token_vec[iter]=="PREFIX"){
        if(token_vec.size()>iter+2){
            prefix_map[token_vec[iter+1]]=token_vec[iter+2];
            iter+=3;
        } else {
            valid=false;
            return ;
        }
    }
    /// TODO More Check!
    while(token_vec[iter]!="{"){
        iter++;
    }
    iter++;

    while(token_vec[iter]!="}"){
        if(token_vec[iter]=="join"){
            join_step=new_vec.size()/4;
            iter++;
            continue;
        }
        if(token_vec[iter]=="fork"){
            fork_step=new_vec.size()/4;
            iter++;
            continue;
        }
        new_vec.push_back(token_vec[iter]);
        iter++;
    }
    token_vec.swap(new_vec);
}