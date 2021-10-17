#include <stdio.h>
#include <UwU.h>

#include <math.h>

#include <time.h>
#include <stdlib.h>

#define PI 3.14159265359

#define X 1920
#define Y 1080

typedef struct Point {
    float x, y;
}Point;


//type color

typedef struct Texture {
    //Color color
    int nbhitx;//index du numero de colone // peut etre passer
    int nbhity;//intex de la hauteur //peut etre déduit 
}Texture;

typedef struct Segment {
    Point A,B;
    char color;
    //Texture
}Segment;

typedef struct Eye {
    Point centre;
    float fov;
    float dirrection;
    float range;
    float precision;
}Eye;


void rstcolor(){
    UwU_setColor(0,0,0);  
}

char intocolorchar(int value){
    switch (value)
    {
    case 0:
        return 'r';
        break;
    case 1:
        return 'v';
        break;
    case 2:
        return 'b';
        break;
    case 3:
        return 'n';
        break;
    default:
        return 'r';
        break;
    }
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
    case 'n':
        UwU_setColor(0,0,0);
        break;
    case 'w':
        UwU_setColor(255,255,255);
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

void printsegment(Segment monsegemnet){
    //printf("\n============\nax=%f\nay=%f\nbx=%f\nby=%f\n",monsegemnet.A.x,monsegemnet.A.y,monsegemnet.B.x,monsegemnet.B.y);
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
    color(mure.color);
    UwU_drawLine(mure.A.x,mure.A.y,mure.B.x,mure.B.y);
    rstcolor();   
}

void placeListeSegment(Segment *liste,int taille){
    for(int u =0 ; u < taille; u++){
        placeSegment(liste[u]);
    }
}

float norme(Point A, Point B){
    return sqrt(pow(B.x-A.x,2)+pow(B.y-A.y,2));
}

float normevecteur(Segment A){
    return norme(A.A,A.B);
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

void colone(float largeur,float longeur,int distancerandu,char couleur){
    longeur=((distancerandu/longeur)-1)*40;
    int ofset = Y/2;
    Segment lignepixelvertical = {largeur,ofset-longeur,largeur,longeur+ofset,couleur};
    //printsegment(lignepixelvertical);
    placeSegment(lignepixelvertical);

}

int scan(Eye lanceur, Segment *object,int taille){
    int exitcode = 0;
    float angledepar    = 2*PI*(lanceur.dirrection-lanceur.fov/2)/360;
    float anglearriver  = 2*PI*(lanceur.dirrection+lanceur.fov/2)/360;
    // printf("anglearriver %f \nangledepar %f",anglearriver,angledepar);
    for(float i = angledepar;i<anglearriver;i+=lanceur.precision){
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
                    rayon.color=object[u].color;
            }
        }
        //on verifie si le rayon a toucher un truc au final
        // if(!pcompegal(rayon.A,pCercleExterieur)){
        //     ptstest(rayon.A,'r');//si oui alor on fait le boom
        // }
        // on met a 0 en enlever l'angle et on fait la proportion des pixel
        float base = (i-angledepar)/(lanceur.precision); 
        //on fait en sorte que tout l'écrant est utiliser pour afficher 
        float coef = X/((anglearriver-angledepar)/(lanceur.precision));
        float total = base * coef; //jsp le 2
        // printf("====\nvaleur base:%f\ncoef%f\ntotal %f\n",base,coef,total);
        if(normevecteur(rayon)<220){
            exitcode = 1;
        }
        colone(total, normevecteur(rayon),lanceur.range,rayon.color);
        // placeSegment(rayon);
        // UwU_render(); 
        // UwU_wait(5);
    }
    return exitcode;
}


void benchmark(){
    Segment test = {{rand()%Y,rand()%Y},{rand()%Y,rand()%Y}};
    Segment test2 = {{rand()%Y,rand()%Y},{rand()%Y,rand()%Y}};
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

//on check pas la taille du tableaux de mur allor qu'il faut au minimum 4   ! 
void initbordure(Segment *mureliste){
        Segment monsegement ={ {0,0}, {X,0},'n'};
        mureliste[0] = monsegement;
        Segment monsegement1 ={ {0,0}, {0,Y},'n'};
        mureliste[1] = monsegement1;
        Segment monsegement2 ={ {X,0}, {X,Y},'n'};
        mureliste[2] = monsegement2;
        Segment monsegement3 ={ {0,Y}, {X,Y},'n'};
        mureliste[3] = monsegement3;
}

void initrandomlisteobject(Segment *trairandom, int taille){
    for(int i=0; i<taille;i++){
        Segment monsegement ={{rand()%X,rand()%Y},{rand()%X,rand()%Y},intocolorchar(rand()%3)};
        trairandom[i] = monsegement;
    }
    initbordure(trairandom);
}

int validitermur(Point center,Segment *listemure,int nbmur){
    Eye parametre = {center,360,0, sqrt(X*X+Y*Y), 0.1};
    int value = scan(parametre,listemure,nbmur);
    printf("retoure %d",value);
    return value;
}

int main(void) {
    static int nombreDeMure=4+10;

    srand(time(NULL));
    UwU_createWindow("Bime", X, Y);
    //le faire bouger ces win
    Point centre =  {X/2,Y/2};
    Eye millieux = {centre,90,-90, sqrt(X*X+Y*Y), 0.0007};
    // printf("%d,%d",x,y);
    while(UwU_isRunning()) {
        UwU_background(255,255,255);
        UwU_setColor(0,0,0);

        //on genere des "mure" random
        Segment trairandom[nombreDeMure];
        initrandomlisteobject(trairandom,nombreDeMure);

        //si mes mure ne sont pas trop pres ou trop loin
        if (validitermur(centre,trairandom,nombreDeMure)==0)
        {
            int angledepart = millieux.dirrection;
            for(float rotation = 0; rotation < 270; rotation+=1){
                UwU_background(255,255,255);
                //on place une liste de segement pour l'affichage
                // placeListeSegment(trairandom,nombreDeMure);
                millieux.dirrection=angledepart + rotation;
                int retour = scan(millieux,trairandom,nombreDeMure);
                UwU_wait(10);
                UwU_render();
            }
            printf("ouis");
        }
        else{printf("non");}
    }
    UwU_closeWindow();
return 0;
}