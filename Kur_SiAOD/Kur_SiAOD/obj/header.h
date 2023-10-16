#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <conio.h>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

#define KB_UP 72
#define KB_DOWN 80
#define KB_LEFT 75
#define KB_RIGHT 77
#define KB_ESCAPE 27
#define N 4000

struct Enterprise
{
	char name[30];
	unsigned short int dep_number;
	char job[22];
	char date[10];
};

struct spis {
	spis(Enterprise data) : data(data) { 
		next = NULL; 
	}

	Enterprise data;
	spis* next;
};

struct queue
{
	spis *head;
	spis *tail;
};

void menu(Enterprise** arr);
void print_bd(Enterprise** arr);
void read_bd(Enterprise** arr);
void HeapSort_bd(Enterprise** array_pointer);
void Create_New_Heap(Enterprise** array_pointer, Enterprise* key, int L, int R);
int Split_to_int(const char* str, char separator);
int compression(Enterprise* left_p, Enterprise* right_p);
int bin_search(Enterprise** arr, int& key);
queue create_queue(Enterprise** arr, int index, int key);
void print_queue(queue *head);