#include<iostream>
#include<fstream>
#include<graphics.h>
#include<conio.h>
#include <math.h>
#include<string>
#include<time.h>
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
class score{
public:
    score();								//constructor
    int get_life() const;					//return life
    void set_life(int);						//set the value of life
    int get_score()const;					//return current score
    void update_c_score();					//update current score
	void update_h_score();
    void display();							//display all the required ingrident during play
    void reset();							//reset life and current score to its default value.
    void display(int i);					//display current score after GAME OVER
private:
    int life,current_score,high_score;

}life_count;								//it will create a global variable of type class score

//class for rainfall the deadly objects
class bullfall{
public:
    bullfall(int ii=0,int jj=0);         			//constructor               																//doubt
    virtual void draw(int i=14,int j=10);							//to create rainfall objects on the screen
    virtual void set_coordinate(int ii,int jj);		//to reset the position of objects
    int get_x_coordinate()const;							//return x-coordinate
	int get_y_coordinate()const;							//return y-coordinate
	~bullfall(){}									//destructor
protected:
    int x,y;										//coordinate from which the bullet start falling
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
private:
    int r;											//centre of circle: (x,y); radius = r;
    int decayrate;									//rate at which radius of target decreases
};

//derived class of class circles
class bullet:protected circles{
public:
    bullet(int,int,int,int);						//constructor
    void draw(const circles&);						//it will shoot bullet in a direction of shooter by making circles
	void check(const circles&);
	int get_x_h_coordinate()const;
private:
     int x_h;                                       //x-coordinate of shooter angle
};

class shooter:public bullfall{
public:
    shooter(int,int,int,char,char,char,char,char);   	//constructor of shooter class
    void draw();									//display shooter on the screen
//    void set_coordinate(int,int);      				//for changing the position of shooter_ box & shooter    never use

	void set_keys(char,char);						//it will set movement key
	void set_s_keys(char,char); 					//it will set shooter key

/*	char get_left_key()const;               		//get left movement key
	char get_right_key()const;                  	//get right movement key

	char get_s_left_key()const;						//get left movement key of shooter
	char get_s_right_key()const;					//get right movement key of shooter
*/
//	int get_x_coordinate()const;					//return x coordinate of shooter machine
//	int get_y_coordinate()const;					//return y coordinate of shooter machine
	int get_h_coordinate()const;								//return h(x-coordinate) of shooter
	void shoot(){
		ob.draw();
//to move shooter machine use 		: postfix operator
//to change angel of shooter use 	: prefix operator
	void operator--(int);							//to move shooter machine left
	void operator++(int);							//to move shooter machine right
	void operator--();								//to rotate angle of shooter anti-clockwise
	void operator++();								//to rotate angel of shooter clockwise
private:
    int h;											//x and y are the left corner point of shooter_box and h is for changing angle for shooter
	char left_key,right_key;						//key to change the position of shooter
	char s_left_key,s_right_key;					//key to change the angle of shooter
	char shoot_key;
	bullet ob(x,y,h);
};


bool game_over();									//it will over the played game if we miss three target
bool game_over(int,int,int,int,int);				//it will over the played game if the shooter machine hit by rainfall of objects
void check(char,shooter&,const circles&);			//checking the wether pressed key have any type of role in our program

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																							//main function
int main(){

    srand(time(NULL));										//use to create random pattern of output of rand() function every time
    initwindow(700,640);									//it will open a graphics screen to play game
start:														//start label used for goto()function
    settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);				//it will set the text ingrident which is displayed on graphics screen
    life_count.reset();										//life =3,current score =0
    int game_status=0;										//to play again,quit
    char key_stroke;										//key pressed while playing
    int y_coordinate_bullfall=4;							//y_coordinate of all object of type bullfall(rainfall)
    shooter machine(189,611,50,75,77,'z','x',' ');				//an shooter machine is created
    bullfall rainfall[3];									//three objects are formed to drop from the above on shoter
    int no_of_rainfall=rand()%3+1;							//how many objects are droped
    int t1=rand()%500;
    int t2=-50,t3=-50;
    circles target(rand()%400+50,rand()%300+50,50,1);
    if(no_of_rainfall==2){
            t2=rand()%500;
    }
    if(no_of_rainfall==3){
            t2=rand()%500;
            t3=rand()%500;
        }

    while(1){
        if(game_status==1)break;
        if(game_over()==0||game_over(t1,t2,t3,y_coordinate_bullfall,machine.get_x_coordinate())==0){
			key_stroke=getch();
            if(key_stroke=='r')game_status=1;
			else
            if(key_stroke==27)goto end;
            continue;
        }
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
            t3=-50;}else
            if(no_of_rainfall==2){
            t2=rand()%500;
            t3=-50;
            }
        }
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
         }
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
    char aa[20];int i;
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
                life_count.display(1);
                return 0;
            }
        else
        if(t2>=i && u>=611 && t2<=i+100){
                cleardevice();
                settextstyle(2,0,50);
                out(220,250,"Game Over");
                 life_count.display(1);
                return 0;
        }
        else
        if(t3>=i && u>=611 && t3<=i+100){
                cleardevice();
                settextstyle(2,0,50);
                out(220,250,"Game Over");
                 life_count.display(1);
                return 0;
        }else
    return 1;
}

bool game_over(){
    if(life_count.get_life()<=0){
        setcolor(RED);
        settextstyle(2,0,50);
        out(220,250,"Game over");
        life_count.display(1);
        return 0;
    }
    else return 1;
}

void check(char key_stroke,shooter& s,const circles& target){
//    if(key_stroke=='p')cout<<s.get_x_coordinate()<<" "<<s.get_x_coordinate()<<endl;

	if(key_stroke==s.left_key)s--;			//move shooter left											prefix operator for moving machine
    if(key_stroke==s.right_key)s++;			//move shooter right										postfix operator for rotating angle of shooter
	if(key_stroke==s.s_left_key)--s;           //rotate shooter anti-clockwise
    if(key_stroke==s.s_right_key)++s;             //rotate shooter clockwise
	/*if(key_stroke==s.shoot_key()){										//for shooting lasers
		s.shoot();
		bullet b(s.get_x_coordinate(),s.get_y_coordinate(),s.get_h_coordinate(),3);
		b.draw(target);
	}*/
    cleardevice();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class score member function defination
score::score():life(3),current_score(0){}
inline int score::get_life() const{return life;}
inline void score::set_life(int n){life=n;}
inline int score::get_score()const{return current_score;}
inline void score::update_c_score(){current_score+=5;}
void score::reset(){life=3,current_score=0;}
inline void score::update_h_score(){
	if(current_score>high_score)
		high_score=current_score;
}
void score::display(int i){
    setcolor(RED);
    out(330,350,current_score);
}
void score::display(){
    setcolor(YELLOW);
    out(599-40,60,"ULTIMATE");
    out(599-40,80,"SHOOTING");
    out(599-40,100,"CHALLENGE");
    out(599-40,190,"HIGH SCORE");
	out(599-20,220,high_score);
    out(599-40,289-32+60,"Current score");
    out(10,10,current_score);									//display current score on left top
    out(599,289+60,current_score);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class shooter member function defination
inline shooter::shooter(int _x,int _y,int _h,char left,char right,char s_left,char s_right,char _shoot):bullfall(_x,_y),h(_h),shoot_key(_shoot){
	set_keys(left,right);
	set_s_keys(s_left,s_right);
}
char shooter::get_left_key()const{return left_key;}
char shooter::get_right_key()const{return right_key;}
char shooter::get_s_left_key()const{return s_left_key;}
char shooter::get_s_right_key()const{return s_right_key;}
int shooter::get_h_coordinate()const{return h;}
inline void shooter::draw(){
    setcolor(YELLOW);								//set color of shooter
    line_styles(SOLID_LINE);                       	//making line solid
    line(x,y,x+100,y);                             	//upper line of shooter
    line(x,y,x,y+28);                              	//left line
    line(x,y+28,x+100,y+28);                       	//bottom line
    line(x+100,y,x+100,y+28);                      	//right line
	line(x+50,y+28,x+h,y);                           	//shooter's line
}
/*inline void shooter::set_coordinate(int ii,int jj){
    x=ii;
    y=jj;
    h=50;
}*/

void shooter::set_keys(char left,char right){
	left_key=left;
	right_key=right;
}
void shooter::set_s_keys(char left,char right){
	s_left_key=left;
	s_right_key=right;
}
void shooter::operator--(int){
    int n=10;
	if(x-n>=1)x-=n;
}
void shooter::operator++(int){
    int n=10;
	if(x+n<=399)x+=n;
}
void shooter::operator--(){
    int n=5;
	if(h-n>=0)h-=n;
}
void shooter::operator++(){
    int n=5;
	if(h+n<=100)h+=n;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class circles member function defination
circles::circles(int ii,int jj,int kk,int decay_rate):bullfall(ii,jj),r(kk){decayrate=decay_rate;}
void circles::draw(int i){
	setcolor(i);
	circle(x,y,r);
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
	r-=decayrate;
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
void bullfall::draw(int i,int j){
    setcolor(i);
	line(x,y,x,y+j);
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
void bullet::draw(const circles& target){
    int hh=x,kk=y;//(x,y)
    while(y>0){
			/*first we calculate radius of the circle and distance between bullets current position and the centre of the circle
            let this distance be d. if d becomes less than radius of the circle then the bullet will lie inside circle
            hence the target has been hit.so life of the shooter will decrease.
            */
        if(dist1(x,y,target.get_x_coordinate(),target.get_y_coordinate())<=target.get_radius())
        {
            life_count.update_c_score();
			life_count.update_h_score();
            target.~circles();
            break;
        }
           //uses two point form y-y1=m*(x-x1) to aim the target where m=(y2-y1)/(x2-x1)
        x=(y-kk-28)*(50-x_h)/28+hh+50;
        (*this).circles::draw(9);                                                                    //doubt
        y-=15;
    }
    delay(30);
}
int bullet::get_x_h_coordinate()const{return x_h;}
