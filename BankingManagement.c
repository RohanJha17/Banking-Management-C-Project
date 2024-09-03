#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int employee() {
    char employee_ID[200];
    char password[100];
    printf("Enter your ID: ");
    fgets(employee_ID,sizeof(employee_ID),stdin);
    employee_ID[strcspn(employee_ID,"\n")] = '\0';
    printf("Enter Password: ");
    fgets(password,sizeof(password),stdin);
    password[strcspn(password,"\n")] = '\0';

    FILE *ptr = fopen("employee.txt", "r");
    if(ptr == NULL){
        printf("Error opening file.\n");
        return 0;
    }

    char emp_ID[200];
    char pass[100];
    int matched = 0;
    while (fscanf(ptr,"%s %s",emp_ID,pass)==2){
        if((strcmp(employee_ID,emp_ID)== 0) && (strcmp(password,pass) == 0)){
            matched = 1;
            break;
        }
    }
    fclose(ptr);
    printf("\n");

    if(matched==1){
        printf("Welcome to......\n");
        return 1;
    }
    else{
        printf("Invalid ID and Password.\n");
        return 0;
    }
}
void menu(){
    printf("BANKING MANAGEMENT SYSTEM...\n");
    printf("Press 1 for Create new Account.\n");
    printf("Press 2 for Update Existing Account.\n");
    printf("Press 3 for Check Account details.\n");
    printf("Press 4 for Withdraw money.\n");
    printf("Press 5 for Deposite money.\n");
    printf("Press 6 for Transfer money.\n");

}
void create();
void update();
void check_Details();
void withdraw_Money();
void deposit_Money();
void transfer_Money();
void close();

int main(){
    printf("Hello!!\n");
    FILE* ptr1 = fopen("employee.txt","a+");
    FILE* ptr2 = fopen("account.txt","a+");
    if(ptr1==NULL || ptr2==NULL){
        printf("Error creating file.\n");
        return 1;
    }
    fclose(ptr1);
    fclose(ptr2);

    while(!employee()){
        printf("Please try again...\n\n");
    }

    int choice;
    menu();
    printf("Enter the choice: ");
    scanf("%d",&choice);
    getchar();
    printf("\n");

    switch(choice){
        case 1: create();
                break;
        case 2: update();
                break;
        case 3: check_Details();
                break;
        case 4: withdraw_Money();
                break;
        case 5: deposit_Money();
                break;
        case 6: transfer_Money();
                break;
        default: close();
  }

  return 0;
}
void create() {
    printf("\nOpening Account...\n");

    FILE* ptr = fopen("account.txt","a+");
    if(ptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    char acc_no[20];
    char name[30];
    float balance;

    char stracc_no[20];
    char strname[30];
    float strbalance;

    input_account:
    printf("Account Number: ");
    fgets(acc_no,sizeof(acc_no),stdin);
    acc_no[strcspn(acc_no,"\n")] = '\0';
    printf("Name: ");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\n")] = '\0';
    printf("Opening Balance: ");
    scanf("%f",&balance);
    getchar();
   
    while(fscanf(ptr,"%s %s %f\n",stracc_no,strname,&strbalance)==3) {
        if (strcmp(acc_no,stracc_no)==0){
            printf("Account number already exists,TRY AGAIN\n");
            goto input_account;
            return;
        }
    }
    fprintf(ptr,"%s %s %.3f\n",acc_no,name,balance);
    fclose(ptr);
    printf("Account Created Successfully.\n");
}
void update(){
    printf("\nUpdating Account...\n");
    FILE* new_ptr = fopen("account_new.txt", "w");
    FILE* old_ptr = fopen("account.txt", "r");
    if(new_ptr == NULL || old_ptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    char stracc_no[20];
    char strname[30];
    float strbalance;

    char acc_no[20];
    char new_name[30];

    input_account:
    printf("Enter the account number that you would like to modify: \n");
    fgets(acc_no,sizeof(acc_no),stdin);
    acc_no[strcspn(acc_no,"\n")] = '\0';

    int found = 0;
    while(fscanf(old_ptr,"%s %s %f",stracc_no,strname,&strbalance)==3){
        if(strcmp(acc_no,stracc_no)==0){
            found = 1;
            break;
        }
    }
    if(found==0){
        printf("Account does not exists,TRY AGAIN.\n");
        goto input_account;
    }
    printf("Enter the new Name: ");
    fgets(new_name,sizeof(new_name),stdin);
    new_name[strcspn(new_name,"\n")] = '\0';

    fseek(old_ptr,0,SEEK_SET);
    while(fscanf(old_ptr,"%s %s %f",stracc_no,strname,&strbalance)==3){
        if(strcmp(acc_no,stracc_no)==0){
            strcpy(strname,new_name);
        }
        fprintf(new_ptr,"%s %s %.3f\n",stracc_no,strname,strbalance);
    }
    printf("Account Updated Successfully.\n");
    fclose(new_ptr);
    fclose(old_ptr);

    remove("account.txt");
    rename("account_new.txt", "account.txt");
}
void check_Details(){
    printf("\nChecking Details...\n");

    FILE* ptr =  fopen("account.txt", "r");
    if(ptr == NULL){
        printf("Error opening file.\n");
        return;
    } 

    char acc_no[20];
    char stracc_no[20];
    char strname[30];
    float strbalance;

    printf("Account Number: ");
    fgets(acc_no,sizeof(acc_no),stdin);
    acc_no[strcspn(acc_no,"\n")] = '\0';
    printf("\n");

    int found = 0;
    while(fscanf(ptr,"%s %s %f",stracc_no,strname,&strbalance)==3){
        if (strcmp(acc_no,stracc_no)==0){
            printf("Account Number: %s\n",stracc_no);
            printf("Account Holder Name: %s\n",strname);
            printf("Total Balance: %.3f\n",strbalance);
            found = 1;
            break;
        } 
    }
    printf("Details Checked Successfully.\n");
    fclose(ptr);

    if(found==0) printf("Account Number doesn't exists.\n");
}
void withdraw_Money(){
    printf("\nWithdrawing Money...\n");

    FILE* new_ptr = fopen("account_new.txt", "w");
    FILE* old_ptr = fopen("account.txt", "r");
    if(new_ptr == NULL || old_ptr == NULL){
        printf("Error opening file.\n");
        return;
    }
    
    char stracc_no[20];
    char strname[30];
    float strbalance;

    char acc_no[20];
    float amt;

    input_account:
    printf("Enter the account number:");
    fgets(acc_no,sizeof(acc_no),stdin);
    acc_no[strcspn(acc_no,"\n")] = '\0';

    int found = 0;
    while(fscanf(old_ptr,"%s %s %f",stracc_no,strname,&strbalance)==3){
        if(strcmp(acc_no,stracc_no)==0){
            found = 1;
            break;
        }
    }
    if(found == 0){
        printf("Account does not exists,TRY AGAIN\n");
        goto input_account;
    }
    printf("Enter the amount to Withdraw: ");
    scanf("%f",&amt);

    fseek(old_ptr,0,SEEK_SET);
    while(fscanf(old_ptr,"%s %s %f",stracc_no,strname,&strbalance)==3){
        if(strcmp(acc_no,stracc_no)==0){
            strbalance = strbalance - amt;
        }
        fprintf(new_ptr,"%s %s %.3f\n",stracc_no,strname,strbalance);
    }
    printf("Amount Withdrawn Successfully.\n");

    fclose(new_ptr);
    fclose(old_ptr);

    remove("account.txt");
    rename("account_new.txt", "account.txt");
}
void deposit_Money(){
    printf("\nDepositing Money...\n");

    FILE *new_ptr = fopen("account_new.txt","w");
    FILE *old_ptr = fopen("account.txt","r");
    if(new_ptr == NULL || old_ptr == NULL){
        printf("Error opening file.\n");
        return;
    }

    char stracc_no[20];
    char strname[30];
    float strbalance;

    char acc_no[20];
    float amt;

    input_account:
    printf("Enter the account number:");
    fgets(acc_no,sizeof(acc_no),stdin);
    acc_no[strcspn(acc_no,"\n")] = '\0';

    int found = 0;
    while(fscanf(old_ptr,"%s %s %f",stracc_no,strname,&strbalance)==3){
        if(strcmp(acc_no,stracc_no)==0) {
            found = 1;
            break;
        }
    }
    if(found == 0){
        printf("Account does not exists,TRY AGAIN\n");
        goto input_account;
    }
    printf("Enter the amount to Deposite: ");
    scanf("%f",&amt);

    fseek(old_ptr,0,SEEK_SET);
    while(fscanf(old_ptr,"%s %s %f",stracc_no,strname,&strbalance)==3){
        if(strcmp(acc_no,stracc_no)==0){
            strbalance = strbalance + amt;
        }
        fprintf(new_ptr,"%s %s %.3f\n",stracc_no,strname,strbalance);
    }

    printf("Amount Deposited Successfully.\n");

    fclose(new_ptr);
    fclose(old_ptr);

    remove("account.txt");
    rename("account_new.txt", "account.txt");
}
void transfer_Money(){
    printf("TRANSFER MONEY\n");

    FILE* new_ptr = fopen("account_new.txt", "w");
    FILE* old_ptr = fopen("account.txt", "r");
    if(old_ptr==NULL || new_ptr==NULL){
        printf("Error opening file.\n");
    }

    char stracc_no[20];
    char strname[30];
    float strbalance;

    char sen_acc_no[20];
    char rec_acc_no[20];
    float amt;

    input_account:
    printf("Enter the Sender account number: ");
    fgets(sen_acc_no,sizeof(sen_acc_no),stdin);
    sen_acc_no[strcspn(sen_acc_no,"\n")] = '\0';
    printf("Enter Receiver account number: ");
    fgets(rec_acc_no,sizeof(rec_acc_no),stdin);
    rec_acc_no[strcspn(rec_acc_no,"\n")] = '\0';

    int found = 0;
    while(fscanf(old_ptr,"%s %s %f",stracc_no,strname,&strbalance)==3){
        if(strcmp(sen_acc_no,stracc_no)==0){
            found = 1;
            break;
        }
        else if(strcmp(rec_acc_no, stracc_no)==0){
            found = 1;
            break;
        }
    }
    if(found == 0){
        printf("Account does not exists,TRY AGAIN\n");
        goto input_account;
    }

    printf("Enter the amount to Transfer: ");
    scanf("%f", &amt);

    fseek(old_ptr,0,SEEK_SET);
    while(fscanf(old_ptr,"%s %s %f",stracc_no,strname,&strbalance)==3){
        if (strcmp(sen_acc_no,stracc_no)==0){
            strbalance = strbalance - amt;
        }
        if(strcmp(rec_acc_no,stracc_no)==0) {
            strbalance = strbalance + amt;
        }
        fprintf(new_ptr,"%s %s %.3f\n",stracc_no,strname,strbalance);
  }
  
  printf("Amount Transfered Successfully.\n");

  fclose(new_ptr);
  fclose(old_ptr);

  remove("account.txt");
  rename("account_new.txt", "account.txt");
}
void close(){ 
   exit(0);
}