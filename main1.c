#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct patient
{
    char surname[20];
    char name[20];
    char patronymic[20];
    int dateOfBirth;
    char sex[10];
    char location[10];
    int contactInformation;
    char diagnosis[15];
                                                                                                                                                          
};
struct users
{
    char login[30];
    char password[30];
    int role;
};
void array_nulling(char *array, int *size)
{
    for (int i=0; i<*size; i++)
    {
        *(array+i)=0;
    }
}
void passwordCapabilities(int *k, struct users *a1, int *size)
{
    int n, stop, MaxLetters=30;
    char login[MaxLetters], password[MaxLetters];
    while (*k==0)
    {
        array_nulling(login, &MaxLetters);
        array_nulling(password, &MaxLetters);
        stop=0;
        printf("Enter your Login: ");
        scanf("%s", &login);
        printf("Enter your Password: ");
        scanf("%s", &password);
        for (int i=0; i<*size; i++)
        {
            if (memcmp((a1+i)->login, login, MaxLetters)==0 && memcmp((a1+i)->password, password, MaxLetters)==0)
            {
                if ((a1+i)->role==1)
                {
                    *k=2;
                    printf("Welcome Back! You are logged in as an Admin!\n");
                    break;
                }
                else *k=3;
                printf("Welcome Back! You are logged in as an User!\n");
                break;
            }
        }
        if (*k==0) printf("\nSorry, you entered the wrong password. Check your password again.\n");
        while ((*k==0) && stop!=1)
        {
            printf("1 - Try logging in again\n2 - Exit\n");
            scanf("%d", &n);
            switch(n)
            {
                case 1:
                    stop=1;
                    break;
                case 2:
                    *k=-1;
                    break;
                default:
                    printf("\nYou entered an invalid number. Please try again later.\n");
            }
        }
    }
    system("pause");
}
void outputPatientInformation(struct patient *a, int *size)
{
    for (int i=0; i<*size; i++)
    {
        printf("%d. /Full Name: %2s %2s %2s/ /Date of Birth: %d/ /Sex: %2s/ /Location: %2s/ /Contact Number: %d/ /Diagnosis: %2s/\n", i+1, (a+i)->surname, (a+i)->name, (a+i)->patronymic, (a+i)->dateOfBirth, (a+i)->sex, (a+i)->location, (a+i)->contactInformation, (a+i)->diagnosis);
    }
}
void editPatientInformation(struct patient *a, int *size)
{
    int n, m=0, n1=0, m1=0;
    while (m==0)
   {
      printf("Enter the patient's number(0-Exit): ");
      scanf("%d", &n1);
      m1=0;
      if ((n1<0) || (n1>*size))
      {
        printf("\nYou entered an invalid number. Please try again later.");
      }
     else if (n1==0)
      {
        m=1;
      }
      else while (m1==0)
        {
            printf("\n1 - Edit Surname\n2 - Edit Name\n3 - Edit Patronymic\n4 - Edit Date of Birth");
            printf("\n5 - Edit Sex\n6 - Edit Location\n7 - Edit Contact Information\n8 - Edit Diagnosis\n0 - Exit\n");
                scanf("%d", &n);
                switch (n)
                {
                    case 1:
                        printf("\nEnter new Surname: ");
                        scanf("%s", &(a+n1-1)->surname);
                        break;
                    case 2:
                        printf("\nEnter new Name: ");
                        scanf("%s", &(a+n1-1)->name);
                        break;
                    case 3:
                        printf("\nEnter new Patronymic: ");
                        scanf("%s", &(a+n1-1)->patronymic);
                        break;
                    case 4:
                        printf("\nEnter new Date of Birth: ");
                        scanf("%d", &(a+n1-1)->dateOfBirth);
                        break;
                    case 5:
                        printf("\nEnter new Sex: ");
                        scanf("%s", &(a+n1-1)->sex);
                        break;
                    case 6:
                        printf("\nEnter new Location: ");
                        scanf("%s", &(a+n1-1)->location);
                        break;
                    case 7:
                        printf("\nEnter new Contact Information: ");
                        scanf("%d", &(a+n1-1)->contactInformation);
                        break;
                        case 8:
                        printf("\nEnter new Diagnosis: ");
                        scanf("%s", &(a+n1-1)->diagnosis);
                        break;
                    case 0:
                        m1=1;
                        break;
                    default:
                        printf("\nYou entered an invalid number. Please try again later.\n");
                        break;
                }
            }
        
    }
}
void addNewPatient(struct patient *a, int *size)
{
    printf("Enter Full Name: ");
    scanf("%s %s %s", &(a+*size)->surname, &(a+*size)->name, &(a+*size)->patronymic);
    printf("Enter Date of Birth: ");
    scanf("%d", &((a+*size)->dateOfBirth));
    printf("Enter Sex: ");
    scanf("%s", &((a+*size)->sex));
    printf("Enter Location: ");
    scanf("%s", &((a+*size)->location));
    printf("Enter Contact Information: ");
    scanf("%d", &((a+*size)->contactInformation));
     printf("Enter Diagnosis: ");
    scanf("%s", &((a+*size)->diagnosis));
    printf("New patient was added\n");
    system("pause");
}
void outputUsers(struct users *a1, int *size)
{
    for (int i=0; i<*size; i++)
    {
        printf("%d.Login: %s  Password: %s  Role: %d\n", i+1, (a1+i)->login, (a1+i)->password, (a1+i)->role);
    }
    system("pause");
}
void addNewUser(struct users *a1, int *size)
{
    printf("\nEnter Login of new user: ");
    scanf("%s", &((a1+*size)->login));
    printf("\nEnter Password of new user: ");
    scanf("%s", &((a1+*size)->password));
    printf("\nEnter Role(0 or 1): ");
    scanf("%d", &((a1+*size)->role));
    printf("\nNew user was added successfully!\n");
    system("pause");
}
int main()
{
    int k=0, size1=2, n, size2=1, m=0;
    struct users a1[5]={"admin", "admin", 1, "user", "user", 0};
    struct patient a[5]={"Alex", "Alex", "Alex", 23052004, "Man", "Gomel", 445892839,"diag"};
    passwordCapabilities(&k, a1, &size1);
    if (k==3)
    {
        m=0;
        while (m==0)
        {
            printf("1 - Display patient's information\n2 - Exit\n");
            scanf("%d", &n);
            switch(n)
            {
                case 1:
                    outputPatientInformation(a, &size2);
                    system("pause");
                    break;
                case 2:
                    m=-1;
                    break;
                default:
                    printf("\nYou entered an invalid number. Please try again later.\n");
                    break;
            }
        }
    }
    if (k==2)
    {
        m=0;
        while (m==0)
        {
           printf("1 - Display patient's information\n2 - Edit patient's information\n3 - Add new patient's\n4 - Display all users\n5 - Add new users\n0 - Exit\n");
            scanf("%d", &n);
            switch(n)
             {
                case 1:
                    outputPatientInformation(a, &size2);
                    system("pause");
                    break;
                case 2:
                    outputPatientInformation(a, &size2);
                    editPatientInformation(a, &size2);
                    break;
                case 3:
                     addNewPatient(a, &size2);
                    size2++;
                    break;
                case 4:
                    outputUsers(a1, &size1);
                    break;
                case 5:
                    addNewUser(a1, &size1);
                    size1++;
                    break;
                case 0:
                    m=1;
                    break;    
                default:
                    printf("\nYou entered an invalid number. Please try again later.\n");
                    break;
            }
        }
    }
    system("pause");
    return 0;
}
