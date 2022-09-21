#include <simplecpp>
#include<string>
#include "shooter.h"
#include "bubble.h"

/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);


/* This "q" is created to generate a time interval in which the life of shooter can't decrease in any way also,
 the time upto which the effect of collision of shooter with a bubble remains in effect, which is represented by the color change */
double q=20;          //" 20 is just a random value not the actual "time interval" as described in the above comment!"
bool chk_score=false;

double time_start=30; // time for which the game will run

/*to string function*/
/* which just convert decimal in range(0.00,99.99) to
   string also it should have only two floating point no.'s */
string tostr(double n){
    int tot_int=round(n*100);// rounding the double after multiplying with 100 so that precision will be there for two decimal places
    string s="abcde";
    for(int i=0;i<5;i++){
        if(i==2) s[i]='.';
        else{
          s[4-i]=char(tot_int%10 + '0'); //storing the decimal part in string//
          tot_int/=10;
        }
    }
    if(s[0]=='0') s.erase(0,1);
    return s;
}

//function for updation of score!
void newscore(bool &chk, string &scr, Text &scrPressed){
    if(chk){
        char ch=scr[7];

        ch=char(ch+1);

        scr[7]=ch;
        scrPressed.setMessage(scr);
        chk=false;
    }
    return;
}

void move_bullets( vector<Bullet> &bullets , vector<Bubble> &bubbles, string &scr, Text &scrPressed){


    // move all bullets
    unsigned int i;
    for ( i=0; i < bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
            }

        //checking whether a bullet hits a bubble and also calling the function to update score!
        unsigned int j;
        for( j=0; j < bubbles.size() ; j++){

         if(abs(bullets[i].get_center_x() - bubbles[j].get_center_x()) <= (5+bubbles[j].get_radius()) && abs(bullets[i].get_center_y() - bubbles[j].get_center_y()) <=(5+bubbles[j].get_radius()) && bullets.size()>0)
         {
            chk_score = true;
            newscore(chk_score, scr, scrPressed);

            //erasing the bullet that shooted the bubble!
            bullets.erase(bullets.begin()+i);

            //if bubble radius == 20(the large bubble) breaking in peices else just erasing it!
            if( bubbles[j].get_radius() == 20){

                bubbles.push_back(Bubble(bubbles[j].get_center_x(), bubbles[j].get_center_y(), BUBBLE_RADIUS_THRESHOLD, -BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
                bubbles.push_back(Bubble(bubbles[j].get_center_x(), bubbles[j].get_center_y(), BUBBLE_RADIUS_THRESHOLD, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));

                bubbles[bubbles.size()-1].t=0;
                bubbles[bubbles.size()-2].t=0;

                bubbles.erase(bubbles.begin()+j);

            }

            else{
                bubbles.erase(bubbles.begin()+j);
            }


         }
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles, Shooter &shooter, string &life, Text &lifePressed){

    /*checking hit with the shooter,
      if yes then decreasing the life by using the defined chk_hit() function in the class "Bubble"! */
    for(unsigned int h=0;h<bubbles.size();h++){
        bubbles[h].chk_hit(shooter, q, life, lifePressed);
    }

    //regaining the color of the shooter
    if(q>1.5) shooter.shootr_set_color(COLOR(0, 255, 0));

    // move all bubbles & introducing collision if its there!
    for (unsigned int j=0; j < bubbles.size(); j++)
    {
        bubbles[j].nextStep(STEP_TIME);
        if(bubbles[j].t<=20) bubbles[j].t+=0.3;
        for(unsigned int k=j+1;k < bubbles.size(); k++)
        {
            double rsum=bubbles[k].get_radius() + bubbles[j].get_radius();

            //introducing collision//
            //the (bubbles[].t>3) condition is used so that is doesn't go on changing the velocity just after separation---//
            if(abs(bubbles[j].get_center_x()-bubbles[k].get_center_x()) <=rsum && abs(bubbles[j].get_center_y()-bubbles[k].get_center_y())<=rsum && bubbles[k].t>3 && bubbles[j].t>3)
                {
                    //introducing collision//
                    double temp=bubbles[k].vx;
                    bubbles[k].vx=bubbles[j].vx;
                    bubbles[j].vx=temp;

                    temp=bubbles[k].vy;
                    bubbles[k].vy=bubbles[j].vy;
                    bubbles[j].vy=temp;
                }
        }

    }

}


vector<Bubble> create_bubbles()
{
    // create initial bubbles in the game
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, BUBBLE_DEFAULT_VY, COLOR(255,105,180)));
    return bubbles;

}


int main()
{

    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    string msg_cmd("CMD: _");
    Text charPressed(LEFT_MARGIN -20, BOTTOM_MARGIN, msg_cmd);
    charPressed.setColor(COLOR(50,0,200));
    charPressed.setFill(true);
    // String for score
    string scr="SCORE: 0";
    Text scrPressed(WINDOW_X-LEFT_MARGIN, BOTTOM_MARGIN, scr);
    scrPressed.setColor(COLOR(50,0,200));
    scrPressed.setFill(true);

    // Strinng for life of the shooter
    string life="LIFE: 3";
    Text lifePressed(WINDOW_X/3 -45, BOTTOM_MARGIN, life);
    lifePressed.setColor(COLOR("red"));
    lifePressed.setFill(true);

    // String for timer
    string timer= "TIME REM: 30.00";
    Text timePressed(2*WINDOW_X/3-10, BOTTOM_MARGIN, timer);
    timePressed.setColor(COLOR("red"));
    timePressed.setFill(true);

    // Intialize the shooter
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles();

    // Initialize the bullets (empty)
    vector<Bullet> bullets;

    XEvent event;

    // Main game loop
    while (true)
    {
        bool pendingEvent = checkEvent(event);
        if (pendingEvent)
        {
            // Get the key pressed
            char c = charFromEvent(event);
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);

            // Update the shooter
            if(c == 'a')
                shooter.move(STEP_TIME, true);
            else if(c == 'd')
                shooter.move(STEP_TIME, false);
            else if(c == 'w')
                bullets.push_back(shooter.shoot());
            else if(c == 'q')
                return 0;
        }

        // Update the bullets
        move_bullets(bullets, bubbles, scr, scrPressed);

        // Update the bubbles
        move_bubbles(bubbles, shooter, life, lifePressed);



        wait(STEP_TIME);

        //Ending of game (3 ways)!
        if(scr == "SCORE: 6" || life == "LIFE: 0" || timer == "TIME REM: 0.00"){
        string gameovr="GAME OVER";
        Text ovr( WINDOW_X/2 -35, BOTTOM_MARGIN, gameovr);
        ovr.setColor(COLOR("blue"));
        ovr.setFill(true);
        wait(2);
        break;
        }

        //Upadate timer// by erasing the substring of decimal in timer and then appending a new string by using tostr() function //
        timer.erase( 10 , 5 );
        string new_time = tostr(time_start - STEP_TIME);
        time_start -= STEP_TIME;
        timer = timer + new_time;
        timePressed.setMessage(timer);

        //  END OF THE LOOP!
    }
}
