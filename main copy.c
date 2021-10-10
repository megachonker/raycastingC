#include <stdio.h>
#include <UwU.h>

#include <math.h>


typedef struct Point {
    int x, y;
}Point;

typedef struct Rond{
    int radius;
    bool fill;
    Point centre;
}Rond;


void printpoint(Point monpoint){
    printf("==Point==\nx=%d\ny=%d\n",monpoint.x,monpoint.y);
}


void cleanclickront(Rond *liste,int size){
    if(UwU_getMouseButtons() & SDL_BUTTON(SDL_BUTTON_LEFT) ){
        for(int u = 0; u < size; u++){
            liste[u].centre.y=0;liste[u].centre.x=0;
            liste[u].radius=5;
        }
    }
}

Point cliqueCoord() {
    // if(! UwU_getMouseButtons() & SDL_BUTTON(SDL_MOUSEBUTTONUP)){
            UwU_wait(100);

   if(UwU_getMouseButtons() & SDL_BUTTON(SDL_BUTTON_RIGHT) ){
        int x,y;
        x=y=0;
        
        UwU_getMousePosition(&x, &y);
        x=10;y=90;
        Point ptsTemporaire = { .x = x, .y = y};

           return ptsTemporaire;
    // }

    }


}

void renderlist(Rond *liste,int longeur){
    int i=0;
    for(int i = 0; i < longeur;i++)
    {
        if( liste[i].centre.x == 0 && liste[i].centre.y == 0 ){
            return;
        }
        UwU_fillEllipse(liste[i].centre.x, liste[i].centre.y,liste[i].radius , liste[i].radius);
    }
}


int addpoint(Point *liste,int longeur){
    int i=0;
    for(int i = 0; i < longeur;i++)
    {
        if( liste[i].x == 0 && liste[i].x == 0 ){
            liste[i] = cliqueCoord();
            return i;
        }
    }
}

int distance(Point a,Point b){
    printf("%f",sqrt(((a.x-b.x)*(a.x-b.x))+(a.y-b.y)*(a.y-b.y)));
    return  30; //sqrt((b.x-b.y)*(b.x-b.y)); //sqrt(((a.x-b.x)*(a.x-b.x))+(a.y-b.y)*(a.y-b.y));
}

void addRond(Rond *listedesrond,int tailleliste){
    int decalage = addpoint(&listedesrond->centre,tailleliste);
    Point segondclique = cliqueCoord();
    listedesrond[decalage].radius=distance(listedesrond[decalage].centre,segondclique);
}

int main(void) {
        UwU_wait(100);
    UwU_createWindow("Fenètre1", 800, 600);
    int x,y;
    x=y=0;
    int longeur=20;

    Rond listrond[20]={0};
    listrond[0].centre.x = 1;
    listrond[0].centre.y = 1;

    while(UwU_isRunning()) {
        UwU_drawFPS();
        UwU_background(255,255,255);
        UwU_setColor(0,0,0);
        addRond(listrond,longeur);
        renderlist(listrond,longeur);
        cleanclickront(listrond,longeur);
        UwU_render();
    }
    UwU_closeWindow();
return 0;
}