#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FN "C:\\Users\\Kaisha Inocencio\\Documents\\FUNCTIONS\\salesman.txt"
#define TEMP "C:\\Users\\Kaisha Inocencio\\Documents\\FUNCTIONS\\temp.txt"

void initFile();
void comms();
void addsm();
void editsm();
void delsm();
void viewsm();
void exitsm();

int main(){
	char choice, confirm;
	
	initFile();
	
	do{
		printf("\nSALESMAN RECORD\n");
		printf("1.[A]dd\n2.[E]dit\n3.[D]elete\n4.[V]iew\n5.E[X]it\n");
		printf("Please select one: ");
		scanf(" %c", &choice);
		
		switch(choice){
			case 'A':
			case 'a':
				addsm();
				break;
			case 'E':
			case 'e':
				editsm();
				break;
			case 'D':
			case 'd':
				delsm();
				break;
			case 'V':
			case 'v':
				viewsm();
			break;
			case 'X':
			case 'x':
				printf("Are you sure [Y/N]? ");
				scanf(" %c", &confirm);
				if(confirm=='Y'|| confirm == 'y'){
					printf("Thank you!");
					exit(0);
				}else{
					printf("Exit Cancelled\n");
				}
			break;
		}//switch
	}while(1);
}


void initFile(){
	FILE *fp, *fp2;
	fp = fopen(FN, "w");
	if (fp != NULL){
		fp2 = fopen(FN, "w");
		fprintf(fp2, "QC-00004-A,Bruce Wayne,65000.00,32500.00,0.50\n");
        fprintf(fp2, "MN-00002-A,John Doe,10000.00,1500.00,0.15\n");
        fprintf(fp2, "TG-00005-B,Edward Collins,22500.00,6750.00,0.30\n");
        fprintf(fp2, "QC-00001-C,Harry Potter,30000.00,25000.00,0.00\n");
        fprintf(fp2, "MN-00001-B,Charles Xavier,12000.00,2400.00,0.20\n");
        fprintf(fp2, "QC-00001-A,Bella Swan,18000.00,4500.00,0.25\n");
        fclose(fp2);
	}
	fclose(fp);
}

void comms(double total, float *rate, float *comm){
	if (total <= 5000.00){
		*rate = 0.10f;
	}else if(total <=10000.00){
		*rate = 0.15f;
	}else if(total <=15000.00){
		*rate = 0.20f;
	}else if(total <=20000.00){
		*rate = 0.25f;
	}else if(total <=25000.00){
		*rate = 0.30f;
	}else{
		*rate =0.50f;
	}
	*comm = total * (*rate);
	if(total > 25000.00 && *comm < 30000.00){
		*comm = 30000.00f;
	}
}

void addsm(){
	FILE *fp;
	fp = fopen(FN, "a");
	if (!fp){
		printf("Error opening file!");
		return;
	}
	
	char sm_num[15], sm_name[80];
	float fst, s, t, frth;
	double ttl_sales;
	float comm, comm_rate;
	
	printf("Enter salesman number: ");
	scanf("%s", sm_num);
	printf("Enter salesman name: ");
	scanf(" %[^\n]", sm_name);
	printf("Enter First Quarter Sales: ");
	scanf("%f", &fst);
	printf("Enter Second Quarter Sales: ");
	scanf("%f", &s);
	printf("Enter Third Quarter Sales: ");
	scanf("%f", &t);
	printf("Enter Fourth Quarter Sales: ");
	scanf("%f", &frth);
	
	ttl_sales = fst + s + t + frth;
	comms(ttl_sales,&comm_rate,&comm);
	
	printf("Total Sales: %.2f\n", ttl_sales);
	printf("Commission: %.2f\n", comm);
	printf("Rate: %.0f%%\n", comm_rate*100);
	
	fprintf(fp, "%s,%s,%.2f,%.2f,%.2f\n", sm_num, sm_name, ttl_sales, comm, comm_rate);
	fclose(fp);
	printf("New Salesman Added\n");	
}

void editsm(){
	FILE *fp, *temp;
	fp = fopen(FN, "r");
	temp = fopen(TEMP, "w");
	if(!fp||!temp){
		printf("Error opening file");
		return;
	}
	char sm_num[15];
	char num[15], name[80];
	double total;
	float commission, rate, first, second, third, fourth;
	int found = 0;
	
	printf("Enter Salesman Number to Edit: ");
	scanf("%s", sm_num);
	
	while(fscanf(fp, " %[^,],%[^,],%lf,%f,%f", num,name,&total,&commission,&rate)==5){
		if(strcmp(num,sm_num)==0){
			found =1;
			printf("Salesman Name: %s\n", name);
			printf("Total Sales: %.2f\n", total);
			printf("Commission: %.2f\n", commission);
			printf("INPUT NEW SALES\n");
			printf("First Quarter: ");
			scanf("%f", &first);
			printf("Second Quarter: ");
			scanf("%f", &second);
			printf("Third Quarter: ");
			scanf("%f", &third);
			printf("Fourth Quarter: ");
			scanf("%f", &fourth);
			
			total = first + second + third + fourth;
			comms(total, &rate, &commission);
			
			printf("Total Sales: %.2f\n", total);
			printf("Commission: %.2f\n", commission);
			printf("Rate: %.0f%%\n", rate*100);
		}
		fprintf(temp, "%s,%s,%.2f,%.2f,%.2f\n", num, name, total, commission, rate);
	}
	fclose(fp);
	fclose(temp);
	remove(FN);
	rename(TEMP, FN);
	
	if(!found){
		printf("Record not found\n");
		return;
	}else{
		printf("Salesman Updated\n");
	}
}

void delsm(){
	FILE *fp, *temp;
	fp = fopen(FN, "r");
	temp = fopen(TEMP, "w");
	if(!fp||!temp){
		printf("Error opening file\n");
		return;
	}
	char sm_num[15];
	char num[15], name[80];
	double total;
	float commission, rate;
	char del;
	int found = 0;
	
	printf("Enter Salesman Number to Delete: ");
	scanf("%s", sm_num);
	
	while(fscanf(fp," %[^,],%[^,],%lf,%f,%f", num, name, &total, &commission,&rate)==5){
		if(strcmp(num,sm_num)==0){
			found = 1;
			printf("Salesman Name: %s\n", name);
			printf("Total Sales: %.2f\n", total);
			printf("Commission: %.2f\n", commission);
			printf("Rate: %.0f%%\n", rate*100);
			printf("Are you sure you want to delete? [Y/N]: ");
			scanf(" %c", &del);
			if(del == 'y'|| del == 'Y'){
				printf("Salesman Deleted\n");
				continue;
			}else{
				printf("Salesman Not Deleted\n");
			}
		}fprintf(temp, "%s,%s,%.2f,%.2f,%.2f\n", num, name, total, commission, rate);
	}
	fclose(fp);
	fclose(temp);
	remove(FN);
	rename(TEMP, FN);
	if (!found){
		printf("Salesman not found\n");
		return;
	}
}

void viewsm(){
	FILE *fp = fopen(FN, "r");
	if(!fp){
		printf("Error opening file");
		return;
	}
	char sm_num[15], sm_name[80];
	float comm, comm_rate;
	double ttl_sales;
	
	printf("%-15s %-15s %-15s %-15s %-15s\n", "SM Number", "SM Name", "Total Sales", "Commissions", "Rate");
	while(fscanf(fp, " %[^,],%[^,],%lf,%f,%f", sm_num,sm_name,&ttl_sales,&comm,&comm_rate)==5){
		printf("%-15s %-15s %-15.2f %-15.2f %.0f%%\n", sm_num,sm_name,ttl_sales,comm,comm_rate*100);
	}
	fclose(fp);
}

