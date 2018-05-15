#include <allegro.h>
//objetos
struct obj {int wx,wy,x,y,w,h,dir;};
struct obj
    p = {42,0,14,23,42,44,4}, f[4];

//funções
void sair();
void fantasma();
void restart();
void mapa(int);
void control();
void fecha_programa();
enum{ MAINMENU, GAMESCREEN, TITLEHELP, TITLECREDITS, LOADING};
void mainmenu();
void titlecredits();
void titlehelp();
void gamescreen();
void titleload();

//Variáveis Globais
int sai    = 0;
int som = 0;
int vida = 0;
int vidas = 3;
int morre = 0;
int inicio = 0;
int fase1 = 0;
int width  = 1048;
int height = 670;
int map [31][28];
int comendo = 0;
volatile int exit_program;
int screen_state;

SAMPLE *ponto, *morto, *comecou, *fase;
BITMAP *buffer, *itens, *fundo, *menu, *cursor, *newgame, *help, *credits, *menuhelp, *menucredits;

int main() {

    //Iniciação
	allegro_init();
    install_keyboard();
    install_mouse();
	set_color_depth(32);
	set_window_title("O Kangaceiro");
	set_close_button_callback(sair);
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, width, height, 0, 0);

	exit_program = FALSE;
    LOCK_FUNCTION(fecha_programa);
    LOCK_VARIABLE(exit_program);
    set_close_button_callback(fecha_programa);

      screen_state = MAINMENU;

	//Variáveis Locais

	while (!exit_program)
	{
	    if(screen_state == MAINMENU)
            mainmenu();
        else if(screen_state == GAMESCREEN)
            gamescreen();
        else if(screen_state == TITLEHELP)
            titlehelp();
        else if(screen_state == TITLECREDITS)
            titlecredits();
        /*else if(screen_state == ENDGAME)
            titlend();*/
    }
    //Finalizacao
	return 0;
}
END_OF_MAIN();

void fecha_programa() { exit_program = TRUE; }
END_OF_FUNCTION(fecha_programa)

void gamescreen(){

    //Variáveis Locais
	buffer = create_bitmap(width, height);
	fundo = load_bitmap("img/mapaQuaseCerto.bmp", NULL);
	itens = load_bitmap("img/Servao.bmp", NULL);
	//f28 = load_font("f283.ttf", NULL, NULL);
	ponto = load_sample("som/comendo.wav");
	comecou = load_sample("som/comecou.mid");
	fase = load_sample("som/som.wav");
	int i;
	for (i = 0; i< 4; i++)
    {
        f[i].wx = 0;
        f[i].wy = 53 + i*41;
        f[i].x = 12 + i;
        f[i].y = 14;
        f[i].w = 40;
        f[i].h = 40;
        f[i].dir = 1;

    }

    mapa(1);
	while (!(sai || key[KEY_ESC]))
	{
	    draw_sprite(buffer, fundo, 5, 5);
		textprintf_ex(buffer, font, 980, 250, 0xffffff, -1,"%i", comendo);
		if(vida) control();
		mapa(0);
		if (vida || inicio) masked_blit(itens, buffer, p.wx, p.wy, p.x*28-8, p.y*21-7, p.w, p.h);
		for (i = 0; i < vidas; i++) masked_blit(itens, buffer, 84, 0, 820 + i*45, 600, 42, 44);
		fantasma();
		draw_sprite(screen, buffer, 0, 0);
		rest(100);
		clear(buffer);
		restart();
		//sons
		if (som == 2) {stop_sample(ponto); play_sample(ponto, 255, 128, 1000, 0);}
		som = 0;
	}

	//Finalização
	//destroy_font(f28);
	destroy_bitmap(itens);
	destroy_bitmap(fundo);
	destroy_bitmap(buffer);
	destroy_sample(ponto);
	destroy_sample(comecou);
	destroy_sample(fase);
}

void mainmenu(){

    //Variáveis Locais
	int exit_screen = FALSE;

	buffer = create_bitmap(width, height);
	menu = load_bitmap("img/telas/MenuPac.bmp", NULL);
	cursor = load_bitmap("img/cursor.bmp", NULL);
	newgame = load_bitmap("img/telas/newgame.bmp", NULL);
    help = load_bitmap("img/telas/help.bmp", NULL);
    credits = load_bitmap("img/telas/credits.bmp", NULL);

	//Game Loop
	while(!exit_program && !exit_screen)
    {
          draw_sprite(buffer, menu, 0, 0);

              if(mouse_x > 320 && mouse_x < 703 && mouse_y > 300 && mouse_y < 370)
                {

                    draw_sprite(buffer, newgame, 0, 0);

                    if(mouse_b == 1)
                        {
                            exit_screen = TRUE;
                            screen_state = GAMESCREEN;
                        }
                }
                else if(mouse_x > 320 && mouse_x < 703 && mouse_y > 400 && mouse_y < 472)
                    {
                        draw_sprite(buffer, help, 0 , 0);

                        if(mouse_b == 1)
                        {
                            exit_screen = TRUE;
                            screen_state = TITLEHELP;
                        }
                    }
                 else if(mouse_x > 320 && mouse_x < 703 && mouse_y > 505 && mouse_y < 570)
                    {
                        draw_sprite(buffer, credits, 0, 0);
                        if(mouse_b == 1)
                            {
                                exit_screen = TRUE;
                                screen_state = TITLECREDITS;
                            }
                    }
              draw_sprite(buffer, cursor, mouse_x-6, mouse_y);
              draw_sprite(screen, buffer, 0, 0);

              clear(buffer);

    }

    //Finalização
    destroy_bitmap(buffer);
    destroy_bitmap(menu);
    destroy_bitmap(cursor);
    destroy_bitmap(newgame);
    destroy_bitmap(help);
    destroy_bitmap(credits);


}

void titlehelp(){

    int exit_screen = FALSE;

    //BITMAPS
    buffer = create_bitmap(width, height);
    menuhelp = load_bitmap("img/telas/MenuHelp.bmp", NULL);
    cursor = load_bitmap("img/cursor.bmp", NULL);

    //LOOP

    while(!exit_program && !exit_screen)
    {
          draw_sprite(buffer, menuhelp, 0, 0);
          //rectfill(buffer, 20, 20, 75, 70, makecol(255,255,0));
          if(mouse_x > 20 && mouse_x < 75 && mouse_y > 20 && mouse_y < 70)
            {
                if(mouse_b == 1)
                    {
                        exit_screen = TRUE;
                        screen_state = MAINMENU;
                    }
            }
          draw_sprite(buffer, cursor, mouse_x-6, mouse_y);
          draw_sprite(screen, buffer, 0, 0);
          clear(buffer);
    }

  //finalizacao
  destroy_bitmap(buffer);
  destroy_bitmap(menuhelp);
  destroy_bitmap(cursor);
}

void titlecredits(){

    int exit_screen = FALSE;

    //BITMAPS
    buffer = create_bitmap(width, height);
    menucredits = load_bitmap("img/telas/MenuCredits.bmp", NULL);
    cursor = load_bitmap("img/cursor.bmp", NULL);

    //LOOP
    while(!exit_program && !exit_screen)
    {
              draw_sprite(buffer, menucredits, 0, 0);
              if(mouse_x > 20 && mouse_x < 75 && mouse_y > 20 && mouse_y < 70)
                {
                    if(mouse_b == 1)
                        {
                            exit_screen = TRUE;
                            screen_state = MAINMENU;
                        }
                }
              draw_sprite(buffer, cursor, mouse_x-6, mouse_y);
              draw_sprite(screen, buffer, 0, 0);
              clear(buffer);

    }
    //finalizacao
    destroy_bitmap(buffer);
    destroy_bitmap(menucredits);
    destroy_bitmap(cursor);

}

void restart(){
    if (morre || !vida) stop_sample(fase);
    if (inicio)
    {
        vida = vidas;
        rest(3000);
        inicio = 0;
        fase1 = 0;
    }
    if(key[KEY_SPACE] && !vida)
    {
        while(key[KEY_SPACE]); inicio = 1;
    }
    if (morre && vida)
    {
        int i;
        vida--;
        vidas--;
        stop_sample(fase);
        for (i = 0; i < 4; i++)
        {
            draw_sprite(buffer, fundo, 5, 5);
            mapa(0);
            draw_sprite(screen, buffer, 0, 0);
            rest(200);
            clear(buffer);
        }
    }
    if (inicio || morre)
    {
        if (!morre) mapa(1);
        p.x = 14;
        p.y = 23;
        p.dir = 4;
        morre = 0;
    }
}
void fantasma(){
    int i;
    for(i = 0; i<4 ; i++){
            //direita
            if (f[i].dir == 2 && map[f[i].y][f[i].x+1] == 1)
            {
                if(map[f[i].y-1][f[i].x] != 1 && map[f[i].y+1][f[i].x] != 1)
                {
                    (rand()%2) ? (f[i].dir = 1) : (f[i].dir = 3);
                }
                else (map[f[i].y-1][f[i].x] != 1) ? (f[i].dir = 1) : (f[i].dir = 3);
            }
            //esquerda
            if (f[i].dir == 0 && map[f[i].y][f[i].x-1] == 1)
            {
                if(map[f[i].y-1][f[i].x] != 1 && map[f[i].y+1][f[i].x] != 1)
                {
                    (rand()%2) ? (f[i].dir = 1) : (f[i].dir = 3);
                }
                else (map[f[i].y-1][f[i].x] != 1) ? (f[i].dir = 1) : (f[i].dir = 3);
            }
            //baixo
            if (f[i].dir == 3 && map[f[i].y+1][f[i].x] == 1)
            {
                if(map[f[i].y][f[i].x-1] != 1 && map[f[i].y][f[i].x+1] != 1)
                {
                    (rand()%2) ? (f[i].dir = 0) : (f[i].dir = 2);
                }
                else (map[f[i].y][f[i].x-1] != 1) ? (f[i].dir = 0) : (f[i].dir = 2);
            }
            //cima
            if (f[i].dir == 1 && map[f[i].y-1][f[i].x] == 1)
            {
                if(map[f[i].y][f[i].x-1] != 1 && map[f[i].y][f[i].x+1] != 1)
                {
                    (rand()%2) ? (f[i].dir = 0) : (f[i].dir = 2);
                }
                else (map[f[i].y][f[i].x-1] != 1) ? (f[i].dir = 0) : (f[i].dir = 2);
            }

                if(f[i].dir == 0 && map[f[i].y][f[i].x-1] != 1) f[i].x--; // esq
            else if(f[i].dir == 1 && map[f[i].y-1][f[i].x] != 1) f[i].y--; //cima
            else if(f[i].dir == 2 && map[f[i].y][f[i].x+1] != 1) f[i].x++; // dir
            else if(f[i].dir == 3 && map[f[i].y+1][f[i].x] != 1) f[i].y++; // baixo


    masked_blit(itens, buffer, f[i].wx, f[i].wy, f[i].x*28 - 8, f[i].y * 21 - 7, f[i].w, f[i].h);

    //colisão
    if(vidas && p.x == f[i].x && p.y == f[i].y)
    {
        morre = 1;
    }
    }

}
void control(){
    if (key[KEY_LEFT] && map [p.y][p.x-1] != 1) p.dir=0;
    if (key[KEY_UP] && map [p.y-1][p.x] != 1) p.dir=1;
    if (key[KEY_RIGHT] && map [p.y][p.x+1] != 1) p.dir=2;
    if (key[KEY_DOWN] && map [p.y+1][p.x] != 1) p.dir=3;

    if(p.dir == 0 && map [p.y][p.x-1] != 1) p.x--;
    if(p.dir == 1 && map [p.y-1][p.x] != 1) p.y--;
    if(p.dir == 2 && map [p.y][p.x+1] != 1) p.x++;
    if(p.dir == 3 && map [p.y+1][p.x] != 1) p.y++;

    //atravessando a tela
    if (p.x > 26 && p.dir) p.x =0;
    if (p.x < 1 && !p.dir) p.x = 27;


    //comendo as bolinhas
    if (map[p.y][p.x] == 2)
    {
        comendo++;
        som = 2;
        map[p.y][p.x] = 0;
    }

}
void mapa(int mod){
    int i, j;
    // numero 31 é vertical, e 28 horizontal. isso é para por os trocinhos dele comer
    char mp[31][28] =  {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                        {1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
                        {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
                        {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
                        {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
                        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                        {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
                        {1,2,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,2,1},
                        {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
                        {1,1,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1},
                        {1,1,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1},
                        {1,1,1,1,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,1,1,1,1},
                        {1,1,1,1,1,1,2,1,1,2,1,1,4,4,4,4,1,1,2,1,1,2,1,1,1,1,1,1},
                        {1,1,1,1,1,1,2,1,1,2,1,4,4,4,4,4,4,1,2,1,1,2,1,1,1,1,1,1},
                        {0,0,0,0,0,0,2,2,2,2,1,4,4,4,4,4,4,1,2,2,2,2,0,0,0,0,0,0},
                        {1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1},
                        {1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1},
                        {1,1,1,1,1,1,2,1,1,2,2,2,2,2,2,2,2,2,2,1,1,2,1,1,1,1,1,1},
                        {1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1},
                        {1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1},
                        {1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1},
                        {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
                        {1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,2,1},
                        {1,2,2,2,1,1,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,1,1,2,2,2,1},
                        {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
                        {1,1,1,2,1,1,2,1,1,2,1,1,1,1,1,1,1,1,2,1,1,2,1,1,2,1,1,1},
                        {1,2,2,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,2,2,1},
                        {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
                        {1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1},
                        {1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1},
                        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};


                        for (i=0; i<31;i++)
                        {
                            for(j=0; j<28; j++)
                            {
                                if (mod) map[i][j] = mp [i][j];
                                if (map [i][j] == 2) masked_blit(itens, buffer, 60, 10, j*28 + 10, i*21 + 16, 6, 6); //pontinhos
                            }

                        }





}
void sair(){sai= 1;}
END_OF_FUNCTION(sair);

