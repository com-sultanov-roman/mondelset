#pragma once
#include "selection.h"
#include "fractal.h"
#include "main.h"
//#include <gmp.h>


#pragma warning (disable : 4996)




GLuint program;
GLint Unif_color;

GLint window;
GLint cnt;

int flag = 0;
int parametr = 7;

ofstream fout;

void drawFractal() {
    glUseProgram(program);
    float c_val[2] = { center.real(), center.imag() };
    //glUniform4fv(Unif_color, 1, red);
    glUniform2fv(::cnt, 1, c_val);
    glUniform2d(::cnt, center.real(), center.imag());
    glUniform1f(window, ::w);

    glBegin(GL_QUADS);
    glVertex2f(-2, -2);
    glVertex2f(-2, 2);
    glVertex2f(2, 2);
    glVertex2f(2, -2);
    glEnd();
    cout << ::center << " " << w << endl;
    glUseProgram(0);
    
 }

Frame frame(10);

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);//очищаем буфер


    
    if (flag==0) {
        drawFractal();
    }
    else if(flag==1){
        frame.clean();
        algo_opt(center, ::w, parametr, &frame);
        frame.draw();
        frame.print_report();
    }
    else if (flag == 2) {
        frame.clean();
        algo_opt_ext(center, ::w, parametr, &frame);
        frame.draw();
        frame.print_report();
    }
    else if (flag == 3) {
        frame.clean();
        algo_standart(center, ::w, &frame);
        frame.draw();
        frame.print_report();
    }
    //fout << center.real() << " " << center.imag() << " " << w << endl;

    glutSwapBuffers();//прорисовываем буфер на экран
    glFlush();
}





GLuint loadShader(const char *source, GLenum type) {
    GLuint shader = glCreateShader(type);
    GLint status, length;
    if (shader == 0) return 0;
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* buf = (char*)malloc(length); 
        glGetShaderInfoLog(shader, length, NULL, buf);
        cout << "Compile failure" << endl << buf << endl;
        free(buf);
        glDeleteShader(shader);
        return 0;
    }
    return shader;

}

GLint loadShaderFromFile(const char* fileName, GLenum type) {
    cout << "Loading: " << fileName << endl;
    FILE* file = fopen(fileName, "rb");
    if (!file) {
        cout << "Eroror opening: " << fileName << endl;
    }
    fseek(file, 0, SEEK_END);
    GLint size = ftell(file);
    if (size < 1) {
        fclose(file);
        cout << "Eroror loading file: " << fileName << endl;
    }
    char* buff = (char *)malloc(size + 1);
    fseek(file, 0, SEEK_SET);
    
    if (fread(buff, 1, size, file) != size) {
        fclose(file);
        delete(buff);
        cout << "Eroror loading file: " << fileName << endl;
        return 1;
    }
    fclose(file);
    buff[size] = '\0';
    GLuint shader = loadShader(buff, type);
    return shader;
}

void shaderInit(const char* path) {
    GLuint fragmentShader = loadShaderFromFile("fragment.txt", GL_FRAGMENT_SHADER);
    program = glCreateProgram();
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status != GL_TRUE)

    {

        int length;

        glGetProgramiv ( program, GL_INFO_LOG_LENGTH, &length );

        char * buf = (char *) malloc (length );

        // получаем сам лог

        glGetProgramInfoLog(program, length, NULL, buf);

        printf ("Link failure. %s ", buf); free (buf ); 
      

    }

    const char* unif_name_window = "window"; 
    const char* unif_name_center = "center"; 
    window = glGetUniformLocation(program, unif_name_window);
    cnt = glGetUniformLocation(program, unif_name_center);
   // cout << center << endl;
}


void keyboardHandler(unsigned char key, int x, int y) {
    
    if (key == 119) { // w
        ::center = complex<long double>(::center.real(), ::center.imag() + (::w / 10));
    }
    if (key == 97) { // a
        ::center = complex<long double>(::center.real() - ::w / 10, ::center.imag());
    }
    if (key == 100) { // d
        ::center = complex<long double>(::center.real() + ::w / 10, ::center.imag());
    }
    if (key == 115) { // s
        ::center = complex<long double>(::center.real(), ::center.imag() - ::w / 10);
    }
    if (key == 't') { // t
        //cout << "started..." << endl;
        //test1();
        flag += 1;
        flag %= 4;
        glutPostRedisplay();
        //cout << "...done" << endl;
    }
    if (key == '2') { // 2
        cout << "started..." << endl;
        test2();
        cout << "...done" << endl;
    }
    if (key == '3') { // 3
        cout << "started..." << endl;
        test3();
        cout << "...done" << endl;
    }
    if (key == '4') { // 4
        cout << "started..." << endl;
        test4();
        cout << "...done" << endl;
    }
    if (key == 'e') { // t
        cout << "started..." << endl;
        Frame f1(10), f2(10);
        algo_standart(center, w, &f1);
        algo_opt(center, w, 7, &f2);
        f2.compute_difference(&f1);
        cout << f2.error << endl;
        cout << "...done" << endl;
    }
    if (key == '-') { // t
        if (parametr > 4) {
            parametr--;
            cout << "the parametr has been reduced. Valuse: " << parametr << endl;
        }
    }
    if (key == '=') { // t
        if (parametr < 9) {
            parametr++;
            cout << "the parametr has been increased. Valuse: " << parametr << endl;
        }
    }
    glutPostRedisplay();
}

void mouseWheelFnc(int button, int dir, int i, int j) {
   
    

    if (dir == 1) {
        if (::w < 1e-5) {
            return;
        }
        ::w *= 0.80;
        //make_comparasion(center, w, 10, 7);
    }
    if (dir == -1) {
     
        if (::w > 15) {
            return;
        }
        ::w *= 1.20;
    }
    //center = complex(i * ::w / 1024 + center.real() - ::w / 2, j * ::w / 1024 + center.imag() - ::w / 2);
    glutPostRedisplay();
}

int main(int argc, char** argv)
{

    
    fout.open("C:\\Users\\Roman\\Desktop\\coursework\\analysis\\test4\\input.txt");
    
    glutInit(&argc, argv);//начальная инициализация окна
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);//установка режима отображения
    glutInitWindowSize(1024, 1024);//размер окна
    glutInitWindowPosition(0, 0);//начальная позиция на экране
    //вы заметили что вначале идут функции с приставкой glutInit...?, так вот они должны быть первыми, а потом уже все остальные ф-ии.
    glutCreateWindow("Window");//заголовок окна
    glClearColor(1.0, 1.0, 1.0, 0.0);//цвет фона

    //////////////////////////////////////////////////////////////////////

    GLenum glew_status = glewInit();

    if (glew_status != GLEW_OK) {
        cout << "error :((" << endl;
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
    }
    else {
        cout << "successed" << endl;
    }

    shaderInit("fragment.txt");
       
    ///////////////////////////////////////////////////////////////////////
    
    // настройка проекции, с этими двумя ф-ми познакомимся поближе чуть позже.
    glMatrixMode(GL_PROJECTION);//режим матрицы
    glLoadIdentity();//отчищает матрицу
    glutMouseFunc(mouseButtonHandler);
    glutMotionFunc(mouseMotionHandler);
    glutPassiveMotionFunc(passiveMouseMotion);
    glutKeyboardFunc(keyboardHandler);
    glutMouseWheelFunc(mouseWheelFnc);
   
    gluOrtho2D(-2, 2, -2, 2);//cоздаем пространство нашей сцены, в данном случае 3D пространство с высотой, шириной и глубиной в 200 едениц.
    glutDisplayFunc(display);//функция которой мы передаем имя функции для отрисовки окна. 
    
    glutMainLoop();//запускаем всё проинициализированное, проще говоря та же ф-я main, только в данном случае glut'овская ф-я main.

    fout.close();
    return 0;
}

