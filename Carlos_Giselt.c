#include <ncurses.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

char ma[1000][1000]; //matriz
int puntos, i, j, n, m,puntaje;
int estado=0; //0=jugando, 1=perdido, 2=ganado
void *Refrescar(void*a);
WINDOW *mapa, *puntajeV;
sem_t sema;

//Carlos Martinez
//Giselt Parra


void *Refrescar(void*a){
	while(estado==0){
		sem_wait(&sema);
		for(i=0;i<n;i++){
			for(j=0;j<m;j++) mvwprintw(mapa,i,j, "%c", ma[i][j]);	
		}
		sem_post(&sema);
		wrefresh(mapa);
		mvwprintw(puntajeV,1,0, "PUNTAJE: %d", puntaje);
		wrefresh(puntajeV);	
		refresh();	
		sleep(0.5);
	}	

	pthread_exit(0);		
}


void* fantasma(void* identificador){
	int x,y,k,p_x,p_y,a,aa=' ';
	char id =*(char*) identificador;
	//Ubicar posicion
	for(i=0; i<n; i++){ for(j=0; j<m; j++){
		if(ma[i][j] == id){
			x = j;
			y = i;
			break;	

	}}}
	while(estado == 0){
		usleep(60000);
		sem_wait(&sema);
		k = rand()%4;
		//A la izquierda
		if (k==0){	
			p_x = x-1;
			if (ma[y][p_x] == '.'|| ma[y][p_x] == ' '){			
				a = ma[y][p_x];
				ma[y][p_x] = id;
				ma[y][x]= aa;
				aa = a;
				x = p_x;
			}
			else if(ma[y][p_x]=='P'){
				
				printf("Partida perdida\n");
				sleep(1);
				estado=1;
				endwin();
				exit(0);
				
			}
		}
		//A la derecha
		else if(k==1){
			p_x = x+1;
			if (ma[y][p_x] == '.'|| ma[y][p_x] == ' '){
				a = ma[y][p_x];
				ma[y][p_x] = id;
				ma[y][x]= aa;
				aa = a;
				x = p_x;
			}
			else if(ma[y][p_x]=='P'){	
				
				printf("Partida perdida\n");
				sleep(1);
				estado=1;
				endwin();
				exit(0);
					
			}
		}
		//Arriba
		else if(k==2){
			p_y = y-1;
			if (ma[p_y][x] == '.'|| ma[p_y][x] == ' '){
				a = ma[p_y][x];				
				ma[p_y][x] = id;
				ma[y][x]= aa;
				aa = a;
				y = p_y;
			}
			else if(ma[p_y][x]=='P'){
				
				printf("Partida perdida\n");
				sleep(1);
				estado=1;
				endwin();
				exit(0);
					
			}
		}
		//Abajo
		else if(k==3){
			p_y = y+1;
			if (ma[p_y][x] == '.' || ma[p_y][x] == ' '){
				a = ma[p_y][x];	
				ma[p_y][x] = id;
				ma[y][x]= aa;
				aa = a;
				y = p_y;
			}
			else if(ma[p_y][x]=='P'){

				
				printf("Partida perdida\n");
				sleep(1);
				estado=1;
				endwin();
				exit(0);
				
			}
		}
		//imprimir();
		sem_post(&sema);
	
	}
	pthread_exit(0);

}

void* p(void* identificador){
	int x,y,k,p_x,p_y,a,aa=' ';
	char id =*(char*) identificador;
	int mov;
	//Ubicar posicion
	for(i=0; i<n; i++){ for(j=0; j<m; j++){
		if(ma[i][j] == id){
			x = j;
			y = i;
			break;	

	}}}
	while(estado == 0){
		//usleep(6000);
		//sem_wait(&sema);
		mov = getch();
		//A la izquierda
		if (mov=='a') {	
			p_x = x-1;
			if(ma[y][p_x]=='*'){}//borde izquierdo
			if (ma[y][p_x] == '.'|| ma[y][p_x] == ' '){
				if(ma[y][p_x] == '.')puntaje++;			
				if(ma[y][p_x]=='.')puntos--;				
				ma[y][p_x] = id;
				ma[y][x]= ' ';
				x = p_x;
			}
			else if(ma[y][p_x]=='1' || ma[y][p_x]=='2'|| ma[y][p_x]=='3'|| ma[y][p_x]=='4' ){
				sleep(1);
				printf("Partida perdida\n");
				estado=1;
				endwin();
				exit(0);
				
			}
		}
		//A la derecha
		else if(mov=='d'){
			p_x = x+1;
			if(ma[y][p_x]=='*'){}//borde derecho
			if (ma[y][p_x] == '.'|| ma[y][p_x] == ' '){
				if(ma[y][p_x] == '.')puntaje++;	
				if(ma[y][p_x]=='.')puntos--;
				ma[y][p_x] = id;
				ma[y][x]= ' ';
				x = p_x;
			}
			else if(ma[y][p_x]=='1' || ma[y][p_x]=='2'|| ma[y][p_x]=='3'|| ma[y][p_x]=='4' ){	
				
				sleep(1);
				printf("Partida perdida\n");estado=1;
				endwin();
				exit(0);
					
			}
		}
		//Arriba
		else if(mov=='w'){
			p_y = y-1;
			if(ma[p_y][x]=='*'){}// adios violacion de segmentoooooooooooo
			else if (ma[p_y][x] == '.'|| ma[p_y][x] == ' '){	
				if(ma[p_y][x]=='.')puntos--;
				if(ma[p_y][x] == '.')puntaje++;			
				ma[p_y][x] = id;
				ma[y][x]= ' ';
				y = p_y;
			}
			else if(ma[y][p_x]=='1' || ma[y][p_x]=='2'|| ma[y][p_x]=='3'|| ma[y][p_x]=='4' ){
				sleep(1);
				printf("Partida perdida\n");
				estado=1;
				endwin();
				exit(0);
					
			}
			
		}
		//Abajo
		else if(mov=='s'){
			p_y = y+1;
			if(ma[p_y][x]=='*'){}// muro inferior
			else if (ma[p_y][x] == '.' || ma[p_y][x] == ' '){
				if(ma[p_y][x] == '.')puntaje++;
				if(ma[p_y][x]=='.')puntos--;
				ma[p_y][x] = id;
				ma[y][x]= ' ';
				y = p_y;
			}
			else if(ma[y][p_x]=='1' || ma[y][p_x]=='2'|| ma[y][p_x]=='3'|| ma[y][p_x]=='4' ){

				sleep(1);
				printf("Partida perdida\n");
				estado=1;
				endwin();
				exit(0);
				
			}
		}
		if (puntos == 0){
			printf("Partida ganada\n");
			sleep(1);
			estado=2;
			endwin();
			exit(0);

		}
	
	}
	pthread_exit(0);

}


int main(int argc, char const *argv[]){
	//Mapa
	FILE *pista = fopen(argv[3], "r");
	if(pista == NULL){
		printf("No existe el archivo\n");
		exit(-1);
	}

	//Ininializacion matriz
	n = atoi(argv[1]);
	m = atoi(argv[2]);
	// inicializando semaforo
 	sem_init(&sema,0,1);
	
	//Rellenando matriz	
	for(i=0;i<n;++i){ 
		for(j=0;j<m;++j){
			ma[i][j] = fgetc(pista);
			if(ma[i][j]=='.')puntos++;
		}	
	}		


	

	//Validacion para bordes del mapa
	for(i=0;i<n;++i){ 
		for(j=0;j<m;++j){
			if(i==0 && j!=m-1 && ma[i][j]!='*'){
				printf("Borde sin '*' o dimension incorrecta (asegurese de contar los saltos de linea)\n");	
				exit(0);}
			if(j==0 && i!=n-1 && ma[i][j]!='*'){
				printf("Borde sin '*' o dimension incorrecta (asegurese de contar los saltos de linea)\n");
				exit(0);}
			if(j==m && ma[i][j]!='*'){
				printf("Borde sin '*' o dimension incorrecta (asegurese de contar los saltos de linea)\n");	
				exit(0);}
			if(i==n-1 && j!=m-1 && ma[i][j]!='*'){
				printf("Borde sin '*' o dimension incorrecta (asegurese de contar los saltos de linea)\n");
				exit(0);}
		}
	}

	//NCURSES
	initscr(); // iniciar ncurses
	
	//Configuracion NCURSES
	noecho(); // quitamos keys
	curs_set(FALSE); // cursor pantalla

	
	//Ventana Mapa
	int height=n+30, width=m+30, start_X, start_Y;
	getmaxyx(stdscr, start_Y, start_X);
	 //crear ventana alto   ancho coordenadas vamos al centro
	mapa =newwin(height, width, 10,10);
	puntajeV = newwin(6, 50, 0, 0);
	
	pthread_t pacman,f1,f2,f3,f4,refrsh;
	//PACMAN
	pthread_create(&pacman, NULL, p, "P"); 

	//FANTASMA
	pthread_create(&f1, NULL, fantasma, "1");
	pthread_create(&f2, NULL, fantasma, "2");
	pthread_create(&f3, NULL, fantasma, "3");
	pthread_create(&f4, NULL, fantasma, "4");

	//INTERFAZ
	pthread_create(&refrsh, NULL, Refrescar, NULL);

		

	//FIN
	pthread_join(pacman, NULL);
	pthread_join(f1, NULL);
	pthread_join(f2, NULL);
	pthread_join(f3, NULL);
	pthread_join(f4, NULL);
	pthread_join(refrsh, NULL);
		
	
	return 0;
}
