#include<iostream>
#include<graphics.h>
#include<conio.h>
#include <math.h>
#include<string>
#include<time.h>
using namespace std;
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



class score{
    int life,s,high_score;
public:
    score():life(3),s(0),high_score(1000){};
    int get_life() const{
        return life;
    }
    void set_life(int n){
        life=n;
    }
    int get_score()const{return s;}
    void update(){s=s+5;}
    void display(){
        char c[]="Current Score";
        setcolor(YELLOW);
        out(599-40,60,"ULTIMATE");
        out(599-40,80,"SHOOTING");
        out(599-40,100,"CHALLENGE");
        out(599-20,220,high_score);
        out(599-40,190,"HIGH SCORE");
        out(599-40,289-32+60,c);

        out(10,10,s);
        out(599,289+60,s);
    }
    void reset(){life=3,s=0;}
    void display(int i){
        setcolor(RED);

        out(330,350,s);
    }
}life_count;
class shooter{
    //i and j are the corner point of shooter_box and x is for changing angle for shooter
    int i,j,x;
public:
    shooter(int ii,int jj,int xx):i(ii),j(jj),x(xx){}   //constructor of shooter class
    void draw(){
        setcolor(YELLOW);
        line_styles(SOLID_LINE);                       //making line solid
        line(i,j,i+100,j);                             //upper line of shooter
        line(i,j,i,j+28);                              //left line
        line(i,j+28,i+100,j+28);                       //bottom line
        line(i+100,j,i+100,j+28);                       //right line
        line(i+50,j+28,x,j);                            //shooter's line
    }
    void change(int ii,int jj,int xx){                  //for changing position of shooter_ box & shooter
        i=ii;
        j=jj;
        x=xx;
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
//////////////////////////////////////////////////////////////////////////////main function
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
    int i=189,j=611;
    int x=50;
    char ch;
    int u=4;
    shooter s(i,j,x);
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
        if(game_over(t1,t2,t3,u,i)==0){     //check if bullet strikes the shooter_box
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

           if(game_over(t1,t2,t3,u,i)==0){     //check if bullet strikes the shooter_box
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
        s.change(i,j,x+i);                   //shooter position change change private variables of shooter
        s.draw();                            //shooter draw it does't take any argument thats why we need change
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
        if(ch=='p')cout<<i<<" "<<j<<endl;
        switch(ch){
         //  case 'w':j-=2;break;
            case 75:if(i>1)i-=10;break;
            case 77:if(i<399)i+=10;break;
         //   case 's':if(j<610)j+=2;break;
            case ' ':{bullet b(i,j,x); b.draw(target);break;}
            case 'z':if(x>0)x-=5;break;                     //rotate shooter anti-clockwise
            case 'x':if(x<100)x+=5;break;                   //rotate shooter clockwise
        }
        cleardevice();
 //       display(i,j,i+x,j);
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
