

//player funtions

void move_player_forward(int speed,player* P ) {
    int dx=sin(torad(P->a))*speed;
    int dy=cos(torad(P->a))*speed;
    P->x+=dx*GetFrameTime(); P->y+=dy*GetFrameTime();
} 

void move_player_back(int speed,player* P ) {
    int dx=sin(torad(P->a))*speed;
    int dy=cos(torad(P->a))*speed;
    P->x-=dx*GetFrameTime(); P->y-=dy*GetFrameTime();
} 

void move_player_left(int speed,player* P ) {
    int dx=sin(torad(P->a))*speed;
    int dy=cos(torad(P->a))*speed;
    P->x-=dy*GetFrameTime(); P->y+=dx*GetFrameTime();
} 

void move_player_right(int speed,player* P ) {
    int dx=sin(torad(P->a))*speed;
    int dy=cos(torad(P->a))*speed;
    P->x+=dy*GetFrameTime(); P->y-=dx*GetFrameTime();
} 

void move_player_up(int speed,player* P ) {
            P->z -= speed*GetFrameTime();
} 

void move_player_down(int speed,player* P ) {
            P->z += speed*GetFrameTime();
} 

void rotate_player_left(int speed,player* P ) {
    P->a -= speed*(GetFrameTime());
    if (P->a < 0){
        P->a += 360;
    }
} 

void rotate_player_right(int speed,player* P ) {
    P->a += speed*(GetFrameTime());
    if (P->a > 359){
        P->a -= 360;
    }
} 

void rotate_player_up(int speed,player* P ) {
    P->l += speed*GetFrameTime();
} 

void rotate_player_down(int speed,player* P ) {
    P->l -= speed*GetFrameTime();
} 
