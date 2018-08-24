#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<pthread.h>
using namespace std;

class shooter{
    int i,j,x;
public:
    shooter(int ii,int jj,int xx):i(ii),j(jj),x(xx){}
    void draw(){
        setcolor(YELLOW);
        line_styles(SOLID_LINE);
        line(i,j,i+100,j);                                                      //upper line
        for(int fil = 0;fil<29;fil++)
            line(i,j+fil,i+100,j+fil);
        line(i,j,i,j+28);                                                       //left side line
//        line(i,j+28,i+100,j+28);                                                //bottom line
        line(i+100,j,i+100,j+28);                                               //right line
        setcolor(RED);
        line(i+50,j+28,x,j);                                                    //shooter line
    }
    void change(int ii,int jj,int xx){
        i=ii;
        j=jj;
        x=xx;
    }
};
class circles{
    int i,j,k;
public:
    circles(int ii=50,int jj=50,int kk=50):i(ii),j(jj),k(kk){}
    void draw(){
        setcolor(YELLOW);
        circle(i,j,k);
    }
    int get_radius()const{return k;}
    void set_radius(int kk){k=kk;}
    void set_centre(){
            i=rand()%400+50;
            j=rand()%300+50;
    }
    void reduce(int kk){k-=kk;}
    ~circles(){}

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
    void draw(){
        int h=a,k=b;
        while(b>0){
            a=(b-k-28)*(50-c)/28 +h+50;
            setcolor(9);
            circles lasers(a,b,3);
            lasers.draw();
            b-=15;
        }
        delay(30);
    }
};

int main(){

   // int gd  = DETECT,gm;
    //char* c = NULL;
    //initgraph(&gd,&gm,c);
    initwindow(500,640);
    int i=189,j=611;
    int x=50;
    char ch;
    int u=4,t1=rand()%500,t2=rand()%500,t3=rand()%500;
    shooter s(i,j,x);
    bullfall fall1,fall2,fall3;
    circles aim;
    while(1){
        if(u<=640){
            u+=5;
            fall1.set_value(t1,u);
            fall1.draw();                                                   //bullet fall draw
            fall2.set_value(t2,u);
            fall2.draw();
            fall3.set_value(t3,u);
            fall3.draw();
        }
        else {
            u=4;
            t1=rand()%500;
            t2=rand()%500;
            t3=rand()%500;
        }

        s.change(i,j,x+i);                   //shooter position change change private variables of shooter
        s.draw();                            //shooter draw it does't take any argument thats why we need change

        if(aim.get_radius()>0)
            setcolor(LIGHTCYAN)
            aim.draw();              //object circle whose size decreasing continuously
        else {
            aim.set_radius(50);
            aim.set_centre();
        }

        if(kbhit()){
        ch = getch();
        if(ch=='x')break;
        if(ch=='p')cout<<i<<" "<<j<<endl;
        switch(ch){
            case 'w':j-=10;break;
            case 'a':if(i>1)i-=10;break;
            case 'd':if(i<399)i+=10;break;
            case 's':if(j<610)j+=10;break;
            case ' ':{bullet b(i,j,x); b.draw();break;}
            case 'j':if(x>0)x-=5;break;
            case 'l':if(x<100)x+=5;break;
        }


       // cleardevice();
 //       display(i,j,i+x,j);
        }else{
            delay(50);
            cleardevice();
            aim.reduce(1);
         }

    }

    closegraph();
    return 0;
}
