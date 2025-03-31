// Write a function that:
// - Has 3 int paramaters.
// - If all numbers are equal: return the sum.
// - If 2 numbers are equal: return the non equal number.
// - If none are equal: return 5.
// - Constraint 1 --> No traditional control flow (if / while / case ...)
// - Constraint 2 --> No equality (a == b)


#include <stdio.h>
#include <stdint.h>


// BRANCHLESS
int branchless_function(int a, int b, int c) {
    	
	return
    	
	!(a ^ b) * !(b ^ c) * (a + b + c)               // All equal check
    	
	+

    	(((!(a ^ b) + !(b ^ c) + !(a ^ c)) > 0) -	// Two Equal check 
	(!(a ^ b) * !(b ^ c))) * (a ^ b ^ c)

    	+

    	!!(a ^ b) * !!(b ^ c) * !!(a ^ c) * 5;          // None equal check

}


// EQUALITY
int equality_function(int a, int b, int c) {

	int all_equal = 	(a == b && b == c) * (a + b + c);

	int two_equal =		((a == b && a != c) * c) + 
                    		((b == c && b != a) * a) + 
                    		((a == c && a != b) * b);
    
    	int none_equal = 	(a != b && b != c && a != c) * 5;
    
    	return 			all_equal + two_equal + none_equal;
}


// TRADITIONAL
int trad_function(int a, int b, int c) {
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
    int test_cases[][3] = {
        {5, 5, 5},
        {2, 2, 7},
        {3, 8, 8},
        {9, 4, 9},
        {1, 2, 3}
    };
    
    // Testing correctness against known working functions.
    printf("Testing correctness:\n");
    for (int i = 0; i < 5; i++) {
        int a = test_cases[i][0];
        int b = test_cases[i][1];
        int c = test_cases[i][2];
        int trad = trad_function(a, b, c);
        int equal = equality_function(a, b, c);
        int branch = branchless_function(a, b, c);
        
        printf("Case (%d,%d,%d): Traditional=%d, Equality=%d, Branchless=%d", 
               a, b, c, trad, equal, branch);
        
        if (trad != equal || trad != branch) {
            printf("ERROR: Results don't match!\n");
        }
        else {
            printf("  -> PASSED!\n");
        }
    }
}
