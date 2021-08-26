#include "Header.h"

product* CreateProdact(product *head) //this function create linked list for the kitchen(product struct) from the Manot file
{
	product *temp;
	temp = head;
	char str[255];					//create temp string for the name of the products
	int g1, g2;						//varible for garbage
	char g3;
	FILE *in;
	if (!(in = fopen("Manot.txt", "rt")))				/*open for read and error check*/
		Error_Msg("The input file is wrong");
	check_emp(in);	//function that check after the program read the file if it's empty of contant.

	while (fscanf(in, " %s", str) == 1)		//keep scannig until the there is noting to scan from the file
	{
		if (stringcomp_check(temp, str) == 1)
		{
			printf("\nthe product %s already in the kitchan!\n", str);
			fscanf(in, "%d %d %c", &g1, &g2, &g3); //every fscanf is countine in the file so have to scan garbage to contine to the next dish
		}
		else
		{
			temp = (product*)malloc(sizeof(product)); //creates a dynamic allocation
			if (temp == NULL)
			{
				DeleteList(head);
				Error_Msg("ERROR");
			}
			temp->ProductName = (char*)malloc(sizeof(char)*strlen(str) + 1); //creates a dynamic allocation in the size of the product name +1 for \0
			if (temp->ProductName == NULL)
			{
				Error_Msg("ERROR");
			}
			strcpy(temp->ProductName, str);
			fscanf(in, "%d %d %c", &temp->quantity, &temp->price, &temp->premium);
			if (((temp->price) <= 0) || ((temp->quantity) <= 0) || (((temp->premium) != 'N') && ((temp->premium) != 'Y')))
			{
				printf("\nwrong input in the manot file\n");
				free(temp->ProductName);
				free(temp);
			}
			else
				if (head == NULL)	//checking if is the first linked list
				{
					temp->next = head;
					head = temp;
				}
				else
				{
					temp->next = head;
					head = temp;
				}
		}
	}
	fclose(in);	//close the Manot file
	return head;//return the linked list to the main
}

void AddItems(product *head, char *name, int quantity)// this function add quantity to the dish in the file to the same dish in the kitchen
{
	int flag = 0;
	if (quantity <= 0) 
	{
		printf("\nquantity must be positive.\n");
		return;
	}
	while (head != NULL) 
	{
		if (strcmp(head->ProductName, name) == 0) //keep checking if found similar name in the file and in the product list
		{
				head->quantity = head->quantity + quantity;
				return; //return when found the right dish
		}
		head = head->next;
	}
	printf("\n There is no dish with this name"); //show error if he scan all the dishes in the kitchen and didn't find any
}

void OrderItem(int num_table, char *name, int q, table *head, product *p) //this function create linked list for specific table in the restaurant
{
	int flag1 = 0, flag2 = 0, i = 0;
	product *temp, *temp2;
	temp = p;
	temp2 = head[num_table - 1].dish; 
	if (num_table > T)
	{
		printf("there is not enough tables");
		return;
	}
	if (q <= 0)
	{
		printf("\nquantity must be positive number.\n");
		return;
	}

	else
	{

		while (temp != NULL && flag1 != 1)
		{
			if (strcmp(name, temp->ProductName) == 0)
			{
				flag1 = 1;
				if (stringcomp_check(temp2, name) == 1)
				{
					printf("\nThe dish %s is already in the Table!\n", name);
					return;
				}
				else
				{
					temp->quantity = temp->quantity - q;
					if (temp->quantity <= 0) //check if the quantity the person order has enough stock in the kitchen 
					{
						printf("\nThe stock from this dish is over for today");
						return;
					}
					if ((temp2 = (product*)malloc(sizeof(product))) == NULL)
					{
						DeleteList(p);
						Error_Msg("ERROR");
					}
					temp2->next = NULL;
					temp2->premium = temp->premium;
					temp2->ProductName = (char*)malloc((strlen(temp->ProductName) + 1) * sizeof(char));
					if (temp2->ProductName == NULL)
					{
						Error_Msg("ERROR");
					}
					strcpy(temp2->ProductName, temp->ProductName);
					temp2->price = temp->price;
					temp2->quantity = q;
					if (head[num_table - 1].dish == NULL) //check if it the first dish to enter to the linked list in the table
					{
						temp2->next = NULL;
						head[num_table - 1].dish = temp2; //update the array linked list in the table
					}
					else
					{
						temp2->next = head[num_table - 1].dish;
						head[num_table - 1].dish = temp2; //update the array linked list in the table
					}
					head[num_table - 1].check = head[num_table - 1].check + (temp2->price)*q; //update the the final check in the table
				}
			}
			p = temp;
			temp = temp->next;
		}
		if (flag1 == 0)
		{
			printf("there is no dish exsit in the kitchen");
			return;
		}
	}
}

void RemoveItem(int num_table, char *name, int q, table *head, product *p) //this funcion remove dish from specific table that it get from the instruction file and update him in the array tables
{
	int flag1 = 0, flag2 = 0, count = 0;
	product *temp1, *temp2, *temp3;
	temp3 = p;
	temp2 = head[num_table - 1].dish;
	if (num_table >= 1 && num_table <= T)
	{
		if (head[num_table - 1].dish == NULL)
		{
			printf("this table has no orders exist");
			return;
		}
	}
	else
	{
		printf("this table doesnt exist");
		return;
	}
	if (q <= 0)
	{
		printf("\nquantity must be positive number.\n");
		return;
	}

	else
	{
		while (temp3 != NULL && flag1 != 1)	
		{
			if (strcmp(name, temp3->ProductName) == 0)	//check if the dish from the file is in the kitchen
				flag1 = 1;
			else
			{
				temp3 = temp3->next;
			}
		}
		if (flag1 == 0)
		{
			printf("the dish is not exist in the system");
			return;
		}
		if (stringcomp_check(temp2, name) == 0) //check if the dish is in the table already
		{
			printf("the dish is not exist in the table");
			return;
		}
		while (strcmp(temp2->ProductName, name) == 0) //this loop give us the location of the file to know if needed to remove the first or the mid/end linked list
		{
			count++;
			temp2 = temp2->next;
		}
		temp2 = head[num_table - 1].dish; //make temp2 to the "prev"
		temp1 = temp2->next; //make temp1 the "next"
		if (count == 1) //check if needed to remove the first or the mid/end linked list
		{
			if (temp2->quantity < q) //check if the quantity that the person order is more then actually in the table
			{
				printf("The quantity you want to cancel is bigger then your order");
				return;
			}
			else
			{
				head[num_table - 1].check = head[num_table - 1].check - (temp2->price)*q;
				temp2->quantity = temp2->quantity - q;
				if (temp2->quantity == 0) //check if needed to remove the linked list or just decrease the quantity
				{
					temp3 = temp2;
					temp2 = temp2->next;
					free(temp3->ProductName);
					free(temp3);
					head[num_table - 1].dish = temp2;
					return;
				}
				else
				{
					head[num_table - 1].dish = temp2;
					return;
				}
			}
		}

		else
		{
			while (temp1 != NULL && flag2 != 1)
			{
				if (strcmp(temp1->ProductName, name) == 0)
				{
					flag2 = 1;
					if (temp1->quantity < q) //check if the quantity that the person order is more then actually in the table
					{
						printf("The quantity you want to cancel is bigger then your order");
						return;
					}
					else
					{
						head[num_table - 1].check = head[num_table - 1].check - (temp1->price)*q;
						temp1->quantity = temp1->quantity - q;
						if (temp1->quantity == 0)//check if needed to remove the linked list or just decrease the quantity
						{
							temp2->next = temp1->next;
							free(temp1->ProductName);
							free(temp1);
							return;
						}
						else
						{
							head[num_table - 1].dish = temp2;
							return;
						}
					}
				}
				temp2 = temp2->next;
				temp1 = temp1->next;
			}
		}
	}
}


void RemoveTable(table *head, int num_table)
{
	int flag = 0;
	product *temp, *temp2;
	temp = head[num_table - 1].dish;
	temp2 = head[num_table - 1].dish;
	if (num_table < 1 && num_table > T)
	{
		printf("\nThis table not exist.\n");
		return;
	}

	while (temp2 != NULL && flag != 1)
	{
		if (temp2->premium == 'Y')
			flag = 1;
		else
			temp2 = temp2->next;
	}
	if (flag == 1) //check if one of the dishes is a premium, which means that the table is a premium one
	{
		head[num_table - 1].check = head[num_table - 1].check + head[num_table - 1].check*0.2; //update the bill by adding 20% to it
		printf("\nThe bill for 'Premium' table number %d is %.2f", num_table, head[num_table - 1].check);
		PrintList(temp); 
	}
	else
	{
		printf("\nThe bill for non 'Premium' table number %d is %.2f", num_table, head[num_table - 1].check);
		PrintList(temp); 
	}

}

void PrintList(product *temp) //this function print and free each dish that the person order to the table.
{
	product *dish;
	int i = 1;
	printf("\nTable Details:");
	while (temp != NULL)
	{
		printf("\n%d.%s %d %d %c", i, temp->ProductName, temp->quantity, temp->price, temp->premium);
		i++;
		dish = temp;
		temp = temp->next;
		free(dish->ProductName);
		free(dish);
	}
	printf("\n");

}

void check_emp(FILE * in)		//this function check if the file is empty and print proper massage
{
	fseek(in, 0, SEEK_END);
	if (ftell(in) == 0)
	{
		printf("\nthe input file is empty\n");
		exit(1);
	}
	else
		fseek(in, 0, SEEK_SET);
}

void Error_Msg(char* str)	//this function print error message and exit the program
{
	printf("\n%s", str);
	exit(1);
}

int stringcomp_check(product* head, char *str1)	//this function check if the name of a dish is in the table and return a boolian expression
{
	{
		product* temp;
		temp = head;
		if (head != NULL)
			while (temp != NULL)
			{
				if (strcmp(temp->ProductName, str1) == 0)
					return 1;
				temp = temp->next;
			}
		return 0;
	}
}

void DeleteList(product* head) //this function free the linked list that she gets
{
	product *temp;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->ProductName);
		free(temp);
	}
}