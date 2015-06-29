//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

//paddle dimensions & y-axis location
#define PHEIGHT 20
#define PWIDTH 75
#define PADDLE_Y (HEIGHT - (PHEIGHT + WINDOW_MARGIN))

#define WINDOW_MARGIN 30
#define BRICK_MARGIN 5

// dimensions of bricks
#define BHEIGHT 10
#define BWIDTH ((WIDTH - COLS*BRICK_MARGIN - WINDOW_MARGIN*2) / COLS)

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{   
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // set ball velocity on both axes
    double x_velocity = drand48()*0.09;
    double y_velocity = 0.055;

    // wait for user to click before starting
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {  
        // MOVE PADDLE
        GEvent event = getNextEvent(MOUSE_EVENT);
        // if event occurred and the even was a mouse movement
        if (event != NULL && getEventType(event) == MOUSE_MOVED)
        {
            // get only x-axis movement of the mouse
            double paddle_x = getX(event) - PWIDTH / 2;
            
            // move paddle along x axis with mouse, but not into the left margin or 
            // further right than margin (including x-dimension of paddle)
            if (paddle_x >= WINDOW_MARGIN && (paddle_x + PWIDTH + WINDOW_MARGIN)  <= WIDTH)
                setLocation(paddle, paddle_x, PADDLE_Y);   
        }

        // MOVE THE BALL
        move(ball, x_velocity, y_velocity); //movement along x & y axes
       
        if (getX(ball) <= 0 || (getX(ball) + 2*RADIUS) >= WIDTH)  // ball hits either side of window
            x_velocity = -x_velocity;    
        else if (getY(ball) <= 0)  // ball hits top of window
            y_velocity = -y_velocity;
        else if ((getY(ball) + 2*RADIUS) >= HEIGHT)   // ball hits bottom of window
        {
            lives--;
            
            setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2 + RADIUS);
            setLocation(paddle, (WIDTH - PWIDTH) / 2, PADDLE_Y);
            
            waitForClick();
        }
                     
        // DETECT COLLISIONS
        GObject hit_object = detectCollision(window, ball);
    
        if (hit_object != NULL && strcmp(getType(hit_object), "GRect") == 0)
        {
            if (hit_object == paddle && y_velocity > 0)
                y_velocity = -y_velocity;
            if (hit_object != paddle)
            {
                removeGWindow(window, hit_object);
                y_velocity = -y_velocity;
                bricks--;
                char str[3];
                sprintf(str, "%d", COLS*ROWS - bricks);
                setLabel(label, str);
            }             
        }
    }
    
    // win/lose message on game over
    removeGWindow(window, label);
    removeGWindow(window, ball);
    GLabel game_over = newGLabel("");
    setFont(game_over, "SansSerif-36");
    if (bricks != 0)
    {
        setLabel(game_over, "YOU LOST!");
        setColor(game_over, "RED");
    }
    else
    {
        setLabel(game_over, "YOU WON!");
        setColor(game_over, "BLUE");
    }
    setLocation(game_over, (WIDTH - getWidth(game_over)) / 2, (HEIGHT + getHeight(game_over)) / 2);
    add(window, game_over);
    
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // initialize location varibles; set y-axis location away from edge of window   
    int brick_x;
    int brick_y = BRICK_MARGIN + WINDOW_MARGIN;
    
    // initialize array of 5 colors for the 5 rows of bricks
    char* colors[] = { "GREEN", "CYAN", "ORANGE", "PINK", "MAGENTA" };
    
    // draw bricks
    for (int i = 0; i < ROWS; i++)
    {
        brick_x = BRICK_MARGIN + WINDOW_MARGIN; // reset x each time for new row
        brick_y += BRICK_MARGIN + BHEIGHT; // adjust y downward for each new row
        
        for (int j = 0; j < COLS; j++)
        {
            // draw each brick      
            GRect brick = newGRect(brick_x, brick_y, BWIDTH, BHEIGHT);
            setColor(brick, colors[i]);
            setFilled(brick, true);
            add(window, brick);
            
            // adjust x - move rightward for next column / next brick in the row
            brick_x += BRICK_MARGIN + BWIDTH;
        } 
    }
}
    

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // instantiate ball in center of window
    GOval ball = newGOval((WIDTH / 2 - RADIUS), (HEIGHT / 2 + RADIUS), 2*RADIUS, 2*RADIUS); // x, y, width, height
    setColor(ball, "RED");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    double paddle_x = (WIDTH - PWIDTH) / 2;
    
    // draw paddle with default init location in bottom center of window
    GRect paddle = newGRect(paddle_x, PADDLE_Y, PWIDTH, PHEIGHT);
    setColor(paddle, "BLUE");
    setFilled(paddle, true);
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SanSerif-36");
    
    setLocation(label, (WIDTH / 2 - RADIUS), (HEIGHT / 2 + RADIUS));
    add(window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
