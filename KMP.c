#include <stdio.h>
#include <string.h>

// Function to preprocess the pattern and create the LPS (longest prefix suffix) array
void computeLPSArray(char* pat, int m, int* lps) {
    int length = 0;  // length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0
    int i = 1;

    // The loop calculates lps[i] for i = 1 to m-1
    while (i < m) {
        if (pat[i] == pat[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];  // Use the previously calculated lps value
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Function to implement the KMP algorithm
void KMPSearch(char* txt, char* pat) {
    int n = strlen(txt);
    int m = strlen(pat);

    // Create the lps[] array to hold the longest prefix suffix values
    int lps[m];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, m, lps);

    int i = 0;  // index for txt[]
    int j = 0;  // index for pat[]

    // Iterate through the text to find the pattern
    while (i < n) {
        if (pat[j] == txt[i]) {
            i++;
            j++;
        }

        if (j == m) {
            // A match is found, print the index (0-based)
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];  // Use the LPS array to skip ahead
        } else if (i < n && pat[j] != txt[i]) {
            // Mismatch occurs
            if (j != 0) {
                j = lps[j - 1];  
            } else {
                i++;
            }
        }
    }
}

int main() {
    char txt[] = "ABABDABACDABABCABAB";
    char pat[] = "ABABCABAB";

    KMPSearch(txt, pat);  // Call the KMP search function

    return 0;
}
