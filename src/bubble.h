#include <simplecpp>

/* Bubble Vars */
const int BUBBLE_START_X = 250;
const int BUBBLE_START_Y = 50;
const int BUBBLE_DEFAULT_RADIUS = 20;
const int BUBBLE_RADIUS_THRESHOLD = 10;
const int BUBBLE_DEFAULT_VX = 100;
const int BUBBLE_DEFAULT_VY = 50;

class Bubble
{
private:
    Circle circle;  // the circle representing the bubble
    //double vx, vy;  // velocity in x and y direction
    Color color;    // color of the bubble

public:
    /* this "t" is to increase the time upto which the effect of spliting of ball of larger size */
    double t=20; //Timer associated with each bubble             //CHANGE

    double vx, vy;  // velocity in x and y direction //                /* i have kept them in the public variables */
    double newx,newy;//coordinates of bubbles after STEP_TIME;
    Bubble(double cx, double cy, double r, double vx_=BUBBLE_DEFAULT_VX, double vy_=BUBBLE_DEFAULT_VY, Color color_=COLOR(250, 0, 0))
    {
        // Bubble constructor
        color = color_;
        circle = Circle(cx, cy, r);
        circle.setColor(color);
        circle.setFill(true);

        vx = vx_;
        vy = vy_;
    }

    void nextStep(double t)
    {
        // move the bubble
        double new_x = circle.getX() + vx*t;
        double new_y = circle.getY() + (vy)*t;
        newx=new_x;
        newy=new_y;
        vy+=3;      // introducing gravity//
        if ((vx < 0 && new_x < (0 + circle.getRadius())) // bounce along X direction at left border
            ||
            (vx > 0 && new_x > (WINDOW_X - circle.getRadius()))) // bounce along X direction at right border
        {

            vx = -vx;
            new_x = circle.getX() + vx*t;

        }

        /*introducing the collision between the walls and the bubbles */
        if ((vy>0 && new_y > (450-circle.getRadius())) || (vy<0 && new_y < (0+circle.getRadius())) )
        {
            vy=-vy;
            new_y=circle.getY() + (vy)*t;
            vy+=3;// gravity
        }

        circle.moveTo(new_x, new_y);
    }

    double get_radius()
    {
        // return the radius of the bubble
        return circle.getRadius();
    }

    double get_center_x()
    {
        // return the x coordinate of the center of the bubble
        return circle.getX();
    }

    double get_center_y()
    {
        // return the y coordinate of the center of the bubble
        return circle.getY();
    }

    double get_vx()
    {
        // return the x velocity of the bubble
        return vx;
    }
    double get_vy()
    {
        // return the y velocity of the bubble
        return vy;
    }

    Color get_color()
    {
        // return the color of the bubble!
        return color;
    }

    // consequences of collision of bubble with shooter, i.e, the change of color of the shooter's body and decrease in life!
    void chk_hit(Shooter &shooter, double &q, string &life, Text &lifePressed)
    {
      if(q<20) q+=0.02;           // "20" is the initialised random value of q in the main file

      if(q>1.5)                  //SO that the life will not decrease continuously
      {
         //checking the condition of shooter hit with bubble
         if(abs(circle.getX() - shooter.get_head_center_x()) <= (circle.getRadius()+shooter.get_head_radius()) &&
            abs(circle.getY() - shooter.get_head_center_y()) <= (circle.getRadius()+shooter.get_head_radius())
            ||
            abs(circle.getX() - shooter.get_body_center_x()) <= (circle.getRadius()+shooter.get_body_width()/2) &&
            abs(circle.getY() - shooter.get_body_center_y()) <= (circle.getRadius()+shooter.get_body_height()/2)  )
         {
             q=0;

             // changing the color of the shooter to show it gets hitted //
             shooter.shootr_set_color(COLOR(255, 100, 255));

             //update life
             if(life!="Life: 1")
             {
                char ch=life[6];
                ch=char(ch-1);
                life[6]=ch;
                lifePressed.setMessage(life);
             }

             else{
                life="Life: 0";
                lifePressed.setMessage(life);
             }

         }


      }
     }

};
