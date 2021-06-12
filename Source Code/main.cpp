#include<iostream>

#include<graphics.h>

#include<conio.h>

#include<dos.h>

#include<time.h>

#include<stdio.h>

#include<math.h>

#define ScWidth 1400
#define ScHeight 700
#define OpWidth 400

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define SPACEBAR 32

using namespace std;

// Dispaly Gameover screen and reset score
void GameOver();

// Draw game board and score / control area
void DrawBoard();

// If player hit collider display gameover screen
int PlayerHitCollider();

// If player hit fruit, score up & regenerate fruit at random position
int PlayerHitFruit();

// Draw Top Crusher
void DrawCrusherUp();

// Draw Bottom Crusher
void DrawCrusherDown();

// Crusher(Enemey) Variables
int e1x = 350, e1y = 200, e2x = 350, e2y = 200;
int e1Step = 3, e2Step = 3, eh = 100, ew = 100;
int e1Init = e1y, e1Limit = 235, e2Init = e2y, e2Limit = 165;

// Player Variables
int px = 485, py = 322;
int ph = 30, pw = 30, pStep = 100;

// Fruits Variables
int fx = 485, fy = py, fStep = -100;

// Other Variables
char option, txtScore[5];
int score = 0;

int main() {
  // to make sure generation of random numbers
  srand((unsigned) time(0));

  // Initialize Graphics
  int gd = DETECT, gm, err, tmp;
  initgraph( & gd, & gm, "C:\\tc\\bgi");

  while (1) { // for keeping game playing

    // Draws game board and score/controls area
    DrawBoard();

    // Draw Crusher (Enemy)
    DrawCrusherUp();
    DrawCrusherDown();

    // Draw Fruit
    setfillstyle(1, LIGHTGREEN);
    bar(fx + fStep, fy, fx + fStep + 30, fy + 30);

    // Draw Player
    setfillstyle(1, LIGHTBLUE);
    bar(px, py, px + pw, py + ph);

    if (kbhit()) { // if any key is pressed while game is playing
      option = getch(); // catch key in options variable
      switch (option) {
      case KEY_LEFT: // if left arrow key is pressed 
        px -= pStep; // update player position
        break;
      case KEY_RIGHT: // if right arrow key is pressed 
        px += pStep; // update player position
        break;
      }
    }

    // when player hit collider
    if (PlayerHitCollider() == 1) {
      delay(300);
      GameOver();
    }

    // when player hit fruit
    if (PlayerHitFruit() == 1) {
      score++; // update score
      if (rand() % 2 == 1) // randomly decide new position of fruit
        fStep = -100; // genenrate fruit at left side
      else
        fStep = 100; // generate fruit at right side
    }

    // for top crusher movement
    e1y += e1Step;
    if (e1y < e1Init || e1y > e1Limit) // if crusher reaches bounds
      e1Step = -e1Step; // reverse direction

    // for bottom crusher movement	
    e2y -= e2Step;
    if (e2y > e2Init || e2y < e2Limit) // if crusher reaches bounds 
      e2Step = -e2Step; // reverse direction

    delay(80);
    cleardevice();
  }

  getch();
  closegraph();
}

void GameOver() {
  cleardevice(); // clear screen

  setcolor(WHITE);
  // Print Game Over Text
  settextstyle(4, 0, 9);
  outtextxy(300, 300, "Game Over");

  settextstyle(4, 0, 2);
  outtextxy(500, 420, "Press any key to restart...");
  getch();
  score = 0; // reset score
  px = 485;
}

void DrawBoard() {

  // draw board
  rectangle(0, 0, ScWidth - OpWidth, ScHeight);
  rectangle(ScWidth - OpWidth, 0, ScWidth, ScHeight);

  // draw title
  settextstyle(4, 0, 4);
  outtextxy(ScWidth - 380, 50, "Avoid Crusher");

  // print score
  // itoa function converts number to character array
  settextstyle(4, 0, 9);
  if (score < 10)
    outtextxy(ScWidth - 270, 250, itoa(score, txtScore, 10));
  else if (score >= 10)
    outtextxy(ScWidth - 320, 250, itoa(score, txtScore, 10));

  settextstyle(4, 0, 1);
  outtextxy(ScWidth - 375, 500, "Controls: ");
  outtextxy(ScWidth - 300, 540, "- Arrow Keys");
}

// If player hit collider display gameover screen
int PlayerHitCollider() {
  // if player is below teeth of crusher
  if (px < 485 || px > 485)
    // if cursher tooth touches player
    if (e1y + eh >= py || 2 * e2y <= py + ph) {
      return 1;
    }
  return 0;
}

// If player hit fruit, score up & regenerate fruit at random position
int PlayerHitFruit() {
  // if position of player and fruit matches
  if (px == fx + fStep)
    return 1;
  return 0;
}

// Draw Top Crusher
void DrawCrusherUp() {
  int offset = e1x;
  setfillstyle(1, WHITE);
  bar(e1x, e1y, e1x + ew, e1y + eh); // draw first tooth
  offset = offset + ew;
  bar(offset, e1y, offset + ew, e1y + eh / 2); // draw gap
  offset = offset + ew;
  bar(offset, e1y, offset + ew, e1y + eh); // draw second tooth
}

// Draw Bottom Crusher
void DrawCrusherDown() {
  int offsetX = e2x;
  int offsetY = e2y;
  setfillstyle(1, WHITE);
  bar(e2x, offsetY + e2y, e2x + ew, offsetY + e2y + eh); // draw first tooth
  offsetX = offsetX + ew;
  bar(offsetX, offsetY + e2y + eh / 2, offsetX + ew, offsetY + e2y + eh); // draw gap
  offsetX = offsetX + ew;
  bar(offsetX, offsetY + e2y, offsetX + ew, offsetY + e2y + eh); // draw second tooth
}
