#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

struct record{        //* creating a record structure to store and read the total income , total expense and balance in the main menu
    double in , ex;
}*point = NULL;

struct node{              //* creating a node structure to store all the necessary data for one node in the link list
    char date[50];        //* Array to store date
    double amount;       //* array to store the amount (money)
    char currency[10];  //* The array will contain the same name of currency as displayed in the main menu
    char category[50];   //* array to store name of chosen category
    char type[10];    //* array to store name of the currency
    struct node *next;
}add , *income=NULL , *expense=NULL;     //* income and expense pointer to read and write the data of the node, depends on income / category

struct category {            //* creating a category structure for categories linked list
  char catname[500];      //* array to store all the categories names
  struct category *next;               
}*INcategories = NULL ,*head, *first, *temp = NULL, *EXcategories = NULL;          //* INcategories and EXcategories pointers for income and expense categories depends on the user.
char name[50];  //* temporary array to store name of new category


double EuroToForint(double amount){    //* Function to convert amount of money from euro to forint
    amount *= 400;
    return amount;
}

double ForintToEuro(double amount){       //* Function to convert amount of money from forint to euro
    amount *= 0.0025; 
    return amount;
}


                                             //* defining all the functions, for income , expense and record saving, reading and creating.
void create(char x[], double y, char z[], char c[] , struct node **temp );     //* function to create a node out of the node struct data and storing it inside a pointer
void deleterecord(struct node *ptr);                                 
struct node *readnext(struct node *ptr, FILE *fptr);             //* function to read next node 
void save_income(struct node *ptr);                //*function to save income record
struct node *readincome(struct node *ptr, FILE *fptr);         //*function to read income record
void save_expense(struct node *ptr);             //*function to save expense record
struct node *readexpense(struct node *ptr , FILE *fptr);      //*function to read expense record
void display_record(int n);                   //*function to display income and expense record
void save_record(struct record *point);              //*function to save the menu record record (roral income , total expense, current balance)
struct record *read_record(struct record *ptr , FILE* fptr);              //*function to read the record of the above function

    //* defining all the functions, for categories record saving, reading, searching and creating.
bool search(struct category* ptr2, char x[10]);       //*function search name of category in a linked list (if exist) 

void New_Category();                                                             //*function to create a new category (node)
void CreateCatList(char x[] ,struct category **temp);                           //*function to create a linked list
void Save_INCOME_Category(struct category *ptr);                                //*function to save income categories
struct category *ReadNextCat(struct category *ptr,FILE *fptr);                  //*function to read next category in list
void DeleteInRecord(struct category *ptr);                                
struct category *Read_INCOME_Category(struct category *ptr , FILE *fptr);              //*function to read income categories
void Save_EXPENSE_Category(struct category *ptr);                         //*function to save expense categories
struct category *Read_EXPENSE_Category(struct category *ptr , FILE *fptr);               //*function to read expense categories
void DisplayCategories(int n);                                           //*function to display income or expense categories

/* Function to delete the entire linked list */
void deleteList(struct node **head_ref)
{
   /* deref head_ref to get the real head */
   struct node *current = *head_ref;
   struct node *next;
 
   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }
   
   /* deref head_ref to affect the real head back
      in the caller. */
   *head_ref = NULL;
}


void deleteCATList(struct category **head_ref)
{
   /* deref head_ref to get the real head */
   struct category *current = *head_ref;
   struct category *next;
 
   while (current != NULL)
   {
       next = current->next;
       free(current);
       current = next;
   }
   
   /* deref head_ref to affect the real head back
      in the caller. */
   *head_ref = NULL;
}

void deleteLista(struct node **head)
{
    struct node *prev = *head;
 
    while (*head)
    {
        *head = (*head)->next;
 
        
        free(prev);
        prev = *head;
    }
}

void deleteListc(struct category **head)
{
    struct category *prev = *head;
 
    while (*head)
    {
        *head = (*head)->next;
 
        
        free(prev);
        prev = *head;
    }
}

int main(){
    char DisplayCoin[10];
    char euro[10] = "Euro";
    char forint[10] = "Forint";
    double current_income = 0 , current_expense = 0;
    system("color a");
    FILE* currencyPTR;
    FILE* aaa;
    FILE* bbb;
    FILE* ccc;
    FILE* ddd;
    FILE* eee;
    currencyPTR = fopen("currency.txt", "r");   //* opening the file that contains the currency data (name)
    if (currencyPTR == NULL) //* Works when the user open the program for the first time, Asks for a currency type, create a file and stores the data.
    {
        currencyPTR = fopen("currency.txt" , "w");     
        printf("************ WELCOME TO YOUR DIGITAL WALLET ************\n\n\n");
        printf("Please choose a currency: \n");
        printf("1. Euro\n");
        printf("2. Forint\n");
        int currency1;
        scanf("%d" , &currency1);
        switch (currency1)
        {
        case 1:
            fputs("Euro", currencyPTR);
            fclose(currencyPTR);
            strcpy(add.currency , euro);
            break;
        case 2:
            fputs("Forint" , currencyPTR);
            fclose(currencyPTR);
            strcpy(add.currency , forint);
        default: printf("Please choose a valid option!\n");
            break;
        }
        printf("\nThe program will start in a few seconds\nPlease enter new categories first! \n");
        Sleep(8000);
      system("cls");  
    }

    if( (aaa = fopen("Record.bin" , "rb") ) != NULL){            //* opening the record file and saving the data into pointers
        point = read_record(point , aaa);
        current_income = point->in;
        current_expense = point->ex;
    }
    if( (bbb =fopen("Income_record.bin" , "rb") ) != NULL){     //* opening the income record file and saving the data into a pointer
        income = readincome(income , bbb);
    }
    if( (ccc= fopen("Expense_record.bin" , "rb") ) != NULL){     //* opening the expense record file and saving the data into a pointer
        expense = readexpense(expense , ccc);
    }

    if( (ddd= fopen("Income_categories.bin","rb") ) != NULL){           //* opening the income category file and saving the data into a pointer
      INcategories = Read_INCOME_Category(INcategories , ddd); 
    }

    if( (eee =fopen("Expense_categories.bin","rb") ) != NULL){           //* opening the expense category file and saving the data into a pointer
      EXcategories = Read_EXPENSE_Category(EXcategories , eee);
    }

    double amount;
    char d[50];
    char day[15] , month[15] , year[15]; 
    int option;
    
    currencyPTR = fopen("currency.txt" , "r");
    fgets(DisplayCoin, 10, currencyPTR);
    fclose(currencyPTR);
    do{               //* Run the program as long as the user did not press exit

        printf("                           Digital Wallet ");
        printf("\n\n                ************************************");
        printf("\n                                                      ");
        printf("\n                   Current balance: %.2lf %s            ",current_income-current_expense , DisplayCoin);   //* Display the current balance
        printf("\n                                                      ");
        printf("\n                   Total income: %.2lf %s               ",current_income , DisplayCoin);   //* Display the Total income
        printf("\n                                                      ");
        printf("\n                   Total expense: %.2lf %s              ",current_expense , DisplayCoin);   //* Display the Total expense
        printf("\n                                                      ");
        printf("\n                   Top category: %s: %.2lf %s          ",DisplayCoin);    //*Insert most expensive category name + total amount  //! unfortunately this function does not work ;(
        printf("\n\n               ***************************************");
        printf("\n \n ");
        printf("\n What would you like to do?");
        printf("\n\n 1. Add income");
        printf("\n 2. Add expense");
        printf("\n 3. Add new category");
        printf("\n 4. View income record");
        printf("\n 5. View expense record");
        printf("\n 6. View statistics");
        printf("\n 7. View income categories");
        printf("\n 8. View expense categories");
        printf("\n 9. EXIT\n");

        scanf("%d", &option);

        switch (option){
            int cointype;
            int cat_type;
            char cat_name[15];
            case 1:
            system("cls");
            printf("************ ADD INCOME ************\n\n");   //* starting the add income function 
            printf("Enter the date(day, month, year)\n");
            scanf("%s %s %s", day, month , year );    //* scanning the dates into temporary strings
            strcpy(d , "");
            strcat(d , day);
            strcat(d , ".");
            strcat(d , month);       //* using strcat to orginize the date in the string d
            strcat(d , ".");
            strcat(d , year);
            printf("Choose currency type:\n1. Euro\n2. Forint\n");
            scanf("%d", &cointype);
            switch (cointype){            //* Creating another menu to calculate, check and return the currency type by the user's request
                 case 1:
                 printf("Enter the amount: \n");
                 scanf("%lf", &amount);
                 if (strstr(forint , DisplayCoin)){   //! If The currency is Forint and the user would like to enter amount in Euro then use function EuroToForint.
                 amount = EuroToForint(amount);
                 add.amount = amount;
                 }break;
                 if( strstr(euro , DisplayCoin)) add.amount = amount;  //! If The currency is already Euro then return the amount as it is.
                 break;

                 case 2:
                 printf("Enter the amount: \n");
                 scanf("%lf", &amount);
                 if(strstr(euro , DisplayCoin)){     //! If The currency is Euro and the user would like to enter amount in Forint then use function ForintToEuro.
                 amount = ForintToEuro(amount);
                 add.amount = amount;
                 }break;
                 if (strstr(forint , DisplayCoin)) add.amount = amount; //! If The currency is already Forint then return the amount as it is.
                 break;

                default: printf("ERROR, Please try again!");
                break;

            } 
            printf("Please choose a category: \n");
            DisplayCategories(1);              //*printing the available income categories
            scanf("%s" , cat_name);     //* scaning the users coice into a temporary array
            system("cls");
             if((search(INcategories , cat_name)) == true){    //*checking if the desired category is avaialbe
              strcpy(add.currency , DisplayCoin);
              printf("Category exist! saving your data...\n");   //* if so, start saving the data
              current_income += amount;
              create(d, amount, add.currency, cat_name ,&income);
              fclose(bbb);
              save_income(income);
              bbb = fopen("Income_record.bin" , "rb");

              point = (struct record*)malloc(sizeof(struct record));
              point->in=current_income;
              point->ex=current_expense;
              fclose(aaa);
              save_record(point);
              aaa= fopen("Record.bin" , "rb");               
              }

            else if((search(INcategories , cat_name)) == false) printf("Category does not exist! Please try again...\n\n");  //*else return to the main menu
            break;

            case 2:
            system("cls");
            printf("************ ADD EXPENSE ************\n\n");   //* starting the add expense function 
            printf("Enter the date(day, month, year)\n");
            scanf("%s %s %s", day, month , year );   //* scanning the dates into temporary strings
            strcpy(d,"");
            strcat(d , day);
            strcat(d , ".");
            strcat(d , month);    //* using strcat to orginize the date in the string d
            strcat(d , ".");
            strcat(d , year);
            printf("Choose currency type:\n1. Euro\n2. Forint\n");
            scanf("%d", &cointype);
            switch (cointype){           //* Creating another menu to calculate, check and return the currency type by the user's request
                 case 1:
                 printf("Enter the amount: \n");
                 scanf("%lf", &amount);
                 if (strstr(forint , DisplayCoin)){     //! If The currency is Forint and the user would like to enter amount in Euro then use function EuroToForint.
                 amount = EuroToForint(amount);
                 add.amount = amount;
                 }break;
                 if( strstr(euro , DisplayCoin)) add.amount = amount;  //! If The currency is already Euro then return the amount as it is.
                 break;

                 case 2:
                 printf("Enter the amount: \n");
                 scanf("%lf", &amount);
                 if(strstr(euro , DisplayCoin)){    //! If The currency is Euro and the user would like to enter amount in Forint then use function ForintToEuro.
                 amount = ForintToEuro(amount);
                 add.amount = amount;
                 }break;;
                 if (strstr(forint , DisplayCoin)) add.amount = amount;   //! If The currency is already Forint then return the amount as it is.
                break;

                default: printf("ERROR, Please try again!");
                break;

            } 
            printf("Please choose a category: \n");
            DisplayCategories(2);                //*printing the available expense categories
            scanf("%s" , cat_name);   //* scaning the users coice into a temporary array
            system("cls");
             if((search(EXcategories , cat_name)) == true){    //*checking if the desired category is avaialbe
              strcpy(add.currency , DisplayCoin);      
              printf("Category exist! saving your data...\n");   //* if so, start saving the data
              current_expense += amount;
              create(d, amount, add.currency, cat_name ,&expense);
              fclose(ccc);
              save_expense(expense);
              ccc = fopen("Expense_record.bin" , "rb");
              point = (struct record*)malloc(sizeof(struct record));
              point->in=current_income;
              point->ex=current_expense;
              fclose(aaa);
              save_record(point);
              aaa = fopen("Record.bin" , "rb");           
              }

            else if((search(EXcategories , cat_name)) == false) printf("Category does not exist! Please try again...\n\n"); //*else return to the main menu
            break;

            case 3:
            system("cls");
            printf("************ ADD NEW CATEGORY ************\n\n");
            printf("Please choose category type: \n1. Income Category \n2. Expense Category\n");
            scanf("%d" , &cat_type);
            if(cat_type == 1 ){
                fclose(ddd);
                New_Category(1);
                CreateCatList(name,&INcategories);
                Save_INCOME_Category(INcategories);
                ddd = fopen("Income_categories.bin","rb");
            }
            else if(cat_type == 2 ){
              fclose(eee);
                New_Category(2);
                CreateCatList(name,&EXcategories);
                Save_EXPENSE_Category(EXcategories);
                eee =fopen("Expense_categories.bin","rb");
                }
            break;

            case 4:
            system("cls");
            fclose(bbb);
            display_record(4);  
            break;

            case 5:
            system("cls");
            fclose(ccc);
            display_record(5);   
            break;

            case 6:
            system("cls");
            printf("************ STATISTICS ************\n\n");      //! unfortunately this function does not work ;(
            printf("Please enter start date: ");
            scanf("%s %s %s", day, month , year );
            printf("Please enter end date: ");
            scanf("%s %s %s", day, month , year );
            system("cls");
            break;

            case 11:
            deleteLista(&income);
            break;

            case 7:
            system("cls");
            printf("************ INCOME CATEGORIES ************\n");
            fclose(ddd);
            DisplayCategories(1);
            break;

            case 8:
            system("cls");
            printf("************ EXPENSE CATEGORIES ************\n");
            fclose(eee);
            DisplayCategories(2);
            break;

            case 9:
            free(point);
            deleteLista(&income);
            deleteLista(&expense);
            deleteListc(&INcategories);
            deleteListc(&EXcategories);
            deleteListc(&head);
            deleteListc(&temp);
            deleteListc(&first);

            amount = 0;

            free(income);
            free(expense);
            free(INcategories);
            free(EXcategories);
            free(head);
            free(temp);
            free(first);

            fclose(aaa);
            fclose(bbb);
            fclose(ccc);
            fclose(ddd);
            fclose(eee);

            break;
            default:
            system("cls");
            option = getchar();   //* In case the user entered a string instead of a number this function will capture it and present an error; (Deleting this line will cause the menu to enter a loop)
            printf("_______________________________________________________________________\n");
            printf("\n* Error *  Please enter valid option number\n");
            printf("_______________________________________________________________________\n\n\n");
            
            break;
            }
    } while (option!=9);


    return 0;
}

//* all of the income , expense , record functions:

void create(char x[], double y, char z[] , char c[], struct node **temp ){
    struct node *newnode, *ptr;
    newnode = (struct node*)malloc(sizeof(struct node));
    if(*temp == NULL){
        strcpy(newnode->date,x);
        newnode->amount = y;
        strcpy(newnode->currency,z);
        strcpy(newnode->category,c);
        newnode->next = NULL;
        *temp=newnode;
    }
    else{
        ptr=*temp;
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        strcpy(newnode->date,x);
        newnode->amount = y;
        strcpy(newnode->currency,z);
        strcpy(newnode->category,c);
        newnode->next = NULL;
        ptr->next=newnode;
    }
}

void deleterecord(struct node *ptr){
  struct node *freeme = ptr;
  struct node *holdme = NULL;
  while(freeme != NULL){
    holdme = freeme->next;
    free(freeme);
    freeme = holdme;
    }
  }

struct node *readnext(struct node *ptr, FILE *fptr){
    if(ptr == NULL){
        ptr=(struct node *)malloc(sizeof(struct node));
        fread(ptr,sizeof(struct node),1,fptr);
        ptr->next = NULL;
    }

    else{
        struct node *ptr1 = ptr;
        struct node *ptr2 = (struct node*)malloc(sizeof(struct node));
        while(ptr->next != NULL){
            ptr1 = ptr1->next;
        }
        fread(ptr2,sizeof(struct node),1,fptr);
        ptr1->next = ptr2;
        ptr2-> next = NULL;
    }
    return ptr;
}

void save_income(struct node *ptr){
    FILE *fptr;
    fptr = fopen("income_record.bin" , "wb");
    if (fptr != NULL)
    {
        struct node *ptr1 = ptr;
        struct node *holdnext = NULL;
        while(ptr1 != NULL){
            holdnext = ptr1->next;
            ptr1->next = NULL;
            fseek(fptr,0,SEEK_END);
            fwrite(ptr1,sizeof(struct node),1,fptr);
            ptr1->next = holdnext;
            holdnext = NULL;
            ptr1 = ptr1->next;
        }
        fclose(fptr);
        fptr = NULL;
        printf("\nINCOME SAVED SUCCESSFULLY\n\n");
        printf("________________________________________________________________________________________________________________\n\n");
    }

    else{
        printf("CANNOT SAVE INCOME! PLEASE TRY AGAIN...\n");
        printf("_______________________________________________________________________\n\n");
    }

}

struct node *readincome(struct node *ptr, FILE *fptr){
  if(fptr != NULL){
    deleterecord(ptr);
    ptr = NULL;
    fseek(fptr,0,SEEK_END);
    long filesize = ftell(fptr);
    rewind(fptr);
    int entries=(int)(filesize/(sizeof(struct node)));
    for(int i=0 ; i<entries ; i++){
      fseek(fptr,(sizeof(struct node)*i),SEEK_SET);
      ptr=readnext(ptr,fptr);
      }
    }
    
  else{
    printf("ERROR IN OPENINNG FILE\n");
    }
return ptr;
}

void save_expense(struct node *ptr){
    FILE* fptr;
    fptr = fopen("Expense_record.bin" , "wb");
    if (expense != NULL){
        struct node *ptr1 = ptr;
        struct node *holdnext = NULL;
        while(ptr1 != NULL){
            holdnext = ptr1->next;
            ptr1->next = NULL;
            fseek(fptr,0,SEEK_END);
            fwrite(ptr1,sizeof(struct node),1,fptr);
            ptr1->next = holdnext;
            holdnext = NULL;
            ptr1 = ptr1->next;
        }
        fclose(fptr);
        fptr = NULL;
        printf("\nEXPENSE SAVED SUCCESSFULLY\n\n");
        printf("_______________________________________________________________________\n\n");
    }

    else{
        printf("CANNOT SAVE EXPENSE! PLEASE TRY AGAIN...\n");
        printf("_______________________________________________________________________\n\n");
    }

}

struct node *readexpense(struct node *ptr , FILE *fptr){
    if(fptr != NULL){
        deleterecord(ptr);
        ptr = NULL;
        fseek(fptr,0,SEEK_END);
        long filesize = ftell(fptr);
        rewind(fptr);
        int entries = (int)(filesize/(sizeof(struct node)));
        for(int i=0 ; i<entries ; i++){
            fseek(fptr,(sizeof(struct node)*i),SEEK_SET);
            ptr=readnext(ptr,fptr);
        }
    }
    else printf("cannonot open file\n");
    return ptr;
}

void display_record(int n){
    if (n == 4){

        if (fopen("Income_record.bin" ,"rb") == NULL){
            printf("********** THERE ARE NO RECORDS **********\n");
            printf("________________________________________________________________________________________________________________\n\n");
        }
    
        else{
            printf("************ YOUR INCOME RECORD ************\n\n");
            struct node *ptr2 = income;
            while(ptr2 != NULL){
                printf("Date: %s\nAmount: %.2lf %s \nCategory: %s\n\n", ptr2->date, ptr2->amount, add.currency , ptr2->category);
                ptr2 = ptr2->next;
            }
        printf("________________________________________________________________________________________________________________\n\n");
            }
    }

    else if (n == 5){
        if (fopen("Expense_record.bin" ,"rb") == NULL){
            printf("********** THERE ARE NO RECORDS **********\n");
            printf("________________________________________________________________________________________________________________\n\n");
        }
    
        else{
            printf("************ YOUR EXPENSE RECORD ************\n\n");
            struct node *ptr2 = expense;
            while (ptr2 != NULL){
                printf("Date: %s\nAmount: %.2lf %s \nCategory: %s\n\n", ptr2->date, ptr2->amount, add.currency, ptr2->category);
                ptr2 = ptr2->next;
            }
        printf("________________________________________________________________________________________________________________\n\n");

        }
    }
}

void save_record(struct record *point){
    FILE *fptr;
    fptr = fopen("Record.bin" , "wb");
    if(fptr != NULL){
        fseek(fptr,0,SEEK_END);
        fwrite(point,sizeof(struct record),1,fptr);
    }
    else printf("***** CANNOT OPEN FILE *****\n");

    fclose(fptr);
    fptr = NULL;
}

struct record *read_record(struct record *ptr , FILE* fptr){
    ptr = NULL;
    if(fptr != NULL){
        fseek(fptr,0,SEEK_SET);
        ptr = (struct record *)malloc(sizeof(struct record));
        fread(ptr,sizeof(struct record),1,fptr);
    }
    else printf("CANNOT OPEN FILE\n");

    return ptr;
}


//* all of the categories functions:

void New_Category(int n) {
  if(n == 1){
    printf("\nEnter name of income category: \n");
    scanf("%s", name);
    
    temp =malloc(sizeof (struct category));
    strcpy(temp->catname , name);
    if (first == NULL) {
      first = temp;
      }
    else {
      head->next = temp;
      }
    temp->next = NULL;
    head = temp;
  }

  else if(n == 2){
    printf("\nEnter name of expense category: \n");
    scanf("%s", name);
    
    temp =malloc(sizeof (struct category));
    strcpy(temp->catname , name);
    if (first == NULL) {
      first = temp;
      }
    else {
      head->next = temp;
      }
    temp->next = NULL;
    head = temp;
  }
}

struct category *ReadNextCat(struct category *ptr,FILE *fptr){
    if(ptr == NULL){
      ptr=malloc(sizeof(struct category));
      fread(ptr,sizeof(struct category),1,fptr);
      ptr->next = NULL;
      }
      
      else{
        struct category *ptr1 = ptr;
        struct category *ptr2 =malloc(sizeof(struct category));
        while(ptr1->next != NULL){
          ptr1 = ptr1->next;
          }
          fread(ptr2,sizeof(struct category),1,fptr);
          ptr1->next = ptr2;
          ptr2->next = NULL;
          }
          return ptr;
    }

void CreateCatList(char x[] ,struct category **temp) {
  struct category *newnode,*ptr;
  newnode=(struct category*)malloc(sizeof(struct category));
  if(*temp==NULL){
    strcpy(newnode->catname,x);
    newnode->next=NULL;
    *temp=newnode;
    }
    else{
      ptr=*temp;
      while(ptr->next!=NULL){
        ptr=ptr->next;
        }
      strcpy(newnode->catname,x);
      newnode->next=NULL;
      ptr->next=newnode;
      }
  }

void Save_INCOME_Category(struct category *ptr){
  FILE *fptr;
  fptr=fopen("Income_categories.bin","wb");    
  if(fptr!=NULL){
    struct category *ptr1=ptr;
    struct category *holdnext=NULL;
    while(ptr1!=NULL){
      holdnext=ptr1->next;
      ptr1->next=NULL;
      fseek(fptr,0,SEEK_END);
      fwrite(ptr1,sizeof(struct category),1,fptr);
      ptr1->next=holdnext;
      holdnext=NULL;
      ptr1=ptr1->next;
      }
    fclose(fptr);
    fptr=NULL;
    printf("\nCATEGORY SAVED SUCCESSFULLY\n\n");
    printf("________________________________________________________________________________________________________________\n\n");
  }
  else{
    printf("\nCANNOT SAVE CATEGORY..TRY AGAIN\n");
    printf("________________________________________________________________________________________________________________\n\n");
  }
}

void DeleteInRecord(struct category *ptr){
  struct category *freeme =ptr;
  struct category *holdme=NULL;
  while(freeme!=NULL){
    holdme=freeme->next;
    free(freeme);
    freeme=holdme;
    }
  }

struct category *Read_INCOME_Category(struct category *ptr , FILE *fptr){
  if(fptr!=NULL){
    DeleteInRecord(ptr);
    ptr=NULL;
    fseek(fptr,0,SEEK_END);
    long filesize=ftell(fptr);
    rewind(fptr);
    int entries=(int)(filesize/(sizeof(struct category)));
    for(int i=0;i<entries;i++){
      fseek(fptr,(sizeof(struct category)*i),SEEK_SET);
      ptr=ReadNextCat(ptr,fptr);
      }
    }
    
  else{
    printf("ERROR IN OPENINNG FILE\n");
    }
return ptr;
}

void Save_EXPENSE_Category(struct category *ptr){
  FILE *fptr;
  fptr=fopen("Expense_categories.bin","wb");    
  if(fptr!=NULL){
    struct category *ptr1=ptr;
    struct category *holdnext=NULL;
    while(ptr1!=NULL){
      holdnext=ptr1->next;
      ptr1->next=NULL;
      fseek(fptr,0,SEEK_END);
      fwrite(ptr1,sizeof(struct category),1,fptr);
      ptr1->next=holdnext;
      holdnext=NULL;
      ptr1=ptr1->next;
      }
    fclose(fptr);
    fptr=NULL;
    printf("\nCATEGORY SAVED SUCCESSFULLY\n\n");
    printf("________________________________________________________________________________________________________________\n\n");
  }
  else{
    printf("\nCANNOT SAVE CATEGORY..TRY AGAIN\n");
    printf("________________________________________________________________________________________________________________\n\n");
  }
}

struct category *Read_EXPENSE_Category(struct category *ptr , FILE *fptr){
  if(fptr!=NULL){
    DeleteInRecord(ptr);
    ptr=NULL;
    fseek(fptr,0,SEEK_END);
    long filesize=ftell(fptr);
    rewind(fptr);
    int entries=(int)(filesize/(sizeof(struct category)));
    for(int i=0;i<entries;i++){
      fseek(fptr,(sizeof(struct category)*i),SEEK_SET);
      ptr=ReadNextCat(ptr,fptr);
      }
    }
    
  else{
    printf("ERROR IN OPENINNG FILE\n");
    }
return ptr;
}

void DisplayCategories(int n){
  if(n == 1){
    if(fopen("Income_categories.bin","rb") == NULL){
        printf("\n **********NO CATEGORIES AVAILABLE **********\n");
        printf("________________________________________________________________________________________________________________\n\n\n");
        }
        else{ 
        printf("________________________________________________________________________________________________________________\n");
            struct category *ptr2 = INcategories;
            while(ptr2 != NULL){
                printf("\n%s" ,ptr2->catname);
                ptr2 = ptr2->next;
            }
        printf("\n________________________________________________________________________________________________________________\n\n\n");
        }
      }

  if(n == 2){
    if(fopen("Expense_categories.bin","rb") == NULL){
        printf("\n **********NO CATEGORIES AVAILABLE **********\n");
        printf("________________________________________________________________________________________________________________\n\n\n");
        }
        else{ 
        printf("________________________________________________________________________________________________________________\n");
            struct category *ptr2 = EXcategories;
            while(ptr2 != NULL){
                printf("\n%s" ,ptr2->catname);
                ptr2 = ptr2->next;
            }
        printf("\n________________________________________________________________________________________________________________\n\n\n");

        }

      }     
}

bool search(struct category* head, char x[50]){             //Checks whether the string x is present in linked list      
	struct category* current = head;                      // Initialize current
	while (current != NULL) {
		if ((strcmp(current->catname , x)) ==0)        //using strcmp function 
			return true;
		current = current->next;
	}
	return false;
  }
