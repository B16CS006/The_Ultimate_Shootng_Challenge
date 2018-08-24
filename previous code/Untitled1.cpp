#include<iostream>
#include<graphics.h>
#include <thread>
using namespace std;

void display(int i,int j,int x){
    cout<< "Hello chetan";

    setcolor(YELLOW);
    line_styles(SOLID_LINE);
    line(i,j,i+100,j);
    line(i,j,i,j+28);
    line(i,j+28,i+100,j+28);
    line(i+100,j,i+100,j+28);
    line(i+50,j+28,x,j);
}

void bullet(int i,int j,int l){
//    cout<<"bullet\n";
    int h=i,k=j;
    while(j--){
//        cout<<"2while\n";
        i=(j-k-28)*(50-l)/28 +h+50;
        setcolor(9);
        circle(i,j,1);
    }
    delay(30);

}

int main(){



  // Both function are now running an different thread
  // We need to wait for them to finish


    int gd  = DETECT,gm;
    char* c = NULL;
    initgraph(&gd,&gm,c);
    int i=269,j=450;
    int x=50;
    while(1){
//        cout<<"1while\n";
        std::thread x(display(i,j,i+x));
        char ch = getch();
        if(ch=='x')break;
        if(ch=='p')cout<<i<<" "<<j<<endl;
        switch(ch){
            case 'w':j-=2;break;
            case 'a':if(i>0)i-=2;break;
            case 'd':if(i<538)i+=2;break;
            case 's':if(j<450)j+=2;break;
            case ' ':std::thread x(bullet(i,j,x));break;
            case 'j':if(x>0)x-=5;break;
            case 'l':if(x<100)x+=5;break;
        }  x.join();
  y.join();
        cleardevice();
 //       display(i,j,i+x,j);
    }

    closegraph();
    return 0;
}
