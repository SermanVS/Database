#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "Database.h"
#include <list>
#include "Source.h"

using namespace std;
int main() {
	std::list <Card> database1;
	LOOP:
	printf("\nWhat would like to do?\n");
	printf("Add new card - enter 'add'\n");
	printf("Remove an existing card - enter 'remove'\n");
	printf("Copy a list to a file - enter 'fprint'\n");
	printf("Pring a list on a screen - enter 'print'\n");
	printf("Read a list from a file - enter 'read'\n");
	printf("Exit - 'exit'\n");
	char* c = (char*)malloc(sizeof(char)*256);
	(void)scanf("%s", c);
	c = (char*)realloc(c, sizeof(char) * (strlen(c) + 1));
	while (strcmp(c, "exit") != 0) {
		if (strcmp(c, "add") == 0) {
			database1.push_back(input());
		}
		if (strcmp(c, "remove") == 0) {
			printf("Which element would you like to remove?\n");
			int temp;
			(void)scanf("%d", &temp);
			remove(database1, temp);
		}
		if (strcmp(c, "fprint") == 0) {
			print_db1(database1);
		}
		if (strcmp(c, "print") == 0) {
			print1(database1);
		}
		if (strcmp(c, "read") == 0) {
			database1 = read_from_file();
		}
		goto LOOP;
	}
	(void)getchar();
	return 0;
}