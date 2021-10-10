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
    Point center;
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

void placeSegment(Segment mure){
    UwU_drawLine(mure.A.x,mure.A.y,mure.B.x,mure.B.y);
}

float norme(Point A, Point B){
    return sqrt(pow(B.x-A.x,2)+pow(B.y-A.y,2));
}

Point intersect(Segment A, Segment B){
    printf("\n++++++++++++++\nx1=%f,y1=%f\nx2=%f,y2=%f\nx3=%f,y3=%f\nx4=%f,y4=%f\n",A.A.x,A.A.y,A.B.x,A.B.y,B.A.x,B.A.y,B.B.x,B.B.y);
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

    // if (t > 1 || t < 0){
    //     return null;
    // }

    printf("s=%f\nt=%f",s,t);

    float x = A.A.x+s*(A.B.x-A.A.x);
    float y = A.A.y+s*(A.B.y-A.A.y);
    Point rep = {x,y};

    return rep;
}

void scan(Eye lanceur, Segment object){


    Point fc = psum(object.B,object.A);
    

    ptstest(object.B,'v');
    for(float var = 0; var < 40; var+=0.1){
        Point coef = {var , var}; 
        ptstest(pscal(coef,fc),'r');
        ptstest(psum(pscal(fc,coef),object.A),'b');
    }
    UwU_render();
    UwU_wait(100);
    // for(float i =0;i<2*3.14159265359;i+=lanceur.precision){
    //     //calcule les coordoner des point pour le cercle
    //     Point pCercleExterieur = {lanceur.center.x+lanceur.range*cos(i)
    //                             , lanceur.center.y+lanceur.range*sin(i)};


    //     // Point truc = psum(pCercleExterieur,fc);
    //     // ptstest(fc,'r');
    //     // if(pCercleExterieur.y>object.A.y && pCercleExterieur.x<object.A.x){
    //     //                     // CENTRE              
    //     //     Segment ligne = {lanceur.center , {0,0}};// pCercleExterieur.x,object.A.y}
    //     //     placeSegment(ligne);
    //     // }else{
    //     //     Segment ligne = {lanceur.center , pCercleExterieur};
    //     //     placeSegment(ligne);        
    //     // }

    //     UwU_wait(200);
    //     // UwU_render(); 
    // }
}

int main(void) {

    srand(time(NULL));
    int r = rand(); 

    UwU_createWindow("Fenètre1", 800, 600);

    Eye centre = {{400,300}, 200, 0.02};

    // int x = (test.B.y - test.A.y)/(test.A.x-test.B.x);
    // int y = (test.A.x*test.B.y-test.B.x*test.A.y)/(test.A.y-test.B.y);
    // printf("%d,%d",x,y);
    while(UwU_isRunning()) {
        Segment test = {rand()%600,rand()%600,rand()%600,rand()%600};
        Segment test2 = {rand()%600,rand()%600,rand()%600,rand()%600};
        UwU_background(255,255,255);
        UwU_setColor(0,0,0);

        if(intersect(test,test2).x != 0 && intersect(test,test2).y !=0){
            ptstest(intersect(test,test2),'v');
        }else{
            ptstest(intersect(test,test2),'r');
            UwU_background(200,150,255);
        }
        placeSegment(test);
        placeSegment(test2);
        UwU_render();
        UwU_wait(500);
        // scan(centre,test);
    }
    UwU_closeWindow();
return 0;
}