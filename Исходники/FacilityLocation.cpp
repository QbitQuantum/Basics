int FacilityLocation::createConsAssignment()
{
	int numCons = 0;
	VariableHash::iterator vit;
	Row::ROWSENSE sense = Row::EQUAL;
	int maxnnz = (g->nVertices - g->nTerminals) + 1;
	double rhs = 1.0;

	for (int i = 1; i <= g->nVertices; ++i)
	{
		Vertex client = g->vertices[i];

		if (!client.isTerminal())
			continue;

		Constraint c(maxnnz, sense, rhs);
		c.setType(Constraint::C_ASSIGNMENT);
		c.setNode(client);

		Variable x;
		x.setType(Variable::V_X);

		for (int j = 1; j <= g->nVertices; ++j)
		{
			Vertex router = g->vertices[j];

			// @annotation: comment next filter to resolve instances where
			// the vpn terminals may be considered internal nodes
			// 20160125
			if (client == router || router.isTerminal())
				continue;

			x.setArc(Arc(router, client, 0.));

			vit = vHash[Variable::V_X].find(x);
			if (vit != vHash[Variable::V_X].end())
			{
				int colVarX = vit->second;
				c.rowAddVar(colVarX, 1.0);
			}
		}

		if (c.getRowNnz() > 0)
		{
			bool isInserted = addRow(&c);

			if (isInserted)
			{
				c.setRowIdx(getNRows() - 1);
				cHash[c] = c.getRowIdx();
				numCons++;
			}
		}
	}

	return numCons;
}