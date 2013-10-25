#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************/
typedef struct _list_type {
    struct _list_type *last_;
    struct _list_type *next_;
    char no_;   /** block number */
    char pos_;  /** block postion */
} list_type;

void **ppblks_;
list_type *pblks_;

/***************************************************************************/
static void
list_create(const char blocks)
{
    int i = 0;

    /* allocate two-dimension */
    list_type *pblks = (list_type *)malloc(sizeof(list_type) * blocks);
    pblks_ = pblks;
    ppblks_ = (void **)malloc(sizeof(void *) * blocks);

    for (i = 0; i < blocks; ++i) {
        ppblks_[i] = (void *)pblks;
        pblks->pos_ = i;
        pblks->no_ = i;
        pblks->last_ = NULL;
        pblks->next_ = NULL;
        pblks++;
    }
}

/***************************************************************************/
static void
list_dump(int size)
{
    int i = 0;
    list_type * blk;

    for (i = 0; i < size; ++i) {
        printf("%d:", i);
        blk = (list_type *)(*(ppblks_ + i));
        if (blk == NULL) {
			printf("\n");
			continue;
		}
        printf(" %d", blk->no_);
        while (blk->next_ != NULL) {
            blk = blk->next_;
            printf(" %d", blk->no_);
        }
        printf("\n");
    }
}

/***************************************************************************/
static void
restore_blk(list_type * pblk)
{
	list_type *p;
	if (pblk == NULL) return;

	p = pblk->next_;
	while (p != NULL) {
		p->last_ = p->next_ = NULL;
		p->pos_ = p->no_;
		*(ppblks_ + p->no_) = p;
		p = p->next_;
	}

	pblk->next_ = NULL;
}
	
/***************************************************************************/
static void
move_blk(list_type * psrc, list_type * pdst)
{
/*	if (psrc->last_ == NULL) *(ppblks_ + psrc->no_) = NULL; 
	if (psrc->last_ != NULL) psrc->last_->next_ = NULL; */

    /** find the tail block */
    list_type * tmp = pdst;
    while (tmp->next_ != NULL) tmp = tmp->next_;
    psrc->last_ = tmp;
    tmp->next_ = psrc;

	*(ppblks_ + psrc->no_) = NULL;

    /** change block position for entries in psrc */
    tmp = psrc;
	while (tmp != NULL) {
		tmp->pos_ = pdst->pos_;
		tmp = tmp->next_;
	}
}

/***************************************************************************/
int
main(void)
{
	int blocks = 0;
	int err = 0;
	err = scanf("%d", &blocks);
	list_create(blocks);

	while (1) {
		char act1[5] = {0}, act2[5] = {0};
		int src = 0, dst = 0;
		list_type *psrc = NULL, *pdst = NULL, *tmp = NULL;

		err = scanf("%s", act1);
		if (strcmp(act1, "quit") == 0) {
			list_dump(blocks);
			break;
		}

		err = scanf("%d%s%d", &src, act2, &dst);
	
		if (src == dst) continue;
		psrc = pblks_ + src;
		pdst = pblks_ + dst;
		if (psrc->pos_ == pdst->pos_) continue;
			
		if (strcmp(act1, "move") == 0) {
			if (strcmp(act2, "onto") == 0) {
				/*restore_blk(psrc->last_); */
				if (psrc->last_ != NULL) restore_blk(psrc->last_);
				restore_blk(pdst);
				move_blk(psrc, pdst);
	
			} else if (strcmp(act2, "over") == 0) {
				/*restore_blk(psrc->last_);*/
				if (psrc->last_ != NULL) restore_blk(psrc->last_);
				move_blk(psrc, pdst);
			}
			
		} else if (strcmp(act1, "pile") == 0) {
			if (strcmp(act2, "onto") == 0) {
				if (psrc->last_ != NULL) psrc->last_->next_ = NULL;
				restore_blk(pdst);
				move_blk(psrc, pdst);

			} else if (strcmp(act2, "over") == 0) {
				if (psrc->last_ != NULL) psrc->last_->next_ = NULL;
				move_blk(psrc, pdst);
			}
		}
	}
}
