#include <stdio.h>
#include <stdint.h>

// Attempt at a branchless implementation
int branchlessFunction(int a, int b, int c) {
    // v3.0 Final
    return
    !(a ^ b) * !(b ^ c) * (a + b + c)               // All equal check
    +
    (!(a ^ b) * !!(b ^ c) * c) +                    // Any two equal check
    (!(b ^ c) * !!(a ^ b) * a) +
    (!(a ^ c) * !!(a ^ b) * b)
    +
    !!(a ^ b) * !!(b ^ c) * !!(a ^ c) * 5;          // None equal check

    // Confirming my understanding:
    // Took me a while to get my head around this one, but as I had more time outside of the interview it let me play with the bitwise XOR operators and observe.
    // For integers, if (a == b) then we get a 0. And if not we get some non-zero value (5 ^ 3) (5 != 3) (101 ^ 011) --> 110. !!(6) = !(0) = 1 MADNESS!
    // So stacking '!' we can just normalize a result to 1 or 0 dependant on what the logic requires.
    // Results we don't want are 0'd out, and results we do want are calculated appropriately.
    // Also going over the assembly I noticed no jmp codes for this function, instead sete and setne is used, which from what I can see sets flags to 1 or 0, which makes sense given this execution.

   
    // Old versions below.
    
    
    // V1.0 
    // Check if pairs are equal (0 when equal, 1 when different)
    // int ab = !!(a ^ b);
    // int bc = !!(b ^ c);
    // int ac = !!(a ^ c);
    
    // // Calculate cases
    // int allEqual = (1 - ab) * (1 - bc) * (a + b + c);
    // int twoEqual = ((1 - ab) * bc * c) + ((1 - bc) * ab * a) + ((1 - ac) * ab * b);
    // int noneEqual = ab * bc * ac * 5;
    
    // // Only one of these conditions will once again (hopefully) evaluate to non-zero
    // return allEqual + twoEqual + noneEqual;

    
    // V2.0
    // // Attempt at version without assignment.
    // return 
    // // All equal check
    // (1 - !!(a ^ b)) * (1 - !!(b ^ c)) * (a + b + c)
    // +
    // // Any two equal check
    // ((1 - !!(a ^ b)) * !!(b ^ c) * c) + 
    // ((1 - !!(b ^ c)) * !!(a ^ b) * a) + 
    // ((1 - !!(a ^ c)) * !!(a ^ b) * b)
    // +
    // // None equal check
    // !!(a ^ b) * !!(b ^ c) * !!(a ^ c) * 5;

}


// Implementation using comparators but no branching (solution during interview)
int compareFunction(int a, int b, int c) {
    // If all integers are equal, return their sum
    int allEqual = (a == b && b == c) * (a + b + c);
    
    // If exactly two integers are equal, return the third one
    int twoEqual =  ((a == b && a != c) * c) + 
                    ((b == c && b != a) * a) + 
                    ((a == c && a != b) * b);
    
    // If no integers are equal, return 5
    int noneEqual = (a != b && b != c && a != c) * 5;
    
    // Only one of these conditions will (hopefully) evaluate to non-zero
    return allEqual + twoEqual + noneEqual;
}


// Traditional implementation with control flow for completeness.
int tradFunction(int a, int b, int c) {
    if (a == b && b == c) {
        return a + b + c;
    } else if (a == b) {
        return c;
    } else if (b == c) {
        return a;
    } else if (a == c) {
        return b;
    } else {
        return 5;
    }
}


int main() {
    // Cases covering a few possible scenarios
    int testCases[][3] = {
        {5, 5, 5},
        {2, 2, 7},
        {3, 8, 8},
        {9, 4, 9},
        {1, 2, 3}
    };
    
    // Testing correctness against known working functions.
    printf("Testing correctness:\n");
    for (int i = 0; i < 5; i++) {
        int a = testCases[i][0];
        int b = testCases[i][1];
        int c = testCases[i][2];
        int trad = tradFunction(a, b, c);
        int comp = compareFunction(a, b, c);
        int branch = branchlessFunction(a, b, c);
        
        printf("Case (%d,%d,%d): Traditional=%d, Comparator=%d, Branchless=%d", 
               a, b, c, trad, comp, branch);
        
        if (trad != comp || trad != branch) {
            printf("ERROR: Results don't match!\n");
        }
        else {
            printf("  -> PASSED!\n");
        }
    }
}