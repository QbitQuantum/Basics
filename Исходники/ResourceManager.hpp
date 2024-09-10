 /** Requests a Resource. If it doesn't exist, create with loadResource().
  * @param key used to identify resource
  */
 virtual R* request ( const K& key )
 {
     auto search = _resources.find ( key );
     if ( search == _resources.end() )
     {
         std::pair<R*, uint32_t> c;
         c.first = loadResource ( key );
         c.second = 1;
         _resources.insert ( std::pair<K, std::pair<R*, uint32_t>> ( key, c ) );
         return c.first;
     }
     else
     {
         std::pair<R*, uint32_t> c = search->second;
         ++search->second.second;
         return c.first;
     }
 }