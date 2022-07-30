 // Structures must be in another file because there are used in engine but must be user editable. 
 
 //player

    typedef struct{
        float x,y,z;  //Position
        float a;      // angle left-right
        float l;      // angle up-down
    }player; player P;

//rendering structures

    typedef struct{
        float x1,y1;
        float x2,y2;
        int c;
        bool t;
        int txt;
    }walls; walls W[64];

    typedef struct{
        float ws,we;
        float z1,z2;
        float x,y;
        float d;
        int c1,c2;
        bool t;
        int txtt;
        int txtb;
        int surf[32000];
        int surface;
    }sectors; sectors S[64];
