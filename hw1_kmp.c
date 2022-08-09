#define MAX_STR 10000000
#define MAX_PAT 3000

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void kmpmatch(char*, char*);
void failure(char*);

char str[MAX_STR];
char pat[MAX_PAT];
int fail[MAX_PAT];
int matchedindex[MAX_STR];
int matchcount = 0;
int lens, lenp;

int main() {
	FILE* fp;

	fp = fopen("string.txt", "r");
	if (!fp) {
		printf("The string file does not exist.\n");
		exit(-1);
	}
	//error1 : string file does not exist.
	fgets(str, MAX_STR, fp);
	fclose(fp);

	fp = fopen("pattern.txt", "r");
	if (!fp) {
		printf("The pattern file does not exist.\n");
		exit(-1);
	}
	//error2: pattern file does not exist.
	fgets(pat, MAX_PAT, fp);
	fclose(fp);
	
	lens = strlen(str), lenp = strlen(pat);
	str[--lens] = '\0';
	pat[--lenp] = '\0';
	failure(pat);
	kmpmatch(str, pat);

	fp = fopen("result_kmp.txt", "w");
	fprintf(fp, "%d\n", matchcount);
	for (int i = 0; i < matchcount; i++)
		fprintf(fp, "%d ", matchedindex[i]);
	printf("The result was stored in 'result_kmp.txt'\n");
	fclose(fp);
	return 0;

}

void failure(char* pat) {
	int i = 0, j = 0;
	fail[0] = -1;
	for (j = 1; j < lenp; j++) {
		i = fail[j - 1];
		while(pat[i + 1] != pat[j] && i >= 0)
			i = fail[i];
		if (pat[i + 1] == pat[j])
			fail[j] = i + 1;
		else
			fail[j] = -1;
	}
}

void kmpmatch(char* str, char* pat) {
	int i = 0, j = 0;
	int temp = 0;


	for (; i < lens; ) {
		if (str[i] == pat[j]) {
			j++;
			if (j < lenp)
				i++;
		}
		else if (str[i] != pat[j] && j == 0) {
			i++;
		}
		else {
			j = fail[j - 1] + 1;
		}
			
		if (j == lenp) {
			matchedindex[matchcount++] = i - lenp + 1;
			j = fail[j - 2] + 1;
		}
		/*Although the pattern has been matched, this will process as if it is mismatched 
		on the last character of the pattern. Because we need O(n+m) time complexity */
	}

	
}
