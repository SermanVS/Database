#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <list>
using namespace std;

struct Card {
	int index;
	char* Name;
	char* LastName;
	int age;

	enum Department {
		DEPT_PROGRAMMERS = 0,
		DEPT_MANAGEMENT = 1,
		DEPT_SHIPPING = 3 
	};

	struct ProgTask {
		char* Project;
		char* CPU;
		int Memory;
		ProgTask();
		ProgTask(char*, char*, int);
	};

	struct ManagerTask {
		char* Project;
		char* Customer;
		int ProgrammersNum;
		ManagerTask();
		ManagerTask(char*, char*, int);
	};

	struct ShipTask {
		char* Address;
		char* Customer;
		int Weight;
		enum Transport {
			TRANSP_TRAIN = 0,
			TRANSP_AUTO = 1,
			TRANSP_AERO = 2,
			TRANSP_SHIP = 3
		};
		Transport tr_type;
		ShipTask();
		ShipTask(char*, char*, int, char*);
	};
	Department dept_type;
	union {
		ProgTask p_task;
		ManagerTask m_task;
		ShipTask s_task;
	};
	Card();
	Card(int index, char* _Name, char* _LastName, int _age, char* _dept_type, char* _project, char* _spec1, int _spec2);
	Card(int index, char* _Name, char* _LastName, int _age, char* _dept_type, char* _address, char* _customer, int _weight, char* _trans);
};

Card input();
void print(Card card);
void print1(list<Card> database1);
void print_db(Card card, FILE* f);
void print_db1(list<Card> database1);
void remove(list<Card> &db1, int num);
list<Card> read_from_file();
list<Card> read_from_file1();
Card parse(char* str);
char* parse1(char* str);