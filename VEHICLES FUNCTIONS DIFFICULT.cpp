#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FN "C:\\Users\\Kaisha Inocencio\\Documents\\FUNCTIONS\\service.txt"
#define TEMP "C:\\Users\\Kaisha Inocencio\\Documents\\FUNCTIONS\\temp.txt"

struct Vehicle {
    char plateNumber[80];
    char ownerName[80];
    char serviceType[80];
    struct ServiceRecord {
        char date[80];
        float serviceCost;
    } sr;
};

void displayVehicle(struct Vehicle cars[], int size) {
    printf("\n=====LISTED VEHICLES=====\n");
    for (int i = 0; i < size; i++) {
        if (cars[i].sr.serviceCost > 500) {
            printf("\nPlate Number: %s\n", cars[i].plateNumber);
            printf("Owner Name: %s\n", cars[i].ownerName);
            printf("Service Type: %s\n", cars[i].serviceType);
            printf("Date: %s\n", cars[i].sr.date);
            printf("Service Cost: %.2f\n", cars[i].sr.serviceCost);
        }
    }
}

int main() {
    char choice;
    FILE *fp, *fp2, *temp;
    struct Vehicle cars[5];

    printf("\nVEHICLE SERVICE MANAGEMENT SYSTEM\n");

  	fp = fopen(FN, "w");
    if (!fp) {
    printf("Error opening file!\n");
    return 1;
    }

    for (int a = 0; a < 5; a++) {
        printf("Vehicle #%d\n", a + 1);
        printf("Input Plate Number: ");
        scanf("%s", cars[a].plateNumber);
        printf("Input Owner Name: ");
        scanf(" %[^\n]", cars[a].ownerName);
        printf("Input Service Type: ");
        scanf(" %[^\n]", cars[a].serviceType);
        printf("Input Date: ");
        scanf(" %[^\n]", cars[a].sr.date);
        printf("Input Service Cost: ");
        scanf("%f", &cars[a].sr.serviceCost);
        fprintf(fp, "%s,%s,%s,%s,%.2f\n", cars[a].plateNumber, cars[a].ownerName, cars[a].serviceType, cars[a].sr.date, cars[a].sr.serviceCost);
    }
    fclose(fp);

    displayVehicle(cars, 5);

    do {
        printf("\nVEHICLE SERVICE MANAGEMENT SYSTEM\n");
        printf("1.Read Records\n2.Search\n3.Exit\n");
        printf("Select One: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1': {
                fp = fopen(FN, "r");
                if (!fp) {
                    printf("No record found!\n");
                    break;
                }
                struct Vehicle tempCar;
                printf("%-15s %-15s %-15s %-15s %-15s\n",
                       "Plate Number", "Owner Name", "Service Type", "Date", "Service Cost");
                while (fscanf(fp, " %[^,],%[^,],%[^,],%[^,],%f",tempCar.plateNumber, tempCar.ownerName, tempCar.serviceType, tempCar.sr.date, &tempCar.sr.serviceCost) == 5) {
                    printf("%-15s %-15s %-15s %-15s %-15.2f\n",
                           tempCar.plateNumber, tempCar.ownerName, tempCar.serviceType,
                           tempCar.sr.date, tempCar.sr.serviceCost);
                }
                fclose(fp);
                break;
            }

            case '2': {
                fp = fopen(FN, "r");
                temp = fopen(TEMP, "w");
                if (!fp || !temp) {
                    printf("Error opening file!\n");
                    break;
                }
                char searchPlate[80];
                printf("\nSEARCH\n");
                printf("Search by plate number: ");
                scanf("%s", searchPlate);
                int found = 0;
                char pn[80], on[80], st[80], dt[80];
                float sc;
                while (fscanf(fp, " %[^,],%[^,],%[^,],%[^,],%f", pn, on, st, dt, &sc) == 5) {
                    if (strcmp(pn, searchPlate) == 0) {
                        found = 1;
                        printf("Owner Name: %s\n", on);
                        printf("Service Type: %s\n", st);
                        printf("Date: %s\n", dt);
                        printf("Service Cost: %.2f\n", sc);
                    }
                    fprintf(temp, "%s,%s,%s,%s,%.2f\n", pn, on, st, dt, sc);
                }
                fclose(fp);
                fclose(temp);
                remove(FN);
                rename(TEMP, FN);
                if (!found)
                    printf("Record not found\n");
                break;
            }

            case '3':
                printf("Exiting program...\n");
                exit(0);
        }
    } while (1);

    return 0;
}
