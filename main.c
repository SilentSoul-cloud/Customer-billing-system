/*
 * Author: Arka Saha
 * Date: 2025-05-25
 * Description: This code is authored by Arka Saha.
 * Feel free to use or modify with proper attribution.
 *
 */

#include<stdio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

#define MAX_NAME_LENGTH 50
#define PHONE_LENGTH 15
#define MAX_CUSTOMER 100
#define MAGIC_HEADER "CUSTFILEv1"
#define SAVE_FILE "Customers_data.txt"


//TODO: make custom rate for Individual


struct customer{
    char name[MAX_NAME_LENGTH];
    char phone[PHONE_LENGTH];
    float usage;
    float total_bill;
};

float rate=1.12;
struct customer customers[MAX_CUSTOMER]; ///to store the customers data in array
int count=0; ///to track the customer number  ///customer count = count


void clear(){    ///clears the input buffer
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}

void add_customer(){ ///add customer data

    if(count<MAX_CUSTOMER){
        printf("\nEnter Name : ");
        fgets(customers[count].name,MAX_NAME_LENGTH,stdin);
        customers[count].name[strcspn(customers[count].name,"\n")]=0; ///remove newline

        if(strlen(customers[count].name)==0){
            printf("Name cannot be empty.\n");
            return;
        }

        char input[PHONE_LENGTH];
        printf("Phone number: ");
        fgets(input,PHONE_LENGTH,stdin);
        input[strcspn(input, "\n")]=0;
        for(int i=0; i<count; i++){
            if(strcmp(customers[i].phone,input)==0){
                printf("The Number is already in use\n\n");
                return;
            }
        }
        strcpy(customers[count].phone, input);

        printf("Enter mobile usage(in minutes) : "); ///user mobile usage
        if(scanf("%f",&customers[count].usage)!=1){
            printf("Invalid input. Mobile usage must be a number.\n");
            clear();
            return;
        }
        clear();

        printf("Customer added successfully!\n");
        customers[count].total_bill=customers[count].usage*rate;
        printf("\n");
        count++;
    }
    else{
        printf("!!!!Limit reached!!!!\n");
    }
    last_action("add_customer");
}


void list(){   ///all the customers
    for(int i=0; i<count-1; i++){
        for(int j=0; j<count-1-i; j++){
            if(strcasecmp(customers[j].name,customers[j+1].name)>0){
                struct customer temp= customers[j];
                customers[j]=customers[j+1];
                customers[j+1]=temp;
            }
        }
    }
    printf("\n%-15s %-15s %-20s %-10s\n","Name","Phone Number","Usage (in minutes)","Total Bill");
    for(int i=0; i<count; i++){
        printf("%-15s %-15s %-20.2f $%-10.2f\n",
               customers[i].name,
               customers[i].phone,
               customers[i].usage,
               customers[i].total_bill);
    }
    printf("\n");
    last_action("list");
}


void call_rate(){
    float new_rate;
    printf("Current call rate: $%.2f\n",rate);
    printf("Enter new rate: ");
    if (scanf("%f",&new_rate)!=1 || new_rate<=0){
        printf("Invalid input.\n");
        clear();
        return;
    }
    clear();
    rate=new_rate;
    for(int i=0; i<count; i++){
        customers[i].total_bill = customers[i].usage * (rate);
    }
    printf("Call rate updated successfully!\n");

    last_action("call_rate");
}


void update_customer(const char phone[]){
    int i;
    int f=0;
    for(i=0; i<count; i++){
        if(strcmp(customers[i].phone,phone)==0){
            f=1;
            break;
        }
    }
    if(!f){
        printf("Customer not found.\n\n");
        return;
    }
    char choice;
    printf("Do you want to update the phone number? (y/n): ");
    scanf(" %c", &choice);
    clear();

    if(choice=='y' || choice=='Y'){
        char new_phone[PHONE_LENGTH];
        printf("Enter new phone number: ");
        scanf("%14s",new_phone);
        clear();

        for(int j=0; j<count; j++){
            if(strcmp(customers[j].phone,new_phone)==0){
                printf("The new phone number is already in use.\n\n");
                return;
            }
        }

        strcpy(customers[i].phone, new_phone);
        printf("Phone number updated successfully.\n");
    }

    printf("Enter new mobile usage: ");
    if (scanf("%f", &customers[i].usage) != 1){
        printf("Invalid input. Mobile usage must be a number.\n\n");
        clear();
        return;
    }
    clear();

    customers[i].total_bill = customers[i].usage * rate;
    printf("Customer information updated.\n");

    last_action("update_customer");
}

void delete(const char phone[]){    ///Deleting customer information
    char confirm;
    printf("Are you sure you want to delete this record? (y/n): ");
    scanf(" %c", &confirm);
    clear();
    if(confirm!='y' && confirm!='Y'){
        printf("Deletion cancelled.\n");
        return;
    }
    for(int i=0;i<count;i++){
        if(strcmp(customers[i].phone,phone)==0){
            for(int j=i; j<count-1; j++){
                customers[j]=customers[j+1];
            }
            count--;
            printf("\nRecord deleted successfully!\n");
            return;
        }
    }
    printf("Invalid Number\n\n");

    last_action("delete");
}


void viewUser(const char phone[]){
    printf("\n%-15s %-15s %-20s %-10s\n","Name","Phone Number","Usage (in minutes)","Total Bill");
    for(int i=0;i<count; i++){
        if(strcmp(customers[i].phone,phone)==0){
            printf("%-15s %-15s %-20.2f $%-10.2f\n",
                   customers[i].name,
                   customers[i].phone,
                   customers[i].usage,
                   customers[i].total_bill);
            printf("\n");
            return;
        }
    }
    printf("\nRecord not found!\n");

    last_action("viewUser");
}


void revenue(){
    float total=0;
    for(int i=0;i<count;i++) total+=customers[i].total_bill;

    printf("\nTotal Revenue from all customers: $%.2f\n", total);
    last_action("revenue");
}


void CSV(){
    FILE*fp=fopen("customers.csv", "w");
    if(!fp){
        printf("Failed to export CSV.\n");
        return;
    }
    fprintf(fp,"Name,Phone Number,Usage (minutes),Total Bill ($)\n");
    for (int i=0;i<count;i++){
        fprintf(fp, "\"%s\",\"%s\",%.2f,%.2f\n",
                customers[i].name,
                customers[i].phone,
                customers[i].usage,
                customers[i].total_bill);
    }
    fclose(fp);
    printf("Customer list exported to 'customers.csv'\n");

    last_action("CSV");
}


void last_action(const char *action){
    FILE *fp=fopen("last_action.txt", "w");
    if(fp){
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        fprintf(fp, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
                t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                t->tm_hour, t->tm_min, t->tm_sec, action);

        fclose(fp);
    }
}



void display(){ ///Display the options to chose

    printf(" ======================================\n");
    printf("|      Customer Billing System        |\n");
    printf(" ======================================\n");
    printf("|  1. Add Customer                    |\n");
    printf("|  2. List                            |\n");
    printf("|  3. Update Call Rate                |\n");
    printf("|  4. Update Customer Info            |\n");
    printf("|  5. Delete Customer                 |\n");
    printf("|  6. View Customer                   |\n");
    printf("|  7. View Total Revenue              |\n");
    printf("|  8. Export to CSV                   |\n");
    printf("|  9. Backup Data                     |\n");
    printf("| 10. Exit                            |\n");
    printf(" ======================================\n");
}


void logData(const char *mg){
    FILE *logData_file=fopen("logData.txt", "a");
    if (logData_file!=NULL){
        time_t now=time(NULL);
        struct tm *t = localtime(&now);
        fprintf(logData_file, "[%04d-%02d-%02d %02d:%02d:%02d] %s\n",
                t->tm_year+1900, t->tm_mon+1, t->tm_mday,
                t->tm_hour, t->tm_min, t->tm_sec, mg);
        fclose(logData_file);
    }
}


void save(){
    FILE *fp=fopen( SAVE_FILE, "w");
    if (fp==NULL){
        printf("Error saving file.\n");
        return;
    }
    fprintf(fp,"%s\n",MAGIC_HEADER);
    fprintf(fp,"%d\n",count);  //save the number of customers
    fprintf(fp,"%.2f\n",rate); //save the current rate

    for (int i=0; i<count; i++){
        fprintf(fp, "%s\n%s\n%.2f\n%.2f\n",
                customers[i].name,
                customers[i].phone,
                customers[i].usage,
                customers[i].total_bill);
    }
    fclose(fp);
    last_action("save");
}

void load(){
    FILE *fp=fopen(SAVE_FILE,"r");
    if(!fp){
        logData("No save file, let's roll fresh!");
        return;
    }
    char header[20];
    fgets(header, sizeof(header),fp);
    header[strcspn(header, "\n")]=0;

    if(strcmp(header, MAGIC_HEADER)!=0){
        logData("Corrupted file: invalid header.");
        fclose(fp);
        return;
    }
    if(fscanf(fp,"%d\n", &count)!=1 || fscanf(fp,"%f\n",&rate)!=1 || count<0 || count>MAX_CUSTOMER){
        printf("Corrupted data file.\n");
        fclose(fp);
        return;
    }

    for (int i=0; i<count; i++){
        fgets(customers[i].name, MAX_NAME_LENGTH, fp);
        customers[i].name[strcspn(customers[i].name, "\n")]=0;

        fgets(customers[i].phone, PHONE_LENGTH, fp);
        customers[i].phone[strcspn(customers[i].phone, "\n")]=0;

        fscanf(fp,"%f\n",&customers[i].usage);
        fscanf(fp,"%f\n",&customers[i].total_bill);
    }
    fclose(fp);
    logData("Customer data loaded successfully.");
    last_action("load");
}

int main(){
    load();
    int choice; ///User choice
    char phone[PHONE_LENGTH];
    char confirm;
    int n;
    while(1){
        display();
        printf("\nPlease choose an option (1-10): ");
        if(scanf("%d",&choice)!=1){
            printf("Invalid input.\n");
            clear();
            continue;
        }
        clear();
        switch(choice){
        case 1:
            printf("\n");
            printf("Currently there are %d customers in the system.\n", count);
            printf("->You can add up to %d more.\n", MAX_CUSTOMER-count);
            printf("->How many customers do you want to add? ");
            if(scanf("%d",&n)!=1 || n<=0){
                printf("Invalid number.\n");
                clear();
                break;
            }
            clear();

            for (int i =0;i<n; i++){
                if (count>= MAX_CUSTOMER){
                    printf("Maximum customer limit reached. Cannot add more.\n");
                    break;
                }
                printf("\nAdding customer %d of %d:\n",i+1,n);
                add_customer();
            }
            printf("\n");
            break;

        case 2:
            list();
            printf("\n");
            save();
            break;
        case 3:
            call_rate();
            save();
            printf("\n");
            break;
        case 4:
            printf("Enter the Phone Number : ");
            scanf("%14s",phone);
            clear();
            update_customer(phone);
            printf("\n");
            save();
            break;
        case 5:
            printf("Enter the Phone Number : ");
            scanf("%14s",phone);
            clear();
            delete(phone);
            printf("\n");
            save();
            break;

        case 6:
            printf("Enter the Phone Number : ");
            scanf("%14s",phone);
            clear();
            viewUser(phone);
            printf("\n");
            save();
            break;
        case 7:
            revenue();
            printf("\n");
            break;
        case 8:
            CSV();
            printf("\n");
            break;
        case 9:
            save();
            last_action("backup_data");
            printf("Data backup completed successfully.\n\n");
            break;
        case 10:
            printf("Do you want to save before exiting? (y/n): ");
            scanf(" %c",&confirm);
            if(confirm == 'y' || confirm == 'Y') save();
            printf("Data saved successfully.Thank you..... Goodbye!\n");
            return 0;

        default:
            printf("!!!!Invalid choice!!!!\n");
        }
    }
}
