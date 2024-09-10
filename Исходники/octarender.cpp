 int addvert(const vertex &v)
 {
     uint h = hthash(v.pos)&(SIZE-1);
     for(int i = table[h]; i>=0; i = chain[i])
     {
         const vertex &c = verts[i];
         if(c.pos==v.pos && c.tc==v.tc && c.norm==v.norm && c.tangent==v.tangent && c.bitangent==v.bitangent)
              return i;
     }
     if(verts.length() >= USHRT_MAX) return -1;
     verts.add(v);
     chain.add(table[h]);
     return table[h] = verts.length()-1;
 }