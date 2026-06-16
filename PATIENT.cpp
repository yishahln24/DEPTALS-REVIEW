#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FN "C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\hp.txt"
#define TEMP "C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\temp.txt"
struct hp{
	char pname[80];
	char pid[80];
	int age;
	float amt;
}pt;

int main(){
	FILE *fp, *fp2, *temp;
	fp = fopen(FN, "r");
		if(fp !=NULL){
			fp2 = fopen(FN, "w");
			fclose(fp2);
		}
	fclose(fp);
	int np;
	int choice, found;
	char tid[80], tname[80];
	int tage;
	float tamt;
	char confirm;
	float maxamt=0;
	char maxname[80], maxid[80];
	int maxage;
			
	struct hp pt;
	printf("\n===HOSPITAL RECORD MANAGEMENT===\n");
	printf("Number of Patients: ");
	scanf("%d", &np);
	for(int a=0;a<np; a++){
		fp=fopen(FN, "a");
		printf("===PATIENT %d===\n",a+1);
		printf("Patient Name: ");
		scanf(" %[^\n]",pt.pname);
		printf("Patient ID: ");
		scanf(" %[^\n]", pt.pid);
		printf("Age: ");
		scanf("%d", &pt.age);
		printf("Bill Amount: ");
		scanf("%f", &pt.amt);
		fprintf(fp, "%s,%s,%d,%.2f\n", pt.pname, pt.pid, pt.age, pt.amt);
		fclose(fp);
	}
	
	do{
		printf("\n===HOSPITAL RECORD MANAGEMENT===\n");
		printf("1.Add\n2.View\n3.Delete\n4.Update Bill\n5.Highest Bill\n6.Exit\n");
		printf("Choose one option: ");
		scanf("%d", &choice);
		
		switch (choice){
			case 1: //add
				fp=fopen(FN,"a");
				if(!fp){
					printf("Error opening file!\n");
					break;
				}
				printf("\n===NEW PATIENT===\n");
				printf("Enter Patient Name: ");
				scanf(" %[^\n]", pt.pname);
				printf("Enter Patient ID: ");
				scanf(" %[^\n]",pt.pid);
				printf("Enter Patient Age: ");
				scanf("%d", &pt.age);
				printf("Enter Bill Amount: ");
				scanf("%f", &pt.amt);
				fprintf(fp,"%s,%s,%d,%.2f\n", pt.pname,pt.pid,pt.age, pt.amt);
				fclose(fp);
				printf("New Patient Added.\n");
			break;
			
			case 2: //view
			fp=fopen(FN, "r");
			if(!fp){
				printf("Error opening file!\n");
				break;
			}
			printf("%-15s %-15s %-15s %-15s\n", "Name", "ID", "Age", "Bill Amount");
			while(fscanf(fp," %[^,],%[^,],%d,%f",pt.pname, pt.pid, &pt.age, &pt.amt)==4){
				printf("%-15s %-15s %-15d %-15.2f\n", pt.pname, pt.pid, pt.age, pt.amt);
			}
			fclose(fp);
			break;
			
			case 3: //delete
			fp=fopen(FN,"r");
			temp=fopen(TEMP, "w");
			if(!fp||!temp){
				printf("Error opening file\n");
				break;
			}
			printf("\n===DELETE PATIENT RECORD===\n");
			printf("Enter Patient ID: ");
			scanf(" %[^\n]", pt.pid);
			found = 0;
			while(fscanf(fp, " %[^,],%[^,],%d,%f", tname,tid,&tage,&tamt)==4){
				if(strcmp(tid,pt.pid)==0){
					found = 1;
					printf("Are you sure you want to delete? [Y/N]: ");
					scanf(" %c", &confirm);
					if(confirm=='Y'|| confirm=='y'){
						printf("Record deleted\n");
						continue;
					}else{
						printf("Record not deleted\n");
					}
				}
				fprintf(temp, "%s,%s,%d,%.2f\n",tname,tid,tage,tamt);
			}
			fclose(fp);
			fclose(temp);
			remove(FN);
			rename(TEMP,FN);
			if (!found){
				printf("Record not found!\n");
			}
			break;
			
			case 4: //search and update
			fp=fopen(FN, "r");
			temp=fopen(TEMP, "w");
			if(!fp||!temp){
				printf("Error opening file!");
				break;
			}
			printf("\n===UPDATE AMOUNT BILL===\n");
			printf("Enter Patient ID: ");
			scanf(" %[^\n]", pt.pid);
			found = 0;
			while(fscanf(fp," %[^,],%[^,],%d,%f", tname, tid, &tage, &tamt) == 4){
				if(strcmp(tid,pt.pid)==0){
					found = 1;
					printf("Patient Name: %s\n", tname);
					printf("Patient Age: %d\n", tage);
					printf("Update Bill Amount: ");
					scanf("%f", &tamt);
				}
				fprintf(temp,"%s,%s,%d,%.2f\n",tname, tid, tage, tamt);
			}
			fclose(fp);
			fclose(temp);
			remove(FN);
			rename(TEMP, FN);
			if (!found){
				printf("Record not found\n");
			}else{
				printf("BILL AMOUNT UPDATED\n");
			}
			break;
			
			case 5: //highest
			fp = fopen(FN, "r");
			if(!fp){
				printf("Error opening file!\n");
				break;
			}
			
			while(fscanf(fp, " %[^,],%[^,],%d,%f", tname,tid,&tage,&tamt)==4){
				if(tamt>maxamt){
					maxamt = tamt;
					strcpy(maxid,tid);
					strcpy(maxname,tname);
					maxage=tage;
				}
			}
			fclose(fp);
			
			if(maxamt==0){
				printf("No records found\n");
			}else{
				printf("\n===HIGHEST BILL===\n");
				printf("Patient Name: %s\n", maxname);
				printf("Patient ID: %s\n", maxid);
				printf("Patient Age: %d\n", maxage);
				printf("Bill Amount: %.2f\n", maxamt);
			}
			break;
			
			case 6: //exit
				printf("Are you sure you want to exit? [Y/N]: ");
				scanf(" %c", &confirm);
				if(confirm=='Y'|| confirm =='y'){
					printf("Thank you!");
					exit(0);
				}else{
					printf("Exit cancelled\n");
					continue;
				}
			break;
			
			default:
				printf("Invalid input, please try again.\n");
		
		}//switch
		
	}while(1);
return 0;
}