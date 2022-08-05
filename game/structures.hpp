  // Structures must be in another file because there are used in engine but must be user editable.  
 
 //player

    typedef struct{
        double x,y,z;  //Position
        double a;      // angle left-right
        double l;      // angle up-down
    }camera; camera Cam;

//rendering structures

    typedef struct{
        double x1,y1;
        double x2,y2;
        double d;
        int c;
        bool t;
        int txt;
    }walls; walls W[64];

    typedef struct{
        double ws,we;
        double z1,z2;
        double x,y;
        double d;
        int c1,c2;
        int surf[32000];
        int surface;
        int flip;
    }sectors; sectors S[64];
                                                                                                                                                                                                                                