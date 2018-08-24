
#include<iostream>
#include<fstream>
using namespace std;

class Game_Status{
public:
    Game_Status();							//constructor
    int get_life() const;					//return life
    void set_life(int);						//set the value of life
    int get_score()const;					//return current score
    void update_c_score();					//update_c_score current score
    void display();							//display all the required ingrident during play
    void reset();							//reset life and current score to its default value.
    void display(int i);					//display current score after GAME OVER
    void display_life();             	 	// display no. of lifes
    void update_h_score();
    void save_h_score();
    void enter_name();
    void sort_score(int&,int&,int&);

private:
    int life,current_score;
    char name[100];
    struct high{
        char user_name[100];
        int s;
        high(){
            user_name[0]='\0';
            s=0;
        }
    }high_score[6];
};								//it will create a global variable of type class score



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																											//class score member function defination
Game_Status::Game_Status():life(3),current_score(0){
    ifstream file;
    file.open("score.text",ios::in);
    for(int i=0;i<5;++i)file.read((char*)&high_score[i],sizeof(high_score[i]));
    file.close();
    high_score;
};

inline int Game_Status::get_life() const{return life;}

inline void Game_Status::set_life(int n){life=n;}

inline int Game_Status::get_score()const{return current_score;}

inline void Game_Status::update_c_score(){current_score+=5;}

void Game_Status::reset(){life=3,current_score=0;vel=0;}

void Game_Status::display(int i){
    setcolor(RED);
    out(330,350,current_score);
}

/*Display:
	Name of the game : ULTIMATE SHOOTING CHALLENGE
	Highscore
	Current Score
	Number of lives : by showing number of line
*/
void Game_Status::display(){
    setcolor(YELLOW);
    out(599-40,60,"ULTIMATE");
    out(599-40,80,"SHOOTING");
    out(599-40,100,"CHALLENGE");
    out(599-40,190,"HIGH SCORE");
	out(599-20,220,high_score[0].s);
    out(599-40,289-32+60,"Current score");
    out(10,10,current_score);									//display current score on left top
    out(599,289+60,current_score);

/*show the number of lines
		if one life then show 1 line else
		if two life then show 2 lines else
		if three life then show 3 lines
*/
	setcolor(GREEN);						//lines will be printed by green colour
    switch(life_count.get_life()){			//check the number of remaining life
		case 3:line(629,429,629,478);
		case 2:line(599,429,599,478);
		case 1:line(569,429,569,478);
	}
}

void Game_Status::display_life(){			//not in use
  cout<<"erase it"<<endl;
}

//Update the Highsocre

void Game_Status::update_h_score(){
    if(current_score>high_score[5].s){								//I have change the 0 to 5
        high_score[5].s=current_score;
    }
}



void Game_Status::enter_name(){
    cleardevice();
	setcolor(WHITE);
    out(100,50,"Please Enter Username : ");
    int i=0;
    char c=getch();
    high_score[5].user_name[i]=c; i++;
    while(1){
    c=getch();
    if(c==13) return ;
    high_score[5].user_name[i]=c; i++;
    out(100,100,high_score[5].user_name);
    }

}


void Game_Status::save_h_score(){
    if(high_score[5].s>high_score[4].s){
        int i,j,n;
        life_count.sort_score(i,j,n);
    }

    ofstream file;
    file.open("score.txt",ios::out);
    for(int i=0;i<5;++i)file.write((char *)&high_score[i],sizeof(high_score[i]));
    file.close();
    for(int ii=0;ii<6;ii++){
        cout<<high_score[ii].user_name<<" "<<high_score[ii].s<<" "<<endl;
    }
}
void Game_Status::sort_score(int& i,int& j,int& n){
        Game_Status::high temp;
        for(i=1;i<=5;i++)
    {
        temp=high_score[i];
        j=i-1;

        while((temp.s>high_score[j].s)&&(j>=0))
        {
            high_score[j+1]=high_score[j];    //moves element forward
            j=j-1;
        }
        high_score[j+1]=temp;    //insert element in proper place
    }
}
