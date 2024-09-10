void RDBMSInterpreter::evaluateRules(const vector<Rule*>& rules)
{
  
  for(Rule* rule : rules)
    {
      
      queue<Relation> intermediate;
      
      Relation outputRelation;
      
      for(Predicate* predicate : rule->predicates())
        {
          map<string,Relation>::iterator it = m_relations.find(predicate->id());
          
          if(it != m_relations.end())
            {
              outputRelation = (*it).second;
              bool hasFree;
              outputRelation = outputRelation.performQuery(*predicate, hasFree);
              intermediate.push(outputRelation);
            }
        }
      
      outputRelation = intermediate.front();
      intermediate.pop();
      
      while (!intermediate.empty())
        {
          
          outputRelation = outputRelation.join(intermediate.front());
          
          intermediate.pop();
        }
      
      outputRelation =  outputRelation.project(rule->headPredicate().parameters());
      
      outputRelation.setName(rule->headPredicate().id());
      
      map<string,Relation>::iterator it = m_relations.find(outputRelation.name());
      
      if(it != m_relations.end())
        {
          Relation original =  (*it).second ;
          
          original = original.rename(original.attributes() , rule->headPredicate().parameters());
          
          outputRelation = original.unionR(outputRelation);
          
          m_relations[outputRelation.name()] = outputRelation;
          
        }
    }
}