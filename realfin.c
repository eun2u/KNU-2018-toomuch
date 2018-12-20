
#include "lib.h"

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
			
			if(backgrd[i][j]==2)  //캐릭터
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

void blockmoving()
{
	int reblock_t, jgame2=1, input, cnt=1, time=0, time_c=0;
	//점프 동작이 끝나면 계속 0으로 초기화
	reblock_t=rand()%blocktime+blocktime-100; //첫 장애물
	while(jgame2)
	{
		if(kbhit())
		{
			input=get_ch();

						
			if(input==' ')
			{
				while(cnt<=6)
				{

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
						++score; 
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
					
					//conflict
					jgame2=gameover();
					if(jgame2==0)
						break;
					
					//create block
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
		
		// 기본 설정
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
void CheckScore()
{
	if((score%100)==0 && speed>20){
		speed-=5;
		blocktime-=20;
	}
	if((score%100)==0 && speed<=10)
		speed--;
}


