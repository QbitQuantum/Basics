bool fabric_t::build_lid_map(bool determine_lmc)
{
  ///Always start clean
  clear_lidmap();
  
  {
    const lmc_t max_lmc_lid = lmc > 0 ? (1 << lmc) - 1 : 0;
    
    /**
    * Walk every entity and build lid map
    */
    for(
      entities_t::iterator 
        itr = entities.begin(),
        eitr = entities.end();
      itr != eitr;
      ++itr
    )
    {
      assert(itr->second.lid() > 0);
      entity_t &entity = itr->second;
      const lid_t blid = entity.lid();
      assert(blid > 0);
      
      if(entity.get_type() == port_type::HCA)
        for(lmc_t i = 0; i <= max_lmc_lid; ++i)
        {
#ifndef NDEBUG
          std::cerr << "set HCA lid " << entity.label() << "(" << itr->first << std::hex << ") = " << regex::string_cast_uint(blid + i) << std::endl;
#endif
          assert(lidmap.find(blid + i) == lidmap.end());
          lidmap[blid + i] = &entity;
        }
      else 
        if(entity.get_type() == port_type::TCA) 
        { ///Switchs do not get a second LID
#ifndef NDEBUG
          {
            entitiesmap_lid_t::iterator itr = lidmap.find(blid);
            if(itr != lidmap.end())
            {
              std::cerr << "attempting fabric lmc = " << regex::string_cast_uint(lmc) << std::endl;
              std::cerr << "found existing port " << itr->second->label() <<  " on lid " << blid << std::endl;
              std::cerr << "was going to set port " << entity.label() <<  " on lid " << blid << std::endl;
              abort();
            }
          }
          std::cerr << "set TCA lid " << entity.label() << "(" << itr->first << std::hex << ") = " << regex::string_cast_uint(blid) << std::endl;
#endif
          lidmap[blid] = &entity;
        }
      else
        abort(); ///unknown port type?
    }
  }
  
  /**
    * attempt to determine LMC value of the subnet
    * this can be done with reasonable accuracy since
    * all lmc lid values are sequential for lmc > 0
    * 
    * this is the brute force solution O(ports)*lmc
    * basically, walk every port and see if there are any other lid+lmc
    * until the smalled lid, lid+lmc*, lid sequence is found 
    * then use lmc=log2(found)
    * 
    * LIDs = BASELID to BASELID + (2^LMC - 1)
    */
  if(determine_lmc)
  {
    using std::log;
    const lmc_t current_lmc = lmc;
    assert(portmap.size() > 1);
    
    ///Start off assuming max LMC value
    lmc_t max_lmc_lid = (1 << MAX_LMC_VALUE) - 1;
    entitiesmap_lid_t::const_iterator lid_end = lidmap.end();
    
    for(
      portmap_guidport_t::const_iterator
        itr = portmap.begin(),
        eitr = portmap.end();
      itr != eitr && max_lmc_lid > 0;
      ++itr
    )
      ///Only search LIDs of HCAs
      if(itr->second->type == port_type::HCA)
      {
#ifndef NDEBUG
        std::cerr << "search port " << itr->second->label() << std::endl;
#endif

        ///walk until highest seen lmc value offset
        for(lmc_t i = 1; i <= max_lmc_lid; ++i)
        {
          assert(itr->second->lid > 0);
          assert(lidmap.find(itr->second->lid) != lid_end);
          
          ///is there lid on base lid + lmc offset
          if(lidmap.find(itr->second->lid + i) != lid_end)
          {
#ifndef NDEBUG
            std::cerr << "found base lid " << itr->second->lid << " + " << regex::string_cast_uint(i) << " = " << itr->second->lid + i << " => collision\n";
#endif
            ///found collision, found new max lid offset
            max_lmc_lid = i - 1;
            break;
          }
#ifndef NDEBUG
          else
            std::cerr << "found base lid " << itr->second->lid << " + " << regex::string_cast_uint(i) << " = " << itr->second->lid + i << " => no collision\n";
#endif
        }
      }
    
#if __cplusplus <= 199711L
    lmc = (log(max_lmc_lid) / log(2)) + 1;
#else
    lmc = std::log2(max_lmc_lid) + 1;
#endif
    
    assert(lmc <= MAX_LMC_VALUE);
#ifndef NDEBUG
    std::cerr << "fabric lmc = " << regex::string_cast_uint(lmc) << " max lmc offset = " << regex::string_cast_uint(max_lmc_lid) << std::endl;
#endif
    
    ///LMC is new number so lid map is incomplete
    if(current_lmc != lmc)
      return build_lid_map(false);
  }
  
  return true;
}