#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#define LARGURA 1280
#define ALTURA 720
#define TAM_PILHA 8

typedef struct Pilha{
	int itens[TAM_PILHA];
	int topo;
} Pilha;

void Cria(Pilha *p){
	p->topo = -1;
}

bool Vazia(Pilha *p){
	if (p->topo == -1)
		return true;
	else
		return false;
}

bool Cheia(Pilha *p){
	if (p->topo == TAM_PILHA - 1)
		return true;
	else
		return false;
}

void Empilha(Pilha *p, int x, bool *DeuCerto) {
	if (Cheia(p)) {
		*DeuCerto = false;
		return;
	}

	p->topo++;
	p->itens[p->topo] = x;
	*DeuCerto = true;
}

void Desempilha(Pilha *p, int *x, bool *DeuCerto) {
	if (Vazia(p)) {
		*DeuCerto = false;
		return;
	}

	*x = p->itens[p->topo];
	p->topo--;
	*DeuCerto = true;
}

bool clicou_dentro(ALLEGRO_BITMAP *botao, float x, float y, float mx, float my) { 
	float w = al_get_bitmap_width(botao);
	float h = al_get_bitmap_height(botao);
	return (mx >= x && mx <= x + w && my >= y && my <= y + h); //nao entendi o que essa linha faz
}

int main()
{
	float start_scale = 1.0f;
	float quit_scale = 1.0f;
	bool start_pressed = false;
	bool quit_pressed = false;

	bool playing = true;

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;

	al_init();
	al_install_mouse();
	al_init_image_addon();

	display = al_create_display(LARGURA, ALTURA);

	ALLEGRO_BITMAP *menu = al_load_bitmap("menu.png");
	ALLEGRO_BITMAP *start = al_load_bitmap("start.png");
	ALLEGRO_BITMAP *quit = al_load_bitmap("quit.png");

	float start_x = 436, start_y = 340;
	float quit_x = 436, quit_y = 490;

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_draw_bitmap(menu, 0, 0, 0);
	al_draw_bitmap(start, start_x, start_y, 0);
	al_draw_bitmap(quit, quit_x, quit_y, 0);
	al_flip_display();

	while (playing) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = false;
		}

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			float mx = event.mouse.x;
			float my = event.mouse.y;
			if (clicou_dentro(start, start_x, start_y, mx, my)) {
				ALLEGRO_BITMAP* fundo = al_load_bitmap("fundo.png");
				al_draw_bitmap(fundo, 0, 0, 0);
				al_flip_display();
			}
			else if (clicou_dentro(quit, quit_x, quit_y, mx, my))
				playing = false;
		}
	}

	al_destroy_bitmap(menu);
	al_destroy_bitmap(start);
	al_destroy_bitmap(quit);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);

	return 0;
}