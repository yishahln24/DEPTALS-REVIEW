#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	}
	displayStudents(record,5);
return 0;
}

