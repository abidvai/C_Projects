#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
//----------------------------
//User-Define FUNCTIONS
int welcome();
void Loading();
int Login();
int userBuilding();
void Register();
void RegBuilding(char *Name);
void recover();
void rentRate(FILE *fp1);
//----------------------------
//Global Variable
int flatEachFloor[100];
int flNum;
int sumFlat;
//----------------------
int main(){
	int logORreg=welcome();
	if(logORreg==1) Login();
	if(logORreg==2) Register();
	if(logORreg==3) recover();
	return 0;
}
int welcome(){
	int choice=0;
	printf("*****|WELCOME to the Program|*****");
	level:
	printf("\n\n\tChoose:\n\t\t[1] Login\n\t\t[2] Register\n\t\t[3] Account Recover\n\t\tChoice: ");
	scanf("%d",&choice);
	if(choice<1||choice>3) goto level;
	Loading(500);
	system("cls");
	return choice;
}
void Loading(int time){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tLoading ");
	Sleep(time+50);
	printf(". ");
	Sleep(time-50);
	printf(". ");
	Sleep(time-100);
	printf(".");
}
int Login(){
	FILE *fp=fopen("HouseOwner_database.txt","r"); //opening database
	int i=0,j=0;
	char chk[5][100],curr;
	char name[100],pin[20],mob[20];
	printf("*****|WELCOME to the Login Page|*****\n");
	printf("\n\n\tEnter User Name: ");
	scanf("%s",name);
	printf("\n\tEnter PIN code:");
	printf("\n\n\t\t   PIN: ");
	int p=0;
	//PIN input
    do{
        pin[p]=getch();
        if(pin[p]=='\b') printf("\b\b");
        if(pin[p]!='\r') printf("*");
        p++;
    }while(pin[p-1]!='\r');
    pin[p-1]='\0';
    while(1){
    	//taking data from database in to chk[] array variable
    	while(1){
			curr=getc(fp);
			if(curr==EOF) break;
			if(curr=='\t'){chk[j][i]='\0';j++;i=0;continue;}
			if(curr=='\n') break;
			chk[j][i]=curr;
			i++;
		}
		if(curr==EOF) break;
		i=0;j=0;
		//comparing the username and pin for valid LOGIN
		if(strcmp(chk[1],name)==0){
			if(strcmp(chk[0],pin)==0) {
				fclose(fp);
				Loading(500);
				system("cls");
				userBuilding(chk[1]);
				return 0;
			}
			else continue;
		}
		else continue;
	}
	fclose(fp);//File closing
	printf("\n\n\n\t\tWrong Username or Password\n\n\t\tGoto Welcome Menu to recover");
	printf("\n\n\t\tPress 'q'-Key to goto Welcome Menu\n\n\t\t\t\t");
	if(getch()==81||getch()==113){
		fflush(stdin);
		Loading(500);
		system("cls");
		main();
	}
	return 0;
}
void Register(){
	char name[100],pin[20],mob[20];
	FILE *fp=fopen("HouseOwner_database.txt","a"); //database opening
	printf("*****|WELCOME to the Registration Page|*****\n");
	printf("\n\tInput owners First Name (Will be used as Username).\n\tFirst Name: ");
	scanf("%s",name);
	printf("\tPIN: ");
	scanf("%s",pin);
	printf("\tEnter Your Mobile Number to recover: ");
	scanf("%s",mob);
	fprintf(fp,"%s\t%s\t%s\n",pin,name,mob); //inputing into the database
	fclose(fp);
	char *Name = name;
	Loading(500);
	system("cls");
	RegBuilding(Name);
}
void recover(){
	FILE *fp=NULL;
	int i=0,j=0,count;
	char chk[5][100],curr;
	char name[100],pin[20],mob[20];
	level:
	fp=fopen("HouseOwner_database.txt","r");//opening database
	printf("*****|Account Recovery Page|*****\n\n");
	printf("### To recover You need to atleast correctly input 2 field ###");
	printf("\n______________________________________________________________\n");
	printf("\n\n\tEnter User Name: ");
	scanf("%s",name);
	printf("\n\tEnter Mobile Number: ");
	scanf("%s",mob);
	printf("\n\tEnter PIN code: ");
	scanf("%s",pin);
	while(1){
    //taking data from database in to chk[] array variable
    	while(1){
			curr=getc(fp);
			if(curr==EOF) break;
			if(curr=='\t'){chk[j][i]='\0';j++;i=0;continue;}
			if(curr=='\n') break;
			chk[j][i]=curr;
			i++;
		}
		if(curr==EOF) break;
		i=0;j=0;
		//comparing the username and pin for valid LOGIN
		count=0;
		if(strcmp(chk[0],pin)==0) count++;
		if(strcmp(chk[1],name)==0) count++;
		if(strcmp(chk[2],mob)==0) count++;
		if(count==2){
			printf("______________________________________________________________________\n");
			printf("\n\n\tYour Username: %s\n\n\tYour Mobile Number: %s\n\n\tYour PIN: %s",chk[1],chk[2],chk[0]);
			printf("\n\n______________________________________________________________________\n");
			fclose(fp);
			printf("\n\tPress 'Any Key' to go to Welcome Screen\n\n\t");
			getch();
			fflush(stdin);
			Loading(500);
			system("cls");
			main();
		}
	}
	fclose(fp);
	if(count<=1){
		printf("\n\n______________________________________________________________________\n");
		printf("\n\tWrong!!!\n");
		printf("\n\n\t\tPress 'q'-Key to goto Welcome Menu\n\n\t\tPress any key to Try Again!\n\n\t\t\t\t");
		if(getch()==81||getch()==113){
			fflush(stdin);
			Loading(500);
			system("cls");
			main();
		}
		Sleep(1000);
		system("cls");
		goto level;
	}
}
void RegBuilding(char *Name){
	int i,j,choice,flt,tempTK;
	char filename[100],fltID[100],filename1[100];
	sprintf(filename,"%s_Building_Database.txt",Name);	//File for payed or not
	sprintf(filename1,"%s_flat_Database.txt",Name);
	FILE *fp=NULL;		//File for payed or not_opened
	FILE *fp1=NULL;
	printf("*****|Welcome %s to the Building Registration Page|*****\n",Name);
	printf("\n\n\tPlease fill Following information Accordingly\n______________________________________________________\n");
	printf("\n\n\t\tNumber of Floors of the Builing (Considering Ground Floor as 1st Floor): ");
	scanf("%d",&flNum);
	printf("\n\tCatagorize Your Floors:\n\t\t\t[1] Office Floor (Full Floor)\n\t\t\t[2] Family (each floor with 1 or multiple Units)\n\t\t\t");
	for(i=0;i<flNum;i++){
		if(i==0) printf("\n\n\t\t\tGround Floor: ");
		if(i>0) printf("\n\n\t\t\tFloor#%d: ",i);
		printf("\n\n\t\t\tCatagorize [1]Office or [2]Family : ");
		scanf("%d",&choice);
		if(choice==1){
			printf("\n\n\t\tMonthly Rent amount: ");
			scanf("%d",&tempTK);
			flatEachFloor[i]=1;
			fp=fopen(filename,"a");
			fprintf(fp,"%d %d Floor#%d %d\n",i,1,i,tempTK);
			fclose(fp);
			fp1=fopen(filename1,"a");
			if(i==flNum-1) fprintf(fp1,"Floor#%d %d %d %d %d %d %d %d %d %d %d %d %d %d",i,tempTK,0,0,0,0,0,0,0,0,0,0,0,0);
			else fprintf(fp1,"Floor#%d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",i,tempTK,0,0,0,0,0,0,0,0,0,0,0,0);
			fclose(fp1);
		}
		if(choice==2){
			printf("\n\n\t\tHow many Flat in this Floor? >>| ");
			scanf("%d",&flt);
			flatEachFloor[i]=flt;
			fp=fopen(filename,"a");
			fprintf(fp,"%d %d ",i,flt);
			fclose(fp);
			for(j=1;j<=flt;j++){
				printf("\n\t\tID of flat#%d: ",j);
				scanf("%s",fltID);
				printf("\n\t\tMonthly Rent amount: ");
				scanf("%d",&tempTK);
				fp=fopen(filename,"a");
				fprintf(fp,"%s %d ",fltID,tempTK);
				fclose(fp);
				fp1=fopen(filename1,"a");
				if(i==flNum-1) fprintf(fp1,"%s %d %d %d %d %d %d %d %d %d %d %d %d %d",fltID,tempTK,0,0,0,0,0,0,0,0,0,0,0,0);
				else fprintf(fp1,"%s %d %d %d %d %d %d %d %d %d %d %d %d %d\n",fltID,tempTK,0,0,0,0,0,0,0,0,0,0,0,0);
				fclose(fp1);
			}
			fp=fopen(filename,"a");
			fprintf(fp,"\n");
			fclose(fp);
		}
	}
	printf("\n\n\t\t\t\tCongaratulation Registration Done!!!\n\t\t\t\tTaking You back to Main Manu in:\n");
	Sleep(200);
	printf("\t\t\t\t\t\t\t3\n");
	Sleep(700);
	printf("\t\t\t\t\t\t\t2\n");
	Sleep(700);
	printf("\t\t\t\t\t\t\t1\n");
	Sleep(700);
	system("cls");
	main();
}
int userBuilding(char *Name){
	//*********Data from the File to the Varaibles___START
	char filename[100],filename1[100];
	sprintf(filename,"%s_Building_Database.txt",Name);
	sprintf(filename1,"%s_flat_Database.txt",Name);
	FILE *fp=fopen(filename,"r");
	FILE *fp1=fopen(filename1,"r");
	char buildFlatID[100][100][100],flatID[100][100];
	int BuildFlatID[100][100],FlatID[100][100];
	int i=-1,j,counterB=-1,counterF=-1;
	while(1){
		i++;
		counterB++;
		fscanf(fp,"%d %d",&BuildFlatID[i][0],&flatEachFloor[i]);
		for(j=1;j<=flatEachFloor[i];j++){
			fscanf(fp,"%s %d",buildFlatID[i][j],&BuildFlatID[i][j]);
		}
		if(feof(fp)) break;
	}
	i=-1;
	while(1){
		i++;
		if(feof(fp1)) break;
		counterF++;
		fscanf(fp1,"%s %d %d %d %d %d %d %d %d %d %d %d %d %d",flatID[i],&FlatID[i][1],&FlatID[i][2],&FlatID[i][3],&FlatID[i][4],&FlatID[i][5],&FlatID[i][6],&FlatID[i][7],&FlatID[i][8],&FlatID[i][9],&FlatID[i][10],&FlatID[i][11],&FlatID[i][12],&FlatID[i][13]);

	}
	fclose(fp);fclose(fp1);
	i=0;j=0;
	//*********Data from the File to the Varaibles___DONE
	int choice,Choice,Earning=0,paid=0;
	char editFlt[100];
XXX:
	printf("*****|Welcome %s|*****\n",Name);
	printf("\n\tFLAT LISTs: ");
	for(i=0;i<=counterF;i++){
		printf("%s ; ",flatID[i]);
	}
	printf("\n\t\t[1] Payment  [2] Total Payed  [3] Total Earning(month)  [4] Exit\n\t\t\t\tCHOOSE: ");
	scanf("%d",&choice);
	if(choice==4) return 0;
	switch(choice){
		case 1:
			printf("\n\tWhich Flat [input from the list,(Case Sensative!!)]: ");
			scanf("%s",editFlt);
			for(i=0;i<=counterF;i++){
				if(strcmp(editFlt,flatID[i])==0){
					printf("\n\tWhich Month:\n\t\t[1]Jan;[2]Feb;[3]Mar;[4]April;\n\t\t[5]May;[6]June;[7]July;[8]Aug;\n\t\t[9]Sep;[10]Oct;[11]Nov;[12]Dec\n\n\t\t>> ");
					scanf("%d",&Choice);
					if(FlatID[i][Choice+1]==0){
						FlatID[i][Choice+1]=1;
						printf("\n\n\t\t\tPayment DONE!!\n");
					}
					else if(FlatID[i][Choice+1]==1) printf("\n\n\t\t\tPayed Already!!\n");
					break;
				}
			}
			break;
		case 3:
			printf("\n\tWhich Month:\n\t\t[1]Jan;[2]Feb;[3]Mar;[4]April;\n\t\t[5]May;[6]June;[7]July;[8]Aug;\n\t\t[9]Sep;[10]Oct;[11]Nov;[12]Dec\n\n\t\t>> ");
			scanf("%d",&Choice);
			for(i=0;i<=counterF;i++){
				if(FlatID[i][Choice+1]==1){
					Earning=Earning+FlatID[i][1];
				}
			printf("\n\n\t\t\tThis Month Earning: %d",Earning);
			}
			break;
		case 2:
			printf("\n\tWhich Flat [input from the list,(Case Sensitive!!)]: ");
			scanf("%s",editFlt);
			for(i=0;i<=counterF;i++){
				if(strcmp(editFlt,flatID[i])==0){
					for(j=2;j<=13;j++){
						if(FlatID[i][j]==1){
							paid=paid+FlatID[i][1];
						}
					}
					break;
				}
			}
			printf("\n\n\t\tTotal Payed by this Flat till now is: %d\n",paid);
	}
	for(i=0;i<=flNum;i++) sumFlat=sumFlat+flatEachFloor[i];
	i=-1;
	fp1=fopen(filename1,"w");
	while(1){
		i++;
		if(i>=sumFlat) break;
		if(i==flNum-1) fprintf(fp1,"%s %d %d %d %d %d %d %d %d %d %d %d %d %d",flatID[i],FlatID[i][1],FlatID[i][2],FlatID[i][3],FlatID[i][4],FlatID[i][5],FlatID[i][6],FlatID[i][7],FlatID[i][8],FlatID[i][9],FlatID[i][10],FlatID[i][11],FlatID[i][12],FlatID[i][13]);
		else fprintf(fp1,"%s %d %d %d %d %d %d %d %d %d %d %d %d %d\n",flatID[i],FlatID[i][1],FlatID[i][2],FlatID[i][3],FlatID[i][4],FlatID[i][5],FlatID[i][6],FlatID[i][7],FlatID[i][8],FlatID[i][9],FlatID[i][10],FlatID[i][11],FlatID[i][12],FlatID[i][13]);
	}
	fclose(fp1);
	Loading(300);
	system("cls");
goto XXX;



}



















