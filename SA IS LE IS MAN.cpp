#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fp, *fp2, *temp;
    char sm_num[15];
    char sm_name[80];
    double ttl_sales;
    float comm;
    float comm_rate;
    char choice;
    char confirm;
    char del;
    float fst, s, t, frth;  // FIX: match scanf %f

    int found;
    char num[15], name[80];
    double total;
    float commission, first, second, third, fourth, rate;

    fp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\salesman.txt", "w");
    if(fp != NULL){
        fp2 = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\salesman.txt", "w");
        fprintf(fp2, "QC-00004-A,Bruce Wayne,65000.00,32500.00,0.50\n");
        fprintf(fp2, "MN-00002-A,John Doe,10000.00,1500.00,0.15\n");
        fprintf(fp2, "TG-00005-B,Edward Collins,22500.00,6750.00,0.30\n");
        fprintf(fp2, "QC-00001-C,Harry Potter,30000.00,25000.00,0.00\n");
        fprintf(fp2, "MN-00001-B,Charles Xavier,12000.00,2400.00,0.20\n");
        fprintf(fp2, "QC-00001-A,Bella Swan,18000.00,4500.00,0.25\n");
        fclose(fp2);
    }
    fclose(fp);

    do {
        printf("\n=====SALESMAN=====\n");
        printf("1. [A]dd\n2. [E]dit\n3. [D]elete\n4. [V]iew\n5. E[X]it\n");
        printf("Please select one to perform: ");
        scanf(" %c", &choice);

        switch(choice){

        case 'A':
        case 'a':
            fp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\salesman.txt", "a");
            if (!fp){ printf("Error opening file!\n"); 
			break;
			}
            printf("Enter Salesman Number: ");
            scanf("%s", sm_num);
            printf("Enter Salesman Name: ");
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

            if(ttl_sales <= 5000.00)       comm_rate = 0.10f;
            else if(ttl_sales <= 10000.00) comm_rate = 0.15f;
            else if(ttl_sales <= 15000.00) comm_rate = 0.20f;
            else if(ttl_sales <= 20000.00) comm_rate = 0.25f;
            else if(ttl_sales <= 25000.00) comm_rate = 0.30f;
            else                           comm_rate = 0.50f;

            comm = ttl_sales * comm_rate;
            if(ttl_sales > 25000.00 && comm < 30000.00)
                comm = 30000.00f;

            printf("Total Sales: %.2f\n", ttl_sales);
            printf("Commission: %.2f\n", comm);
            printf("Rate: %.0f%%\n", comm_rate * 100);
            fprintf(fp, "%s,%s,%.2f,%.2f,%.2f\n", sm_num, sm_name, ttl_sales, comm, comm_rate);
            fclose(fp);
            printf("New Salesman Added!\n");
            break;

        case 'E':
        case 'e':
            fp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\salesman.txt", "r");
            temp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\temp.txt", "w");
            if(!fp || !temp){ 
			printf("Error opening file!\n");
			break; }
            printf("Enter Salesman Number to edit: ");
            scanf("%s", sm_num);
            found = 0;

            while(fscanf(fp, " %14[^,],%79[^,],%lf,%f,%f",num, name, &total, &commission, &rate) == 5){
                if(strcmp(num, sm_num) == 0){
                    found = 1;
                    printf("Salesman Name: %s\n", name);
                    printf("Total Sales: %.2f\n", total);
                    printf("Commission: %.2f\n", commission);
                    printf("Input new sales:\n");
                    printf("First Quarter: ");  scanf("%f", &first);
                    printf("Second Quarter: "); scanf("%f", &second);
                    printf("Third Quarter: ");  scanf("%f", &third);
                    printf("Fourth Quarter: "); scanf("%f", &fourth);
                    total = first + second + third + fourth;

                    if(total <= 5000.00)       rate = 0.10f;
                    else if(total <= 10000.00) rate = 0.15f;
                    else if(total <= 15000.00) rate = 0.20f;
                    else if(total <= 20000.00) rate = 0.25f;
                    else if(total <= 25000.00) rate = 0.30f;
                    else                       rate = 0.50f;

                    commission = total * rate;
                    if(total > 25000.00 && commission < 30000.00)
                        commission = 30000.00f;

                    printf("Total Sales: %.2f\n", total);
                    printf("Commission: %.2f\n", commission);
                    printf("Rate: %.0f%%\n", rate * 100);
                }
                fprintf(temp, "%s,%s,%.2f,%.2f,%.2f\n", num, name, total, commission, rate);
            }
            fclose(fp);
            fclose(temp);
            remove("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\salesman.txt");
            rename("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\temp.txt",
                   "C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\salesman.txt");
            if(!found){
            	printf("Salesman not found!\n");
			}
            else{
            	printf("Salesman updated!\n");	
			}
            break;

        case 'D':
        case 'd':
            fp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\salesman.txt", "r");
            temp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\temp.txt", "w");
            if(!fp || !temp){ 
				printf("Error opening file!\n");
				break;
			}
            printf("Enter Salesman Number to delete: ");
            scanf(" %14s", sm_num);
            found = 0;
            
            while(fscanf(fp, " %14[^,],%79[^,],%lf,%f,%f",
                         num, name, &total, &commission, &rate) == 5){
                if(strcmp(num, sm_num) == 0){
                    found = 1;
                    printf("Salesman Name: %s\n", name);
                    printf("Total Sales: %.2f\n", total);
                    printf("Commission: %.2f\n", commission);
                    printf("Do you really want to delete? [Y/N]: ");
                    scanf(" %c", &del);
                    if(del == 'Y' || del == 'y'){
                        printf("Salesman Deleted.\n");
                        continue; 
                    } else {
                        printf("Salesman not deleted.\n");
                    }
                }
                fprintf(temp, "%s,%s,%.2f,%.2f,%.2f\n", num, name, total, commission, rate);
            }
            fclose(fp);
            fclose(temp);
            remove("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\salesman.txt");
            rename("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\temp.txt",
                   "C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\salesman.txt");
            if(!found)
			{
			printf("Salesman not found!\n");
			}
            break;

        case 'V':
        case 'v':
            fp = fopen("C:\\Users\\Kaisha Inocencio\\Documents\\PRACTICE\\salesman.txt", "r");
            if(!fp){ printf("Error opening file!\n"); break; }
            printf("%-15s %-20s %-15s %-15s %-10s\n",
                   "SM Number", "SM Name", "Total Sales", "Commission", "Rate");
            while(fscanf(fp, " %14[^,],%79[^,],%lf,%f,%f", sm_num, sm_name, &ttl_sales, &comm, &comm_rate) == 5){
                printf("%-15s %-20s %-15.2f %-15.2f %.0f%%\n",
                       sm_num, sm_name, ttl_sales, comm, comm_rate * 100);
            }
            fclose(fp);
            break;

        case 'X':
        case 'x':
            printf("Are you sure you want to exit? [Y/N]: ");
            scanf(" %c", &confirm);
            if(confirm == 'Y' || confirm == 'y'){
                printf("Thank you!\n");
                exit(0);
            } else {
                printf("Exit cancelled.\n");
            }
            break;

        default:
            printf("Choice is invalid.\n");
        }

    } while(1);

    return 0;
}