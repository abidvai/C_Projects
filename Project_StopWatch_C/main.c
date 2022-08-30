//  main.c
//  Project_StopWatch_C
//  Created by Abdullah Al Abid on 25/8/22.

#include <stdio.h>
#define cycle 5

#ifdef _WIN32
#inlude<conio.h>
#definr sleep(x) sleep(x*1000)
#else
#define clrscr() printf("\e[1;1H\e[2J")
#include<unistd.h>
#endif



int main(int argc, const char * argv[]) {
    int hour, minutes, second;
    printf("Enter Hour Minute Second:");
    scanf("%d%d%d",&hour, &minutes, &second);
    clrscr();
    
    int h = 0, m = 0, s = 0;
    while(1)
    {
        printf("\n\n-------------------------stop Watch------------------\n\n\n");
        printf("                 %.2d:%.2d:%.2d\n",h,m,s);
        printf("\n\n-----------------------------------------------------\n\n\n");
        if(h == hour && m == minutes && s == second){
            break;
        }else{
            clrscr();
        }
        s++;
        sleep(1);
        if(s == cycle){
            m++;
            s = 0;
        }
        if(m == cycle){
            h++;
            m = 0;
        }
    }
    return 0;
}
