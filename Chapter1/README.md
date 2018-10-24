# Quicksort + Randomized Pivotpoint + Permutation

## /* QuickSort의 Process */
1. Set Pivotpoint.
2. Set variable "i" to (Pivotpoint + 1) and "j" to (Pivotpoint) if the start of the data to be Sorted does not exceed end.
3. By increasing i, determining the amount of data value in the pivotpoint, "a small number is left and a large number is right". 
4. If the "i"th value is less than the pivotitem, increase "j" and swap with the "j"th value that is increased.
5. When "i" reaches the end number of the data, swap the value of j and pivot in data, and set the value of pivotpoint to j.
6. End number to Pivotpoint -1, start number to Pivotpoint + 1 to resolve the partition that is divided reculsivly.

## /* Permutation의 Process */
1. When recursively  a function, the first thing you specify is the termination condition.
2. The termination condition of Permutation is when the right and left are equal to the right or greater than the right. -> After printed, termination.
3. Sort the accepted string using QuickSort and print it out.
4. From the aligned "left+1" value, the right becomes greater than or equal to the left, and if the right value is less than the left value, swaps the value.
5. After the left+1, call the Perm function to resolve it recursively.  

/* Randomized Idea */  
Set the pivotpoint randomly, Swap randomized pivotitem and the left value of the data.

/* Error */  
180906. Chapter1/ QUICKSORT) RANDMIZED 하는데 문제있음. -> pivotpoint를 포인터형태로 전달해줘서 해결함.
