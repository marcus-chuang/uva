/***************************************************************************/
/*
 * author:      marcus
 * start date:  2013/01/11
 * finish date: 2013/01/14
 *
 */
/***************************************************************************/
#include <stdio.h>
enum {B = 0, G = 1, C = 2};

/***************************************************************************/
int
main(void)
{
	int bins[3][3] = {0};
	char color[][3] = {{B, C, G}, {B, G, C}, {C, B, G}, {C, G, B}, {G, B, C}, {G, C, B}};
	char s[][4] = {"BCG", "BGC", "CBG", "CGB", "GBC", "GCB"};

	while (scanf("%d %d %d", *bins, *bins + 1, *bins + 2) != EOF &&
			scanf("%d %d %d", *(bins + 1), *(bins + 1) + 1, *(bins + 1) + 2) != EOF &&
			scanf("%d %d %d", *(bins + 2), *(bins + 2) + 1, *(bins + 2) + 2) != EOF) {
		
		int i = 0, unmoved = 0, moves = 0, tol = 0;
		int max = 0, cand;
		for (i = 0; i < 3; ++i) {
			tol += bins[i][B] + bins[i][G] + bins[i][C];
		}

		for (i = 0; i < 6; ++i) {
			unmoved = bins[0][color[i][0]] + bins[1][color[i][1]] + bins[2][color[i][2]];
			if (unmoved > max) {
				max = unmoved;
				cand = i;
			}
		}

		moves = tol - max;
		printf("%s %d\n", s[cand], moves);
	}
	return 0;
}
