#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILENAME "C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\grade.txt"
#define TEMP "C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\temp.txt"

int main(){
	FILE *fp, *fp2, *temp;
	char stdno[10], stdname[80], sub[80];
	float midg, fing, sis;
	char choice;
	char no[10], name[80], subject[80];
	float mid, fin, sisg;
	int found;
	char del;
	char confirm; 
	
	fp = fopen(FILENAME, "r");
		if (fp != NULL){
			fp2 = fopen(FILENAME, "w");
			fprintf(fp2, "ABC10,Colarina,Prog2,1.75,1.0,1.5\n");
			fprintf(fp2,"ABC12,Brences,Prog2,2.0,1.0,1.75\n");
			fclose(fp2);
		}
	fclose(fp);

do{
	printf("\n=====GRADE MANAGEMENT SYSTEM=====\n");
	printf("1. [A]dd\n2. [E]dit\n3. [D]elete\n4. [V]iew\n5. E[X]it\n");
	printf("Please Select: ");
	scanf(" %c", &choice);
	
	switch(choice){
		case 'A':
		case 'a':
			fp = fopen(FILENAME, "a");
			if (!fp){
				printf("Error opening file!\n");
				break;
			}
			printf("ADD NEW STUDENT\n"); 
			printf("Student Number: ");
			scanf("%s", stdno);
			printf("Student Name: ");
			scanf("%s", stdname);
			printf("Subject: ");
			scanf("%s", sub);
			printf("MidGrade: ");
			scanf("%f", &midg);
			printf("FinalGrade: ");
			scanf("%f", &fing);
			sis = (midg+fing)/2;
			if(sis < 1.25){
				sis = 1.00;
			}else if(sis < 1.5){
				sis = 1.25;
			}else if(sis <1.75){
				sis = 1.50;
			}else if(sis <2.00){
				sis = 1.75;
			}else if(sis <2.25){
				sis = 2.00;
			}else if(sis <2.50){
				sis = 2.25;
			}else if(sis < 2.75){
				sis = 2.50;
			}else if(sis < 3.00){
				sis = 2.75;
			}else if(sis < 3.25){
				sis = 3.00;
			}else if(sis < 3.50){
				sis = 3.25;
			}else if (sis < 3.75){
				sis = 3.50;
			}else if (sis < 4.00){
				sis = 3.75;
			}else if (sis <4.25){
				sis = 4.00;
			}else if (sis <4.50){
				sis = 4.25;
			}else if (sis <4.75){
				sis = 4.50;
			}else if (sis < 5.00){
				sis = 4.75;
			}else{
				sis = 5.00;
			}
			fprintf(fp, "%s,%s,%s,%.2f,%.2f,%.2f", stdno, stdname, sub, midg, fing, sis);
			fclose(fp);
				printf("NEW STUDENT ADDED\n");
		break;
		
		case 'E':
		case 'e':
			fp = fopen(FILENAME, "r");
			temp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\temp.txt", "w");
			if (!fp||!temp){
				printf("Error opening file!\n");
				break;
			}
			printf("Enter Student Number: ");
			scanf("%s", stdno);
			printf("Enter Subject: ");
			scanf("%s", sub);
			found = 0;
			
			while(fscanf(fp, " %[^,],%[^,],%[^,],%f,%f,%f",no,name,subject,&mid,&fin,&sisg)==6){
				if(strcmp(no, stdno) == 0 && strcmp(subject, sub)==0){
					found = 1;
					printf("%-15s %-15s %-15s %-15s %-15s %-15s\n", "Student Number", "Student Name", "Subject", "MidGrade", "FinGrade", "SIS");
					printf("%-15s %-15s %-15s %-15.2f %-15.2f %-15.2f", no, name, subject, mid, fin, sisg);
					printf("\nINPUT NEW STUDENT INFORMATION\n");
					printf("MidGrade: ");
					scanf("%f", &mid);
					printf("FinalGrade: ");
					scanf("%f", &fin);
					sisg = (mid+fin)/2;
					if(sisg < 1.25){
						sisg = 1.00;
					}else if(sisg < 1.5){
						sisg = 1.25;
					}else if(sisg <1.75){
						sisg = 1.50;
					}else if(sisg <2.00){
						sisg = 1.75;
					}else if(sisg <2.25){
						sisg = 2.00;
					}else if(sisg <2.50){
						sisg = 2.25;
					}else if(sisg < 2.75){
						sisg = 2.50;
					}else if(sisg < 3.00){
						sisg = 2.75;
					}else if(sisg < 3.25){
						sisg = 3.00;
					}else if(sisg < 3.50){
						sisg = 3.25;
					}else if (sisg < 3.75){
						sisg = 3.50;
					}else if (sisg < 4.00){
						sisg = 3.75;
					}else if (sisg <4.25){
						sisg = 4.00;
					}else if (sisg <4.50){
						sisg = 4.25;
					}else if (sisg <4.75){
						sisg = 4.50;
					}else if (sisg < 5.00){
						sisg = 4.75;
					}else{
						sisg = 5.00;
					} 	
				}
				fprintf(temp, "%s,%s,%s,%f,%f,%f", no,name,subject,mid,fin,sisg);
			}
			
			fclose(fp);
			fclose(temp);
			remove(FILENAME);
			rename(TEMP,FILENAME);
			
			if (!found){
				printf("Student Not Found\n");
				continue;
			}else{
				printf("Student Record Updated\n");
			}
			break;
		
		case 'D':
		case 'd':
			fp = fopen(FILENAME, "r");
			temp = fopen(TEMP, "w");
			if(!fp||!temp){
				printf("Error opening file");
			}
			printf("Enter Student Number: ");
			scanf("%s", stdno);
			printf("Enter Subject: ");
			scanf("%s", sub);
			found = 0;
			
			while(fscanf(fp, " %[^,],%[^,],%[^,],%f,%f,%f", no,name,subject,&mid,&fin,&sisg)==6){
				if(strcmp(no,stdno)==0 && strcmp(subject,sub)==0){
					found = 1;
					printf("%-15s %-15s %-15s %-15s %-15s %-15s\n", "Student Number", "Student Name", "Subject", "MidGrade", "FinalGrade", "SIS");
					printf("%-15s %-15s %-15s %-15.2f %-15.2f %-15.2f\n", no,name,subject,mid,fin,sisg);
					printf("Are you sure you want to delete? [Y/N]: ");
					scanf(" %c", &del);
					if(del == 'Y'|| del == 'y'){
						printf("Student Record Deleted\n");
						continue;
					}else{
						printf("Student Record Not Deleted\n");
					}
				}fprintf(temp, "%s,%s,%s,%f,%f,%f", no, name, subject, mid,fin,sisg);
			}
			fclose(fp);
			fclose(temp);
			remove(FILENAME);
			rename(TEMP, FILENAME);
			
			if (!found){
				printf("Student Record NOT FOUND\n");
			}
			break;
			
		case 'V':
		case 'v':
			fp = fopen(FILENAME, "r");
			if (!fp){
				printf("Error opening file!\n");
				break;
			}
			printf("%-15s %-15s %-15s %-15s %-15s %-15s\n", "StudentNo","StudentName", "Subject", "MidGrade", "FinalGrade", "SIS");
			while(fscanf(fp, " %[^,],%[^,],%[^,],%f,%f,%f", stdno, stdname, sub, &midg, &fing, &sis) == 6){
				printf("%-15s %-15s %-15s %-15.2f %-15.2f %-15.2f\n", stdno, stdname, sub, midg, fing, sis);
			}
			fclose(fp);
		break;
		
		case 'X':
		case 'x':
			printf("Are you sure you want to exit? [Y/N]: ");
			scanf(" %c", &confirm);
			if(confirm == 'Y'|| confirm == 'y'){
				printf("Thank you!\n");
				exit(0);
			}else{
				printf("Exit cancelled\n");
			}
			break;
			
		default:
			printf("Invalid choice. Please try again.\n");
	}
}while(1);

return 0;	
}