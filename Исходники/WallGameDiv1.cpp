    int play(vector <string> costs) 
    {	
        cost = costs;
        N = size(cost);
        M = size(cost[0]);
        for(int i=0;i<size(cost);i++) {
            for(int j=0;j<size(cost[i]);j++) cost[i][j] -= '0';
        }
        cur.resize(M);
        for(int i=0;i<M;i++) {
            cur[i] = cost.back()[i];
        }

        for(int i=N-2;i>=0;i--) {
            calc(cost[i]);
            cur.swap(nex);
            for(int i=0;i<M;i++) {
                cout << cur[i] << " ";
            }
            cout << endl;
        }

        int ret = cur[0];
        for(int i=1;i<M;i++) {
            ret = min(ret, cur[i]);
        }
        return ret;
    }