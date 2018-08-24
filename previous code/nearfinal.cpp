#include<iostream>
#include<graphics.h>
#include<conio.h>
#include <math.h>
#include<time.h>
#include<fstream>
using namespace std;

//OVERLOADING OF FUNCTION print_at_x_y()
//it will display text on the graphics screen such as GAME_NAME, HIGH_SCORE, CURRENT_SCORE, or any other text.
void print_at_x_y(int,int,const char[]);			//it will display char array on the graphics screen
void print_at_x_y(int,int,int);					//it will display integer on the graphic screen

/*It will take integer(to be converted to string), char array(to which the string is copied), and integer(length of char array which it will take in argument)
 and return a pointer to char*/
char *int_to_string(int,char[],int);	//convert intger value into array of char

//It will take the coordinate of the two points and return the floor value of the distance between these points
int distance(int x1,int y1,int x2,int y2);//calculate the distance between to point

//score class for taking care of life, current_score, high_score
double vel=1.1;
class Game_Status{
public:
    Game_Status();								//constructor
    int get_life() const;					//return life
    void set_life(int);						//set the value of life
    int get_score()const;					//return current score
    void update_c_score();							//update_c_score current score
    void display();							//display all the required ingrident during play
    void reset();							//reset life and current score to its default value.
    void display(int i);					//display current score after GAME OVER
    void display_life();              // display no. of lifes
    void save_h_score();
    void update_h_score();
    void enter_name();
    void sort_score();
	void reduce_health();
	void pro_health();
	bool check_health()const;
	short get_health()const;
	int curr_score(){return current_score;}
private:
	short health;
    int life,current_score;
    //char name[100];
    struct high{
		char user_name[100];
        int s;
        high(){
            user_name[0]='\0';
            s=0;
        }
    }high_score[6];
}life_count;								//it will create a global variable of type class score

//class for rainfall the deadly objects
class bullfall{
public:
    bullfall(int ii=0,int jj=0);         			//constructor               																//doubt
    void draw(int o,int i=14,int j=10);							//to create rainfall objects on the screen
    void set_coordinate(int ii,int jj);		//to reset the position of objects
    int get_x_coordinate()const;							//return x-coordinate
	int get_y_coordinate()const;							//return y-coordinate
	~bullfall(){}									//destructor
protected:
    int x,y;										//coordinate from which the bullet start falling
};

class shooter:public bullfall{
public:
    shooter(int,int,int,char,char,char,char,char);   	//constructor of shooter class
    void draw();									//display shooter on the screen
//    void set_coordinate(int,int);      			//for changing the position of shooter_ box & shooter    never use

	void set_keys(char,char);						//it will set movement key
	void set_s_keys(char,char,char); 					//it will set shooter key

	char get_left_key()const;               		//get left movement key
	char get_right_key()const;                  	//get right movement key

	char get_s_left_key()const;						//get left movement key of shooter
	char get_s_right_key()const;					//get right movement key of shooter
	char get_s_shoot_key()const;

//	int get_x_coordinate()const;					//return x coordinate of shooter machine
//	int get_y_coordinate()const;					//return y coordinate of shooter machine
	int get_h_coordinate()const;								//return h(x-coordinate) of shooter



//to move shooter machine use 		: postfix operator
//to change angel of shooter use 	: prefix operator
	void operator--(int);							//to move shooter machine left
	void operator++(int);							//to move shooter machine right
	void operator--();								//to rotate angle of shooter anti-clockwise
	void operator++();								//to rotate angel of shooter clockwise
private:
    int h;											//x and y are the left corner point of shooter_box and x is for changing angle for shooter
	char left_key,right_key;						//key to change the position of shooter
	char s_left_key,s_right_key;					//key to change the angle of shooter
	char shoot_key;

};

class Rainfall{
public:
	Rainfall(int);	//constructor
	void fall(const shooter&);
	friend bool fall_hit_shooter(const bullfall&,const shooter&);
	void draw();
private:
	short number;	//number of objects are falls
	short speed;
	bullfall *b;
	int o;
};

class circles:public bullfall{                   //for making any kind of circle
public:
    circles(int ii=50,int jj=50,int kk=50,int decay_rate=0);							//constructor
    void draw(int i);									//create a circle on screen
    void setdecayrate(int);							//change the decayrate to a specific value
    int get_radius()const;							//return radius of a circle
    void set_radius(int);							//change the radius of a circle
    void operator--(int);							//to reduce the radius of circle by decayrate
	void set_circle(int,int,int);
    ~circles();										//destructor when it run it reset the radius of a circle to zero
    void draw_rotator(int);
private:
    int r;											//centre of circle: (x,y); radius = r;
    int decayrate;									//rate at which radius of target decreases
};

//derived class of class circles
class bullet:protected circles{
public:
    bullet(int,int,int,int);						//constructor
    void draw(const circles& target,const circles& rot);						//it will shoot bullet in a direction of shooter by making circles
	int get_x_h_coordinate()const;
	~bullet(){};
private:
     int x_h;                                       //x-coordinate of shooter angle
};


bool game_over();				//it will over the played game if the shooter machine hit by rainfall of objects
void check(char,shooter&,const circles&,const circles& rot);			//checking the wether pressed key have any type of role in our program
void fall(int&,bullfall[],int&,int&,int&,int&);
void mainwindow(int);
void speed(int &);

bool fall_hit_shooter(const bullfall& b,const shooter& t){
	if(b.get_x_coordinate()>=t.get_x_coordinate()&&b.get_x_coordinate()<=t.get_x_coordinate()+100&&b.get_y_coordinate()>=t.get_y_coordinate()-3){
		life_count.reduce_health();
		return true;
	}
	return false;
}
void speed1(int &);
/////////////////////////////////////////////////////////////////////
class player{
    int number_laser;
    protected:
    int velocity;
    public:
    enum player_type{B,P};
    player_type type;
    player(int laser):number_laser(laser),velocity(5){type=B;}
    player* promote();
    virtual int increase_speed(){return velocity;}
    virtual int health_bar(){return 4;}

};
class pro_player:public player{
    int accerleration;
    public:
    pro_player():player(2){type=P;accerleration=7;};
    int increase_speed(){return accerleration+velocity;}
    int health_bar(){return 2;}
    void drop_spl_obj();
};
//player& player::promote(pro_player& pro){
   // player*p=new pro_player();
   // p=this;
    //player*p=static_cast<pro_player*>(this);
   // delete this;
  //  return p;
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int rotate_angle=0;
 player* p=new player(1);                                                                       //main function
int main(){

    srand(time(NULL));										//use to create random pattern of output of rand() function every time
    initwindow(700,640);									//it will open a graphics screen to play game
    int flag=0;

start:                                                       //start label used for goto()function
    mainwindow(flag);
    life_count.enter_name();
    settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);				//it will set the font and size of the text which is being displayed on graphics screen
    life_count.reset();										//life =3,current score =0
    int game_status=0;										//to play again,quit
    char key_stroke;										//key pressed while playing
    shooter machine(189,611,50,75,77,'z','x',' ');				//an shooter machine is created
    circles target(rand()%400+50,rand()%300+50,50,1);
    int vel=0;
    int t=0;
    int enable_pro=0;
    Rainfall rain(4);
    circles rot(0,0,0,0);
    pro_player pp;
    while(1){
        rotate_angle++;
        speed1(vel);
        life_count.display_life();

         if(life_count.curr_score()>=50){
           p=&pp;
           if(enable_pro==0){
           life_count.pro_health();cout<<life_count.get_life();
           enable_pro=1;
            }
        }
        if(game_status==1)break;
        if(game_over()==0){
            if(t==0){t=1;
            life_count.save_h_score();}
			getch();
			key_stroke=getch();
            if(key_stroke=='r')game_status=1;
			else
            if(key_stroke==27)goto end;
            continue;
        }
        rain.draw();
        rain.fall(machine);

        life_count.display();												//it will display high_score,current_score,and name of the game
        setcolor(GREEN);
		machine.draw();                            							//it will display shooter machine

		if(target.get_radius()>0){target.draw(WHITE);rot.draw_rotator(rotate_angle);}							//it will display circle until its radius become zero
        else {int temp1=rand()%400+50;int temp2=rand()%300+50;
                target.set_circle(temp1,temp2,50);
                rot.set_circle(temp1,temp2,14);
               }				//if radius become zero it will reset circle again

        if(kbhit()){														//check wether a key is press or not
			key_stroke = getch();											//update key_stroke to latest pressed key
			if(key_stroke=='r')break;
			if(key_stroke==27)goto end;										//RESTART THE GAME
			check(key_stroke,machine,target,rot);								//check which key is pressed and then directe program action according the pressed key
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
void speed1(int &vel){
    vel+=1.1;
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

void check(char key_stroke,shooter& s,const circles& target,const circles& rot){
    if(key_stroke=='p')cout<<s.get_x_coordinate()<<" "<<s.get_x_coordinate()<<endl;

	if(key_stroke==s.get_left_key())s--;			//move shooter left											prefix operator for moving machine
    if(key_stroke==s.get_right_key())s++;			//move shooter right										postfix operator for rotating angle of shooter
	if(key_stroke==s.get_s_left_key())--s;              //rotate shooter anti-clockwise
    if(key_stroke==s.get_s_right_key())++s;             //rotate shooter clockwise
	if(key_stroke==s.get_s_shoot_key()){										//for shooting lasers
		bullet b(s.get_x_coordinate(),s.get_y_coordinate(),s.get_h_coordinate(),3);
		b.draw(target,rot);
	}
    cleardevice();
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class score member function defination
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
	//strcpy(high_score[5].user_name , "No_one);
	high_score[5].s = 0;
};
inline int Game_Status::get_life() const{return life;}
inline void Game_Status::set_life(int n){life=n;}
inline int Game_Status::get_score()const{return current_score;}
inline void Game_Status::update_c_score(){current_score+=5;high_score[5].s=current_score;}
void Game_Status::reset(){life=3,current_score=0;vel=0;health = 7;high_score[5].user_name[0]='\0';p=new player(1);}
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
    setcolor(YELLOW);
    print_at_x_y(599-40,60,"ULTIMATE");
    print_at_x_y(599-40,80,"SHOOTING");
    print_at_x_y(599-40,100,"CHALLENGE");
    print_at_x_y(599-40,190,"HIGH SCORE");
	print_at_x_y(599-20,220,high_score[0].s);
    print_at_x_y(599-40,289-32+60,"Current score");
    print_at_x_y(10,10,current_score);									//display current score on left top
    print_at_x_y(599,289+60,current_score);
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
/////////////////////new
void Game_Status::enter_name(){
    cleardevice();
	setcolor(WHITE);
    print_at_x_y(100,50,"enter name");
    int i=0;
    char c=getch();
    high_score[5].user_name[i]=c;
    i++;
    while(1){
        c=getch();
        if(c==13) return;
        high_score[5].user_name[i]=c;i++;
        print_at_x_y(100,100,high_score[5].user_name);
    }
    high_score[5].user_name[i]='\0';

}

////////////////////////
void Game_Status::save_h_score(){
    if(current_score>high_score[4].s){
        high_score[4]=high_score[5];
        high_score[4].s = current_score;
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
void Game_Status::update_h_score(){
    high temp;
    if(current_score>high_score[0].s){
        high_score[0]=temp;
        high_score[0]=high_score[5];
        high_score[5]=temp;

    }
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class shooter member function defination
inline shooter::shooter(int ii,int jj,int xx,char left,char right,char s_left,char s_right,char _shoot):bullfall(ii,jj),h(xx){
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
	for(int i=1;i<life_count.get_health()*(p->health_bar());i++)
        line(x+1,y+28-i,x+99,y+28-i);
    setcolor(YELLOW);								//set color of shooter
    line_styles(SOLID_LINE);                       	//making line solid
    line(x,y,x+100,y);                             	//upper line of shooter
    line(x,y,x,y+28);                              	//left line
    line(x,y+28,x+100,y+28);                       	//bottom line
    line(x+100,y,x+100,y+28);                      	//right line
	line(x+45,y+28,x+h,y-19);                           	//shooter's line
	line(x+55,y+28,x+h,y-19);

}

void speed(int &vel){
    vel+=0.05;
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
void shooter::operator--(int){
    int n=10;
	if(x-n>=1)x=x-n-vel;
}
void shooter::operator++(int){
    int n=10;
	if(x+n<=399)x=x+n+vel;
}
void shooter::operator--(){
    int n=5;
	if(h-n>=0)h=h-n+vel;
}
void shooter::operator++(){
    int n=5;
	if(h+n<=100)h=h+n+vel;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class circles member function defination
circles::circles(int ii,int jj,int kk,int decay_rate):bullfall(ii,jj),r(kk){decayrate=decay_rate;}
void circles::draw(int i){
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
void circles::setdecayrate(int x){
	decayrate=x;
}
int circles::get_radius()const{return r;}
void circles::set_radius(int kk){r=kk;}
void circles::set_circle(int ii,int jj,int kk){
	set_radius(kk);
	set_coordinate(ii,jj);
}
void circles::operator--(int){
	r=r-decayrate-vel;
	if(r<=0){
		int n=life_count.get_life();
		life_count.set_life(--n);
	}
}
circles::~circles(){
    r=0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class bullfall members function defination
bullfall::bullfall(int ii,int jj):x(ii),y(jj){}
void bullfall::draw(int o,int i,int j){

    switch(p->type){
       case player::B: setcolor(i);break;
       case player::P:{ setcolor(LIGHTRED);}
    }
	line(x,y,x,y+j);
    line(x,y,x-j,y);
    line(x,y,x+j,y);

}
void bullfall::set_coordinate(int ii,int jj){
	x=ii;
	y=jj;
}
int bullfall::get_x_coordinate()const{return x;}
int bullfall::get_y_coordinate()const{return y;}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																												//class bullet members function definations
bullet::bullet(int hh,int kk,int x_hh,int rr):circles(hh,kk,rr,0),x_h(x_hh){}
int bullet::get_x_h_coordinate()const{return x_h;}
void bullet::draw(const circles& target,const circles& rot){
    int hh=x,kk=y;//(x,y)
    while(y>0){
			/*first we calculate radius of the circle and distance between bullets current position and the centre of the circle
            let this distance be d. if d becomes less than radius of the circle then the bullet will lie inside circle
            hence the target has been hit.so life of the shooter will decrease.
            */
        if(distance(x,y,rot.get_x_coordinate()+60*sin(0.05*rotate_angle),rot.get_y_coordinate()+60*cos(0.05*rotate_angle))<=rot.get_radius()||distance(x,y,rot.get_x_coordinate()+60*cos(0.05*rotate_angle),rot.get_y_coordinate()+60*sin(0.05*rotate_angle))<=rot.get_radius())
        {
           break;
        }
        if(distance(x,y,target.get_x_coordinate(),target.get_y_coordinate())<=target.get_radius())
        {
            life_count.update_c_score();
            life_count.update_h_score();
            target.~circles();
            rot.~circles();
            break;
        }

           //uses two point form y-y1=m*(x-x1) to aim the target where m=(y2-y1)/(x2-x1)
        x=(y-kk-28)*(50-x_h)/28+hh+50;
        (*this).circles::draw(9);                                                                    //doubt
        y-=15;
    }
    delay(30);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Rainfall::Rainfall(int _number):number(_number),speed(p->increase_speed()){
	b=new bullfall[number];
//	o=rand()%2+1;
	for(int i=0;i<number;i++){
		b[i].set_coordinate(rand()%500+1,rand()%640-640);

	}
}



void Rainfall::fall(const shooter& t){
	for(int i=0;i<number;i++){
		b[i].set_coordinate(b[i].get_x_coordinate(),b[i].get_y_coordinate()+p->increase_speed());
		if(b[i].get_y_coordinate()>640||fall_hit_shooter(b[i],t)) {
            b[i].set_coordinate(rand()%500+1,rand()%640-640);
		}
	}
}

void Rainfall::draw(){
    int o;
	for(int i=0;i<number;i++){

        b[i].draw(YELLOW);}
}
