# The Ultimate Shootng Challenge
  A simple shooting game using c++ in which there is a shooter which shoot some circlur objects
  surrounded by obstacles and size of these targeted objects gradually decreasing if any three
  targets are completely lost then the game is over. There is another way too to end the game,
  some meteors like objects are falling from above and as soon as the objects hit our shooter
  it loses some of its healh and if health become zero(0) we lost the game. There is anothe
  interesting thing in our game that the difficult is increasing as we score than target like
  the objects's falling speed increase as well as circular objects are decreasing more fasther.
  Our game store TOP 5 score in a sorted form.

# System Requirement 
    • To Compile the project you need incule graphics.h and and conio.h(if compiling with g++ compiler).
    
# How to start the game
    • Windows Users : Simply double click the .exe file.
    • Linux Users : You need to install windows campatiblity in linux
      i.e wine and then Start the .exe file by writing  “wine Ultimate_shooting_game.exe” in the 
      directory of the game (in terminal). 

# Controls
    •   <- (left arrow key)   :       Move left
    •  -> (right arrow key)   :       Move right
    •                     Z   :       Rotate angle anti-clock wise
    •                     X   :       Rotate angle clock wise
    •                 Space   :       Shoots bullets
    •                   Esc   :       Exit the game
    •                     P   :       Pause the game
    •                     R   :       Restart’s the game

# STARING THE GAME               
    • First screen will be this you have to press space to go to next screen
    • Next screen will contain the instructions of the game.
    • After that you have to enter your name so that if you break any previous high score we will 
      save your high score in our database.
    • After this screen your game will be started.
    • Health Bar & the Shooter tank

# About Game Components
## Health Bar & the Shooter tank
    1. This Tank is actually you, you have to move this and protect this.
    2. The triangle represents your gun you can rotate it as you like you have to shoot at the circles
       genrating randomly on the screen using this gun.
    3. The red bar represets your health 
    4. Initially you have 7 health means you can take upto 7 damage from bullets.
    5. After getting certain amount of score level will be changed and you health bar will get full and
       then you can get upto 14 damage from the bullets.
    6. As the damage increases your red bar will Starts decreasing.

## Randomly generating circles
    • This object will be generated on your screen randomly anywhere you have to shoot the inner bigger
      circle before it disappears
    • Radius of the inner circle will be decreasing at some rate after which it will disappear and your
      life will decrease.
    • Those 2 blue circles will be rotating in opposite direction to each other around the inner circle 
      and these two will be an obstacle for you to shoot the inner circle.
      
## Player’s Life
    • Initially player will have 3 lifes as you as game goes if you are unable to shoot the target circle
      your life will decrease.
    • If you miss more than 3 circles you will not have any life lift so you will lose.

## Level Change
    • As you break certain amount of score the level will get change speed of bullets falling from about
      will increase and color of the bullets will change from yellow to red and your health will increase
      from 7 to 14.

## Falling Bullets
    • These Bullets are the real enemy of you in this in this game. 
    • If you got hit by them them your health will decrease.
    • As the level change speed of their falling will increase
    • At a time, maximum 4 bullets can fall.

## The Gun
    • The weapon you have in this game is this gun. It shoots circle in range from 0 to 180 degree. 
    • You have to shoot the randomly genrating target(circles) with this gun.

## Pause
    • To pause the game at any movement press ‘P’ and to resume press ‘P’ again.

## After Game Over
    • To restart the game press ‘r’ and to see high score press h and to exit press esc.

# About Code
## How the game works?
    • At first there exists a base class that is x_y_coordinates, which contains and maintains all
      the x and y coordinates of the game.
    • Origin of the screen is at top left point of the screen.

## Basic functions which we have used from graphcs.h
    1. Outtextxy(x_coordinate,y_coordinate,char* textstring): It silmpy prints the given string to
       the given coordinates.
    2. Settextstyle(int font,int direction,int charsize): It decides to font of the string which
       we like to print.
    3. Setcolor(color name) : It decide the color of the whatever printing after this function line.
    4. Circle(x_center_coordinate,y_center_coordinate,radius): make circle at at provided center.
    5. Line(x1,y1,x2,y2): make line from (x1,y1) to (x2,y2).
    6. Delay(time(ms)): stop the code execution for that much milli seconds.
    7. Getch(): saves char in its stream.
    8. Cleardevice(): clear the whole screen .
    9. Initwindow(): creates a window on which we work in graphics.

## Why we used conio.h?
    • we include conio.h just to use only one of its basic function and that is kbhit() and its work is
      to return true if any key is pressed.

## How the shooter tank is moving horizontally and shooting bullets at different angels?
    • Here shooter tank is derived class of x_y_coordinate as all the x,y coordinates are maintained
      by x_y_coordinate class.
    • set_s_keys and set_keys set the gun and tank movement keys.
    • get.. returns left ,right keys of the tank.
    • get_s.. returns left and right of gun.
    • get_h_key return x coordinate of top of the gun.
    • Here prefix overloading is for angle movement.
    • Here postfix overloading is for shooter tank moving horizontally.

## How bullets are falling?
    • Here fall() is responsible for bullets to fall and for checking simultaneously that the tank
      is hitted by the bullet or not by calling the friend function fall_hit_shooter.
    • draw() make bullets.
    • We can also control the speed of the bullets falling.

## How we are checking does the bullets hit the tank or not?
    • We simply check whether x coordinate of bullet is in range of length of x coordinate of the tank
      and greater than y coordinate of the top of tank.

## How circles are generating at random place and how gun is shooting and those rotating circles?
    • As discussed above all the x,y coordinates are maintained by x_y_coordinates class that’s why
      circles is also derived class of this base class.
    • Here we can set decay rate of the circle using setdecayrate() i.e how fast circle radius will decrease.
    • get_radius returns current radius of the circle.
    • set_radius sets radius to a circle.
    • Postfix – operater is overloaded to reduce the radius of the circle.
    • Set_circle sets coordinates to circle i.e random coordinates
    • ~circles() is distructor of the circle it makes radius of the circle to 0
    • draw_rotator() draws the rotating circles, takes int l in argument to continuously rotate
      and increase the angle of rotation.
    • draw draws the circles and gun also use this same function to shoot the circles.

## How we are checking gun has shooted the target circle or not?
    • Shooter is actually shooting circle whose center coordinates are increasing in straight line.
    • So if distance from centre of these shooted circles to the target circle is less than that
      radius of the target circle than the shooted circle lies inside that of target circle so in
      other way target has been shooted so in that case distructor of the target circle has been
      called and  score will increase we will see later how score is changing.
    • Same concept has been used when the gun shoots the rotating circle but in this case destructor
      of the shooting circle has been called because these rotating circles made to be solid shooting
      circle can’t pass these rotating circles.

## How we are shooting at different angles?
    • In our case y2=y1 and we are only changing x2 with help of postfix ++ and – overloading in shooter
      class we have discussed earliear.
    • So by using 2 point form we get a direction for shooting
    • Two point form:
                    (y-y1)=((y2-y1)/(x2-x1))(x-x1)

## How level of the game is changing?
    • Run time polymorphism has been used to do this.
    • Here we have made 2 classes to this.
    • At the beginning of the game we have pointer p to the player class or we call that player
      initially a beginner.
    • So initially all the function like speed, health bar are used of that of player class as pointer p
      is pointing to player classs.
    • As player breaks certain amount of score pointer p will start pointing to an object of pro_player
      class or player has become a pro-player.
    • So now pointer p will start using functions of pro_player class so speed of the bullets wil increase
      and health bar will also change according to what we want to set.

## How score, health and life has been maintained?
    • get_life(), set_life() maintains life of the player.
    • Reduce_health(), pro_health(),check_health(),get_health() maintains life bar of the player.
    • Update_c_score() updates current score continuously.
    • Update_h_score() updates high score if current score>top score till now.
    • Sort_score sort the scores in the file.
    • Save_h_score() save the score into the file
    • Enter() name used for entering the name of the player at the beginning of the game.

## Why we used c++?
    • Because It is object oriented, I could have also used C but C++ being object oriented helped us to deal
      with complex situation much better than that of C which is not object oriented.

## Future plans 
    • Implement this using parallel programming because right know whole game is running in a single
      loop which makes the game looks flashing.
    • Special object falling, by shooting that object 5 times health and life of the player increases.
    • Better levels.
    • Better score saving method.

## Bibliography
    • en.cppreference.com
    • bjarne stroustrup book
