#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 1. High Complexity & Too Many Params (AST Engine will catch this)
void ProcessData_Complex(int a, int b, int c, int d, int e, int f, int g) {
    if (a > b) {
        if (b > c) {
            if (c > d) {
                if (d > e) {
                    if (e > f) {
                        printf("Deep nesting detected!\n");
                    }
                }
            }
        }
    }
}

// 2. Buffer Overflow & Command Injection (RAG Engine & CodeBERT will catch this)
void handle_user_input(char *user_input) {
    char buffer[50];
    
    // RAG Engine: Buffer Overflow (CWE-120) -> auto-fixes to strncpy
    strcpy(buffer, user_input);
    
    // RAG Engine: Format String Vulnerability (CWE-134)
    printf(buffer);
    
    // RAG Engine: Command Injection (CWE-78) -> auto-fixes by commenting out
    system(user_input);
}

// 3. Memory Leak (RAG Engine will catch this)
void memory_leak_example() {
    char *data = malloc(1024);
    // RAG Engine: Missing NULL check after malloc (CWE-252)
    
    // Hardcoded Credential (CWE-798)
    char *api_key = "sk_live_1234567890abcdef";
}
