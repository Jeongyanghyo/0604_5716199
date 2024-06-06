#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {
	element data;
	struct DListNode* llink, * rlink;
}DListNode;

void init(DListNode* phead) {
	phead->llink = phead->rlink = phead;
}

void dinsert(DListNode* before, element data) {
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));   //<1>
	newnode->data = data;    //<1>
	newnode->llink = before;   //<2>
	newnode->rlink = before->rlink;  //<3>
	before->rlink->llink = newnode;   //<5>
	before->rlink = newnode;   //<4>
}

void print_dlist(DListNode* phead) {
    DListNode* p = phead->rlink;
    while (p != phead) {
        printf(" %2d", p->data);
        if (p->rlink != phead) {
            printf(" ->");
        }
        p = p->rlink;
    }
    printf(" (head)\n");
}

element ddelete(DListNode* head, DListNode* removed) {
	element r;
	if (removed == head) return;
	r = removed->data;

	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	return r;

}

int main(void) {
    DListNode* head = (DListNode*)malloc(sizeof(DListNode));
    init(head);
    element deleted;
    int choice, data;
    while (1) {
        printf("\n1: 숫자 입력 받아서 리스트 처음에 추가\n2: 숫자 입력 받아서 리스트 마지막에 추가\n3: 리스트 처음 노드 삭제\n4: 리스트 마지막 노드 삭제\n5: 리스트 프린트\n6: 종료\n");
        printf("선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("리스트 처음에 추가할 숫자를 입력하세요: ");
            scanf("%d", &data);
            dinsert(head, data);
            break;
        case 2:
            printf("리스트 마지막에 추가할 숫자를 입력하세요: ");
            scanf("%d", &data);
            dinsert(head->llink, data);
            break;
        case 3:
            deleted = ddelete(head, head->rlink);
            break;
        case 4:
            deleted = ddelete(head, head->llink);
            break;
        case 5:
            print_dlist(head);
            break;
        case 6:
            free(head);
            printf("종료합니다...\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
    return 0;
}