# Chapter 3  
## Chapter3-1 > DFS  
_input 형식_  

| 노드개수(N) | 엣지갯수(M) |
| ----- | ----- |
| 출발지 | 목적지 | 

### /* ADJList + DFS */  
DFS(Depth_First_Search) idea  
Color를 통해 아직 방문하지 않았으면 WHITE(0)  
방문중일때는 GRAY(1)  
방문이 끝났을때는 BLACK(2)로 둔다.  
color[100] (방문여부 확인) 배열과 p[100] (부모 확인) 배열을 글로벌 변수로 선언한다.  

1. __DFS__
 > 1-1. 1부터 노드개수까지 color를 WHITE로, 부모를 -1로 초기화 해준다.  
 > 1-2. 1부터 노드개수까지 __DFS_visit__ 함수를 수행한다.  
2. __DFS_visit__  
 > 2-1. color를 GRAY로 둠.  
 > 2-2. 임시 노드포인터 temp를 vertex[i]의 다음으로 연결해준다.  
 > 2-3. temp가 NULL, 즉 vertex가 끝날때까지 다음을 반복한다.
  >> 2-3-1. temp의 목적지의 color가 WHITE일때, temp의 목적지의 부모를 u로 두고, temp의 목적지를 parameter로 __DFS_visit함수를 재귀적__ 으로 수행.  
  >> 2-3-2. temp를 다음 노드로 이동시킴.  
 
 > 2-4. color를 BLACK으로 둔다.
3. DFS의 결과는 p배열에 저장됨.


## Chapter3-2 > Topological Sort
_input 형식_  

|노드개수(N)|엣지갯수(M)|  
|----|----|
|출발지|목적지|  

### /* DFS + Topological Sort */  
** Idea **  
Insert함수를 추가해 DFS_visit함수가 끝나는 지점에 insert해준다.  
Insert함수는 키값을 가진 임시노드를 헤드에 추가해주는 함수임.  
정렬된 결과는 PrintLinked함수를 통해 출력함.  

1. __Insert__  
 > 1-1. data를 임시노드의 출발점으로, 다음은 NULL로 초기화 해준다.
 > 1-2. 헤드가 없으면 바로 head에 temp를 연결해주고,  
 > 1-3. 헤드가 있으면 temp의 다음노드에 head를 연결해 준뒤, head에 temp를 연결해준다.  
2. __PrintLinked__  
 > 2-1. find를 head로 연결.  
 > 2-2. find를 차례대로 출력.  

## Chapter3-3 > To Build The Tallest Tower
_input 형식_  

|노드개수(N)|||
|---|---|---|
|밑변|높이|무게|  
