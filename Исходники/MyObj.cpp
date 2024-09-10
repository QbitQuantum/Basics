void MyObj::Draw(CDC &dc){
dc.MoveTo(m_dCenterX,m_dCenterY); 
dc.LineTo(m_dCenterX,m_dCenterY-m_dA/2+m_dA1); 
dc.MoveTo(m_dCenterX,m_dCenterY-m_dA+m_dA1/2); 
dc.AngleArc(m_dCenterX,m_dCenterY-m_dA/2,m_dA1,90,180); 
dc.MoveTo(m_dCenterX,m_dCenterY-m_dA+m_dA1/2); 
dc.LineTo(m_dCenterX,m_dCenterY-m_dA); 
dc.LineTo(m_dCenterX-m_dA+m_dA2,m_dCenterY-m_dA); 
dc.AngleArc(m_dCenterX-m_dA+m_dA2,m_dCenterY-m_dA+m_dA2,m_dA2,90,90); 
dc.LineTo(m_dCenterX-m_dA,m_dCenterY-m_dA3); 
dc.MoveTo(m_dCenterX-m_dA+m_dA3,m_dCenterY); 
dc.AngleArc(m_dCenterX-m_dA,m_dCenterY,m_dA3,0,90); 
dc.MoveTo(m_dCenterX-m_dA+m_dA3,m_dCenterY); 
dc.LineTo(m_dCenterX,m_dCenterY);
}