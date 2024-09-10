 IGraphVertex * GetVertex(unsigned int hash) const
 {
     CComPtr<IGraphVertex> retVal = m_graph.GetVertex(hash);
     if (IsChild(retVal))
     {
         return retVal;
     }
     return NULL;
 }