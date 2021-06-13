#pragma once
#include <GL\glew.h>
#include <GL\freeglut.h>

#include <stdio.h>
#include <iostream>
#include <stack>
#include <vector>
#include <complex>
#include <thread>
#include <algorithm>
#include <fstream>

#include <string.h>

#pragma warning (disable: 4996)

using namespace std;

inline double windowSizeW = 1024;
inline double windowSizeH = 1024;

inline double areaSizeW = 4;
inline double areaSizeH = 4;

inline int RIGHT_BUTTON_ACTION = 2;
inline int LEFT_BUTTON_ACTION = 0;

inline int BUTTON_PRESSED = 0;
inline int BUTTON_RELEASED = 1;

inline complex<int> from_selection_local;
inline complex<int> to_selection_local;

inline complex<double> from_selection_global;
inline complex<double> to_selection_global;

inline bool draw_selection = false;

inline complex<double> center(0, 0);
inline double w = 4.;

void drawFractal();

