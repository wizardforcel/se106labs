/*
 * File: Sierpinski.cpp
 * ----------------------
 * Student ID: 5110369009
 * Name: 张子辰
 * This file is the starter project for the Sierpinski Triangle problem.
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

#define GW_W 640
#define GW_H 480

const double SQRT3 = sqrt(3);

GWindow* win;

void drawTriangle(const GPoint &a, const GPoint &b, const GPoint &c);
void rdrawTriangle(int order, int max, const GPoint &a, const GPoint &b, const GPoint &c);


void drawTriangle(const GPoint &a, const GPoint &b, const GPoint &c) {
  win->drawLine(a, b);
  win->drawLine(b, c);
  win->drawLine(c, a);
}

void rdrawTriangle(int order, int max, const GPoint &a, const GPoint &b, const GPoint &c)
{
  if(order > max) return;

  //find middle points, named d, e, f
  GPoint d((a.getX() + b.getX()) / 2, (a.getY() + b.getY()) / 2); //left
  GPoint e((a.getX() + c.getX()) / 2, (a.getY() + c.getY()) / 2); //right
  GPoint f((b.getX() + c.getX()) / 2, (b.getY() + c.getY()) / 2); //down
  drawTriangle(d, e, f);

  rdrawTriangle(order + 1, max, a, d, e); //up
  rdrawTriangle(order + 1, max, b, d, f); //leftdown
  rdrawTriangle(order + 1, max, c, e, f); //rightdown

}

int main() {
  win = new GWindow(GW_W, GW_H);
  double len;
  do {
    len = getReal("Please input the length of edge: ");
    if(len <= 0) cout << "Try again." << endl;
  } while(len <= 0);
  int order;
  do {
    order = getInteger("Please input the order of the Sierpinski Triangle: ");
    if(order < 0) cout << "Try again." << endl;
  } while(order < 0);
  
  GPoint a(GW_W / 2, GW_H / 2 - len * SQRT3 / 4); //up
  GPoint b(GW_W / 2 - len / 2, GW_H / 2 + len * SQRT3 / 4); //leftdown
  GPoint c(GW_W / 2 + len / 2, GW_H / 2 + len * SQRT3 / 4); //rightdown
  drawTriangle(a, b, c);
  
  rdrawTriangle(1, order, a, b, c);

  delete win;
  return 0;
}
