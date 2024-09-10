        void buildFaceIndices()
        {
#ifdef VERBOSE
            std::cout << "Building unique face indices... " << std::flush;
	    Opm::time::StopWatch clock;
            clock.start();
#endif
            typedef CellIterator CI;
            typedef typename CI::FaceIterator FI;

            // We build the actual cell to face mapping in two passes.
            // [code mostly lifted from IncompFlowSolverHybrid::enumerateGridDof(),
            //  but with a twist: This code builds a mapping from cells in index
            //  order to unique face numbers, while the mapping built in the
            //  enumerateGridDof() method was ordered by cell iterator order]

            // Allocate and reserve structures.
            const int nc = numberOfCells();
            std::vector<int> cell(nc, -1);
            std::vector<int> num_faces(nc); // In index order.
            std::vector<int> fpos;     fpos  .reserve(nc + 1);
            std::vector<int> num_cf;   num_cf.reserve(nc); // In iterator order.
            std::vector<int> faces ;

            // First pass: enumerate internal faces.
            int cellno = 0; fpos.push_back(0);
            int tot_ncf = 0, tot_ncf2 = 0, max_ncf = 0;
            for (CI c = cellbegin(); c != cellend(); ++c, ++cellno) {
                const int c0 = c->index();
                ASSERT((0 <= c0) && (c0 < nc) && (cell[c0] == -1));
                cell[c0] = cellno;
                num_cf.push_back(0);
                int& ncf = num_cf.back();
                for (FI f = c->facebegin(); f != c-> faceend(); ++f) {
                    if (!f->boundary()) {
                        const int c1 = f->neighbourCellIndex();
                        ASSERT((0 <= c1) && (c1 < nc) && (c1 != c0));

                        if (cell[c1] == -1) {
                            // Previously undiscovered internal face.
                            faces.push_back(c1);
                        }
                    }
                    ++ncf;
                }
                num_faces[c0] = ncf;
                fpos.push_back(int(faces.size()));
                max_ncf  = std::max(max_ncf, ncf);
                tot_ncf  += ncf;
                tot_ncf2 += ncf * ncf;
            }
            ASSERT(cellno == nc);

            // Build cumulative face sizes enabling direct insertion of
            // face indices into cfdata later.
            std::vector<int> cumul_num_faces(numberOfCells() + 1);
            cumul_num_faces[0] = 0;
            std::partial_sum(num_faces.begin(), num_faces.end(), cumul_num_faces.begin() + 1);

            // Avoid (most) allocation(s) inside 'c' loop.
            std::vector<int>    l2g;
            l2g.reserve(max_ncf);
            std::vector<double> cfdata(tot_ncf);
            int total_num_faces = int(faces.size());

            // Second pass: build cell-to-face mapping, including boundary.
            typedef std::vector<int>::iterator VII;
            for (CI c = cellbegin(); c != cellend(); ++c) {
                const int c0 = c->index();
                ASSERT ((0 <=      c0 ) && (     c0  < nc) &&
                        (0 <= cell[c0]) && (cell[c0] < nc));
                const int ncf = num_cf[cell[c0]];
                l2g.resize(ncf, 0);
                for (FI f = c->facebegin(); f != c->faceend(); ++f) {
                    if (f->boundary()) {
                        // External, not counted before.  Add new face...
                        l2g[f->localIndex()] = total_num_faces++;
                    } else {
                        // Internal face.  Need to determine during
                        // traversal of which cell we discovered this
                        // face first, and extract the face number
                        // from the 'faces' table range of that cell.

                        // Note: std::find() below is potentially
                        // *VERY* expensive (e.g., large number of
                        // seeks in moderately sized data in case of
                        // faulted cells).
                        const int c1 = f->neighbourCellIndex();
                        ASSERT ((0 <=      c1 ) && (     c1  < nc) &&
                                (0 <= cell[c1]) && (cell[c1] < nc));

                        int t = c0, seek = c1;
                        if (cell[seek] < cell[t])
                            std::swap(t, seek);
                        int s = fpos[cell[t]], e = fpos[cell[t] + 1];
                        VII p = std::find(faces.begin() + s, faces.begin() + e, seek);
                        ASSERT(p != faces.begin() + e);
                        l2g[f->localIndex()] = p - faces.begin();
                    }
                }
                ASSERT(int(l2g.size()) == num_faces[c0]);
                std::copy(l2g.begin(), l2g.end(), cfdata.begin() + cumul_num_faces[c0]);
            }
            num_faces_ = total_num_faces;
            max_faces_per_cell_ = max_ncf;
            face_indices_.assign(cfdata.begin(), cfdata.end(),
                                 num_faces.begin(), num_faces.end());

#ifdef VERBOSE
            clock.stop();
            double elapsed = clock.secsSinceStart();
            std::cout << "done.     Time elapsed: " << elapsed << std::endl;
#endif
        }