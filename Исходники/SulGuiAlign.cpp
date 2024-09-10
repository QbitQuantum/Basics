void CSulGuiAlign::update()
{
	sigma::uint32 count = getNumChildren();
	for ( sigma::uint32 i=0; i<count ; i++ )
	{
		CSulGuiCanvas* p = dynamic_cast<CSulGuiCanvas*>(getChild(i));
		if ( p )
		{
			if ( m_eAlignH==H_CENTER )
			{
				float xx = (getW()/2.0f - p->getW()/2.0) + p->getX();

				// we write directly to the matrixtransform
				osg::Matrix m;
				m = p->getMatrix();
				osg::Vec3 pos = m.getTrans();
				pos.x() = xx;
				m.setTrans( pos );
				p->setMatrix( m );	
			}

			if ( m_eAlignH==H_RIGHT )
			{
				float xx = getW() - (p->getW()+p->getX());

				// we write directly to the matrixtransform
				osg::Matrix m;
				m = p->getMatrix();
				osg::Vec3 pos = m.getTrans();
				pos.x() = xx;
				m.setTrans( pos );
				p->setMatrix( m );	
			}

			if ( m_eAlignV==V_CENTER )
			{
				float yy = (getH()/2.0f - p->getH()/2.0) + p->getY();

				// we write directly to the matrixtransform
				osg::Matrix m;
				m = p->getMatrix();
				osg::Vec3 pos = m.getTrans();
				pos.y() = yy;
				m.setTrans( pos );
				p->setMatrix( m );	
			}

			if ( m_eAlignV==V_BOTTOM )
			{
				float yy = getH() - (p->getH()+p->getY());

				// we write directly to the matrixtransform
				osg::Matrix m;
				m = p->getMatrix();
				osg::Vec3 pos = m.getTrans();
				pos.y() = yy;
				m.setTrans( pos );
				p->setMatrix( m );	
			}
		}
	}
}