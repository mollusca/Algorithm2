# Chapter2-1 >  Heap Sort
  
_input.txt 형식_  

|힙 크기|
|---|
|힙 배열|  

1. 파일에서 읽어들인 키를 저장할 힙 배열을 글로벌 변수로 선언 ( S[100] )
2. 파일 끝까지 키를 읽어 S배열에 저장
3. 힙 크기를 parameter로 한 __MakeHeap__ 함수 호출
 > 3-1. heapSize의 반 크기에서부터 1보다 작아질때까지 __siftdown__ 함수 호출  
``` 
void makeheap(int n) {
	int i;

	heapSize = n;

	for (i = n / 2; i >= 1; i--)
		siftdown(i);
}
```

4. __Siftdown__  
> 4-1. 불러온 인자 i에 해당하는 S[i]를 siftkey변수에 저장  
> 4-2. parent를 i로  
> 4-3. parent * 2가 HeapSize크기보다 커질때까지 아래를 반복
 >> 4-3-1. parent * 2 가 HeapSize보다 작고, S[parent * 2]값이 S[parent * 2 + 1]값보다 작을때, SmallerChild = parent * 2  
 >> 4-3-2. 위 조건에 해당없으면 SmallerChild = parent * 2 + 1  
 >> 4-3-3. siftkey값이 S[SmallerChild]값보다 클 때, S[parent]는 S[SmallerChild]이고, parent는 SmallerChild가 됨.  
 >> 4-3-4. 해당 없을 경우에는 while문 탈출.  

> 4-4. S[parent]를 siftkey로.  
```
void siftdown(int i) {
	int siftkey = S[i];
	int parent = i;
	int smallerChild;

	while (2 * parent <= heapSize) {
		if ((2 * parent < heapSize) && (S[2 * parent] < S[2 * parent + 1]))
			smallerChild = 2 * parent;
		else
			smallerChild = 2 * parent + 1;

		if (siftkey > S[smallerChild]) {
			S[parent] = S[smallerChild];
			parent = smallerChild;
		}
		else
			break;
	}
	S[parent] = siftkey;
}
```

5. __MakeHeap__ 을 힙 크기만큼으로 수행 했을때, 결과는 S배열에 저장된다.  
6. __RemoveKeys__  
 > 6-1. 1부터 heapSize까지 root함수호출 한것을 HeapSort배열에 저장  
```
 void removekeys() {
	int i, cnt = heapSize;

	for (i = 1; i <= cnt; i++)
		heapSort[i] = root();
}
```
 
7. __Root__  
 > 7-1. 뽑아 낼 값은 배열의 첫번째값. 즉 S[1]. keyout변수로 저장.  
 > 7-2. 배열의 마지막 값 S[heapSize]를 S[1]에 저장.  
 > 7-3. HeapSize--  
 > 7-4. 1번부터 __Siftdown__ 함수 호출.  
 ```
 int root() {
	int keyout = S[1];
	int i;

	S[1] = S[heapSize];
	heapSize--;
	
	siftdown(1);

	return keyout;
}
```
8. __InsertKeys__  
 > 8-1. HeapSize++  
 > 8-2. child를 heapSize로 둔다.  
 > 8-3. i를 heapSize/2 부터 1보다 작아질때까지 i를 반씩 줄이면서(parent) 반복한다.  
  >> 8-3-1. S[i]가 data보다 크면 S[child]에 S[i]. child를 i로 둔다.  
  >> 8-3-2. data보다 작을경우, S[child]를 data로 두고 반복문을 빠져나온다.
```
void insert(int data) {
	int child;
	int i;

	heapSize++;
	child = heapSize;

	for (i = heapSize / 2; 1 >= 1; i = i / 2) {
		if (S[i] > data) {
			S[child] = S[i];
			child = i;
		}
		else {
			S[child] = data;
			break;
		}
	}
}
```


# Chapter2-2 >  ADJLIST

input형식 

|노드갯수|엣지갯수||
|---|---|---|
|출발점|목적지|가중치|  

N : 노드갯수, M : 엣지갯수  
1. 목적지와 가중치, 다음 노드포인터를 갖는 Node구조체와 다음정보와 마지막 정보를 담는 Front구조체를 정의한다.  
```
typedef struct node* nodePointer;
typedef struct node {
	// 목적지
	int num;
	// 가중치
	int weight;
	nodePointer node_next;
} Node;

typedef struct front* frontPointer;
typedef struct front {
	nodePointer next;
	nodePointer last;
} Front;

frontPointer* vertex;
```
2. vertex포인터를 N+1크기만큼 Front구조체로 이중 동적할당 해준다.  
3. vertex를 초기화해준다.  
```
vertex = (frontPointer*)malloc(sizeof(Front*) * (N + 1));

	for (i = 0; i <= N; i++)
		vertex[i] = (frontPointer)malloc(sizeof(Front));
	for (i = 1; i <= N; i++) {
		vertex[i]->last = NULL;
		vertex[i]->next = NULL;
	}
```

4. 파일에서 Edge정보를 읽어 엣지갯수만큼 __addEdge__ 함수를 호출한다.  
 > 4-1. 임시 노드 temp를 동적할당해줌.  
 > 4-2. temp의 목적지, 가중치정보를 초기화해준다.  
 > 4-3. 출발점에서 다음노드 정보가 없으면 임시노드 temp를 연결해준다.  
 > 4-4. 다음 노드가 있으면 마지막노드의 다음에 temp를 연결해준다.  
 > 4-5. 출발점에서 마지막노드에 temp를 연결해준다.
```
void addEdge(int from, int to, int weight) {
	nodePointer temp = (nodePointer)malloc(sizeof(Node));

	temp->num = to;
	temp->weight = weight;
	temp->node_next = NULL;

	if (vertex[from]->next == NULL)
		vertex[from]->next = temp;
	else
		vertex[from]->last->node_next = temp;
	
	vertex[from]->last = temp;
}
```

