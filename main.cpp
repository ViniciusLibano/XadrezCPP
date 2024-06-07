#include <GL/glut.h>
#include <iostream>
#include <vector>

#define WIN_WIDTH 1024
#define WIN_HEIGHT 512
#define NULL '\0'

int ts=32,ps=16;

void renderizarTexto(int x,int y, char *str)
{
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1.0f,1.0f,1.0f);
    glRasterPos2i(x,y);
    for (char *txt=str;*txt!=NULL;txt++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *txt);
    }
}

class Peca
{
public:
    int px,py;
    std::string time,nome,estado;
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
    Peca(1,1,"branco","torre"),
    Peca(2,1,"branco","cavalo"),
    Peca(3,1,"branco","bispo"),
    Peca(4,1,"branco","rei"),
    Peca(5,1,"branco","dama"),
    Peca(6,1,"branco","bispo"),
    Peca(7,1,"branco","cavalo"),
    Peca(8,1,"branco","torre"),

    Peca(1,2,"branco","peao"),
    Peca(2,2,"branco","peao"),
    Peca(3,2,"branco","peao"),
    Peca(4,2,"branco","peao"),
    Peca(5,2,"branco","peao"),
    Peca(6,2,"branco","peao"),
    Peca(7,2,"branco","peao"),
    Peca(8,2,"branco","peao"),

    Peca(1,8,"preto","torre"),
    Peca(2,8,"preto","cavalo"),
    Peca(3,8,"preto","bispo"),
    Peca(4,8,"preto","rei"),
    Peca(5,8,"preto","dama"),
    Peca(6,8,"preto","bispo"),
    Peca(7,8,"preto","cavalo"),
    Peca(8,8,"preto","torre"),

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
        //std::cout << pecas[i].time << std::endl;
        pecas[i].desenharPeca();
    }
}

void selecionarPeca(int cx, int cy)
{
    for (int i=0;i<pecas.size();i++)
    {
        if(cx>=pecas[i].px && cx<=pecas[i].px+ps && cy>=pecas[i].py && cy<=pecas[i].py+ps)
        {
            std::cout << pecas[i].nome << std::endl;
            renderizarTexto(300,50,(char*)pecas[i].nome.c_str());
            return;
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    desenharTabuleiro();
    desenharTodasPecas();
    renderizarTexto(400,50,"Teste");
    glutSwapBuffers();
}

void btn(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}


void click(int b, int s, int x, int y)
{
    if(b==GLUT_LEFT_BUTTON && s==GLUT_DOWN){std::cout<<x<<"\n"<<y<<std::endl; selecionarPeca(x,y);}
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
    glutMouseFunc(click);
    glutMainLoop();
    return 0;
}
