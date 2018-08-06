void memory_copy(char * source, char *dest, int nbytes) {
    int i;
    for (i=0;i<nbytes;i++) {
        *(dest + i) = *(source + i);
    }
    return;
}

int string_len(char *str) {
    int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

void swap(char *a, char *b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void string_rev(char *str, int n) {
    int i = 0;
    while (i < n-i-1) {
        swap(&str[i], &str[n-i-1]);
    }
}

void int_to_ascii(int n, char str_n[]) {
    int i=0, sign;
    if ((sign=n)<0) n=-n;
    do {
        str_n[i++] = n%10 + '0';
    } while((n/=10)>0);

    if(sign<0) str_n[i++] = '-';
    str_n[i] = '\0';
    // Reverse the number
    int len = string_len(str_n);
    string_rev(str_n, len);
}