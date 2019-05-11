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
	printf("Enter a name: ");
	(void)scanf("%s", Name);
	Name = (char*)realloc(Name, sizeof(char) * (strlen(Name) + 1));
	printf("Enter a last name: ");
	(void)scanf("%s", LastName);
	LastName = (char*)realloc(LastName, sizeof(char) * (strlen(LastName) + 1));
	printf("Enter an age: ");
	(void)scanf("%d", &age);
	if (strcmp(dept_type, "Prog-s") == 0) {
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
		printf("Enter a project name: ");
		getchar();
		gets_s(project, 255);
		printf("Enter the client's first name: ");
		gets_s(spec1, 255);
		printf("Enter the number of programmers: ");
		(void)scanf("%d", &spec2);
		return Card(count++, Name, LastName, age, dept_type, project, spec1, spec2);
	}
	if (strcmp(dept_type, "Shipping") == 0) {
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
	char* c = (char*)malloc(sizeof(char) * 7);
	strcpy(c, "Sergei");
	Name = (char*)malloc(sizeof(char) * 7);
	LastName = (char*)malloc(sizeof(char) * 7);
	strcpy(Name, c);
	strcpy(LastName, c);
	age = 0;
}

Card::Card(int _index, char* _Name, char* _LastName, int _age, char* _dept_type, char* _project, char* _spec1, int _spec2) {
	index = _index;
	age = _age;
	Name = (char*)malloc(sizeof(char) * (strlen(_Name) + 1));
	strcpy(Name, _Name);
	LastName = (char*)malloc(sizeof(char) * (strlen(_LastName) + 1));
	strcpy(LastName, _LastName);
	//char* project = (char*)malloc(sizeof(char) * (strlen(_project) + 1));
	//char* spec1 = (char*)malloc(sizeof(char) * (strlen(_spec1) + 1));
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
	char prog[] = "Prog-s";
	char man[] = "Management";
	char del[] = "Shipping  ";
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
	char file_name1[] = "Support.txt";
	FILE* f;
	FILE* f1;
	if ((f = fopen(file_name, "r")) == NULL) printf("File error\n");
	if ((f1 = fopen(file_name1, "w")) == NULL) printf("File error\n");
	/*int index = 0;
	char* name = (char*)malloc(sizeof(char) * 256);
	char* lastname = (char*)malloc(sizeof(char) * 256);
	char* dept_type = (char*)malloc(sizeof(char) * 256);
	char* project = (char*)malloc(sizeof(char) * 256);
	char* customer = (char*)malloc(sizeof(char) * 256);
	char* address = (char*)malloc(sizeof(char) * 256);
	char* CPU = (char*)malloc(sizeof(char) * 256);
	char* trans = (char*)malloc(sizeof(char) * 256);
	char* spec1 = (char*)malloc(sizeof(char) * 256);
	char* spec2 = (char*)malloc(sizeof(char) * 256);
	int age = 0;
	int spec3 = 0;*/
	//int k;
	while (!feof(f)) {
		//printf("\nwe're here\n");
		fgets(str, 256, f);
		str = (char*)realloc(str, sizeof(char) * (strlen(str) + 1));
		if (isdigit(str[0])) {
			//printf("Pushed back str\n");
			str = parse1(str);
			fprintf(f1, str);
			fclose(f1);
			//db.push_back(parse(str));
		}
		str = (char*)realloc(str, sizeof(char) * 256);
		/*k = fscanf(f, "%d %s %s %d %s %s %s %d %s", &index, name, lastname, &age, dept_type, spec1, spec2, &spec3, trans);
		printf("%d\n", k);
		name = (char*)realloc(name, sizeof(char) * (strlen(name) + 1));
		lastname = (char*)realloc(lastname, sizeof(char) * (strlen(lastname) + 1));
		dept_type = (char*)realloc(dept_type, sizeof(char) * (strlen(dept_type) + 1));
		spec1 = (char*)realloc(spec1, sizeof(char) * (strlen(spec1) + 1));
		spec2 = (char*)realloc(spec2, sizeof(char) * (strlen(spec2) + 1));
		trans = (char*)realloc(trans, sizeof(char) * (strlen(trans) + 1));*/


		//if (strcmp(dept_type, "Prog-s") == 0 || strcmp(dept_type, "Management") == 0) db.push_back(Card(index, name, lastname, age, dept_type, spec1, spec2, spec3));
		//else if (strcmp(dept_type, "Shipping") == 0) db.push_back(Card(index, name, lastname, age, dept_type, spec1, spec2, spec3, trans));
	}
	//print_db1(db);
	return db;
}
char* parse1(char* str) {
	char* istr = (char*)malloc(sizeof(char) * 256);
	char* sub = (char*)malloc(sizeof(char) * 256);
	char sep[] = "|, CR";
	int i, j;
	istr = strtok(str, sep);
	while (istr != NULL) {
		printf("sub = %s\n", istr);
		istr = strtok(NULL, sep);
	}
	printf("str = %s\n", str);
	free(istr);
	free(sub);
	return str;
}

Card parse(char* str) {
	char* name = (char*)malloc(sizeof(char) * 256);
	char* lastname = (char*)malloc(sizeof(char) * 256);
	char* dept_type = (char*)malloc(sizeof(char) * 256);
	char* spec1 = (char*)malloc(sizeof(char) * 256);
	char* spec2 = (char*)malloc(sizeof(char) * 256);
	char* trans = (char*)malloc(sizeof(char) * 4);
	char* istr = (char*)malloc(sizeof(char) * 256);
	char* substr = (char*)malloc(sizeof(char) * 256);
	char* sub = (char*)malloc(sizeof(char) * 256);
	int lastspec = 0;
	int age = 0;
	int i, j;
	int k = 0;
	char sep[] = "|CR";
	istr = strtok(str, sep);

	/*while (istr != NULL) {
		for (i = j = 0; istr[i] != '\0'; i++) if (istr[i] != ' ' || (istr[i - 1] != ' ' && istr[i + 1] != ' ' && i != 0 && (int)istr[i] >= 32 && (int)istr[i] < 123)) sub[j++] = istr[i];
		sub = (char*)realloc(sub, sizeof(char) * strlen(sub) + 1);
		printf("sub = %s\n", sub);
		printf("sub strlen = %d\n", strlen(sub));
		istr = strtok(NULL, sep);
	}
	//fprintf(f, "%s", sub);
	
	while (!feof(f)) {
		(void)fscanf(f, "%s", substr);
		switch (k) {
		case 0:
			//index = atoi(substr);
			//index = 0;
			//printf("index = %d\n", count1);
			//printf("%s\n", substr);
			break;
		case 1:
			strcpy(name, substr);
			name = (char*)realloc(name, sizeof(char) * (strlen(name) + 1));
			//printf("name = %s\n", name);
			//printf("%s\n", substr);
			break;
		case 2:
			strcpy(lastname, substr);
			lastname = (char*)realloc(lastname, sizeof(char) * (strlen(lastname) + 1));
			//printf("lastname = %s\n", lastname);
			//printf("%s\n", substr);
			break;
		case 3:
			age = atoi(substr);
			//age = 0;
			//printf("age = %d\n", age);
			//printf("%s\n", substr);
			break;
		case 4:
			strcpy(dept_type, substr);
			dept_type = (char*)realloc(dept_type, sizeof(char) * (strlen(dept_type) + 1));
			//printf("dept_type = %s\n", dept_type);
			//printf("%s\n", substr);
			break;
		case 5:
			strcpy(spec1, substr);
			spec1 = (char*)realloc(spec1, sizeof(char) * (strlen(spec1) + 1));
			//printf("spec1 = %s\n", spec1);
			//printf("%s\n", substr);
			break;
		case 6:
			strcpy(spec2, substr);
			spec2 = (char*)realloc(spec2, sizeof(char) * (strlen(spec2) + 1));
			//printf("spec2 = %s\n", spec2);
			//printf("%s\n", substr);
			break;
		case 7:
			lastspec = atoi(substr);
			//lastspec = 0;
			//printf("lastspec = %d\n", lastspec);
			//printf("%s\n", substr);
			break;
		case 8:
			if (strcmp(dept_type, "Shipping") == 0) {
				strcpy(trans, substr);
				trans = (char*)realloc(trans, sizeof(char) * (strlen(trans) + 1));
				//printf("trans = %s\n", trans);
				//printf("%s\n", substr);
			}
			break;
		}
		k++;
	}*/
	static int count1 = 0;

	Card card;


	//TODO
	//TEST STRINGS FOR LENGTH AND COMPARE WITH ACTUAL LENGTH. DONE
	//SEE IF IT'LL WORK WITH PARSE1
	//READ CODE AGAIN

	if (strcmp(dept_type, "Prog-s") == 0) {
		Card card = Card(count1++, name, lastname, age, dept_type, spec1, spec2, lastspec);
	}
	else if (strcmp(dept_type, "Management") == 0) {
		Card card = Card(count1++, name, lastname, age, dept_type, spec1, spec2, lastspec);
	}
	else if (strcmp(dept_type, "Shipping") == 0) {
		Card card = Card(count1++, name, lastname, age, dept_type, spec1, spec2, lastspec, trans);
	}
	else Card card = Card();
	print(card);
	free(name);
	free(lastname);
	free(dept_type);
	free(spec1);
	free(spec2);
	free(trans);
	free(istr);
	free(substr);
	return card;
}











list<Card> read_from_file1() {
	list<Card> db;
	char* name = (char*)malloc(sizeof(char) * 256);
	char* lastname = (char*)malloc(sizeof(char) * 256);
	char* dept_type = (char*)malloc(sizeof(char) * 256);
	char* spec1 = (char*)malloc(sizeof(char) * 256);
	char* spec2 = (char*)malloc(sizeof(char) * 256);
	char* trans = (char*)malloc(sizeof(char) * 4);
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
	FILE* f1;
	int index;
	int count = 0;
	if ((f = fopen(file_name, "r")) == NULL) printf("File error\n");
	if ((f1 = fopen(file_name1, "w+")) == NULL) printf("File error\n");
	while (!feof(f)) {
		fgets(str, 256, f);
		if (isdigit(str[0])) {
			istr = strtok(str, sep);
			int k = 0;
			while (istr != NULL) {
				fprintf(f1, "%s\n", istr);
				switch (k) {
				case 0:
					//index = atoi(istr);
					//index = 0;
					printf("index = %d\n", count);
					//printf("%s\n", substr);
					break;
				case 1:
					strcpy(name, istr);
					name = (char*)realloc(name, sizeof(char) * (strlen(name) + 1));
					printf("name = %s\n", name);
					//printf("%s\n", substr);
					break;
				case 2:
					strcpy(lastname, istr);
					lastname = (char*)realloc(lastname, sizeof(char) * (strlen(lastname) + 1));
					printf("lastname = %s\n", lastname);
					//printf("%s\n", substr);
					break;
				case 3:
					age = atoi(istr);
					//age = 0;
					printf("age = %d\n", age);
					//printf("%s\n", substr);
					break;
				case 4:
					strcpy(dept_type, istr);
					dept_type = (char*)realloc(dept_type, sizeof(char) * (strlen(dept_type) + 1));
					printf("dept_type = %s\n", dept_type);
					//printf("%s\n", substr);
					break;
				case 5:
					strcpy(spec1, istr);
					spec1 = (char*)realloc(spec1, sizeof(char) * (strlen(spec1) + 1));
					printf("spec1 = %s\n", spec1);
					//printf("%s\n", substr);
					break;
				case 6:
					strcpy(spec2, istr);
					spec2 = (char*)realloc(spec2, sizeof(char) * (strlen(spec2) + 1));
					printf("spec2 = %s\n", spec2);
					//printf("%s\n", substr);
					break;
				case 7:
					lastspec = atoi(istr);
					//lastspec = 0;
					printf("lastspec = %d\n", lastspec);
					//printf("%s\n", substr);
					break;
				case 8:
					if (strcmp(dept_type, "Shipping") == 0) {
						strcpy(trans, istr);
						trans = (char*)realloc(trans, sizeof(char) * (strlen(trans) + 1));
						printf("trans = %s\n", trans);
						//printf("%s\n", substr);
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
		
	}
	for (int g = 0; g < i; g++) {
		db.push_back(cards[g]);
	}
	fclose(f);
	fclose(f1);
	free(name);
	free(lastname);
	free(dept_type);
	free(spec1);
	free(spec2);
	free(trans);
	free(str);
	free(istr);
	free(sub);
	
	return db;
}
