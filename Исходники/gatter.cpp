 /*
� * Calculates the gatter intersections and hoshis position
� */
void Gatter::resize(int offsetX, int offsetY, int square_size)
{
	int i,j;
	QGraphicsEllipseItem *e;
	QMapIterator<int,QGraphicsEllipseItem*> it( hoshisList );
	
	int size = square_size / 5;

	// Round size top be odd (hoshis)
	if (size % 2 == 0)
		size--;
	if ((size < 7) && (size>2))
		size = 7;
	else if (size <= 2)
		size = 3;
	

	for (i=0; i<board_size; i++)
		for (j=0; j<board_size; j++)
		{

			HGatter[i][j]->setLine(int(offsetX + square_size * ( i - 0.5*(i!=0))), 
						offsetY + square_size * j,
						int(offsetX + square_size * ( i + 0.5 * (i+1 != board_size))), 
						offsetY + square_size * j );
			
			VGatter[i][j]->setLine(offsetX + square_size *  i, 
						int(offsetY + square_size * ( j - 0.5*(j!=0))),
						offsetX + square_size *  i, 
						int(offsetY + square_size * ( j + 0.5 * (j+1 != board_size)))); 
			
			
			if (hoshisList.contains(board_size*(i+1)+j+1))
			{
				e = hoshisList.value(board_size*(i+1)+j+1);
				e->setRect(offsetX + square_size * i - size/2,
					offsetY + square_size * j- size/2,
					size , 
					size );
			}
		}

}