#pragma once //include guard

#undef strtok

char *strtok(char * __restrict str, const char * __restrict delim);

char *strtok(char * __restrict str, const char * __restrict delim) {
    static char *saved = nullptr;
    
    // Helper lambda to check if a character is a delimiter
    auto is_delim_char = [&](char c) -> bool {
        for (const char *p = delim; *p != '\0'; p++) {
            if (*p == c) return true;
        }
        return false;
    };
    
    char *start;
    
    if (str != nullptr) {
        start = str;
    } else {
        start = saved;
        if (start == nullptr) return nullptr;
    }
    
    // Skip leading delimiters
    while (is_delim_char(*start)) {
        start++;
    }
    
    // Check if we reached end of string
    if (*start == '\0') {
        saved = nullptr;
        return nullptr;
    }
    
    // Find end of token
    char *token_start = start;
    while (!is_delim_char(*start) && *start != '\0') {
        start++;
    }
    
    // Replace delimiter with '\0'
    if (*start != '\0') {
        *start = '\0';
        start++;
    }
    
    // Save position for next call (AFTER the '\0' we just placed)
    saved = start;
    
    return token_start;
}
