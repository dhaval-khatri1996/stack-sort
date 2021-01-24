# stack-sort
A new sorting algorithm named stack-sort.

The basic princple is to divide and conquer. Each element is either added to current stack or the other stack based on wheather the current element is in order compared to the previous element. If its in order its added to current stack, otherwise the stack is changed and the element is added to new current stack.


C++ sort compared to stack sort on Ubuntu 10.04
1.5 * 10^8 integer elements
Time in seconds
        | Stack-sort  | C++ sort
Random  |     39      |    47
Sorted  |     1       |    26        
Reverse |     2       |    23

Note: Results can be optimized by micro-optimizing, like
    -merging smallest arrays first rather then just recursive merging 
    -thresshold can be better selected to save time