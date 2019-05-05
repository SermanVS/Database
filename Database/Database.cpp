#define _CRT_SECURE_NO_WARNINGS
#include "Database.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <list>
#include <ctype.h>

Card input() {
	static int count = 0;
	printf("Who do you want to add?\n");
	printf("Programmer - 'Prog'\n");
	printf("Manager - 'Management'\n");
	printf("Delivery man - 'Shipping'\n");
	char* Name = (char*)malloc(sizeof(char) * 256);
	char* LastName = (char*)malloc(sizeof(char) * 256);
	int age;
	char* dept_type = (char*)malloc(sizeof(char) * 256);
	char* project = (char*)malloc(sizeof(char) * 256);
	char* spec1 = (char*)malloc(sizeof(char) * 255);
	int spec2;
	(void)scanf("%s", dept_type);
	dept_type = (char*)realloc(dept_type, sizeof(char) * (strlen(dept_type) + 1));
	printf("Enter a name: ");
	(void)scanf("%s", Name);
	Name = (char*)realloc(Name, sizeof(char) * (strlen(Name) + 1));
	printf("Enter a last name: ");
	(void)scanf("%s", LastName);
	LastName = (char*)realloc(LastName, sizeof(char) * (strlen(LastName) + 1));
	printf("Enter an age: ");
	(void)scanf("%d", &age);
	if (strcmp(dept_type, "Prog") == 0) {
		printf("Enter a project name: ");
		(void)scanf("%s", project);
		project = (char*)realloc(project, sizeof(char) * (strlen(project) + 1));
		printf("Enter a CPU name: ");
		(void)scanf("%s", spec1);
		spec1 = (char*)realloc(spec1, sizeof(char) * (strlen(spec1) + 1));
		printf("Enter the amount of memory: ");
		(void)scanf("%d", &spec2);
		return Card(count++, Name, LastName, age, dept_type, project, spec1, spec2);
	}
	if (strcmp(dept_type, "Management") == 0) {
		printf("Enter a project name: ");
		(void)scanf("%s", project);
		printf("Enter the client's name: ");
		(void)scanf("%s", spec1);
		printf("Enter the number of programmers: ");
		(void)scanf("%d", &spec2);
		return Card(count++, Name, LastName, age, dept_type, project, spec1, spec2);
	}
	if (strcmp(dept_type, "Shipping") == 0) {
		char* address = (char*)malloc(sizeof(char) * 256);
		char* customer = (char*)malloc(sizeof(char) * 256);
		int weight;
		char* trans = (char*)malloc(sizeof(char) * 256);
		printf("Enter the address: ");
		(void)scanf("%s", address);
		address = (char*)realloc(address, sizeof(char) * (strlen(address) + 1));
		printf("Enter the client's name: ");
		(void)scanf("%s", customer);
		customer = (char*)realloc(customer, sizeof(char) * (strlen(customer) + 1));
		printf("Enter the item's weight: ");
		(void)scanf("%d", &weight);
		printf("What delivery type? Availible: Train, Auto, Plane, Ship.\n");
		(void)scanf("%s", trans);
		trans = (char*)realloc(trans, sizeof(char) * (strlen(trans) + 1));
		return Card(count++, Name, LastName, age, dept_type, address, customer, weight, trans);
	}
	else return Card();
}
Card::Card() : index(0) {
	Name = nullptr;
	LastName = nullptr;
	age = 0;
}
Card::Card(int _index, char* _Name, char* _LastName, int _age, char* _dept_type, char* _project, char* _spec1, int _spec2) : index(_index), Name(_Name), LastName(_LastName), age(_age){
	if (strcmp(_dept_type, "Prog") == 0) dept_type = DEPT_PROGRAMMERS;
	if (strcmp(_dept_type, "Management") == 0) dept_type = DEPT_MANAGEMENT;
	if (dept_type == DEPT_PROGRAMMERS) p_task = ProgTask(_project, _spec1, _spec2);
	else m_task = ManagerTask(_project, _spec1, _spec2);

}

Card::Card(int _index, char* _Name, char* _LastName, int _age, char* _dept_type, char* _address, char* _customer, int _weight, char* _trans) : index(_index), Name(_Name), LastName(_LastName), age(_age) {
	dept_type = DEPT_SHIPPING;
	s_task = ShipTask(_address, _customer, _weight, _trans);
}

Card::ProgTask::ProgTask(char* _project, char* _cpu, int _mmr) {
	Project = _project;
	CPU = _cpu;
	Memory = _mmr;
}

Card::ManagerTask::ManagerTask(char* _project, char* _cust, int _prnum) {
	Project = _project;
	Customer = _cust;
	ProgrammersNum = _prnum;
}

Card::ShipTask::ShipTask(char* _adr, char* _cust, int _weight, char* _trans) {
	Address = _adr;
	Customer = _cust;
	Weight = _weight;
	if (strcmp(_trans, "Train") == 0) tr_type = TRANSP_TRAIN;
	if (strcmp(_trans, "Auto") == 0) tr_type = TRANSP_AUTO;
	if (strcmp(_trans, "Plane") == 0) tr_type = TRANSP_AERO;
	if (strcmp(_trans, "Ship") == 0) tr_type = TRANSP_SHIP;
}
Card::ProgTask::ProgTask() {
	Project = nullptr;
	CPU = nullptr;
}
Card::ManagerTask::ManagerTask() {
	Project = nullptr;
	Customer = nullptr;
}
Card::ShipTask::ShipTask() {
	Address = nullptr;
	Customer = nullptr;
}
void print1(list<Card> database1) {
	printf("#  |%10s|%10s|%10s|%10s||%10s|%10s|%10s|%10s\n", "Name", "Last Name", "Age", "Dept P", "Project", "CPU", "Memory", " ");
	printf("   |%10s|%10s|%10s|%10s||%10s|%10s|%10s|%10s\n", " ", " ", " ", " M", "Project", "Customer", "Progers", " ");
	printf("   |%10s|%10s|%10s|%10s||%10s|%10s|%10s|%10s\n", " ", " ", " ", " S", "Address", "Customer", "Weight", "Transport");
	printf("--------------------------------------------------------------------------------------------\n");
	list<Card>::iterator it = database1.begin();
	for (it; it != database1.end();) {
		print(*it);
		advance(it, 1);
	}
}
void print(Card card) {
	char prog[] = "    Prog-s    ";
	char man[] = "    Management";
	char del[] = "    Shipping  ";
	char tr[] = "Train";
	char au[] = "Auto";
	char pl[] = "Plane";
	char sh[] = "Ship";
	if (card.dept_type == card.DEPT_PROGRAMMERS) {
		printf("%d %10s %10s %10d %10s", card.index, card.Name, card.LastName, card.age, prog);
		printf("%10s %10s %10d\n", card.p_task.Project, card.p_task.CPU, card.p_task.Memory);
	}
	if (card.dept_type == card.DEPT_MANAGEMENT) {
		printf("%d %10s %10s %10d %10s", card.index, card.Name, card.LastName, card.age, man);
		printf("%10s %10s %10d\n", card.m_task.Project, card.m_task.Customer, card.m_task.ProgrammersNum);
	}
	if (card.dept_type == card.DEPT_SHIPPING) {
		printf("%d %10s %10s %10d %10s", card.index, card.Name, card.LastName, card.age, del);
		printf("%10s %10s %10d", card.s_task.Address, card.s_task.Customer, card.s_task.Weight);
		switch (card.s_task.tr_type) {
		case 0:
			printf("%10s\n", tr);
			break;
		case 1:
			printf("%10s\n", au);
			break;
		case 2:
			printf("%10s\n", pl);
			break;
		case 3:
			printf("%10s\n", sh);
			break;
		default:
			printf("Some error\n");
			break;
		}
	}
}
void print_db1(std::list<Card> database1) {
	FILE* f;
	char file_name[] = "Out.txt";
	if ((f = fopen(file_name, "w")) == NULL) printf("File error\n");
	fprintf(f, "#  |%10s|%10s|%10s|%10s||%10s|%10s|%10s|%10s\n", "Name", "Last Name", "Age", "Dept P", "Project", "CPU", "Memory", " ");
	fprintf(f, "   |%10s|%10s|%10s|%10s||%10s|%10s|%10s|%10s\n", " ", " ", " ", " M", "Project", "Customer", "Progers", " ");
	fprintf(f, "   |%10s|%10s|%10s|%10s||%10s|%10s|%10s|%10s\n", " ", " ", " ", " S", "Address", "Customer", "Weight", "Transport");
	fprintf(f, "--------------------------------------------------------------------------------------------\n");
	list<Card>::iterator it = database1.begin();
	for (it; it != database1.end();) {
		print_db(*it, f);
		advance(it, 1);
	}
	fclose(f);
	printf("\nYour database was printed to Out.txt\n");
}
void print_db(Card card, FILE* f) {
	char prog[] = "    Prog-s    ";
	char man[] = "    Management";
	char del[] = "    Shipping  ";
	char tr[] = "Train";
	char au[] = "Auto";
	char pl[] = "Plane";
	char sh[] = "Ship";


	if (card.dept_type == card.DEPT_PROGRAMMERS) {
		fprintf(f, "%d %10s %10s %10d %10s", card.index, card.Name, card.LastName, card.age, prog);
		fprintf(f, "%10s %10s %10d\n", card.p_task.Project, card.p_task.CPU, card.p_task.Memory);
	}
	if (card.dept_type == card.DEPT_MANAGEMENT) {
		fprintf(f, "%d %10s %10s %10d %10s", card.index, card.Name, card.LastName, card.age, man);
		fprintf(f, "%10s %10s %10d\n", card.m_task.Project, card.m_task.Customer, card.m_task.ProgrammersNum);
	}
	if (card.dept_type == card.DEPT_SHIPPING) {
		fprintf(f, "%d %10s %10s %10d %10s", card.index, card.Name, card.LastName, card.age, del);
		fprintf(f, "%10s %10s %10d", card.s_task.Address, card.s_task.Customer, card.s_task.Weight);
		switch (card.s_task.tr_type) {
		case 0:
			fprintf(f, "%10s\n", tr);
			break;
		case 1:
			fprintf(f, "%10s\n", au);
			break;
		case 2:
			fprintf(f, "%10s\n", pl);
			break;
		case 3:
			fprintf(f, "%10s\n", sh);
			break;
		default:
			printf("Some error\n");
			break;
		}
	}
}

void remove(list<Card> &db1, int num) {
	list<Card>::iterator it = db1.begin();
	for (int i = 0; i < num; i++) {
		it++;
	}
	printf("Will delete this element: ");
	printf(it->Name);
	printf("\n\n");
	db1.erase(it);
}

list<Card> read_from_file() {
	list<Card> db;
	char* str = (char*)malloc(sizeof(char) * 256);
	char file_name[] = "In.txt"; 
	FILE* f;
	if ((f = fopen(file_name, "r")) == NULL) printf("File error\n");

	while (!feof(f)) {
		fgets(str, 256, f);
		str = (char*)realloc(str, sizeof(char) * (strlen(str) + 1));
		if (isdigit(str[0])) printf(str);
		str = (char*)realloc(str, sizeof(char) * 256);
	}
	return db;
}