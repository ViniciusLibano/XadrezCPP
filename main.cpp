#include <GL/glut.h>
#include <iostream>
#include <vector>

#define WIN_WIDTH 1024
#define WIN_HEIGHT 512

int ts=32,ps=16;

class Peca
{
public:
    int px,py;
    std::string time,nome;
    Peca(int px, int py, std::string time, std::string nome)
    {
        this->px=px; this->py=py; this->time=time; this->nome=nome;
    }
    void desenharPeca()
    {
        int x,y,xo,yo,ol=1;
        x=(this->px-1)*ts+(ps/2); y=(this->py-1)*ts+(ps/2);
        xo=x+ps; yo=y+ps;
        if(this->time=="branco")
        {
            glColor3f(0.0f,0.0f,0.0f);
                glBegin(GL_QUADS);
                glVertex2i(x ,yo);
                glVertex2i(x ,y );
                glVertex2i(xo,y );
                glVertex2i(xo,yo);
            glEnd();

            glColor3f(1.0f,1.0f,1.0f);
            glBegin(GL_QUADS);
                glVertex2i(x+ol ,yo-ol);
                glVertex2i(x+ol ,y+ol );
                glVertex2i(xo-ol,y+ol );
                glVertex2i(xo-ol,yo-ol);
            glEnd();
        }

        if(this->time=="preto")
        {
            glColor3f(1.0f,1.0f,1.0f);
            glBegin(GL_QUADS);
                glVertex2i(x ,yo);
                glVertex2i(x ,y );
                glVertex2i(xo,y );
                glVertex2i(xo,yo);
            glEnd();

            glColor3f(0.0f,0.0f,0.0f);
            glBegin(GL_QUADS);
                glVertex2i(x+ol ,yo-ol);
                glVertex2i(x+ol ,y+ol );
                glVertex2i(xo-ol,y+ol );
                glVertex2i(xo-ol,yo-ol);
            glEnd();
        }
    }
};

std::vector<Peca> pecas = {
    Peca(1,1,"branco","peao"),
    Peca(2,1,"branco","peao"),
    Peca(3,1,"branco","peao"),
    Peca(4,1,"branco","peao"),
    Peca(5,1,"branco","peao"),
    Peca(6,1,"branco","peao"),
    Peca(7,1,"branco","peao"),
    Peca(8,1,"branco","peao"),
    Peca(1,2,"branco","peao"),
    Peca(2,2,"branco","peao"),
    Peca(3,2,"branco","peao"),
    Peca(4,2,"branco","peao"),
    Peca(5,2,"branco","peao"),
    Peca(6,2,"branco","peao"),
    Peca(7,2,"branco","peao"),
    Peca(8,2,"branco","peao"),

    Peca(1,8,"preto","peao"),
    Peca(2,8,"preto","peao"),
    Peca(3,8,"preto","peao"),
    Peca(4,8,"preto","peao"),
    Peca(5,8,"preto","peao"),
    Peca(6,8,"preto","peao"),
    Peca(7,8,"preto","peao"),
    Peca(8,8,"preto","peao"),
    Peca(1,7,"preto","peao"),
    Peca(2,7,"preto","peao"),
    Peca(3,7,"preto","peao"),
    Peca(4,7,"preto","peao"),
    Peca(5,7,"preto","peao"),
    Peca(6,7,"preto","peao"),
    Peca(7,7,"preto","peao"),
    Peca(8,7,"preto","peao"),
};

void desenharTabuleiro()
{
    int x,y,xo,yo;
    for(y=0;y<8;y++)
    {
        for(x=0;x<8;x++)
        {
            xo=x*ts; yo=y*ts;
            if(y%2==0 && x%2==0){glColor3f(1.0f,1.0f,1.0f);}
            if(y%2==0 && x%2==1){glColor3f(0.0f,0.0f,0.0f);}
            if(y%2==1 && x%2==0){glColor3f(0.0f,0.0f,0.0f);}
            if(y%2==1 && x%2==1){glColor3f(1.0f,1.0f,1.0f);}
            glBegin(GL_QUADS);
                glVertex2i(xo   ,yo+ts);
                glVertex2i(xo   ,yo   );
                glVertex2i(xo+ts,yo   );
                glVertex2i(xo+ts,yo+ts);
            glEnd();
        }
    }
}

void desenharTodasPecas()
{
    for(int i=0;i<pecas.size();i++)
    {
        std::cout << pecas[i].time << std::endl;
        pecas[i].desenharPeca();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    desenharTabuleiro();
    desenharTodasPecas();
    glutSwapBuffers();
}

void btn(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}

void start()
{
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0,WIN_WIDTH,WIN_HEIGHT,0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIN_WIDTH,WIN_HEIGHT);
    glutCreateWindow("Xadrez");

    start();
    glutDisplayFunc(display);
    glutKeyboardFunc(btn);
    glutMainLoop();
    return 0;
}
