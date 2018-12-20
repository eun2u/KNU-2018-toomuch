#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#define size_x 30
#define size_y 10
#define my_y 8 //내 위치
#define my_x 2
#define spdi 100 //속도 초기값
#define blki 501 //장애물 재로딩 초기값


int speed=spdi;
int score=0;


int blocktime=blki;
int backgrd[size_y][size_x];

void before_game();
void backbase();
void drawback();
void jump(int a);
void makeblock();
void blockmoving();
int gameover();
void CheckScore();
int after_game();
int kbhit();
int get_ch();


int main()
{
	int jgame=1;

	srand(time(NULL));

	before_game();
	while(jgame){

		blockmoving();
		jgame=after_game();
		score=0;
	}
	
	return 0;
}

void before_game()
{
	/*FILE *fp= fopen("rank.txt","a");
	char line[50];*/
	system("clear");

	printf("System Programming\n");	
	printf("\t\t2017113881 심의량\n");
	printf("\t\t2017111054 한은주\n");
	
	printf("\n\n\n=====================GAME START!=====================\n\n\n");

	sleep(3);

	
	backbase();
	system("clear");
	drawback();


} 


void backbase()
{
	int i,j;
	FILE *fp= fopen("rank.txt","a");
	char line[50];


	system("clear");
	printf("\n\n\t Write name!\n\t-> ");
	
	fscanf(stdin,"%s",line);
	fprintf(fp,"%s ",line);

	fclose(fp);
	sleep(3);


	for(i=0;i<size_y;i++){
		for(j=0;j<size_x;j++){
			if(i==9)
				backgrd[i][j]=1;
			else
				backgrd[i][j]=0;
		}
	}
	
	backgrd[my_y][my_x]=2;
}

void drawback()
{
	int i,j;

	printf(" Score : %d\n\n", score/2);
		
	printf(" ♩ ♭ ♪ ＃     ♩ ♭ ♪      ♬ ♩      ♪ ＃ ♬        ♭ ♪         ♬ ♩ ♭ ♪ ＃  \n");
	for(i=0;i<size_y;i++)
	{
		for(j=0;j<size_x-5;j++)
		{
			if(backgrd[i][j]==0)  //빈 공간
				printf("   ");
			
			if(backgrd[i][j]==1)  //테두리
				printf("___");
			
			if(backgrd[i][j]==2)  //주인공
				printf("☺  ");
			
			if(backgrd[i][j]==3)  //장애물
				printf("＊");
		}
	
		printf("\n");
	}



}

void jump(int cnt)
{
	int cnt_x,cnt_y;
	int i,j;

	for(i=0;i<size_y;i++){
		for(j=0;j<size_x;j++){
			if(backgrd[i][j]==2){

				cnt_x=j;
				cnt_y=i;
			}
		}
	}
	
	if(cnt<4){

		if(backgrd[cnt_y-1][cnt_x]==3)
			backgrd[cnt_y][cnt_x]=0;
		else{
			backgrd[cnt_y-1][cnt_x]=2;
			backgrd[cnt_y][cnt_x]=0;
			drawback();
		}
	}
	if(cnt>=4){

		if(backgrd[cnt_y+1][cnt_x]==3)
			backgrd[cnt_y][cnt_x]=0;
		else{
			backgrd[cnt_y][cnt_x]=0;
			backgrd[cnt_y+1][cnt_x]=2;
			drawback();
		}
	}
}
//장애물
void makeblock()
{
	int b;
	int blk[5][size_y-1];
	
	b=rand()%4;
	
	if(b==0)
	{
		blk[b][size_y-10]=0;
		blk[b][size_y-9]=0;
		blk[b][size_y-8]=0;
		blk[b][size_y-7]=0;
		blk[b][size_y-6]=0;
		blk[b][size_y-5]=0;
		blk[b][size_y-4]=0;
		blk[b][size_y-3]=0;
		blk[b][size_y-2]=3;
		for(int i=0;i<size_y-1;i++)
		{
			backgrd[i][size_x-1]=blk[b][i];
		}
	}
	if(b==1)
	{
		blk[b][size_y-10]=0;
		blk[b][size_y-9]=0;
		blk[b][size_y-8]=0;
		blk[b][size_y-7]=0;
		blk[b][size_y-6]=0;
		blk[b][size_y-5]=0;
		blk[b][size_y-4]=0;
		blk[b][size_y-3]=3;
		blk[b][size_y-2]=3;
		for(int i=0;i<size_y-1;i++)
		{
			backgrd[i][size_x-1]=blk[b][i];
		}
	}
	if(b==2)
	{
		blk[b][size_y-10]=0;
		blk[b][size_y-9]=0;
		blk[b][size_y-8]=0;
		blk[b][size_y-7]=0;
		blk[b][size_y-6]=0;
		blk[b][size_y-5]=0;
		blk[b][size_y-4]=0;
		blk[b][size_y-3]=3;
		blk[b][size_y-2]=0;
		for(int i=0;i<size_y-1;i++)
		{
			backgrd[i][size_x-1]=blk[b][i];
		}
	}
	if(b==3)
	{
		blk[b][size_y-10]=3;
		blk[b][size_y-9]=3;
		blk[b][size_y-8]=3;
		blk[b][size_y-7]=3;
		blk[b][size_y-6]=3;
		blk[b][size_y-5]=3;
		blk[b][size_y-4]=3;
		blk[b][size_y-3]=0;
		blk[b][size_y-2]=0;
		for(int i=0;i<size_y-1;i++)
		{
			backgrd[i][size_x-1]=blk[b][i];
		}
	}
}
//장애물 무빙
void blockmoving()
{
	int reblock_t/*장애물 재로딩 시간*/, jgame2=1, input, cnt=1, time=0, time_c=0;
	//점프할때 좀 더 매끄럽게 하기위해 점프 동작이 끝나면 계속 0으로 초기화
	reblock_t=rand()%blocktime+blocktime-100; //첫 장애물 생성	
	while(jgame2)
	{
		if(kbhit())
		{
			input=get_ch();

						
			if(input==' ')
			{
				while(cnt<=6)
				{
					//나
					if(cnt==1)
					{
						system("clear");
						jump(cnt);
						++cnt;
						usleep(300000);
					}
					if((time%25)==0 && cnt>1)
					{
						system("clear");
						jump(cnt);
						if(cnt==6)
							time=0;
						++cnt;
					}
					
					//장애물
					if((time%22)==0)
					{
						++score; //점수
						CheckScore();
						for(int i=0;i<size_y-1;i++){
							for(int j=0;j<size_x;j++){

								if(j!=0 && backgrd[i][j]!=2 &&(backgrd[i][j-1]!=2 || backgrd[i][j]==3))
								{
									backgrd[i][j-1]=backgrd[i][j];
									backgrd[i][j]=0;
								}
							}
						}
						system("clear");
						drawback();
						usleep(speed*1000);
					}
					
					//둘이 겹쳤을때
					jgame2=gameover();
					if(jgame2==0)
						break;
					
					//장애물 생성
					if((time_c%reblock_t)==0)
					{
						makeblock();
						system("clear");
						drawback();
						time_c=0; 
						reblock_t=rand()%blocktime+blocktime-100;
					}
					time++;
					time_c++;
				}
				cnt=1;
			}
		}
		
		
		//점프키를 안 눌렀을때
		if((time%22)==0)
		{	
			++score; 
			CheckScore();
			for(int i=0;i<size_y-1;i++){
				for(int j=0;j<size_x;j++){
					if(j!=0 && backgrd[i][j]!=2 && (backgrd[i][j-1]!=2||backgrd[i][j]==3) ){

							backgrd[i][j-1]=backgrd[i][j];
							backgrd[i][j]=0;
					}
				}
			}
			system("clear");
			drawback();
			usleep(speed*1000);
		}
		
		
		jgame2=gameover();
		
		
		if((time_c%reblock_t)==0)
		{
			makeblock();
			system("clear");;
		 	drawback();
			time_c=0;
			reblock_t=rand()%blocktime+blocktime-100;
		}
		time++;
		time_c++;
	}
	speed=spdi;
	blocktime=blki;

}
//장애물 맞았을때
int gameover()
{
	int i,j;

	for(i=0;i<size_y;i++){
		for(j=0;j<size_x;j++){
			if(backgrd[i][j]==2)
				return 1;
			
			if(i==size_y-1 && j==size_x-1 && backgrd[i][j]!=2){
				system("clear");
				drawback();
				return 0;
			}
		}
	}
}
//점수 몇점 이상 올라가면 스피드 조절 
void CheckScore()
{
	if((score%100)==0 && speed>20){
		speed-=5;
		blocktime-=20;
	}
	if((score%100)==0 && speed<=10)
		speed--;
}

int after_game()
{
	
	FILE* f=fopen("rank.txt","a");
	FILE* f2= fopen("rank.txt","r");
	int option;
	char name[50];
	int grade;

	system("clear");
	printf("\n==================Game over!!========================\n\n\n");

	printf("\t\t ▶  your score : %d\n\n",score/2);
	fprintf(f,"%d\n", score/2);

	fclose(f);

	printf("\t\t ※  HISTORY ※\n");
	

	while(!feof(f2)){
		fscanf(f2,"%s %d ",name,&grade);		
		fprintf(stdout,"\t\t%s %d\n",name,grade);	
	}
	
	
	printf("\n\n\n\t\t ▷  restart => press '1'");
	printf("\n\t\t ▷  exit    => press anything\n");
	
	fscanf(stdin,"%d", &option);
	if(option==1){

		system("clear");

		backbase();
		drawback();
		return 1;
	}
	else {
		system("clear");
		return 0;
	}
	
}


int kbhit()
{
   struct termios oldt, newt;
   int input;
   int oldf;

   tcgetattr(STDIN_FILENO, &oldt);
   newt = oldt;
   newt.c_lflag &= ~(ICANON | ECHO);
   tcsetattr(STDIN_FILENO, TCSANOW, &newt);
   oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
   fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

   input = getchar();

   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
   fcntl(STDIN_FILENO, F_SETFL, oldf);

   if(input != EOF){

     ungetc(input, stdin);
     return 1;
   }

   return 0;
}


int get_ch() {

   int ch; 
   struct termios old;
   struct termios new;
   tcgetattr(0, &old);
   new = old; 
   new.c_lflag &= ~(ICANON|ECHO); 
   new.c_cc[VMIN] = 1;
   new.c_cc[VTIME] = 0;
   tcsetattr(0, TCSAFLUSH, &new);
   ch = getchar(); 
   tcsetattr(0, TCSAFLUSH, &old);

   return ch; 
}

