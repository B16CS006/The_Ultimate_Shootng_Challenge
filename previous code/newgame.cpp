/*all the three function are required because they give warning during compile time
when a string literal is passed in the argument of original funcion so we refine 
these function. Warning is come because type of string literal is const char*
and in prototype of these function we use char* instead of const char*
*/
void out(int,int,const char[]);	//display Text on screen
void out(int,int,int);	//display integer on screen
char *int_to_string(int char[],int); //convert intger to string

int dist(int x1,int y1,int x2,int y2);	//calculate distance between (x1,y1) and (x2,y2)

class Game{
public:
	Game();	//constructor
	void reset_life();	//reset life to default
	void update_c_score();	//target hit, current_score updated
	void update_h_score();	//current_score>high_score, high_score updated
	void display();	//display current_score,high_score,life
	void reset();	//reset all current_score,high_score,life
	~Game();
private:
	int current_score;
	int high_score;
	int life;
	int status;
};

struct base{
public:
	base(int _x,int _y):x(_x),y(_y){}	//constructor
	void set_coordinate(int _x,int _y){x=_x;y=_y;}	//set x and y coordinate
	int get_x()const{return x;}	//return x-coordinate
	int get_y()const{return y;}	//return y-coordinate
protected:
	int x,y;						//x-coordinate and y-coordinate
};

class Rainfall{
public:
	Rainfall(int);	//constructor
	
private:
	int number;	//number of objects are falls
	vector<base*> b;
};

class Circle:protected base{
public:
	Circle(int,int,int _r = 50,int _decayrate=0);	//constructor
	void draw()const;	//draw a circle of radius r at (x,y)
	void operator--(int);	//reduce the radius of circle by unit decayrate
	void reset(int,int,int _r = 50,);	//reset the centre and radius of circle
	~Circle();	//destructor, it will set radius to zero
protected:
	int r;		//radius of a circle
	const int decayrate;	//rate at which radius of circle decreases
};

//Only one coordinate of Gun change rest of other are fixed w.r.t tank
class Gun:protected Circle{
public:
	Gun(int,int,int,int _r = 3);	//constructor
	void display();	//display Gun on screen
	bool is_target_hit(const Circle&)const;	//check wether bullet hit target or not
	int get_s_x_coordinate()const;	//return upper x-coordinate of Gun
	void set_s_key(char,char,char);	//set left and right movement key of Gun
	void shoot();	//shoot the circle
	void operator--(int);	//rotate Gun to left
	void operator++(int);	//rotate Gun to right
	void action(char);	//perform action according to received key i.e. move or shoot
	~Gun();
private:
	int s_x;	//upper x-coordinate of Gun
	char left_s_key,right_s_key;//key to shift Gun
	char shoot_key;
};

class Tank:protected:base{
public:
	Tank();	//constructor
	void display();	//display Tank object on screen
	void set_movement_key(char,char);	//set left and right movement key of tank
	void operator--(int);	//move tank to left
	void operator++(int);	//move tank to right
	friend action(char,Tank&);	//perform action when key press i.e. move tank or pass key to Gun
	
	~Tank();
protected:
	char left_t_key,right_t_key;	//key to shift tank left and right
	Gun *gun;						//every tank has gun
};

bool game_over();	//overall game over
bool game_over_hit();	//game over if tank hit by obstacles
bool game_over_disappear();	//game over if 3 target successfully escape
void action(char,Tank&);	//perform action when key hit perform its work



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
										//rainfall
Rainfall::Rainfall(int _number)number(_number){
	for(int i=0;i<n-1;i++)
		b.push_back();
	for(int i=0;i<n;i++){
		b[i]->x = rand()%LENGTH