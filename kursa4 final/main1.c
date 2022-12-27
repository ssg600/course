#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct patient
{
    char surname[20];
    char name[20];
    char patronymic[20];
    int age;
    int dayOfBirth;
    int monthOfBirth;
    int yearOfBirth;
    char sex[10];
    char location[10];
    int contactInformation;
    char diagnosis[15];                                                                                                                                                         
} patients[100];
struct user
{
    char login[15];
    char password[15];
    int role;
} users[50];
int sizeUsers = 0, sizePatients = 0, userNum = 0, role = 0;
void massive_Nulling(char *array, int size)                           
{
    for (int i = 0; i < size; i++)
    {
        *(array + i) = '\000';
    }
}
void logginAgain(int *stopmain)
{
    int n, stop = 0;
    while (stop == 0)
    {
        system("cls");
        printf("1. Log in again\n0. Close programme\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            userNum = 0;
            stop = 1;
            break;
        case 0:
            userNum = -1;
            stop = 1;
            *stopmain = 1;
            break;
        default:
            system("cls");
            printf("Wrong number, please try again\n");
            system("pause");
            break;
        }
    }
}
void authorization(char *login, char *password)
{
    for (int i = 0; i < sizeUsers; i++)
    {
        if (strcmp(users[i].login, login) == 0 && strcmp(users[i].password, password) == 0) 
        {
            userNum = i + 1;              
            role = users[i].role;
            printf("The login was completed succesfully\n");
        }
    }
}
void loginSystem(int *stopmain)
{
    int n, stop;
    char login[15], password[15];
    while (userNum == 0)
    {
        system("cls");
        stop = 0;
        role = 0;
        massive_Nulling(login, 15);
        massive_Nulling(password, 15);
        printf("Login: ");
        scanf("%s", &login);
        printf("Password: ");
        scanf("%s", &password);
        authorization(login, password);
        if (userNum == 0)
        {
            system("cls");
            printf("Wrong login or password\n");
            system("pause");
            logginAgain(stopmain);
        }
    }
    if (userNum != -1)
        system("pause");
}
void adminCreate()
{
    sizeUsers++;
    strcpy(users[0].login, "admin");
    strcpy(users[0].password, "admin");
    users[0].role = 1;
    printf("Admin account was created.\nLogin: admin Password: admin\n");
    system("pause");
}
int loadDatabase()
{
    FILE *fPatients = fopen("database.txt", "rb");
    FILE *fUsers = fopen("users.txt", "r");
    if (fUsers)
    {
        fscanf(fUsers, "%d", &sizeUsers);
        fread(&sizePatients, sizeof(int), 1, fPatients);
        if (sizeUsers > 50)
        {
            printf("The users database is damaged\n");
            system("pause");
            return 1;
        }
        if (sizePatients > 100)
        {
            printf("The patients database is damaged\n");
            system("pause");
            return 1;
        }
        else
        {
            if (sizeUsers > 0)
            {
                for (int i = 0; i < sizeUsers; i++)
                    fscanf(fUsers, "%s %s %d\n", &users[i].login, &users[i].password, &users[i].role);
            }
            if (sizePatients > 0)
                fread(patients, sizeof(struct patient), sizePatients, fPatients);
        }
        fclose(fPatients);
        fclose(fUsers);
    }
    else
        adminCreate();
    return 0;
}
void saveDatabase()
{
    FILE *fPatients = fopen("database.txt", "wb");
    FILE *fUsers = fopen("users.txt", "w");
    fprintf(fUsers, "%d\n", sizeUsers);
    fwrite(&sizePatients, sizeof(int), 1, fPatients);
    if (sizeUsers > 0)
    {
        for (int i = 0; i < sizeUsers; i++)
        {
            fprintf(fUsers, "%s %s %d\n", users[i].login, users[i].password, users[i].role);
        }
    }
    if (sizePatients > 0)
    {
        fwrite(patients, sizeof(struct patient), sizePatients, fPatients);
    }
    fclose(fPatients);
    fclose(fUsers);
}
void outputPatientInformation()
{
    system("cls");
    fflush(stdin);
    if (sizePatients > 0)
    {
        printf("Display information about patient's: \n");
        for (int i = 0; i < sizePatients; i++)
            printf("%d.  <Full Name>: %s %s %s <Full Age>: %d <Date of Birth>: %d/%d/%d <Sex>: %s <Hometown>: %s <Contact Number>: %d <Diagnosis>: %s\n", i + 1, (patients + i)->surname, (patients + i)->name, (patients + i)->patronymic, (patients + i)->age, (patients + i)->dayOfBirth, (patients + i)->monthOfBirth, (patients + i)->yearOfBirth, (patients + i)->sex, (patients + i)->location, (patients + i)->contactInformation, (patients + i)->diagnosis);
    }
    else
        printf("There are no patients in the database\n");
}
void addNewPatient()
{
    system("cls");
    fflush(stdin);
    printf("Enter Patient Full Name: ");
    scanf("%s %s %s", &(patients + sizePatients)->surname, &(patients + sizePatients)->name, &(patients + sizePatients)->patronymic);
    printf("Enter Patient Age: ");
    scanf("%d", &(patients + sizePatients)->age);
    printf("Enter Patient Date of Birth: ");
    scanf("%d %d %d", &(patients + sizePatients)->dayOfBirth, &(patients + sizePatients)->monthOfBirth, &(patients + sizePatients)->yearOfBirth);
    printf("Enter Patient sex: ");
    scanf("%s", &((patients + sizePatients)->sex));
    printf("Enter Patient hometown: ");
    scanf("%s", &((patients + sizePatients)->location));
    printf("Enter Patient contact inormation: ");
    scanf("%d", &((patients + sizePatients)->contactInformation));
    printf("Enter Patient diagnosis: ");
    scanf("%s", &((patients + sizePatients)->diagnosis));
    printf("New patient was added\n");
    sizePatients++;
    system("pause");
}
void editPatientInformation()
{
    int n, stop = 0, n1, stop1;
    while (stop == 0)
    {
        outputPatientInformation();
        if (sizePatients > 0)
        {
            printf("Enter patient number (0. Exit): ");
            scanf("%d", &n1);
            stop1 = 0;
            if ((n1 < 0) || (n1 > sizePatients))
                printf("Wrong number, please try again\n");
            else if (n1 == 0)
                stop = 1;
            else
                while (stop1 == 0)
                {
                    system("cls");
                    printf("\n1. Edit Surname\n2. Edit Name\n3. Edit Patronymic\n4. Edit Age of Patient\n5 - Edit Date of Birth");
                    printf("\n6 - Edit Sex\n7 - Edit Location\n8 - Edit Contact Information\n9 - Edit Diagnosis\n0 - Exit\n");
                    scanf("%d", &n);
                    switch (n)
                    {
                    case 1:
                        printf("\nEnter new surname: ");
                        scanf("%s", &patients[n1 - 1].surname);
                        printf("Patient surname has been changed\n");
                        break;
                    case 2:
                        printf("\nEnter new name: ");
                        scanf("%s", &patients[n1 - 1].name);
                        printf("Patient name has been changed\n");
                        break;   
                    case 3:
                        printf("\nEnter new patronymic: ");
                        scanf("%s", &patients[n1 - 1].patronymic);
                        printf("Patient patronymic has been changed\n");
                        break;
                    case 4:
                        printf("\nEnter new age: ");
                        scanf("%s", &patients[n-1].age);
                        break;    
                    case 5:
                        printf("\nEnter new Date of Birth: ");
                        scanf("%d.%d.%d", &patients[n1 - 1].dayOfBirth, &patients[n1 - 1].monthOfBirth, &patients[n1 - 1].yearOfBirth);
                        printf("Patient Date of Birh has been changed\n");
                        break;
                    case 6:
                        printf("\nEnter new sex: ");
                        scanf("%s", &patients[n1 - 1].sex);
                        printf("Patient sex has been changed\n");
                        break;
                    case 7:
                        printf("\nEnter new location: ");
                        scanf("%s", &patients[n1 - 1].location);
                        printf("Arrival time has been changed\n");
                        break;
                    case 8:
                        printf("\nEnter new contact information: ");
                        scanf("%d", &patients[n1 - 1].contactInformation);
                        printf("Contact Information has been changed\n");
                        break;
                    case 9:
                        printf("\nEnter new diagnosis: ");
                        scanf("%s", &patients[n1 - 1].diagnosis);
                        printf("Diagnosis has been changed\n");
                        break;
                    case 0:
                        stop1 = 1;
                        break;
                    default:
                        printf("Wrong number, please try again\n");
                        break;
                    }
                }
        }
        else
        {
            stop = 1;
            system("pause");
        }
    }
}
void deletePatient()
{
    int stop = 0, n, i;
    while (stop == 0)
    {
        outputPatientInformation();
        if (sizePatients > 0)
        {
            printf("Enter patient number (0. Exit): ");
            scanf("%d", &n);
            if ((n < 0) || (n > sizePatients))
                printf("Wrong number, please try again\n");
            else if (n == 0)
                stop = 1;
            else
            {
                for (i = n - 1; i < sizePatients - 1; i++)
                {
                    strcpy(patients[i].surname, patients[i+1].surname);
                    strcpy(patients[i].name, patients[i+1].name);
                    strcpy(patients[i].patronymic, patients[i+1].patronymic);
                    patients[i].age = patients[i + 1].age;
                    patients[i].dayOfBirth = patients[i + 1].dayOfBirth;
                    patients[i].monthOfBirth = patients[i + 1].monthOfBirth;
                    patients[i].yearOfBirth = patients[i + 1].yearOfBirth;
                    strcpy(patients[i].sex, patients[i+1].sex);
                    strcpy(patients[i].location, patients[i+1].location);
                    patients[i].contactInformation = patients[i + 1].contactInformation;
                    strcpy(patients[i].diagnosis, patients[i+1].diagnosis);
                }
                sizeUsers--;
                printf("Patient deleted successfully\n");
            }
        }
        else
        {
            stop = 1;
            system("pause");
        }
    }
}
void searchByAgeAndDiagnosis()
{
    char diagnosis[30];
    int i, age;
    system("cls");
    if (sizePatients == 0)
        printf("There are no patients in the database\n");
    else
    {
        printf("Enter a diagnosis: ");
        scanf("%s", &diagnosis);
        printf("Enter the age by which you want to find a patients: ");
        scanf("%d", &age);
    for (i = 0; i < sizePatients; i++)
    {
        if (strcmp((patients + i)->diagnosis, diagnosis) == 0 && patients[i].age == age)
        {
            printf("%d.  <Full Name>: %s %s %s <Full Age>: %d <Date of Birth>: %d/%d/%d <Diagnosis>: %s\n", i + 1, (patients + i)->surname, (patients + i)->name, (patients + i)->patronymic, (patients + i)->age, (patients + i)->dayOfBirth, (patients + i)->monthOfBirth, (patients + i)->yearOfBirth, (patients + i)->diagnosis);
        }
    }
    system("pause");
}
}
void searchNonResedentPatient()
{
    char location[20];
    system("cls");
    if (sizePatients == 0)
        printf("There are no patients in the database\n");
    else
    {
        printf("Enter hospital location: ");
        scanf("%s", &location);
        for (int i = 0; i < sizePatients; i++)
        {
            if (strcmp(patients[i].location, location) != 0)
            {
                printf("%d.  <Full Name>: %s %s %s <Full Age>: %d <Date of Birth>: %d/%d/%d <Sex>: %s <Hometown>: %s <Contact Number>: %d <Diagnosis>: %s\n", i + 1, (patients + i)->surname, (patients + i)->name, (patients + i)->patronymic, (patients + i)->age, (patients + i)->dayOfBirth, (patients + i)->monthOfBirth, (patients + i)->yearOfBirth, (patients + i)->sex, (patients + i)->location, (patients + i)->contactInformation, (patients + i)->diagnosis);
            }
        }    
    }
}
void outputUsers()
{
    system("cls");
    printf("A list of users:\n");
    for (int i = 0; i < sizeUsers; i++)
        printf("%d. Login: %s  Password: %s  Role: %d\n", i + 1, (users + i)->login, (users + i)->password, (users + i)->role);
}
void addNewUser()
{
    int i, stop = 0;
    while (stop == 0)
    {
        system("cls");
        stop = 1;
        printf("Enter Login: ");
        scanf("%s", &((users + sizeUsers)->login));
        for (i = 0; i < sizeUsers; i++)
        {
            if (strcmp((users + sizeUsers)->login, (users + i)->login) == 0)
            {
                printf("This login already exists\n");
                stop = 0;
                system("pause");
                break;
            }
        }
    }
    if (stop == 1)
    {
        printf("Enter Password: ");
        scanf("%s", &((users + sizeUsers)->password));
        while (stop == 1)
        {
            printf("Enter Role(1-admin or 2-user): ");
            scanf("%d", &((users + sizeUsers)->role));
            if ((users + sizeUsers)->role == 1 || (users + sizeUsers)->role == 2)
            {
                printf("New user was added\n");
                sizeUsers++;
                stop = 0;
                system("pause");
            }
            else
            {
                printf("Wrong number of role, please try again\n");
                system("pause");
            }
        }
    }
}
void editUsers()
{
    int stop = 0, n, stop1, n1, stop2;
    while (stop == 0)
    {
        outputUsers();
        stop1 = 0;
        stop2 = 0;
        printf("Enter number of user(0-Exit): ");
        scanf("%d", &n);
        if ((n < 0) || (n > sizeUsers))
            printf("Wrong number, please try again\n");
        else if (n == 0)
            stop = 1;
        else
            while (stop1 == 0)
            {
                printf("1. Edit login\n2. Edit password\n3. Edit users role\n0 - Exit\n");
                scanf("%d", &n1);
                switch (n1)
                {
                case 1:
                    system("cls");
                    printf("Enter new login: ");
                    scanf("%s", &(users + n - 1)->login);
                    printf("Login has been changed\n");
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    printf("Enter new password: ");
                    scanf("%s", &(users + n - 1)->password);
                    printf("Password has been changed\n");
                    system("pause");
                    break;
                case 3:
                    while (stop2 == 0)
                    {
                        system("cls");
                        printf("Enter new role(1-admin or 2-user): ");
                        scanf("%d", &(users + n - 1)->role);
                        if ((users + n - 1)->role == 1 || (users + n - 1)->role == 2)
                            stop2 = 1;
                        else
                            printf("Wrong number, please try again\n");
                    }
                    printf("Role has been changed\n");
                    system("pause");
                    break;
                case 0:
                    stop1 = 1;
                    break;
                default:
                    system("cls");
                    printf("Wrong number, please try again\n");
                    system("pause");
                    break;
                }
            }
    }
}
void deleteUsers()
{
    int stop = 0, n;
    while (stop == 0)
    {
        system("cls");
        outputUsers();
        printf("Enter number of user(0-Exit): ");
        scanf("%d", &n);
        if ((n < 0) || (n > sizeUsers))
            printf("Wrong number, please try again\n");
        else if (n == 0)
            stop = 1;
        else if (n == userNum)
        {
            printf("You can't delete an active user\n");
            system("pause");
        }
        else
        {
            for (int i = n - 1; i < sizeUsers - 1; i++)
            {
                strcpy((users + i)->login, (users + i + 1)->login);
                strcpy((users + i)->password, (users + i + 1)->password);
                (users + i)->role = (users + i + 1)->role;
            }
            sizeUsers--;
            if (userNum > n)
                userNum--;
            printf("User was deleted\n");
            system("pause");
        }
    }
}
void userInteraction()
{
    int stop = 0, n;
    while (stop == 0)
    {
        system("cls");
        printf("1. Display all users\n2. Add new user\n3. Edit user\n4. Delete user\n0. Exit\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            outputUsers();
            system("pause");
            break;
        case 2:
            addNewUser();
            break;
        case 3:
            editUsers();
            break;
        case 4:
            deleteUsers();
            break;
        case 0:
            stop = 1;
            break;
        default:
            printf("Wrong number, please try again\n");
            system("pause");
            break;
        }
    }
}
void patientInteraction()
{
    int stop = 0, n;
    while (stop == 0)
    {
        system("cls");
        printf("1. Display Patient Information\n2. Add new Patient\n3. Edit Patient information\n4. Delete Patient from database\n5. Search by age and diagnosis\n6. Search nonresedent patient\n0. Exit\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            outputPatientInformation();
            system("pause");
            break;
        case 2:
            addNewPatient();
            break;
        case 3:
            editPatientInformation();
            system("pause");
        case 4:
            deletePatient();    
            break;
        case 5:
            searchByAgeAndDiagnosis();
            break;
        case 6:
            searchNonResedentPatient();
            system("pause");
  
        case 0:
            stop = 1;
            break;
        default:
            printf("Wrong number, please try again\n");
            system("pause");
            break;
        }
    }
}
void userMenu() // Меню возможностей обычного пользователя
{
    int stop = 0, n;
    while (stop == 0)
    {
        system("cls");
        printf("1. Display patient information\n2. Search by age and diagnosis\n3. Search nonresedent patient\n0. Log out\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            outputPatientInformation();
            system("pause");
            break;
        case 2:
            searchByAgeAndDiagnosis();
            break;
        case 3:
            searchNonResedentPatient();
            system("pause");
        case 0:
            stop = 1;
            userNum = 0;
            break;
        default:
            printf("Wrong number, please try again\n");
            break;
        }
    }
}
void adminMenu()
{
    int stop = 0, n;
    while (stop == 0)
    {
        system("cls");
        printf("1. Users Panel\n2. Patients Panel\n0. Log out\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            userInteraction();
            break;
        case 2:
            patientInteraction();
            break;
        case 0:
            stop = 1;
            userNum = 0;
            break;
        default:
            printf("Wrong number, please try again\n");
            system("pause");
            break;
        }
    }
}
int main()
{
    int stopmain = 0;
    if (loadDatabase() == 0)
    {
        while (stopmain == 0)
        {
            system("cls");
            loginSystem(&stopmain);
            if (role == 2)
                userMenu();
            else if (role == 1)
                adminMenu();
            if (userNum == 0)
                logginAgain(&stopmain);
        }
        saveDatabase();
    }
    return 0;
}