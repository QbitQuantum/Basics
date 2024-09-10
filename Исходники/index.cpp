/*
Initialize index tables and pointers
*/
void init_indices() {
    int temp[2048];
    int index;
    int i,j;
    int u1,u2;
    int rot,val;

    for( i = 0; i < 4096; i++) {
        KK_index[i] = ILLEGAL;
        KK_WP_index[i] = ILLEGAL;
    }

    /*without pawn*/
    for( i = 0; i < 2048; i++) {
        temp[i] = ILLEGAL;
    }

    index = 0;
    for(i = 0;i < 64;i++) {
        for(j = 0;j < 64;j++) {
            if(distance(SQ6488(i),SQ6488(j)) <= 1)
                continue;
            /*rotations*/
            u1 = i;
            u2 = j;
            rot = 0;

            if(file64(u1) > FILED) {
                u1 = MIRRORF64(u1);
                u2 = MIRRORF64(u2);
                rot ^= rotF;
            }
            if(rank64(u1) > RANK4) {
                u1 = MIRRORR64(u1);
                u2 = MIRRORR64(u2);
                rot ^= rotR;
            }
            if(rank64(u1) > file64(u1)) {
                u1 = MIRRORD64(u1);
                u2 = MIRRORD64(u2);
                rot ^= rotD;
            }
            if(file64(u1) == rank64(u1)) {
                if(rank64(u2) > file64(u2)) {
                    u1 = MIRRORD64(u1);
                    u2 = MIRRORD64(u2);
                    rot ^= rotD;
                }
            }

            val = (u1 << 6) | u2;

            /*actual index*/
            if(file64(u1) == rank64(u1)) {
                u1 = K_TR[u1];
                u2 = K1_TR[u2];
            } else {
                u1 = K_TR[u1];
                u2 = u2;
            }

            if(temp[u1 * 64 + u2] == ILLEGAL) {
                temp[u1 * 64 + u2] = index;
                KK_index[i * 64 + j] = index;
                KK_rotation[i * 64 + j] = rot;
                KK_square[index] = val;
                index++;
            } else {
                KK_index[i * 64 + j] = temp[u1 * 64 + u2];
                KK_rotation[i * 64 + j] = rot;
            }
        }
    }
    /*with pawn*/
    for( i = 0; i < 2048; i++) {
        temp[i] = ILLEGAL;
    }

    index = 0;
    for( i = 0;i < 64;i++) {
        for( j = 0; j < 64;j++) {
            if(distance(SQ6488(i),SQ6488(j)) <= 1)
                continue;

            /*reflection*/
            u1 = i;
            u2 = j;
            rot = 0;
            if(file64(u1) > FILED) {
                u1 = MIRRORF64(u1);
                u2 = MIRRORF64(u2);
                rot ^= rotF;
            }

            val = (u1 << 6) | u2;
            /*actual index*/
            u1 = K2_TR[u1];
            u2 = u2;

            if(temp[u1 * 64 + u2] == ILLEGAL) {
                temp[u1 * 64 + u2] = index;
                KK_WP_index[i * 64 + j] = index;
                KK_WP_rotation[i * 64 + j] = rot;
                KK_WP_square[index] = val;
                index++;
            } else {
                KK_WP_index[i * 64 + j] = temp[u1 * 64 + u2];
                KK_WP_rotation[i * 64 + j] = rot;
            }
            /*end*/
        }
    }
}