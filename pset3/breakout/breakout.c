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

// paddle height and width
#define PHEIGHT 10
#define PWIDTH 75

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

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
    
    // lost game with bricks remaining
    GLabel gameover = newGLabel("Game Over");
    
    // all bricks destroyed. Good Game, well played!
    GLabel winning = newGLabel("GG, wp");

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // initial velocity
    double velocityX = drand48()*2;
    double velocityY = 1.0;
    
    int t = 1;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        updateScoreboard(window, label, points);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event);
                if(x > 325)
                    x = 325;
                setLocation(paddle, x, 500);
            }
        }
        
        move(ball, velocityX, velocityY);
        GObject object = detectCollision(window, ball);
        
        if(strcmp(getType(object), "GRect") == 0 && object != paddle)
        {
            removeGWindow(window, object);
            velocityY = -velocityY;
            points++;
            bricks--;
        }
        
        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= WIDTH)
        {
            velocityX = -velocityX;
        }
        else if (getX(ball) <= 0)
        {
            velocityX = -velocityX;
        }
        else if (getY(ball) + getHeight(ball) >= HEIGHT)
        {
            lives -= 1;
            if(lives == 0)
                break;
            setLocation(ball, 200, 300);
            setLocation(paddle, 169, 500);
            waitForClick();
        }
        else if (getY(ball) <= 0)
        {
            velocityY = -velocityY;
        }
        
        if(object == paddle)
        {
            velocityY = -velocityY;
        }
        
        
        
        // linger before moving again
        pause(2);
    }

    if(bricks > 0)
    {
       setFont(gameover, "Arial-60");
       setColor(gameover, "fa334f");
       add(window, gameover);
       setLocation(gameover, 25, 325); 
    }
    else
    {
       setFont(winning, "Arial-65");
       setColor(winning, "b2950b");
       add(window, winning);
       setLocation(winning, 75, 325);
    }
    
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
    int i, j, x = 0, y = 25;
    
    for(i = 0; i<ROWS; i++){
        x = 2;
        for(j = 0; j<COLS; j++){
            GRect brick = newGRect(0, 0, 35, 25);
            setFilled(brick, true);
            setLocation(brick, x, y);
            switch(i)
            {
                case 0:
                    setColor(brick, "99A5F2");
                    break;
                case 1:
                    setColor(brick, "99C3F2");
                    break;
                case 2:
                    setColor(brick, "99E2F2");
                    break;
                case 3:       
                    setColor(brick, "99F2F1");
                    break;
                default:
                    setColor(brick, "99F2DC");
            }
            x = x + 40;
            add(window, brick);
        }
        y = y + 30;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2, HEIGHT/2, 25, 25);
    setFilled(ball, true);
    setColor(ball, "b413ec");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int x = 0, y = 500;
    x = (WIDTH/2) - (PWIDTH/2);
    GRect rect = newGRect(0, 0, PWIDTH, PHEIGHT);
    setFilled(rect, true);
    setColor(rect, "37007e");
    setLocation(rect, x, y);
    add(window, rect);
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel(" ");
    setFont(label, "Arial-50");
    setColor(label, "d9daf2");
    add(window, label);
    setLocation(label, 200, 175);
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
