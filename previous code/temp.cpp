class shooter:public bullfall{
public:
    shooter(int,int,int,char,char,char,char,char);   	//constructor of shooter class
    void draw();									//display shooter on the screen
//    void set_coordinate(int,int);      				//for changing the position of shooter_ box & shooter    never use

	void set_keys(char,char);						//it will set movement key
	void set_s_keys(char,char); 					//it will set shooter key

	char get_left_key()const;               		//get left movement key
	char get_right_key()const;                  	//get right movement key
	char get_shoot_key()const:
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
	char s_shoot_key;
};

inline shooter::shooter(int ii,int jj,int xx,char left,char right,char s_left,char s_right,char s_shoot):bullfall(ii,jj),h(xx){
	set_keys(left,right);
	set_s_keys(s_left,s_right,_shoot);
	
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
