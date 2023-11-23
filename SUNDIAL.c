#include <stdio.h>
#include <stdlib.h>  //for exit(0), system("cls")
#include <unistd.h>
#include <conio.h> //for kbhit, getch()
#include <time.h> //for clock(), time(), clock_t, time_t
#include <windows.h>
#include <setjmp.h> //for jumping from function to function
#include <string.h>
#include<unistd.h>
#include <pthread.h>
//#include <ncurses.h>
#define LENGTH 7
#define WIDTH 6
#define COLON_WIDTH 5

//Only Structure used
typedef struct inf
{
    char som[200];
    int as ;
} info ;

//All Global Variables
static jmp_buf buf;
static jmp_buf ag;
static jmp_buf come;//For Time Converter
int red=0, rever=0;//For Time Converter
int milli=0, min=0, second=0, flag=0;  //global variables
clock_t s=0, n=0;
char phrase[1000], charCommand[1000]; //global variable for voice

//All Functions
void setNumber (int n, int asciiN[LENGTH][WIDTH * 2]);
void displayTime (int hour, int minute, int second);
void showDigital_time();

void speak(char *phraseIn);

void setAlarm(void);
void snooze_stopAlarm(int h,int m, char *str);
void ring_alarm(int h,int m, char *str);
void delayAC(int ms);
void selectionAC(int h,int m);
void startReset(void);

void startStopWatch(void);
void running_clock(void);
void delaySW(int ms);
int printDataSW(int minute,int second,int milli);
int selection();

void startTimer(void);
void delay(int ms);
void printData(int hour,int mini,int sec);
void countdown(int hour,int mini,int sec);

void startConverter(void);
void replaced(char*str);
int isSpace(char*str);
int isSpaceOnly(char*str);
void printstruc(info *arrays , int n);
void printstruchalf(info *arrays , int n);
void delayTC(int ms);
void splittime(char *str , int s , char*result);
char *remove_white_spaces(char *str);
int levenshtein(char *s1, char *s2);
int found (char *wanted);
void foundPrint (char *wanted);
void foundPrintDiff (char *wanted);
int foundSubstr(char *wanted);
void foundSubstrPrint(char *wanted);
void foundSubstrPrintPRO(char *wanted);
void matchWordByWord(char *wanted);
void matchWordByWordPRO(char *wanted);
void splitString(char *str1);


//void *displayDigitalTime(void *args) {
//    while (1) {
//        time_t timer;
//        struct tm *t_st;
//        time(&timer);
//        t_st = localtime(&timer);
//
//        clear(); // Clear the screen
//
//        // Use mvprintw to print the digital time at a specific location (adjust as needed)
//        mvprintw(0, 0, "%02d:%02d:%02d", t_st->tm_hour, t_st->tm_min, t_st->tm_sec);
//
//        refresh(); // Refresh the screen
//
//        sleep(1); // Sleep for one second
//    }
//    return NULL;
//}


/*Driver Function*/

int main()
{
    //Give a nice background starting view

    speak("Welcome to sundial. Select from the menu to continue.");
    system("COLOR 01");
    start:
    setjmp(buf);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_RED);
    printf("\t\t\t\t\tSUNDIAL");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

//    initscr(); // Initialize ncurses
//    noecho();
//    cbreak();
//    curs_set(FALSE);
//
//    pthread_t digitalTimeThread;
//    pthread_create(&digitalTimeThread, NULL, displayDigitalTime, NULL);

    while(1){
            startmenu:

//                clear(); // Clear the screen
//                // Print your menu or options using mvprintw
//                mvprintw(1, 1, "1. Set Alarm");
//                mvprintw(2, 1, "2. Start Timer");
//                mvprintw(3, 1, "3. Start Stopwatch");
//                mvprintw(4, 1, "4. Start Converter");
//                mvprintw(5, 1, "5. Exit");
//                refresh(); // Refresh the screen

                printf("\n\n\n\nSelect from the menubar to continue:\n");
                printf("\n\t\t\t\t\t1. Set alarm\n\n\t\t\t\t\t2. Start Timer\n\n\t\t\t\t\t3. Start Stopwatch\n\n\t\t\t\t\t4. Convert Time\n\n\t\t\t\t\t5. Exit\n");



          switch(getch())
          {

                case '1' :
                {
                    system("cls");
                    fflush(stdin);
                    setAlarm();

                }
                case '2' :
                {
                    system("cls");
                    startTimer();
                }
               case '3' :
                {
                    system("cls");
                    startStopWatch();
                }
                case '4' :

                {
                    system("cls");
                    startConverter();
                }
                case '5' :
//                    pthread_cancel(digitalTimeThread); // Stop the time display thread
//                    pthread_join(digitalTimeThread, NULL);
                    return 0;
                default :
                {
                    //printf("Please select from the menu\n");
                    system("cls");
                    goto startmenu;
                }
          }

    }

    goto start;
    return 0;
}



void displayTime (int hour, int minute, int second)
{
  int h[LENGTH][WIDTH * 2], m[LENGTH][WIDTH * 2], s[LENGTH][WIDTH * 2];
  memset (h, 0, sizeof (h));
  memset (m, 0, sizeof (m));
  memset (s, 0, sizeof (s));
  int i = 0, j = 0;
  char colon[][COLON_WIDTH] = {
    {"     "},
    {"  |  "},
    {"  |  "},
    {"     "},
    {"  |  "},
    {"  |  "},
    {"     "}
  };
  int timeWidth =
    WIDTH * 2 + COLON_WIDTH + WIDTH * 2 + COLON_WIDTH + WIDTH * 2;
  char clockDisplay[LENGTH][timeWidth];
  memset (clockDisplay, 0, sizeof (clockDisplay));
  setNumber (hour, h);
  setNumber (minute, m);
  setNumber (second, s);

//Unite
  for (i = 0; i < LENGTH; i++)
    {
      for (j = 0; j < WIDTH * 2; j++)
	{
	  clockDisplay[i][j] = h[i][j];
	}
    }
//
  for (i = 0; i < LENGTH; i++)
    {
      for (j = 0; j < COLON_WIDTH; j++)
	{
	  clockDisplay[i][j + WIDTH * 2] = colon[i][j];
	}
    }
//
  for (i = 0; i < LENGTH; i++)
    {
      for (j = 0; j < WIDTH * 2; j++)
	{
	  clockDisplay[i][j + WIDTH * 2 + COLON_WIDTH] = m[i][j];
	}
    }
//
  for (i = 0; i < LENGTH; i++)
    {
      for (j = 0; j < COLON_WIDTH; j++)
	{
	  clockDisplay[i][j + WIDTH * 2 + COLON_WIDTH + WIDTH * 2] =
	    colon[i][j];
	}
    }
//
  for (i = 0; i < LENGTH; i++)
    {
      for (j = 0; j < WIDTH * 2; j++)
	{
	  clockDisplay[i][j + WIDTH * 2 + COLON_WIDTH + WIDTH * 2 +
			  COLON_WIDTH] = s[i][j];
	}
    }

//Display
  for (i = 0; i < LENGTH; i++)
    {
      for (j = 0; j < timeWidth; j++)
	{
	  printf ("%c", clockDisplay[i][j]);
	}
      printf ("\n");
    }

}

void setNumber (int n, int asciiN[LENGTH][WIDTH * 2])
{
  int i = 0, j = 0;
  char zero[][WIDTH] = {
    {" **** "},
    {" *  * "},
    {" *  * "},
    {" *  * "},
    {" *  * "},
    {" *  * "},
    {" **** "}
  };
  char one[][WIDTH] = {
    {"    * "},
    {"    * "},
    {"    * "},
    {"    * "},
    {"    * "},
    {"    * "},
    {"    * "}
  };
  char two[][WIDTH] = {
    {" **** "},
    {"    * "},
    {"    * "},
    {" **** "},
    {" *    "},
    {" *    "},
    {" **** "}
  };
  char three[][WIDTH] = {
    {" **** "},
    {"    * "},
    {"    * "},
    {" **** "},
    {"    * "},
    {"    * "},
    {" **** "}
  };
  char four[][WIDTH] = {
    {" *  * "},
    {" *  * "},
    {" *  * "},
    {" **** "},
    {"    * "},
    {"    * "},
    {"    * "}
  };
  char five[][WIDTH] = {
    {" **** "},
    {" *    "},
    {" *    "},
    {" **** "},
    {"    * "},
    {"    * "},
    {" **** "}
  };
  char six[][WIDTH] = {
    {" **** "},
    {" *    "},
    {" *    "},
    {" **** "},
    {" *  * "},
    {" *  * "},
    {" **** "}
  };
  char seven[][WIDTH] = {
    {" **** "},
    {"    * "},
    {"    * "},
    {"    * "},
    {"    * "},
    {"    * "},
    {"    * "}
  };
  char eight[][WIDTH] = {
    {" **** "},
    {" *  * "},
    {" *  * "},
    {" **** "},
    {" *  * "},
    {" *  * "},
    {" **** "}
  };
  char nine[][WIDTH] = {
    {" **** "},
    {" *  * "},
    {" *  * "},
    {" **** "},
    {"    * "},
    {"    * "},
    {" **** "}
  };
  char none[][WIDTH] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "},
    {"      "},
    {"      "},
    {"      "}
  };

//char asciiN[LENGTH][WIDTH*2]={};
//memset(asciiN,0,sizeof(asciiN));

  int oneDigit = n % 10, twoDigit = n / 10;

  for (i = 0; i < LENGTH; i++)
    {
      for (j = 0; j < WIDTH; j++)
	{
	  switch (twoDigit)
	    {
	    case 0:
	      asciiN[i][j] = zero[i][j];
	      break;
	    case 1:
	      asciiN[i][j] = one[i][j];
	      break;
	    case 2:
	      asciiN[i][j] = two[i][j];
	      break;
	    case 3:
	      asciiN[i][j] = three[i][j];
	      break;
	    case 4:
	      asciiN[i][j] = four[i][j];
	      break;
	    case 5:
	      asciiN[i][j] = five[i][j];
	      break;
	    case 6:
	      asciiN[i][j] = six[i][j];
	      break;
	    case 7:
	      asciiN[i][j] = seven[i][j];
	      break;
	    case 8:
	      asciiN[i][j] = eight[i][j];
	      break;
	    case 9:
	      asciiN[i][j] = nine[i][j];
	      break;
	    }
	}
    }

  for (i = 0; i < LENGTH; i++)
    {
      for (j = 0; j < WIDTH; j++)
	{
	  switch (oneDigit)
	    {
	    case 0:
	      asciiN[i][j + WIDTH] = zero[i][j];
	      break;
	    case 1:
	      asciiN[i][j + WIDTH] = one[i][j];
	      break;
	    case 2:
	      asciiN[i][j + WIDTH] = two[i][j];
	      break;
	    case 3:
	      asciiN[i][j + WIDTH] = three[i][j];
	      break;
	    case 4:
	      asciiN[i][j + WIDTH] = four[i][j];
	      break;
	    case 5:
	      asciiN[i][j + WIDTH] = five[i][j];
	      break;
	    case 6:
	      asciiN[i][j + WIDTH] = six[i][j];
	      break;
	    case 7:
	      asciiN[i][j + WIDTH] = seven[i][j];
	      break;
	    case 8:
	      asciiN[i][j + WIDTH] = eight[i][j];
	      break;
	    case 9:
	      asciiN[i][j + WIDTH] = nine[i][j];
	      break;
	    default:
	      asciiN[i][j + WIDTH] = none[i][j];
	      break;
	    }
	}
    }

}

void showDigital_time()
{
    time_t timer;
    struct tm *t_st;
      system("cls");
      time (&timer);
      t_st = localtime (&timer);

      displayTime (t_st->tm_hour, t_st->tm_min, t_st->tm_sec);
}


//Function For the Speech Generator
void speak(char *phraseIn)
{
    strcpy(charCommand,"espeak -v +f5 \"");
    strcat(charCommand, phraseIn);
    strcat(charCommand,"\"");
    system(charCommand);
}



//Alarm Clock Starts Here





//Delay Function used in Alarm Clock
void delayAC(int ms)  //delay function
{
    clock_t timeDelay = ms + clock();    //Step up the difference from clock delay and clock() gives CPU clock time
    while (timeDelay > clock());         //stop when the clock is higher than time delay
}


//Selection Function used in Alarm Clock
void selectionAC(int h,int m)       // menu selection
{
    switch(getch())        //collect input from user
    {
    case '1':          //press 1 to reset everything and set flag to 0
        flag = 0;
        fflush(stdin);
        system("cls");
        fflush(stdout);
        h=m=0;
        startReset();
        break;
    case '2':          // press 2 to go to menu and set flag to 1
        flag = 1;
        system("cls");
        longjmp(buf,1);
        break;
    default:        // press any other key to set flag to 0
        flag = 0;
        break;
    }

}


void ring_alarm(int h,int m, char *str)           // count and display digital clock time
{

    int hour,minute,second;
    flag=0;
    while(hour!=h || minute!=m)         //keep looping while time doesn't match with alarm time
    {
        // moves cursor to the beginning of current line while working on it
        printf("\r");
        // taking os time
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        //update hour, minute and second
        hour=tm.tm_hour;
        minute=tm.tm_min;
        second = tm.tm_sec;

        //print time in HH : MM : SS format
        printf("\t\t%02d : %02d : %02d ",hour,minute,second);
        if(kbhit())
        {
            selectionAC(h,m);
        }
        delayAC(998);       // delay for 0.998 sec
    }
    printf("\a");         //beep sound
    speak(str);
    system("cls");
    printf("*************************************************\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED|BACKGROUND_GREEN);  //light brown background
    printf("1. Snooze   2. Stop Alarm  ");    // menu for user
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    printf("\n*************************************************\n\n");
    delayAC(500);        // delay for 0.5 sec
    snooze_stopAlarm(h,m,str);
}


void snooze_stopAlarm(int h,int m, char *str)      // after selection of snooze or stop option
{
    while(!kbhit() && flag==0)          //keep beeping while the user didn't hit any key and flag is 0
    {
        printf("\a");
        speak(str);         //beep sound
        delayAC(500);         // delay for 1 sec
    }
    switch(getch())        //collect input from user
    {

    case '1':              // press 1 to snooze and  set flag to 0
        flag = 0;
        system("cls");                    // clear output screen
        printf("******************************************************\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN); //green background
        printf("1. Reset alarm   2. End program\n");      //menu for user
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        printf("******************************************************\n\n");
        ring_alarm(h,m+5,str);          // 5 minutes snooze
        break;
    case '2':          // press 2 to go to menu and set flag to 1
        flag = 1;
        system("cls");
        longjmp(buf,1);
        break;
    default:       // press any other key to set flag to 0
        flag = 0;
        snooze_stopAlarm(h,m,str);
        break;

    }
}

void startReset(void)
{
    char str[1000];
    //fflush(stdin);
    printf("Name of the label(0 to exit) : ");    // name of task to do
    gets(str);
    fflush(stdin);
     if(strcmp("0",str)==0) //Exit command
            {
                 system("cls");
                longjmp(buf, 1); //Going back to menu
            }
    char x[25],y[25];
    int h,m;
    printf("Set alarm in 24 hr format(HH MM): ");
    scanf("%s %s",&x,&y);
    system("cls");                // clear output screen
    while(!((strlen(x)<=2 && strlen(y)<=2) && ((x[0]>='0'&& x[0]<'3')&&(x[1]>='0'||x[1]<'4')&&(y[0]>='0'&& y[0]<'6')&&(y[1]>='0'&&y[1]<='9'))))
    {
        printf("Invalid input\nPlease set alarm again in 24 hr format(HH MM): ");
        scanf("%s %s",&x,&y);
        system("cls");                // clear output screen
    }
    h=10*((int)x[0]-48)+((int)x[1]-48);
    m=10*((int)y[0]-48)+((int)y[1]-48);
    printf("******************************************************\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN);  //light blue background
    printf("1. Reset Alarm      2. Go back to Menu\n");     //menu for user
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    printf("*******************************************************\n\t\t  ");
    ring_alarm(h,m,str);
}

void setAlarm(void)
{
    printf("*************************************************\n");
    printf("**************#"); //Background change to do a little dhong
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_RED);
    printf("  THIS IS SETTING ALARM  "); //Setting everything normal
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    printf("#**************\n");     //output the data
    printf("*************************************************\n");
    fflush(stdout);

    startReset();
}

//Alarm Clock Ends here






//StopWatch Starts Here


//Delay of stopWatch
void delaySW(int ms)    //delay function
{
    clock_t timeDelay = ms + clock();    //Step up the difference from clock delay and clock() gives CPU clock time
    while (timeDelay > clock());         //stop when the clock is higher than time delay
}

//Print Data For StopWatch
int printDataSW(int minute,int second,int milli)   //print data to screen
{
    printf("\r");    // moves cursor to the beginning of current line while working on it
    printf("Time count-\t %02d : %02d : %03d ",minute,second,milli);      //output the data
    delaySW(50);      //delay for 50 milliseconds
}

//Selection For StopWatch
int selection()       // menu selection
{
    switch(getch())     //collect input from user
    {
    case '1':
        flag = 0;         //press 1 to start/resume and set flag to 0
        s=s+(clock()-n);  //starting clock time and after resume, clock time
        break;
    case '2':
        flag = 1;       //press 2 to stop, set flag to 1
        break;
    case '3':
        if(s!=0 && n!=0)   // when stopwatch not start running, this won't trigger
        {
            s=n=0;
            min = second = milli= 0;
            flag = 1;                 //press 3 reset everything, set flag to 1 means stop
            printDataSW(min,second,milli);        //print the new data after reset
        }
        else         // at the start, this will trigger
        {
            flag = 1;
        }
        break;
    case '4':      // press 4 to go back to menu
        system("cls");
        longjmp(buf,1);
    default:
        if(s!=0 && n!=0)   // when stopwatch not start running, this won't trigger
        {
        running_clock();
        flag = 0;
        }
        else        // at the start, this will trigger
        {
            flag = 1;
        }
        break;
    }
}

//Running StopWatch
void running_clock(void)
{
    while(1)
    {
        while(!kbhit() && flag ==0)       //keep looping while the user didn't hit any key and flag is 0
        {
            n=clock();                 // current clock time
            min = ((n-s)/1000)/60 ;    //minute calculation
            second = ((n-s)/1000)%60 ;    // second calculation
            milli =  (n-s)%1000 ;      //milli second calculation
            printDataSW(min,second,milli);      // print current time count
        }
        selection();
    }
}

void startStopWatch(void)
{
    printf("*************************************************\n");
    printf("**************#");  //Background change to do a little dhong
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_RED);
    printf("  THIS IS STOPWATCH  ");  //Setting everything normal
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    printf("#**************\n");     //output the data
    printf("*************************************************\n\n\n");
    printf("****************************************************************************\n");
    printf(" 1.Start/Resume  2.Stop  3.Reset  4.Go back to Menu\n");       //menu for user
    printf("****************************************************************************\n");
    selection();
    running_clock();
}

//StopWatch Ends Here






//Timer Starts Here




//Delay of Timer
void delay(int ms)  //delay function
{
    clock_t timeDelay = ms + clock();    //Step up the difference from clock delay and clock() gives CPU clock time
    while (timeDelay > clock());         //stop when the clock is higher than time delay
}

//Print Data of Timer
void printData(int hour,int mini,int sec){

    printf("\r");  // moves cursor to the beginning of current line while working on it
    printf("Time left(Enter to back)-\t %02d : %02d : %02d ",hour,mini,sec);      //output the data
    delaySW(50);      //delay for 50 milliseconds
}


void countdown(int hour,int mini,int sec){
    int x = hour*3600 + mini*60 + sec ; //converting time to seconds
    int init = x;
    int h,m,s;
    strcpy(phrase,"Time's Up");
  while(x&&!kbhit()){
    float som = (float)x/(float)init ; //present left seconds divided by initial seconds

    h = x/3600;
    m = (x -(3600*h))/60;
    s = (x -(3600*h)-(m*60));
    if(som<=0.25){
        printf("\033[0;31m"); //RED
    }
    if(som<=0.5&&som>0.25){
        printf("\033[0;33m"); //YELLOW
    }
   printData(h,m,s);
   printf("\033[0m");
   delay(998);
   x--;
  }
  system("cls");
  if(x==0)
  {
    printf("\a\n\n\n\t\tTime's Up !!!\n\n\n");
  speak(phrase);
  }
  else
  {
      longjmp(buf,1);
  }

}


void startTimer(void)
{
    int hour,mini,sec;
    printf("*************************************************\n");
    printf("**************#");
    //Background change to do a little dhong
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_RED);
    printf("  THIS IS A TIMER  ");
    //Setting everything normal
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    printf("#**************\n");     //output the data
    printf("*************************************************\n");
    printf("\nPress Enter to set timer\nPress q to go back\n");
    if(getch()=='q')
    {
        system("cls");
        longjmp(buf,1);
    }
    else
    {
        system("cls");
      printf("\n\nSet Timer for (Hour : Minute : Second) : ");
      scanf("%d:%d:%d",&hour,&mini,&sec);
      system("cls");
      printf("\n\n");
      countdown(hour,mini,sec);
      longjmp(buf,1);
    }

}

//Timer Ends Here







//Time Converter Starts here

int isSpace(char*str)
{
    int flag =0;
    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]==' '||str[i]==','||str[i]=='-')
            flag++;

    }
    return flag;
}
int isSpaceOnly(char*str)
{
    int flag =0;
    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]==' ')
            flag++;

    }
    return flag;
}

//Replace Numeric values to decrease leveshtein
void replaced(char*str)
{
    int i;
    for(i=0;i<strlen(str);i++)
    {
        if(str[i]>='1'&&str[i]<='9')
            str[i]='m';
    }
}

//This is used in printing possible search results
void printstruc(info *arrays , int n)
{
    int i;
    for(i=0;i<n;i++)
    {
       printf("%d )  %s\n",arrays[i].as,arrays[i].som);
    }
}

//The famous delay Function!!!
void delayTC(int ms)
{
    clock_t timeDelay = ms + clock();    //Step up the difference from clock delay and clock() gives CPU clock time
    while (timeDelay > clock());         //stop when the clock is higher than time delay
}

//This function is the most important one
//It takes the time difference as a string
//Converts it to integer and
//Adds or subtracts time difference with the clock time
void splittime(char *str , int s , char*result)
{
    int str1[3]={},str2[3]={};
    int i,j=0,k=0;

    for(i=0;str[i]!=':';i++)
    {
      str1[k] = (int)str[i] - 48;
      k++;
    }
    for(i=i+1;str[i]!='\0';i++)
    {
      str2[j] = (int)str[i] - 48;
      j++;
    }
   int h = (10*str1[0]+str1[1]);
   int m = 10*str2[0]+str2[1] ;
   if(s==1) h=h-6;
   if(s==2)h=-h-6;
//   char string[]="Current time in " ;
//   strncat(string,result,strlen(string)+strlen(result)+1);
//   string[strlen(string)-1]='\0';
//    speak(string);
    printf("\n");
    printf("\t\t");//Changing color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_RED);
    puts(result);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
    printf("\n\n\n\nTime in chosen place(Press enter to choose another)\n\n\n");
    int hour=0,minute=0,second=0;
    while(1)
    {

        printf("\r");
         // taking os time
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        //update hour, minute and second

        hour=tm.tm_hour;
        minute=tm.tm_min;
        second = tm.tm_sec;
        if(s==1)
        {
           hour = hour+h;
           minute=minute+m;
           if(minute>59)
           {
               hour=hour+1;
               minute=minute-60;
           }
            if(hour>23)
           {
               hour=hour-24;
           }
           if(hour<0)
           {
               hour = hour+24;
           }

        }
        else if(s==2)
        {
           hour = hour+h;
           minute=minute-m;

           if(minute<0)
           {
               hour=hour-1;
               minute=minute+60;
           }
           if(hour<0)
           {
               hour=hour+24;
           }
        }
        //print time in HH : MM : SS format
        printf("\t\t\t\t\t%02d : %02d : %02d ",hour,minute,second);
        //clear output buffer
        fflush(stdout);
        if(kbhit())
        {
            getch();
            //break;
            red=1;
            system("cls");
            longjmp(come,1);
        }
        delayTC(998);

    }
    system("cls");

    fflush(stdin);
}


//This function excludes unwanted characters
//for handling the files easily
//remove white spaces , comas, extra chracters
char *remove_white_spaces(char *str)
{
	int i = 0, j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
          str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	 i = 0, j = 0;
	while (str[i])
	{
		if (str[i] != ',')
          str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	 i = 0, j = 0;
	while (str[i])
	{
		if ((str[i]>='a'&&str[i]<='z'))
          str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return str;
}


int found (char *wanted)  //Function if user's entered country is found
{
    char str[300], country[200] ;
    char roughcountry[200], roughwanted[200];
    int i=0,f=0;
    FILE *fp;
    fp = fopen("timemod.txt", "r");
    if(fp == NULL) {
            printf("\nFILE NOT FOUND !\n");
		longjmp(buf,1);
	}
	while(!feof(fp))
    {
       fgets(str , 70 ,fp);
       for(i=0;str[i]!='#';i++)
       {
           country[i]=str[i];
       }
       country[i]='\0';
       strcpy(roughcountry , remove_white_spaces(strlwr(country)));
       strcpy(roughwanted , remove_white_spaces(strlwr(wanted)));
       if(strcmp((roughcountry),(roughwanted))==0)
       {
           f = 1;
       }

    }
    fclose(fp);
    return f;

}

//Prints the country if found
void foundPrint (char *wanted)
{
    char str[300], country[200] ,countryreal[200];
    char roughcountry[200], roughwanted[200];
    int i=0;
    FILE *fp;
    fp = fopen("timemod.txt", "r");
    if(fp == NULL) {
            printf("\nFILE NOT FOUND !\n");
		longjmp(buf,1);
	}
	while(!feof(fp))
    {
       fgets(str , 70 ,fp);
       for(i=0;str[i]!='#';i++)
       {
           country[i]=str[i];
       }
       country[i]='\0';
       strcpy(countryreal,country);
       strcpy(roughcountry , remove_white_spaces(strlwr(country)));
       strcpy(roughwanted , remove_white_spaces(strlwr(wanted)));
       if(strcmp((roughcountry),(roughwanted))==0)
       {
          puts(countryreal);
          break;
       }

    }
    fclose(fp);

}

//This function shows desired time
void foundPrintDiff (char *wanted)
{
    char str[300], country[200] , timedeff[10],countryreal[200];
    char roughcountry[200], roughwanted[200];
    int i=0, j=0 ;
    FILE *fp;
    fp = fopen("timemod.txt", "r");
    if(fp == NULL) {
            printf("\nFILE NOT FOUND !\n");
		longjmp(buf,1);
	}
	while(!feof(fp))
    {
       fgets(str , 70 ,fp);
       for(i=0;str[i]!='#';i++)
       {
           country[i]=str[i];
       }
       country[i]='\0';
       strcpy(countryreal,country);
       strcpy(roughcountry , remove_white_spaces(strlwr(country)));
       strcpy(roughwanted , remove_white_spaces(strlwr(wanted)));
       if(strcmp((roughcountry),(roughwanted))==0)
       {
         for(i=strlen(str)-6;i<strlen(str);i++)
         {
           timedeff[j]= str[i];
           j++;
         }
         int x;
          timedeff[j] ='\0';
          if(str[strlen(str)-7]=='+') x=1;
          else if(str[strlen(str)-7]=='-') x=2;
          splittime(timedeff,x,countryreal);
          break;
       }

    }
    fclose(fp);

}
//Checks if inputted value is substring of any element of the file
int foundSubstr(char *wanted)
{
    int i=0,oc=0 ;
    char str[300], country[200]  , countryreal[200];
    char roughcountry[200], roughwanted[200];
    info arrays[100];
    FILE *fp;
    fp = fopen("timemod.txt", "r");
    if(fp == NULL) {
            printf("\nFILE NOT FOUND !\n");
		longjmp(buf,1);
	}
	while(!feof(fp))
    {
       fgets(str , 70 ,fp);
       for(i=0;str[i]!='#';i++)
       {
           country[i]=str[i];
       }
       country[i]='\0';
       strcpy(countryreal,country);
       strcpy(roughcountry , remove_white_spaces(strlwr(country)));
       strcpy(roughwanted , remove_white_spaces(strlwr(wanted)));
       if(strstr((roughcountry),(roughwanted)))
       {
          arrays[oc].as = oc+1;
          strcpy(arrays[oc].som,countryreal);
          oc++;
       }

    }
    return oc;
    fclose(fp);

}

//Prints the substrings to choose
void foundSubstrPrint(char *wanted)
{
    int i=0,oc=0 ,choo;
    char str[300], country[200] ,countryreal[200];
    char roughcountry[200], roughwanted[200];
    info arrays[100];
    FILE *fp;
    fp = fopen("timemod.txt", "r");
    if(fp == NULL) {
            printf("\nFILE NOT FOUND !\n");
		longjmp(buf,1);
	}
	while(!feof(fp))
    {
       fgets(str , 70 ,fp);
       for(i=0;str[i]!='#';i++)
       {
           country[i]=str[i];
       }
       country[i]='\0';
       strcpy(countryreal,country);
       strcpy(roughcountry , remove_white_spaces(strlwr(country)));
       strcpy(roughwanted , remove_white_spaces(strlwr(wanted)));
       if(strstr((roughcountry),(roughwanted)))
       {
          arrays[oc].as = oc+1;
          strcpy(arrays[oc].som,countryreal);
          oc++;
       }

    }
    if(oc==1)
    {
           foundPrintDiff(arrays[0].som);
    }
    if(oc>1&&oc<21)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN);
        printf("\nSimilar search results :\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        printstruc(arrays,oc);
        printf("\n\n");
        printf("Make a choice :  ( 0 to Search Again )    ");
        scanf("%d",&choo);
         //Coming back to converter function
        if(choo==0)
        {
            red=1;
            system("cls");
             longjmp(come, 1);
        }
        if(choo>oc)
        {
            longjmp(buf,1);
        }
        system("cls");
        foundPrintDiff(arrays[choo-1].som);
    }
    else if(oc>20)
    {
        int c;
        printf("Too many results ! Search specifically !\n");
        printf("Choose : \n1)See all of them\n2)Search again\n");
        scanf("%d",&c);
        if(c==1)
        {
                 system("cls");
                   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN);
                printf("\nSimilar search results :\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
                printstruc(arrays,oc);
                printf("\n\n");
                printf("Make a choice :  ( 0 to Search Again )    ");
                scanf("%d",&choo);
                 //Coming back to converter function
                if(choo==0)
                {
                    red=1;
                    system("cls");
                     longjmp(come, 1);
                }
                if(choo>oc)
                {
                    longjmp(buf,1);
                }
                system("cls");
                foundPrintDiff(arrays[choo-1].som);
        }
    else if(c==2)
    {
    red=1;
//    getch();
    longjmp(come, 1);
    }

    }
    fclose(fp);

}


//If user gives a random word, this function will
//match the word with every individual word of the
//words containing file and find the closest word
//closest word will be used for substring matching
void matchWordByWord(char *wanted)
{
  int c, min=10000 , l ;
    char str[100],extra[100],strreal[100];
    FILE *fp2;
    fp2 = fopen("ForLavenstein.txt", "r");
    if(fp2 == NULL) {
            printf("\nFILE NOT FOUND !\n");
		longjmp(buf,1);
	}
	while(!feof(fp2))
    {
       fgets(str , 30 ,fp2);

       strcpy(strreal,str);
       l=levenshtein(strlwr(wanted),strlwr(str));
       if(l<min)
       {
         min=l;
         strcpy(extra,strreal)  ;
       }
    }
    printf("\n\nFound a word closest to your search : \n\n");
    puts(extra);
    printf("\nWant to see details?  \n1) Yes  ( Press 1 )\n2) No   ( Press 2 to Search Again )\n");
    scanf("%d",&c);
    system("cls");
    if(c==1)
    foundSubstrPrint(extra);
    //Coming back to main function
    else if(c==2)
    {
        red=1;
        longjmp(come, 1);
    }
    fclose(fp2);

}

void splitString(char *str1)
{
    char newString[100][200];
    int i,j,ctr;

    j=0; ctr=0;
    for(i=0;i<=(strlen(str1));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(str1[i]==' '||str1[i]==','||str1[i]=='-'||str1[i]=='\0')
        {
            newString[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            newString[ctr][j]=str1[i];
            j++;
        }
    }
    setjmp(ag);
    while(rever<ctr)
    {
        matchWordByWordPRO(newString[rever]);
    }
    longjmp(come,1);


}


void matchWordByWordPRO(char *wanted)
{
  int c, min=10000 , l ;
    char str[100],extra[100],strreal[100];
    FILE *fp2;
    fp2 = fopen("ForLavenstein.txt", "r");
    if(fp2 == NULL) {
            printf("\nFILE NOT FOUND !\n");
		longjmp(buf,1);
	}
	while(!feof(fp2))
    {
       fgets(str , 30 ,fp2);

       strcpy(strreal,str);
       l=levenshtein(strlwr(wanted),strlwr(str));
       if(l<min)
       {
         min=l;
         strcpy(extra,strreal)  ;
       }
    }
    foundSubstrPrintPRO(extra);

    fclose(fp2);

}

void foundSubstrPrintPRO(char *wanted)
{
    int i=0,oc=0 ,choo;
    char str[300], country[200] ,countryreal[200];
    char roughcountry[200], roughwanted[200];
    info arrays[100];
    FILE *fp;
    fp = fopen("timemod.txt", "r");
    if(fp == NULL) {
            printf("\nFILE NOT FOUND !\n");
		longjmp(buf,1);
	}
	while(!feof(fp))
    {
       fgets(str , 70 ,fp);
       for(i=0;str[i]!='#';i++)
       {
           country[i]=str[i];
       }
       country[i]='\0';
       strcpy(countryreal,country);
       strcpy(roughcountry , remove_white_spaces(strlwr(country)));
       strcpy(roughwanted , remove_white_spaces(strlwr(wanted)));
       if(strstr((roughcountry),(roughwanted)))
       {
          arrays[oc].as = oc+1;
          strcpy(arrays[oc].som,countryreal);
          oc++;
       }

    }
    int cc;
    if(oc==1)
    {
        printf("\n\n");
        puts(arrays[0].som);
        printf("\n\nFinding this?\n(1 for yes)\n(2 for no)\n");
        scanf("%d",&cc);
    if(cc==1)foundPrintDiff(arrays[0].som);
    else
    {
        system("cls");
        rever++;
        longjmp(ag,1);
    }

    }
    if(oc>1&&oc<21)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN);
        printf("\nSimilar search results :\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        printstruc(arrays,oc);
        printf("\n\n");
        printf("Make a choice :  ( 0 to Search Again )    ");
        scanf("%d",&choo);
         //Coming back to converter function
        if(choo==0)
        {
            system("cls");
            rever++;
             longjmp(ag, 1);
        }
        if(choo>oc)
        {
            longjmp(buf,1);
        }
        system("cls");
        foundPrintDiff(arrays[choo-1].som);
    }
    else if(oc>20)
    {
        printf("Too many results ! Search specifically !\n");
        printf("See next - ");
        getch();
        red=1;
        rever++;
        longjmp(ag, 1);
    }
    fclose(fp);

}


int minmin(int a, int b, int c) //finding minimum from three integers
{
	if(a <= b && a <= c)
	{
		return a;
	}
	else if(b <= a && b <= c)
	{
		return b;
	}
	else if(c <= a && c <= b)
	{
		return c;
	}
	return 0;
}
int levenshtein(char *s1, char *s2)  //Function to determine closeness of two names
{
    unsigned int x, y, s1len, s2len;
    strcpy(s1,strlwr(remove_white_spaces(s1)));
    strcpy(s2,strlwr(remove_white_spaces(s2)));
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = minmin(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));

    return(matrix[s2len][s1len]);
}


void startConverter(void)
{

    char wanted[200], emer[200] , wanteds[200], extra[200];
    printf("\n**********************************************************\n");
    printf("**************#");
    //Background change to do a little dhong
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_RED);
    printf("  THIS IS A TIME CONVERTER  ");
    //Setting everything normal
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    printf("#**************\n");     //output the data
    printf("**********************************************************\n");

    printf("Please Avoid Using Any Disturbing Characters\n\n\n");

    FILE *fp;
    fp = fopen("timemod.txt", "r");
    if(fp == NULL) {
            printf("\nFILE NOT FOUND !\n");
		longjmp(buf, 1);
	}

	while(1)
    {
        hi:
            setjmp(come);
            rever=0;
        printf("\nBe Specific about your input\n");
        printf("Avoid Spelling Mistakes\n");
        printf("\n\nType name of a place (0 to exit) : ");
        //getchar();
         gets(emer);
         strcpy(extra,emer);
        system("cls");
        strcpy(wanteds,emer);
        if(strcmp("0",wanteds)==0) //Exit command
            {
                longjmp(buf, 1); //Going back to menu
            }

            //When user tries to give too many unwanted characters but only a few letters
        strcpy(wanted,remove_white_spaces(strlwr(emer)));
        if(strlen(wanted)<3)
            {
                if(red==0)
                {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_RED);
                printf("\nGive the input correctly \n");//Wanna give red color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
                goto hi;
                }
                else
                {
                    red=0;
                    goto hi;
                }

            }
            replaced(wanteds);

        int count = isSpace(wanteds);
        if(found(wanteds)) // If the name is found in the list
        {
            system("cls");
           foundPrintDiff(wanteds);
        }
        else if(foundSubstr(wanteds)!=0) //If the input is a substring of any name of the list
        {
           foundSubstrPrint(wanteds);
        }
        else if(foundSubstr(wanteds)==0) //When input is neither found nor a substring
        {
            if(count==0)
            {
                 matchWordByWord(wanteds);
            }
            else
            {
                  splitString(extra);
            }
        }

    }

    fclose(fp);

}

//End
