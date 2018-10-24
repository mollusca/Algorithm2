# MaxFlow (최대 유량 알고리즘)

## Concept
가중치가 있는 Directed Graph __G__ 와 Source노드 __s__, Destination노드 __t__ 가 주어졌을 때, 각 엣지의 capacity를 고려하여 __s__ 에서 __t__ 로 흘려보낼수 있는 최대 유량(flow)를 구하는 알고리즘.  
__G__ 의 각 엣지 가중치를 Capacity라고 하며, (u,v)의 Capacity를 __c(u,v)__ 라고 쓴다. Capacity는 항상 0이상 이다. 노드 __u__ 와 __v__ 사이를 흐르는 유량(net flow)는 __f(u,v)__ 라고 쓰며, 유량은 실수치 함수.  

최대유량 문제의 세가지 제약조건.  
- __Capacity constraint__ : __f(u,v)__ <= __c(u,v)__ (유량은 용량을 초과할수 없다.)
- __Skew symmetry__ : __f(u,v)__ = __-f(u,v)__
- __Flow conservation__ : 각 노드에서 유량은 새로 더해지거나 감소되지 않는다.

만약, __c(u,v) = 10__ 이고, __c(v,u) = 4__ 라면 ..  
![1](https://github.com/mollusca/Algorithm2/blob/master/IMG/Maxflow_img/1.PNG)  

__u__ 에서 __v__ 로 유량이 8이면..  
![2](https://github.com/mollusca/Algorithm2/blob/master/IMG/Maxflow_img/2.png)  

__v__ 에서 __u__ 로 유량이 3이면..  
![3](https://github.com/mollusca/Algorithm2/blob/master/IMG/Maxflow_img/3.png)  

위의 그래프를 양의 순 유량(positive net flow)으로 다시 표시하면.. (cancellation)  
![4](https://github.com/mollusca/Algorithm2/blob/master/IMG/Maxflow_img/4.png)  

_Residual network_ : __u__ 에서 __v__ 로의 _residual capacity_ __Cf(u,v)__ 는  
  - __Cf(u,v) = C(u,v) - f(u,v)__

예를 들어, 아래 그림의 왼쪽과 같은 유량 그래프 __G__ 가 주어졌을 때, __G__ 의 _residual network_ __Gf__ 는 아래 그림의 오른쪽과 같다.  
__Gf__ 의 엣지는 _cancellation_ 과정을 거쳐 도출된 양의 순 유량(positive net flow)을 바탕으로 계산된다.  
![5](https://github.com/mollusca/Algorithm2/blob/master/IMG/Maxflow_img/5.png)  
- __Cf(u,v) = C(u,v) - f(u,v) = 9 - 4 = 5__  
- __Cf(v,u) = C(v,u) - f(v,u) = 0 - (-4) = 4__  

__argumenting path__ 란 _residual network_ __Gf__ 상에서 __s__ 에서 __t__ 로 가는 경로를 가르킨다.
