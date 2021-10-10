#include <stdio.h>
#include <UwU.h>

#include <math.h>

#include <time.h>
#include <stdlib.h>

typedef struct Point {
    float x, y;
}Point;

typedef struct Segment {
    Point A,B;
}Segment;

typedef struct Eye {
    Point centre;
    float range;
    float precision;
}Eye;


void rstcolor(){
    UwU_setColor(0,0,0);  
}

void color(char c){
    switch (c)
    {
    case 'r':
        UwU_setColor(255,0,0);
        break;
    case 'v':
        UwU_setColor(0,255,0);
        break;
    case 'b':
        UwU_setColor(0,0,255);
        break;
    default:
        UwU_setColor(0,0,0);
        break;
    }
}

void ptstest(Point point, char c){
    color(c);
    UwU_fillEllipse(point.x,point.y,10,10);
    rstcolor();
}

Point pscal(Point A,Point B){
    Point resultat = {(A.x*B.x),A.y*B.y};
    return resultat; 
}

Point psum(Point A, Point B){
    Point out = {B.x-A.x, B.y-A.y};
    return out;
}

Point padd(Point A, Point B){
    Point out = {B.x+A.x, B.y+A.y};
    return out;
}

bool pcompegal(Point A, Point B){
    if(A.x == B.x && A.y == B.y){
        return true;
    }
    return false;
}



void placeSegment(Segment mure){
    UwU_drawLine(mure.A.x,mure.A.y,mure.B.x,mure.B.y);
}

void placeListeSegment(Segment *liste,int taille){
    for(int u =0 ; u < taille; u++){
        placeSegment(liste[u]);
    }
}

float norme(Point A, Point B){
    return sqrt(pow(B.x-A.x,2)+pow(B.y-A.y,2));
}

Point intersect(Segment A, Segment B){
    // printf("\n++++++++++++++\nx1=%f,y1=%f\nx2=%f,y2=%f\nx3=%f,y3=%f\nx4=%f,y4=%f\n",A.A.x,A.A.y,A.B.x,A.B.y,B.A.x,B.A.y,B.B.x,B.B.y);
    //utiliser les multiplication est soustraction de point dirrectemetn

    float s1=A.B.x-A.A.x;
    float t1=B.B.x-B.A.x;
    float s2=A.B.y-A.A.y;
    float t2=B.B.y-B.A.y;

    float r1=B.A.x-A.A.x;
    float r2=B.A.y-A.A.y;


    // s1-t1 == r1;
    // s2-t2 == r2;
    
    Point null = {0,0};

    if(s1*t2-s2*t1 == 0){
        return null;
    }

    // printf("\n==============\nr1=%f\nr2=%f\ns1=%f\ns2=%f\nt1=%f\nt2=%f\n",r1,r2,s1,s2,t1,t2);
    float s = (r1*t2-r2*t1)/(s1*t2-s2*t1);
    float t = (s1*r2-s2*r1)/(s1*t2-s2*t1);

    if (s > 1 || s < 0){
        return null;
    }

    if (-t > 1 || -t < 0){
        return null;
    }

    // printf("s=%f\nt=%f",s,t);

    float x = A.A.x+s*(A.B.x-A.A.x);
    float y = A.A.y+s*(A.B.y-A.A.y);
    Point rep = {x,y};

    return rep;
}

void scan(Eye lanceur, Segment *object,int taille){

    for(float i =0;i<2*3.14159265359;i+=lanceur.precision){
        //calcule les coordoner des point pour le cercle
        Point pCercleExterieur = {lanceur.centre.x+lanceur.range*cos(i)
                                , lanceur.centre.y+lanceur.range*sin(i)};

        Segment rayon = {pCercleExterieur,lanceur.centre};
        

        //lol on testera tout les objet le la map LA FAMEUSE OPTIMISATION
        for(int u = 0; u<taille;u++){
            Point touche = intersect(rayon,object[u]);
            //wtf ces censer etre l'inverse ...
            if( touche.x != 0 && touche.y != 0 ){
                //on verifie que lobjet qui a toucher est bien plus proche que le precedant 
                    rayon.A = touche;   //si oui allor le pron rayon lancer sera plus cour ect 
            }
        }
        //on verifie si le rayon a toucher un truc au final
        if(!pcompegal(rayon.A,pCercleExterieur)){
            ptstest(rayon.A,'r');//si oui alor on fait le boom
        }

        placeSegment(rayon);
        UwU_render(); 
        UwU_wait(5);
    }
}


void benchmark(){
    Segment test = {{rand()%600,rand()%600},{rand()%600,rand()%600}};
    Segment test2 = {{rand()%600,rand()%600},{rand()%600,rand()%600}};
    if(intersect(test,test2).x != 0 && intersect(test,test2).y !=0){
        UwU_background(255,255,255);
        ptstest(intersect(test,test2),'v');
    }else{
        UwU_background(200,150,255);
        ptstest(intersect(test,test2),'r');

    }
    placeSegment(test);
    placeSegment(test2);
    UwU_render();
}

void initrandomlisteobject(Segment *trairandom, int taille){
    for(int i=0; i<taille;i++){
        Segment monsegement ={{rand()%800,rand()%600},{rand()%800,rand()%600}};
        trairandom[i] = monsegement;
    }
}

int main(void) {
    static int nombreDeMure=5;

    srand(time(NULL));
    UwU_createWindow("Fenètre1", 800, 600);

    Eye millieux = {{400,300}, 300, 0.02};
    // printf("%d,%d",x,y);
    while(UwU_isRunning()) {
        UwU_background(255,255,255);
        UwU_setColor(0,0,0);

        //on genere des "mure" random
        Segment trairandom[nombreDeMure];
        initrandomlisteobject(trairandom,nombreDeMure);


        //on place une liste de segement pour l'affichage
        placeListeSegment(trairandom,nombreDeMure);

        scan(millieux,trairandom,nombreDeMure);
 
        
        UwU_render();
        UwU_wait(300);
        // scan(centre,test);
    }
    UwU_closeWindow();
return 0;
}