#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FN "C:\\Users\\Kaisha Inocencio\\Documents\\FUNCTIONS\\grades.txt"
#define TEMP "C:\\Users\\Kaisha Inocencio\\Documents\\FUNCTIONS\\temp.txt"

struct Student{
	char studentID [10];
	char name[80];
	char course[80];
	struct GradeRecord{
	char subject[80];
	float grade;
	}grd;
};


void displayStudents(struct Student record[], int size){	
	printf("\nSTUDENTS WITH GRADES ABOVE 85\n");
	for(int i = 0; i<5; i++){
		if(record[i].grd.grade > 85.00){
		printf("Student ID: %s\n", record[i].studentID);
		printf("Student Name: %s\n", record[i].name);
		printf("Student Course: %s\n", record[i].course);
		printf("Subject: %s\n", record[i].grd.subject);
		printf("Grade: %.2f\n", record[i].grd.grade);
		}printf("\n");
	}
}

int main(){
	struct Student record[5];
	char choice;
	char search[80];
				char tid [10];
				char tname[80];
				char tcourse[80];
				char tsub[80];
				float tgrade;
				int found = 0;
	
	FILE *fp, *fp2, *temp;
	fp = fopen(FN,"w");
		if(!fp){
		printf("error");
		return 1;	
		}
	printf("\nSTUDENT GRADE MANAGEMENT SYSTEM\n");
	for(int i = 0; i<5; i++){
		printf("STUDENT %d\n", i+1);
		printf("Enter Student ID: ");
		scanf("%s", record[i].studentID);
		printf("Enter Student Name: ");
		scanf(" %[^\n]", record[i].name);
		printf("Enter Course: ");
		scanf(" %[^\n]",record[i].course);
		printf("Enter Subject: ");
		scanf(" %[^\n]", record[i].grd.subject);
		printf("Enter Grade: ");
		scanf("%f", &record[i].grd.grade);
		fprintf(fp, "%s,%s,%s,%s,%.2f\n", record[i].studentID,record[i].name,record[i].course,record[i].grd.subject,record[i].grd.grade);
	}fclose(fp);
	
	displayStudents(record,5);
	
	do{
		printf("1.Save\n2.Read\n3.Search\n4.Exit\n");
		printf("Select one: ");
		scanf(" %c", &choice);
		
		switch(choice){
			case '1':
				fp = fopen(FN, "r");
				if(!fp){
					printf("Error opening file\n");
					break;
				}
				printf("Saved successfully\n");
				fclose(fp);
				break;
			case '2':	
				fp = fopen(FN, "r");
				if(!fp){
					printf("Error opening file\n");
					break;
				}
				struct Student tempRecord;
				while(fscanf(fp, " %[^,],%[^,],%[^,],%[^,],%f",tempRecord.studentID,tempRecord.name,tempRecord.course,tempRecord.grd.subject,&tempRecord.grd.grade)==5){
					printf("%-15s %-15s %-15s %-15s %-15.2f\n",tempRecord.studentID,tempRecord.name,tempRecord.course,tempRecord.grd.subject,tempRecord.grd.grade);
				}
				fclose(fp);
				break;
			case '3':
				fp = fopen(FN, "r");
				temp = fopen(TEMP, "w");
				if(!fp||!temp){
					printf("Error opening file\n");
					break;
				}
				
				printf("Enter Student ID: ");
				scanf(" %[^\n]", search);
				while(fscanf(fp, " %[^,],%[^,],%[^,],%[^,],%f",tid,tname,tcourse,tsub, &tgrade)==5){
					if(strcmp(tid,search)==0){
						found = 1;
						printf("Student ID: %s\n", tid);
						printf("Student Name: %s\n", tname);
						printf("Student Course: %s\n", tcourse);
						printf("Subject: %s\n",tsub);
						printf("Grade: %.2f\n", tgrade);
					}fprintf(temp,"%s,%s,%s,%s,%.2f\n",tid,tname,tcourse,tsub,tgrade);
				}
				fclose(fp);
				fclose(temp);
				remove(FN);
				rename(TEMP, FN);
				if(!found){
					printf("Record not found\n");
				}
				break;
			case '4':
				printf("Thank you!");
				exit(0);
				
		}
	}while(1);
return 0;
}

