#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;

typedef struct info{
	int job;
	int deadline;
	int profit;
} Info;

void Init(int *parent, int *schedule, int *empty) {
	int i;
	for (i = 1; i <= N; i++) {
		parent[i] = -1;
		empty[i] = i;
		schedule[i] = 0;
	}
}

int CollapsingFind(int *parent, int i) {
	int r, s;

	for (r = i; parent[r] >= 0; r = parent[r]);

	while (i != r) {
		s = parent[i];
		parent[i] = r;
		i = s;
	}
	return r;
}

void SimpleUnion(int *parent, int i, int j) {
	parent[i] = j;
}
// SimpleUnion
void Scheduling1(Info sch_info, int *parent, int *schedule, int *empty) {
	int temp, root, empty_slot;

	root = CollapsingFind(parent, sch_info.deadline);
	empty_slot = empty[root];
	schedule[empty_slot] = sch_info.job;

	if (empty_slot == 1)
		temp = N;
	else
		temp = empty_slot - 1;

	SimpleUnion(parent, empty_slot, temp);
}

void WeightedUnion(int *parent, int *empty, int i, int j) {
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) {
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
		empty[i] = empty[j];
	}
}
// WeightedUnion
void Scheduling2(Info sch_info, int *parent, int *schedule, int *empty) {
	int root1, root2;
	int empty_slot, temp;
	
	root1 = CollapsingFind(parent, sch_info.deadline);
	empty_slot = empty[root1];
	schedule[empty_slot] = sch_info.job;

	if (empty_slot == 1)
		temp = N;
	else
		temp = empty_slot - 1;
	
	root2 = CollapsingFind(parent, temp);
	
	WeightedUnion(parent, empty, root1, root2);
}

int main() {
	int i, j;
	int *parent, *schedule, *empty;
	Info sch_info;

	char *filename = (char *)malloc(sizeof(char) * 20);
	scanf("%s", filename);
	strcat(filename, ".txt");
	FILE *fin = fopen(filename, "r");
	free(filename);	

	fscanf(fin, "%d", &N);
	
	parent = (int *)malloc(sizeof(int) * (N + 1));
	schedule = (int *)malloc(sizeof(int) * (N + 1));
	empty = (int *)malloc(sizeof(int) * (N + 1));

	parent[0] = N;
	Init(parent, schedule, empty);

	for (i = 1; i <= N; i++) {
		fscanf(fin, "%d %d %d", &sch_info.job, &sch_info.deadline, &sch_info.profit);
		Scheduling1(sch_info, parent, schedule, empty);
		//Scheduling2(sch_info, parent, schedule, empty);
		
		for (j = 1; j <= N; j++)
			printf("%d ", schedule[j]);
		printf("\n");
		
	}
	for (j = 1; j <= N; j++)
		printf("%d ", schedule[j]);
	printf("\n");

	free(parent);
	free(schedule);
	free(empty);
	fclose(fin);
	return 0;
}