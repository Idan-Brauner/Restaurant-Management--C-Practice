#pragma once
#ifndef Header
#define Header
#include <stdio.h>
#include <stdlib.h>

#define T 15

//declaration of structure
typedef struct product
{
	char *ProductName;
	int price;
	int quantity;
	char premium;

	struct product* next;
}product;

//declaration of structure
typedef struct table
{
	product* dish;
	float check;

}table;


//declaration of functions
void check_emp(FILE * in);
void Error_Msg(char* str);
int stringcomp_check(product* head, char *str1);
product* CreateProdact(product *p);
void DeleteList(product* head);
void AddItems(product* head, char *name, int quantity);
void OrderItem(int num_table, char *name, int q, table *head, product *p);
void RemoveItem(int num_table, char *name, int q, table *head, product *p);
void RemoveTable(table *head, int num_table);
void PrintList(product *temp);

#endif
