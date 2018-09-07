/* Quicksort + Randomized Pivotpoint + Permutation */

/* QuickSort의 Process */
1. Pivotpoint를 잡을 수를 정한다.
2. Sorting할 자료의 start가 end가 넘지 않는 선에서, 변수 i를 Pivotpoint + 1로, j를 Pivotpoint로 설정해준다.
3. i를 증가시키면서 , pivotpoint의 자료값의 대소를 판별하여, 작은수는 왼쪽, 큰수는 오른쪽으로 몰아준다. 
4. i번쨰 값이 pivotitem보다 작은 수일 경우에, j를 증가시켜주고, 증가시킨 j번째 값과 Swap해준다.
5. i가 자료의 끝 번호에 도달하면, j번째와 Pivotpoint번째의 값을 Swap해준뒤, pivotpoint의 값을 j로 둔다.
6. 재귀적으로 end번호에 pivotpoint -1, start번호에 pivotpoint + 1를 해주어 나누어진 파티션에 대해 해결한다.

/* Permutation의 Process */
1. 재귀적으로 함수를 짤때, 제일 처음은 탈출조건을 명시한다.
2. Permutation의 재귀탈출 조건은 left와 right가 같아지거나 left가 right보다 커지는 경우임. -> 출력 후, 재귀탈출
3. 받아들인 문자열을 QuickSort를 이용해 정렬한후, 출력.
4. 정렬된 left+1의 값으로부터 right가 left와 크거나 같아지면서, left값보다 right값이 작으면 값을 Swap해줌.
5. 다시 left+1을 한뒤, Perm함수 호출하여 재귀적으로 해결한다.

/* Error */
180906. Chapter1/ QUICKSORT) RANDMIZED 하는데 문제있음. -> pivotpoint를 포인터형태로 전달해줘서 해결함.
