#define _CRT_SECURE_NO_WARNINGS
#include "Database.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <list>
#include <ctype.h>

Card input() {
	static int count = 0;
	char* Name = (char*)malloc(sizeof(char) * 256);
	char* LastName = (char*)malloc(sizeof(char) * 256);
	int age;
	char* dept_type = (char*)malloc(sizeof(char) * 256);
	char* project = (char*)malloc(sizeof(char) * 256);
	char* spec1 = (char*)malloc(sizeof(char) * 255);
	int spec2;
	printf("Who do you want to add?\n");
	printf("Programmer - 'Prog-s'\n");
	printf("Manager - 'Management'\n");
	printf("Delivery man - 'Shipping'\n");
	(void)scanf("%s", dept_type);
	dept_type = (char*)realloc(dept_type, sizeof(char) * (strlen(dept_type) + 1));
	if (strcmp(dept_type, "Prog-s") == 0) {
		printf("Enter a name: ");
		(void)scanf("%s", Name);
		Name = (char*)realloc(Name, sizeof(char) * (strlen(Name) + 1));
		printf("Enter a last name: ");
		(void)scanf("%s", LastName);
		LastName = (char*)realloc(LastName, sizeof(char) * (strlen(LastName) + 1));
		printf("Enter an age: ");
		(void)scanf("%d", &age);
		printf("Enter a project code name: ");
		getchar();
		gets_s(project, 255);
		project = (char*)realloc(project, sizeof(char) * (strlen(project) + 1));
		printf("Enter a CPU name. Intel or AMD: ");
		gets_s(spec1, 255);
		spec1 = (char*)realloc(spec1, sizeof(char) * (strlen(spec1) + 1));
		printf("Enter the amount of memory: ");
		(void)scanf("%d", &spec2);
		return Card(count++, Name, LastName, age, dept_type, project, spec1, spec2);
	}
	if (strcmp(dept_type, "Management") == 0) {
		printf("Enter a name: ");
		(void)scanf("%s", Name);
		Name = (char*)realloc(Name, sizeof(char) * (strlen(Name) + 1));
		printf("Enter a last name: ");
		(void)scanf("%s", LastName);
		LastName = (char*)realloc(LastName, sizeof(char) * (strlen(LastName) + 1));
		printf("Enter an age: ");
		(void)scanf("%d", &age);
		printf("Enter a project name: ");
		getchar();
		gets_s(project, 255);
		project = (char*)realloc(project, sizeof(char) * (strlen(project) + 1));
		printf("Enter the client's first name: ");
		gets_s(spec1, 255);
		spec1 = (char*)realloc(spec1, sizeof(char) * (strlen(spec1) + 1));
		printf("Enter the number of programmers: ");
		(void)scanf("%d", &spec2);
		return Card(count++, Name, LastName, age, dept_type, project, spec1, spec2);
	}
	if (strcmp(dept_type, "Shipping") == 0) {
		printf("Enter a name: ");
		(void)scanf("%s", Name);
		Name = (char*)realloc(Name, sizeof(char) * (strlen(Name) + 1));
		printf("Enter a last name: ");
		(void)scanf("%s", LastName);
		LastName = (char*)realloc(LastName, sizeof(char) * (strlen(LastName) + 1));
		printf("Enter an age: ");
		(void)scanf("%d", &age);
		char* address = (char*)malloc(sizeof(char) * 256);
		char* customer = (char*)malloc(sizeof(char) * 256);
		int weight;
		char* trans = (char*)malloc(sizeof(char) * 256);
		printf("Enter the address with no spaces: ");
		getchar();
		gets_s(address, 256);
		address = (char*)realloc(address, sizeof(char) * (strlen(address) + 1));
		printf("Enter the client's first name: ");
		gets_s(customer, 256);
		customer = (char*)realloc(customer, sizeof(char) * (strlen(customer) + 1));
		printf("Enter the item's weight: ");
		(void)scanf("%d", &weight);
		getchar();
		printf("What delivery type? Availible: Train, Auto, Plane, Ship.\n");
		gets_s(trans, 256);
		trans = (char*)realloc(trans, sizeof(char) * (strlen(trans) + 1));
		return Card(count++, Name, LastName, age, dept_type, address, customer, weight, trans);
	}
	else return Card();
}
Card::Card() {
	Name = nullptr;
	LastName = nullptr;
	age = 0;
}

Card::Card(int _index, char* _Name, char* _LastName, int _age, char* _dept_type, char* _project, char* _spec1, int _spec2) {
	index = _index;
	age = _age;
	Name = (char*)malloc(sizeof(char) * (strlen(_Name) + 1));
	strcpy(Name, _Name);
	LastName = (char*)malloc(sizeof(char) * (strlen(_LastName) + 1));
	strcpy(LastName, _LastName);
	if (strcmp(_dept_type, "Prog-s") == 0) dept_type = DEPT_PROGRAMMERS;
	if (strcmp(_dept_type, "Management") == 0) dept_type = DEPT_MANAGEMENT;
	if (dept_type == DEPT_PROGRAMMERS) p_task = ProgTask(_project, _spec1, _spec2);
	else if (dept_type == DEPT_MANAGEMENT) m_task = ManagerTask(_project, _spec1, _spec2);

}

Card::Card(int _index, char* _Name, char* _LastName, int _age, char* _dept_type, char* _address, char* _customer, int _weight, char* _trans) : index(_index), Name(_Name), LastName(_LastName), age(_age) {
	dept_type = DEPT_SHIPPING;
	s_task = ShipTask(_address, _customer, _weight, _trans);
}

Card::ProgTask::ProgTask(char* _project, char* _cpu, int _mmr) {
	Project = (char*)malloc(sizeof(char) * (strlen(_project) + 1));
	CPU = (char*)malloc(sizeof(char) * (strlen(_cpu) + 1));
	strcpy(Project, _project);
	strcpy(CPU, _cpu);
	Memory = _mmr;
}

Card::ManagerTask::ManagerTask(char* _project, char* _cust, int _prnum) {
	Project = (char*)malloc(sizeof(char) * (strlen(_project) + 1));
	Customer = (char*)malloc(sizeof(char) * (strlen(_cust) + 1));
	strcpy(Project, _project);
	strcpy(Customer, _cust);
	ProgrammersNum = _prnum;
}

Card::ShipTask::ShipTask(char* _adr, char* _cust, int _weight, char* _trans) {
	Customer = (char*)malloc(sizeof(char) * (strlen(_cust) + 1));
	Address = (char*)malloc(sizeof(char) * (strlen(_adr) + 1));
	strcpy(Address, _adr);
	strcpy(Customer, _cust);
	Weight = _weight;
	if (_trans[0] == 'T') tr_type = TRANSP_TRAIN;
	if (_trans[0] == 'A') tr_type = TRANSP_AUTO;
	if (_trans[0] == 'P') tr_type = TRANSP_AERO;
	if (_trans[0] == 'S') tr_type = TRANSP_SHIP;
	//Because of trash that is stored with the transport type after the word itsefl, we check only the first letter.
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
	char prog[] = "   Prog-s     ";
	char man[] =  "   Management ";
	char del[] =  "   Shipping   ";
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
	char prog[] = "Prog-s";
	char man[] = "Management";
	char del[] = "Shipping  ";
	char tr[] = "Train";
	char au[] = "Auto";
	char pl[] = "Plane";
	char sh[] = "Ship";


	if (card.dept_type == card.DEPT_PROGRAMMERS) {
		fprintf(f, "%d  |%10s|%10s|%10d|%10s|", card.index, card.Name, card.LastName, card.age, prog);
		fprintf(f, "|%10s|%10s|%10d|\n", card.p_task.Project, card.p_task.CPU, card.p_task.Memory);
	}
	if (card.dept_type == card.DEPT_MANAGEMENT) {
		fprintf(f, "%d  |%10s|%10s|%10d|%10s|", card.index, card.Name, card.LastName, card.age, man);
		fprintf(f, "|%10s|%10s|%10d|\n", card.m_task.Project, card.m_task.Customer, card.m_task.ProgrammersNum);
	}
	if (card.dept_type == card.DEPT_SHIPPING) {
		fprintf(f, "%d  |%10s|%10s|%10d|%10s|", card.index, card.Name, card.LastName, card.age, del);
		fprintf(f, "|%10s|%10s|%10d|", card.s_task.Address, card.s_task.Customer, card.s_task.Weight);
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

void remove(list<Card> &db1) {
	printf("Which element would you like to remove?\n");
	int num;
	(void)scanf("%d", &num);
	list<Card>::iterator it = db1.begin();
	for (int i = 0; i < num; i++) {
		it++;
	}
	printf("Will delete this element: ");
	printf(it->Name);
	printf("\n\n");
	db1.erase(it);
}


list<Card> read_from_file1() {
	list<Card> db;
	char* str = (char*)malloc(sizeof(char) * 256);
	char file_name[] = "In.txt";
	char file_name1[] = "Support.txt";
	char* istr = (char*)malloc(sizeof(char) * 256);
	Card* cards = (Card*)malloc(sizeof(Card) * 256);
	char* sub = (char*)malloc(sizeof(char) * 256);
	char sep[] = " |CR";
	int age;
	int lastspec;
	int i = 0;
	FILE* f;
	int index;
	int count = 0;
	if ((f = fopen(file_name, "r")) == NULL) printf("File error\n");
	while (!feof(f)) {
		fgets(str, 256, f);
		char* name = (char*)malloc(sizeof(char) * 256);
		char* lastname = (char*)malloc(sizeof(char) * 256);
		char* dept_type = (char*)malloc(sizeof(char) * 256);
		char* spec1 = (char*)malloc(sizeof(char) * 256);
		char* spec2 = (char*)malloc(sizeof(char) * 256);
		char* trans = (char*)malloc(sizeof(char) * 4);
		if (isdigit(str[0])) {
			istr = strtok(str, sep);
			int k = 0;
			while (istr != NULL) {
				switch (k) {
				case 1:
					strcpy(name, istr);
					name = (char*)realloc(name, sizeof(char) * (strlen(name) + 1));
					break;
				case 2:
					strcpy(lastname, istr);
					lastname = (char*)realloc(lastname, sizeof(char) * (strlen(lastname) + 1));
					break;
				case 3:
					age = atoi(istr);
					break;
				case 4:
					strcpy(dept_type, istr);
					dept_type = (char*)realloc(dept_type, sizeof(char) * (strlen(dept_type) + 1));
					break;
				case 5:
					strcpy(spec1, istr);
					spec1 = (char*)realloc(spec1, sizeof(char) * (strlen(spec1) + 1));
					break;
				case 6:
					strcpy(spec2, istr);
					spec2 = (char*)realloc(spec2, sizeof(char) * (strlen(spec2) + 1));
					break;
				case 7:
					lastspec = atoi(istr);
					break;
				case 8:
					if (strcmp(dept_type, "Shipping") == 0) {
						strcpy(trans, istr);
						trans = (char*)realloc(trans, sizeof(char) * (strlen(trans) + 1));
					}
					break;
				}
				k++;
				istr = strtok(NULL, sep);
			}
			free(istr);
			if (strcmp(dept_type, "Prog-s") == 0) {
				cards[i++] = Card(count, name, lastname, age, dept_type, spec1, spec2, lastspec);
			}
			else if (strcmp(dept_type, "Management") == 0) {
				cards[i++] = Card(count, name, lastname, age, dept_type, spec1, spec2, lastspec);
			}
			else if (strcmp(dept_type, "Shipping") == 0) {
				cards[i++] = Card(count, name, lastname, age, dept_type, spec1, spec2, lastspec, trans);
			}
			count++;
		}
		free(dept_type);
		free(spec1);
		free(spec2);
		free(trans);
	}
	for (int g = 0; g < i; g++) {
		db.push_back(cards[g]);
	}
	fclose(f);
	free(str);
	free(istr);
	free(sub);

	return db;
}
