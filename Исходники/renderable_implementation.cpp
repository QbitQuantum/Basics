LineRenderable::LineRenderable(const LineSymbol* symbol, const VirtualPath& virtual_path, bool closed)
 : Renderable(symbol->getColor())
 , line_width(0.001f * symbol->getLineWidth())
{
	Q_ASSERT(virtual_path.size() >= 2);
	
	float half_line_width = (color_priority < 0) ? 0.0f : 0.5f * line_width;
	
	switch (symbol->getCapStyle())
	{
		case LineSymbol::FlatCap:		cap_style = Qt::FlatCap;	break;
		case LineSymbol::RoundCap:		cap_style = Qt::RoundCap;	break;
		case LineSymbol::SquareCap:		cap_style = Qt::SquareCap;	break;
		case LineSymbol::PointedCap:	cap_style = Qt::FlatCap;	break;
	}
	switch (symbol->getJoinStyle())
	{
		case LineSymbol::BevelJoin:		join_style = Qt::BevelJoin;	break;
		case LineSymbol::MiterJoin:		join_style = Qt::MiterJoin;	break;
		case LineSymbol::RoundJoin:		join_style = Qt::RoundJoin;	break;
	}
	
	auto& flags  = virtual_path.coords.flags;
	auto& coords = virtual_path.coords;
	
	bool has_curve = false;
	bool hole = false;
	bool gap = false;
	QPainterPath first_subpath;
	
	auto i = virtual_path.first_index;
	path.moveTo(coords[i]);
	extent = QRectF(coords[i].x(), coords[i].y(), 0.0001f, 0.0001f);
	extentIncludeCap(i, half_line_width, false, symbol, virtual_path);
	
	for (++i; i <= virtual_path.last_index; ++i)
	{
		if (gap)
		{
			if (flags[i].isHolePoint())
			{
				gap = false;
				hole = true;
			}
			else if (flags[i].isGapPoint())
			{
				gap = false;
				if (first_subpath.isEmpty() && closed)
				{
					first_subpath = path;
					path = QPainterPath();
				}
				path.moveTo(coords[i]);
				extentIncludeCap(i, half_line_width, false, symbol, virtual_path);
			}
			continue;
		}
		
		if (hole)
		{
			Q_ASSERT(!flags[i].isHolePoint() && "Two hole points in a row!");
			if (first_subpath.isEmpty() && closed)
			{
				first_subpath = path;
				path = QPainterPath();
			}
			path.moveTo(coords[i]);
			extentIncludeCap(i, half_line_width, false, symbol, virtual_path);
			hole = false;
			continue;
		}
		
		if (flags[i-1].isCurveStart())
		{
			Q_ASSERT(i < virtual_path.last_index-1);
			has_curve = true;
			path.cubicTo(coords[i], coords[i+1], coords[i+2]);
			i += 2;
		}
		else
			path.lineTo(coords[i]);
		
		if (flags[i].isHolePoint())
			hole = true;
		else if (flags[i].isGapPoint())
			gap = true;
		
		if ((i < virtual_path.last_index && !hole && !gap) || (i == virtual_path.last_index && closed))
			extentIncludeJoin(i, half_line_width, symbol, virtual_path);
		else
			extentIncludeCap(i, half_line_width, true, symbol, virtual_path);
	}
	
	if (closed)
	{
		if (first_subpath.isEmpty())
			path.closeSubpath();
		else
			path.connectPath(first_subpath);
	}
	
	// If we do not have the path coords, but there was a curve, calculate path coords.
	if (has_curve)
	{
		//  This happens for point symbols with curved lines in them.
		const auto& path_coords = virtual_path.path_coords;
		Q_ASSERT(path_coords.front().param == 0.0);
		Q_ASSERT(path_coords.back().param == 0.0);
		for (auto i = path_coords.size()-1; i > 0; --i)
		{
			if (path_coords[i].param != 0.0)
			{
				const auto& pos = path_coords[i].pos;
				auto to_coord   = pos - path_coords[i-1].pos;
				auto to_next    = path_coords[i+1].pos - pos;
				to_coord.normalize();
				to_next.normalize();
				auto right = (to_coord + to_next).perpRight();
				right.setLength(half_line_width);
				
				rectInclude(extent, pos + right);
				rectInclude(extent, pos - right);
			}
		}
	}
	Q_ASSERT(extent.right() < 999999);	// assert if bogus values are returned
}