#include<iostream>
#include<graphics.h>
#include<conio.h>
#include <math.h>
#include<time.h>
#include<fstream>
#include "score.cpp"
#include "shooter.h"
using namespace std;

//OVERLOADING OF FUNCTION out()
//it will display text on the graphics screen such as GAME_NAME, HIGH_SCORE, CURRENT_SCORE, or any other text.
void out(int,int,const char[]);			//it will display char array on the graphics screen
void out(int,int,int);					//it will display integer on the graphic screen

/*It will take integer(to be converted to string), char array(to which the string is copied), and integer(length of char array which it will take in argument)
 and return a pointer to char*/
char *int_to_string(int,char[],int);	//convert intger value into array of char

//It will take the coordinate of the two points and return the floor value of the distance between these points
int dist1(int x1,int y1,int x2,int y2);//calculate the distance between to point

//score class for taking care of life, current_score, high_score
int vel=0;



bool game_over();									//it will over the played game if we miss three target
bool game_over(int,int,int,int,int);				//it will over the played game if the shooter machine hit by rainfall of objects
void check(char,shooter&,const circles&);			//checking the wether pressed key have any type of role in our program
void fall(int&,bullfall[],int&,int&,int&,int&);
void mainwindow(int);
void speed(int &);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void enter_name();
																			//main function
int main(){

    srand(time(NULL));										//use to create random pattern of output of rand() function every time
    initwindow(700,640);									//it will open a graphics screen to play game
    int flag=0;

start:                                                       //start label used for goto()function
    mainwindow(flag);
    life_count.enter_name();
    settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);				//it will set the text ingrident which is displayed on graphics screen
    life_count.reset();										//life =3,current score =0
    int game_status=0;										//to play again,quit
    char key_stroke;										//key pressed while playing
    int y_coordinate_bullfall=4;							//y_coordinate of all object of type bullfall(rainfall)
    shooter machine(189,611,50,75,77,'z','x');				//an shooter machine is created
    bullfall rainfall[3];									//three objects are formed to drop from the above on shoter
    int no_of_rainfall=rand()%3+1;							//how many objects are droped
    int t1=rand()%500;
    int t2=-50,t3=-50;
    circles target(rand()%400+50,rand()%300+50,50,1);
    int vel=0;
    if(no_of_rainfall==2){
            t2=rand()%500;
    }
    if(no_of_rainfall==3){
            t2=rand()%500;
            t3=rand()%500;
        }

    while(1){cout<<vel;speed(vel);
        life_count.display_life();
        if(game_status==1)break;
        if(game_over()==0||game_over(t1,t2,t3,y_coordinate_bullfall,machine.get_x_coordinate())==0){
			getch();
			key_stroke=getch();
            if(key_stroke=='r')game_status=1;
			else
            if(key_stroke==27)goto end;
            continue;
        }
        fall(y_coordinate_bullfall,rainfall,t1,t2,t3,no_of_rainfall);

        life_count.display();												//it will display high_score,current_score,and name of the game
		bullfall(500,0).draw(2,640);										//it will draw separation line on the screen
		machine.draw();                            							//it will display shooter machine

		if(target.get_radius()>0)target.draw(8);							//it will display circle until its radius become zero
        else target.set_circle(rand()%400+50,rand()%300+50,50);				//if radius become zero it will reset circle again

        if(kbhit()){														//check wether a key is press or not
			key_stroke = getch();											//update key_stroke to latest pressed key
			if(key_stroke=='r')break;
			if(key_stroke==27)goto end;										//RESTART THE GAME
			check(key_stroke,machine,target);								//check which key is pressed and then directe program action according the pressed key
        }else{
			target--;														//reduces the size of target (i.e. circle)
			delay(50);														//give delay of 50ms
			cleardevice();													//clear whole screen
         }flag=1;

    }//end while
    goto start;														//if program reaches here then it again go on start: (position)

    end:
	closegraph();
    return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char* int_to_string(int num,char a[],int n=10){
    char* aa=a;
    a=itoa(num,a,n);
    return aa;
}

void out(int x_cord,int y_cord,const char a[]){
    char aa[30];int i;
    for(i=0;a[i]!='\0';i++)
        aa[i]=a[i];
    aa[i] = '\0';
    outtextxy(x_cord,y_cord,aa);
}

void out(int x_cord,int y_cord,int num){
    char aa[10];
    char* a = int_to_string(num,aa);
    outtextxy(x_cord,y_cord,a);
}

int dist1(int x1,int y1,int x2,int y2){
    x1=x1-x2; y1=y1-y2; x1=x1*x1;y1=y1*y1;x1=x1+y1;
    int i= sqrt(x1);
    return i;
}

bool game_over(int t1,int t2,int t3,int u,int i){
        setcolor(RED);

        if(t1>=i && u>=611 && t1<=i+100){
                cleardevice();
                settextstyle(2,0,50);
                out(220,250,"Game Over");
                settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,5);
                out(150,470,"r:to try again bitch");
                life_count.display(1);
                cout<<"sd";
                char ch=getch();
                if(ch=='h')
                life_count.save_h_score();
                return 0;
            }
        else
        if(t2>=i && u>=611 && t2<=i+100){
                cleardevice();
                settextstyle(2,0,50);
                out(220,250,"Game Over");
                settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,5);
                out(150,470,"r:to try again bitch");
                life_count.display(1);
                cout<<"dss";
                 char ch=getch();
                if(ch=='h')
                life_count.save_h_score();
                return 0;
        }
        else
        if(t3>=i && u>=611 && t3<=i+100){
                cleardevice();
                settextstyle(2,0,50);
                out(220,250,"Game Over");
                settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,5);
                out(150,470,"r:to try again bitch");
                life_count.display(1);
                cout<<"sdd";
                 char ch=getch();
                if(ch=='h')
                life_count.save_h_score();
                return 0;
        }else
    return 1;
}

bool game_over(){
    if(life_count.get_life()<=0){
        life_count.save_h_score();
        setcolor(RED);
        settextstyle(2,0,50);
        out(220,250,"Game over");
        settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,5);
                out(150,470,"r:to try again bitch");
        life_count.display(1);
        return 0;
    }
    else return 1;
}

void check(char key_stroke,shooter& s,const circles& target){
    if(key_stroke=='p')cout<<s.get_x_coordinate()<<" "<<s.get_x_coordinate()<<endl;

	if(key_stroke==s.get_left_key())s--;			//move shooter left											prefix operator for moving machine
    if(key_stroke==s.get_right_key())s++;			//move shooter right										postfix operator for rotating angle of shooter
	if(key_stroke==s.get_s_left_key())--s;              //rotate shooter anti-clockwise
    if(key_stroke==s.get_s_right_key())++s;             //rotate shooter clockwise
	if(key_stroke==' '){										//for shooting lasers
		bullet b(s.get_x_coordinate(),s.get_y_coordinate(),s.get_h_coordinate(),3);
		b.draw(target);
	}
    cleardevice();
}
void fall(int &y_coordinate_bullfall,bullfall rainfall[],int &t1,int& t2,int& t3,int& no_of_rainfall){
    if(y_coordinate_bullfall<=640){
        y_coordinate_bullfall+=5;
        rainfall[0].set_coordinate(t1,y_coordinate_bullfall);
        rainfall[0].draw();
        rainfall[1].set_coordinate(t2,y_coordinate_bullfall);
        rainfall[1].draw();
        rainfall[2].set_coordinate(t3,y_coordinate_bullfall);
        rainfall[2].draw();
    }
    else{
        y_coordinate_bullfall=4;
        t1=rand()%500;
        no_of_rainfall=rand()%3+1;
        if(no_of_rainfall==3){
            t2=rand()%500;
            t3=rand()%500;
        }else
        if(no_of_rainfall==1){
            t2=-50;
            t3=-50;}
            else
            if(no_of_rainfall==2){
                t2=rand()%500;
                t3=-50;
            }
        }
}
void mainwindow(int flag){
    cleardevice();											//start window fix it
      for(int i=0;i<30;++i){
        if(i<5)setcolor(DARKGRAY);
        else if(i<10)setcolor(LIGHTGRAY);
        else if(i<15) setcolor(WHITE);
        else if(i<20)setcolor(WHITE);
        else if(i<25)setcolor(LIGHTGRAY);
        else setcolor(DARKGRAY);
        line(215-15*sin((i*3.14/30.0)),i+200,85+15*sin(i*3.14/30.0),i+400);
        if(flag==0){
            delay(100);
        }
    }
    setcolor(RED);
    settextstyle(2,0,50);
    out(30,300,"Ultimate Shooting Game");
    settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);
    setcolor(GREEN);
    out(200,450,"Press Space to Start Game");
    char ch=getch();
    while(1){
        if(ch==' '){cleardevice();
            settextstyle(10 ,HORIZ_DIR,5);
            setcolor(RED);
            out(220,160,"INSTRUCTIONS");
            setcolor(GREEN);
              settextstyle(10 ,HORIZ_DIR,2);
            out(220,250,"z: Rotate Anti-Clockwise");
            out(220,280,"x: Rotate Clockwise");
            out(220,310,"->: Move Right");
            out(220,340,"<-: Move Left");
            out(220,370,"Space: Shoot");
            setcolor(BLUE);
            out(200,450,"Press Space to Start Game");
            while(1){ch=getch();
                  if(ch==' '){cleardevice(); break;}
            }
            cleardevice();
            break;
        }else ch=getch();
    }
}
