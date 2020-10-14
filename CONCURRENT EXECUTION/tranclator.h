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

#define MAX_VAR 10
#define MAX_GLOBAL 10

struct table_variable{
	char var_name[20];
	int *var_value;
	int mal;
	int set_in_var_table;
};

struct table_global_variable{
	char globalvar_name[20];
	int *globalvar_value;
	int mal;
};

struct variable{
	char var_name[20];
	int var_value;
	int set_in_var;
};

struct global_variable{
	char globalvar_name[20];
	int globalvar_value;
};

struct return_value{
	struct table_variable *table_variable;
	struct variable *var;
};

struct global_variable *GlobalVar;
struct table_global_variable *GlobalVarTable;
volatile int set_in_global=0, set_in_global_table=0;

int chek_table(char *string){
	
	char *op3;
	
 	op3=strchr(string, '[');
	
	if(op3==NULL){
		return 0;
	}
	if(strchr(op3,'[')==NULL){
		printf("la8os morfi : periexei pinaka\n");
		exit(0);
	}
	
	if(op3[1]=='$'){
		return 2;
	}
	else if(isdigit(op3[1])){
		return 1;
	}
	
 	return 0;
	
}

int check_Var(char *string){
	
	int check_type_table=-2;
	
	if (string==NULL){
		printf("den do8ike metabliti\n");
		exit(0);
	}
	
	if (string[0]=='$'){
		if(!isalpha(string[1])){
			printf("la8os morfi onomatos metablitis\n");
			exit(0);
		}
	}
	else if(string[0]!='$'){
		printf("la8os morfi onomatos metablitis to prwto gramma den einai $\n");
		exit(0);
	}
	
	check_type_table=chek_table(string);
	if (check_type_table==0){
		return 2;
	}
	else if (check_type_table==1){
		return 3;
	}
	else if (check_type_table==2){
		return 4;
	}
	
	
	return -1;
	
}

int check_VarVal(char *string){
	
	int check_type_table=-2;
	
	if (string==NULL){
		printf("den do8ike metabliti\n");
		exit(0);
	}
	
	if (string[0]=='$'){
		if(!isalpha(string[1])){
			printf("la8os morfi onomatos metablitis\n");
			exit(0);
		}
		check_type_table=chek_table(string);
		if (check_type_table==0){
			return 2;
		}
		else if (check_type_table==1){
			return 3;
		}
		else if (check_type_table==2){
			return 4;
		}
	}
	
	return 1;
	
}

int check_Label(char *string){
	
	if (string==NULL){
		printf("den do8ike metabliti\n");
		exit(0);
	}
	
	if(string[0]!='L'){
		printf("la8os morfi onomatos Label\n");
		exit(0);
	}
	
	return 2;
	
}

int search_global(char *name){
	
	int i=0;
	
	while(i<set_in_global){
		if(strcmp(GlobalVar[i].globalvar_name ,name)==0){
			return i;
		}
		i++;
	}
	
	return -1;
	
}

int search_global_table(char *name){
	
	int i=0;
	
	while(i<set_in_global_table){
		if(strcmp(GlobalVarTable[i].globalvar_name ,name)==0){
			return i;
		}
		i++;
	}
	
	return -1;
	
}

int search_var(struct variable *var, char *name){
 	
 	int i=0;
 	
 	while(i<var->set_in_var){
 		if(strcmp(var[i].var_name,name)==0){
 			return i;
 		}
 		i++;
 	}
 	
 	return -1;
 	
}

int search_var_table(struct table_variable *var_table, char *name){
 	
 	int i=0;
 	
 	while(i<var_table->set_in_var_table){
 		if(strcmp(var_table[i].var_name,name)==0){
 			return i;
 		}
 		i++;
 	}
 	
 	return -1;
 	
}

int put_global(char *name, int value){
	
	int check_search=0;
	
	if(set_in_global == 0){
		GlobalVar = (struct global_variable *)malloc(sizeof(struct global_variable));
		if(GlobalVar == NULL){
			printf("malloc not\n");
			exit(0);
		}
		
		strcpy(GlobalVar[set_in_global].globalvar_name, name);
		GlobalVar[set_in_global].globalvar_value= value;
			
		set_in_global++;
	}
	else{
		
		check_search = search_global(name);
		if(check_search==-1){
			GlobalVar = (struct global_variable *)realloc(GlobalVar,sizeof(struct global_variable)*(set_in_global+1));
			
			strcpy(GlobalVar[set_in_global].globalvar_name, name);
			GlobalVar[set_in_global].globalvar_value= value;
			
			set_in_global++;
		}
		else{
			strcpy(GlobalVar[check_search].globalvar_name, name);
			GlobalVar[check_search].globalvar_value= value;
		}
	}
	
	return 0;
	
}

int put_global_table(char *name, int value,int thesi){
	
	int check_search=0;

	if(set_in_global_table == 0){
		GlobalVarTable = (struct table_global_variable *)malloc(sizeof(struct table_global_variable));
		if(GlobalVarTable == NULL){
			perror("malloc:");
			exit(0);
		}
		
		GlobalVarTable[set_in_global_table].mal= thesi;
		
		GlobalVarTable[set_in_global_table].globalvar_value= (int *)malloc(sizeof(int)*(thesi+1));

		strcpy(GlobalVarTable[set_in_global_table].globalvar_name, name);
		GlobalVarTable[set_in_global_table].globalvar_value[thesi]= value;
		
		set_in_global_table++;
	}
	else{
		
		check_search = search_global_table(name);
		
		if(check_search == -1){
			
			GlobalVarTable = (struct table_global_variable *)realloc(GlobalVarTable,sizeof(struct table_global_variable)*(set_in_global_table+1));
			GlobalVarTable[set_in_global_table].mal= thesi;
			GlobalVarTable[set_in_global_table].globalvar_value = (int *)malloc(sizeof(int)*(thesi+1));
			
			strcpy(GlobalVarTable[set_in_global_table].globalvar_name, name);
			GlobalVarTable[set_in_global_table].globalvar_value[thesi]= value;
			
			set_in_global_table++;
		}
		else {
			//an uparxei ston pinaka 
			if(thesi > GlobalVarTable[check_search].mal){
				GlobalVarTable[check_search].mal= thesi;
				GlobalVarTable[check_search].globalvar_value = (int *)realloc(GlobalVarTable[check_search].globalvar_value,sizeof(int)*(thesi+1));
			}
			
			strcpy(GlobalVarTable[check_search].globalvar_name, name);
			GlobalVarTable[check_search].globalvar_value[thesi]= value;
		}
	}
	
	
	return 0;
	
}

int return_value_global(int check_type, char *op, struct variable *var){
	
	char *op4,*op5;
	int value_op=0, thesi=0, thesi_argument=0, position=0, value_argument=0;
	
	
	if (check_type==1){
		value_op = atoi(op);
	}
	else if(check_type==2){
		thesi = search_global(op);
		if(thesi == -1){
// 			printf("error variable not found\n");
			return 0;
		}
		else{
			value_op = GlobalVar[thesi].globalvar_value;
		}
	}
	else if(check_type==3){
		op5=strtok(op,"[");
		thesi= search_global_table(op5);
		
		if(thesi == -1){
// 			printf("error variable not found\n");
			return 0;
		}
		else{
			op4=strtok(NULL,"]");
			position=atoi(op4);
			value_op = GlobalVarTable[thesi].globalvar_value[position];
		}
	}
	else if(check_type==4){
		op5=strtok(op,"[");
		thesi= search_global_table(op);
		if(thesi == -1){
// 			printf("error variable not found\n");
			return 0;
		}
		else{
			op4=strtok(NULL,"]");
			thesi_argument = search_var(var,op4);
			if(thesi_argument == -1){
// 				printf("error variable not found\n");
				return 0;
			}
			else{
				value_argument = GlobalVar[thesi_argument].globalvar_value;
			}
			value_op = GlobalVarTable[thesi].globalvar_value[value_argument];
		}
	}
	
	return value_op;
	
}

int put_value_global(int check_type, int value, char *op, struct variable *var){
	
	char *op4;
	int position=0, lenght=0, thesi_argument=0,value_argument=0;
	
	if(check_type == 2){
		put_global(op,value);
	}
	else if(check_type == 3){
		op4=strchr(op,'[');
		lenght=strlen(op4);
		op4[lenght-1]='\0';
		position=atoi(op4+1);
		op=strtok(op,"[");
		put_global_table(op,value,position);
	}
	else if(check_type == 4){
		op4=strchr(op,'[');
		lenght=strlen(op4);
		op4[lenght-1]='\0';
		thesi_argument= search_var(var,op4+1);
		if(thesi_argument == -1){
// 			printf("error variable not found\n");
			return 0;
		}
		else{
			value_argument = GlobalVar[thesi_argument].globalvar_value;
		}
		op=strtok(op,"[");
		put_global_table(op,value,value_argument);
	}
	
	return 0;
	
}


struct variable *put_var(struct variable *var, char *name, int value, int first_time){
	
	int check_search=0;
	
	if(first_time == 0){
		var = (struct variable *)malloc(sizeof(struct variable));
		if(var == NULL){
			exit(0);
		}
		var->set_in_var=0;
		strcpy(var[var->set_in_var].var_name, name);
		var[var->set_in_var].var_value= value;
		
// 		printf("var_name %s, value %d\n",var[var->set_in_var].var_name, var[var->set_in_var].var_value);
		
		var->set_in_var++;
	}
	else{
		
		check_search = search_var(var, name);
		
		if(check_search == -1){
			var = (struct variable *)realloc(var,sizeof(struct variable)*(var->set_in_var+1));
			strcpy(var[var->set_in_var].var_name, name);
			var[var->set_in_var].var_value= value;
// 			printf("var_name %s, value %d\n",var[var->set_in_var].var_name, var[var->set_in_var].var_value);
			var->set_in_var++;
		}
		else{
			strcpy(var[check_search].var_name, name);
			var[check_search].var_value= value;
			
// 			printf("var_name %s, value %d\n",var[check_search].var_name, var[check_search].var_value);
		}
	}
	
	
	
	
	return var;
	
}

struct table_variable *put_var_table(struct table_variable *var_table, char *name, int value,int thesi, int first_time){
	
	int check_search=0;
	
	if(first_time== 0){
		var_table = (struct table_variable *)malloc(sizeof(struct table_variable));
		if(var_table == NULL){
			perror("malloc:");
			exit(0);
		}
		var_table->set_in_var_table=0;
		var_table[var_table->set_in_var_table].mal= thesi;
		
		var_table[var_table->set_in_var_table].var_value= (int *)malloc(sizeof(int)*(thesi+1));
		
		strcpy(var_table[var_table->set_in_var_table].var_name, name);
		var_table[var_table->set_in_var_table].var_value[thesi]= value;
		
// 		printf("var_name %s, value %d\n",var_table[var_table->set_in_var_table].var_name, var_table[var_table->set_in_var_table].var_value[thesi]);
		
		var_table->set_in_var_table++;
	}
	else{
		
		check_search = search_var_table(var_table,name);
		
		if(check_search == -1){
			
			var_table = (struct table_variable *)realloc(var_table,sizeof(struct table_variable)*(var_table->set_in_var_table+1));
			var_table[var_table->set_in_var_table].mal= thesi;
			var_table[var_table->set_in_var_table].var_value = (int *)malloc(sizeof(int)*(thesi+1));
			
			strcpy(var_table[var_table->set_in_var_table].var_name, name);
			var_table[var_table->set_in_var_table].var_value[thesi]= value;
			
// 			printf("var_name %s, value %d\n",var_table[var_table->set_in_var_table].var_name, var_table[var_table->set_in_var_table].var_value[thesi]);
			
			var_table->set_in_var_table++;
		}
		else {
			//an uparxei ston pinaka 
			if(thesi > var_table[check_search].mal){
				var_table[check_search].mal= thesi;
				var_table[check_search].var_value = (int *)realloc(var_table[check_search].var_value,sizeof(int)*(thesi+1));
			}
			
			strcpy(var_table[check_search].var_name, name);
			var_table[check_search].var_value[thesi]= value;
			
// 			printf("var_name %s, value %d\n",var_table[check_search].var_name, var_table[check_search].var_value[thesi]);
			
		}
	}
	
	
	return var_table;
	
}

int return_value_op(struct variable *var,struct table_variable *var_table,int check_type_op2, char *op2){
	
	int value_op2;
	int thesi=0,thesi_argument=0,position=0,value_argument=0;
	char *op4,*op5;
	
	if (check_type_op2==1){
		value_op2 = atoi(op2);
	}
	else if(check_type_op2==2){
		thesi = search_var(var,op2);
		if(thesi == -1){
// 			printf("error variable not found\n");
			exit (0);
		}
		else{
			value_op2 = var[thesi].var_value;
		}
	}
	else if(check_type_op2==3){
		op5=strtok(op2,"[");
		thesi= search_var_table(var_table, op5);
		if(thesi == -1){
// 			printf("error variable not found\n");
			exit (0);
		}
		else{
			op4=strtok(NULL,"]");
			position=atoi(op4);
			value_op2 = var_table[thesi].var_value[position];
		}
	}
	else if(check_type_op2==4){
		op5=strtok(op2,"[");
		thesi= search_var_table(var_table,op5);
		if(thesi == -1){
// 			printf("error variable not found\n");
			exit (0);
		}
		else{
			op4=strtok(NULL,"]");
			thesi_argument = search_var(var,op4);
			if(thesi_argument == -1){
// 				printf("error variable not found\n");
				exit (0);
			}
			else{
				value_argument = var[thesi_argument].var_value;
			}
			value_op2 = var_table[thesi].var_value[value_argument];
		}
	}
	return value_op2;
}

struct return_value return_value_var(struct variable *var,struct table_variable *var_table,int check_type_op1, char *op1,int value_op2, int first_time){
	
	int thesi_argument,position,lenght,value_argument;
	char *op4;
	struct return_value new_address;
	
	if(check_type_op1 == 2){
		var = put_var(var,op1,value_op2,first_time);
	}
	else if(check_type_op1 == 3){
		op4=strchr(op1,'[');
		lenght=strlen(op4);
		op4[lenght-1]='\0';
		position=atoi(op4+1);
		op1=strtok(op1,"[");
		var_table = put_var_table(var_table,op1,value_op2,position,first_time);
	}
	else if(check_type_op1 == 4){
		op4=strchr(op1,'[');
		lenght=strlen(op4);
		op4[lenght-1]='\0';
		thesi_argument= search_var(var,op4+1);
		if(thesi_argument == -1){
// 			printf("error variable not found\n");
			exit (0);
		}
		else{
			value_argument = var[thesi_argument].var_value;
		}
		op1=strtok(op1,"[");
		var_table = put_var_table(var_table,op1,value_op2,value_argument,first_time);
	}
	
	new_address.var =var;
	new_address.table_variable =var_table;
	
	return new_address;
	
}

int read_line(int fd,char *line){
	
	int check=0, i=0;
	char charachter;
	
	while(1){
		check=read(fd, &charachter, sizeof(char));
		if (check==-1){
			printf("error in read\n");
			exit(0);
		}
		else if(charachter=='\n'){
			line[i]='\0';
			break;
		}
		else{
			line[i]=charachter;
			i++;
		}
	}
	
	return 0;
	
}

