struct model *load_obj_from_memory(const char *filename, unsigned char *data, int len)
{
	char dirname[1024];
	char *line, *next, *p, *s;
	struct model *model;
	struct mesh *mesh;
	int fvp[20], fvt[20], fvn[20];
	int first, material;
	int i, n;

	printf("loading obj model '%s'\n", filename);

	strlcpy(dirname, filename, sizeof dirname);
	p = strrchr(dirname, '/');
	if (!p) p = strrchr(dirname, '\\');
	if (p) *p = 0;
	else strlcpy(dirname, "", sizeof dirname);

	mtl_count = 0;
	position.len = 0;
	texcoord.len = 0;
	normal.len = 0;
	element.len = 0;
	part.len = 0;

	first = 0;
	material = 0;

	data[len-1] = 0; /* over-write final newline to zero-terminate */

	for (line = (char*)data; line; line = next) {
		next = strchr(line, '\n');
		if (next)
			*next++ = 0;

		s = strtok(line, SEP);
		if (!s) {
			continue;
		} else if (!strcmp(s, "v")) {
			char *x = strtok(NULL, SEP);
			char *y = strtok(NULL, SEP);
			char *z = strtok(NULL, SEP);
			add_position(atof(x), atof(y), atof(z));
		} else if (!strcmp(s, "vt")) {
			char *u = strtok(NULL, SEP);
			char *v = strtok(NULL, SEP);
			add_texcoord(atof(u), atof(v));
		} else if (!strcmp(s, "vn")) {
			char *x = strtok(NULL, SEP);
			char *y = strtok(NULL, SEP);
			char *z = strtok(NULL, SEP);
			add_normal(atof(x), atof(y), atof(z));
		} else if (!strcmp(s, "f")) {
			n = 0;
			s = strtok(NULL, SEP);
			while (s) {
				if (*s) {
					splitfv(s, fvp+n, fvn+n, fvt+n);
					n++;
				}
				s = strtok(NULL, SEP);
			}
			for (i = 1; i < n - 1; i++) {
				add_triangle(fvp[0], fvn[0], fvt[0],
					fvp[i], fvn[i], fvt[i],
					fvp[i+1], fvn[i+1], fvt[i+1]);
			}
		} else if (!strcmp(s, "mtllib")) {
			s = strtok(NULL, SEP);
			mtllib(dirname, s);
		} else if (!strcmp(s, "usemtl")) {
			if (element.len > first)
				push_part(&part, first, element.len, material);
			s = strtok(NULL, SEP);
			material = usemtl(s);
			first = element.len;
		}
	}

	if (element.len > first)
		push_part(&part, first, element.len, material);

	printf("\t%d parts; %d vertices; %d triangles", part.len, vertex.len/8, element.len/3);

	mesh = malloc(sizeof(struct mesh));
	mesh->tag = TAG_MESH;
	mesh->enabled = 1<<ATT_POSITION | 1<<ATT_NORMAL | 1<<ATT_TEXCOORD;
	mesh->skel = NULL;
	mesh->inv_bind_matrix = NULL;
	mesh->count = part.len;
	mesh->part = malloc(part.len * sizeof(struct part));
	memcpy(mesh->part, part.data, part.len * sizeof(struct part));

	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ibo);

	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);

	glBufferData(GL_ARRAY_BUFFER, vertex.len * 4, vertex.data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(ATT_POSITION);
	glEnableVertexAttribArray(ATT_NORMAL);
	glEnableVertexAttribArray(ATT_TEXCOORD);
	glVertexAttribPointer(ATT_POSITION, 3, GL_FLOAT, 0, 32, (void*)0);
	glVertexAttribPointer(ATT_NORMAL, 3, GL_FLOAT, 0, 32, (void*)20);
	glVertexAttribPointer(ATT_TEXCOORD, 2, GL_FLOAT, 0, 32, (void*)12);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, element.len * 2, element.data, GL_STATIC_DRAW);

	model = malloc(sizeof *model);
	model->skel = NULL;
	model->mesh = mesh;
	model->anim = NULL;
	return model;
}