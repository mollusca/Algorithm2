# Chapter 4

## BellmanFord (자동차경주대회)
![정비소](https://github.com/mollusca/Algorithm2/blob/master/IMG/RepairShop.PNG)

_input 형식_

|정비받지않고 갈수있는 최대거리|
|:----:|
|정비소의 갯수|
|정비소의 거리를 차례대로|
|정비소별 정비시간|

```
int p[1000]; // 방문하는 정비소 번호
int d[1000]; // 총 걸리는 시간
int length[1000]; // 정비소 사이 거리
int r[1000]; // 정비 시간

int maxLen; // 갈 수있는 최대 거리
int N; // 정비소 갯수
int cnt; // 방문 수
```
1. __BellmanFord__  
 > 1-1. 현재까지 달린 거리를 기록할 변수 temp선언.  
 > 1-2. temp에 정비소 사이거리를 가중해주면서 maxLen이 초과하지 않도록 해준다.  
 > 1-3. 가중해준 값이 현재위치의 시간과 다음 정비소 시간의 합보다 클 때 총 걸린시간을 현재값과 다음값의 합으로 바꿔주고 p[다음값]을 현재위치로 해준다.  
 ```
 void BellmanFord() {
	int i, j;
	int temp; // 달린 거리
	
	for (i = 0; i <= N; i++) {
		temp = 0;
		for (j = i + 1; j <= N; j++) {
			temp += length[j];

			if (temp > maxLen)
				break;
			
			if (d[j] > d[i] + r[j]) {
				d[j] = d[i] + r[j];
				p[j] = i;
			}
		}
	}
}
 ```
2. 들른 정비소 수를 세준다음, 정비소 순서를 출력해준다.  


## MaxFlow
[MaxFlow](https://github.com/mollusca/Algorithm2/tree/master/Chapter4/MaxFlow)
