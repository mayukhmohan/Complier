#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 
#include<fcntl.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdbool.h>

int semicolontokenizer(char*, char**);
void split_line(char *);
int tokenizer(char *,char **,char **);
void spacetokenizer(char*, char**);
bool isDelimiter(char);
bool isOperator(char);
bool isValidIdentifier(char*);
bool isKeyword(char*); 
bool isInteger(char*);
bool isFloat(char*);
char* subString(char*, int, int);
void parse(char*);
bool isSpecialDelimiter(char);
char* myspaceremover(char *, char *);




int main()
{
	FILE *fp; 
	char c; 
	char *buffer = malloc(sizeof(char) * 4096);
	fp = fopen("file.c", "r"); 
	if (fp == NULL) { printf("\nFile can't be read\n"); exit(1); } 
	int i = 0;

	while((c = fgetc(fp)) != EOF)
	{
		printf("%c",c);
		if(c == '\n')
		{
			buffer[i] = '\0';
			parse(buffer);
			//split_line(buffer);
			i = 0;
			memset(buffer, '\0', 4096*sizeof(char)); 
			continue;
		}
		buffer[i++] = c;

	}

	free(buffer);
	return 0;
}

void split_line(char *line)
{
	int execFlag;
	int i;
  	char* semicolontoken[4096];
	int token_len = semicolontokenizer(line, semicolontoken);
	for(i=0;i<token_len;i++)
	{
		char* token_1[4096]; 
		
		char* token_2[4096]; 
		
		tokenizer(semicolontoken[i], token_1, token_2); 
		
	}
}

int semicolontokenizer(char* line, char** semicolontoken)
{
	int i;
	for(i=0; i<4096; i++){
		semicolontoken[i]=strsep(&line, ";");
		if(semicolontoken[i]==NULL)
			break;
	}	
	return i;
} 

char* myspaceremover(char *str, char *parsed)
{
	int i = 0, j = 0;
	char minimal[1024];
	while (str[i] != '\0')
    {
      if (str[i] == '\t' && str[i+1] == '-') 
	  {
        minimal[j] = str[i];
        j++;
      }
	  else if(str[i] != '\t')
	  {
		minimal[j] = str[i];
        j++;
	  }
      i++;
    }
 
     minimal[j] = '\0';
	 parsed = minimal;
	 return parsed;
}

int tokenizer(char *semicolontoken,char **token_1,char **token_2) 
{ 
	int i;
	char* strpiped[4096]; 
	char *andp = strstr(semicolontoken,"&&");
	char *orp = strstr(semicolontoken,"||");
	if(orp)
	{
		for (i = 0; i < 3; i++){
			strpiped[i] = strsep(&semicolontoken, "||"); 
			if (strpiped[i] == NULL) 
				break; 
		}
		spacetokenizer(strpiped[0], token_1); 
		spacetokenizer(strpiped[2], token_2);

	}
	else if(andp)
	{
		for (i = 0; i < 3; i++)
		{
			strpiped[i] = strsep(&semicolontoken, "&&"); 
			if (strpiped[i] == NULL) 
				break; 
		}
		spacetokenizer(strpiped[0], token_1); 
		spacetokenizer(strpiped[2], token_2);
	}
	else
	{	
		spacetokenizer(semicolontoken, token_1); 
	} 
}

void spacetokenizer(char* str, char** parsed)
{ 
	int i; 
	for (i = 0; i < 4096; i++) 
	{ 
		parsed[i] = strsep(&str, " "); 
		if (parsed[i] == NULL) 
			break; 
		if (strlen(parsed[i]) == 0) 
			i--; 
	} 
}
 
bool isDelimiter(char ch) 
{ 
	if (ch == '#' || ch == ' ' || ch == ',' || ch == ';' || ch == '<' || ch == '>' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}') 
		return (true); 
	return (false); 
} 

bool isSpecialDelimiter(char ch) 
{ 
	if (ch == '#' || ch == '<' || ch == '>' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}') 
		return (true); 
	return (false); 
} 

bool isOperator(char ch) 
{ 
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=' || ch == '%') 
		return (true); 
	return (false); 
} 

bool isValidIdentifier(char* str) 
{ 
	if (isInteger(&str[0]) == true || isDelimiter(str[0]) == true || isOperator(str[0]) == true) 
		return (false); 
	return (true); 
} 

 
bool isKeyword(char* str) 
{ 
	if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") || 
		!strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case") || !strcmp(str, "char") || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned") || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto")) 
		return (true); 
	return (false); 
} 

bool isInteger(char* str) 
{ 
	int i, len = strlen(str); 
	if (len == 0) 
		return (false); 
	for (i = 0; i < len; i++) { 
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0)) 
			return (false); 
	} 
	return (true); 
} 
 
bool isFloat(char* str) 
{ 
	int i, len = strlen(str); 
	bool hasDecimal = false; 

	if (len == 0) 
		return (false); 
	for (i = 0; i < len; i++) { 
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0)) 
			return (false); 
		if (str[i] == '.') 
			hasDecimal = true; 
	} 
	return (hasDecimal); 
} 
 
char* subString(char* str, int left, int right) 
{ 
	int i; 
	char* subStr = (char*)malloc( 
				sizeof(char) * (right - left + 2)); 

	for (i = left; i <= right; i++) 
		subStr[i - left] = str[i]; 
	subStr[right - left + 1] = '\0'; 
	return (subStr); 
} 

void parse(char* str) 
{ 
	int left = 0, right = 0; 
	int len = strlen(str); 

	while (right <= len && left <= right) { 
		if (isDelimiter(str[right]) == false) 
			right++; 

		if (isDelimiter(str[right]) == true && left == right) { 
			if (isSpecialDelimiter(str[right]) == true)
			{
				printf("'%c' is an delimiter\n", str[right]); 
			}
			if (isOperator(str[right]) == true) 
				printf("'%c' is an operator\n", str[right]); 

			right++; 
			left = right; 
		} else if (isDelimiter(str[right]) == true && left != right 
				|| (right == len && left != right)) { 
			char* STR = subString(str, left, right - 1);
			char* subStr;
			subStr = myspaceremover(STR,subStr);


			if (isKeyword(subStr) == true) 
				printf("'%s' is a keyword\n", subStr); 

			else if (isInteger(subStr) == true) 
				printf("'%s' is an integer\n", subStr); 

			else if (isFloat(subStr) == true) 
				printf("'%s' is a float\n", subStr); 
			
			else if (isOperator(subStr[0]) == true) 
				printf("'%s' is a operator\n", subStr); 

			else if (isValidIdentifier(subStr) == true
					&& isDelimiter(str[right - 1]) == false) 
				printf("'%s' is a valid identifier\n", subStr); 

			else if (isValidIdentifier(subStr) == false
					&& isDelimiter(str[right - 1]) == false) 
				printf("'%s' is not a valid identifier\n", subStr); 
			left = right; 
		} 
	} 
	return; 
} 
