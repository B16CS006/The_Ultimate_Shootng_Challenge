#include<iostream>
#include<graphics.h>
#include<conio.h>
#include <math.h>
using namespace std;

int dist1(int x1,int y1,int x2,int y2){
    x1=x1-x2; y1=y1-y2; x1=x1*x1;y1=y1*y1;x1=x1+y1;
    int i= sqrt(x1);
    return i;
}

class score{
	int s,life;
public:
	score(int ss=0):s(ss),life(3){}
	void set_score(int ss){s=ss;}
	int get_score()const{return s;}
	void update(){s++;}
	void display(int i,int j){
	    char a[3];
	    char* aa=a;
	    aa=itoa(s,a,3);
	    cout<<aa<<endl;
	    outtextxy(i,j,aa);
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
public:
    circles(int ii=50,int jj=50,int kk=50):i(ii),j(jj),k(kk){}  //constructor of circle
    void draw(){                                              //draw circle
        circle(i,j,k);

    }
    int get_radius()const{return k;}                       //return current radius
    void set_radius(int kk){k=kk;}                         //set radius
    void set_centre(){                                     //set centre for randomly genrating circle
        i=rand()%400+50;
        j=rand()%300+50;
    }
    void reduce(int kk){
        k-=kk;
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
				life_count.display(10,10);getch();
//                char c[]="life decrease";
//                outtextxy(189,611,c);
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
void game_over(int t1,int t2,int t3,int u,int i){
        char c[]="Game Over";
        if(t1>=i && u>=611 && t1<=i+100){
                cleardevice();
                outtextxy(189,611,c);
                getch();
            }
        else
        if(t2>=i && u>=611 && t2<=i+100){
                cleardevice();
                outtextxy(189,611,c);
                getch();
        }
        else
        if(t3>=i && u>=611 && t3<=i+100){
                cleardevice();
                outtextxy(189,611,c);
                getch();
        }
                                  //bullet fall draw
}



int main(){

   // int gd  = DETECT,gm;
    //char* c = NULL;
    //initgraph(&gd,&gm,c);
    initwindow(700,640);
    int i=189,j=611;
    int x=50;
    char ch;
    int k=100;int u=4;
    shooter s(i,j,x);
    bullfall fall[3];
    int bull_no=rand()%3+1;
    int t1=rand()%500;
    int t2=-50,t3=-50;
    circles target;
    if(bull_no==2){
            t2=rand()%500;
        }
    if(bull_no==3){
            t2=rand()%500;
            t3=rand()%500;
        }

    while(1){
//falling bullets
   //     cout<<life_count.get_score()<<endl;
        if(u<=640){
            u+=5;
            fall[0].set_value(t1,u);
            fall[0].draw();
            fall[1].set_value(t2,u);
            fall[1].draw();
            fall[2].set_value(t3,u);
            fall[2].draw();
            delay(5);
            game_over(t1,t2,t3,u,i);     //check if bullet strikes the shooter_box
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
            target.set_centre();
        }
        if(kbhit()){
        ch = getch();
        if(ch==27)break;
        if(ch=='p')cout<<i<<" "<<j<<endl;
        switch(ch){
            case 72:j-=2;break;
            case 75:if(i>1)i-=10;break;
            case 77:if(i<39999)i+=10;break;
            case 80:if(j<6100)j+=2;break;
            case ' ':{bullet b(i,j,x); b.draw(target);break;}
            case 'z':if(x>0)x-=5;break;                     //rotate shooter anti-clockwise
            case 'x':if(x<100)x+=5;break;                   //rotate shooter clockwise
        }
        cleardevice();
 //       display(i,j,i+x,j);
        }else{
         target.reduce(1);
         delay(50);
         cleardevice();
         }

    }

    closegraph();
    return 0;
}
