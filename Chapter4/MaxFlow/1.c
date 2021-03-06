#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

#define TRUE 1
#define FALSE 0
#define MAX 999999

typedef struct queueNode *queueNodePointer;
typedef struct queueNode {
	int vertex;
	queueNodePointer next;
}QueueNode;

typedef struct queue_list *queueListPointer;
typedef struct queue_list {
	queueNodePointer front;
	queueNodePointer tail;
}QueueList;

void QueueInit(queueListPointer root) {
	root->front = NULL;
	root->tail = NULL;
}

int isEmpty(queueListPointer root) {
	if (root->front == NULL)
		return TRUE;
	return FALSE;
}

void enQueue(queueListPointer root, int data) {
	queueNodePointer newNode = (queueNodePointer)malloc(sizeof(QueueNode));
	
	newNode->next = NULL;
	newNode->vertex = data;

	if (isEmpty(root)) {
		root->front = newNode;
		root->tail = newNode;
	}
	else {
		root->tail->next = newNode;
		root->tail = newNode;
	}
}

void deQueue(queueListPointer root) {
	int output;
	queueNodePointer dequeue_node;

	if (isEmpty(root)) {
		printf("Queue is Empty \n");
		exit(-1);
	}
	dequeue_node = root->front;
	output = dequeue_node->vertex;

	// 마지막 한개의 노드가 dequeue가 될때.
	if (root->front->next == NULL) {
		root->front = NULL;
		root->tail = NULL;

		free(dequeue_node);
		return;
	}
	root->front = dequeue_node->next;
	
	free(dequeue_node);
}

int getFront(queueListPointer root) {
	return root->front->vertex;
}

/*					큐	끝					*/		

typedef struct node *nodePointer;
typedef struct node {
	int num;
	int capacity;
	int flow;

	nodePointer tween;
	nodePointer next;
} Node;

typedef struct front *frontPointer;
typedef struct front {
	nodePointer next;
	nodePointer last;
} Front;

/*				 구조체 끝				*/

frontPointer *vertex;
int N, M;
int color[1000];
int p[1000];
int d[1000];

QueueList s1;
int maxFlow = 0;

/*				전역 끝				*/

void insertNode(int from, int to, int capa) {
	nodePointer temp = (nodePointer)malloc(sizeof(Node));
	nodePointer find = vertex[from]->next;

	temp->num = to;
	temp->capacity = capa;
	temp->flow = 0;
	temp->next = NULL;
	temp->tween = NULL;
	
	// 아직 들어온게 없을 때
	if (vertex[from]->next == NULL) {
		vertex[from]->next = temp;
		vertex[from]->last = temp;
	}
	else {
		// 이미 존재하는지 확인
		while (1) {
			// 끝까지 없으면 제일 끝에 삽입
			if (find == NULL) {
				vertex[from]->last->next = temp;
		
				vertex[from]->last = temp;
				break;
			}
			// 존재하면 capacity값만 바꿈
			if (find->num == to) {
				find->capacity = temp->capacity;
				break;
			}
			find = find->next;
		}
	}
}

void setTween(int from, int to) {
	nodePointer findFrom = vertex[from]->next;
	nodePointer findTo = vertex[to]->next;

	while (1) {
		if (findFrom->num == to)
			break;

		findFrom = findFrom->next;
	}
	while (findTo->num != from) {
		findTo = findTo->next;
	}
	findFrom->tween = findTo;
	findTo->tween = findFrom;
}

void printList() {
	int i;
	for (i = 0; i <= N + 1; i++) {
		nodePointer Print = vertex[i]->next;

		printf("%d : ", i);

		while (Print) {
			printf("(%d, %d, %d) ", Print->num, Print->capacity, Print->flow);
			Print = Print->next;
		}
		printf("\n");
	}
}

void BFS(queueListPointer s1, int s) {
	int u;
	nodePointer temp;

	for (u = 0; u <= N + 1; u++) {
		color[u] = WHITE;
		d[u] = MAX;
		p[u] = -1;
	}
	color[s] = GRAY;
	d[s] = 0;
	p[s] = -1;

	QueueInit(&s1);
	enQueue(&s1, s);

	while (!isEmpty(&s1)) {
		u = getFront(&s1);
		deQueue(&s1);

		temp = vertex[u]->next;

		while (temp != NULL) {
			if ((color[temp->num] == WHITE) && (temp->capacity - temp->flow > 0)) {
				color[temp->num] = GRAY;
				d[temp->num] = d[u] + 1;
				p[temp->num] = u;

				enQueue(&s1, temp->num);
			}
			temp = temp->next;
		}
		color[u] = BLACK;
	}
}

void findFlow(queueListPointer s1) {
	nodePointer arr[1000];
	nodePointer find;

	int residual = MAX;
	int now, before, temp, i;

	while (1) {
		BFS(&s1, 0);

		now = N + 1; // 마지막 노드
		before = p[N + 1]; // 마지막 노드가 갈 곳

		if (p[now] == -1)
			return;
		temp = N + 1;

		for (i = d[N + 1] - 1; i >= 0; i--) {
			find = vertex[p[temp]]->next;

			while (1) {
				if (find->num == temp)
					break;
				find = find->next;
			}
			arr[i] = find;

			temp = p[temp];
		}

		// residual 찾기 ( min값 찾기)
		for (i = 0; i <= d[N + 1] - 1; i++)
			if ((arr[i]->capacity - arr[i]->flow) < residual)
				residual = arr[i]->capacity - arr[i]->flow;

		// flow값 만큼 빼기
		for (i = 0; i <= d[N + 1] - 1; i++) {
			arr[i]->flow = arr[i]->flow + residual;
			arr[i]->tween->flow = 0 - arr[i]->flow;
		}

		// MaxFlow값 증가
		maxFlow = maxFlow + residual;
	}
}

int findTo(int from, int to) {
	nodePointer find = vertex[to]->next;

	while (find != NULL) {
		if (find->num == from)
			return 1;
		find = find->next;
	}
	return 0;
}

int main() {
	int i, from, to, capa;
	

	FILE *fin = fopen("input2.txt", "r");
	FILE *fout = fopen("output.txt", "w");

	fscanf(fin, "%d %d", &N, &M);
	vertex = (frontPointer *)malloc(sizeof(frontPointer) * (N + 2));

	for (i = 0; i <= N + 1; i++) {
		vertex[i] = (frontPointer)malloc(sizeof(Front));
		vertex[i]->last = NULL;
		vertex[i]->next = NULL;

		color[i] = WHITE;
		p[i] = -1;
	}
	for (i = 0; i < M; i++) {
		fscanf(fin, "%d %d %d", &from, &to, &capa);

		insertNode(from, to, capa);

		// 존재하지 않을때
		if (!findTo(from, to))
			insertNode(to, from, 0);
		setTween(from, to);
	}
	
	printList();
	
	BFS(&s1, 0);

	printf("\nbfs[i] : ");
	for (i = 0; i <= N + 1; i++)
		printf("%d ", p[i]);
	printf("\n");

	findFlow(&s1);

	printf("\nMaxflow : %d\n", maxFlow);

	fclose(fin);
	fclose(fout);
	return 0;
}