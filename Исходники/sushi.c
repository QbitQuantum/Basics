/*
 * ゲーム関連
 * 寿司の位置を更新したり、ポイントを計算したりする
 */
struct sushi_game *sushi_init_game(char const *sushi, char const *fish[], int len, double fish_per_call)
{
	int i;
	char const *eraser = " ";
	struct sushi_game *sg;

	sg = (struct sushi_game *)malloc(sizeof(struct sushi_game));
	if(sg == NULL) {
		return NULL;
	}
//#define STRNCPY 	mbstowcs
#define STRNCPY 	strncpy

	STRNCPY(sg->sushi, sushi, 10);
	STRNCPY(sg->eraser, eraser, 10);
	sg->fish_attr_cnt = 0;
	while(*fish != NULL && sg->fish_attr_cnt < 50) {
		STRNCPY(sg->fish[sg->fish_attr_cnt++], *fish++, 10);
	}
#undef STRNCPY
	sg->width = SUSHI_XWINDOW;			// 寿司1つで半角2文字分を消費するので、x座標は2文字ごとに1進める
	sg->height = SUSHI_YWINDOW;

	// 寿司の位置の初期化 (最初は(0, 0)に縮重している)
	sg->sushi_len = len;				// 最初の寿司の長さは1
	sg->dir = SUSHI_RIGHT;
	sg->sushi_max = 50 * (sg->width + sg->height);
	sg->sushi_pos = (struct sushi_pos *)malloc((sg->sushi_max + 1) * sizeof(struct sushi_pos));
	if(sg->sushi_pos == NULL) {
		free(sg);
		return NULL;
	}
	sg->sushi_pos[0].x = sg->sushi_pos[0].y = sg->sushi_pos[0].attr = 0;
	for(i = 1; i < sg->sushi_max; i++) {
		sg->sushi_pos[i].x = sg->sushi_pos[i].y = -1;
		sg->sushi_pos[i].attr = 0;
	}

	// 魚の位置の初期化 (最初は魚はいない)
	sg->fish_per_call = fish_per_call;
	sg->fish_cnt = 0;
	sg->fish_max = (sg->width * sg->height) / 100;
	sg->fish_pos = (struct sushi_pos *)malloc((sg->fish_max + 1) * sizeof(struct sushi_pos));
	if(sg->fish == NULL) {
		free(sg->sushi_pos);
		free(sg);
		return NULL;
	}
	memset(sg->fish_pos, 0, (sg->fish_max + 1) * sizeof(struct sushi_pos));

	return(sg);
}