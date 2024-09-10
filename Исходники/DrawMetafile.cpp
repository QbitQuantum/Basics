void CDrawMetaFile::setMetaFile( HENHMETAFILE data )
{
	HENHMETAFILE copy = CopyEnhMetaFile( data, NULL );

	ENHMETAHEADER hdr;
	GetEnhMetaFileHeader( data, sizeof(hdr), &hdr );

	double width = fabs(static_cast<double>(hdr.rclFrame.left - hdr.rclFrame.right) ) ;
	double height = fabs(static_cast<double>(hdr.rclFrame.bottom - hdr.rclFrame.top) ) ;

	m_point_b.x = fabs(static_cast<double>(m_point_b.y - m_point_a.y)) * height / width;

	m_metafile = m_pDesign->GetOptions()->AddMetaFile( new CImageMetafile( copy ) );
}