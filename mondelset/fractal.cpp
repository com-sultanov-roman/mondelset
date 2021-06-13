#include "fractal.h"
unsigned int OPTIMIZED_AREA_COLOR = 0x00ffff;
unsigned int BLACK = 0;
unsigned int WHITE = 0xffffff;


Frame::Frame(int dPower){
	this->dPower = dPower;
	this->d = (1 << dPower);
	matrix = new unsigned int* [d];
    for (int i = 0; i < d; i++) {
        matrix[i] = new unsigned int[d];
        memset(matrix[i], 200, d * sizeof(unsigned int));
    }
}

void Frame::setCenterCoord(double x, double y){
	this->centerX = x;
	this->centerY = y;
}

double Frame::compute_density()
{
    this->density = 0;
    for (int i = 0; i < this->d; i++)
        for (int j = 0; j < this->d; j++)
            if(this->matrix[i][j] == BLACK || this->matrix[i][j] == OPTIMIZED_AREA_COLOR)
                this->density++;
    this->density /= ((double)d * (double)d);
    return this->density;
}

double Frame::compute_difference(Frame* frame){
    if (this->d != frame->d) return -1.;
    unsigned int** matrix_ = frame->matrix;
    double difference = 0;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            if ((matrix_[i][j] == BLACK || matrix_[i][j] == OPTIMIZED_AREA_COLOR) && (matrix[i][j] == BLACK || matrix[i][j] == OPTIMIZED_AREA_COLOR)) continue;
            if (matrix_[i][j] == WHITE && matrix[i][j] == WHITE) continue;

            difference += 1.;
        }

    }

    this->error = difference / (d * d);
    return error;
}

void Frame::print_report(){
    cout << "algo: " << algo_name << " | d: " << d << " | spent time: " << spent_time << " | density: " << density << "| h: "<< h << endl;
}


void Frame::draw(){
    glBegin(GL_POINTS);
    double color;
    float r, g, b;
    unsigned char* components;
    for (int i = 0; i < d; ++i)
    {
        for (int j = 0; j < d; ++j)
        {   
            components = reinterpret_cast<unsigned char*>(&matrix[i][j]);
            r = components[0] / 255.;
            g = components[1] / 255.;
            b = components[2] / 255.;
            glColor3f(r, g, b);
            glVertex2d(4.0 / d * i - 2, 4.0 / d * j - 2);
        }
    }
    glEnd();
}

void Frame::clean(){
    for (int i = 0; i < d; i++) memset(matrix[i], 255, d * sizeof(unsigned int));
}

void Frame::del(){
    for (int i = 0; i < d; i++) delete matrix[i];
    delete matrix;
    matrix = nullptr;
}



inline unsigned int calculate(double x, double y){

    /*double val = 0.5 * (1 - cos(atan2(y, x - 0.25)));
    if ((x-0.25) *(x-0.25) + y * y <=  val * val) {
                return 0x000000;
    }
    if((x + 1)*(x + 1) + y * y < 0.062){
     
                return 0;
    }*/


    double xi = 0, yi = 0;
    double xii = 0, yii = 0;
    int grey = 2048;
    for (; grey >= 0; --grey) {
        xii = (xi - yi) * (xi + yi) + x;
        yii = 2 * xi * yi + y;

        if (xi * xi + yi * yi > 4) {
            
            return WHITE;
        }
        xi = xii;
        yi = yii;
    }
    return BLACK;
}

void test1(){
    int count = 100;
  
    Frame frame(10);
    FILE* f = fopen("C:\\Users\\Roman\\Desktop\\coursework\\analysis\\test12.csv", "w");

    fprintf(f, "%s", "Density,Time\n");

    double xc = 0, yc = 0;
    double h = 4.;
    if (f != nullptr) {
        for (int i = 0; i <= count; ++i) {
            algo_standart(complex<double>(xc, yc), h - i * 0.0395, &frame);
            frame.compute_density();
            fprintf(f, "%f,%d\n", frame.density, frame.spent_time);
            frame.print_report();
            frame.clean();
        }
        fclose(f);
    }
    
    else cout << "ERROOOOOOOOR!!!" << endl;
    
}

void test2() {
    int count = 100;

    Frame frame(10);
    Frame frame16(10);
    Frame frame32(10);
    Frame frame64(10);
    Frame frame128(10);
    Frame frame256(10);
    Frame frame512(10);

    FILE* f = fopen("C:\\Users\\Roman\\Desktop\\coursework\\analysis\\test2\\test21.csv", "w");

    fprintf(f, "%s", "Density,Time16,Time32,Time64,Time128,Time256,Time512,Error16,Error32,Error64,Error128,Error256,Error512\n");

    double xc = 0, yc = 0;
    double h = 4.;
    if (f != nullptr) {
        for (int i = 0; i <= count; ++i) {
            algo_standart(complex<double>(xc, yc), h - i * 0.0395, &frame);

            algo_opt(complex<double>(xc, yc), h - i * 0.0395, 4, &frame16);
            algo_opt(complex<double>(xc, yc), h - i * 0.0395, 5, &frame32);
            algo_opt(complex<double>(xc, yc), h - i * 0.0395, 6, &frame64);
            algo_opt(complex<double>(xc, yc), h - i * 0.0395, 7, &frame128);
            algo_opt(complex<double>(xc, yc), h - i * 0.0395, 8, &frame256);
            algo_opt(complex<double>(xc, yc), h - i * 0.0395, 9, &frame512);

            frame16.compute_difference(&frame);
            frame32.compute_difference(&frame);
            frame64.compute_difference(&frame);
            frame128.compute_difference(&frame);
            frame256.compute_difference(&frame);
            frame512.compute_difference(&frame);
           
            frame.compute_density(); 
            fprintf(f, "%f,%d,%d,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f\n", frame.density, 
                frame16.spent_time, frame32.spent_time, frame64.spent_time, frame128.spent_time, frame256.spent_time, frame512.spent_time,
                frame16.error, frame32.error, frame64.error, frame128.error, frame256.error, frame512.error);

            frame.print_report();
            frame16.print_report();
            frame32.print_report();
            frame64.print_report();
            frame128.print_report();
            frame256.print_report();
            frame512.print_report();

            frame.clean();
            frame16.clean();
            frame32.clean();
            frame64.clean();
            frame128.clean();
            frame256.clean();
            frame512.clean();
        }
        fclose(f);
    }

    else cout << "ERROOOOOOOOR!!!" << endl;
}

void test3() {
    int count = 100;

    Frame frame128(10);
    Frame frame256(10);
    Frame frame512(10);

    Frame frame(10);

    FILE* f = fopen("C:\\Users\\Roman\\Desktop\\coursework\\analysis\\test3\\test31.csv", "w");

    fprintf(f, "%s", "Density,Time128,Time256,Time512,Error128,Error256,Error512\n");

    double xc = 0, yc = 0;
    double h = 4.;
    if (f != nullptr) {
        for (int i = 0; i <= count; ++i) {
            algo_standart(complex<double>(xc, yc), h - i * 0.0395, &frame);

      
            algo_opt_ext(complex<double>(xc, yc), h - i * 0.0395, 7, &frame128);
            algo_opt_ext(complex<double>(xc, yc), h - i * 0.0395, 8, &frame256);
            algo_opt_ext(complex<double>(xc, yc), h - i * 0.0395, 9, &frame512);

            frame128.compute_difference(&frame);
            frame256.compute_difference(&frame);
            frame512.compute_difference(&frame);

            frame.compute_density();
            fprintf(f, "%f,%d,%d,%d,%f,%f,%f\n", frame.density,
                frame128.spent_time, frame256.spent_time, frame512.spent_time,
                frame128.error, frame256.error, frame512.error);

            frame.print_report();
           
            frame128.print_report();
            frame256.print_report();
            frame512.print_report();

            frame.clean();
      
            frame128.clean();
            frame256.clean();
            frame512.clean();
        }
        fclose(f);
    }

    else cout << "ERROOOOOOOOR!!!" << endl;
}

void test4(){
    int count = 100;

    Frame frame(10);
    Frame frame1(10);
    Frame frame2(10);

    FILE* f = fopen("C:\\Users\\Roman\\Desktop\\coursework\\analysis\\test4\\test41.csv", "w");
    FILE* input = fopen("C:\\Users\\Roman\\Desktop\\coursework\\analysis\\test4\\input__.txt", "r");

    fprintf(f, "%s", "Density,TimeA0,TimeA1,TimeA2,ErrorA1,ErrorA2, h\n");
    char c;
    int rows = 0;
    
    
    while ((c = fgetc(input))!=EOF) {
        if (c == '\n') {
            rows++;
        }
    }
    cout << endl << "rows: " << rows << endl;
    
    fclose(input);

    ifstream fin;
    fin.open("C:\\Users\\Roman\\Desktop\\coursework\\analysis\\test4\\input__.txt");

    double xc = 0, yc = 0;
    double h = 4.;
    if (f != nullptr) {
        for (int i = 0; i < rows-1; ++i) {
            cout << i << endl;
            fin >> xc >> yc >> h;


            algo_standart(complex<double>(xc, yc), h, &frame);
            algo_opt(complex<double>(xc, yc), h, 7, &frame1);
            algo_opt_ext(complex<double>(xc, yc), h, 7, &frame2);

            frame1.compute_difference(&frame);
            frame2.compute_difference(&frame);

            frame.compute_density();
            fprintf(f, "%f,%d,%d,%d,%f,%f,%f\n", frame.density,
                frame.spent_time, frame1.spent_time, frame2.spent_time,
                frame1.error, frame2.error, h);
            




            frame.print_report();
            frame1.print_report();
            frame2.print_report();

            frame.clean();
            frame1.clean();
            frame2.clean();
           
        }
        fclose(f);
    }

    else cout << "ERROOOOOOOOR!!!" << endl;
}

void input_data_prepare(ofstream fout){
    fout << center.real() << " " << center.imag() << " " << w << endl;
}

void make_comparasion(complex<double> center, double h, unsigned int dPower, unsigned int dPower_p){
    Frame frame_a1(dPower);
    Frame frame_a2(dPower);
    Frame frame_a3(dPower);
    
    /*algo_standart(center, h, &frame_a1);
    algo_opt(center, h, dPower_p, &frame_a2);
    algo_opt_ext(center, h, dPower_p, &frame_a3);*/
    thread t1(algo_standart, center, h, &frame_a1);
    thread t2(algo_opt, center, h, dPower_p, &frame_a2);
    thread t3(algo_opt_ext, center, h, dPower_p, &frame_a3);
    t1.join();
    t2.join();
    t3.join();
    frame_a2.compute_difference(&frame_a1);
    frame_a3.compute_difference(&frame_a2);
    
    cout << "*************************************************************************" << endl;
    frame_a1.print_report();
    frame_a2.print_report();
    frame_a3.print_report();
    cout << "*************************************************************************" << endl;

}

void algo_standart(complex<double> center, double h, Frame* frame){
    clock_t start = clock();
    frame->h = h;

    double x, y;
    double cx = center.real(), cy = center.imag();

    frame->setCenterCoord(cx, cy);

    double split_diameter = h / frame->d;
    double start_point_x = cx - h / 2;
    double start_point_y = cy - h / 2;

    for (int i = 0; i < frame->d; i++){
        for (int j = 0; j < frame->d; j++){
            x = start_point_x + split_diameter * i;
            y = start_point_y + split_diameter * j;
            frame->matrix[i][j] = calculate(x, y);
        }
    }
    frame->spent_time = (double)(clock() - start);
    frame->compute_density();
    frame->algo_name = "1";
}


void fill_area(int i_0, int j_0, int i_1, int j_1, Frame* frame, unsigned int const color, int offset) {
    unsigned int** matrix = frame->matrix;
    for (int i = i_0 * offset; i <= i_1 * offset; ++i) {
        for (int j = j_0 * offset; j <= j_1 * offset; ++j) {
            matrix[i][j] = color;
        }
    }
}

void post_processing(Frame * frame) {
   unsigned int ** matrix = frame->matrix;

   double x, y, cx, cy;
   double split_diameter = frame->h / frame->d;
   cx = frame->centerX - frame->h / 2.;
   cy = frame->centerY - frame->h / 2.;

    for (int i = 0; i < frame->d; ++i) {
        for (int j = 0; j < frame->d; ++j) {
            if (matrix[i][j] == OPTIMIZED_AREA_COLOR) {
                continue;
            }
            x = i * split_diameter + cx;
            y = j * split_diameter + cy;

            matrix[i][j] = calculate(x, y);

        }
    }
}

void algo_opt(complex<double> center, double h, int dPower_p, Frame* frame){
    clock_t start = clock();
    Frame mini_frame(dPower_p);
    algo_standart(center, h, &mini_frame);

    frame->h = h;
    frame->setCenterCoord(center.real(), center.imag());
    frame->dPower_p = dPower_p;

    unsigned int BLACK = 0;
    unsigned int** matrix = mini_frame.matrix;
    int offset = 1 << (frame->dPower - dPower_p);
    unsigned int color;

    for (int i = 1; i < mini_frame.d - 1; ++i) {
        for (int j = 1; j < mini_frame.d - 1; ++j) {
            color = matrix[i][j];
            if (matrix[i][j] == BLACK) {
                frame->matrix[i * offset][j * offset] = 0;
            }
            if (matrix[i - 1][j - 1] == BLACK &&
                matrix[i - 1][j] == BLACK &&
                matrix[i - 1][j + 1] == BLACK &&
                matrix[i][j - 1] == BLACK &&
                matrix[i][j] == BLACK &&
                matrix[i][j + 1] == BLACK &&
                matrix[i + 1][j - 1] == BLACK &&
                matrix[i + 1][j] == BLACK &&
                matrix[i + 1][j + 1] == BLACK)
            {
                fill_area(i - 1, j - 1, i + 1, j + 1, frame, OPTIMIZED_AREA_COLOR, offset);
                continue;
            }
        }
    }
    post_processing(frame);
    frame->spent_time = (double)(clock() - start);
    frame->compute_density();
    frame->algo_name = "2";
    mini_frame.del();
}

void algo_opt_ext(complex<double> center, double h, int dPower_p, Frame* frame) {
    clock_t start = clock();
    Frame mini_frame(dPower_p);
    algo_standart(center, h, &mini_frame);
   
    frame->h = h;
    frame->setCenterCoord(center.real(), center.imag());
    frame->dPower_p = dPower_p;

    unsigned int BLACK = 0;
    unsigned int** matrix = mini_frame.matrix;
    int offset = 1 << (frame->dPower - dPower_p);

    Frame temporary_frame(dPower_p);
    for (int i = 1; i < mini_frame.d - 1; ++i) {
        for (int j = 1; j < mini_frame.d - 1; ++j) {
            if (matrix[i - 1][j - 1] == BLACK &&
                matrix[i - 1][j] == BLACK &&
                matrix[i - 1][j + 1] == BLACK &&
                matrix[i][j - 1] == BLACK &&
                matrix[i][j] == BLACK &&
                matrix[i][j + 1] == BLACK &&
                matrix[i + 1][j - 1] == BLACK &&
                matrix[i + 1][j] == BLACK &&
                matrix[i + 1][j + 1] == BLACK)
            {
                temporary_frame.matrix[i][j] = BLACK;
                continue;
            }
        }
    }
    matrix = temporary_frame.matrix;
    for (int i = 1; i < mini_frame.d - 1; ++i) {
        for (int j = 1; j < mini_frame.d - 1; ++j) {
            if (matrix[i - 1][j - 1] == BLACK &&
                matrix[i - 1][j] == BLACK &&
                matrix[i - 1][j + 1] == BLACK &&
                matrix[i][j - 1] == BLACK &&
                matrix[i][j] == BLACK &&
                matrix[i][j + 1] == BLACK &&
                matrix[i + 1][j - 1] == BLACK &&
                matrix[i + 1][j] == BLACK &&
                matrix[i + 1][j + 1] == BLACK)
            {
                fill_area(i - 1, j - 1, i + 1, j + 1, frame, OPTIMIZED_AREA_COLOR, offset);
                continue;
            }
        }
    }
    post_processing(frame);

    frame->spent_time = (double)(clock() - start);
    frame->compute_density();
    frame->algo_name = "3";
    temporary_frame.del();
    mini_frame.del();
}

