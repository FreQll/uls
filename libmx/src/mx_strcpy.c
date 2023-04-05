char *mx_strcpy(char *dst, const char *src) {
    int i = 0;
    const char *tSrc = src;
    for (; *tSrc; i++) *dst++ = *tSrc++;

    for (; *dst; i++) *dst++ = 0;

    dst -= i;
    return dst;
}
