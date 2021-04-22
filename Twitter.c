
  
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <shellapi.h>
#include <cwchar>
#include <math.h>

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

struct record
{
    int id;
    char username[20];
    char password[20];
    int tweets[100];
    int length;
    int inode[15];
};
typedef struct hours
{

    int hour;
    int minute;
    int second;

} Hour;
struct tweet
{
    int tweetid;
    char tweets[100];
    int likes[100];
    int length;
    int inode[15];
    int day;
    int month;
    int year;
    Hour hour;
};
struct array
{
    int arr[100];
    int length;
    int inode[15];
};
int userid;
long int cursor;
int arrayposition;
int bitvectorbytes = 30400;
char fname[] = { "C:\\Users\\user\\Desktop\\Twitter.txt" };

void g(int x, int y);//used for graphics
void create_file();//creates file twitter.h
void clear_console();//clears the console screen
void homepage();//Homepage after login
void header();//shows header "welcome to mini twitter"
void signpage();//shows two option signin and signout
void signup_form();//signup form structure
void signin_form();//sigin form structure
void encrypt(char password[], int key);//to encrypt the data
void decrypt(char password[], int key);//to decrypt the data
int signup();//used to signup
int signup_password(struct record ** rec);
int signin();//used to signin
int check_username(char *username);//checks weather username already exsists or not
int check_username_array(struct array * array, struct record * record, unsigned char * arr,char * username);
int check_username_inode(struct array * array, struct record * record, unsigned char * arr, char * username);
int check_username_1x_indirect(struct array * array, struct record * record, unsigned char * arr, char * username);
int check_username_2x_indirect(struct array * array, struct record * record, unsigned char * arr, char * username);
char * get_password();//used to read the password with * encryption
int  loginrecord_into_file(struct record *re);//stores record when signed up
void write_struct_record(struct record * re, int j);//writes struct record to file
int check_signin(struct record *re);//checks weather the password and username entered are valid or not
int make_a_tweet();//called to make a tweet
int store_your_tweet(struct record * rec, struct tweet * tweet, unsigned char *arr, int k);//to store that tweet
void homepage_structure();//used to show the menu with options to choose which operation to perform in twitter
void recent_tweets();//used to view 100 recent tweets
void display_recent_tweets(struct array * array1, struct array * array2);
void update_array_length(int num, struct record *rec);//used to increment the no.of tweets count(length) in struct record when tweet is made
void into_x3indirect(int fcursor, struct record *rec);//used to insert tweet address in inode 2x indirect addresing
void create_x3indirect_inode(int fcursor, struct record *rec, unsigned char* arr);//used to create the first inode 2x indirect addresing arrays for storing tweeet
void create_x3indirect(int fcursor, struct record *rec, unsigned char* arr);//used to create the  inode 2x indirect addresing array for storing tweeet
void into_x2indirect(int fcursor, struct record *rec);//used to insert tweet address in inode 1x indirect addresing for storing tweeet
void create_x2indirect(int fcursor, struct record *rec, unsigned char* arr);//used to create the  inode 1x indirect addresing array for storing tweet
void record_tweet(struct tweet **tweet, int max);//used to store the tweet in struct tweet in file
int memory_overflow(int fcursor, struct record *rec);//used to find empty spaces to link tweet to the user when inode  is filled
int memory_overflow_array(int fcursor, struct record *rec);
int memory_overflow_inode(int fcursor, struct record *rec);
int memory_overflow_1x_indirect(int fcursor, struct record *rec);
int memory_overflow_2x_indirect(int fcursor, struct record *rec);
int vacant_inode_area(unsigned char *arr);//used to find the empty memory blocks in the file
void tweet_menu();//used to show the options like (like,unlike,view tweets,delete tweets)
int make_choice();//used to choose what to do next
void choose_make_a_tweet();
void choose_view_own_tweets(char * ch);
void choose_like(char * ch);
void choose_unlike(char *ch);
void choose_view_likes(char * ch);
void choose_delete(char * ch);
void view_tweets_by_username();//used to  view tweets of a user by entering username
void delete_account();//delete account operation is performed
void delete_account_array(struct record *record, unsigned char * arr);
void delete_account_inode(struct record *record, unsigned char * arr);
void delete_account_1x_indirect(struct record *record, unsigned char * arr);
void delete_account_2x_indirect(struct record *record, unsigned char * arr);
void delete_like(int pointer);//deletes likes of that user
void view_tweets(int pointer);//view tweets of a user
void view_tweets_array(int *  k, unsigned char * arr, struct record *record);
void view_tweets_inode(int *  k, unsigned char * arr, struct record *record);
void view_tweets_1x_indirect(int *  k, unsigned char * arr, struct record *record);
void view_tweets_2x_indirect(int *  k, unsigned char * arr, struct record *record);
void like(int num);//to like a tweet
int check_already_liked(int pointer);//checks if its already liked by that user
int check_already_liked_1x_indirect(int pointer, struct tweet * tweet);
int check_already_liked_2x_indirect(int pointer, struct tweet * tweet);
int tweet_memory_overflow(int pointer, struct tweet *tweet);//used to find empty spaces to link like to the tweet when inode  is filled
int tweet_memory_overflow_array(int pointer, struct tweet *tweet);
int tweet_memory_overflow_inode(int pointer, struct tweet *tweet);
int tweet_memory_overflow_1x_indirect(int pointer, struct tweet *tweet);
int tweet_memory_overflow_2x_indirect(int pointer, struct tweet *tweet);
void like_into_array(struct tweet *tweet, int pointer);//stores the like into array in struct tweet
void create_x2indirect_like(int pointer, struct tweet *tweet,unsigned char * arr);//used to create the  inode 1x indirect addresing array for storing like
void into_x2indirect_like(int pointer, struct tweet *tweet);//used to insert userid in inode 1x indirect addresing for storing like
void create_x3indirect_like(int pointer, struct tweet *tweet, unsigned char * arr);//used to create the first inode 2x indirect addresing arrays for storing like
void create_x3indirect_inode_like(int pointer, struct tweet *tweet, unsigned char * arr);//used to create the first inode 2x indirect addresing arrays for storing like
void into_x3indirect_like(int pointer, struct tweet *tweet);//used to insert userid in inode 2x indirect addresing
void unlike(int tid);//used to unlike the tweet
int remove_like(int pointer);//to remove like
int remove_like_array(int pointer, struct tweet * tweet);
int remove_like_inode(int pointer, struct tweet * tweet);
int remove_like_1x_indirect(int pointer, struct tweet * tweet);
int remove_like_2x_indirect(int pointer, struct tweet * tweet);
void get_username(int uid);//to print the username of the given uid
int get_username_array(struct array * array, struct record * record, unsigned char * arr, int uid);
int get_username_inode(struct array * array, struct record * record, unsigned char * arr, int uid);
int get_username_1x_inode(struct array * array, struct record * record, unsigned char * arr, int uid);
int get_username_2x_inode(struct array * array, struct record * record, unsigned char * arr, int uid);
void display_usernames(int pointer);//to print username from that location in file
void display_username_1(int pointer,struct tweet * tweet);
void display_username_2(int pointer,struct tweet * tweet);
void view_likes(int num);//used to view the usernames of who liked that particular tweet
void delete_tweet_in_record(int num);//remove tweet address from struct record of that user
int delete_tweet_in_record_array(struct record * record, struct tweet * tweet, unsigned char * arr,int num);
int delete_tweet_in_record_inode(struct record * record, struct tweet * tweet, unsigned char * arr, int num);
int delete_tweet_in_record_1x_indirect(struct record * record, struct tweet * tweet, unsigned char * arr, int num);
int delete_tweet_in_record_2x_indirect(struct record * record, struct tweet * tweet, unsigned char * arr, int num);
void record_struct_record_location();//store record pointer in struct record array.Below are for handling this array
int array_memory_overflow(int pointer, struct array * array);
int array_memory_overflow_array(int pointer, struct array * array);
int array_memory_overflow_inode(int pointer, struct array *array);
int array_memory_overflow_1x_indirect(int pointer, struct array *array);
int array_memory_overflow_2x_indirect(int pointer, struct array *array);
void array_into_array(struct array *array, int pointer);
void create_x2indirect_array(int pointer, struct array *array, unsigned char * arr);
void into_x2indirect_array(int pointer, struct array *array);
void create_x3indirect_array(int pointer, struct array *array, unsigned char * arr);
void create_x3indirect_inode_array(int pointer, struct array *array, unsigned char * arr);
void into_x3indirect_array(int pointer, struct array *array);
int parse_usernames_array(char * username, char * password);//used to read all struct records in the array
int parse_usernames_array_array(struct array *array,struct record * record,unsigned char * arr, char * username, char * password);
int parse_usernames_array_inode(struct array *array, struct record * record, unsigned char * arr, char * username, char * password);
int parse_usernames_array_1x_indirect(struct array *array, struct record * record, unsigned char * arr, char * username, char * password);
int parse_usernames_array_2x_indirect(struct array *array, struct record * record, unsigned char * arr, char * username, char * password);
int get_username_location(char * username);//used to get the struct record location
int get_username_location_array(struct array * array, unsigned char * arr, char * username);
int get_username_location_inode(struct array * array, unsigned char * arr, char * username);
int get_username_location_1x_indirect(struct array * array, unsigned char * arr, char * username);
int get_username_location_2x_indirect(struct array * array, unsigned char * arr, char * username);
void delete_record_in_array();//remove struct record address from array
void delete_record_in_array_array();
void delete_record_in_array_inode();
void delete_record_in_array_1x_indirect();
void delete_record_in_array_2x_indirect();
void tweet_struct_record_location(int fcursor);//store tweet pointer in struct tweet array.Below are for handling this array
int tweet_array_memory_overflow(int pointer, struct array *array, int fcursor);
int tweet_array_memory_overflow_array(int pointer, struct array * array, unsigned char * arr, int fcursor);
int tweet_array_memory_overflow_inode(int pointer, struct array * array, unsigned char * arr, int fcursor);
int tweet_array_memory_overflow_1x_indirect(int pointer, struct array * array, unsigned char * arr, int fcursor);
int tweet_array_memory_overflow_2x_indirect(int pointer, struct array * array, unsigned char * arr, int fcursor);
void tweet_array_into_array(struct array *array, int pointer, int fcursor);
void create_x2indirect_tweet_array(int pointer, struct array *array, unsigned char * arr, int fcursor);
void into_x2indirect_tweet_array(int pointer, struct array *array, int fcursor);
void create_x3indirect_tweet_array(int pointer, struct array *array, unsigned char * arr, int fcursor);
void create_x3indirect_inode_tweet_array(int pointer, struct array *array, unsigned char * arr, int fcursor);
void into_x3indirect_tweet_array(int pointer, struct array *array, int fcursor);
int parse_tweets_array(int num);//used to read all struct tweets in the array
int parse_tweets_array_array(struct array *array,struct tweet * tweet,unsigned char * arr,int num);
int parse_tweets_array_inode(struct array *array, struct tweet * tweet, unsigned char * arr, int num);
int parse_tweets_array_1x_indirect(struct array *array, struct tweet * tweet, unsigned char * arr, int num);
int parse_tweets_array_2x_indirect(struct array *array, struct tweet * tweet, unsigned char * arr, int num);
void recent_tweets_record(int fcursor);//used to store recent tweets in array
void recent_tweets_userid_record();//used to store the struct record locations of users of those recent tweets
void delete_in_recent_records(int num);//used to delete the any deleted tweet from recent tweet records array
int find_max_userid();//used to find maximum userid in the file
int max_tweetid();//used to find maximum tweetid in the file
int bitvector_status(int num, unsigned char * array);//used to check waether num block is occupied or not
int bit_vector_vacancy(int num, unsigned char *array);//checks for vacancy in bit vector
void bitvector_clear(int num, unsigned char *array);//to clear the block
void update_bitvector_block_status(unsigned char *arr, int num);//updates the block statuses in bitvector

//Better UI experience with fontsize 16 in Maximised Console Window ;
int main()
{
    system("COLOR 71");
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 16;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    clear_console();
    signpage();
    system("pause");
    return 0;
}
void g(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
void create_file()
{
    system("fsutil file createnew C:\\Users\\user\\Desktop\\Twitter.txt 145950400");
    unsigned char *freespace_vector = (unsigned char *)malloc(bitvectorbytes);
    FILE *fp;
    struct array *arr= (struct array *)malloc(sizeof(struct array));
    int i;
    freespace_vector[0] = 30;
    for (i = 1; i <bitvectorbytes; i++)
    {
        freespace_vector[i] = 0;
    }
    fp = fopen(fname, "r+b");
    fwrite(freespace_vector, sizeof(freespace_vector), 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    arr->length = 0;
    fseek(fp, bitvectorbytes + 600, SEEK_SET);
    fwrite(arr, sizeof(struct array), 1, fp);
    fseek(fp, bitvectorbytes + 600 + 600, SEEK_SET);
    fwrite(arr, sizeof(struct array), 1, fp);
    fseek(fp, bitvectorbytes + 600 + 600 + 600, SEEK_SET);
    fwrite(arr, sizeof(struct array), 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    arr->length = 1;
    arr->arr[0] = 0;
    fseek(fp, bitvectorbytes, SEEK_SET);
    fwrite(arr, sizeof(struct array), 1, fp);
    fclose(fp);
}
void encrypt(char password[], int key)
{
    unsigned int i;
    for (i = 0; i<strlen(password); ++i)
    {
        password[i] = password[i] - key;
    }
}

void decrypt(char password[], int key)
{
    unsigned int i;
    for (i = 0; i<strlen(password); ++i)
    {
        password[i] = password[i] + key;
    }
}
void clear_console()
{
    system("cls");
}
void header()
{
    printf("_______________________________________________________________________________________________________________________________________________________________________\n");
    printf("\n                                                                         WELCOME TO MINI TWITTER                           \n");
    printf("_______________________________________________________________________________________________________________________________________________________________________\n");
}
void signpage()
{
    int num;
    header();
    printf("\n                                     To Sign up [Press 1]                            |                            To Sign in [Press 0] \n");
    printf("_______________________________________________________________________________________________________________________________________________________________________\n");
    int i;
    fflush(stdin);
    printf("\nEnter your option : ");
    scanf("%d", &num);
    if (num == 1)
        i = signup();
    else
        i = signin();
    if (i == 1)
        homepage();
    else
        main();
}
void signup_form()
{
    clear_console();
    header();
    int i = 60;
    g(i, 7);
    printf(" __________________________________________________\n");
    g(i, 8);
    printf("|                                                  |\n");
    g(i, 9);
    printf("|                   Sign Up Form                   |\n");
    g(i, 10);
    printf("|__________________________________________________|\n");
    g(i, 11);
    printf("|                                                  |\n");
    g(i, 12);
    printf("| Username :                                       |\n");
    g(i, 13);
    printf("|                                                  |\n");
    g(i, 14);
    printf("| Password :                                       |\n");
    g(i, 15);
    printf("|                                                  |\n");
    g(i, 16);
    printf("| Re-Type Password :                               |\n");
    g(i, 17);
    printf("|__________________________________________________|\n");
    g(i, 18);
    printf("|                                                  |\n");
    g(i, 19);
    printf("|                                                  |\n");
    g(i, 20);
    printf("|__________________________________________________|\n");
}
void signin_form()
{
    clear_console();
    header();
    int i = 60;
    g(i, 7);
    printf(" __________________________________________________\n");
    g(i, 8);
    printf("|                                                  |\n");
    g(i, 9);
    printf("|                   Sign In Form                   |\n");
    g(i, 10);
    printf("|__________________________________________________|\n");
    g(i, 11);
    printf("|                                                  |\n");
    g(i, 12);
    printf("| Username :                                       |\n");
    g(i, 13);
    printf("|                                                  |\n");
    g(i, 14);
    printf("| Password :                                       |\n");
    g(i, 15);
    printf("|__________________________________________________|\n");
    g(i, 16);
    printf("|                                                  |\n");
    g(i, 17);
    printf("|                                                  |\n");
    g(i, 18);
    printf("|__________________________________________________|\n");
}
int signup()
{
    FILE *fp;
    fp = fopen(fname, "r+b");
    if (fp == NULL)
    {
        create_file();
        fp = fopen(fname, "r+b");
    }
    fclose(fp);
    signup_form();
    int i = 1;
    struct record *rec = (struct record *)malloc(sizeof(struct record));
    char username[20], error[25];
    strcpy(error, "                    ");
    do
    {
        if (i == 0)
            strcpy(error, "Duplicte Username");
        g(62, 19);
        printf("%s", error);
        g(73, 12);
        printf("                     ");
        g(73, 12);
        scanf(" %[^\t\n]s", username);
        i = check_username(username);

    }
    while (i == 0);
    strcpy(rec->username, username);
    g(62, 19);
    strcpy(error, "                    ");
    return  signup_password(&rec);
}
int signup_password(struct record ** rec)
{
    int i = 1;
    char * password1 = (char *)malloc(sizeof(char) * 20);
    char * password2 = (char *)malloc(sizeof(char) * 20);
    char error[25];
    strcpy(error, "                    ");
    do
    {
        if (i == 0)
            strcpy(error, "Passwords unmatched    ");
        g(62, 19);
        printf("%s", error);
        i = 0;
        g(73, 14);
        printf("                   ");
        g(73, 14);
        password1 = get_password();
        g(80, 16);
        printf("                   ");
        g(80, 16);
        password2 = get_password();
    }
    while (strcmp(password1, password2) || !strcmp(password1, ""));
    strcpy(error, "                   ");
    g(62, 19);
    printf("%s", error);
    strcpy((*rec)->password, password1);
    if (loginrecord_into_file(*rec))
        return 1;
    else
        return 0;
}
int bitvector_status(int num, unsigned char * array)
{
    int num1 = num / 8;
    int num2 = num % 8;
    int j=1;
    j=(int)pow((int)2, (int)num2);
    if ((array[num1] & j)!=0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int check_username(char *username)
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    struct record * record = (struct record *)malloc(sizeof(struct record));
    int i;
    int k = 0;
    unsigned char *arr=(unsigned char *)malloc(bitvectorbytes);
    FILE *fp;
    fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    encrypt(username, 0xFACA);
    k=check_username_array(array, record, arr, username);
    if (k == 0)
    {
        decrypt(username, 0xFACA);
        return k;
    }
    k=check_username_inode(array, record, arr, username);
    if (k == 0)
    {
        decrypt(username, 0xFACA);
        return k;
    }
    k=check_username_1x_indirect(array, record, arr, username);
    if (k == 0)
    {
        decrypt(username, 0xFACA);
        return k;
    }
    k=check_username_2x_indirect(array, record, arr, username);
    decrypt(username, 0xFACA);
    return k;
}
int check_username_array(struct array * array,struct record * record, unsigned char * arr,char *username)
{
    int i;
    FILE *fp;
    int k =0;
    for (i = 0; i < 100 && i < array->length; i++)
    {

        if (array->arr[i] != 0 && bitvector_status((array->arr[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->arr[i], SEEK_SET);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if ((!strcmp(record->username, username)))
            {
                return k;
            }
        }
    }
    return 1;
}
int check_username_inode(struct array * array, struct record * record, unsigned char * arr, char *username)
{
    int i,k=0;
    FILE *fp;
    for (i = 0; i < 13 && i < array->length - 100; i++)
    {
        if (array->inode[i] != 0 && bitvector_status((array->inode[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->inode[i], SEEK_SET);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if ((!strcmp(record->username, username)))
            {
                return k;
            }
        }
    }
    return 1;
}
int check_username_1x_indirect(struct array * array, struct record * record, unsigned char * arr, char *username)
{
    int i, k = 0;
    FILE *fp;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i < array->length - 113; i++)
    {
        if (ar[i] != 0 && bitvector_status((ar[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, ar[i], SEEK_SET);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if ((!strcmp(record->username, username)))
            {
                return k;
            }
        }
    }
    return 1;
}
int check_username_2x_indirect(struct array * array, struct record * record, unsigned char * arr, char *username)
{
    FILE *fp;
    int i, k = 0;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int j;
    for (i = 0; i < 100 && i <= (array->length - 213) / 100; i++)
    {
        int br[100];
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j < array->length - 213 - i * 100; j++)
        {
            if (br[j] != 0 && bitvector_status((br[j] - bitvectorbytes) / 600, arr) == 1)
            {
                fp = fopen(fname, "r+b");
                fseek(fp, br[j], SEEK_SET);
                fread(record, sizeof(struct record), 1, fp);
                fclose(fp);
                if ((!strcmp(record->username, username)))
                {
                    return k;
                }
            }
        }
    }
    return 1;
}
char * get_password()
{
    char * password1 = (char *)malloc(sizeof(char) * 20);
    int h = 0;
    char c;
    while (h <= 100)
    {
        password1[h] = getch();
        c = password1[h];
        if (c == 13)
            break;
        else if (c == 8)
        {
            h--;
            if (h < 0)
                h++;
            else
                printf("\b \b");
        }
        else if (c > 31 && c < 127 && (c < 37 || c>40))
        {
            printf("*");
            h++;
        }
    }
    password1[h] = '\0';
    return password1;
}
int bit_vector_vacancy(int num, unsigned char *array)
{
    int i=0,j=1;
	if (num % 100 != 0)
	{
		if ((array[num] & j) == 0)
		{
			array[num] = array[num] | j;
			FILE *fp = fopen(fname, "r+b");
			fwrite(array, bitvectorbytes, 1, fp);
			fclose(fp);
			return (num * 8 + i);
		}
	}
    for (i = 1; i < 8; i++)
    {
        j = j * 2;
        if  ((array[num] & j) == 0)
        {
            array[num]=array[num] | j;
            FILE *fp = fopen(fname, "r+b");
            fwrite(array, bitvectorbytes, 1, fp);
            fclose(fp);
            return (num * 8 + i);
        }
		
    }
    return 0;
}
int vacant_inode_area(unsigned char *arr)
{
	int i, j, k;
	for (k = 0;k < 304;k++)
	{
		if (bitvector_status(k * 100*8, arr) == 0)
		{
			for (i = k * 100; i < k * 100 + 100; i++)
			{
				j = bit_vector_vacancy(i, arr);
				if (j != 0)
				{
					update_bitvector_block_status(arr, k * 100);
					return j;
				}
			}
		}
	}
	return i;
}
void update_bitvector_block_status(unsigned char *arr, int num)
{
	int i, j, k = 1,l;
	for (i = num; i < num + 100; i++)
	{
		if (i % 100 != 0)
		{
			j = bitvector_status(i*8, arr);
			if (j == 0)
			{
				k = 0;
				return;
			}
		}
		for (l = 1;l < 8;l++)
		{
			j = bitvector_status((i*8)+l, arr);
			if (j == 0)
			{
				k = 0;
				return;
			}
		}
	}
	if (k == 1)
	{
		arr[num] = arr[num]||1;
		FILE *fp = fopen(fname, "r+b");
		fwrite(arr, bitvectorbytes, 1, fp);
		fclose(fp);
	}
}

int  loginrecord_into_file(struct record *re)
{
    struct record *rec = (struct record *)malloc(sizeof(struct record));
    FILE *fp;
    unsigned char *arr = (unsigned char *)malloc(bitvectorbytes);
    int i = 0;
    int j = 1, k, max = 0;
    fp = fopen(fname, "r+b");
    if (fp == NULL)
    {
        create_file();
        fp = fopen(fname, "r+b");
    }
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
	j = vacant_inode_area(arr);
    if (j == bitvectorbytes)
    {
        g(62, 19);
        printf("No memory in file\n");
        return 0;
    }
    else
    {
        write_struct_record(re, j);
        return 1;
    }
}
void write_struct_record(struct record * re,int j)
{
    int max;
    struct record *rec = (struct record *)malloc(sizeof(struct record));
    FILE *fp;
    max = find_max_userid();
    fp = fopen(fname, "r+b");
    strcpy(rec->username, re->username);
    encrypt(rec->username, 0xFACA);
    strcat(rec->username, "\0");
    strcpy(rec->password, re->password);
    encrypt(rec->password, 0xFACA);
    strcat(rec->password, "\0");
    rec->length = 0;
    rec->id = ++max;
    fseek(fp, bitvectorbytes + j * 600, SEEK_SET);
    cursor = ftell(fp);
    fwrite(rec, sizeof(struct record), 1, fp);
    userid = rec->id;
    fclose(fp);
    record_struct_record_location();
}
int find_max_userid()
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    FILE *fp;
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    return array->arr[0];

}
void record_struct_record_location()
{
    int pointer = bitvectorbytes;
    struct array *array;
    array = (struct array *)malloc(sizeof(struct array));
    FILE *fp;
    unsigned char *arr=(unsigned char *)malloc(bitvectorbytes);
    fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    arrayposition = array->length;
    if (array->length > 9999)
    {
        int x = array_memory_overflow(pointer, array);
    }
    else if (array->length < 100)
    {
        array_into_array(array, pointer);
    }
    else if (array->length <113)
    {
        array->inode[array->length - 100] = cursor;
        array->arr[0]++;
        array->length++;
        FILE * fp = fopen(fname, "r+b");
        fseek(fp, bitvectorbytes, SEEK_SET);
        fwrite(array, sizeof(struct array), 1, fp);
        fclose(fp);
    }
    else if (array->length == 113)
    {
        create_x2indirect_array(pointer, array, arr);
    }
    else if (array->length <213)
    {
        into_x2indirect_array(pointer, array);
    }
    else if (array->length == 213)
    {
        create_x3indirect_array(pointer, array, arr);
    }
    else if ((array->length - 213) % 100 == 0)
    {
        create_x3indirect_inode_array(pointer, array, arr);
    }
    else
    {
        into_x3indirect_array(pointer, array);
    }

}
void create_x2indirect_array(int pointer, struct array *array, unsigned char* arr)
{
    int ar[100] = { 0 };
    ar[0] = cursor;
    int i;
    i = vacant_inode_area(arr);
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    array->inode[13] = pointer2;
    array->length++;
    array->arr[0]++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);

}
void into_x2indirect_array(int pointer, struct array *array)
{
    int ar[100];
    FILE *fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fread(&ar, sizeof(ar), 1, fp);
    fclose(fp);
    ar[(array->length - 113)] = cursor;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fwrite(&ar, sizeof(ar), 1, fp);
    fclose(fp);
    array->length++;
    array->arr[0]++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void create_x3indirect_array(int pointer, struct array *array,unsigned char* arr)
{
    int ar[100] = { 0 };
    ar[0] = cursor;
    int i;
    i = vacant_inode_area(arr);
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100; i++)
        ar[i] = 0;
    ar[0] = pointer2;
    i = vacant_inode_area(arr);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    array->inode[14] = pointer2;
    array->length++;
    array->arr[0]++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void create_x3indirect_inode_array(int pointer, struct array *array,unsigned char* arr)
{
    int i;
    i = vacant_inode_area(arr);
    int ar[100];
    ar[0] = cursor;
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    ar[(array->length - 213) / 100] = pointer2;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    array->length++;
    array->arr[0]++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void into_x3indirect_array(int pointer, struct array *array)
{
    int ar[100] = { 0 };
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int var = ar[(array->length - 213) / 100];
    int br[100] = { 0 };
    fp = fopen(fname, "r+b");
    fseek(fp, var, SEEK_SET);
    fread(br, sizeof(br), 1, fp);
    fclose(fp);
    br[(array->length - 213) % 100] = cursor;
    fp = fopen(fname, "r+b");
    fseek(fp, var, SEEK_SET);
    fwrite(br, sizeof(br), 1, fp);
    fclose(fp);
    array->length++;
    array->arr[0]++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct tweet), 1, fp);
    fclose(fp);
}
int array_memory_overflow(int pointer, struct array *array)
{
    if (array_memory_overflow_array(pointer, array))
        return 1;
    if (array_memory_overflow_inode(pointer, array))
        return 1;
    if (array_memory_overflow_1x_indirect(pointer,array))
        return 1;
    if (array_memory_overflow_2x_indirect(pointer,array))
        return 1;
    return 0;
}
int array_memory_overflow_array(int pointer, struct array *array)
{
    int i;
    FILE * fp;
    for (i = 0; i < 100; i++)
    {
        if (array->arr[i] == 0)
        {
            array->arr[i] = cursor;
            array->arr[0]++;
            fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(array, sizeof(struct array), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int array_memory_overflow_inode(int pointer, struct array *array)
{
    FILE * fp;
    int i;
    for (i = 0; i < 13; i++)
    {
        if (array->inode[i] == 0)
        {
            array->inode[i] = cursor;
            array->arr[0]++;
            fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(array, sizeof(struct array), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int array_memory_overflow_1x_indirect(int pointer, struct array *array)
{
    int ar[100];
    FILE *fp;
    int j;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (j = 0; j < 100; j++)
    {
        if (ar[j] == 0)
        {
            ar[j] = cursor;
            fp = fopen(fname, "r+b");
            fseek(fp, array->inode[13], SEEK_SET);
            fwrite(ar, sizeof(ar), 1, fp);
            fclose(fp);
            array->arr[0]++;
            fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(array, sizeof(struct array), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int array_memory_overflow_2x_indirect(int pointer, struct array *array)
{
    FILE *fp;
    int ar[100];
    int i, j;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int br[100], k;
    for (i = 0; i < 100; i++)
    {
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100; j++)
        {
            if (br[j] == 0)
            {
                br[j] = cursor;
                fp = fopen(fname, "r+b");
                fseek(fp, ar[i], SEEK_SET);
                fwrite(br, sizeof(br), 1, fp);
                fclose(fp);
                array->arr[0]++;
                fp = fopen(fname, "r+b");
                fseek(fp, pointer, SEEK_SET);
                fwrite(array, sizeof(struct array), 1, fp);
                fclose(fp);
                return 1;
            }
        }
    }
    return 0;
}
void array_into_array(struct array *array, int pointer)
{
    array->arr[array->length] = cursor;
    array->length++;
    array->arr[0]++;
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
int signin()
{
    FILE *fp;
    fp = fopen(fname, "r+b");
    if (fp == NULL)
    {
        create_file();
        signup();
    }
    else
    {
        fclose(fp);
        signin_form();
        int i = 0;
        int j = 1;
        struct record *rec = (struct record *)malloc(sizeof(struct record));
        char username[20], error[25];
        char * password = (char *)malloc(sizeof(char) * 20);
        strcpy(error, "                    ");
        do
        {

            g(62, 17);
            if (j == 0)
                strcpy(error, "Invalid password  ");
            do
            {
                if (i == 1)
                    strcpy(error, "Invalid Username");
                g(62, 17);
                printf("%s", error);
                g(73, 12);
                printf("                     ");
                g(73, 14);
                printf("                     ");
                g(73, 12);
                scanf(" %[^\t\n]s", username);
                i = check_username(username);

            }
            while (i == 1);
            strcpy(rec->username, username);
            g(62, 17);
            printf("                     ");
            g(73, 14);
            password = get_password();
            strcpy(rec->password, password);
            j = check_signin(rec);
        }
        while (j == 0);
    }
    return 1;
}
int check_signin(struct record *re)
{
    int j = 0;
    encrypt(re->username, 0xFACA);
    encrypt(re->password, 0xFACA);
    j = parse_usernames_array(re->username, re->password);
    return j;
}
int parse_usernames_array(char * username, char * password)
{
    struct array * array = (struct array *)malloc(sizeof(struct array));
    struct record * record = (struct record *)malloc(sizeof(struct record));
    int i;
    int k = 0;
    unsigned char * arr = (unsigned char *)malloc(bitvectorbytes);
    FILE *fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    k=parse_usernames_array_array(array, record, arr, username, password);
    if (k != 0)
        return k;
    k=parse_usernames_array_inode(array, record, arr, username, password);
    if (k != 0)
        return k;
    k=parse_usernames_array_1x_indirect(array, record, arr, username,password);
    if (k != 0)
        return k;
    k=parse_usernames_array_2x_indirect(array, record, arr, username, password);

    return k;
}
int parse_usernames_array_array(struct array * array,struct record * record, unsigned char * arr, char * username, char * password)
{
    int i,k=0;
    FILE *fp;
    for (i = 1; i < 100 && i < array->length; i++)
    {

        if (array->arr[i] != 0 && bitvector_status((array->arr[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->arr[i], SEEK_SET);
            k = ftell(fp);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if ((!strcmp(record->username, username)) && (!strcmp(record->password, password)))
            {
                userid = record->id;
                cursor = k;
                arrayposition = i;
                return k;
            }
        }
    }
    return 0;
}
int parse_usernames_array_inode(struct array * array, struct record * record, unsigned char * arr, char * username, char * password)
{
    int i,k=0;
    FILE *fp;
    for (i = 0; i < 13 && i < array->length - 100; i++)
    {
        if (array->inode[i] != 0 && bitvector_status((array->inode[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->inode[i], SEEK_SET);
            k = ftell(fp);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if ((!strcmp(record->username, username)) && (!strcmp(record->password, password)))
            {
                userid = record->id;
                cursor = k;
                arrayposition = 100 + i;
                return k;
            }
        }
    }
    return 0;
}
int parse_usernames_array_1x_indirect(struct array * array, struct record * record, unsigned char * arr, char * username, char * password)
{
    int ar[100];
    FILE *fp;
    int i, k = 0;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i < array->length - 113; i++)
    {
        if (ar[i] != 0 && bitvector_status((ar[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, ar[i], SEEK_SET);
            k = ftell(fp);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if ((!strcmp(record->username, username)) && (!strcmp(record->password, password)))
            {
                userid = record->id;
                cursor = k;
                arrayposition = 113 + i;
                return k;
            }
        }
    }
    return 0;
}
int parse_usernames_array_2x_indirect(struct array * array, struct record * record, unsigned char * arr, char * username, char * password)
{
    FILE *fp;
    int i, k = 0;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int j;
    for (i = 0; i < 100 && i <= (array->length - 213) / 100; i++)
    {
        int br[100];
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j < array->length - 213 - i * 100; j++)
        {
            if (br[j] != 0 && bitvector_status((br[j] - bitvectorbytes) / 600, arr) == 1)
            {
                fp = fopen(fname, "r+b");
                fseek(fp, br[j], SEEK_SET);
                k = ftell(fp);
                fread(record, sizeof(struct record), 1, fp);
                fclose(fp);
                if ((!strcmp(record->username, username)) && (!strcmp(record->password, password)))
                {
                    userid = record->id;
                    cursor = k;
                    arrayposition = 213 + i * 100 + j;
                    return k;
                }
            }
        }
    }
    return 0;
}
void homepage()
{
    clear_console();
    header();
    homepage_structure();
    make_choice();
}
int make_choice()
{
    struct array *arr = (struct array *)malloc(sizeof(struct array));
    char ch[20];
    fflush(stdout);
    printf("\nEnter your choice : ");
a:
    do
    {
        fflush(stdin);
        scanf(" %[^\t\n]s", ch);

    }
    while (ch[0] != '0'&&ch[0] != '1'&& ch[0] != '2'&& ch[0] != '3'&& ch[0] != '4'&& ch[0] != '5'&& ch[0] != '6' && (strncmp(ch, "like ", 5) && strlen(ch)<6) && (strncmp(ch, "unlike ", 7) && strlen(ch)<8) && (strncmp(ch, "view likes ", 11) && strlen(ch)<12) && (strncmp(ch, "delete ", 7) && strlen(ch)<8) && strcmp(ch, "exit"));
    if (ch[0] == '1')
    {
        choose_make_a_tweet();
    }
    else if (ch[0] == '0')
    {
        homepage();
        make_choice();
    }
    else if (ch[0] == '2')
    {
        recent_tweets();
        make_choice();
    }
    else if (ch[0] == '6')
    {
        cursor = -1;
        clear_console();
        signpage();
    }
    else if (ch[0] == '5')
    {
        delete_account();
        clear_console();
        signpage();

    }
    else if (ch[0] == '3')
    {
        view_tweets_by_username();
        make_choice();
    }
    else if (ch[0] == '4')
    {
        choose_view_own_tweets(ch);
    }
    else if (!strncmp("like ", ch, 5) && strlen(ch)>5)
    {
        choose_like(ch);
    }
    else if (!strncmp("unlike ", ch, 7) && strlen(ch)>7)
    {
        choose_unlike(ch);
    }
    else if (!strncmp("view likes ", ch, 11) && strlen(ch)>11)
    {
        choose_view_likes(ch);
    }
    else if (!strncmp("delete ", ch, 7) && strlen(ch)>7)
    {
        choose_delete(ch);
    }
    else if (!strcmp(ch, "exit"))
    {
        exit(0);
    }
    else
    {
        goto a;
    }
    return 0;
}
void choose_make_a_tweet()
{
    int i;
    i = make_a_tweet();
    if (i == 1)
        printf("\nTweeted succesfully\n");
    else
        printf("\nTweet failed\n");
    make_choice();
}
void choose_view_own_tweets(char * ch)
{
    clear_console();
    header();
    homepage_structure();
    tweet_menu();
    printf("\nYour Tweets :) \n");
    view_tweets(cursor);
    make_choice();
}
void choose_like(char *ch)
{
    int i = 5;
    int num = 0;
    while (ch[i] != '\0')
    {
        num = num * 10 + (ch[i] - 48);
        i++;
    }
    like(num);
    recent_tweets();
    make_choice();
}
void choose_unlike(char * ch)
{
    int i = 7;
    int num = 0;
    while (ch[i] != '\0')
    {
        num = num * 10 + (ch[i] - 48);
        i++;
    }
    unlike(num);
    recent_tweets();
    make_choice();
}
void choose_view_likes(char * ch)
{
    int i = 11;
    int num = 0;
    while (ch[i] != '\0')
    {
        num = num * 10 + (ch[i] - 48);
        i++;
    }
    view_likes(num);
    make_choice();
}
void choose_delete(char *ch)
{
    int i = 7;
    int num = 0;
    while (ch[i] != '\0')
    {
        num = num * 10 + (ch[i] - 48);
        i++;
    }
    delete_tweet_in_record(num);
    recent_tweets();
    make_choice();
}
void delete_tweet_in_record(int num)
{
    struct record * record = (struct record *)malloc(sizeof(struct record));
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    int i;
    unsigned char *arr = (unsigned char *)malloc(bitvectorbytes);
    FILE *fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, cursor, SEEK_SET);
    fread(record, sizeof(struct record), 1, fp);
    fclose(fp);
    i = delete_tweet_in_record_array(record, tweet, arr, num);
    if (i == 1)
        return;
    i = delete_tweet_in_record_inode(record,tweet,arr,num);
    if (i == 1)
        return;
    i = delete_tweet_in_record_1x_indirect(record, tweet, arr, num);
    if (i == 1)
        return;
    i = delete_tweet_in_record_2x_indirect(record, tweet, arr, num);
}
int delete_tweet_in_record_array(struct record * record,struct tweet * tweet,unsigned char *arr,int num)
{
    int i;
    FILE *fp;
    for (i = 0; i < 100 && i < record->length; i++)
    {

        if (record->tweets[i] != 0 && bitvector_status((record->tweets[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, record->tweets[i], SEEK_SET);
            fread(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            if (tweet->tweetid == num)
            {
                delete_in_recent_records(record->tweets[i]);
                bitvector_clear((record->tweets[i] - bitvectorbytes) / 600, arr);
                delete_like(record->tweets[i]);
                record->tweets[i] = 0;
                fp = fopen(fname, "r+b");
                fseek(fp, cursor, SEEK_SET);
                fwrite(record, sizeof(struct record), 1, fp);
                fclose(fp);
                return 1;
            }

        }
    }
    return 0;
}
int delete_tweet_in_record_inode(struct record * record, struct tweet * tweet, unsigned char *arr, int num)
{
    int i;
    FILE *fp;
    for (i = 0; i < 13 && i < record->length - 100; i++)
    {
        if (record->inode[i] != 0 && bitvector_status((record->inode[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, record->inode[i], SEEK_SET);
            fread(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            if (tweet->tweetid == num)
            {
                delete_in_recent_records(record->inode[i]);
                bitvector_clear((record->inode[i] - bitvectorbytes) / 600, arr);
                delete_like(record->inode[i]);
                record->inode[i] = 0;
                fp = fopen(fname, "r+b");
                fseek(fp, cursor, SEEK_SET);
                fwrite(record, sizeof(struct record), 1, fp);
                fclose(fp);
                return 1;
            }
        }
    }
    return 0;
}
int delete_tweet_in_record_1x_indirect(struct record * record, struct tweet * tweet, unsigned char *arr, int num)
{
    int ar[100];
    FILE *fp;
    int i;
    fp = fopen(fname, "r+b");
    fseek(fp, record->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i < record->length - 113; i++)
    {
        if (ar[i] != 0 && bitvector_status((ar[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, ar[i], SEEK_SET);
            fread(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            if (tweet->tweetid == num)
            {
                delete_in_recent_records(ar[i]);
                bitvector_clear((ar[i] - bitvectorbytes) / 600, arr);
                delete_like(ar[i]);
                ar[i] = 0;
                fp = fopen(fname, "r+b");
                fseek(fp, cursor, SEEK_SET);
                fwrite(record, sizeof(struct record), 1, fp);
                fclose(fp);
                fp = fopen(fname, "r+b");
                fseek(fp, record->inode[13], SEEK_SET);
                fwrite(ar, sizeof(ar), 1, fp);
                fclose(fp);
                return 1;
            }
        }
    }
    return 0;
}
int delete_tweet_in_record_2x_indirect(struct record * record, struct tweet * tweet, unsigned char *arr, int num)
{
    FILE *fp;
    int i;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, record->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int j;
    for (i = 0; i < 100 && i <= (record->length - 213) / 100; i++)
    {
        int br[100];
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j < record->length - 213 - i * 100; j++)
        {
            if (br[j] != 0 && bitvector_status((br[j] - bitvectorbytes) / 600, arr) == 1)
            {
                fp = fopen(fname, "r+b");
                fseek(fp, br[j], SEEK_SET);
                fread(tweet, sizeof(struct tweet), 1, fp);
                fclose(fp);
                if (tweet->tweetid == num)
                {
                    delete_in_recent_records(br[j]);
                    bitvector_clear((br[j] - bitvectorbytes) / 600, arr);
                    delete_like(br[j]);
                    br[j] = 0;
                    fp = fopen(fname, "r+b");
                    fseek(fp, ar[i], SEEK_SET);
                    fwrite(br, sizeof(br), 1, fp);
                    fclose(fp);
                    return 1;
                }
            }
        }
    }
    return 0;
}
void bitvector_clear(int num, unsigned char *array)
{
    int num1 = num / 8;
    int num2 = num % 8;
    int k=0;
    k = (int)pow((int)2, (int)num2);
    k = 255 - k;
    array[num1] = array[num1] & k;
    array[(num1/100)*100] = array[(num1 / 100) * 100] & 254;
    FILE *fp = fopen(fname, "r+b");
    fwrite(array, bitvectorbytes, 1, fp);
    fclose(fp);
}
void delete_in_recent_records(int num)
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    FILE *fp;
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + 600 + 600, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    int i,j=array->length;
    if (array->length > 99)
    {
        j = 100;
    }
    for (i = 0; i < j; i++)
    {
        if (array->arr[i] == num)
        {
            array->arr[i] = 0;
            break;
        }
    }
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + 600 + 600, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);


}
void view_likes(int num)
{
    clear_console();
    header();
    homepage_structure();
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    FILE *fp;
    int i;
    i = parse_tweets_array(num);
    fp = fopen(fname, "r+b");
    fseek(fp, i, SEEK_SET);
    fread(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
    if (tweet->tweetid == num)
    {
        printf("\nTweet ID : %d\t\tTweet : %s\t\tDate : %d-%d-%d\n", tweet->tweetid, tweet->tweets, tweet->day, tweet->month, tweet->year);
        printf("\nLiked by : \n\n");
        if (tweet->length == 0)
        {
            printf("No Likes\n");
        }
        else
        {
            display_usernames(i);
        }
    }
}

int parse_tweets_array(int num)
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    struct tweet * tweet = (struct tweet *)malloc(sizeof(struct tweet));
    int i;
    int k = 0;
    unsigned char *arr = (unsigned char *)malloc(bitvectorbytes);
    FILE *fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + 600, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    k = parse_tweets_array_array(array, tweet,arr, num);
    if (k != 0)
        return k;
    k = parse_tweets_array_inode(array, tweet,arr, num);
    if (k != 0)
        return k;
    k = parse_tweets_array_1x_indirect(array, tweet,arr,num);
    if (k != 0)
        return k;
    k = parse_tweets_array_2x_indirect(array, tweet, arr, num);

    return k;
}
int parse_tweets_array_array(struct array *array,struct tweet * tweet, unsigned char *arr, int num)
{
    FILE *fp;
    int i,k=0;
    for (i = 0; i < 100 && i < array->length; i++)
    {

        if (array->arr[i] != 0 && bitvector_status((array->arr[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->arr[i], SEEK_SET);
            k = ftell(fp);
            fread(tweet, sizeof(struct  tweet), 1, fp);
            fclose(fp);
            if (tweet->tweetid == num)
            {
                return k;
            }
        }
    }
	return 0;
}
int parse_tweets_array_inode(struct array *array, struct tweet * tweet, unsigned char *arr, int num)
{
    int i,k=0;
    FILE *fp;
    for (i = 0; i < 13 && i < array->length - 100; i++)
    {
        if (array->inode[i] != 0 && bitvector_status((array->inode[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->inode[i], SEEK_SET);
            k = ftell(fp);
            fread(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            if (tweet->tweetid == num)
            {
                return k;
            }
        }
    }
	return 0;
}
int parse_tweets_array_1x_indirect(struct array *array,struct tweet *tweet, unsigned char *arr,int num)
{
    int ar[100];
    FILE *fp;
    int i, k = 0;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i < array->length - 113; i++)
    {
        if (ar[i] != 0 && bitvector_status((ar[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, ar[i], SEEK_SET);
            k = ftell(fp);
            fread(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            if (tweet->tweetid == num)
            {
                return k;
            }
        }
    }
	return 0;
}
int parse_tweets_array_2x_indirect(struct array *array, struct tweet *tweet, unsigned char *arr, int num)
{
    FILE *fp;
    int ar[100];
    int i, k = 0;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int j;
    for (i = 0; i < 100 && i <= (array->length - 213) / 100; i++)
    {
        int br[100];
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j < array->length - 213 - i * 100; j++)
        {
            if (br[j] != 0 && bitvector_status((br[j] - bitvectorbytes) / 600, arr) == 1)
            {
                fp = fopen(fname, "r+b");
                fseek(fp, br[j], SEEK_SET);
                k = ftell(fp);
                fread(tweet, sizeof(struct tweet), 1, fp);
                fclose(fp);
                if (tweet->tweetid == num)
                {
                    return k;
                }
            }
        }
    }
	return 0;
}
void display_usernames(int pointer)
{
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    FILE *fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fread(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
    int i;
    for (i = 0; i < 100 && i < tweet->length; i++)
    {
        if (tweet->likes[i] > 0)
        {
            get_username(tweet->likes[i]);
        }

    }
    for (i = 0; i < 13 && i < tweet->length - 100; i++)
    {
        if (tweet->inode[i] > 0)
        {
            get_username(tweet->inode[i]);
        }

    }
    if(tweet->length>113)
        display_username_1(pointer, tweet);
    if(tweet->length>213)
        display_username_2(pointer, tweet);

}
void display_username_1(int pointer, struct tweet * tweet)
{
    FILE *fp;
    int ar[100];
    int i;
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i < tweet->length - 113; i++)
    {
        if (ar[i] > 0)
        {
            get_username(ar[i]);
        }
    }

}
void display_username_2(int pointer, struct tweet * tweet)
{
    FILE *fp;
    int ar[100];
    int i;
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int j;
    for (i = 0; i < 100 && i <= (tweet->length - 113) / 100; i++)
    {
        int br[100];
        FILE *fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j < tweet->length - 113 - 100 * i; j++)
        {
            if (br[i] > 0)
            {
                get_username(br[i]);
            }
        }
    }
}
void get_username(int uid)
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    struct record * record = (struct record *)malloc(sizeof(struct record));
    int i;
    int k = 0;
    unsigned char * arr = (unsigned char *)malloc(bitvectorbytes);
    FILE *fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    if (get_username_array(array, record, arr, uid))
        return;
    if (get_username_inode(array, record, arr, uid))
        return;
    if (get_username_1x_inode(array, record, arr, uid))
        return;
    if (get_username_2x_inode(array, record, arr, uid))
        return;

    printf("Deleted User\n\n");
    return;

}
int get_username_array(struct array * array,struct record * record,unsigned char * arr,int uid)
{
    int i;
    FILE * fp;
    for (i = 0; i < 100 && i < array->length; i++)
    {

        if (array->arr[i] != 0 && bitvector_status((array->arr[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->arr[i], SEEK_SET);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if (record->id == uid)
            {
                decrypt(record->username, 0xFACA);
                printf("%s\n\n", record->username);
                return 1;
            }
        }
    }
    return 0;
}
int get_username_inode(struct array * array, struct record * record, unsigned char * arr, int uid)
{
    int i;
    FILE *fp;
    for (i = 0; i < 13 && i < array->length - 100; i++)
    {
        if (array->inode[i] != 0 && bitvector_status((array->inode[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->inode[i], SEEK_SET);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if (record->id == uid)
            {
                decrypt(record->username, 0xFACA);
                printf("%s\n\n", record->username);
                return 1;
            }
        }
    }
    return 0;
}
int get_username_1x_inode(struct array * array, struct record * record, unsigned char * arr, int uid)
{
    int ar[100];
    int i;
    FILE * fp;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i < array->length - 113; i++)
    {
        if (ar[i] != 0 && bitvector_status((ar[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, ar[i], SEEK_SET);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if (record->id == uid)
            {
                decrypt(record->username, 0xFACA);
                printf("%s\n\n", record->username);
                return 1;
            }
        }
    }
    return 0;
}
int get_username_2x_inode(struct array * array, struct record * record, unsigned char * arr, int uid)
{
    FILE *fp;
    int ar[100];
    int i,j;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i <= (array->length - 213) / 100; i++)
    {
        int br[100];
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j < array->length - 213 - i * 100; j++)
        {
            if (br[j] != 0 && bitvector_status((br[j] - bitvectorbytes) / 600, arr) == 1)
            {
                fp = fopen(fname, "r+b");
                fseek(fp, br[j], SEEK_SET);
                fread(record, sizeof(struct record), 1, fp);
                fclose(fp);
                if (record->id == uid)
                {
                    decrypt(record->username, 0xFACA);
                    printf("%s\n\n", record->username);
                    return 1;
                }
            }
        }

    }
    return 0;
}
void like(int num)
{
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    unsigned char *arr=(unsigned char*)malloc(bitvectorbytes);
    int pointer;
    FILE *fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    pointer = parse_tweets_array(num);
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fread(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
    if (check_already_liked(pointer) && pointer != 0)
    {
        if (tweet->length > 9999)
        {
            int x = tweet_memory_overflow(pointer, tweet);
        }
        else if (tweet->length < 100)
        {
            like_into_array(tweet, pointer);
        }
        else if (tweet->length <113)
        {
            tweet->inode[tweet->length - 100] = userid;
            tweet->length++;
            FILE * fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
        }
        else if (tweet->length == 113)
        {
            create_x2indirect_like(pointer, tweet, arr);
        }
        else if (tweet->length <213)
        {
            into_x2indirect_like(pointer, tweet);
        }
        else if (tweet->length == 213)
        {
            create_x3indirect_like(pointer, tweet, arr);
        }
        else if ((tweet->length - 213) % 100 == 0)
        {
            create_x3indirect_inode_like(pointer, tweet, arr);
        }
        else
        {
            into_x3indirect_like(pointer, tweet);
        }
    }

}
void create_x2indirect_like(int pointer, struct tweet *tweet, unsigned char* arr)
{
    int ar[100] = { 0 };
    ar[0] = userid;
    int i;
    i = vacant_inode_area(arr);
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    tweet->inode[13] = pointer2;
    tweet->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
}
void into_x2indirect_like(int pointer, struct tweet *tweet)
{
    int x[100];
    FILE *fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[13], SEEK_SET);
    fread(x, sizeof(x), 1, fp);
    fclose(fp);
    x[(tweet->length - 113)] = userid;
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[13], SEEK_SET);
    fwrite(x, sizeof(x), 1, fp);
    fclose(fp);
    tweet->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
}
void create_x3indirect_like(int pointer, struct tweet *tweet, unsigned char* arr)
{
    int ar[100] = { 0 };
    ar[0] = userid;
    int i;
    i = vacant_inode_area(arr);
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100; i++)
        ar[i] = 0;
    ar[0] = pointer2;
    i = vacant_inode_area(arr);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    tweet->inode[14] = pointer2;
    tweet->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
}
void create_x3indirect_inode_like(int pointer, struct tweet *tweet, unsigned char* arr)
{
    int i;
    i = vacant_inode_area(arr);
    int ar[100];
    ar[0] = userid;
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    ar[(tweet->length - 213) / 100] = pointer2;
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[14], SEEK_SET);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    tweet->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
}
void into_x3indirect_like(int pointer, struct tweet *tweet)
{
    int ar[100] = { 0 };
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int var = ar[(tweet->length - 213) / 100];
    int br[100] = { 0 };
    fp = fopen(fname, "r+b");
    fseek(fp, var, SEEK_SET);
    fread(br, sizeof(br), 1, fp);
    fclose(fp);
    br[(tweet->length - 213) % 100] = userid;
    fp = fopen(fname, "r+b");
    fseek(fp, var, SEEK_SET);
    fwrite(br, sizeof(br), 1, fp);
    fclose(fp);
    tweet->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
}
int tweet_memory_overflow(int pointer, struct tweet *tweet)
{
    int i, j;
    FILE * fp;
    if (tweet_memory_overflow_array(pointer, tweet))
        return 1;
    if (tweet_memory_overflow_inode(pointer, tweet))
        return 1;
    if (tweet_memory_overflow_1x_indirect(pointer, tweet))
        return 1;
    if (tweet_memory_overflow_2x_indirect(pointer, tweet))
        return 1;
    return 0;
}
int tweet_memory_overflow_array(int pointer, struct tweet *tweet)
{
    int i;
    FILE *fp;
    for (i = 0; i < 100; i++)
    {
        if (tweet->likes[i] == 0)
        {
            tweet->likes[i] = userid;
            fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int tweet_memory_overflow_inode(int pointer, struct tweet *tweet)
{
    int i;
    FILE *fp;
    for (i = 0; i < 13; i++)
    {
        if (tweet->inode[i] == 0)
        {
            tweet->inode[i] = userid;
            fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int tweet_memory_overflow_1x_indirect(int pointer, struct tweet *tweet)
{
    int ar[100];
    int j;
    FILE * fp;
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (j = 0; j < 100; j++)
    {
        if (ar[j] == 0)
        {
            ar[j] = userid;
            fp = fopen(fname, "r+b");
            fseek(fp, tweet->inode[13], SEEK_SET);
            fwrite(ar, sizeof(ar), 1, fp);
            fclose(fp);
            return 1;
        }
    }
}
int tweet_memory_overflow_2x_indirect(int pointer, struct tweet *tweet)
{
    int ar[100];
    int i,j;
    FILE * fp;
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int br[100], k;
    for (i = 0; i < 100; i++)
    {
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100; j++)
        {
            if (br[j] == 0)
            {
                br[j] = userid;
                fp = fopen(fname, "r+b");
                fseek(fp, ar[i], SEEK_SET);
                fwrite(br, sizeof(br), 1, fp);
                fclose(fp);
                return 1;
            }
        }
    }
}
void like_into_array(struct tweet *tweet, int pointer)
{
    tweet->likes[tweet->length] = userid;
    tweet->length++;
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
}
int check_already_liked(int pointer)
{
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    FILE *fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fread(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
    int i;
    for (i = 0; i < 100 && i < tweet->length; i++)
    {
        if (tweet->likes[i] == userid)
            return 0;
    }
    for (i = 0; i < 13 && i < tweet->length - 100; i++)
    {
        if (tweet->inode[i] == userid)
            return 0;
    }
    if (check_already_liked_1x_indirect(pointer, tweet) == 0)
        return 0;
    if (check_already_liked_2x_indirect(pointer, tweet) == 0)
        return 0;
    return 1;
}
int check_already_liked_1x_indirect(int pointer,struct tweet * tweet)
{
    FILE * fp;
    int i;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i < tweet->length - 113; i++)
    {
        if (ar[i] == userid)
            return 0;
    }
    return 1;
}
int check_already_liked_2x_indirect(int pointer, struct tweet * tweet)
{
    FILE * fp;
    int i;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int j;
    for (i = 0; i < 100 && i <= (tweet->length - 113) / 100; i++)
    {
        int br[100];
        FILE *fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j < tweet->length - 113 - 100 * i; j++)
        {
            if (br[i] == userid)
                return 0;
        }
    }
    return 1;
}
void unlike(int tid)
{
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    int pointer;
    pointer = parse_tweets_array(tid);
    if (pointer != 0)
        remove_like(pointer);
    return;

}

int remove_like(int pointer)
{
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    FILE *fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fread(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
    if (remove_like_array(pointer, tweet) == 0)
        return 0;
    if (remove_like_inode(pointer, tweet) == 0)
        return 0;
    if (remove_like_1x_indirect(pointer, tweet) == 0)
        return 0;
    if (remove_like_2x_indirect(pointer, tweet) == 0)
        return 0;
    return 1;
}
int remove_like_array(int pointer, struct tweet * tweet)
{
    int i;
    FILE * fp;
    for (i = 0; i < 100 && i < tweet->length; i++)
    {
        if (tweet->likes[i] == userid)
        {
            tweet->likes[i] = 0;
            tweet->length--;
            fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            return 0;
        }
    }
    return 1;
}
int remove_like_inode(int pointer, struct tweet * tweet)
{
    int i;
    FILE * fp;
    for (i = 0; i < 13 && i < tweet->length - 100; i++)
    {
        if (tweet->inode[i] == userid)
        {
            tweet->inode[i] = 0;
            tweet->length--;
            fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            return 0;
        }
    }
    return 1;
}
int remove_like_1x_indirect(int pointer, struct tweet * tweet)
{
    int i;
    FILE * fp;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i < tweet->length - 113; i++)
    {
        if (ar[i] == userid)
        {
            ar[i] = 0;
            tweet->length--;
            fp = fopen(fname, "r+b");
            fseek(fp, tweet->inode[13], SEEK_SET);
            fwrite(ar, sizeof(ar), 1, fp);
            fclose(fp);
            fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            return 0;
        }
    }
    return 1;
}
int remove_like_2x_indirect(int pointer, struct tweet * tweet)
{
    int i,j;
    FILE * fp;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i <= (tweet->length - 113) / 100; i++)
    {
        int br[100];
        FILE *fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j < tweet->length - 113 - 100 * i; j++)
        {
            if (br[i] == userid)
            {
                br[i] = 0;
                tweet->length--;
                fp = fopen(fname, "r+b");
                fseek(fp, ar[i], SEEK_SET);
                fwrite(br, sizeof(br), 1, fp);
                fclose(fp);
                fp = fopen(fname, "r+b");
                fseek(fp, pointer, SEEK_SET);
                fwrite(tweet, sizeof(struct tweet), 1, fp);
                fclose(fp);
                return 0;
            }
        }
    }
    return 1;
}
void delete_account()
{
    int num = cursor;
    num = (num - bitvectorbytes) / 600;
    unsigned char *arr=(unsigned char *)malloc(bitvectorbytes);
    FILE *fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    struct record * record = (struct record *)malloc(sizeof(struct record));
    fp = fopen(fname, "r+b");
    fseek(fp, cursor, SEEK_SET);
    fread(record, sizeof(struct record), 1, fp);
    fflush(stdout);
    fclose(fp);
    bitvector_clear(num, arr);
    delete_account_array(record,  arr);
    delete_account_inode(record, arr);
    delete_account_1x_indirect(record, arr);
    delete_account_2x_indirect(record, arr);
    delete_record_in_array();

}
void delete_account_array(struct record *record,unsigned char * arr)
{
    int i;
    for (i = 0; i < record->length && i<100; i++)
    {
        if (0 <= record->tweets[i] && record->tweets[i]<145950400)
            if (bitvector_status((record->tweets[i] - bitvectorbytes) / 600, arr) == 1)
            {
                delete_in_recent_records(record->tweets[i]);
                delete_like(record->tweets[i]);
                bitvector_clear((record->tweets[i] - bitvectorbytes) / 600, arr);
            }
    }
}
void delete_account_inode(struct record *record, unsigned char * arr)
{
    int i;
    for (i = 0; i < 13 && i<record->length - 100; i++)
    {
        if (0 <= record->inode[i] && record->inode[i]<145950400)
            if (bitvector_status((record->inode[i] - bitvectorbytes) / 600, arr) == 1)
            {
                delete_in_recent_records(record->inode[i]);
                delete_like(record->inode[i]);
                bitvector_clear((record->inode[i] - bitvectorbytes) / 600, arr);
            }
    }
}
void delete_account_1x_indirect(struct record *record, unsigned char * arr)
{
    int i;
    int ar[100];
    FILE * fp;
    fp = fopen(fname, "r+b");
    fseek(fp, record->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i<record->length - 113; i++)
    {
        if (0 <= ar[i] && ar[i]<145950400)
            if (bitvector_status((ar[i] - bitvectorbytes) / 600, arr) == 1)
            {
                delete_in_recent_records(ar[i]);
                delete_like(ar[i]);
                bitvector_clear((ar[i] - bitvectorbytes) / 600, arr);

            }
    }
    if (record->length >= 113)
        bitvector_clear((record->inode[13] - bitvectorbytes) / 600, arr);
}
void delete_account_2x_indirect(struct record *record, unsigned char * arr)
{
    int i,j;
    int ar[100];
    FILE * fp;
    fp = fopen(fname, "r+b");
    fseek(fp, record->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i <= (record->length - 213) / 100; i++)
    {
        int br[100];
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j<record->length - 213 - 100 * i; j++)
        {
            if (0 <= br[j] && br[j]<145950400)
                if (bitvector_status((br[j] - bitvectorbytes) / 600, arr) == 1)
                {
                    delete_like(br[j]);
                    delete_in_recent_records(br[j]);
                    bitvector_clear((br[j] - bitvectorbytes) / 600, arr);
                }
        }
        bitvector_clear((ar[i] - bitvectorbytes) / 600, arr);
    }
    if (record->length >= 213)
        bitvector_clear((record->inode[14] - bitvectorbytes) / 600, arr);
}
void delete_record_in_array()
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    FILE *fp;
    if (arrayposition<100)
    {
        delete_record_in_array_array();
    }

    else if (arrayposition<113)
    {
        delete_record_in_array_inode();
    }
    else if (arrayposition<213)
    {
        delete_record_in_array_1x_indirect();
    }
    else if (arrayposition>213)
    {
        delete_record_in_array_2x_indirect();
    }
}
void delete_record_in_array_array()
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    FILE *fp;
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    array->arr[arrayposition] = 0;
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void delete_record_in_array_inode()
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    FILE *fp;
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    array->inode[arrayposition - 100] = 0;
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void delete_record_in_array_1x_indirect()
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    FILE *fp;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    ar[arrayposition - 113] = 0;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
}
void delete_record_in_array_2x_indirect()
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    FILE *fp;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int br[100];
    fp = fopen(fname, "r+b");
    fseek(fp, ar[(arrayposition - 213) / 100], SEEK_SET);
    fread(br, sizeof(br), 1, fp);
    fclose(fp);
    br[(arrayposition - 213) % 100] = 0;
    fp = fopen(fname, "r+b");
    fseek(fp, ar[(arrayposition - 213) / 100], SEEK_SET);
    fwrite(br, sizeof(br), 1, fp);
    fclose(fp);
}
void delete_like(int pointer)
{
    int num = pointer;
    num = (num - bitvectorbytes) / 600;
    unsigned char *arr=(unsigned char *) malloc (bitvectorbytes);
    FILE *fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    struct tweet * tweet = (struct tweet *)malloc(sizeof(struct tweet));
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fread(tweet, sizeof(struct tweet), 1, fp);
    fflush(stdout);
    fclose(fp);
    bitvector_clear(num,arr);
    int i;
    int ar[100];
    if (tweet->length > 113)
    {
        bitvector_clear((tweet->inode[13] - bitvectorbytes) / 600, arr);
    }
    fp = fopen(fname, "r+b");
    fseek(fp, tweet->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fflush(stdout);
    fclose(fp);
    for (i = 0; i < 100 && i <= (tweet->length - 213) / 100; i++)
    {
        if (bitvector_status((ar[i] - bitvectorbytes) / 600,arr)== 1)
        {
            bitvector_clear((ar[i] - bitvectorbytes) / 600, arr);
        }

    }


}
void view_tweets(int pointer)
{
    struct record * record = (struct record *)malloc(sizeof(struct record));
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    int i;
    int k = 1;
    unsigned char * arr=(unsigned char *)malloc(bitvectorbytes);
    FILE *fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fread(record, sizeof(struct record), 1, fp);
    fclose(fp);
    view_tweets_array(&k,arr, record);
    view_tweets_inode(&k,arr, record);
    view_tweets_1x_indirect(&k,arr, record);
    view_tweets_2x_indirect(&k,arr, record);
    if (k == 1)
        printf("\nNo Tweets\n");

}
void view_tweets_array(int *  k,unsigned char * arr,struct record *record)
{
    int i;
    FILE * fp;
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    for (i = 0; i < 100 && i < record->length; i++)
    {

        if (record->tweets[i] != 0 && bitvector_status((record->tweets[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, record->tweets[i], SEEK_SET);
            fread(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            g(0, 11 + 2 * (*k));
            printf("Tweet ID : ");
            printf("%d\t", tweet->tweetid);
            printf("Tweet : ");
            printf("%s\t\t", tweet->tweets);
            g(95, 11 + 2 * (*k));
            printf("Likes : ");
            printf("%d\t\t", tweet->length);
            printf("Date & Time : ");
            printf("%d - %d - %d   %d : %d\n\n", tweet->day, tweet->month, tweet->year, tweet->hour.hour, tweet->hour.minute);
            (*k)++;
            fflush(stdout);
        }
    }
}
void view_tweets_inode(int * k, unsigned char * arr, struct record *record)
{
    int i;
    FILE * fp;
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));

    for (i = 0; i < 13 && i < record->length - 100; i++)
    {
        if (record->inode[i] != 0 && bitvector_status((record->inode[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, record->inode[i], SEEK_SET);
            fread(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            g(0, 11 + 2 * (*k));
            printf("Tweet ID : ");
            printf("%d\t", tweet->tweetid);
            printf("Tweet : ");
            printf("%s\t\t", tweet->tweets);
            g(95, 11 + 2 * (*k));
            printf("Likes : ");
            printf("%d\t\t", tweet->length);
            printf("Date & Time : ");
            printf("%d - %d - %d   %d : %d\n\n", tweet->day, tweet->month, tweet->year, tweet->hour.hour, tweet->hour.minute);
            (*k)++;
            fflush(stdout);
        }
    }
}
void view_tweets_1x_indirect(int  *k, unsigned char * arr, struct record *record)
{
    int i;
    FILE * fp;
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, record->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i < record->length - 113; i++)
    {
        if (ar[i] != 0 && bitvector_status((ar[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, ar[i], SEEK_SET);
            fread(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            g(0, 11 + 2 * (*k));
            printf("Tweet ID : ");
            printf("%d\t", tweet->tweetid);
            printf("Tweet : ");
            printf("%s\t\t", tweet->tweets);
            g(95, 11 + 2 * (*k));
            printf("Likes : ");
            printf("%d\t\t", tweet->length);
            printf("Date & Time : ");
            printf("%d - %d - %d   %d : %d\n\n", tweet->day, tweet->month, tweet->year, tweet->hour.hour, tweet->hour.minute);
            (*k)++;
            fflush(stdout);
        }
    }
}
void view_tweets_2x_indirect(int * k, unsigned char * arr, struct record *record)
{
    int i;
    FILE * fp;
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, record->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int j;
    for (i = 0; i < 100 && i <= (record->length - 213) / 100; i++)
    {
        int br[100];
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j < record->length - 213 - i * 100; j++)
        {
            if (br[j] != 0 && bitvector_status((br[j] - bitvectorbytes) / 600, arr) == 1)
            {
                fp = fopen(fname, "r+b");
                fseek(fp, br[j], SEEK_SET);
                fread(tweet, sizeof(struct tweet), 1, fp);
                fclose(fp);
                g(0, 11 + 2 * (*k));
                printf("Tweet ID : ");
                printf("%d\t", tweet->tweetid);
                printf("Tweet : ");
                printf("%s\t\t", tweet->tweets);
                g(95, 11 + 2 * (*k));
                printf("Likes : ");
                printf("%d\t\t", tweet->length);
                printf("Date & Time : ");
                printf("%d - %d - %d   %d : %d\n\n", tweet->day, tweet->month, tweet->year, tweet->hour.hour, tweet->hour.minute);
                (*k)++;
                fflush(stdout);
            }
        }
    }
}
void view_tweets_by_username()
{
    clear_console();
    header();
    homepage_structure();
    tweet_menu();
    printf("\nEnter a Username to see their tweets : ");
    char str[100];
    int pointer;
    scanf(" %[^\t\n]s", str);
    int i;
    encrypt(str, 0xFACA);
    i = get_username_location(str);
    if (i == 0)
        printf("\nInvalid Username\n");
    else
    {
        view_tweets(i);
    }
}

int get_username_location(char * username)
{
    struct array *array = (struct array *)malloc(sizeof(struct array));
    int i;
    int k = 0;
    unsigned char * arr = (unsigned char *)malloc(bitvectorbytes);
    FILE *fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    int j;
    j = get_username_location_array(array, arr, username);
    if (j)
        return j;
    j = get_username_location_inode(array, arr, username);
    if (j)
        return j;
    j = get_username_location_1x_indirect(array, arr, username);
    if (j)
        return j;
    j = get_username_location_2x_indirect(array, arr, username);
    if (j)
        return j;



    return 0;
}
int get_username_location_array(struct array * array, unsigned char * arr, char * username)
{
    int i, k = 0;
    FILE * fp;
    struct record * record = (struct record *)malloc(sizeof(struct record));
    for (i = 1; i < 100 && i < array->length; i++)
    {
        if (array->arr[i] != 0 && bitvector_status((array->arr[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->arr[i], SEEK_SET);
            k = ftell(fp);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if ((!strcmp(record->username, username)))
            {
                return k;
            }
        }
    }
    return 0;
}
int get_username_location_inode(struct array * array, unsigned char * arr,char * username)
{
    int i, k = 0;
    FILE * fp;
    struct record * record = (struct record *)malloc(sizeof(struct record));
    for (i = 0; i < 13 && i < array->length - 100; i++)
    {
        if (array->inode[i] != 0 && bitvector_status((array->inode[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->inode[i], SEEK_SET);
            k = ftell(fp);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if ((!strcmp(record->username, username)))
            {
                return k;
            }
        }
    }
    return 0;
}
int get_username_location_1x_indirect(struct array * array, unsigned char * arr, char * username)
{
    int i, k = 0;
    FILE * fp;
    struct record * record = (struct record *)malloc(sizeof(struct record));
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100 && i < array->length - 113; i++)
    {
        if (ar[i] != 0 && bitvector_status((ar[i] - bitvectorbytes) / 600, arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, ar[i], SEEK_SET);
            k = ftell(fp);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            if ((!strcmp(record->username, username)))
            {
                return k;
            }
        }
    }
    return 0;
}
int get_username_location_2x_indirect(struct array * array, unsigned char * arr, char * username)
{
    int i, k = 0;
    FILE * fp;
    struct record * record = (struct record *)malloc(sizeof(struct record));
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int j;
    for (i = 0; i < 100 && i <= (array->length - 213) / 100; i++)
    {
        int br[100];
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100 && j < array->length - 213 - i * 100; j++)
        {
            if (br[j] != 0 && bitvector_status((br[j] - bitvectorbytes) / 600, arr) == 1)
            {
                fp = fopen(fname, "r+b");
                fseek(fp, br[j], SEEK_SET);
                k = ftell(fp);
                fread(record, sizeof(struct record), 1, fp);
                fclose(fp);
                if ((!strcmp(record->username, username)))
                {
                    return k;
                }
            }
        }
    }
    return 0;
}
void recent_tweets()
{
    clear_console();
    header();
    homepage_structure();
    tweet_menu();
    int i = 0,k=0;
    struct array *array1 = (struct array *)malloc(sizeof(struct array));
    struct array *array2 = (struct array *)malloc(sizeof(struct array));
    FILE *fp;
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + 600 + 600, SEEK_SET);
    fread(array1, sizeof(struct array), 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + 600 + 600 +600, SEEK_SET);
    fread(array2, sizeof(struct array), 1, fp);
    fclose(fp);
    display_recent_tweets(array1, array2);

}
void display_recent_tweets(struct array * array1, struct array * array2)
{
    int i,k=0;
    FILE *fp;
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    struct record *record = (struct record *)malloc(sizeof(struct record));
    printf("\nRecent Tweets :) \n");
    if (array1->length > 99)
    {
        array1->length = 100;
    }
    for (i = 0; i < array1->length; i++)
    {
        if (array1->arr[i] != 0)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array2->arr[i], SEEK_SET);
            fread(record, sizeof(struct record), 1, fp);
            fclose(fp);
            decrypt(record->username, 0xFACA);
            fp = fopen(fname, "r+b");
            fseek(fp, array1->arr[i], SEEK_SET);
            fread(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            g(0, 13 + 2 * k);
            printf("Tweet ID : ");
            printf("%d\t", tweet->tweetid);
            printf("Tweet : ");
            printf("%s\t\t", tweet->tweets);
            g(95, 13 + 2 * k);
            printf("By : ");
            printf("%s\t", record->username);
            g(120, 13 + 2 * k);
            printf("Likes : ");
            printf("%d\t", tweet->length);
            g(138, 13 + 2 * k);
            printf("Date & Time : ");
            printf("%d - %d - %d  \n\n", tweet->day, tweet->month, tweet->year);
            fflush(stdout);
            k++;
        }
    }
    if (k == 0)
        printf("\nNo tweets today\n");

}
int make_a_tweet()
{
    clear_console();
    header();
    homepage_structure();
    int max = 0;
    printf("\nEnter your tweet (100 characters) : ");
    long int inodecursor;
    struct record *rec = (struct record *)malloc(sizeof(struct record));
    FILE *fp;
    fp = fopen(fname, "r+b");
    fseek(fp, cursor, SEEK_SET);
    fread(rec, sizeof(struct record), 1, fp);
    fflush(stdout);
    fclose(fp);
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    int k;
    unsigned char *arr=(unsigned char *)malloc(bitvectorbytes);
    fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    max = max_tweetid();
    record_tweet(&tweet, max);
    long int fcursor;
    k = vacant_inode_area(arr);
    if (k != bitvectorbytes)
    {
        return store_your_tweet(rec, tweet, arr,  k);
    }
    return 0;
}
int store_your_tweet(struct record * rec,struct tweet * tweet,unsigned char *arr,int k )
{
    int fcursor;
    FILE * fp;
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + k * 600, SEEK_SET);
    fcursor = ftell(fp);
    fwrite(tweet, sizeof(struct tweet), 1, fp);
    fclose(fp);
    if (rec->length > 9999)
    {
        int x = memory_overflow(fcursor, rec);
        if (x != 0)
        {
            tweet_struct_record_location(fcursor);
            recent_tweets_record(fcursor);
            recent_tweets_userid_record();
        }
        return x;

    }
    else if (rec->length < 100)
    {
        update_array_length(fcursor, rec);
    }
    else if (rec->length <113)
    {
        rec->inode[rec->length - 100] = fcursor;
        rec->length++;
        FILE * fp = fopen(fname, "r+b");
        fseek(fp, cursor, SEEK_SET);
        fwrite(rec, sizeof(struct record), 1, fp);
        fclose(fp);
    }
    else if (rec->length == 113)
    {
        create_x2indirect(fcursor, rec, arr);
    }
    else if (rec->length <213)
    {
        into_x2indirect(fcursor, rec);
    }
    else if (rec->length == 213)
    {
        create_x3indirect(fcursor, rec, arr);
    }
    else if ((rec->length - 213) % 100 == 0)
    {
        create_x3indirect_inode(fcursor, rec, arr);

    }
    else
    {
        into_x3indirect(fcursor, rec);
    }
    tweet_struct_record_location(fcursor);
    recent_tweets_record(fcursor);
    recent_tweets_userid_record();
    return 1;
}
int max_tweetid()
{
    unsigned char *arr=(unsigned char *)malloc(bitvectorbytes);
    int i;
    FILE *fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    struct array *array = (struct array *)malloc(sizeof(struct array));
    struct tweet *tweet = (struct tweet *)malloc(sizeof(struct tweet));
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + 600 + 600, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    int max = 0;
    if (array->length > 99)
    {
        array->length = 100;
    }
    for (i = 0; i < array->length; i++)
    {
        if (bitvector_status((array->arr[i] - bitvectorbytes) / 600,arr) == 1)
        {
            fp = fopen(fname, "r+b");
            fseek(fp, array->arr[i], SEEK_SET);
            fread(tweet, sizeof(struct tweet), 1, fp);
            fclose(fp);
            if (tweet->tweetid > max)
            {
                max = tweet->tweetid;
            }
        }

    }
    return max;
}
void recent_tweets_userid_record()
{
    FILE *fp;
    struct array *array;
    array = (struct array *)malloc(sizeof(struct array));
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + 600 + 600 + 600, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    array->arr[array->length % 100] = cursor;
    array->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + 600 + 600 + 600, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void recent_tweets_record(int fcursor)
{
    FILE *fp;
    struct array *array;
    array = (struct array *)malloc(sizeof(struct array));
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + 600 + 600, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    array->arr[array->length % 100] = fcursor;
    array->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + 600 + 600, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void tweet_struct_record_location(int fcursor)
{
    int pointer = bitvectorbytes+600;
    struct array *array;
    array = (struct array *)malloc(sizeof(struct array));
    FILE *fp;
    unsigned char * arr=(unsigned char *)malloc(bitvectorbytes);
    fp = fopen(fname, "r+b");
    fread(arr, bitvectorbytes, 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fread(array, sizeof(struct array), 1, fp);
    fclose(fp);
    if (array->length > 9999)
    {
        int x = tweet_array_memory_overflow(pointer, array, fcursor);
    }
    else if (array->length < 100)
    {
        tweet_array_into_array(array, pointer, fcursor);
    }
    else if (array->length <113)
    {
        array->inode[array->length - 100] = fcursor;
        array->length++;
        FILE * fp = fopen(fname, "r+b");
        fseek(fp, 31000, SEEK_SET);
        fwrite(array, sizeof(struct array), 1, fp);
        fclose(fp);
    }
    else if (array->length == 113)
    {
        create_x2indirect_tweet_array(pointer, array, arr, fcursor);
    }
    else if (array->length <213)
    {
        into_x2indirect_tweet_array(pointer, array, fcursor);
    }
    else if (array->length == 213)
    {
        create_x3indirect_tweet_array(pointer, array, arr, fcursor);
    }
    else if ((array->length - 213) % 100 == 0)
    {
        create_x3indirect_inode_tweet_array(pointer, array, arr, fcursor);
    }
    else
    {
        into_x3indirect_tweet_array(pointer, array, fcursor);
    }

}
void create_x2indirect_tweet_array(int pointer, struct array *array, unsigned char* arr, int fcursor)
{
    int ar[100] = { 0 };
    ar[0] = fcursor;
    int i;
    i = vacant_inode_area(arr);
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    array->inode[13] = pointer2;
    array->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void into_x2indirect_tweet_array(int pointer, struct array *array, int fcursor)
{
    int ar[100];
    FILE *fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fread(&ar, sizeof(ar), 1, fp);
    fclose(fp);
    ar[(array->length - 113)] = fcursor;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fwrite(&ar, sizeof(ar), 1, fp);
    fclose(fp);
    array->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void create_x3indirect_tweet_array(int pointer, struct array *array, unsigned char* arr, int fcursor)
{
    int ar[100] = { 0 };
    ar[0] = fcursor;
    int i;
    i = vacant_inode_area(arr);
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i < 100; i++)
        ar[i] = 0;
    ar[0] = pointer2;
    i = vacant_inode_area(arr);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    array->inode[14] = pointer2;
    array->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void create_x3indirect_inode_tweet_array(int pointer, struct array *array, unsigned char* arr, int fcursor)
{
    int i;
    i = vacant_inode_area(arr);
    int ar[100];
    ar[0] = fcursor;
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer2 = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    ar[(array->length - 213) / 100] = pointer2;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    array->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
void into_x3indirect_tweet_array(int pointer, struct array *array, int fcursor)
{
    int ar[100] = { 0 };
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int var = ar[(array->length - 213) / 100];
    int br[100] = { 0 };
    fp = fopen(fname, "r+b");
    fseek(fp, var, SEEK_SET);
    fread(br, sizeof(br), 1, fp);
    fclose(fp);
    br[(array->length - 213) % 100] = fcursor;
    fp = fopen(fname, "r+b");
    fseek(fp, var, SEEK_SET);
    fwrite(br, sizeof(br), 1, fp);
    fclose(fp);
    array->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct tweet), 1, fp);
    fclose(fp);
}
int tweet_array_memory_overflow(int pointer, struct array *array, int fcursor)
{
    int i, j;
    FILE * fp;
    unsigned char *arr = (unsigned char *)malloc(bitvectorbytes);
    fp = fopen(fname, "r+b");
    fread(arr,bitvectorbytes, 1, fp);
    fclose(fp);
    if (tweet_array_memory_overflow_array(pointer, array, arr, fcursor))
        return 1;
    if (tweet_array_memory_overflow_inode(pointer, array, arr,fcursor))
        return 1;
    if (tweet_array_memory_overflow_1x_indirect(pointer,array,arr,fcursor))
        return 1;
    if (tweet_array_memory_overflow_2x_indirect(pointer, array, arr, fcursor))
        return 1;

    return 0;
}
int tweet_array_memory_overflow_array(int pointer, struct array *array,unsigned char * arr, int fcursor)
{
    FILE * fp;
    int i;
    for (i = 0; i < 100; i++)
    {
        if (array->arr[i] == 0 || bitvector_status((array->arr[i] - bitvectorbytes) / 600, arr) == 0)
        {
            array->arr[i] = fcursor;
            fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(array, sizeof(struct array), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int tweet_array_memory_overflow_inode(int pointer, struct array *array, unsigned char * arr, int fcursor)
{
    int i;
    FILE * fp;
    for (i = 0; i < 13; i++)
    {
        if (array->inode[i] == 0 || bitvector_status((array->inode[i] - bitvectorbytes) / 600, arr) == 0)
        {
            array->inode[i] = fcursor;
            fp = fopen(fname, "r+b");
            fseek(fp, pointer, SEEK_SET);
            fwrite(array, sizeof(struct array), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int tweet_array_memory_overflow_1x_indirect(int pointer, struct array *array, unsigned char * arr, int fcursor)
{
    int ar[100];
    FILE * fp;
    int j;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (j = 0; j < 100; j++)
    {
        if (ar[j] == 0 || bitvector_status((ar[j] - bitvectorbytes) / 600, arr) == 0)
        {
            ar[j] = fcursor;
            fp = fopen(fname, "r+b");
            fseek(fp, array->inode[13], SEEK_SET);
            fwrite(ar, sizeof(ar), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int tweet_array_memory_overflow_2x_indirect(int pointer, struct array *array, unsigned char * arr, int fcursor)
{
    int ar[100];
    FILE * fp;
    int i,j;
    fp = fopen(fname, "r+b");
    fseek(fp, array->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int br[100], k;
    for (i = 0; i < 100; i++)
    {
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100; j++)
        {
            if (br[j] == 0 || bitvector_status((br[j] - bitvectorbytes) / 600, arr) == 0)
            {
                br[j] = fcursor;
                fp = fopen(fname, "r+b");
                fseek(fp, ar[i], SEEK_SET);
                fwrite(br, sizeof(br), 1, fp);
                fclose(fp);
                return 1;
            }
        }
    }
    return 0;
}
void tweet_array_into_array(struct array *array, int pointer, int fcursor)
{
	array->arr[array->length] = fcursor;
    array->length++;
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, pointer, SEEK_SET);
    fwrite(array, sizeof(struct array), 1, fp);
    fclose(fp);
}
int memory_overflow(int fcursor, struct record *rec)
{
    if (memory_overflow_array(fcursor,rec))
        return 1;
    if (memory_overflow_inode(fcursor, rec))
        return 1;
    if (memory_overflow_1x_indirect(fcursor, rec))
        return 1;
    if (memory_overflow_2x_indirect(fcursor, rec))
        return 1;

    return 0;
}
int memory_overflow_array(int fcursor, struct record *rec)
{
    int i;
    FILE * fp;
    for (i = 0; i < 100; i++)
    {
        if (rec->tweets[i] == 0)
        {
            rec->tweets[i] = fcursor;
            fp = fopen(fname, "r+b");
            fseek(fp, cursor, SEEK_SET);
            fwrite(rec, sizeof(struct record), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int memory_overflow_inode(int fcursor, struct record *rec)
{
    FILE * fp;
    int i;
    for (i = 0; i < 13; i++)
    {
        if (rec->inode[i] == 0)
        {
            rec->inode[i] = fcursor;
            fp = fopen(fname, "r+b");
            fseek(fp, cursor, SEEK_SET);
            fwrite(rec, sizeof(struct record), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int memory_overflow_1x_indirect(int fcursor, struct record *rec)
{
    int ar[100];
    FILE * fp;
    int j;
    fp = fopen(fname, "r+b");
    fseek(fp, rec->inode[13], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (j = 0; j < 100; j++)
    {
        if (ar[j] == 0)
        {
            ar[j] = fcursor;
            fp = fopen(fname, "r+b");
            fseek(fp, rec->inode[13], SEEK_SET);
            fwrite(ar, sizeof(ar), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    return 0;
}
int memory_overflow_2x_indirect(int fcursor, struct record *rec)
{
    FILE *fp;
    int i, j;
    int ar[100];
    fp = fopen(fname, "r+b");
    fseek(fp, rec->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int br[100], k;
    for (i = 0; i < 100; i++)
    {
        fp = fopen(fname, "r+b");
        fseek(fp, ar[i], SEEK_SET);
        fread(br, sizeof(br), 1, fp);
        fclose(fp);
        for (j = 0; j < 100; j++)
        {
            if (br[j] == 0)
            {
                br[j] = fcursor;
                fp = fopen(fname, "r+b");
                fseek(fp, ar[i], SEEK_SET);
                fwrite(br, sizeof(br), 1, fp);
                fclose(fp);
                return 1;
            }
        }
    }
    return 0;
}
void record_tweet(struct tweet **tweet, int max)
{
    char str[100];
    scanf(" %[^\t\n]s", str);
    char buff[100];
    time_t now = time(0);
    struct tm now_t = *localtime(&now);
    strftime(buff, 100, "%d-%m-%Y %H:%M:%S", &now_t);
    (*tweet)->tweetid = max + 1;
    (*tweet)->length = 0;
    (*tweet)->year = now_t.tm_year + 1900; // years since 1900
    (*tweet)->month = now_t.tm_mon + 1;  // months since January [0-11]
    (*tweet)->day = now_t.tm_mday;  // day of month [1-31]

    (*tweet)->hour.hour = now_t.tm_hour;
    (*tweet)->hour.minute = now_t.tm_min;
    (*tweet)->hour.second = now_t.tm_sec;
    strcpy((*tweet)->tweets, str);
    strcat((*tweet)->tweets, "\0");
}
void update_array_length(int num, struct record *rec)
{
    rec->length++;
    rec->tweets[rec->length - 1] = num;
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, cursor, SEEK_SET);
    fwrite(rec, sizeof(struct record), 1, fp);
    fclose(fp);
}

void create_x2indirect(int fcursor, struct record *rec, unsigned char* arr)
{
    int ar[100] = { 0 };
    ar[0] = fcursor;
    int i;
    i = vacant_inode_area(arr);
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    rec->inode[13] = pointer;
    rec->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, cursor, SEEK_SET);
    fwrite(rec, sizeof(struct record), 1, fp);
    fclose(fp);
}
void into_x2indirect(int fcursor, struct record *rec)
{
    int x[100];
    FILE *fp = fopen(fname, "r+b");
    fseek(fp, rec->inode[13], SEEK_SET);
    fread(x, sizeof(x), 1, fp);
    fclose(fp);
    x[(rec->length - 113)] = fcursor;
    fp = fopen(fname, "r+b");
    fseek(fp, rec->inode[13], SEEK_SET);
    fwrite(x, sizeof(x), 1, fp);
    fclose(fp);
    rec->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, cursor, SEEK_SET);
    fwrite(rec, sizeof(struct record), 1, fp);
    fclose(fp);
}
void create_x3indirect(int fcursor, struct record *rec,unsigned  char* arr)
{
    int ar[100] = { 0 };
    ar[0] = fcursor;
    int i;
    i = vacant_inode_area(arr);
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    for (i = 0; i<100; i++)
        ar[i] = 0;
    ar[0] = pointer;
    i = vacant_inode_area(arr);
    fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    pointer = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    rec->inode[14] = pointer;
    rec->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, cursor, SEEK_SET);
    fwrite(rec, sizeof(struct record), 1, fp);
    fclose(fp);
}

void create_x3indirect_inode(int fcursor, struct record *rec,unsigned char* arr)
{
    int i;
    i = vacant_inode_area(arr);
    int ar[100];
    ar[0] = fcursor;
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, bitvectorbytes + i * 600, SEEK_SET);
    int pointer = ftell(fp);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    fp = fopen(fname, "r+b");
    fseek(fp, rec->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    ar[(rec->length - 213) / 100] = pointer;
    fp = fopen(fname, "r+b");
    fseek(fp, rec->inode[14], SEEK_SET);
    fwrite(ar, sizeof(ar), 1, fp);
    fclose(fp);
    rec->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, cursor, SEEK_SET);
    fwrite(rec, sizeof(struct record), 1, fp);
    fclose(fp);
}
void into_x3indirect(int fcursor, struct record *rec)
{
    int ar[100] = { 0 };
    FILE * fp = fopen(fname, "r+b");
    fseek(fp, rec->inode[14], SEEK_SET);
    fread(ar, sizeof(ar), 1, fp);
    fclose(fp);
    int var = ar[(rec->length - 213) / 100];
    int br[100] = { 0 };
    fp = fopen(fname, "r+b");
    fseek(fp, var, SEEK_SET);
    fread(br, sizeof(br), 1, fp);
    fclose(fp);
    br[(rec->length - 213) % 100] = fcursor;
    fp = fopen(fname, "r+b");
    fseek(fp, var, SEEK_SET);
    fwrite(br, sizeof(br), 1, fp);
    fclose(fp);
    rec->length++;
    fp = fopen(fname, "r+b");
    fseek(fp, cursor, SEEK_SET);
    fwrite(rec, sizeof(struct record), 1, fp);
    fclose(fp);

}
void homepage_structure()
{
    printf("\n     1. Make a Tweet     |     2.View Recent Tweets      |      3.View Tweets by Username      |      4.View My Tweets     |    5. Delete Account    |    6. Logout   \n");
    printf("_______________________________________________________________________________________________________________________________________________________________________\n");

}
void tweet_menu()
{
    printf("\n   like [like <Tweet ID>]    |    unlike [unlike <Tweet ID>]    |    view who liked the tweet [view likes <Tweet ID>]    |    Delete your Tweet [delete <Tweet ID>]   \n");
    printf("_______________________________________________________________________________________________________________________________________________________________________\n");

}



