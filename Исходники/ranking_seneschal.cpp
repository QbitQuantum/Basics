bool ranking_synthesis_seneschalt::read_output(exprt &rf)
{
  // Check if there is a result at all...
  std::ifstream err("seneschal.err");
  bool result_found=false;
  while(err)
  {
    std::string line;
    std::getline(err, line);

    if(line=="Solving ... no solution" ||
       line=="Solving ... found a solution")
    {
      result_found = true;
      break;
    }
  }
  err.close();

  if(!result_found) return false;

  // There is a result!
  std::ifstream in("seneschal.out");

  std::string rank_string;
  std::string bound_string;

  while(in)
  {
    std::string line;

    std::getline(in, line);

    if(line.substr(0,7)=="Ranking")
    {
      std::vector<std::string> tokens;
      tokenize(line, tokens, " =[],\tr");

      bool work=false;
      for(std::vector<std::string>::const_iterator it=tokens.begin();
          it!=tokens.end();
          it++)
      {
        // std::cout << "TOKEN: " << *it << std::endl;

        if(*it=="Ranking")
        {
          result_found=true;
          work=true;
        }
        else if(*it=="function:") /* SKIP */ ;
        else if(work)
        {
          rank_string += " " + *it;
        }
      }
    }
    else if(line.substr(0,25)=="Lower bound (post-state):")
    {
      std::vector<std::string> tokens;
      tokenize(line, tokens, " =[],\t");

      std::vector<std::string>::const_iterator it=tokens.begin();
      it++; it++; it++;
      if(it!=tokens.end())
      {
        //std::cout << "TOKEN: " << *it << std::endl;

        bound_string = *it;
      }
    };
  }

  if(rank_string!="")
  {
    bound = string2integer(bound_string);

    if(bound!=0)
      rank_string = "(" + rank_string + ") - (" + bound_string + ")";

    exprt rfl;

    if(parse_rank_function(rank_string, trans_context, ns, *message_handler, rfl))
      throw ("RF EXTRACTION ERROR");

    replace_expr(variable_map, rfl);
    std::cout << "FOUND FUNCTION: " << from_expr(ns, "", rfl) << std::endl;

    rf.swap(rfl);

    std::cout << "BOUND: " << bound << std::endl;
  }
    
  return true;
}