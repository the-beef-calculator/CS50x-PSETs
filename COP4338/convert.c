#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define error(m, c) do{fprintf(stderr, "%s\n", m);exit(c);}while(0)
typedef enum{
    NONE = 0,//no flags are passed in CLAs
    CLEAR = 1,//-c
    HEX = 1<<1, //-x
    SCIENTIFIC = 1<<2,//-e
    TRUNCATED = 1<<3,//-s
}flags;


char* strip(char * input){
    char* rv = (char*)malloc(strlen(input)+1);
    int left, right;
    for(left = 0, right = strlen(input)-1;
        left < right && (input[left] == ' ' || input[right] == ' ');
        /*no update*/){
        if(input[left] == ' '){
            left++;
        }
        if(input[right] == ' '){
            right--;
        }
    }
    strncpy(rv, input + left, right-left+1);
    return rv;
}
int is_double(char*);
int is_int(char*);


int main(int argc, char* argv[]){
    flags flag = NONE;// combination of flags
    char in_fmt[4] = "txt";
    char out_fmt[4] = "csv";
    int i = 1;
    while(argc != 1){
        char* current_arg = argv[i++];
        if(current_arg[0] != '-')
            error("fatal error: illegal CLAs", 2);
        while(*++current_arg){
            switch(*current_arg){
                case 'i':
                if(strcmp(argv[i], "txt") && strcmp(argv[i], "csv"))
                    error("fatal error: illegal input format", 3);
                else if(!strcmp(argv[i], "txt"))
                    strcpy(in_fmt, "txt");
                else
                    strcpy(in_fmt, "csv");
                i++;argc--;
                break;
                case 'o':
                if(strcmp(argv[i], "txt") && strcmp(argv[i], "csv"))
                    error("fatal error: illegal output format", 4);
                else if(!strcmp(argv[i], "txt"))
                    strcpy(out_fmt, "txt");
                else
                    strcpy(out_fmt, "csv");
                i++;argc--;
                break;
                case 'c':
                flag |= CLEAR;//flag is an enum XXX0 | 0001 = XXX1
                break;
                case 'x':
                flag |= HEX;
                break;
                case 'e':
                flag |= SCIENTIFIC;
                break;
                case 's':
                flag |= TRUNCATED;
                break;
                default:
                error("fatal error: illegal option entered", 5);
            }
        }argc--;
    }

    fprintf(stderr, "Note: converting %s to %s with options: ", in_fmt, out_fmt);
    if(flag & CLEAR)
        fprintf(stderr, "-c ");
    if(flag & HEX)//HEX: 2 = 0010, flag: XX1X, HEX & flag = 0010
        fprintf(stderr, "-x ");
    if(flag & SCIENTIFIC)
        fprintf(stderr, "-e ");
    if(flag & TRUNCATED)
        fprintf(stderr, "-s ");
    fprintf(stderr, "\n");


    char line[1000];//placeholder for a line
    while(fgets(line, 1000, stdin)){
        char* delimiter = strcmp(in_fmt, "csv") == 0?",": "\t";
        char* cell;
        int ival; double dval;
        if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';//dropping the new line
        cell = strtok(line, delimiter);
        while(cell){
            if(sscanf(cell, "%d", &ival) && is_int(cell))//is_int checks the entire cell for an int
                printf("Integer cell: %d\n", ival);//use %x if -x is given by CLAs
            else if(sscanf(cell, "%lf", &dval) && is_double(cell))// && //sscanf is like java.util.scanner(String val not System.in)
                printf("Double cell: %f\n", dval);//use %.3e if -e is given by CLAs
            else
                printf("String cell: %s\n", cell);//use %.5s if -s is given by CLAs
            cell = strtok(NULL, delimiter);
        }
    }
    return 0;//no error occured!
}
int is_int(char* input){
    input = strip(input);
    //checks whether input can be a string representation of an int
    if(*input == '+' || * input == '-')
        input++;
    while(*input)
        if(!isdigit(*input++))
            return 0;
    return 1;
}
char* tolower_str(char* input){
    char* rv = strdup(input);
    int i = 0;
    while(*input)
        rv[i++] = tolower(*input++);
    return rv[i] = '\0', rv;
}
int is_double(char* input){
    //checks whether input can be a string representation of a double
    input = tolower_str(strip(input));
    if(!strcmp(input, "inf") || !strcmp(input, "nan") ||
    !strcmp(input, "-inf"))
        return 1;
    if(strchr(input, 'e') != strrchr(input, 'e'))
        return 0;//at-most one 'e' is allowed!
    if(*input == '+' || * input == '-')//parse the sign
        input++;
    while(*input && *input != '.' && *input != 'e')
        if(!isdigit(*input++))//parse the integer value
            return 0;
    if(*input++ == '.')
        while(*input && *input != 'e')
            if(!isdigit(*input++))//parse the fraction
                return 0;
    if(*input++ == 'e'){
        if(*input == '+' || * input == '-')
            input++;//parse the sign of exponent
        while(*input)
            if(!isdigit(*input++))//parse the exponent
                return 0;
    }
    return 1;
}