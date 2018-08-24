#include<iostream>
#include<graphics.h>
#include<conio.h>
#include <math.h>
#include<time.h>
#include<fstream>
using namespace std;

#define HEIGHT 			640
#define LENGTH          500
#define TANK_LENGTH 	100
#define TANK_HEIGHT 	28

//OVERLOADING OF FUNCTION print_at_x_y()
//it will display text on the graphics screen such as GAME_NAME, HIGH_SCORE, CURRENT_SCORE, or any other text.
void print_at_x_y(int,int,const char[]);					//it will display char array on the graphics screen
void print_at_x_y(int,int,int);								//it will display integer on the graphic screen

/*It will take integer(to be converted to string), char array(to which the string is copied), and integer(length of char array which it will take in argument)
 and return a pointer to char*/
char *int_to_string(int,char[],int);						//convert intger value into array of char return a pointer to char

//It will take the coordinate of the two points and return the floor value of the distance between these points
int distance(int x1,int y1,int x2,int y2);					//calculate the distance between to point

//score class for taking care of life, current_score, high_score
class Game_Status{
public:
    Game_Status();											//constructor
    int get_life() const;									//return life
    void reduce_life();										//set the value of life
    int get_score()const;									//return current score
    void update_c_score();									//update_c_score current score
    void display();											//display all the required ingrident during play
    void reset();											//reset life and current score to its default value.
    void display(int i);									//display current score after GAME OVER
    void display_life();              						//display no. of lifes
    void save_h_score();									//save the high score to a file using file handling
    void enter_name();										//ask for name to user before staring the game if user denied then a default name is save
    void sort_score();										//sort the all 5 high score in decending order
	void reduce_health();									// reduce the health of the tank by one
	bool check_health()const;								//if health is zero(0) than return false else return true
	short get_health()const;								//return the how much health of tank is left
private:
	short health;											//store the health of tank health is reduce by falling objects
    int life;												//it store how many circle we are allowed to skip while shooting them
	int current_score;										//current score of user on every target shoots current score is increases
    struct high{											//structure to store the name and score of user
		char user_name[7];									// name of the user
        int s;												//score of the user
        high(){												//consturctor of class high
            strcpy(user_name,"No_one");						//copy one string to another and default name is "No_one" in case user not give his/her name
            s=0;											// default score is zero
        }
    }high_score[6];											//an array of objects of class high
}life_count;												//it will create a global variable of type class score

//class for rainfall the deadly objects
class bullfall{
public:
    bullfall(int ii=0,int jj=0);         					//constructor
    void draw(int i=14,int j=10);							//to create rainfall objects on the screen
    void set_coordinate(int ii,int jj);						//to reset the position of objects
    int get_x_coordinate()const;							//return x-coordinate
	int get_y_coordinate()const;							//return y-coordinate
	~bullfall(){}											//destructor
protected:
    int x,y;												//coordinate from which the bullet start falling
};//end bullfall

/*	Class to drop objects from above which will harm the tank and lower is health
	we can drop any number of objects from above by specifing the number(declared in class Rainfall)
	we can also set the speed of object which are falling by this we can set difficulty level of the game
	as falling objects hit the tank the health of the tank reduce by a default number
*/

class Tank:public bullfall{
public:
    Tank(int,int,int,char,char,char,char,char);   		//constructor of Tank class
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

};//end Tank

/*for making any kind of circle like :
	-> Target which is being shooted
	-> Bullets fired by tank
It is a derived class of bullfall because circle also have x and y coordinate along with radius
*/
class circles:public bullfall{
public:
    circles(int ii=50,int jj=50,int kk=50,int decay_rate=0);	//constructor
    void draw(int i);											//create a circle on screen at (x,y) point of radius r
    void setdecayrate(int);										//change the decayrate to a specific value
    int get_radius()const;										//return radius of a circle
    void set_radius(int);										//change the radius of a circle
    void operator--(int);										//to reduce the radius of circle by decayrate
	void set_circle(int,int,int);								//set the coordinate and radius of center
    ~circles();													//destructor when it run it reset the radius of a circle to zero
private:
    int r;														//centre of circle: (x,y); radius = r;
    int decayrate;												//rate at which radius of target decreases
};//end circles

//	derived class of class circles
//	resposible for shooting the bullets
class bullet:protected circles{
public:
    bullet(int,int,int,int);									//constructor
    void draw(const circles&);									//it will shoot bullet in a direction of shooter by making circles
	int get_x_h_coordinate()const;								//return the x coordinate from which the bullet is shooting
private:
     int x_h;                                  					//x-coordinate of shooter angle i.e the point from which the bullets fired
};

class Rainfall{
public:
	Rainfall(int);													//constructor
//this functoin change the coordinate of the falling object and reset there coordinate when they hit an object or reaches at the end of the screen.
	void fall(const Tank&);
	friend bool fall_hit_shooter(const bullfall&,const Tank&);	//Check wether falling objects hit the tank or not
	void draw();													//Draw objects : by making vertical line of a default length at it (x,y) point
private:
	short number;													//number of objects which are falling
	short speed;													//object's falling speed
	bullfall *b;													//object like b[0] or b[1]
};//end Rainfall


bool game_over();												//it will over the played game if the tank hit by rainfall of objects
void check(char,Tank&,const circles&);						//check the function of pressed key then perform the same action else do nothing
void mainwindow(int);											//display the screen before actual game started like name of the game, instruction etc;
bool fall_hit_shooter(const bullfall&,const Tank&);			//check wether falling object hit the tank

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																			//main function
int main(){
    srand(time(NULL));											//use to create random pattern of output of rand() function every time
    initwindow(700,HEIGHT);										//it will open a graphics screen to play game
    bool flag=0;												//check wether we choose try again or not
start:                                                     		//start label used for goto()function
    mainwindow(flag);											//display the game screen before game play like name and instructions
    life_count.enter_name();									//asking for user name
    settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);					//it will set the font and size of the text which is being displayed on graphics screen
    life_count.reset();											// reset life =3,current score =0 and health 5;
    bool restart=0;												//to play again,quit
    char key_stroke;											//store which key is pressed during game play
    Tank tank(189,611,50,75,77,'z','x',' ');				//tank is created with its initialization like position and key to perform action
    circles target(rand()%400+50,rand()%300+50,50,1);			//a circle of radius 50 is created at random position which reduce with 1 unit every time
    Rainfall rain(5);											//number of falling object created

/*		Actual Game start from here i.e.
	From now tank, target object, falling object, score, etc are displayed
	The whole screen is displayed at an instant and at the next instant whole screen is cleared and at next instant the whole screen is displayed with
	new position of the objects and new values of score, In case if any of these doesn't changes then these displayed at there previous position.
*/
	while(1){

        if(restart)break;										//to RESTART the game,if restart is true then the game will RESTART
		if(game_over()==0){										//check wether game is over or not
			key_stroke=getch();
            if(	key_stroke=='r'	||	key_stroke=='R'	)			//Check if user wants to restart the game after game over
				restart=true;									//if he wants to RESTART then restart became true
			else if(key_stroke==27)								//if user wants to quit then user must have to press esc key
				goto end;
            continue;											//after game over below code never run and infinite loop created until 'r','esc' pressed
        }
/*
	Make a separation line to separate game play screen to the screen which showing the name of the game, high score and current score
*/
		bullfall(500,0).draw(2,HEIGHT);								//it will first call constructor and then call its draw function
        life_count.display();										//it will display name of the game, high_score,current_score and remaining life
        rain.draw();												//it will show the falling objects
		tank.draw();                            					//it will display tank

		rain.fall(tank);

		if(target.get_radius()>0)target.draw(8);					//it will display circle until its radius become zero
        else target.set_circle(rand()%400+50,rand()%300+50,50);		//if radius become zero it will reset circle again

        if(kbhit()){												//check wether a key is press or not
			key_stroke = getch();									//update key_stroke to latest pressed key
			if(key_stroke=='r'||key_stroke=='R')break;				//if true then we ancounter with 'goto start' and our game again restart
			if(key_stroke==27)goto end;								//QUIT the game
			check(key_stroke,tank,target);						//check which key is pressed and then direct program action according the pressed key
        }else{
  			target--;												//reduces the size of target (i.e. circle) by unit
			delay(50);												//give delay of 50ms so that the radius of circle reduce after every 50ms
			cleardevice();											//clear whole screen so that we can print new stuffs
         }flag=1;

    }//end while
    goto start;														//if program reaches here then it again go on start: (position)
end:																//used for goto keyword
	closegraph();													//close the graphics screen
    return 0;
}//end main

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																										//functions defination which no belong to any class
char* int_to_string(int num,char a[],int n=10){
    char* aa=a;
    a=itoa(num,a,n);
    return aa;
}

void print_at_x_y(int x_cord,int y_cord,const char a[]){
    char aa[30];int i;
    for(i=0;a[i]!='\0';i++)
        aa[i]=a[i];
    aa[i] = '\0';
    outtextxy(x_cord,y_cord,aa);
}

void print_at_x_y(int x_cord,int y_cord,int num){
    char aa[10];
    char* a = int_to_string(num,aa);
    outtextxy(x_cord,y_cord,a);
}

int distance(int x1,int y1,int x2,int y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

bool game_over(){
    setcolor(RED);
	if(!life_count.check_health()||life_count.get_life()<=0){
		life_count.save_h_score();
		cleardevice();
		settextstyle(2,0,50);
		print_at_x_y(220,250,"Game Over");
		settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,5);
		print_at_x_y(150,470,"r:to try again");
		life_count.display(1);
		return 0;
	}
    return 1;
}

void check(char key_stroke,Tank& s,const circles& target){
    if(key_stroke=='p')cout<<s.get_x_coordinate()<<" "<<s.get_x_coordinate()<<endl;

	if(key_stroke==s.get_left_key())s--;			//move tank left											prefix operator for moving tank
    if(key_stroke==s.get_right_key())s++;			//move tank right										postfix operator for rotating angle of shooter
	if(key_stroke==s.get_s_left_key())--s;              //rotate shooter anti-clockwise
    if(key_stroke==s.get_s_right_key())++s;             //rotate shooter clockwise
	if(key_stroke==s.get_s_shoot_key()){										//for shooting lasers
		bullet b(s.get_x_coordinate(),s.get_y_coordinate(),s.get_h_coordinate(),3);
		b.draw(target);
	}
    cleardevice();
}

void mainwindow(int flag){
    cleardevice();											//start window fix it
      for(int i=0;i<30;++i){
        if(i<10)setcolor(RED);
        else if(i<20)setcolor(WHITE);
        else setcolor(GREEN);
        line(215-15*sin((i*3.14/30.0)),i+200,85+15*sin(i*3.14/30.0),i+400);
        if(flag==0){
//            delay(100);
        }
    }
    do{
        setcolor(RED);
        settextstyle(2,0,50);
        print_at_x_y(30,300,"Ultimate Shooting Game");
        settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);
        setcolor(GREEN);
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

bool fall_hit_shooter(const bullfall& b,const Tank& t){
	if(b.get_x_coordinate()>=t.get_x_coordinate()&&b.get_x_coordinate()<=t.get_x_coordinate()+TANK_LENGTH&&b.get_y_coordinate()>=t.get_y_coordinate()-3){
		life_count.reduce_health();
		return true;
	}
	return false;
}

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																											//class score member functions defination
Game_Status::Game_Status():life(3),current_score(0),health(7){
	FILE* file;
	file=fopen("save","r");
	if(file==NULL){
		file = fopen("save","w");
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
inline void Game_Status::update_c_score(){current_score+=5;}
void Game_Status::reset(){life=3,current_score=0;health = 7;}
void Game_Status::reduce_health(){
	health--;
}

bool Game_Status::check_health()const{
	return health<=0?false:true;
}

short Game_Status::get_health()const{
    return health;
}

void Game_Status::display(int i){
    setcolor(RED);
    print_at_x_y(330,350,current_score);
}
void Game_Status::display(){
    setcolor(YELLOW);
    print_at_x_y(599-40,60,"ULTIMATE");
    print_at_x_y(599-40,80,"SHOOTING");
    print_at_x_y(599-40,100,"CHALLENGE");
    print_at_x_y(599-40,190,"HIGH SCORE");
	print_at_x_y(599-20,220,high_score[0].s);
    print_at_x_y(599-40,289-32+60,"Current score");
    print_at_x_y(10,10,current_score);									//display current score on left top
    print_at_x_y(599,289+60,current_score);
	display_life();
}
void Game_Status::display_life(){
    setcolor(GREEN);
    switch(life_count.get_life()){
		case 3:line(629,429,629,478);
		case 2:line(599,429,599,478);
		case 1:line(569,429,569,478);
	}
}
/////////////////////new
void Game_Status::enter_name(){
    cleardevice();
	setcolor(WHITE);
    print_at_x_y(100,50,"enter name");
    int i=0;
    char c=getch();
    high_score[5].user_name[i]=c; i++;
    while(1){
        c=getch();
        if(c==13) return;
        high_score[5].user_name[i]=c; i++;
        print_at_x_y(100,100,high_score[5].user_name);
    }

}

////////////////////////
void Game_Status::save_h_score(){
    if(current_score>high_score[4].s){
        high_score[4].s = current_score;
        high_score[4]=high_score[5];
        life_count.sort_score();
    }
    for(int ii=0;ii<5;ii++){
        cout<<high_score[ii].user_name<<" "<<high_score[ii].s<<" "<<endl;
    }

	FILE* file = fopen("save","w");
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
																											//class Tank member functions defination
inline Tank::Tank(int ii,int jj,int xx,char left,char right,char s_left,char s_right,char _shoot):bullfall(ii,jj),h(xx){
	set_keys(left,right);
	set_s_keys(s_left,s_right,_shoot);
}
char Tank::get_left_key()const{return left_key;}
char Tank::get_right_key()const{return right_key;}
char Tank::get_s_left_key()const{return s_left_key;}
char Tank::get_s_right_key()const{return s_right_key;}
char Tank::get_s_shoot_key()const{return shoot_key;}
int Tank::get_h_coordinate()const{return h;}
inline void Tank::draw(){
	setcolor(RED);
	for(int i=1;i<life_count.get_health()*4;i++)
        line(x+1,y+TANK_HEIGHT-i,x+TANK_LENGTH-1,y+TANK_HEIGHT-i);
    setcolor(YELLOW);								//set color of tank
    line_styles(SOLID_LINE);                       	//making line solid
    line(x, y, x+TANK_LENGTH, y);                             	//upper line of tank
    line(x, y, x, y+TANK_HEIGHT);                              	//left line
    line(x, y+TANK_HEIGHT, x+TANK_LENGTH, y+TANK_HEIGHT);                       	//bottom line
    line(x+TANK_LENGTH, y, x+TANK_LENGTH, y+TANK_HEIGHT);                      	//right line
	line(x+TANK_LENGTH/2, y+TANK_HEIGHT, x+h, y-1);                           	//shooter's line
}

inline void Tank::set_keys(char left,char right){
	left_key=left;
	right_key=right;
}

inline void Tank::set_s_keys(char left,char right,char _shoot){
	s_left_key=left;
	s_right_key=right;
	shoot_key = _shoot;
}

inline void Tank::operator--(int){
    int n=10;														//how much tank shifted left by a single key stroke
	if(x-n>=1)x=x-n;
}

inline void Tank::operator++(int){
    int n=10;														//how much tank shifted right by a single key stroke
	if(x+n<=LENGTH-TANK_LENGTH-1)x=x+n;
}

inline void Tank::operator--(){
    int n=5;														//how much shooter rotate counter-clockwise by a single key stoke
	if(h-n>=0)h=h-n;
}

inline void Tank::operator++(){
    int n=5;														//how much shooter rotate clockwise by a single key stoke
	if(h+n<=TANK_LENGTH)h=h+n;
}

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																											//class circles member functions defination
circles::circles(int ii,int jj,int kk,int decay_rate):bullfall(ii,jj),r(kk){decayrate=decay_rate;}	//constructor

//draw a circle of desired colour and radius at desired location
inline void circles::draw(int i){
	setcolor(i);
	circle(x,y,r);
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
																											//class bullfall member functions defination
inline bullfall::bullfall(int ii,int jj):x(ii),y(jj){}					//consturctor

//draw a vertical line of 'i' colour and of 'j' length at (x,y) point
inline void bullfall::draw(int i,int j){
    setcolor(i);
	line(x,y,x,y+j);
}

inline void bullfall::set_coordinate(int ii,int jj){
	x=ii;
	y=jj;
}

inline int bullfall::get_x_coordinate()const{return x;}

inline int bullfall::get_y_coordinate()const{return y;}

/**********************************************************************************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**********************************************************************************************************************************************************/
																												//class bullet member functions definations
bullet::bullet(int hh,int kk,int x_hh,int rr):circles(hh,kk,rr,0),x_h(x_hh){}	//constructor

inline int bullet::get_x_h_coordinate()const{return x_h;}

void bullet::draw(const circles& target){
    int hh=x,kk=y;//(x,y)
    while(y>0){
			/*first we calculate radius of the circle and distance between bullets current position and the centre of the circle
            let this distance be d. if d becomes less than radius of the circle then the bullet will lie inside circle
            hence the target has been hit.so life of the tank will decrease.
            */
        if(distance(x,y,target.get_x_coordinate(),target.get_y_coordinate())<=target.get_radius())
        {
            life_count.update_c_score();
            target.~circles();
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
																												//class Rainfall member functions defination
inline Rainfall::Rainfall(int _number):number(_number),speed(10){		//consturctor
	b=new bullfall[number];
	for(int i=0;i<number;i++){
		b[i].set_coordinate(rand()%500+1,rand()%HEIGHT-HEIGHT);
	}
}

void Rainfall::fall(const Tank& t){
	for(int i=0;i<number;i++){
		b[i].set_coordinate(b[i].get_x_coordinate(),b[i].get_y_coordinate()+speed);
//below condition check either falling objects hit tank or touches the floor
		if(b[i].get_y_coordinate()>HEIGHT||fall_hit_shooter(b[i],t)) b[i].set_coordinate(rand()%500+1,rand()%HEIGHT-HEIGHT);
	}
}

void Rainfall::draw(){
	for(int i=0;i<number;i++)
        b[i].draw(YELLOW);
}
