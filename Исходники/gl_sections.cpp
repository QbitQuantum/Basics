void DumpSection(int no, FGLSection *sect)
{
	Printf(PRINT_LOG, "Section %d, sector %d\n{\n", no, sect->sector->sectornum);

	for(int i = 0; i < sect->numloops; i++)
	{
		Printf(PRINT_LOG, "\tLoop %d\n\t{\n", i);

		FGLSectionLoop *loop = sect->GetLoop(i);

		for(int i = 0; i < loop->numlines; i++)
		{
			FGLSectionLine *ln = loop->GetLine(i);
			if (ln->sidedef != NULL)
			{
				vertex_t *v1 = V1(ln->sidedef);
				vertex_t *v2 = V2(ln->sidedef);
				double dx = FIXED2FLOAT(v2->x-v1->x);
				double dy = FIXED2FLOAT(v2->y-v1->y);
				double dx1 = FIXED2FLOAT(ln->start->x-v1->x);
				double dy1 = FIXED2FLOAT(ln->start->y-v1->y);
				double dx2 = FIXED2FLOAT(ln->end->x-v1->x);
				double dy2 = FIXED2FLOAT(ln->end->y-v1->y);
				double d = sqrt(dx*dx+dy*dy);
				double d1 = sqrt(dx1*dx1+dy1*dy1);
				double d2 = sqrt(dx2*dx2+dy2*dy2);

				Printf(PRINT_LOG, "\t\tLinedef %d, %s: Start (%1.2f, %1.2f), End (%1.2f, %1.2f)", 
					ln->linedef - lines, ln->sidedef == ln->linedef->sidedef[0]? "front":"back",
					ln->start->x/65536.f, ln->start->y/65536.f,
					ln->end->x/65536.f, ln->end->y/65536.f);

				if (ln->otherside != -1)
				{
					Printf (PRINT_LOG, ", other side = %d", ln->otherside);
				}
				if (d1 > 0.005 || d2 < 0.995)
				{
					Printf(PRINT_LOG, ", Range = %1.3f, %1.3f", d1/d, d2/d);
				}
			}
			else
			{
				Printf(PRINT_LOG, "\t\tMiniseg: Start (%1.3f, %1.3f), End (%1.3f, %1.3f)\n", 
					ln->start->x/65536.f, ln->start->y/65536.f, ln->end->x/65536.f, ln->end->y/65536.f);

				if (ln->otherside != -1)
				{
					Printf (PRINT_LOG, ", other side = %d", ln->otherside);
				}
			}
			Printf(PRINT_LOG, "\n");
		}
		Printf(PRINT_LOG, "\t}\n");
	}
	int prim = 1;
	for(unsigned i = 0; i < sect->vertices.Size(); i++)
	{
		int v = sect->vertices[i];
		if (v < 0)
		{
			if (i > 0)
			{
				Printf(PRINT_LOG, "\t}\n");
			}
			switch (v)
			{
			case -GL_TRIANGLE_FAN:
				Printf(PRINT_LOG, "\t%d: Triangle fan\n\t{\n", prim);
				break;

			case -GL_TRIANGLE_STRIP:
				Printf(PRINT_LOG, "\t%d: Triangle strip\n\t{\n", prim);
				break;

			case -GL_TRIANGLES:
				Printf(PRINT_LOG, "\t%d: Triangles\n\t{\n", prim);
				break;

			default:
				break;
			}
			prim++;
		}
		else
		{
			Printf(PRINT_LOG, "\t\tVertex %d: (%1.2f, %1.2f)\n", 
				v, vertexes[v].x/65536.f, vertexes[v].y/65536.f);
		}
	}
	Printf(PRINT_LOG, "}\n\n");
}