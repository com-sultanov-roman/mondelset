#pragma once
#include "selection.h"
#include "fractal.h"
#include <iomanip>



void mouseButtonHandler(int button, int status, int i, int j)
{
    complex<int> coord(i, j);

    if (button == LEFT_BUTTON_ACTION && status == BUTTON_PRESSED) {
        if (!draw_selection) draw_selection = true;
        from_selection_local = coord;
    }

    if (button == LEFT_BUTTON_ACTION && status == BUTTON_RELEASED) {
        //if (draw_selection) draw_selection = false;
        //to_selection_local = coord;

        //// HERE WE ARE CREATING A NEW FRAME
        //complex<double> from = convert_to_real_global(from_selection_local);
        //complex<double> to = convert_to_real_global(to_selection_local);
        //complex<double> center = findCentralPoint(from, to);
        //double window_size = max(abs(from.real() - to.real()),
        //                         abs(from.imag() - to.imag()));

        ////std::cout << std::setprecision(64) << fixed <<"from: " << from << ", " << "to: " << to <<endl <<" center: " << findCentralPoint(from, to) <<" win_size: " << window_size << ": " 
        //  //  << (window_size < 1e-14 ? "True" : "False") <<std::endl << "-----------------------------------" << endl;
        ////t = new thread(createFrame, 1024, window_size, center);
        //::w = window_size;
        //::center = center;
       
        ////createFrame(1024, window_size, center);
    }
    if (button == RIGHT_BUTTON_ACTION && status == BUTTON_RELEASED) {


        center = complex(i * ::w / 1024. + center.real() - ::w/2., -j * ::w / 1024. + center.imag() + ::w / 2.);

        glutSwapBuffers();
        glutPostRedisplay();

    }
}

void mouseMotionHandler(int i, int j)
{
    complex<int> coord(i, j);
    cout << coord << endl;
    if (draw_selection) {
        to_selection_local = coord;
        glutPostRedisplay();
    }
	
}
void passiveMouseMotion(int i, int j) {
   
   
    //glutPostRedisplay();
    /*cout << "z_i = " << frames.top().carr[i][j] <<" modul = "<< abs(frames.top().carr[i][j]) <<endl;
    cout << "color: " << (frames.top().points[i][j] == 0 ? "b" : "w") << " (" << i << ", " << j << ")" << endl;*/
}





