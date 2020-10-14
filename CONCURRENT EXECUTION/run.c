#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include "tranclator.h"

#define MAX_NUM_THREAD 5
#define MAX_NUM_PROGRAM 20

pthread_mutex_t mtx;

struct program_character{
	pthread_t thread_id;
	char name[20];
	char line[256];
	int situation;
	int fd;
	int thesi_pou_mpike;
	int transport;
	int down_thread;
	char name_sem[100];
	int check_type_sem;
};

struct program_character program_character[MAX_NUM_THREAD][MAX_NUM_PROGRAM];
volatile int num_of_programs[MAX_NUM_THREAD],num_input[MAX_NUM_THREAD], se_poio_thread_trexw=0;


int print_list(int num, int k){
	
	int i=0;
	
	for(i=0;i < num;i++){
		printf("name : %s, thread_id : %ld, situation : %d\n",program_character[k][i].name,program_character[k][i].thread_id,program_character[k][i].situation);
	}
	
	return 0;
}

void *tranclator(void *arg){
	
	char *line=(char *)arg;
	int i,check;
	int check_start_file[MAX_NUM_PROGRAM],thesi=0;
	int file_read,first=0, entoles_pou_etreksan=0, check_down_value=0;
	int value_op1=0, value_op2=0, value_op3=0, found_branch[MAX_NUM_PROGRAM];
	int check_type_op1=0, check_type_op2=0, check_type_op3=0, num_of_argv=0;
	char *token, *value_argv;
	char line_file[256];
	char *op1,*op2,*op3, op5[MAX_NUM_PROGRAM][50];
	int thesi_eisagwgis_stoixeiwn=0, thesi_exagwgis_stoixeiwn=0;
	struct variable *var[MAX_NUM_PROGRAM];
	struct table_variable *var_table[MAX_NUM_PROGRAM];
	struct return_value new_address;
	
	thesi=se_poio_thread_trexw-1;
	
	first=0;
	value_argv = strtok(line," '\0''\n'");
	printf("value_argv %s\n",value_argv);
	file_read=open(value_argv, O_RDONLY);
	if(file_read==-1){
		printf("file not found.\n");
		return 0;//exit(0)'''''';;;;;'''''
	}
	program_character[thesi][thesi_eisagwgis_stoixeiwn].fd=file_read;
	program_character[thesi][thesi_eisagwgis_stoixeiwn].down_thread=0;
	var_table[thesi_eisagwgis_stoixeiwn] = put_var_table(var_table[thesi_eisagwgis_stoixeiwn],"$argv",thesi_eisagwgis_stoixeiwn,num_of_argv, first);
	num_of_argv++;
	
	first=1;
	while(1){
		value_argv=strtok(NULL," '\0''\n'");
		if(value_argv==NULL){
			break;
		}
		else{
			var_table[thesi_eisagwgis_stoixeiwn] = put_var_table(var_table[thesi_eisagwgis_stoixeiwn],"$argv",atoi(value_argv),num_of_argv, first);
			num_of_argv++;
		}
	}
	
	first=0;
	var[thesi_eisagwgis_stoixeiwn]= put_var(var[thesi_eisagwgis_stoixeiwn],"$argc",num_of_argv, first);
	num_of_argv=0;
	check_start_file[thesi_eisagwgis_stoixeiwn]=0;
	found_branch[thesi_eisagwgis_stoixeiwn]=0;
	thesi_eisagwgis_stoixeiwn++;
	first=1;
	
	while(1){
		for(i=0;i<MAX_NUM_PROGRAM;i++){
			if(program_character[thesi][i].transport == 1){
				printf("pernw stoixeia !!!\n");
				first=0;
				
				value_argv = strtok(program_character[thesi][i].line," '\0''\n'");
				file_read = open(value_argv, O_RDONLY);
				program_character[thesi][thesi_eisagwgis_stoixeiwn].fd=file_read;
				program_character[thesi][thesi_eisagwgis_stoixeiwn].down_thread=0;
				program_character[thesi][thesi_eisagwgis_stoixeiwn].transport = 2;
				var_table[thesi_eisagwgis_stoixeiwn] = put_var_table(var_table[thesi_eisagwgis_stoixeiwn],"$argv",thesi_eisagwgis_stoixeiwn,num_of_argv, first);
				num_of_argv++;
				
				first=1;
				while(1){
					value_argv=strtok(NULL," '\0''\n'");
					if(value_argv==NULL){
						break;
					}
					else{
						var_table[thesi_eisagwgis_stoixeiwn] = put_var_table(var_table[thesi_eisagwgis_stoixeiwn],"$argv",atoi(value_argv),num_of_argv, first);
						num_of_argv++;
					}
				}
				
				first=0;
				var[thesi_eisagwgis_stoixeiwn]= put_var(var[thesi_eisagwgis_stoixeiwn],"$argc",num_of_argv, first);
				num_of_argv=0;
				check_start_file[thesi_eisagwgis_stoixeiwn]=0;
				found_branch[thesi_eisagwgis_stoixeiwn]=0;
				thesi_eisagwgis_stoixeiwn++;
				first=1;
			}
			
		}
		
		while(1){
			if(program_character[thesi][thesi_exagwgis_stoixeiwn].down_thread==1){
				check=pthread_mutex_lock(&mtx);
				if(check){
					printf("error lock\n");
				}
				check_down_value=return_value_global(program_character[thesi][thesi_exagwgis_stoixeiwn].check_type_sem, program_character[thesi][thesi_exagwgis_stoixeiwn].name_sem, var[thesi_exagwgis_stoixeiwn]);
				
				if(check_down_value<0){
					program_character[thesi][thesi_exagwgis_stoixeiwn].situation=0;
					for(i=0; i<MAX_NUM_PROGRAM; i++){
						thesi_exagwgis_stoixeiwn++;
						if(thesi_exagwgis_stoixeiwn==MAX_NUM_PROGRAM){
							thesi_exagwgis_stoixeiwn=0;
						}
						if(program_character[thesi][thesi_exagwgis_stoixeiwn].situation==0){
							program_character[thesi][thesi_exagwgis_stoixeiwn].situation=1;
							break;
						}
					}
					entoles_pou_etreksan=0;
				}
				else{
					program_character[thesi][thesi_exagwgis_stoixeiwn].down_thread=0;
					for(i=0;i<MAX_NUM_PROGRAM;i++){
						if(program_character[thesi][i].down_thread==1){
							check_down_value--;
							put_value_global(program_character[thesi][i].check_type_sem,check_down_value, program_character[thesi][i].name_sem, var[thesi_exagwgis_stoixeiwn]);
							break;
						}
					}
				}
				check=pthread_mutex_unlock(&mtx);
				if(check){
					printf("error unlock\n");
				}
			}
			else{
				break;
			}
			//an einai mono ena kai exei kollisei logo down
			for(i=0;i<MAX_NUM_PROGRAM;i++){
				if(program_character[thesi][i].transport == 1){
					printf("pernw stoixeia !!!\n");
					first=0;
					
					value_argv = strtok(program_character[thesi][i].line," '\0''\n'");
					file_read = open(value_argv, O_RDONLY);
					program_character[thesi][thesi_eisagwgis_stoixeiwn].fd=file_read;
					program_character[thesi][thesi_eisagwgis_stoixeiwn].down_thread=0;
					program_character[thesi][thesi_eisagwgis_stoixeiwn].transport = 2;
					var_table[thesi_eisagwgis_stoixeiwn] = put_var_table(var_table[thesi_eisagwgis_stoixeiwn],"$argv",thesi_eisagwgis_stoixeiwn,num_of_argv, first);
					num_of_argv++;
					
					first=1;
					while(1){
						value_argv=strtok(NULL," '\0''\n'");
						if(value_argv==NULL){
							break;
						}
						else{
							var_table[thesi_eisagwgis_stoixeiwn] = put_var_table(var_table[thesi_eisagwgis_stoixeiwn],"$argv",atoi(value_argv),num_of_argv, first);
							num_of_argv++;
						}
					}
					
					first=0;
					var[thesi_eisagwgis_stoixeiwn]= put_var(var[thesi_eisagwgis_stoixeiwn],"$argc",num_of_argv, first);
					num_of_argv=0;
					check_start_file[thesi_eisagwgis_stoixeiwn]=0;
					found_branch[thesi_eisagwgis_stoixeiwn]=0;
					thesi_eisagwgis_stoixeiwn++;
					first=1;
				}
				
			}
			
		}
		
		if(program_character[thesi][thesi_exagwgis_stoixeiwn].situation==-1){
			for(i=0; i<MAX_NUM_PROGRAM; i++){
				thesi_exagwgis_stoixeiwn++;
				if(thesi_exagwgis_stoixeiwn==MAX_NUM_PROGRAM){
					thesi_exagwgis_stoixeiwn=0;
				}
				if(program_character[thesi][thesi_exagwgis_stoixeiwn].situation==0){
					program_character[thesi][thesi_exagwgis_stoixeiwn].situation=1;
					break;
				}
			}
			entoles_pou_etreksan=0;
			
		}
		
		read_line(program_character[thesi][thesi_exagwgis_stoixeiwn].fd, line_file);
		token=strtok(line_file," '\n'	");
		if(token==NULL){
			printf("den bre8ike leksi pou prosdiorizei tin leitourgeia\n");
			return 0;
		}
		if(check_start_file[thesi_exagwgis_stoixeiwn]==0){
			if(strcmp(token,"#PROGRAM") != 0){
				printf("den einai swsti i morfi tou kwdika leipei to #PROGRAM \n");
				return 0;
			}
			else {
				check_start_file[thesi_exagwgis_stoixeiwn]=1;
			}
		}
		
		if(found_branch[thesi_exagwgis_stoixeiwn]==1){
			if(strcmp(token, op5[thesi_exagwgis_stoixeiwn])==0){
				found_branch[thesi_exagwgis_stoixeiwn]=0;
			}
			token=strtok(NULL," '\n'");
		}
		
		if(found_branch[thesi_exagwgis_stoixeiwn]==0){
			
			entoles_pou_etreksan++;
			
			if ((token[0]=='L') && (strcmp(token,"LOAD")!=0)){
				token=strtok(NULL," '\n'");
			}
			if(strcmp(token,"LOAD") == 0){
				check=pthread_mutex_lock(&mtx);
				if(check){
					printf("error lock\n");
				}
				op1 = strtok(NULL," '\n'");
				check_type_op1=check_Var(op1);
				
				op2 = strtok(NULL," '\n");
				check_type_op2=check_Var(op2);
				value_op2=return_value_global(check_type_op2, op2, var[thesi_exagwgis_stoixeiwn]);
				
				new_address = return_value_var(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1,value_op2, first);
				var[thesi_exagwgis_stoixeiwn] = new_address.var;
				var_table[thesi_exagwgis_stoixeiwn] = new_address.table_variable;
				check=pthread_mutex_unlock(&mtx);
				if(check){
					printf("error unlock\n");
				}
			}
			else if(strcmp(token,"STORE") == 0){
				check=pthread_mutex_lock(&mtx);
				if(check){
					printf("error lock\n");
				}
				op1 = strtok(NULL," '\n'");
				check_type_op1=check_Var(op1);
				
				op2 = strtok(NULL," '\n'");
				
				check_type_op2=check_VarVal(op2);
				value_op2 = return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				put_value_global(check_type_op1, value_op2, op1, var[thesi_exagwgis_stoixeiwn]);
				check=pthread_mutex_unlock(&mtx);
				if(check){
					printf("error unlock\n");
				}
			}
			else if(strcmp(token,"SET") == 0){
				op1 = strtok(NULL," '\n'");
				check_type_op1=check_Var(op1);
				
				op2 = strtok(NULL," '\n'");
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				new_address = return_value_var(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1,value_op2, first);
				var[thesi_exagwgis_stoixeiwn] = new_address.var;
				var_table[thesi_exagwgis_stoixeiwn] = new_address.table_variable;
			}
			else if(strcmp(token,"ADD") == 0){
				op1 = strtok(NULL," '\n'");
				op2 = strtok(NULL," '\n'");
				op3 = strtok(NULL," '\n'");
				
				check_type_op1=check_Var(op1);
				
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				check_type_op3=check_VarVal(op3);
				value_op3  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op3, op3);
				
				value_op1=value_op2+value_op3;
				
				new_address = return_value_var(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1,value_op1, first);
				var[thesi_exagwgis_stoixeiwn] = new_address.var;
				var_table[thesi_exagwgis_stoixeiwn] = new_address.table_variable;
				sleep(1);
			}
			else if(strcmp(token,"SUB") ==0){
				op1 = strtok(NULL," '\n'");
				op2 = strtok(NULL," '\n'");
				op3 = strtok(NULL," '\n'");
				
				check_type_op1=check_Var(op1);
				
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				check_type_op3=check_VarVal(op3);
				value_op3  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op3, op3);
				
				value_op1=value_op2-value_op3;
				
				new_address = return_value_var(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1,value_op1, first);
				var[thesi_exagwgis_stoixeiwn] = new_address.var;
				var_table[thesi_exagwgis_stoixeiwn] = new_address.table_variable;
			}
			else if(strcmp(token,"MUL") == 0){
				op1 = strtok(NULL," '\n'");
				op2 = strtok(NULL," '\n'");
				op3 = strtok(NULL," '\n'");
				
				check_type_op1=check_Var(op1);
				
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				check_type_op3=check_VarVal(op3);
				value_op3  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op3, op3);
				
				value_op1=value_op2*value_op3;
				
				new_address = return_value_var(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1,value_op1, first);
				var[thesi_exagwgis_stoixeiwn] = new_address.var;
				var_table[thesi_exagwgis_stoixeiwn] = new_address.table_variable;
			}
			else if(strcmp(token,"DIV") ==0){
				op1 = strtok(NULL," '\n'");
				op2 = strtok(NULL," '\n'");
				op3 = strtok(NULL," '\n'");
				
				check_type_op1=check_Var(op1);
				
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				check_type_op3=check_VarVal(op3);
				value_op3  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op3, op3);
				
				value_op1=value_op2/value_op3;
				
				new_address = return_value_var(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1,value_op1, first);
				var[thesi_exagwgis_stoixeiwn] = new_address.var;
				var_table[thesi_exagwgis_stoixeiwn] = new_address.table_variable;
			}
			else if(strcmp(token,"MOD") ==0){
				op1 = strtok(NULL," '\n'");
				op2 = strtok(NULL," '\n'");
				op3 = strtok(NULL," '\n'");
				
				check_type_op1=check_Var(op1);
				
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				check_type_op3=check_VarVal(op3);
				value_op3  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op3, op3);
				
				value_op1=value_op2%value_op3;
				
				new_address = return_value_var(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1,value_op1, first);
				var[thesi_exagwgis_stoixeiwn] = new_address.var;
				var_table[thesi_exagwgis_stoixeiwn] = new_address.table_variable;
			}
			else if(strcmp(token,"BRGT") ==0){
				op1 = strtok(NULL," '\n'");
				op2 = strtok(NULL," '\n'");
				op3 = strtok(NULL," '\n'	");
				
				check_type_op1=check_VarVal(op1);
				value_op1  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1);
				
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				check_Label(op3);
				
				if(value_op1 > value_op2 ){
					found_branch[thesi_exagwgis_stoixeiwn]=1;
					strcpy(op5[thesi_exagwgis_stoixeiwn], op3);
					lseek(program_character[thesi][thesi_exagwgis_stoixeiwn].fd, 0, SEEK_SET);
				}
			}
			else if(strcmp(token,"BRGE") ==0){
				op1 = strtok(NULL," '\n'");
				op2 = strtok(NULL," '\n'");
				op3 = strtok(NULL," '\n'	");
				
				check_type_op1=check_VarVal(op1);
				value_op1  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1);
				
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				check_Label(op3);
				
				if(value_op1 >= value_op2 ){
					found_branch[thesi_exagwgis_stoixeiwn]=1;
					strcpy(op5[thesi_exagwgis_stoixeiwn], op3);
					lseek(program_character[thesi][thesi_exagwgis_stoixeiwn].fd, 0, SEEK_SET);
				}
			}
			else if(strcmp(token,"BRLT") ==0){
				op1 = strtok(NULL," '\n'");
				op2 = strtok(NULL," '\n'");
				op3 = strtok(NULL," '\n'	");
				
				check_type_op1=check_VarVal(op1);
				value_op1  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1);
				
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				check_Label(op3);
				
				if(value_op1 < value_op2 ){
					found_branch[thesi_exagwgis_stoixeiwn]=1;
					strcpy(op5[thesi_exagwgis_stoixeiwn], op3);
					lseek(program_character[thesi][thesi_exagwgis_stoixeiwn].fd, 0, SEEK_SET);
				}
			}
			else if(strcmp(token,"BRLE") ==0){
				op1 = strtok(NULL," '\n'");
				op2 = strtok(NULL," '\n'");
				op3 = strtok(NULL," '\n'	");
				
				check_type_op1=check_VarVal(op1);
				value_op1  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1);
				
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				check_Label(op3);
				
				if(value_op1 <= value_op2 ){
					found_branch[thesi_exagwgis_stoixeiwn]=1;
					strcpy(op5[thesi_exagwgis_stoixeiwn], op3);
					lseek(program_character[thesi][thesi_exagwgis_stoixeiwn].fd, 0, SEEK_SET);
				}
			}
			else if(strcmp(token,"BREQ") ==0){
				op1 = strtok(NULL," '\n'");
				op2 = strtok(NULL," '\n'");
				op3 = strtok(NULL," '\n'	");
				
				check_type_op1=check_VarVal(op1);
				value_op1  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1);
				
				check_type_op2=check_VarVal(op2);
				value_op2  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op2, op2);
				
				check_Label(op3);
				
				if(value_op1 == value_op2 ){
					found_branch[thesi_exagwgis_stoixeiwn]=1;
					strcpy(op5[thesi_exagwgis_stoixeiwn], op3);
					lseek(program_character[thesi][thesi_exagwgis_stoixeiwn].fd, 0, SEEK_SET);
				}
			}
			else if(strcmp(token,"BRA") ==0){
				op1 = strtok(NULL," '\n'	");
				check_Label(op1);
				
				found_branch[thesi_exagwgis_stoixeiwn]=1;
				strcpy(op5[thesi_exagwgis_stoixeiwn], op1);
				lseek(program_character[thesi][thesi_exagwgis_stoixeiwn].fd, 0, SEEK_SET);
			}
			else if(strcmp(token,"DOWN")==0){
				check=pthread_mutex_lock(&mtx);
				if(check){
					printf("error lock\n");
				}
				op1 = strtok(NULL," '\n'");
				check_type_op1=check_Var(op1);
				value_op1=return_value_global(check_type_op1, op1, var[thesi_exagwgis_stoixeiwn]);
				check=pthread_mutex_unlock(&mtx);
				if(check){
					printf("error unlock\n");
				}
				
				if(value_op1 >= 1){
					value_op1--;
				}
				else if(value_op1 == 0){
					value_op1--;
					program_character[thesi][thesi_exagwgis_stoixeiwn].down_thread=1;
					program_character[thesi][thesi_exagwgis_stoixeiwn].check_type_sem=check_type_op1;
					strncpy(program_character[thesi][thesi_exagwgis_stoixeiwn].name_sem, op1,strlen(op1));
					
				}
				else if(value_op1 == -1){
					program_character[thesi][thesi_exagwgis_stoixeiwn].down_thread=1;
					program_character[thesi][thesi_exagwgis_stoixeiwn].check_type_sem=check_type_op1;
					strncpy(program_character[thesi][thesi_exagwgis_stoixeiwn].name_sem, op1,strlen(op1));
				}
				
				
				check=pthread_mutex_lock(&mtx);
				if(check){
					printf("error lock\n");
				}
				put_value_global(check_type_op1, value_op1, op1, var[thesi_exagwgis_stoixeiwn]);
				check=pthread_mutex_unlock(&mtx);
				if(check){
					printf("error unlock\n");
				}
				
				program_character[thesi][thesi_exagwgis_stoixeiwn].situation=0;
				for(i=0; i<MAX_NUM_PROGRAM; i++){
					thesi_exagwgis_stoixeiwn++;
					if(thesi_exagwgis_stoixeiwn==MAX_NUM_PROGRAM){
						thesi_exagwgis_stoixeiwn=0;
					}
					if(program_character[thesi][thesi_exagwgis_stoixeiwn].situation==0){
						program_character[thesi][thesi_exagwgis_stoixeiwn].situation=1;
						break;
					}
				}
				
				entoles_pou_etreksan=0;
			}
			else if(strcmp(token,"UP")==0){
				op1 = strtok(NULL," '\n'");
				check_type_op1=check_Var(op1);
				check=pthread_mutex_lock(&mtx);
				if(check){
					printf("error lock\n");
				}
				value_op1=return_value_global(check_type_op1, op1,var[thesi_exagwgis_stoixeiwn]);
				value_op1++;
				
				put_value_global(check_type_op1, value_op1, op1, var[thesi_exagwgis_stoixeiwn]);
				check=pthread_mutex_unlock(&mtx);
				if(check){
					printf("error unlock\n");
				}
				
				
				program_character[thesi][thesi_exagwgis_stoixeiwn].situation=0;
				for(i=0; i<MAX_NUM_PROGRAM; i++){
					thesi_exagwgis_stoixeiwn++;
					if(thesi_exagwgis_stoixeiwn==MAX_NUM_PROGRAM){
						thesi_exagwgis_stoixeiwn=0;
					}
					if(program_character[thesi][thesi_exagwgis_stoixeiwn].situation==0){
						program_character[thesi][thesi_exagwgis_stoixeiwn].situation=1;
						break;
					}
				}
				entoles_pou_etreksan=0;
			}
			else if(strcmp(token,"SLEEP") ==0){
				op1 = strtok(NULL," '\n'");
				
				check_type_op1=check_VarVal(op1);
				value_op1  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op1, op1);
				
				sleep(value_op1);
				
				program_character[thesi][thesi_exagwgis_stoixeiwn].situation=0;
				for(i=0; i<MAX_NUM_PROGRAM; i++){
					thesi_exagwgis_stoixeiwn++;
					if(thesi_exagwgis_stoixeiwn==MAX_NUM_PROGRAM){
						thesi_exagwgis_stoixeiwn=0;
					}
					if(program_character[thesi][thesi_exagwgis_stoixeiwn].situation==0){
						program_character[thesi][thesi_exagwgis_stoixeiwn].situation=1;
						break;
					}
				}
				
				entoles_pou_etreksan=0;
				
			}
			else if(strcmp(token,"PRINT")  ==0){
				printf("tread id: %ld,", (long) pthread_self());
				op1 = strtok(NULL," '\n'");
				if(op1[0]=='"'){
					printf(" %s", op1+1);
					op2= strtok(NULL,"'\"'");
					printf(" %s", op2);
				}
				else{
					printf("error in printf\n");
					return 0;//exit(0)'''''';;;;''''
				}
				
				while (1){
					op3 = strtok(NULL," '\n''\0'");
					if (op3!=NULL){
						check_type_op3=check_VarVal(op3);
						value_op3  =return_value_op(var[thesi_exagwgis_stoixeiwn],var_table[thesi_exagwgis_stoixeiwn],check_type_op3, op3);
						
						printf(", %d", value_op3);
					}
					else {
						break;
					}
				}
				
				printf("\n");
			}
			else if(strcmp(token,"RETURN") ==0){
				program_character[thesi][thesi_exagwgis_stoixeiwn].situation=-1;
				for(i=0; i<MAX_NUM_PROGRAM; i++){
					thesi_exagwgis_stoixeiwn++;
					if(thesi_exagwgis_stoixeiwn==MAX_NUM_PROGRAM){
						thesi_exagwgis_stoixeiwn=0;
					}
					if(program_character[thesi][thesi_exagwgis_stoixeiwn].situation==0){
						program_character[thesi][thesi_exagwgis_stoixeiwn].situation=1;
						break;
					}
				}
				
				entoles_pou_etreksan=0;
				
				num_of_programs[thesi]--;
				if(num_of_programs[thesi]==0){
					return 0;
				}
			}
			
			if(entoles_pou_etreksan==10){
				program_character[thesi][thesi_exagwgis_stoixeiwn].situation=0;
				for(i=0; i<MAX_NUM_PROGRAM; i++){
					thesi_exagwgis_stoixeiwn++;
					if(thesi_exagwgis_stoixeiwn==MAX_NUM_PROGRAM){
						thesi_exagwgis_stoixeiwn=0;
					}
					if(program_character[thesi][thesi_exagwgis_stoixeiwn].situation==0){
						program_character[thesi][thesi_exagwgis_stoixeiwn].situation=1;
						break;
					}
				}
				
				entoles_pou_etreksan=0;
			}
		}
	 }
	 
	return 0;
}

int main(int argc,char *argv[]){
	
	int check;
	int i=0, j=0, k=0;
	int thread_id_kill, thread_number=0;
	char command[256];
	char *op1,*op2, *op3, name_file[20] ,*name_file_final;
	pthread_t thread;
	
	for(i=0;i<MAX_NUM_THREAD;i++){
		num_of_programs[i]=0;
		num_input[i]=0;
	}
	
	check=pthread_mutex_init(&mtx, NULL);
	if(check){
		printf("error mutex init\n");
	}
	
	if(argc!=2){
		printf("error not argument\n");
		return 0;
	}
	
	
	thread_number=atoi(argv[1]);
	
	
	for(j=0;j<MAX_NUM_THREAD;j++){
		for(i=0;i<MAX_NUM_PROGRAM;i++){
			program_character[j][i].transport = 0;
			program_character[j][i].situation = 2;
			program_character[j][i].down_thread=0;
		}
	}
	
	while(1){
		
		fgets(command,256,stdin);
		
		op1 = strtok(command," '\n'");
		
		if(strcmp(op1,"run") == 0){
 			op2 = strtok(NULL,"'\n'");
			if(num_of_programs[k]==0){
				se_poio_thread_trexw++;
				printf("prwti fora to thread\n");
				strcpy(name_file, op2);
				name_file_final=strtok(name_file," '\n'");
				strncpy(program_character[k][num_of_programs[k]].name, name_file_final,strlen(name_file_final));
				program_character[k][num_of_programs[k]].situation=1;
				program_character[k][num_of_programs[k]].transport = 2;
				program_character[k][num_of_programs[k]].thesi_pou_mpike=0;
				num_input[k]=1;
				check = pthread_create(&thread,NULL,tranclator, op2);
				if(check !=0){
					printf("error in pthread\n");
				}
				program_character[k][num_of_programs[k]].thread_id=(long int)thread;
			}
			else{
				printf("meta dedomenwn sto thread\n");
				strcpy(name_file, op2);
				name_file_final=strtok(name_file," '\n'");
				strncpy(program_character[k][num_input[k]].name, name_file_final,strlen(name_file_final));
				strncpy(program_character[k][num_input[k]].line, op2,strlen(op2));
				program_character[k][num_input[k]].thread_id=program_character[k][0].thread_id;
				program_character[k][num_input[k]].situation=0;
				program_character[k][num_input[k]].transport = 1;
				program_character[k][num_input[k]].thesi_pou_mpike=num_input[k];
				num_input[k]++;
			}
			num_of_programs[k]++;
			
		}
		else if(strcmp(op1,"exit") == 0){
			printf("exit run time\n");
			return 0;
		}
		else if(strcmp(op1,"kill") == 0){
			op2 = strtok(NULL," '\n'");
			thread_id_kill = atoi(op2);
			
			op3 = strtok(NULL," '\n'");
			j=atoi(op3);
			
			program_character[j][thread_id_kill].situation = -1;
		}
		else if(strcmp(op1,"list")==0){
			for(i=0;i<thread_number;i++){
				print_list(num_input[i],i);
			}
		}
		
		k++;
		if(k==thread_number){
			k=0;
		}
	}
	
	return 0;
}
 
 
