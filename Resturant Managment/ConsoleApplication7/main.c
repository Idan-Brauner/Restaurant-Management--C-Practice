#include "Header.h"

void main()
{
	int i, was_a_press = 0, t_number, I_quantity, t_num;		 // boolean flags for if was a pressed and varibles
	char press, choice;
	char str[50];
	product *p = NULL;			 //instizle the Product struct
	table arr[T];
	for (i = 0; i < T; i++)		//instizle the table struct
	{
		arr[i].check = 0;
		arr[i].dish = NULL;
	}
	FILE *in;
	if (!(in = fopen("Instructions.txt", "rt")))				/*open for read and error check*/
		Error_Msg("The input file is wrong");

	check_emp(in);	//function that check after the program read the file if it's empty of contant.
	printf("Welcome To the Resturant Menu Program\n\n1 - Creating dishes that will be avalibl to use from the file 'Manot'.");
	printf("\n2 - Add inventory to an existing dish in the kitchen.");
	printf("\n3 - Ordering dishes to table.");
	printf("\n4 - Cancel item order.");
	printf("\n5 - Closing a table.\n\n");

	while (fscanf(in, "  %c", &choice) == 1)  // keep getting inputs until the Instructions file reach to the end 
	{

		printf("please enter 0 to start");
		printf("\nWaiting for your press please: ");
		scanf(" %c", &press);

		while (press != '0')	//if input is invalid get a valid input
		{
			printf("wrong input, please try asgain ");
			scanf(" %c", &press);
		}
		if (press == '0')
		{
			was_a_press = 1;			// indicate the input file order in the struct(which means that the program have to free the memory in the end).
			printf("\nstarting function %c\n\n",choice);

			if (choice == '1')		//1
				p = CreateProdact(p);
			else
				if (choice == '2')		//2
				{
					fscanf(in, "%s %d", str, &I_quantity);
					AddItems(p, str, I_quantity);
				}
				else
					if (choice == '3')		//3
					{
						fscanf(in, " %d %s %d", &t_num, str, &I_quantity);
						OrderItem(t_num, str, I_quantity, &arr, p);
					}
					else
						if (choice == '4')		//4
						{
							fscanf(in, " %d %s %d", &t_num, str, &I_quantity);
							RemoveItem(t_num, str, I_quantity, &arr, p);
						}
						else
							if (choice == '5')		//5
							{
								fscanf(in, " %d", &t_num);
								RemoveTable(&arr, t_num);
							}
							else
								printf("\nwrong function scanf from the 'Instruction' file\n"); //massage for entering char that is not 1-5.
		}
	}

	printf("\nYou reach the end of the file\n"); //massage for reaching the end of the file.

	if (was_a_press == 1)					// if a press was free the linked list in the kitchen  
		DeleteList(p);

	printf("\nBye!\n");
	fclose(in);		//close the instruction file
}