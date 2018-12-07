#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "reg_alloc.h"
#include "list.h"

int RegAlloc_Allocate(FILE *fp_in, FILE *fp_out, FILE *fp_report, int regNum)
{
	char line[50];
    int line_count = 0;
	int regUsed = 0;

    while(NULL != fgets(line, 50, fp_in))
    {
		char line_out[100];

        line_count++;

		fprintf(fp_report, "%s", line);
        
        char *op_code = strtok(line, " ");

        if (strcmp(op_code, OP_CODE) == 0)
        {
            char *var;
			char temp[50];
			int reg_pos = 0;

			strcpy(line_out, op_code);

			while ((var = strtok(NULL, ", \n")) != NULL)
			{
				int regId;
				reg_pos++;

				if (regUsed < regNum)
				{
				    varList_t *cursor;

					if ( (cursor = SymTable_getNode(var)) != NULL)
					{
						fprintf(fp_report, "variable %s is already in register r%d\n", var, cursor->regName);
						regId = SymTable_getRegNum(var);
						SymTable_removeNode(var);
					}
					else
					{
						regUsed++;
						regId = regUsed;
						fprintf(fp_report, "variable %s is added to register r%d\n", var, regId);					
					}
					
					SymTable_createVar(var, regId);

					if (reg_pos == 3)
					{
						sprintf(temp, " r%d;\n", regId);
					}
					else
					{
						sprintf(temp, " r%d,", regId);
					}
					
					strcat(line_out, temp);					
				}
				else
				{
					varList_t *cursor;

					if ( (cursor = SymTable_getNode(var)) != NULL)
					{
						regId = SymTable_getRegNum(var);
						SymTable_removeNode(var);
						SymTable_createVar(var, regId);

						fprintf(fp_report, "variable %s is already in register r%d\n", var, cursor->regName);

						if (reg_pos == 3)
						{
							sprintf(temp, " r%d;\n", regId);
						}
						else
						{
							sprintf(temp, " r%d,", regId);
						}
						
						strcat(line_out, temp);	
							
					}
					else
					{
						fprintf(fp_report, "Spill variable %s in register r%d. ", pHead->var_name, pHead->regName);
						fprintf(fp_report, "Assign register r%d to variable %s\n", pHead->regName, var);
						
						fprintf(fp_out, "store r%d, @%s\n", pHead->regName, pHead->var_name);

						regId = SymTable_getRegNum(pHead->var_name);
						SymTable_removeNode(pHead->var_name);
						SymTable_createVar(var, regId);

						if (reg_pos == 3)
						{
							sprintf(temp, " r%d;\n", regId);
						}
						else
						{
							fprintf(fp_out, "load @%s, r%d;\n", var, regId);
							sprintf(temp, " r%d,", regId);
						}
						
						strcat(line_out, temp);	
					}
				}
			}

			fprintf(fp_out, line_out, "");
        }
        else
        {
            printf("Invalid op code %s at line %d!", op_code, line_count);
            exit(EXIT_FAILURE);
        }

		fprintf(fp_report, "\n");
    }

    if ( fseek(fp_in, 0L, SEEK_SET) != 0 )
    {
        printf("Error setting file pointer to start\n");
        exit(EXIT_FAILURE);
    }
}

int main (int argc, char *argv[])
{
	if (argc != CMD_ARG_LEN)
	{
		printf("Invalid input parameters. Exiting!\n");
		exit(EXIT_FAILURE);
	}

	FILE *fp_in = fopen(argv[1], "r");
    FILE *fp_out = fopen("output.txt", "w");
	FILE *fp_report = fopen("btm_up_reg_alloc_report.txt", "w");

	if ((fp_in == NULL) || (fp_out == NULL) || (fp_report == NULL))
	{
		printf("Error: couldn't open file\n");
		exit(EXIT_FAILURE);
	}

	int numReg = strtol(argv[2], NULL, 10);

	RegAlloc_Allocate(fp_in, fp_out, fp_report, numReg);


	fclose(fp_in);
    fclose(fp_out);
	fclose(fp_report);

	SymTable_freeList();

    exit(EXIT_SUCCESS);
}
