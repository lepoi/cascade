// minimum between two variables
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

// dump char * memory block to another char *
void strdmps(char *dest, char *source, unsigned int length) {
    while (length--)
	*dest++ = *source++;
};

// dump char to char * (redundant)
void strdmpc(char *dest, char source) {
    *dest = source;
};

// dump char * memory block to stdout
void stddmp(char *source, unsigned int length) {
    while (length--)
	putc(*source++, stdout);
};

// dump char * memory block to stdout, formatted as hex
void stddmpx(char *source, unsigned int length) {
    while (length--)
	printf("%02x.", *source++);

    printf("\n");
};

// dump char * memory block to file
void fdmps(FILE *dest, char *source, unsigned int length) {
    printf("POI\n");
    while (length--) {
	printf("%c", *source);
    	fwrite(source++, 1, 1, dest);
	// putc(*source++, dest);
    }
};

