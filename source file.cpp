#include<iostream>
#include<graphics.h>
#include<conio.h>
#include <math.h>
#include<time.h>
#include<fstream>
using namespace std;

#define HEIGHT 			640									//height of the play screen
#define LENGTH          500									//length of the play screen
#define TANK_LENGTH 	100									//length of the tank(shooter)
#define TANK_HEIGHT 	28									//height of the tank(shooter)

//OVERLOADING OF FUNCTION print_at_x_y()
//it will display text on the graphics screen such as GAME_NAME, HIGH_SCORE, CURRENT_SCORE, or any other text.
void print_at_x_y(int,int,const char[]);					//it will display char array on the graphics screen
void print_at_x_y(int,int,int);								//it will display integer on the graphic screen

/*It will take integer(to be converted to string), char array(to which the string is copied), and integer(length of char array which it will take in argument)
 and return a pointer to char*/
char *int_to_string(int,char[],int);						//convert integer value into array of char return a pointer to char

//It will take the coordinate of the two points and return the floor value of the distance between these points
int distance(int x1,int y1,int x2,int y2);					//calculate the distance between to point

//score class for taking care of life, current_score, high_score
class Game_Status{
public:
    Game_Status();											//constructor
    int get_life() const;									//return life
    void reduce_life();										//reduce the life by one unit
    int get_score()const;									//return current score
    void update_c_score();									//update_c_score current score
    void display();											//display all the required ingrident during play
    void reset();											//reset life and current score to its default value.
    void display(int i);									//display current score after GAME OVER
    void display_life();              						//display no. of life
    void save_h_score();									//save the high score to a file using file handling
    void enter_name();										//ask for name to user before staring the game if user denied then a default name is save
    void sort_score();										//sort the all 5 high score in decending order
	void reduce_health();									// reduce the health of the tank by one
	bool check_health()const;								//if health is zero(0) than return false else return true
	short get_health()const;								//return the how much health of tank is left
	void pro_health();										//update health by certain amount
	void display_high_score();
private:
	short health;											//store the health of tank health is reduce by falling objects
    int life;												//it store how many circle we are allowed to skip while shooting them
	int current_score;										//current score of user on every target shoots current score is increases
    struct high{											//structure to store the name and score of user
		char user_name[30];									// name of the user
        int s;												//score of the user
        high(){												//constructor of class high
            strcpy(user_name,"No_one");						//copy one string to another and default name is "No_one" in case user not give his/her name
            s=0;											// default score is zero
        }
    }high_score[6];											//an array of objects of class high
}life_count;

//class for maintaing x and y coordinate of whole the deadly objects
class x_y_coordinate{
public:
    x_y_coordinate(int ii=0,int jj=0);         				//constructor
    void draw(int i=14,int j=10);							//to create rainfall objects on the screen
    void set_coordinate(int ii,int jj);						//to reset the position of objects
    int get_x_coordinate()const;							//return x-coordinate
	int get_y_coordinate()const;							//return y-coordinate
	~x_y_coordinate(){}										//destructor
protected:
    int x,y;												//coordinate from which the bullet start falling
};//end x_y_coordinate

/*	Class to drop objects from above which will harm the tank and lower is health
	we can drop any number of objects from above by specifying the number(declared in class Rainfall)
	we can also set the speed of object which are falling by this we can set difficulty level of the game
	as falling objects hit the tank the health of the tank reduce by a default number
*/

class shooter:public x_y_coordinate{
public:
    shooter(int,int,int,char,char,char,char,char);   		//constructor of shooter class
    void draw();											//display tank on the screen

	void set_keys(char,char);								//it will set movement key
	void set_s_keys(char,char,char); 						//it will set shooter key

	char get_left_key()const;        			       		//get left movement key
	char get_right_key()const;                  			//get right movement key

	char get_s_left_key()const;								//get left movement key of shooter
	char get_s_right_key()const;							//get right movement key of shooter
	char get_s_shoot_key()const;

//	int get_x_coordinate()const;							//return x coordinate of tank
//	int get_y_coordinate()const;							//return y coordinate of tank
	int get_h_coordinate()const;							//return h(x-coordinate) of shooter



//to move tank use 		: postfix operator
//to change angle of shooter use 	: prefix operator
	void operator--(int);									//to move tank left
	void operator++(int);									//to move tank right
	void operator--();										//to rotate angle of shooter anti-clockwise
	void operator++();										//to rotate angel of shooter clockwise
private:
    int h;													//x and y are the left corner point of shooter_box and x is for changing angle for shooter
	char left_key,right_key;								//key to change the position of tank
	char s_left_key,s_right_key;							//key to change the angle of shooter
	char shoot_key;											//key to fire the bullet in a specific direction

};//end shooter

//class for making objects which fall from above
class Bullet_fall{
public:
	Bullet_fall(int);															//constructor
//this functoin change the coordinate of the falling object and reset there coordinate when they hit an object or reaches at the end of the screen.
	void fall(const shooter&);
	friend bool fall_hit_shooter(const x_y_coordinate&,const shooter&);			//Check whether falling objects hit the tank or not
	void draw();																//Draw objects : by making vertical line of a default length at it (x,y) point
private:
	short number;																//number of objects which are falling
	short speed;																//object's falling speed
	x_y_coordinate *b;															//object like b[0] or b[1]
};//end Bullet_fall


/*for making any kind of circle like :
	-> Target which is being shooted
	-> Bullets fired by tank
It is a derived class of x_y_coordinate because circle also have x and y coordinate along with radius
*/
class circles:public x_y_coordinate{
public:
    circles(int ii=50,int jj=50,int kk=50,int decay_rate=0);	//constructor
    void draw(int i);											//create a circle on screen at (x,y) point of radius r
    void setdecayrate(int);										//change the decayrate to a specific value
    int get_radius()const;										//return radius of a circle
    void set_radius(int);										//change the radius of a circle
    void operator--(int);										//to reduce the radius of circle by decayrate
	void set_circle(int,int,int);								//set the coordinate and radius of center
    void draw_rotator(int);										//draw rotating circle
	~circles();													//destructor when it run it reset the radius of a circle to zero
private:
    int r;														//centre of circle: (x,y); radius = r;
    int decayrate;												//rate at which radius of target decreases
};//end circles

//	derived class of class circles
//	resposible for shooting the bullets
class bullet:protected circles{
public:
    bullet(int,int,int,int);											//constructor
    void draw(const circles& target,const circles& rotating_circle);	//it will shoot bullet in a direction of shooter by making circles
	int get_x_h_coordinate()const;										//return the x coordinate from which the bullet is shooting
	~bullet(){}															//destructor
	private:
     int x_h;                                  							//x-coordinate of shooter angle i.e the point from which the bullets fired
};//end bullet

class player{
    int number_laser;                                                   //number of lasers player can shoot
    protected:
    int velocity;                                                       //velocity of falling bullets
    public:
    enum player_type{B,P};                                              //type of player beginner or pro
    player_type type;
    player(int laser):number_laser(laser),velocity(4){type=B;}          //constructor
    player* promote();                                                  //promote beginner to pro
    virtual int increase_speed(){return velocity;}                      //returns speed for beginner
    virtual int health_bar(){return 4;}                                 //health bar for beginner

};
class pro_player:public player{
    int accerleration;                                                  //falling bullets accelerate of beginner becomes pro
    public:
    pro_player():player(2){type=P;accerleration=5;};                    //constructor
    int increase_speed(){return accerleration+velocity;}                //return increased velocity
    int health_bar(){return 2;}                                         //increase health bar if beginner becomes pro
};

int rotate_angle=0;                                                     //rotate angle for rotating circles
player* p=new player(1);                                                //pointer p pointing to player class

bool game_over();														//it will over the played game if the tank hit by rainfall of objects
void check(char,shooter&,const circles&,const circles& rotating_circle);//check the function of pressed key then perform the same action else do nothing
void fall(int&,x_y_coordinate[],int&,int&,int&,int&);
void mainwindow(int);													//display the screen before actual game started like name of the game, instruction etc;



/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																									//main function

 int main(){
    srand(time(NULL));													//use to create random pattern of output of rand() function every time
    initwindow(700,HEIGHT);												//it will open a graphics screen to play game
    bool flag=0;														//check whether we choose try again or not
start:                                                     				//start label used for goto()function
    mainwindow(flag);													//display the game screen before game play like name and instructions
    life_count.reset();													// reset life =3,current score =0 and health 5;
    life_count.enter_name();											//asking for user name
    settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);							//it will set the font and size of the text which is being displayed on graphics screen
    bool restart=0;														//to play again,quit
    char key_stroke;													//store which key is pressed during game play
    shooter tank(189,611,50,75,77,'z','x',' ');							//tank is created with its initialization like position and key to perform action
    int initial_c_codinate_x=rand()%400+50; int initial_c_codinate_y=rand()%300+50;
    circles target(initial_c_codinate_x,initial_c_codinate_y,50,1);		//a circle of radius 50 is created at random position which reduce with 1 unit every time
    int t = 0;
	int enable_pro =0;
	short No_of_bullet_fall = 4;										//number of falling object created
	Bullet_fall rain(No_of_bullet_fall);
	circles rotating_circle(initial_c_codinate_x,initial_c_codinate_y,0,0);
	pro_player pp;

/*		Actual Game start from here i.e.
	From now tank, target object, falling object, score, etc are displayed
	The whole screen is displayed at an instant and at the next instant whole screen is cleared and at next instant the whole screen is displayed with
	new position of the objects and new values of score, In case if any of these doesn't changes then these displayed at there previous position.
*/
	while(1){
		rotate_angle=(rotate_angle+1)%360;                      		//rotating angle always less than 360 degree
		if(life_count.get_score()>=200){                        		//if this condition fullfills player becomes pro
			p = &pp;                                            		// p starts pointing to pro player
			if(enable_pro == 0){
				life_count.pro_health();
				enable_pro = 1;
			}
		}
        if(restart)break;												//to RESTART the game,if restart is true then the game will RESTART
		if(game_over()==0){												//check whether game is over or not
			if(t==0){
				t=1;
				life_count.save_h_score();
			}
			key_stroke=getch();
            if(	key_stroke=='r'	||	key_stroke=='R'	){					//Check if user wants to restart the game after game over
				restart=true;}											//if he wants to RESTART then restart became true
			else if(key_stroke==27){									//if user wants to quit then user must have to press esc key
				goto end;
            }
            else if(key_stroke=='h'){
                   cleardevice();
                   setcolor(GREEN);
                   life_count.display_high_score();
                   key_stroke=getch();
                }
                continue;												//after game over below code never run and infinite loop created until 'r','esc' pressed
        }
/*
	Make a separation line to separate game play screen to the screen which showing the name of the game, high score and current score
*/
		x_y_coordinate(500,0).draw(2,HEIGHT);							//it will first call constructor and then call its draw function

        life_count.display();											//it will display name of the game, high_score,current_score and remaining life
        life_count.display_life();                                 	 	//it will show no. of remaining life

        rain.draw();													//it will show the falling objects
		tank.draw();                            						//it will display tank

		rain.fall(tank);

		if(target.get_radius()>0){										//it will display circle until its radius become zero
			target.draw(WHITE);
			rotating_circle.draw_rotator(rotate_angle);
		}
		else{															//if radius become zero it will reset circle again
			int temp1 = rand()%400+50,temp2 = rand()%300+50;
			target.set_circle(temp1,temp2,50);
			rotating_circle.set_circle(temp1,temp2,14);
		}
		if(kbhit()){													//check whether a key is press or not
			key_stroke = getch();										//update key_stroke to latest pressed key
			if(key_stroke=='r'||key_stroke=='R')break;					//if true then we encounter with 'goto start' and our game again restart
			if(key_stroke==27)goto end;									//QUIT the game
			check(key_stroke,tank,target,rotating_circle);				//check which key is pressed and then direct program action according the pressed key
			if(key_stroke=='p'){
			    setcolor(GREEN);
			    settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,3);
                print_at_x_y(250,200,"To resume press p");
                print_at_x_y(250,400,"Press h: High score");
                char c=getch();
                if(c=='p'){
                    settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);
                    continue;
                }
                if(c=='h'){
                    cleardevice();
                    life_count.display_high_score();
                    c=getch();
                    if(c=='r') continue;
                }
			}
		}else{
  			target--;													//reduces the size of target (i.e. circle) by unit
			delay(50);													//give delay of 50ms so that the radius of circle reduce after every 50ms
			cleardevice();												//clear whole screen so that we can print new stuffs
         }flag=1;

    }//end while
    goto start;															//if program reaches here then it again go on start: (position)
end:																	//used for goto keyword
	closegraph();														//close the graphics screen
    return 0;
}//end main



/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/

char* int_to_string(int num,char a[],int n=10){
    char* aa=a;
    a=itoa(num,a,n);
    return aa;
}

void print_at_x_y(int x_cord,int y_cord,const char a[]){
    char aa[100];int i;
    for(i=0;a[i]!='\0';i++)
        aa[i]=a[i];
    aa[i] = '\0';
    outtextxy(x_cord,y_cord,aa);
}

void print_at_x_y(int x_cord,int y_cord,int num){
    char aa[100];
    char* a = int_to_string(num,aa);
    outtextxy(x_cord,y_cord,a);
}

int distance(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

bool game_over(){
    setcolor(RED);
	if(!life_count.check_health()||life_count.get_life()<=0){

		cleardevice();
		settextstyle(2,0,50);
		print_at_x_y(220,250,"Game Over");
		life_count.display(1);
		settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,3);
		print_at_x_y(220,470,"r: to try again");
		print_at_x_y(350,470,"h: High score");
		return 0;
	}
    return 1;
}

void check(char key_stroke,shooter& s,const circles& target,const circles& rotating_circle){

	if(key_stroke==s.get_left_key())s--;				//move shooter left											prefix operator for moving tank
    if(key_stroke==s.get_right_key())s++;				//move shooter right										postfix operator for rotating angle of shooter
	if(key_stroke==s.get_s_left_key())--s;              //rotate shooter anti-clockwise
    if(key_stroke==s.get_s_right_key())++s;             //rotate shooter clockwise
	if(key_stroke==s.get_s_shoot_key()){										//for shooting lasers
		bullet b(s.get_x_coordinate(),s.get_y_coordinate(),s.get_h_coordinate(),3);
		b.draw(target,rotating_circle);
	}
    cleardevice();
}

void mainwindow(int flag){
    cleardevice();										//clear whole window
      for(int i=0;i<30;++i){
        if(i<10)setcolor(LIGHTGRAY);
        else if(i<20)setcolor(WHITE);
        else setcolor(DARKGRAY);
        line(215-15*sin((i*3.14/30.0)),i+200,85+15*sin(i*3.14/30.0),i+400);
        if(flag==0){
  //         delay(100);
        }
    }
    do{
        setcolor(RED);
        settextstyle(2,0,50);
        print_at_x_y(30,300,"Ultimate Shooting Game");
        settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);
        setcolor(GREEN);
        print_at_x_y(200,450,"Press Space to Start Game");
    }
    while(getch()!=' ');
    do{
		cleardevice();
        settextstyle(10 ,HORIZ_DIR,5);
        setcolor(RED);
        print_at_x_y(220,160,"RULES");
        setcolor(GREEN);
        settextstyle(10 ,HORIZ_DIR,2);
        print_at_x_y(100,250,"1: Shoot decreasing circles.");
        print_at_x_y(100,280,"2: You have 3 life showing at right.");
        print_at_x_y(100,310,"3: protect yourself from falling objects.");
        print_at_x_y(100,340,"4: red bar on you represent your health.");
        setcolor(BLUE);
        print_at_x_y(200,450,"Press Space to Start Game");
    }while(getch()!=' ');
    do{
		cleardevice();
        settextstyle(10 ,HORIZ_DIR,5);
        setcolor(RED);
        print_at_x_y(220,160,"INSTRUCTIONS");
        setcolor(GREEN);
        settextstyle(10 ,HORIZ_DIR,2);
        print_at_x_y(220,250,"z: Rotate Anti-Clockwise");
        print_at_x_y(220,280,"x: Rotate Clockwise");
        print_at_x_y(220,310,"->: Move Right");
        print_at_x_y(220,340,"<-: Move Left");
        print_at_x_y(220,370,"Space: Shoot");
        setcolor(BLUE);
        print_at_x_y(200,450,"Press Space to Start Game");
    }while(getch()!=' ');

}

bool fall_hit_shooter(const x_y_coordinate& b,const shooter& t){
	if(b.get_x_coordinate()>=t.get_x_coordinate()&&b.get_x_coordinate()<=t.get_x_coordinate()+100&&b.get_y_coordinate()>=t.get_y_coordinate()-3){
		life_count.reduce_health();
		return true;
	}
	return false;
}

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																											//class score member function defination
Game_Status::Game_Status():life(3),current_score(0),health(7){
	FILE* file;
	file=fopen("High_score","r");
	if(file==NULL){
		file = fopen("High_score","w");
		for(int i=0;i<5;i++){
			strcpy(high_score[i].user_name,"No_one");
			high_score[i].s=0;
			fprintf(file,"%s \t %d \n",high_score[i].user_name,high_score[i].s);
		}
		fclose(file);
	}
	else{
		for(int i=0;i<5;i++)
			fscanf(file,"%s %d",high_score[i].user_name,&high_score[i].s);
		fclose(file);
	}
	strcpy(high_score[5].user_name , "No_one");
	high_score[5].s = 0;
};
inline int Game_Status::get_life() const{return life;}
inline void Game_Status::reduce_life(){life--;}
inline int Game_Status::get_score()const{return current_score;}
inline void Game_Status::update_c_score(){current_score+=5;high_score[5].s=current_score;}

void Game_Status::display_high_score(){
    settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);
        print_at_x_y(200,100,"High Score");
    for(int i=0;i<5;i++){
        print_at_x_y(200,200+i*30,life_count.high_score[i].user_name);
        print_at_x_y(350,200+i*30,life_count.high_score[i].s);
    }
    print_at_x_y(200,400,"Press r to Resume");
}
void Game_Status::reset(){
    life=3;
    current_score=0;
    health = 7;
    strcpy(high_score[5].user_name,"No_one");
    delete p;
    p=new player(1);
}

void Game_Status::reduce_health(){
	health--;
}

bool Game_Status::check_health()const{
	return health<=0?false:true;
}
void Game_Status::pro_health(){
    life_count.health=14;
}
short Game_Status::get_health()const{
    return health;
}

void Game_Status::display(int i){
    setcolor(RED);
    print_at_x_y(330,350,current_score);
}

void Game_Status::display(){
//	int max_size = (current_score>high_score[0].s) ? current_score : high_score[0].s;
    setcolor(YELLOW);
    print_at_x_y(599-40,60,"ULTIMATE");
    print_at_x_y(599-40,80,"SHOOTING");
    print_at_x_y(599-40,100,"CHALLENGE");
    print_at_x_y(599-40,190,"HIGH SCORE");
	print_at_x_y(599-20,220,(current_score>high_score[0].s)?current_score : high_score[0].s);
    print_at_x_y(599-40,289-32+60,"Current score");
    print_at_x_y(10,10,current_score);									//display current score on left top
    print_at_x_y(599,289+60,current_score);
    print_at_x_y(599-30,550,"p:Pause");
}
void Game_Status::display_life(){
    setcolor(GREEN);
    line(500,0,500,640);
    switch(life_count.get_life()){
		case 3:line(629,429,629,478);
		case 2:line(599,429,599,478);
		case 1:line(569,429,569,478);
	}
}

void Game_Status::enter_name(){
	setcolor(WHITE);
    int i=0;
    strcpy(high_score[5].user_name,"");
    while(1){
        char c;
		cleardevice();
		print_at_x_y(250,250,"Enter Name");
        print_at_x_y(250,300,high_score[5].user_name);
        c=getch();

        if(c==13) break;										//ascii value of return key(enter) : 13
        if(c==8){												//ascii value of backspace key : 8
            if(i!=0)
                high_score[5].user_name[--i]='\0';
        }
		else{
			high_score[5].user_name[i++]=c;
			high_score[5].user_name[i] = '\0';
		}
    }
    if(i==0)
        strcpy(high_score[5].user_name,"No_one");
}

void Game_Status::save_h_score(){
    if(current_score>high_score[4].s){
        high_score[4]=high_score[5];
        high_score[4].s = current_score;
        life_count.sort_score();
    }

	FILE* file = fopen("High_score","w");
	for(int i=0;i<5;i++)
		fprintf(file,"%s \t %d \n",high_score[i].user_name,high_score[i].s);
	fclose(file);
}

void Game_Status::sort_score(){
    Game_Status::high temp;
    for(int i=1;i<5;i++){
        temp=high_score[i];
        int j=i-1;
        while((temp.s>high_score[j].s)&&(j>=0)){
            high_score[j+1]=high_score[j];    //moves element forward
            j=j-1;
        }
        high_score[j+1]=temp;    //insert element in proper place
    }
}

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																											//class shooter member function defination
inline shooter::shooter(int ii,int jj,int xx,char left,char right,char s_left,char s_right,char _shoot):x_y_coordinate(ii,jj),h(xx){
	set_keys(left,right);
	set_s_keys(s_left,s_right,_shoot);
}
char shooter::get_left_key()const{return left_key;}
char shooter::get_right_key()const{return right_key;}
char shooter::get_s_left_key()const{return s_left_key;}
char shooter::get_s_right_key()const{return s_right_key;}
char shooter::get_s_shoot_key()const{return shoot_key;}
int shooter::get_h_coordinate()const{return h;}

inline void shooter::draw(){
    setcolor(RED);
	for(int i=1;i<life_count.get_health()*(p->health_bar());i+=4)
        line(x+1,y+TANK_HEIGHT-i,x+TANK_LENGTH-1,y+TANK_HEIGHT-i);
    setcolor(YELLOW);															//set color of tank
    line_styles(SOLID_LINE);                       								//making line solid
    line(x, y, x+TANK_LENGTH, y);                             					//upper line of tank
    line(x, y, x, y+TANK_HEIGHT);                              					//left line
    line(x, y+TANK_HEIGHT, x+TANK_LENGTH, y+TANK_HEIGHT);                      	//bottom line
    line(x+TANK_LENGTH, y, x+TANK_LENGTH, y+TANK_HEIGHT);                      	//right line
	line(x+TANK_LENGTH/2, y+TANK_HEIGHT, x+h, y-1);

}

void shooter::set_keys(char left,char right){
	left_key=left;
	right_key=right;
}
void shooter::set_s_keys(char left,char right,char _shoot){
	s_left_key=left;
	s_right_key=right;
	shoot_key = _shoot;
}

inline void shooter::operator--(int){
    int n=10;														//how much tank shifted left by a single key stroke
	if(x-n>=1)x=x-n;
}

inline void shooter::operator++(int){
    int n=10;														//how much tank shifted right by a single key stroke
	if(x+n<=LENGTH-TANK_LENGTH-1)x=x+n;
}

inline void shooter::operator--(){
    int n=5;														//how much shooter rotate counter-clockwise by a single key stoke
	if(h-n>=0)h=h-n;
}

inline void shooter::operator++(){
    int n=5;														//how much shooter rotate clockwise by a single key stoke
	if(h+n<=TANK_LENGTH)h=h+n;
}

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																											//class circles member function defination
circles::circles(int ii,int jj,int kk,int decay_rate):x_y_coordinate(ii,jj),r(kk){decayrate=decay_rate;}	//constructor

//draw a circle of desired colour and radius at desired location
inline void circles::draw(int i){
	setcolor(i);
	circle(x,y,r);

}

void circles::draw_rotator(int l){
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,BLUE);
    circle(x+(60*cos(l*0.05)),y+(60*sin(l*0.05)),10);
    floodfill(x+(60*cos(l*0.05)),y+(60*sin(l*0.05)),WHITE);
    setfillstyle(SOLID_FILL,BLUE);
    circle(x+(60*sin(l*0.05)),y+(60*cos(l*0.05)),10);
    floodfill(x+(60*sin(l*0.05)),y+(60*cos(l*0.05)),WHITE);

}

//by how much units circle's radius decreases
// for target we set to 1
// for bullets we set to 0
inline void circles::setdecayrate(int x){
	decayrate=x;
}

inline int circles::get_radius()const{return r;}

inline void circles::set_radius(int kk){r=kk;}

inline void circles::set_circle(int ii,int jj,int kk){
	set_radius(kk);
	set_coordinate(ii,jj);
}

void circles::operator--(int){
	r=r-decayrate;
	if(r<=0){												//if circle disappear without being hitted one life reduces
		life_count.reduce_life();
	}
}

circles::~circles(){
    r=0;
}

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																											//class x_y_coordinate member functions defination
inline x_y_coordinate::x_y_coordinate(int ii,int jj):x(ii),y(jj){}					//consturctor

//draw a vertical line of 'i' colour and of 'j' length at (x,y) point
inline void x_y_coordinate::draw(int i,int j){

    switch(p->type){
       case player::B: setcolor(i);break;
       case player::P:{ setcolor(LIGHTRED);}
    }
	line(x,y,x,y+j);
    line(x,y,x-j,y);
    line(x,y,x+j,y);

}

inline void x_y_coordinate::set_coordinate(int ii,int jj){
	x=ii;
	y=jj;
}

inline int x_y_coordinate::get_x_coordinate()const{return x;}

inline int x_y_coordinate::get_y_coordinate()const{return y;}

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																												//class bullet member functions definations
bullet::bullet(int hh,int kk,int x_hh,int rr):circles(hh,kk,rr,0),x_h(x_hh){}	//constructor

inline int bullet::get_x_h_coordinate()const{return x_h;}

void bullet::draw(const circles& target,const circles& rotating_circle){
    int hh=x,kk=y;//(x,y)
    while(y>0){

		if(distance(x,y,rotating_circle.get_x_coordinate()+60*sin(0.05*rotate_angle),rotating_circle.get_y_coordinate()+60*cos(0.05*rotate_angle))<=rotating_circle.get_radius()||distance(x,y,rotating_circle.get_x_coordinate()+60*cos(0.05*rotate_angle),rotating_circle.get_y_coordinate()+60*sin(0.05*rotate_angle))<=rotating_circle.get_radius())
        {
           break;
        }

			/*first we calculate radius of the circle and distance between bullets current position and the centre of the circle
            let this distance be d. if d becomes less than radius of the circle then the bullet will lie inside circle
            hence the target has been hit.so life of the tank will decrease.
            */
        if(distance(x,y,target.get_x_coordinate(),target.get_y_coordinate())<=target.get_radius())
        {
            life_count.update_c_score();
            target.~circles();
            rotating_circle.~circles();
            break;
        }
           //uses two point form y-y1=m*(x-x1) to aim the target where m=(y2-y1)/(x2-x1)
        x=(y-kk-TANK_HEIGHT)*(50-x_h)/TANK_HEIGHT+hh+50;
        (*this).circles::draw(9);                                                                    //doubt
        y-=15;
    }
    delay(30);
}

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																												//class Bullet_fall member functions defination
inline Bullet_fall::Bullet_fall(int _number):number(_number),speed(p->increase_speed()){		//consturctor
	b=new x_y_coordinate[number];
	for(int i=0;i<number;i++){
		b[i].set_coordinate(rand()%500+1,rand()%HEIGHT-HEIGHT);
	}
}

void Bullet_fall::fall(const shooter& t){
	for(int i=0;i<number;i++){
		b[i].set_coordinate(b[i].get_x_coordinate(),b[i].get_y_coordinate()+p->increase_speed());
//below condition check either falling objects hit tank or touches the floor
		if(b[i].get_y_coordinate()>HEIGHT||fall_hit_shooter(b[i],t))
			b[i].set_coordinate(rand()%500+1,rand()%HEIGHT-HEIGHT);
	}
}

void Bullet_fall::draw(){
	for(int i=0;i<number;i++)
        b[i].draw(YELLOW);
}
