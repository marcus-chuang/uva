/***************************************************************************/
/*
 * author:      marcus
 * start date:  2013/01/14
 * finish date: 2013/01/14
 *
 */
/***************************************************************************/
#include <stdio.h>

#define MAX_BOX 30
#define MAX_DIMEN 12 /* the second last: sum of dimen, the last: box number */
int g_seq[MAX_BOX][MAX_DIMEN];
int g_units[MAX_BOX];

/***************************************************************************/
void
dump_boxes(int boxlist[MAX_BOX][MAX_DIMEN], char seq_num, char dimen)
{
	int i = 0, j = 0;
	printf("*****************\n");
	for (i = 0; i < seq_num; ++i) {
		for (j = 0; j < MAX_DIMEN; ++j) {
			printf("%d ", boxlist[i][j]);
		}
		printf("\n");
	}

	printf("*****************\n");
}

FILE *g_fptr;
/***************************************************************************/
static int
sort_dimen(char seq_num, char dimen)
{
	int i = 0, j = 0, tmp = 0;
	for (i = 0; i < dimen; ++i) {
		if (scanf("%d", &g_seq[seq_num][i]) == EOF) return 0;  
/*		if (fscanf(g_fptr, "%d", &g_seq[seq_num][i]) == EOF) return; */
	}

	/* bubble sort */
	for (i = 0; i < dimen; ++i) {
		for (j = 0; j < dimen - i - 1; ++j) {
			if (g_seq[seq_num][j] > g_seq[seq_num][j + 1]) {
				tmp = g_seq[seq_num][j + 1];
				g_seq[seq_num][j + 1] = g_seq[seq_num][j];
				g_seq[seq_num][j] = tmp;
			}
		}
	}
	g_seq[seq_num][MAX_DIMEN - 1] = seq_num + 1;
	return 1;
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
		g_seq[i][MAX_DIMEN - 2] = g_units[i];
	}

	/* 2. bubble sort: sort sequences by total dimension units */
	for (i = 0; i < seq_num; ++i) {
		for (j = 0; j < seq_num - i - 1 ; ++j) {
			if (g_units[j] > g_units[j + 1]) {
				tmp = g_units[j];
				g_units[j] = g_units[j + 1];
				g_units[j + 1] = tmp;
				swap_seq(j, j + 1);
			}
		}
	}
}

/***************************************************************************/
static void
find_nest(char seq, char dimen)
{
	int ans[MAX_BOX] = {0}, tmp[MAX_BOX] = {0};
	int boxes = 0, start = 0, k = 0;

	for (start = 0; start < seq; ++start) {
		int i = 0, pos = 0, n = 0;
		pos = start;
		i = pos + 1;
		tmp[n++] = g_seq[pos][MAX_DIMEN - 1];
		while (i < seq) {
			int j = 0;
			while (j < dimen && g_seq[i][j] > g_seq[pos][j]) ++j;
			if (j == dimen) {
				tmp[n++] = g_seq[i][MAX_DIMEN - 1];
				pos = i;
			}
			++i;
		}
		if (n > boxes) {
			boxes = n;
			for (i = 0; i < boxes; ++i) ans[i] = tmp[i];		
		}		
	}

	printf("%d\n", boxes);
	for (k = 0; k < boxes; ++k) printf("%d ", ans[k]);
	printf("\n");
}

/***************************************************************************/
static void
read_sort(int *row, int **order, int boxidx, int dimen)
{
	int i = 0, j = 0, tmp = 0, volume = 0;
	int *ptmp;

	/* 1. read and sort dimension in one row */
	while (i < dimen && scanf("%d", &row[i]) != EOF) {
		/* sort dimen */
		for (j = 0; j < i; ++j) {
			if (row[i] < row[j]) {
				tmp = row[i];
				row[i] = row[j];
				row[j] = tmp;
			}
		}
		volume += row[i];
		++i;
	}

	row[MAX_DIMEN - 2] = volume; /* total dimensions */
	row[MAX_DIMEN - 1] = boxidx;
	order[boxidx] = row;

	/* sort order by volume */
	for (i = 0; i < boxidx; ++i) {
		if (volume < order[i][MAX_DIMEN - 2]) {
			ptmp = order[i];
			order[i] = order[boxidx];
			order[boxidx] = order[i];
		}
	}
}

/***************************************************************************/
static void
findnests(int **order, int selectbox, int *answer, int boxes, int dimen)
{

}

/***************************************************************************/
int 
main(void)
{
	int boxnum = 0, dimen = 0;
	int boxlist[MAX_BOX][MAX_DIMEN] = {0};
	int *orderbox[MAX_BOX] = {0};

	g_fptr = fopen("StackingBoxes.in", "r");
	if (g_fptr == NULL) {
		printf("open input file failed!!\n");
		return 0;
	}

	while (scanf("%d %d", &boxnum, &dimen) != EOF) {   
/*	while (fscanf(g_fptr, "%d %d", &boxes, &dimen) != EOF) { */
		int i = 0;

		/* read and sort */
		for (i = 0; i < boxnum; ++i) {
			int *row = boxlist[i];
			read_sort(row, orderbox, i, dimen);
		}	
		printf("-----------------\n");
		dump_boxes(boxlist, boxnum, dimen);		

		/* find nested boxes */

/*		dump_boxes(boxlist, boxes, dimen); 
		sort_sequence(boxes, dimen); 
		dump_boxes(boxes, dimen); 
		find_nest(boxes, dimen); */
	}
	return 0;
}

