 twRect rectForItem(int index) const{
     twRect rt=getClientRect();
     rt.x=0; rt.y=m_rowHeight*index;
     rt.h=m_rowHeight;
     return rt;
 }