//CLA: ./find -p apple
//INPUT: I like different types of fruit, especially apple and orange!
//OUTPUT: I like dif...apple...ange!
//CLA: ./find -p apple
//INPUT: I like different types of fruit, especially apple
//OUTPUT: I like dif...apple
//CLA: ./find -p apple
//INPUT: I like apple
//OUTPUT: I like apple
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>



char* strdup (const char* s)
{
  size_t slen = strlen(s);
  char* result = malloc(slen + 1);
  if(result == NULL)
  {
    return NULL;
  }

  memcpy(result, s, slen+1);
  return result;
}

void swap(char* arr[], int i, int j)
{
	void* temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

char *igncstrstr(const char *haystack, const char *needle) {
    const char *h, *n;
    for (; *haystack; ++haystack) {
        h = haystack;
        n = needle;
        while (*h && *n && (tolower((unsigned char)*h) == tolower((unsigned char)*n))) {
            ++h;
            ++n;
        }
        if (!*n) {
            return (char *) haystack;
        }
    }
    return NULL;
}
char *strstr_fully_matched(char *haystack, char *needle) {
	//needle = "apple"
  char *rv;
  char padded_needle[strlen(needle) + 3];
  padded_needle[0] = ' ';
  strcpy(padded_needle + 1, needle);
  padded_needle[strlen(needle) + 1] = ' ';
  padded_needle[strlen(needle) + 2] = '\0';//" apple "
  if (!strncmp(haystack, padded_needle + 1, strlen(needle) + 1)) {
    return haystack; // needle is at the beginning
  }
  if ((rv = strstr(haystack, padded_needle)) != NULL) {
    return rv + 1; // needle is at the middle.
  }
  padded_needle[strlen(needle) + 1] = '\0';
  if ((rv = strstr(haystack, padded_needle)) != NULL &&
      rv[strlen(padded_needle)] == '\0') {
    return rv + 1; // needle is at the end.
  }
  return NULL;
}

void book_s_qsort(char*v[], int left, int right)

{
  int i, last;
  if(left >= right)
    return;
  swap(v, left, left + (right-left)/2);
  last = left;
  for(i = left+1; i <= right;i++)
    if(strcmp(v[i],v[left]) < 0){
      swap(v, ++last, i);
	}
  swap(v, left, last);
  book_s_qsort(v, left, last-1);
  book_s_qsort(v, last+1, right);
}

void error(char* message)
{
	printf("%s\n", message);
}

char* lineptr[1000];

char* strstr_updated(char* haystack, char* needle, int match)
{
	if(match)
		return strstr_fully_matched(haystack, needle);
	else
		return strstr(haystack, needle);
}

int findIndexLocation(char *haystack, char *needle, int match)
{
	if (match)
	{
		char *start = strstr_fully_matched(haystack, needle); // Find the start of the substring

		  if (start == NULL)
		  {
			 // If the substring isn't found, return -1
			 return -1;
		  }

		  return (int)(strlen(haystack) - strlen(start));
	}


    char *start = strstr(haystack, needle); // Find the start of the substring

    if (start == NULL) // If the substring isn't found, return -1
        return -1;

    return (int)(strlen(haystack) - strlen(start)); // Return the index of the substring
}

char* insert_string(char* haystack, char* needle) {
    char* result = malloc(strlen(haystack) + strlen(needle) + 14); // Allocate memory for the result string
    int first_ellipsis_pos = 10; // Set the position of the first set of ellipses to 10
    int needle_pos = -1; // Initialize the position of the needle to -1
    int haystack_len = strlen(haystack);

    // Find the position of the needle in the haystack string
    char* match = strstr(haystack, needle);

    if (match != NULL) {
        needle_pos = match - haystack;
    }

    // Determine if the first set of ellipses should be added
    if (needle_pos >= 0 && needle_pos >= first_ellipsis_pos) {
        first_ellipsis_pos = needle_pos + 3 + strlen(needle); // Set the position of the first set of ellipses to 3 characters after the needle
    }

    // Add the first set of ellipses to the result string if it's not overlapping the first 10 characters
    if (first_ellipsis_pos > 10) {
        strncat(result, haystack, first_ellipsis_pos);
        strcat(result, "...");
    }
    else {
        strncat(result, haystack, first_ellipsis_pos);
    }

    // Add the needle and the second set of ellipses to the result string if the needle was found in the haystack string
    if (needle_pos >= 0) {
        if (needle_pos + strlen(needle) >= haystack_len - 5) {
            strncat(result, haystack + first_ellipsis_pos, needle_pos - first_ellipsis_pos + 3 + strlen(needle));
            strncat(result, needle, strlen(needle));
            strncat(result, haystack + haystack_len - 5, 5);
        }
        else {
            strncat(result, haystack + first_ellipsis_pos, needle_pos - first_ellipsis_pos + 3);
            strncat(result, needle, strlen(needle));
            strcat(result, "...");
            strncat(result, haystack + haystack_len - 5, 5);
        }
    }
    // If the needle was not found in the haystack string, just add the second set of ellipses and the last 5 characters of the haystack string
    else {
        if (haystack_len > 15) {
            strncat(result, haystack + first_ellipsis_pos, haystack_len - first_ellipsis_pos - 5);
            strcat(result, "...");
            strncat(result, haystack + haystack_len - 5, 5);
        }
        else {
            strncat(result, haystack + first_ellipsis_pos, haystack_len - first_ellipsis_pos);
        }
    }

    return result;
}


int main(int argc, char* argv[])
{
	int except = 0, number = 0, sort = 0, reverse = 0, match = 0, caseIgnore = 0, indexLocation = 0, partialPrint = 0;
	if(argc < 2){
		error("fatal error: too few arguments");
		return 1;
	}
	int i = 1;
	while(argc != 2){
		char* current_arg = argv[i++];
		if(current_arg[0] != '-'){
			error("fatal error: illegal CLAs");
			return 2;
		}
		while(*++current_arg){
			switch(*current_arg){
				case 'x': case 'X':
				except = 1;
				break;
				case 'n': case 'N':
				number = 1;
				break;
				case 's': case 'S':
				sort = 1;
				break;
				case 'r': case 'R':
				reverse = 1;
				break;
				case 'm': case 'M':
				match = 1;
				break;
				case 'c': case 'C':
				caseIgnore = 1;
				break;
				case 'f': case 'F':
				indexLocation = 1;
				break;
				case 'p': case'P':
				partialPrint = 1;
				break;


				default:
				error("fatal error: illegal option entered");
				return 3;
			}
		}argc--;
	}

	char* pattern = argv[i];
	printf("pattern is %s, n = %d, s = %d, r = %d, m = %d, x = %d, c = %d, f = %d\n p = %d", pattern, number,
						sort, reverse, match, except, caseIgnore, indexLocation, partialPrint);
	printf("Entries: \n");

	if(reverse && sort)
	{
		error("fatal error: can't use -r and -s in the same execution");
		return 4;

	}

	if(except && indexLocation)
	{
		error("fatal error: can't use -x and -f in the same execution");
		return 5;
	}

	if (except && partialPrint)
	{
		error("fatal error: can't use -x and -p in the same execution");
		return 6;
	}
	//input stream read operation...
	char line[1000];
	i = 0;
	while (fgets(line, 1000, stdin)) {
		if(line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';//drop the new line

		lineptr[i++] = strdup(line);//malloc to allocate space in heap and strcpy to copy line to heap
	}//i represents the no of sentences input by the user

	printf("\nMatches: (if any)\n\n");
	if(!sort && !reverse && !caseIgnore && !indexLocation)
	{
		for(int j = 0; j < i; j++)
		{

			char* result = strstr_updated(lineptr[j], pattern, match);
			char* line_no = (char*) malloc(10);
			sprintf(line_no, "%d. ", (j+1));
			//if pattern is found and -x doesn't exist
			//or if pattern is missing and -x exists
			//then print the line in the output
			if((result && !except) || (!result && except))
				printf("%s%s\n", number? line_no:"", lineptr[j]);
		}

	}else if(sort)
	{
		book_s_qsort(lineptr, 0, i - 1);

		for(int j = 0; j < i; j++){

			if (caseIgnore)
			{
				char* result = igncstrstr(lineptr[j], pattern);
				char* line_no = (char*) malloc(10);
				sprintf(line_no, "%d. ", (j+1));

				if((result && !except) || (!result && except))
				{
					printf("%s%s\n", number? line_no:"", lineptr[j]);
				}

				continue;
			}
			char* result = strstr_updated(lineptr[j], pattern, match);
			char* line_no = (char*) malloc(10);
			sprintf(line_no, "%d. ", (j+1));
			if((result && !except) || (!result && except))
				printf("%s%s\n", number? line_no:"", lineptr[j]);

		}
	}

	else if(reverse)
	{
		int z = 0;
		int entries = 0;
		char* allMatches[1000];

		for(int j = 0; j < i; j++)
		{
			if (caseIgnore)
			{
				char* result = igncstrstr(lineptr[j], pattern);
				char* line_no = (char*) malloc(10);
				sprintf(line_no, "%d. ", (j+1));

				if((result && !except) || (!result && except))
				{
					printf("%s%s\n", number? line_no:"", lineptr[j]);
				}

				if ((result && !except) || (!result && except)) //stores current match in an array
				{
					allMatches[z] = lineptr[j];
					z++;
				}


				continue;
			}

			char* result = strstr_updated(lineptr[j], pattern, match);
			char* line_no = (char*) malloc(10);
			sprintf(line_no, "%d. ", (j+1));

			if ((result && !except) || (!result && except)) //stores current match in an array
			{
				allMatches[z] = lineptr[j];
				z++;
			}


		}
		z--;
		while(z != -1)
			{
				char* line_no = (char*) malloc(10);
				sprintf(line_no, "%d. ", (z));
				printf("%s%s\n", number? line_no:"", allMatches[z]);
				z--;
			}

	}

	else if(indexLocation)
	{

		for(int j = 0; j < i; j++)
		{
			if (caseIgnore)
			{
				char* result = igncstrstr(lineptr[j], pattern);
				char* line_no = (char*) malloc(10);
				sprintf(line_no, "%d. ", (j+1));
				int index = findIndexLocation(lineptr[j], pattern, match);

				if(result)
				{
					printf("%s@:%d %s\n", number? line_no:"", index, lineptr[j]);
				}

			continue;
			}


			char* result = strstr_updated(lineptr[j], pattern, match);
			char* line_no = (char*) malloc(10);
			sprintf(line_no, "%d. ", (j+1));
			int index = findIndexLocation(lineptr[j], pattern, match);

			if(result)
			{
				printf("%s@:%d %s\n", number? line_no:"", index, lineptr[j]);
			}

		}
	}

	else if(caseIgnore)
	{
		for(int j = 0; j < i; j++)
		{

			char* result = igncstrstr(lineptr[j], pattern);
			char* line_no = (char*) malloc(10);
			sprintf(line_no, "%d. ", (j+1));
			if((result && !except) || (!result && except))
				printf("%s%s\n", number? line_no:"", lineptr[j]);
		}
	}
	else if(partialPrint)
	{
		for(int j = 0; j < i; j++)
		{

			char* result = strstr_updated(lineptr[j], pattern, match);
			char* line_no = (char*) malloc(10);


			sprintf(line_no, "%d. ", (j+1));
			//if pattern is found and -x doesn't exist
			//or if pattern is missing and -x exists
			//then print the line in the output
			if(((result && !except) || (!result && except)) &&   )
				printf("%s%s\n", number? line_no:"", lineptr[j]);
		}

	}



	return 0;//no error occured!
}
