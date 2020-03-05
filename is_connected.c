#include <stdio.h>
#include <string.h>
#include <stdbool.h> // For bool
#include <ctype.h> // For isspace(), etc.
#include <errno.h> // For better error messages

#define BUFSIZE 300

/* Return position of first non-whitespace character or -1 if only
white-space is found. */
int first_non_white_space(const char *s) {
	int i = 0; // Start at first char.
	// Advance until we hit EOL as long as we're loooking at white-space.
	while (s[i] && isspace(s[i])) {
		i++;
	}
	if (s[i]) {
		return i; // Return position of found a non-white-space char.
	} else {
		return -1; // Return fail.
	}
}

/* Return position of last non-whitespace character or -1 if only
36 white-space is found. */
int last_non_white_space(const char *s) {
	// Start at last char.
	int i = strlen(s) - 1;
	// Move back until we hit beginning-of-line as long as we're
	// loooking at white-space.
	while (i >= 0 && isspace(s[i])) {
		i--;
	}
	if (i >= 0) {
		return i; // Return position of found a non-white-space char.
	} else {
		return -1; // Return fail.
	}
}


/* Return true if s only contains whitespace */
bool line_is_blank(const char *s) {
	// Line is blank if it only contained white-space chars.
	return first_non_white_space(s) < 0;
}

/* Return true if s is a comment line, i.e. first non-whitespc char is '#' */
bool line_is_comment(const char *s) {
	int i = first_non_white_space(s);
	return (i >= 0 && s[i] == '#');
}


int main(int argc, const char **argv) {
	//char line[BUFSIZE]; // Input buffer
	//char longest[BUFSIZE] = ""; // Longest string seen so far
	//int max_len = 0; // Length of longest string seen so far
	const char *file_name;
	//const char *dest1 = "UMU";
	//const char *dest2 = "ABC";
	FILE *in;

	// Verify number of parameters
	if (argc <= 1) {
		fprintf(stderr, "Usage: longest file.txt\n");
		return -1;
	}

	// Try to open the input file
	file_name = argv[1];
	in = fopen(file_name, "r");
	if (in == NULL) {
		fprintf(stderr, "Couldn't open input file %s: %s\n",
		file_name, strerror(errno));
		return -1;
	}
	char ch;
	while((ch=fgetc(in))!=EOF){
		if(ch=='\n'){

		}
		fprintf(stderr, "%c", ch);
	}
	/*
	int i = 1;
	// Read a line at a time from the input file until EOF
	while (fgets(line, BUFSIZE, in) != NULL) {
		if (line_is_blank(line) || line_is_comment(line)) {
		// Ignore blank lines and comment lines.
			continue;
		}
		// How long is the line, ignoring leading and trailing
		// white-space? (We know there is at least one
		// non-white-space char.)
		int beg = first_non_white_space(line);
		int end = last_non_white_space(line);
		int len = end - beg + 1;



		strncpy(longest, line + beg, len);

		if(memcmp(longest, dest1, len)){
			fprintf(stderr, "Found UMU:%d\n",i);
		}

		if(memcmp(longest, dest2, len)){
			fprintf(stderr, "Found ABC:%d\n",i);
		}

		i++;
	}
	*/

	// Close files before exit
	if (fclose(in)) {
		fprintf(stderr, "Failed to close %s: %s\n",
		file_name, strerror(errno));
		return -1;
	}

	return 0;
}
