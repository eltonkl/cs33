//3.56
int loop(int x, int n)
{
    int result = -1;
    int mask;
    for (mask = 1; mask != 0; mask =  mask << n) {
        result ^= mask & x;
}

//A. esi holds x, ebx holds n, edi holds result, edx holds mask
//B. result is initally -1, and mask is initially 1
//C. The test condition for mask is if mask != 0. Using test with one register 
//as both operands sets the zero flag if the register is zero. The loop continues if
//mask is not zero.
//D. mask gets updated with a left shift by n. The emitted assembly only uses the lower
//8 bits of N because a left shift by values greater than that is the same as shifting by > 31.
//E. result is updated with x & mask. eax is a temporary that at first holds mask and is then 
//&'d with x. eax is then used to ^ edi, which holds the result.