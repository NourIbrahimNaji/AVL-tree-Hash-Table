///P3_1190270_Nour Naji_SectionNo.2”

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 40

//the node structure containing multiple data with different types .
struct AVLnode
{
    char PatientName[MAX];
    char Gender[MAX] ;
    int Dateofadmission ;
    int Dateofbirth ;
    char Illness[MAX] ;
    char Address[MAX] ;
    char Bloodtype[MAX];
    // pointer to the left and right elements .
    struct AVLnode* Left;
    struct AVLnode* Right;
    //Balance information
    int H;
};
// define a pointer of structure as an new data type.
typedef struct AVLnode *node ;
node Tree = NULL ;
//the node structure containing multiple data with different types and a status value
typedef struct HAShtable
{
    int status;
    /*
    * status = Empty (0) : data not present
    * status = collision (1): some data already present
    * status = deleted  (2): data was present,but deleted
    */
    char PatientName[MAX];
    char Gender[MAX];
    int Dateofadmission;
    int Dateofbirth ;
    char Illness[MAX];
    char Address[MAX];
    char Bloodtype[MAX];

} ;
// define a pointer of structure as an new data type.
struct HAShtable * Array;
struct HAShtable *newHashTable;
// local variable
int size = 0;
int tableSize = 107;
// HIGHT OF TERR
int Height(node T)
{
    if(T==NULL) // IF TREE IS EMPTY
        return -1;
    return T->H; // RETURN HIGHT OF TERR
}
// MAX OF TERR
int Max( int T1, int T2 )
{
    if(T1 > T2)
        return T1;
    return T2;
}
//Rotate between two nodes...
//to rotate to the right one time
node singleRotateRight(node T)
{
    node T2 ;
    T2 = T->Left;
    T->Left = T2->Right;
    T2->Right = T;

    T->H = Max( Height( T2->Right ), Height( T2->Left ) ) + 1;
    T2->H = Max( Height( T ),Height( T2->Right ) ) + 1;
    return T;
}
//to rotate to the left one time
node singleRotateLeft(node T)
{
    node  T2;
    T2 = T->Right;
    T->Right = T2->Left;
    T2->Left = T;

    T->H = Max(Height( T->Right), Height( T->Left)) + 1;
    T2->H = Max(Height( T),Height( T2->Right)) + 1;
    return T2;
}
//left right rotation
node doubleRotateRight(node T)
{
    T->Right = singleRotateRight(T->Right);
    return singleRotateLeft(T);
}
//right left rotation
node doubleRotateLeft(node T)
{
    T->Right = singleRotateLeft(T->Left);
    return singleRotateRight(T);
}
//return the difference between left and right node
int B(node n )
{
    if (n == NULL)
        return 0 ;
    return Height(n->Left) - Height(n->Right);
}
//to change a string into a lowercase string
char * ToLower(char s [])
{
    int length=strlen(s);
    char *T = malloc(length);
    for(int i=0; i < strlen(s); i++)
    {
        T[i] = tolower(s[i]);
    }
    return T;
}
//creating the tree with the data from the text document...
node  insertAVL(node n, char name[], char Gender[], int D_admission, int D_birth, char Illness[], char Address[], char Blood[])
{
    if (n == NULL)
    {
        //create new data to insert
        n = malloc( sizeof( struct AVLnode ));
        if( n == NULL )
            printf( "Out of space!!! \n" );
        else
        {
            strcpy(n->PatientName,name);
            strcpy(n->Gender,Gender);
            n->Dateofadmission = D_admission;
            n->Dateofbirth = D_birth ;
            strcpy(n->Illness,Illness);
            strcpy(n->Address,Address);
            strcpy(n->Bloodtype,Blood);
            n->Left = NULL ;
            n->Right = NULL ;

        }
    }
    else if(strcmp(ToLower(name),ToLower(n->PatientName))>=0)
    {
        n->Right = insertAVL(n->Right,name,Gender,D_admission,D_birth,Illness,Address,Blood);
        if(B(n) == 2)
        {
            if (strcmp(name,n->Right->PatientName)>0)
                n = singleRotateRight(n);
            else
                n = doubleRotateLeft(n);
        }

    }
    else if(strcmp(ToLower(name),ToLower(n->PatientName))<0)
    {
        n->Left = insertAVL(n->Left,name,Gender,D_admission,D_birth,Illness,Address,Blood);
        if(B(n) == -2)
        {
            if (strcmp(name,n->Left->PatientName)<0)
                n = singleRotateLeft(n);
            else
                n = doubleRotateRight(n);
        }
    }
    n->H = 1 + Max(Height(n->Left), Height(n->Right));
    return n;
}
//function to find the Patients using the Patients name
node find(char name[], node T)
{
    if (T != NULL)
    {
        if(strcmp(ToLower(name),ToLower(T->PatientName)) < 0)
            return (find(name, T->Left));
        else if(strcmp(ToLower(name),ToLower(T->PatientName))>0)
            return (find(name, T->Right));
        else if(strcmp(ToLower(name),ToLower(T->PatientName)) ==0)
            return T ;
    }
    else
    {
        puts("The Tree is not fined \n");
    }
}
//to find the minimum node
node findmin(node n)
{
    if (n == NULL)
        return -1 ;
    else
    {
        if (n->Left == NULL)
            return n ;
        return(findmin(n->Left));
    }
}
//Delete Patient
node DeletePatient(node n, char *name)
{
    node temp = NULL;
    if(n == NULL)
    {
        printf("Tree is empty .. :( \n");
        return n;
    }
    else if(strcmp(ToLower(name),ToLower(n->PatientName))<0)
        n->Left = DeletePatient(n->Left, name);
    else if (strcmp(ToLower(name),ToLower(n->PatientName))>0)
        n->Right = DeletePatient(n->Right, name);
    else
    {
        //case OF r one child
        if (n->Left == NULL && n->Right != NULL)
        {
            temp = n ;
            n = n->Right;
            //then delete the node
            free(temp);
            return n ;

        }
        //case  OF one child
        else if (n->Left != NULL && n->Right == NULL)
        {
            temp = n ;
            n = n->Left;
            //then delete the node
            free(temp);
            return n ;

        }
        //case OF zero child
        else if (n->Left == NULL && n->Right == NULL)
        {
            temp = n;
            n = NULL ;
            //then delete the node
            free(n);

        }
        else
        {
            //case for two children
            temp = findmin(n->Right);
            strcpy(n->PatientName,temp->PatientName);
            strcpy(n->Gender,temp->Gender);
            n->Dateofadmission = temp->Dateofadmission;
            n->Dateofbirth = temp->Dateofbirth ;
            strcpy(n->Illness,temp->Illness);
            strcpy(n->Address,temp->Address);
            strcpy(n->Bloodtype, temp->Bloodtype);
            n->Right= DeletePatient(n->Right, temp->PatientName);

        }
    }
    //balances ..
    if (n == NULL)
    {
        if( B(n)  == 2 )
        {
            if(B(n->Left) == -1)
                return singleRotateRight(n);
            else if(B(n->Left) == 1)
                return doubleRotateLeft(n);
        }
        if( B(n)  == -2 )
        {
            if(B(n->Right) == -1)
                return singleRotateLeft(n);
            else if(B(n->Right) == 1)
                return doubleRotateRight(n);
        }
    }

    return n ;
}
//function to change the data
void update(node q)
{
    printf(" > \n Search for the name of the patient  you want to update his information .. \n");
    char name[30];
    getchar();
    gets(name);
    node T = find(name,q);
    if (T == NULL)
        puts("NOT FINED patient..!");
    else
    {
        char newname[20], newGender[20],newIllness[30],newAddress[30], newBlood[20];
        int newD_admission, newD_birth;
        printf(" > Do you want to update patient information? \n");
        printf(" 1. YES  \n   2.NO  \n");
        int a;
        scanf("%d",&a);
        if (a == 1)
        {
            puts("If you want to change the name, press 1,,Other than that, press any number");
            int a ;
            scanf("%d", &a);
            if (a == 1)
            {
                puts("Enter the new name :");
                gets(newname);
                gets(newname);
                strcpy(newname,strtok(newname,"\n"));
            }
            else
                strcpy(newname,T->PatientName);
            puts("If you want to change the Gender, press 2 ,,Other than that, press any number");
            int b ;
            scanf("%d", &b);
            if (b ==2)
            {
                puts("Enter the new Gender :");
                gets(newGender);
                gets(newGender);
                strcpy(newGender,strtok(newGender,"\n"));
            }
            else
                strcpy(newGender,T->Gender);
            puts("If you want to change the Date of admission, press 3,,Other than that, press any number");
            int c ;
            scanf("%d", &c);
            if (c==3)
            {
                puts("Enter the new Date of admission :");
                scanf("%d", &newD_admission);
            }
            else
                newD_admission = T->Dateofadmission ;

            puts("If you want to change the Date of birth, press 4,,Other than that, press any number");
            int d ;
            scanf("%d", &d);
            if (d==4)
            {
                puts("Enter the new Date of birth :");
                scanf("%d", &newD_birth);
            }
            else
                newD_birth = T->Dateofbirth ;
            puts("If you want to change the The type of disease, press 5,,Other than that, press any number");
            int e ;
            scanf("%d", &e);
            if (e==5)
            {
                puts("Enter the new type of disease :");
                gets(newIllness);
                gets(newIllness);
                strcpy(newIllness,strtok(newIllness,"\n"));

            }
            else
                strcpy(newIllness,T->Illness);
            puts("If you want to change the Address (City), press 6,,Other than that, press any number");
            int f ;
            scanf("%d", &f);
            if (f==6)
            {
                puts("Enter the new Address :");
                gets(newAddress);
                gets(newAddress);
                strcpy(newAddress,strtok(newAddress,"\n"));

            }
            else
                strcpy(newAddress,T->Address);
            puts("If you want to change the Blood type, press 7,,Other than that, press any number");
            int g ;
            scanf("%d", &g);
            if (g==7)
            {
                puts("Enter the new Blood type :");
                gets(newBlood);
                gets(newBlood);
                strcpy(newBlood,strtok(newBlood,"\n"));

            }
            else
                strcpy(newBlood,T->Bloodtype);
            q = DeletePatient(q,name);
            q = insertAVL(q,newname,newGender,newD_admission,newD_birth,newIllness,newAddress,newBlood);
            PrintInOrder(q);
            puts(" >successfully update .. :)");

        }

        else if (a ==2)
        {
            puts(" >ok .. :)");

        }
        else
            puts(" >Wrong !!");

    }
}
node readFile(FILE* infile,node Tree )
{
    char string[200],*token;

    if (infile == NULL)
    {
        printf("File does not exist..!!\n");
        exit(1);
    }
    //if the file is successfully opened..
    else
    {
        char name_p[MAX], G[MAX],Illness[MAX],city[MAX],blood[MAX] ;
        int Date_admission, Date_birth;
        while(fgets(string,200, infile)!=NULL)
        {
            int *H = "#" ;
            //to split the new-line character from the read string by using #
            char *token =  strtok(string, H);
            int counter = 0;
            while(token != NULL)
            {
                if (counter ==0)
                    strcpy(name_p, token);
                else if (counter ==1)
                    strcpy(G, token);
                else if (counter ==2)
                    //atoi is used for converting from string to integer
                    Date_admission=atoi(token);
                else if (counter ==3)
                    //atoi is used for converting from string to integer
                    Date_birth=atoi(token);
                else if (counter ==4)
                    strcpy(Illness, token);
                else if (counter ==5)
                    strcpy(city, token);
                else if (counter ==6)
                    strcpy(blood, token);
                token = strtok(NULL, H);
                counter++;
                //END ROF LINE..
                if (counter ==7)
                {
                    Tree= insertAVL(Tree,name_p,G,Date_admission,Date_birth,Illness,city,blood);
                    counter = 0 ;
                }
            }
        }
    }
    return(Tree);
}
//function to insert a new patient in the tree
node Insertnewpatient(node T)
{
    char name[MAX], Gender[MAX],Illness[MAX],Address[MAX], Blood[MAX];
    int D_admission, D_birth;
    printf("Please enter name of the patient:\n");
    gets(name);
    gets(name);
    printf("Gender :\n");
    gets(Gender);
    printf("Date of admission :\n");
    scanf("%d", &D_admission);
    printf("Date of birth :\n");
    scanf("%d", &D_birth);
    printf("The type of disease :\n");
    getchar();
    gets(Illness);
    printf("Address :\n");
    gets(Address);
    printf("blood type :\n");
    //getchar();
    gets(Blood);
    T= insertAVL(T,name,Gender, D_admission,D_birth,Illness,Address,Blood);
    return T;
}
//function to find All Patients That Have The Same Illness
node findAllPatientsThatHaveTheSameIllness(char illness[], node T)
{
    if(T == NULL)
    {
        printf("The Tree is not fined \n");
        return NULL ;
    }
    else
    {
        if(T->Left!=NULL)
            findAllPatientsThatHaveTheSameIllness(illness, T->Left );
        if(T->Right!=NULL)
            findAllPatientsThatHaveTheSameIllness(illness, T->Right );

        if(strcmp(ToLower(T->Illness), ToLower(illness)) == 0)
        {
            printf("%-20s\t", T->PatientName);
            printf("%-20s\t", T->Gender);
            printf("%-10d\t", T->Dateofadmission);
            printf("%-10d\t", T->Dateofbirth);
            printf("%-20s\t", T->Illness);
            printf("%-20s\t", T->Address);
            printf("%-20s\t\n", T->Bloodtype);
        }


    }
}
//in-order print to see the elements
void PrintInOrder(node t)
{
    if( t != NULL)
    {
        PrintInOrder(t->Left);
        printf("%-20s\t", t->PatientName);
        printf("%-20s\t", t->Gender);
        printf("%-10d\t", t->Dateofadmission);
        printf("%-10d\t", t->Dateofbirth);
        printf("%-20s\t", t->Illness);
        printf("%-20s\t", t->Address);
        printf("%-20s\t \n", t->Bloodtype);
        PrintInOrder(t->Right );
    }
}
void save(node T)
{
    FILE* outfile;
    //opening the file
    outfile = fopen("patients_hash.data","w");
    fclose(outfile);
    Ssave(T);
}
void Ssave(node T)
{
    if (T != NULL)
    {
        // go to lift
        Ssave(T->Left);
        FILE* outfile;
        //opening the file
        outfile = fopen("patients_hash.data","a");
        fprintf(outfile,"%s#%s#%d#%d#%s#%s#%s", T->PatientName, T->Gender, T->Dateofadmission, T->Dateofbirth,T->Illness, T->Address, T->Bloodtype);
        fprintf(outfile,"\n");
        fclose(outfile);
        //go to write
        Ssave(T->Right);
    }
}
///-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
///  >> HASH PART ...
unsigned int hash (char name[])
{
    unsigned int hash_Value = 0 ;
    for (int i =0 ; i < strlen(name) ; i++)
    {
        hash_Value += (int)name[i];
        hash_Value = (hash_Value ) % tableSize ;
    }
    return hash_Value ;
}
void initialHash()
{
    for (int i=0 ; i< tableSize ; i++)
    {
        Array[i].status = 0;

    }
}
//Rehash table and update Size table
void Rehash()
{
    puts("<<<<<<<<<<<<Rehash >>>>>>>>>>>>>>>");
    char name[30],Gender[20],Illness[30],Address[30],Blood[30];
    int D_admission, D_birth ;
    int Hash = hash(name);
    int i = Hash ;
    int oldSiz = tableSize;
    //allocating the needed size
    newHashTable = (struct HAShtable*) malloc(oldSiz* sizeof(struct HAShtable));
    newHashTable == Array;
    //inserting the old size to the new one
    tableSize = 2* tableSize +1;
    Array = (struct HAShtable*) malloc(tableSize * sizeof(struct HAShtable*));
    for (int j=0 ; j< oldSiz ; j++)
        Array[j].status = 0;
    size =0;
    for (int j=0 ; j< tableSize ; j++)
        if (newHashTable[i].status == 1)
            insertHASH(newHashTable[i].PatientName,newHashTable[i].Gender,newHashTable[i].Dateofadmission,newHashTable[i].Dateofbirth,newHashTable[i].Illness,newHashTable[i].Address,newHashTable[i].Bloodtype);
    newHashTable[i].status = 1;

}
void insertHASH(char name[], char Gender[], int D_admission, int D_birth, char Illness[], char Address[], char Blood[])
{
    int Hash = hash(name);
    printf(" sum of all characters in ASCII code in the name ->(%s) % max size of hash table =  %d \n",name, Hash);
    int i = Hash ;
    if(Array[i].status == 1 || Array[i].status == 2)
    {
        i ++ ;
        i %= tableSize ;
    }
    //if (size > tableSize*0.7)
    //    Rehash();
    strcpy(Array[i].PatientName,name);
    strcpy(Array[i].Gender,Gender);
    Array[i].Dateofadmission = D_admission;
    Array[i].Dateofbirth =D_birth ;
    strcpy(Array[i].Illness,Illness);
    strcpy( Array[i].Address,Address);
    strcpy(Array[i].Bloodtype,Blood);
    Array[i].status = 1;
    size++;
}
//to remove an element from the array
void DeleteAspecificRecord(char name[])
{
    int Hash = hash(name);
    int i = Hash ;
    if (Array[i].status == 1)
    {
        if (strcmp(Array[i].PatientName, name)==0)
        {
            Array[i].status = 2;
            size -- ;

        }
        else
            puts("NOT FINED patient..!");
    }
    else if (Array[i].status == 2)
        printf(" > Array[%d] --> : Deleted !! \n", i);

}
void searchAspecificRecord(char *name)
{
    int Hash = hash(name);
    int i = Hash ;
    if (size == 0)
        puts(" >Hash Table is empty .. :(");
    else
    {
        if (Array[i].status == 1)
        {
            if (strcmp(Array[i].PatientName, name)==0)
            {
                printf(" > Array[%d] --> : ", i);
                printf("%-20s\t", Array[i].PatientName);
                printf("%-20\t", Array[i].Gender);
                printf("%-10d\t", Array[i].Dateofadmission);
                printf("%-10d\t", Array[i].Dateofbirth);
                printf("%-20s\t", Array[i].Illness);
                printf("%-20s\t", Array[i].Address);
                printf("%-20s\t \n", Array[i].Bloodtype);
            }
        }

        else
            puts("NOT FINED patient..! <<<Deleted>>>");
    }
}
void printfHash()
{
    for (int i =0 ; i< tableSize ; i++)
    {

        if (Array[i].status == 0)
            printf(" > Array[%d] --> : ---- \n", i);
        else if (Array[i].status == 2)
            printf(" > Array[%d] --> : Deleted !! \n", i);
        else
        {
            //Array[i].status == 1
            printf(" > Array[%d] --> : ", i);
            printf("%-20s\t", Array[i].PatientName);
            printf("%-20\t", Array[i].Gender);
            printf("%-10d\t", Array[i].Dateofadmission);
            printf("%-10d\t", Array[i].Dateofbirth);
            printf("%-20s\t", Array[i].Illness);
            printf("%-20s\t", Array[i].Address);
            printf("%-20s\t \n", Array[i].Bloodtype);
        }
    }
}
void readFiletounsertinhashtable()
{
    FILE* outfile;
    outfile = fopen("patients_hash.data","r");
    char string[200],*token;
    if (outfile == NULL)
    {
        printf("File does not exist..!!\n");
        exit(1);
    }
    else
    {
        char name_p[MAX];
        char G[MAX];
        int Date_admission;
        int Date_birth;
        char Illness[MAX];
        char Address[MAX];
        char blood[MAX];
        while(fgets(string, 200, outfile) !=NULL)
        {
            int *H = "#" ;
            char *token =  strtok(string, H);
            int counter = 0;
            while(token != NULL)
            {
                if (counter ==0)
                    strcpy(name_p, token);
                else if (counter ==1)
                    strcpy(G, token);
                else if (counter ==2)
                    Date_admission=atoi(token); //atoi is used for converting from string to integer
                else if (counter ==3)
                    Date_birth=atoi(token);
                else if (counter ==4)
                    strcpy(Illness, token);
                else if (counter ==5)
                    strcpy(Address, token);
                else if (counter ==6)
                    strcpy(blood, token);
                token = strtok(NULL, H);
                counter++;

                if (counter ==7)
                {
                    insertHASH(name_p,G,Date_admission,Date_birth,Illness,Address,blood);
                    counter = 0 ;
                }
            }
        }
    }
    fclose(outfile);
}
void size_of_hashtable()
{
    printf("the size of Hash Table  =  %d \n", tableSize);
    printf("The number of places reserved in the Hash table =  %d \n ", size);

}
void saveHashTable()
{
    FILE* outfile;
    outfile = fopen("patients_hash.data","w");
    for(int i =0 ; i < tableSize ; i++)
    {
        if (Array[i].status == 1)
        {
            fprintf(outfile, "Array [%d] -> ", i );
            fprintf(outfile,"%-20s\t", Array[i].PatientName);
            fprintf(outfile,"%-20\t", Array[i].Gender);
            fprintf(outfile,"%-10d\t", Array[i].Dateofadmission);
            fprintf(outfile,"%-10d\t", Array[i].Dateofbirth);
            fprintf(outfile,"%-20s\t", Array[i].Illness);
            fprintf(outfile,"%-20s\t", Array[i].Address);
            fprintf(outfile,"%-20s\t", Array[i].Bloodtype);
            fprintf(outfile,"\n");
        }
        else if (Array[i].status == 2)
            fprintf(outfile,"Array[%d] --> : Deleted !! \n", i);

        else
            fprintf(outfile, "Array [%d] ->  --- \n", i );
    }
    fclose(outfile);
}
// system menu.
void showMenu()
{
    printf("\n<<< Menu >>>\n1. Read the File that contains the patient. \n2.Print Tree .\n3. Insert a new patient.");
    printf("\n4. Find a patient and update the information of the patient. \n5. List all patients in lexicographic order with their associated information.\n");
    printf("6. List all patients that have the same illness.\n7. Delete a patient from the system.");
    printf("\n8. Save the result. \n9.create a Hash Table using the patients data of the previous step (use names as keys).\n");
}
// system menu.
void showMenu_2()
{
    printf("\n<<< Menu_2 >>>\n1.Print hashed table.\n2.Print out table size. ");
    printf("\n3.Print out the used hash function. \n4. Insert a new record into the hash table. \n");
    printf("5. Search for a specific patient. \n6. Delete a specific record. \n7. Save hash table back to file.\n8. Exit the system.\n");
}
// main function
int main()
{
    puts("Welcome to our system...");
    puts("This system helps you manage patients data in a hospital.");
    puts(" The hospital patient management system stores specific information in the form of health record to keep track of the patients data. \n");
    puts("***The below menu show you what you can do using this system, please select what the choice you want :).***");
    FILE* infile;
    // opening the file.
    infile = fopen("patients.txt","r");
    int x, y, n;
    Tree = readFile(infile, Tree);
    Array = (struct HAShtable*) malloc(tableSize * sizeof(struct HAShtable));
    char name[20], Gender[20],Illness[30],Address[30], Blood[20];
    int D_admission, D_birth;
    initialHash();

    while(x!=10)
    {
        //printing the main menu with the options
        showMenu();
        scanf("%d",&x);
        switch (x)
        {
        case 1:
            printf(" >Reading from the file and storing in the tree successfully completed .. :) \n");
            break;
        case 2:
            PrintInOrder(Tree);
            break;
        case 3:
            Insertnewpatient(Tree);
            puts("The Tree afrer Insert : ");
            PrintInOrder(Tree);
            break;
        case 4:
            update(Tree);
            break;
        case 5:
            PrintInOrder(Tree);
            break;
        case 6:
            printf(" \n >Enter the name of the disease.. \n");
            char  illness[30];
            getchar();
            gets(illness);
            findAllPatientsThatHaveTheSameIllness(illness,Tree);

            break;
        case 7:
            printf(" \n >Enter the name of the patient you want to delete .. \n");
            char  name_d[30];
            getchar();
            gets(name_d);
            node e = find(name_d,Tree);
            if(e != NULL)
            {
                DeletePatient(Tree,name_d);
                printf(" >Successfully Deleted ..:) \n");
            }
            else
                printf(" >The given patient is not found .\n");

            break;
        case 8:
            save(Tree);
            printf(" >Successfully saved to the file.. :) \n");
            break;

        case 9:
            while(y!=9)
            {
                //printing the main menu with the options
                showMenu_2();
                scanf("%d",&y);

                switch (y)
                {
                case 1:
                    readFiletounsertinhashtable();
                    printfHash();
                    break;
                case 2:
                    size_of_hashtable();
                    break;
                case 3:
                    puts(" <<< Print out the used hash function >>> ");
                    puts("Open Addressing --> Linear Probing");
                    puts("hash function --> sum of all characters  in ASCII code % max size of hash table ..");
                    break;
                case 4:
                    puts(" >  Insert a new record into the hash table");
                    printf("Please enter name of the patient:\n");
                    getchar();
                    gets(name);
                    printf("Gender :\n");
                    gets(Gender);
                    printf("Date of admission :\n");
                    scanf("%d", &D_admission);
                    printf("Date of birth :\n");
                    scanf("%d", &D_birth);
                    printf("The type of disease :\n");
                    getchar();
                    gets(Illness);
                    printf("Address :\n");
                    gets(Address);
                    printf("blood type :\n");
                    gets(Blood);
                    insertHASH(name,Gender,D_admission,D_birth,Illness,Address,Blood);
                    puts("Table after insert new Hash::");
                    printfHash();

                    break;
                case 5:
                    printf(" \n >Enter the name of the patient that you want to search for in the hash table .. \n");
                    char  name_S[30];
                    getchar();
                    gets(name_S);
                    searchAspecificRecord(name_S);
                    break;
                case 6:
                    printf(" \n >Enter the name of the patient you want to Delete it .. \n");
                    char  name_h[30];
                    getchar();
                    gets(name_h);
                    DeleteAspecificRecord(name_h);
                    printf(" >Successfully Deleted ..:) \n");
                    puts("Table after deletion ::");
                    printfHash();

                    break;
                case 7:
                    saveHashTable();
                    printf(" >Successfully saved to the file.. :) \n");

                    break;
                case 8:
                    printf("> Good Bye ! ");
                    exit(0);

                    break;
                default:
                    printf(" > Please select one of the options that appears in the menu :).\n");
                    break;
                }
            }
        default:
            printf(" > Please select one of the options that appears in the menu :).\n");
            break;
        }
    }
    return 0;
}
