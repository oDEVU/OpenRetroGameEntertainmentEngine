  // Structures must be in another file because there are used in engine but must be user editable.    
  // This  is  writed  from  in  editor  code  editor  [im  mess  even  when  speling  C:] 
 
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
        float d;
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
        int surf[32000];
        int surface;
        int flip;
    }sectors; sectors S[64];
                                                                                                                                                                                                                                