#pragma once

#include "common.h"







struct Frame {
	string algo_name;
	double centerX = 0;
	double centerY = 0;
	unsigned int** matrix;
	double error = 0;
	unsigned int dPower_p = 0;	// direction power parameter
	double h = 0;				// window height
	int dPower;					// direction power
	int d = 0;
	int spent_time = 0;
	double density = 0;
	Frame(int dPower);
	void setCenterCoord(double x, double y);
	double compute_density();
	double compute_difference(Frame *frame);
	void print_report();
	void draw();
	void clean();
	void del();
};

void input_data_prepare(ofstream *);
	

void make_comparasion(complex<double> center, double h, unsigned int dPower, unsigned int dPower_p);

void algo_standart(complex<double> center, double h, Frame *frame);
void algo_opt(complex<double> center, double h, int dPower_p, Frame *frame);

void algo_opt_ext(complex<double> cdenter, double h, int dPower_p, Frame *frame);
unsigned int calculate(double, double);


void test1();
void test2();
void test3();
void test4();



	

	

	

	 

	



