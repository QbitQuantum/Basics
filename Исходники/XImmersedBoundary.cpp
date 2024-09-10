TCylinderElasticBoundary* TCylinderElasticBoundary::Initialize()
{
    //LOG(INFO) << "Start boundary creation";
	/*
	this->nodes = new TNode*[this->nodesCount];

    for(int n = 0; n < 120; ++n) {
        for (int i = 0; i < 120; i++) {
            this->nodes[i+n*120] = new TFixedElasticNode();
        }
    }

    for(int n = 0; n < 120; ++n) {
        for (int i = 0; i < 120; i++) {
            long double x = float(n) / float(120);
            long double y = this->yCenter - this->radius * cos(-M_PI * 2 * (double)(119-i)/119);
            long double z = this->zCenter + this->radius * sin(-M_PI * 2 * (double)(119-i)/119);

            this->nodes[i+n*120]->x = x;
            this->nodes[i+n*120]->xRef = x;
            this->nodes[i+n*120]->xVel = 0;
            this->nodes[i+n*120]->xForce = 0;

            this->nodes[i+n*120]->y = y;
            this->nodes[i+n*120]->yRef = y;
            this->nodes[i+n*120]->yVel = 0;
            this->nodes[i+n*120]->yForce = 0;

            this->nodes[i+n*120]->z = z;
            this->nodes[i+n*120]->zRef = z;
            this->nodes[i+n*120]->zVel = 0;
            this->nodes[i+n*120]->zForce = 0;
        }
    }

    for(int n = 0; n < 120; ++n) {
        for (int i = 0; i < 120; i++) {
            this->nodes[i+n*120]->boundary = this;

            if (n < 119)
            {
                this->nodes[i+n*120]->neighbors.next = this->nodes[i+(n+1)*120];
                this->nodes[i+n*120]->neighbors.initialDistanceNext = TNode::distance_3d(this->nodes[i+n*120], this->nodes[i+n*120]->neighbors.next);
            }
            if (n > 0)
            {
                this->nodes[i+n*120]->neighbors.prev = this->nodes[i+(n-1)*120];
                this->nodes[i+n*120]->neighbors.initialDistancePrev = TNode::distance_3d(this->nodes[i+n*120], this->nodes[i+n*120]->neighbors.prev);
            }

            if (this->nodes[i+n*120]->neighbors.prev != nullptr && this->nodes[i+n*120]->neighbors.next != nullptr )
            {
                this->nodes[i+n*120]->neighbors.initialCurvatures[OX] = TNode::curvature(
                    this->nodes[i+n*120],
                    this->nodes[i+n*120]->neighbors.next,
                    this->nodes[i+n*120]->neighbors.prev,
                    TNode::Ox
                );
                this->nodes[i+n*120]->neighbors.initialCurvatures[OY] = TNode::curvature(
                    this->nodes[i+n*120],
                    this->nodes[i+n*120]->neighbors.next,
                    this->nodes[i+n*120]->neighbors.prev,
                    TNode::Oy
                );
                this->nodes[i+n*120]->neighbors.initialCurvatures[OZ] = TNode::curvature(
                    this->nodes[i+n*120],
                    this->nodes[i+n*120]->neighbors.next,
                    this->nodes[i+n*120]->neighbors.prev,
                    TNode::Oz
                );
            }
        }
    }
	*/

	this->step = 0.01; // 0.069;
	long double iPart = 0.;
	//this->height = 1.0;

	modfl(this->height / this->step, &iPart);
	int endIndex = (int)iPart;
	this->height_nodes = endIndex + 1;

	modfl(this->radius*2.*M_PI / this->step, &iPart);
	endIndex = (int)iPart;
	this->radius_nodes = endIndex;
	this->nodesCount = this->height_nodes*this->radius_nodes;
	this->nodes = new TNode*[this->nodesCount];

	for (int n = 0; n < this->height_nodes; ++n) {
		for (int i = 0; i < this->radius_nodes; i++) {
			this->nodes[i + n*this->radius_nodes] = new TFixedElasticNode();
			//this->nodes[i + n * 120]->;
		}
	}


	double rc, stiffness_plus = this->stiffness / 50;
	double iRadius = (double) this->radius_nodes;
	double iHeight = (double) this->height_nodes - 1.;
	int cx = this->height_nodes/2., cy = 3.*this->radius_nodes/4., Rpip = this->radius_nodes/10., ix, iy;

	for (int n = 0; n < this->height_nodes; ++n) {
		for (int i = 0; i < this->radius_nodes; i++) {
			long double x = this->height*float(n) / iHeight;
			long double y = this->yCenter + this->radius * cos(-M_PI * 2 * (iRadius-i) / iRadius);
			long double z = this->zCenter + this->radius * sin(-M_PI * 2 * (iRadius-i) / iRadius);

			this->nodes[i + n*this->radius_nodes]->x = x;
			this->nodes[i + n*this->radius_nodes]->xRef = x;
			this->nodes[i + n*this->radius_nodes]->xVel = 0;
			this->nodes[i + n*this->radius_nodes]->xForce = 0;

			this->nodes[i + n*this->radius_nodes]->y = y;
			this->nodes[i + n*this->radius_nodes]->yRef = y;
			this->nodes[i + n*this->radius_nodes]->yVel = 0;
			this->nodes[i + n*this->radius_nodes]->yForce = 0;

			this->nodes[i + n*this->radius_nodes]->z = z;
			this->nodes[i + n*this->radius_nodes]->zRef = z;
			this->nodes[i + n*this->radius_nodes]->zVel = 0;
			this->nodes[i + n*this->radius_nodes]->zForce = 0;

			/*
			ix = abs(n-cx);
			iy = abs(i-cy);
			rc = sqrt((double)(ix*ix + iy*iy));
			if (rc <= Rpip)
				//this->nodes[i + n * 120]->stretchingStiffness = this->stiffness*rc*rc + sin(rc/Rpip)*stiffness_plus;
				this->nodes[i + n * this->radius_nodes]->stretchingStiffness = stiffness_plus; //+(this->stiffness - stiffness_plus)*sqrt(rc);    //sin(rc*0.5*M_PI / Rpip);
			else
			this->nodes[i + n *this->radius_nodes]->stretchingStiffness = this->stiffness;
			*/
			// Verison 1 (not good)
			/*
			if ((n>=49 && n<=69) && (i>=20 && i<=39))
			this->nodes[i + n * 120]->stretchingStiffness = this->stiffness/100;
			else
			this->nodes[i + n * 120]->stretchingStiffness=this->stiffness;
			*/
		}
		this->zCenter += 0.005;
	}
	this->zCenter -= 0.005;
	printf("\nzCenter=%lf\n", this->zCenter);

	for (int n = 0; n < this->height_nodes; ++n) {
		for (int i = 0; i < this->radius_nodes; i++) {
			this->nodes[i + n*this->radius_nodes]->boundary = this;

			if (n <  this->height_nodes - 1)
			{
				this->nodes[i + n*this->radius_nodes]->neighbors.next = this->nodes[i + (n + 1) * this->radius_nodes];
				this->nodes[i + n*this->radius_nodes]->neighbors.initialDistanceNext =
					TNode::distance_3d(this->nodes[i + n * this->radius_nodes], this->nodes[i + n * this->radius_nodes]->neighbors.next);
			}
			if (n > 0)
			{
				this->nodes[i + n*this->radius_nodes]->neighbors.prev = this->nodes[i + (n - 1) * this->radius_nodes];
				this->nodes[i + n*this->radius_nodes]->neighbors.initialDistancePrev = TNode::distance_3d(this->nodes[i + n * this->radius_nodes], this->nodes[i + n * this->radius_nodes]->neighbors.prev);
			}

			if (this->nodes[i + n*this->radius_nodes]->neighbors.prev != nullptr && this->nodes[i + n * this->radius_nodes]->neighbors.next != nullptr)
			{
				this->nodes[i + n*this->radius_nodes]->neighbors.initialCurvatures[OX] = TNode::curvature(
					this->nodes[i + n*this->radius_nodes],
					this->nodes[i + n*this->radius_nodes]->neighbors.next,
					this->nodes[i + n*this->radius_nodes]->neighbors.prev,
					TNode::Ox
					);
				this->nodes[i + n*this->radius_nodes]->neighbors.initialCurvatures[OY] = TNode::curvature(
					this->nodes[i + n*this->radius_nodes],
					this->nodes[i + n*this->radius_nodes]->neighbors.next,
					this->nodes[i + n*this->radius_nodes]->neighbors.prev,
					TNode::Oy
					);
				this->nodes[i + n*this->radius_nodes]->neighbors.initialCurvatures[OZ] = TNode::curvature(
					this->nodes[i + n*this->radius_nodes],
					this->nodes[i + n*this->radius_nodes]->neighbors.next,
					this->nodes[i + n*this->radius_nodes]->neighbors.prev,
					TNode::Oz
					);
			}
		}
	}

	//TNode **CutNodes;
	//int **CutGrid;
	/*
	ncut = this->radius_nodes*this->radius_nodes/8.0 + this->radius_nodes/2.0+1;
	double x_level,z_level;
	int ix_stp_before = 0, ix_stp_after = this->height_nodes-1;
	int iy_start = ix_stp_before*this->radius_nodes;
	int scount = 0, nd_count, mcount=0;
	cut_nodes = new TNode* [2];
	for (int i = 0; i < 2; i++)
		cut_nodes[i] = new TNode[ncut];

	for (int i = 0; i <= 4; i++)
	{
		printf(" ->%lf, %lf", this->nodes[ix_stp_before*this->radius_nodes + i]->y, this->nodes[ix_stp_before*this->radius_nodes + i]->z);
	}
	printf("\n");

	for (int ix = 0; ix < 2; ix++)
	{
		x_level = ix == 0 ? this->nodes[ix_stp_before*this->radius_nodes]->x : this->nodes[ix_stp_after*this->radius_nodes]->x;
		for (int lv = 0; lv <= this->radius_nodes / 4; lv++)
		{

			z_level = this->nodes[ix_stp_before*this->radius_nodes + lv]->z;
			for (int i = 0 + lv; i <= this->radius_nodes / 2 - lv; i++)
			{
				cut_nodes[ix][scount].x = x_level;
				cut_nodes[ix][scount].y = this->nodes[ix_stp_before*this->radius_nodes + i]->y;
				cut_nodes[ix][scount].z = z_level;
				printf(" !!!->num=%d %lf, %lf, %lf", scount,cut_nodes[ix][scount].x, cut_nodes[ix][scount].y, cut_nodes[ix][scount].z);
				++scount;
			}
		}

		for (int lv = 1; lv <= this->radius_nodes / 4; lv++)
		{

			z_level = this->nodes[ix_stp_before*this->radius_nodes + this->radius_nodes - lv]->z;
			for (int i = 0 + lv; i <= this->radius_nodes / 2 - lv; i++)
			{
				cut_nodes[ix][scount].x = x_level;
				cut_nodes[ix][scount].y = this->nodes[ix_stp_before*this->radius_nodes + this->radius_nodes - i]->y;
				cut_nodes[ix][scount].z = z_level;
				printf(" ***->num = %d %lf, %lf, %lf", scount,cut_nodes[ix][scount].x, cut_nodes[ix][scount].y, cut_nodes[ix][scount].z);
				++scount;
			}
		}

	}

	//necut = ncut - 1;
	
	int ne = 0;
	//int begin_point = 0;
	int no_node = -1;
	int nmdl = this->radius_nodes / 2 + 1;
	int nlv,el;
	int ne_tmp;
	for (el = nmdl - 1, nlv = 0, ne_tmp = 0; el>1; el -= 2)
	{
		ne_tmp += el;
		nlv++;
	}
		
	necut = ne_tmp*2;
    cut_grid = new int*[necut];
	for (int i = 0; i < necut; i++)
		cut_grid[i] = new int[4];

	// выше середины
	int lv,point,nline;
	for (lv = 0, nline=nmdl, point=0; lv < nlv; lv++,nline-=2)
	{
		for (int i = 0; i < nline-1; i++)
		{
			if (i == 0)
			{
				cut_grid[ne][0] = point++;
				cut_grid[ne][1] = point;
				cut_grid[ne][2] = point+nline-1;
				cut_grid[ne][3] = -1;
				ne++;
			}
			else if (i == nline-2)
			{
				cut_grid[ne][0] = point++;
				cut_grid[ne][1] = point;
				cut_grid[ne][2] = point++ + (nline - 2);
				cut_grid[ne][3] = -1;
				//point += (nline - 2)+1;
				ne++;
			}
			else 
			{
				cut_grid[ne][0] = point++;
				cut_grid[ne][1] = point;
				cut_grid[ne][2] = point + (nline - 2) + 1;
				cut_grid[ne][3] = point + (nline - 2);
				ne++;
			}
			printf("\nel=%d : %d, %d, %d, %d", ne-1,cut_grid[ne-1][0], cut_grid[ne-1][1], cut_grid[ne-1][2], cut_grid[ne-1][3]);
		}
	}
	point += (nline - 2) + 2;

	// первая строка ниже
	//int in_mdline_point = this->radius_nodes / 2;
	//int begin_point = this->radius_nodes*this->radius_nodes /4 + this->radius_nodes/2;
	for (int i = 0, nline = nmdl; i < nline - 1; i++)
	{
		if (i == 0)
		{
			cut_grid[ne][0] = i;
			cut_grid[ne][1] = point;
			cut_grid[ne][2] = i+1;
			cut_grid[ne][3] = -1;
			ne++;
		}
		else if (i == nline - 2)
		{
			cut_grid[ne][0] = nline - 2;
			cut_grid[ne][1] = point;
			cut_grid[ne][2] = nline -1;
			cut_grid[ne][3] = -1;
			ne++;
		}
		else
		{
			cut_grid[ne][0] = i;
			cut_grid[ne][1] = point++;
			cut_grid[ne][2] = point;
			cut_grid[ne][3] = i +1;
			ne++;
		}

		printf("\nel=%d : %d, %d, %d, %d", ne - 1, cut_grid[ne - 1][0], cut_grid[ne - 1][1], cut_grid[ne - 1][2], cut_grid[ne - 1][3]);
	}
	point = point - (nmdl - 2) + 1;

	// последние строки
	for ( lv = 1, nline = nmdl-2; lv < nlv; lv++, nline -= 2)
	{
		for (int i = 0; i < nline - 1; i++)
		{
			if (i == 0)
			{
				cut_grid[ne][0] = point++;
				cut_grid[ne][1] = point + nline - 1;
				cut_grid[ne][2] = point;
				cut_grid[ne][3] = -1;
				ne++;
			}
			else if (i == nline - 2)
			{
				cut_grid[ne][0] = point++;
				cut_grid[ne][1] = point+ (nline - 2);
				cut_grid[ne][2] = point;
				cut_grid[ne][3] = -1;
				ne++;
			}
			else
			{
				cut_grid[ne][0] = point++;
				cut_grid[ne][1] = point + (nline - 2);
				cut_grid[ne][2] = point + (nline - 2) + 1;
				cut_grid[ne][3] = point;
				ne++;
			}
			printf("\nel=%d : %d, %d, %d, %d", ne - 1, cut_grid[ne - 1][0], cut_grid[ne - 1][1], cut_grid[ne - 1][2], cut_grid[ne - 1][3]);
		}
	}

	printf("\nall right!");
	*/
	/*
	double sum[] = { 0.0, 0.0 };
	int i1, i2, i3, i4;
	double xc, yc, zc;
	for (int ix = 0; ix < 2; ix++)
	for (int i = 0; i < necut; i++)
	{
		i1 = cut_grid[i][0];
		i2 = cut_grid[i][1];
		i3 = cut_grid[i][2];
		i4 = cut_grid[i][3];

		// calculate center of element
		if (i4 != -1) //square
		{
			xc = (cut_nodes[ix][i1].x + cut_nodes[ix][i2].x + cut_nodes[ix][i3].x + cut_nodes[ix][i4].x)*.25;
			yc = (cut_nodes[ix][i1].y + cut_nodes[ix][i2].y + cut_nodes[ix][i3].y + cut_nodes[ix][i4].y)*.25;
			zc = (cut_nodes[ix][i1].z + cut_nodes[ix][i2].z + cut_nodes[ix][i3].z + cut_nodes[ix][i4].z)*.25;
		}
		else //triangle
		{
			xc = (cut_nodes[ix][i1].x + cut_nodes[ix][i2].x + cut_nodes[ix][i3].x) / 3.;
			yc = (cut_nodes[ix][i1].y + cut_nodes[ix][i2].y + cut_nodes[ix][i3].y) / 3.;
			zc = (cut_nodes[ix][i1].z + cut_nodes[ix][i2].z + cut_nodes[ix][i3].z) / 3.;
		}

		// calculate S of element

		// calculate u in point (xc,yc,zc)

		//sum plus

	}
	*/
    //cnpy::NpyArray x_valves = cnpy::npy_load("aortic_valve_x.npy");
    //cnpy::NpyArray y_valves = cnpy::npy_load("aortic_valve_y.npy");
    //cnpy::NpyArray z_valves = cnpy::npy_load("aortic_valve_z.npy");

    //cnpy::NpyArray prev_indices = cnpy::npy_load("prev_indices.npy");
    //cnpy::NpyArray next_indices = cnpy::npy_load("next_indices.npy");
    //cnpy::NpyArray fixed_indices = cnpy::npy_load("fixed_indices.npy");
    //cnpy::NpyArray closed_indices = cnpy::npy_load("closed_indices.npy");

    //cnpy::NpyArray x_valves = cnpy::npy_load("cloned_valve_x.npy");
    //cnpy::NpyArray y_valves = cnpy::npy_load("cloned_valve_y.npy");
    //cnpy::NpyArray z_valves = cnpy::npy_load("cloned_valve_z.npy");

//    cnpy::NpyArray x_valves = cnpy::npy_load("cloned_closed_valves_x.npy");
//    cnpy::NpyArray y_valves = cnpy::npy_load("cloned_closed_valves_y.npy");
//    cnpy::NpyArray z_valves = cnpy::npy_load("cloned_closed_valves_z.npy");
//
//    //cnpy::NpyArray initial_force_x = cnpy::npy_load("cloned_closed_initial_force_x.npy");
//    //cnpy::NpyArray initial_force_y = cnpy::npy_load("cloned_closed_initial_force_y.npy");
//    //cnpy::NpyArray initial_force_z = cnpy::npy_load("cloned_closed_initial_force_z.npy");
//
//    cnpy::NpyArray prev_indices = cnpy::npy_load("cloned_closed_prev_indices.npy");
//    cnpy::NpyArray next_indices = cnpy::npy_load("cloned_closed_next_indices.npy");
//    cnpy::NpyArray fixed_indices = cnpy::npy_load("cloned_closed_fixed_indices.npy");
//    //cnpy::NpyArray closed_indices = cnpy::npy_load("cloned_closed_indices.np_steppedy");
//
//    float *x_loaded_data = reinterpret_cast<float *>(x_valves.data);
//    float *y_loaded_data = reinterpret_cast<float *>(y_valves.data);
//    float *z_loaded_data = reinterpret_cast<float *>(z_valves.data);
//
//    //float *initial_force_x_data = reinterpret_cast<float *>(initial_force_x.data);
//    //float *initial_force_y_data = reinterpret_cast<float *>(initial_force_y.data);
//    //float *initial_force_z_data = reinterpret_cast<float *>(initial_force_z.data);
//
//    long int *prev_indices_data = reinterpret_cast<long int *>(prev_indices.data);
//    long int *next_indices_data = reinterpret_cast<long int *>(next_indices.data);
//    long int *fixed_indices_data = reinterpret_cast<long int *>(fixed_indices.data);
//    //long int *closed_indices_data = reinterpret_cast<long int *>(closed_indices.data);
//
//    int fixed_iter = 0;
//    for(int i=0; i<x_valves.shape[0]; i++)
//    {
//        if (fixed_indices_data[fixed_iter] == i) 
//        {
//            this->nodes[this->nodesCount - 3282 + i] = new TFixedElasticNode();
//            fixed_iter++;
//            continue;
//        }
//
//        this->nodes[this->nodesCount - 3282 + i] = new TElasticNode();
//        //if (IN(closed_indices_data, closed_indices_data + x_valves.shape[0], i))
//        //{
//        //    LOG(INFO) << "Found a TFixedStretchingNode at " << this->nodesCount - 3282 + i;
//        //    this->nodes[this->nodesCount - 3282 + i] = new TFixedStretchingNode();
//        //}
//        //else
//        //{
//        //    this->nodes[this->nodesCount - 3282 + i] = new TElasticNode();
//        //}
//    }
//
//    for(int i=0; i<x_valves.shape[0]; i++)
//    {
//        long double x = x_loaded_data[i];
//        this->nodes[this->nodesCount - 3282 + i]->x = x - 0.2;
//        this->nodes[this->nodesCount - 3282 + i]->xRef = x - 0.2;
//        this->nodes[this->nodesCount - 3282 + i]->xVel = 0;
//        this->nodes[this->nodesCount - 3282 + i]->xForce = 0;//initial_force_x_data[i];
//
//        long double y = y_loaded_data[i];
//        this->nodes[this->nodesCount - 3282 + i]->y = y;
//        this->nodes[this->nodesCount - 3282 + i]->yRef = y;
//        this->nodes[this->nodesCount - 3282 + i]->yVel = 0;
//        this->nodes[this->nodesCount - 3282 + i]->yForce = 0;//initial_force_y_data[i];
//
//        long double z = z_loaded_data[i];
//        this->nodes[this->nodesCount - 3282 + i]->z = z;
//        this->nodes[this->nodesCount - 3282 + i]->zRef = z;
//        this->nodes[this->nodesCount - 3282 + i]->zVel = 0;
//        this->nodes[this->nodesCount - 3282 + i]->zForce = 0;//initial_force_z_data[i];
//    }
//
//    for(int i=0; i<x_valves.shape[0]; i++)
//    {
//        this->nodes[this->nodesCount - 3282 + i]->boundary = this;
//        this->nodes[this->nodesCount - 3282 + i]->neighbors.next = this->nodes[this->nodesCount - 3282 + next_indices_data[i]];
//        this->nodes[this->nodesCount - 3282 + i]->neighbors.prev = this->nodes[this->nodesCount - 3282 + prev_indices_data[i]];
//        this->nodes[this->nodesCount - 3282 + i]->neighbors.initialDistanceNext = TNode::distance_3d(
//            this->nodes[this->nodesCount - 3282 + i],
//            this->nodes[this->nodesCount - 3282 + i]->neighbors.next
//        );
//
//        this->nodes[this->nodesCount - 3282 + i]->neighbors.initialCurvatures[OX] = TNode::curvature(
//            this->nodes[this->nodesCount - 3282 + i],
//            this->nodes[this->nodesCount - 3282 + i]->neighbors.next,
//            this->nodes[this->nodesCount - 3282 + i]->neighbors.prev,
//            TNode::Ox
//        );
//        this->nodes[this->nodesCount - 3282 + i]->neighbors.initialCurvatures[OY] = TNode::curvature(
//            this->nodes[this->nodesCount - 3282 + i],
//            this->nodes[this->nodesCount - 3282 + i]->neighbors.next,
//            this->nodes[this->nodesCount - 3282 + i]->neighbors.prev,
//            TNode::Oy
//        );
//        this->nodes[this->nodesCount - 3282 + i]->neighbors.initialCurvatures[OZ] = TNode::curvature(
//            this->nodes[this->nodesCount - 3282 + i],
//            this->nodes[this->nodesCount - 3282 + i]->neighbors.next,
//            this->nodes[this->nodesCount - 3282 + i]->neighbors.prev,
//            TNode::Oz
//        );
//
//        if (this->nodes[this->nodesCount - 3282 + i]->neighbors.initialDistanceNext == 0)
//        {
//            this->nodes[this->nodesCount - 3282 + i]->neighbors.next = nullptr;
//        }
//    }

    return this;
}