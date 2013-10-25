/***************************************************************************/
/*
 * author:      marcus
 * start date:  2013/01/14
 * finish date: 2013/01/14
 *
 */
/***************************************************************************/
#include <stdio.h>

#define MAX_SEQ 30
#define MAX_DIMEN 11 /* last element: store orig pos */
int g_seq[MAX_SEQ][MAX_DIMEN];
int g_units[MAX_SEQ];

/***************************************************************************/
void
dump_boxes(char seq_num, char dimen)
{
	int i = 0, j = 0;
	printf("*****************\n");
	for (i = 0; i < seq_num; ++i) {
		for (j = 0; j < MAX_DIMEN; ++j) {
			printf("%d ", g_seq[i][j]);
		}
		printf("\n");
	}
	printf("*****************\n");
}

FILE *g_fptr;
/***************************************************************************/
static void
sort_dimen(char seq_num, char dimen)
{
	int i = 0, j = 0, tmp = 0;
	for (i = 0; i < dimen; ++i) {
		if (scanf("%d", &g_seq[seq_num][i]) == EOF) return; 
/*		if (fscanf(g_fptr, "%d", &g_seq[seq_num][i]) == EOF) return;  */
		if (i == 0) continue;

		/* sort current sequence*/
		for (j = 0; j < i; ++j) {
			if (g_seq[seq_num][i] < g_seq[seq_num][j]) {
				tmp = g_seq[seq_num][j];
				g_seq[seq_num][j] = g_seq[seq_num][i];
				g_seq[seq_num][i] = tmp;
			}
		}
	}
	g_seq[seq_num][MAX_DIMEN - 1] = seq_num + 1;
}

/***************************************************************************/
static void
swap_seq(int seq1, int seq2)
{	
	int i = 0, tmp = 0;

	for (i = 0; i < MAX_DIMEN; ++i) {
		tmp = g_seq[seq2][i];
		g_seq[seq2][i] = g_seq[seq1][i];
		g_seq[seq1][i] = tmp;
	}

}

/***************************************************************************/
static void
sort_sequence(char seq_num, char dimen)
{
	int i = 0, j = 0, tmp = 0;

	/* 1. calculate total dimension units */
	for (i = 0; i < seq_num; ++i) {
		for (j = 0; j < dimen; ++j) {
			g_units[i] += g_seq[i][j];
		}
/*		printf("g_units[%d] = %d\n", i, g_units[i]); */
	}


	/* 2. sort sequences by total dimension units */
	for (i = 0; i < seq_num; ++i) {
		for (j = 0; j < i; ++j) {
			if (g_units[i] < g_units[j]) {
				tmp = g_units[i];
				g_units[i] = g_units[j];
				g_units[j] = tmp;
				swap_seq(i, j); 
			}
		}
	}
}

/***************************************************************************/
int 
main(void)
{
	int seq = 0, dimen = 0;
	g_fptr = fopen("StackingBoxes.in", "r");
	if (g_fptr == NULL) {
		printf("open input file failed!!\n");
		return 0;
	}

	while (scanf("%d %d", &seq, &dimen) != EOF) { 
/*	while (fscanf(g_fptr, "%d %d", &seq, &dimen) != EOF) { */
		int i = 0, j = 0, pos = 0, cnt = 0;
		char ret[MAX_SEQ] = {0};
		/* clear arrary */	
		for (i = 0; i < MAX_SEQ; ++i) {
			g_units[i] = 0;
			for (j = 0; j < MAX_DIMEN - 1; ++j) {
				g_seq[i][j] = 0;
			}
		}

		for (i = 0; i < seq; ++i) {
			sort_dimen(i, dimen);
		}
		
/*		dump_boxes(seq, dimen); */
		sort_sequence(seq, dimen);
/*		dump_boxes(seq, dimen); */

		ret[cnt++] = g_seq[0][MAX_DIMEN - 1];
		for (i = 0; i < seq; ++i) {
			j = 0;
			while (j < dimen && g_seq[i][j] > g_seq[pos][j]) ++j;
			if (j == dimen) {
				ret[cnt++] = g_seq[i][MAX_DIMEN - 1];
				pos = i;
			}
		}

		printf("%d\n", cnt);
		for (i = 0; i < cnt; ++i) {
			printf("%d ", ret[i]);
		}
		printf("\n");

	}
	return 0;
}

