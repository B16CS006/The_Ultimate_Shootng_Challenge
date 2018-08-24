
#include<iostream>
#include<score.h>


Game_status life_count;

//class for rainfall the deadly objects
class bullfall{
public:
    bullfall(int ii=0,int jj=0);         			//constructor               																//doubt
    void draw(int i=14,int j=10);							//to create rainfall objects on the screen
    void set_coordinate(int ii,int jj);		//to reset the position of objects
    int get_x_coordinate()const;							//return x-coordinate
	int get_y_coordinate()const;							//return y-coordinate
	~bullfall(){}									//destructor
protected:
    int x,y;										//coordinate from which the bullet start falling
};

class shooter:public bullfall{
public:
    shooter(int,int,int,char,char,char,char);   	//constructor of shooter class
    void draw();									//display shooter on the screen
//    void set_coordinate(int,int);      				//for changing the position of shooter_ box & shooter    never use

	void set_keys(char,char);						//it will set movement key
	void set_s_keys(char,char); 					//it will set shooter key

	char get_left_key()const;               		//get left movement key
	char get_right_key()const;                  	//get right movement key

	char get_s_left_key()const;						//get left movement key of shooter
	char get_s_right_key()const;					//get right movement key of shooter

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
	int get_x_h_coordinate()const;
private:
     int x_h;                                       //x-coordinate of shooter angle
};













/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class shooter member function defination
inline shooter::shooter(int ii,int jj,int xx,char left,char right,char s_left,char s_right):bullfall(ii,jj),h(xx){
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
void speed(int &vel){
    vel+=0.05;
}
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

int bullet::get_x_h_coordinate()const{return x_h;}

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