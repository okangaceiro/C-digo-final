void fantasmas()
{

  int i;

  for(i=0; i<4; i++)
  {

    //FANTASMAS ATRAVESSANDO A TELA (NO PONTO)
    if(f[i].x < 1)
    {
      f[i].x = 27;
    } 
    else if(f[i].x > 26 && f[i].dir == 2)
    { 
      f[i].x = 1;
    } 
    
    //Sr. de Engenho = perseguidor
    
    else if(i==3 && f[3].x < p.x && f[3].dir != 0 && map[f[3].y][f[3].x+1] != 1) f[3].dir = 2;
    else if(i==3 && f[3].x > p.x && f[3].dir != 2 && map[f[3].y][f[3].x-1] != 1) f[3].dir = 0;
    else if(i==3 && f[3].x < p.x && f[3].dir != 1 && map[f[3].y+1][f[3].x] != 1) f[3].dir = 3;
    else if(i==3 && f[3].x > p.x && f[3].dir != 3 && map[f[3].y-1][f[3].x] != 1) f[3].dir = 1;

    //Curupira = fica um pouco longe do Kangaceiro
    else if(i==2 && f[2].x < p.x+16 && f[2].dir != 0 && map[f[2].y][f[2].x+1] != 1) f[2].dir = 2;
    else if(i==2 && f[2].x > p.x+16 && f[2].dir != 2 && map[f[2].y][f[2].x-1] != 1) f[2].dir = 0;
    else if(i==2 && f[2].x < p.x+16 && f[2].dir != 1 && map[f[2].y+1][f[2].x] != 1) f[2].dir = 3;   
    else if(i==2 && f[2].x < p.x+16 && f[2].dir != 3 && map[f[2].y-1][f[2].x] != 1) f[2].dir = 1;

    //Lobisomem = tenta imitar a posição do Kangaceiro
    else if(i==1 && f[1].x < p.x-8 && f[1].dir != 0 && map[f[1].y][f[1].x+1] != 1) f[1].dir = 2;
    else if(i==1 && f[1].x > p.x-8 && f[1].dir != 2 && map[f[1].y][f[1].x-1] != 1) f[1].dir = 0;
    else if(i==1 && f[1].x < p.x-8 && f[1].dir != 1 && map[f[1].y+1][f[1].x] != 1) f[1].dir = 3;
    else if(i==1 && f[1].x > p.x-8 && f[1].dir != 3 && map[f[1].y-1][f[1].x] != 1) f[1].dir = 1;

    //Boitatá = anda aleatoriamente pelo mapa, funcao já implementada






  }



}
