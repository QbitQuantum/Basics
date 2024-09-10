bool UniGridApprox::SurfMeshParam()
{
    // hier wird das in MeshOffset erzeugte gitter parametrisiert
    // parametrisierung: (x,y) -> (u,v)  ,  ( R x R ) -> ( [0,1] x [0,1] )

    int n = m_Grid.size()-1;      // anzahl der zu approximierenden punkte in x-richtung
    int m = m_Grid[0].size()-1;   // anzahl der zu approximierenden punkte in y-richtung

    std::vector<double> dist_x, dist_y;
    double sum,d;
    Base::Vector3f vlen;

    m_uParam.clear();
    m_vParam.clear();
    m_uParam.resize(n+1);
    m_vParam.resize(m+1);
    m_uParam[n] = 1.0;
    m_vParam[m] = 1.0;

    // berechne knotenvektor in u-richtung (entspricht x-richtung)
    for (int j=0; j<m+1; ++j)
    {
        sum = 0.0;
        dist_x.clear();
        for (int i=0; i<n; ++i)
        {
            vlen = (m_Grid[i+1][j] - m_Grid[i][j]);
            dist_x.push_back(vlen.Length());
            sum += dist_x[i];
        }
        d = 0.0;
        for (int i=0; i<n-1; ++i)
        {
            d += dist_x[i];
            m_uParam[i+1] = m_uParam[i+1] + d/sum;
        }
    }

    for (int i=0; i<n; ++i)
        m_uParam[i] /= m+1;

    // berechne knotenvektor in v-richtung (entspricht y-richtung)
    for (int i=0; i<n+1; ++i)
    {
        sum = 0.0;
        dist_y.clear();
        for (int j=0; j<m; ++j)
        {
            vlen = (m_Grid[i][j+1] - m_Grid[i][j]);
            dist_y.push_back(vlen.Length());
            sum += dist_y[j];
        }
        d = 0.0;
        for (int j=0; j<m-1; ++j)
        {
            d += dist_y[j];
            m_vParam[j+1] = m_vParam[j+1] + d/sum;
        }
    }

    for (int j=0; j<m; ++j)
        m_vParam[j] /= n+1;

    /*cout << "uParam:" << endl;
    for(int i=0; i<m_uParam.size(); ++i){
     cout << " " << m_uParam[i] << ", " << endl;
    }

    cout << "vParam:" << endl;
    for(int i=0; i<m_vParam.size(); ++i){
     cout << " " << m_vParam[i] << ", " << endl;
    }*/

    return true;
}