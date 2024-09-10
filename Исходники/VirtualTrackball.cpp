bool
VirtualTrackball::mouseMoved ( const MouseEvent* event )
{
        if ( !event->isLeftButtonPressed() ) return false;
        const Eigen::Vector3f p0 = this->_oldp;
        const Eigen::Vector3f p1 = this->project_on_sphere ( event->x(), event->y() );
        this->_oldp = p1;
        if ( ( p0 - p1 ).norm() < this->_eps ) return false; // do nothing
		//何か間違ってそうなので訂正してみる
        float radian = std::acos( p0.dot ( p1 ) )*0.5;
        const float cost = std::cos(radian);
        const float sint = std::sin(radian);
        //const float cost = p0.dot ( p1 );
        //const float sint = std::sqrt ( 1 - cost * cost );
        const Eigen::Vector3f axis = p0.cross ( p1 ).normalized();
        const Eigen::Quaternionf q ( -cost, sint * axis.x(), sint * axis.y(), sint * axis.z() );
        if( ( q.x()!=q.x() )|| ( q.y()!=q.y() )|| ( q.z()!=q.z() )|| ( q.w()!=q.w() ) ) return false;

        /*
        Eigen::Vector3f bmin , bmax;
        Mesh mesh;
        mesh = this->_model.getMesh();
        mesh.getBoundingBox(bmin,bmax);
        Eigen::Vector3f mc = (bmin + bmax)*0.5;
        Eigen::Vector3f c = Eigen::Matrix3f(q) * ( this->_model.getCamera().getCenter() - mc ) + mc ;
        this->_model.setCameraPosition(c.x(),c.y(),c.z());*/

        //this->_model.addRotation ( q );
        return true;
}