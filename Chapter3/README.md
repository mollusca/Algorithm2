<<<<<<< HEAD
# Chapter 3  
## Chapter3-1 > DFS  
_input ����_  
��尳��(N) ��������(M)  
����� ������ ...  

/* ADJList + DFS */  
DFS(Depth_First_Search) idea  
Color�� ���� ���� �湮���� �ʾ����� WHITE(0)  
�湮���϶��� GRAY(1)  
�湮�� ���������� BLACK(2)�� �д�.  
color[100] (�湮���� Ȯ��) �迭�� p[100] (�θ� Ȯ��) �迭�� �۷ι� ������ �����Ѵ�.  

1. DFS
 > 1-1. 1���� ��尳������ color�� WHITE��, �θ� -1�� �ʱ�ȭ ���ش�.  
 > 1-2. 1���� ��尳������ DFS_visit�Լ��� �����Ѵ�.  
2. DFS_visit  
 > 2-1. color�� GRAY�� ��.  
 > 2-2. �ӽ� ��������� temp�� vertex[i]�� �������� �������ش�.  
 > 2-3. temp�� NULL, �� vertex�� ���������� ������ �ݺ��Ѵ�.
  >> 2-3-1. temp�� �������� color�� WHITE�϶�, temp�� �������� �θ� u�� �ΰ�, 
temp�� �������� parameter�� DFS_visit�Լ��� ��������� ����.  
  >> 2-3-2. temp�� ���� ���� �̵���Ŵ.  
 
 > color�� BLACK���� �д�.
3. DFS�� ����� p�迭�� �����.


## Chapter3-2 > Topological Sort
_input ����_  
��尳��(N) ��������(M)  
����� ������ ...  

/* DFS + Topological Sort */  
** Idea **  
Insert�Լ��� �߰��� DFS_visit�Լ��� ������ ������ insert���ش�.  
Insert�Լ��� Ű���� ���� �ӽó�带 ��忡 �߰����ִ� �Լ���.  
���ĵ� ����� PrintLinked�Լ��� ���� �����.  

1. Insert  
 > 1-1. data�� �ӽó���� ���������, ������ NULL�� �ʱ�ȭ ���ش�.
 > 1-2. ��尡 ������ �ٷ� head�� temp�� �������ְ�,  
 > 1-3. ��尡 ������ temp�� ������忡 head�� ������ �ص�, head�� temp�� �������ش�.  
2. PrintLinked  
 > 2-1. find�� head�� ����.  
 > 2-2. find�� ���ʴ�� ���.  

## Chapter3-3 > To Build The Tallest Tower
_input ����_  
��尳��(N)  
�غ� ���� ���� ...  

=======
# Chapter 3
## Chapter3-1 > DFS

## Chapter3-2 > Topological Sort

## Chapter3-3 > To Build The Tallest Tower
>>>>>>> 885b3147d42ae6c803edbd9f26b8b29c48019279
