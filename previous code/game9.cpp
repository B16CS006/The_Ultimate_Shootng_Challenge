#include<iostream>
#include<graphics.h>
#include<conio.h>
#include <math.h>
#include<string>
#include<time.h>
using namespace std;
char *int_to_string(int,char[],int);	//convert intger value into array of char
//OVERLOADING OF FUNCTION out()
//it will display text on the graphics screen such as GAME_NAME, HIGH_SCORE, CURRENT_SCORE, or any other text.
void out(int,int,const char[]);			//it will display char array on the graphics screen
void out(int,int,int);					//it will display integer on the graphic screen

//score class for taking care of life, current_score, high_score
//
class score{
    int life,s,high_score;
public:
    score();								//constructor
    int get_life() const;					//return life
    void set_life(int);						//set the value of life
    int get_score()const;					//return current score
    void update();							//update current score
    void display();							//display all the required ingrident during play
    void reset();							//reset life and current score to its default value.
    void display(int i);					//display current score after GAME OVER
}life_count;								//it will create a global variable of type class score


class shooter{
    //x and y are the left corner point of shooter_box and x is for changing angle for shooter
    int x,y,h;
	char left_key,right_key,s_left_key,s_right_key;
//	static shooter default_poistion;
//	static int length,width;
public:
    shooter(int,int,int,char,char,char,char);   					//constructor of shooter class
    void draw();							//display shooter on the screen
    void change_position(int,int,int);      //for changing the position of shooter_ box & shooter
/*	static void set_default_position(int xx,int yy,int hh){
		default_poistion = shooter(189,611,50);
	}*/
	void set_keys(char left,char right){
		left_key=left;
		right_key=right;
	}
	void set_s_keys(char left,char right){
		s_left_key=left;
		s_right_key=right;
	}
	char get_left_key()const{return left_key;}
	char get_right_key()const{return right_key;}

	char get_s_left_key()const{return s_left_key;}
	char get_s_right_key()const{return s_right_key;}

	int get_x_coordinate()const{return x;}
	int get_y_coordinate()const{return y;}
	int get_h()const{return h;}

	void operator--(int){
	    int n=10;
		if(x-n>=1)x-=n;
	}
	void operator++(int){
	    int n=10;
		if(x+n<=399)x+=n;
	}
	void operator--(){
	    int n=5;
		if(h-n>=0)h-=n;
	}
	void operator++(){
	    int n=5;
		if(h+n<=100)h+=n;
	}
};


class circles{                                           //for making any kind of circle
    int i,j,k;
    int decayrate;
public:
    circles(int ii=50,int jj=50,int kk=50):i(ii),j(jj),k(kk){decayrate=1;}  //constructor of circle
    void draw(){                                              //draw circle
        circle(i,j,k);

    }
    void setdecayrate(int x){
        decayrate=x;
    }
    int get_radius()const{return k;}                       //return current radius
    void set_radius(int kk){k=kk;}                         //set radius
    void set_centre(int ii,int jj){                                     //set centre for randomly genrating circle
        i=ii;
        j=jj;
    }
    void operator--(int){
        k-=decayrate;
        if(k<=0){
          int n=life_count.get_life();
          life_count.set_life(--n);
        }
    }
    int get_x_coordinate() const{return i;}
    int get_y_coordinate() const{return j;}
    ~circles(){
        k=0;
    }

};
class bullfall{
    int i,j;
public:
    bullfall(int ii=0,int jj=0):i(ii),j(jj){}                       //doubt
    void draw(){
        setcolor(YELLOW);
        LINE_FILL;
        line_styles(DASH_LINE);
        line(i,j,i,j+10);
    }
    void set_value(int ii,int jj){
        i=ii;
        j=jj;
    }
    ~bullfall(){}
};
int dist1(int x1,int y1,int x2,int y2){
    x1=x1-x2; y1=y1-y2; x1=x1*x1;y1=y1*y1;x1=x1+y1;
    int i= sqrt(x1);

    return i;
}
class bullet{
    int a,b,c;
public:
    bullet(int i,int j,int l):a(i),b(j),c(l){}
//    cout<<"bullet\n";
    void draw(const circles& target){
        int h=a,k=b;
        while(b>0){
            /*first we calculate radius of the circle and distance between bullets current position and the centre of the circle
            let this distance be d. if d becomes less than radius of the circle then the bullet will lie inside circle
            hence the target has been hit.so life of the shooter will decrease.
            */
            if(dist1(a,b,target.get_x_coordinate(),target.get_y_coordinate())<=target.get_radius())
            {

                life_count.update();
                target.~circles();
                break;
            }
           //uses two point form y-y1=m*(x-x1) to aim the target where m=(y2-y1)/(x2-x1)
            a=(b-k-28)*(50-c)/28 +h+50;
            setcolor(9);
            circles lasers(a,b,3);
            lasers.draw();
            b-=15;
        }

        delay(30);
    }
};
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
    return 1;                                //bullet fall draw
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

void func(char ch,shooter& s,const circles& target){
    if(ch=='p')cout<<s.get_x_coordinate()<<" "<<s.get_x_coordinate()<<endl;

	if(ch==s.get_left_key())s--;			//move shooter left											prefix operator for moving machine
    if(ch==s.get_right_key())s++;			//move shooter right										postfix operator for rotating angle of shooter
	if(ch==s.get_s_left_key())--s;              //rotate shooter anti-clockwise
    if(ch==s.get_s_right_key())++s;             //rotate shooter clockwise
	if(ch==' '){										//for shooting lasers
		bullet b(s.get_x_coordinate(),s.get_y_coordinate(),s.get_h());
		b.draw(target);
	}
    cleardevice();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																							//main function
int main(){

    srand(time(NULL));
   // int gd  = DETECT,gm;
    //char* c = NULL;
    //initgraph(&gd,&gm,c);
    initwindow(700,640);
start:
    settextstyle(SANS_SERIF_FONT ,HORIZ_DIR,1);
    life_count.reset();
    int flag=0;
//    int i=189,j=611;
//    int x=50;
    char ch;
    int u=4;
    shooter s(189,611,50,75,77,'z','x');
    bullfall fall[3];
    int bull_no=rand()%3+1;
    int t1=rand()%500;
    int t2=-50,t3=-50;
    circles target(rand()%400+50,rand()%300+50);
    if(bull_no==2){
            t2=rand()%500;
        }
    if(bull_no==3){
            t2=rand()%500;
            t3=rand()%500;
        }

    while(1){
//falling bullets
//std::string s = std::to_string(life_count.get_score());
 //int will be stored here as a string
        if(flag==1){cout<<"hello";
            break;
        }
        if(game_over()==0){
           ch=getch();
               if(ch=='h'){
                flag=1;
               }else flag=0;
               continue;

        }
        if(game_over(t1,t2,t3,u,s.get_x_coordinate())==0){     //check if bullet strikes the shooter_box
               ch=getch();
               if(ch=='h'){
                flag=1;
               }else flag=0;
               continue;
            }
        if(u<=640){
            u+=5;
            fall[0].set_value(t1,u);
            fall[0].draw();
            fall[1].set_value(t2,u);
            fall[1].draw();
            fall[2].set_value(t3,u);
            fall[2].draw();
           // delay(5);

           if(game_over(t1,t2,t3,u,s.get_x_coordinate())==0){     //check if bullet strikes the shooter_box
               ch=getch();
               if(ch=='h'){
                flag=1;
               }else flag=0;
               continue;
            }

        }
        else{
            u=4;
            t1=rand()%500;
            bull_no=rand()%3+1;
            if(bull_no==3){
                t2=rand()%500;
                t3=rand()%500;
            }else
            if(bull_no==1){
            t2=-50;
            t3=-50;}else
            if(bull_no==2){
            t2=rand()%500;
            t3=-50;
            }
        }
//falling bullets end

//s:shooter box
//targer:circle
        life_count.display();
        setcolor(GREEN);
        line(500,0,500,640);
//        s.change_position(i,j,x+i);                   //shooter position change change private variables of shooter
        s.draw();                            //shooter draw it does't take any argument thats why we need change_position
        if(target.get_radius()>0){
            setcolor(DARKGRAY);
            target.draw();
            //delay(50);
        }
        else{
            target.set_radius(50);
            target.set_centre(rand()%400+50,rand()%300+50);
        }
        if(kbhit()){
			ch = getch();
			if(ch==27)break;
			func(ch,s,target);
        }else{
			target--;
			delay(50);
			cleardevice();
         }

    }
    if(1)goto start;
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class score member function defination
inline score::score():life(3),s(0),high_score(1000){};
inline int score::get_life() const{return life;}
inline void score::set_life(int n){life=n;}
inline int score::get_score()const{return s;}
inline void score::update(){s=s+5;}
void score::reset(){life=3,s=0;}
void score::display(int i){
    setcolor(RED);
    out(330,350,s);
}
void score::display(){
    setcolor(YELLOW);
    out(599-40,60,"ULTIMATE");
    out(599-40,80,"SHOOTING");
    out(599-40,100,"CHALLENGE");
    out(599-40,190,"HIGH SCORE");
	out(599-20,220,high_score);
    out(599-40,289-32+60,"Current score");
    out(10,10,s);									//display current score on left top
    out(599,289+60,s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class shooter member function defination
inline shooter::shooter(int ii,int jj,int xx,char left,char right,char s_left,char s_right):x(ii),y(jj),h(xx){
	set_keys(left,right);
	set_s_keys(s_left,s_right);
}
inline void shooter::draw(){
    setcolor(YELLOW);								//set color of shooter
    line_styles(SOLID_LINE);                       	//making line solid
    line(x,y,x+100,y);                             	//upper line of shooter
    line(x,y,x,y+28);                              	//left line
    line(x,y+28,x+100,y+28);                       	//bottom line
    line(x+100,y,x+100,y+28);                      	//right line
	line(x+50,y+28,x+h,y);                           	//shooter's line
}
inline void shooter::change_position(int ii,int jj,int xx){
    x=ii;
    y=jj;
    h=xx;
}
