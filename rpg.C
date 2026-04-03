#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
    int vida;
    int ataque;
    int defesa;
    int nivel;
    int xp;
} Personagem;

void limpar() {
    system("cls"); 
}

void barraVida(int vida) {
    int i;
    int blocos = vida / 5;

    if (blocos > 20) blocos = 20; 
    printf("[");
    for (i = 0; i < blocos; i++) printf("#");
    for (; i < 20; i++) printf("-");
    printf("] %d HP\n", vida);
}

void atacar(Personagem *jogador, Personagem *inimigo) {
    int dano = (rand() % jogador->ataque) + 5;
    inimigo->vida -= dano;
    printf("\n⚔️ Você causou %d de dano!\n", dano);
}

void defender(Personagem *jogador) {
    jogador->defesa = 2;
    printf("\n🛡️ Defesa ativada!\n");
}

void curar(Personagem *jogador) {
    int cura = rand() % 15 + 10;
    jogador->vida += cura;
    printf("\n❤️ Você recuperou %d de vida!\n", cura);
}

void ataqueInimigo(Personagem *jogador, Personagem *inimigo) {
    int dano = rand() % inimigo->ataque + 5;
    
    if (jogador->defesa) {
        dano /= 2;
        jogador->defesa = 0;
    }

    jogador->vida -= dano;
    printf("💀 Inimigo causou %d de dano!\n", dano);
}

void ganharXP(Personagem *jogador) {
    jogador->xp += 20;
    
    if (jogador->xp >= 50) {
        jogador->nivel++;
        jogador->xp = 0;
        jogador->vida += 20;
        jogador->ataque += 5;
        printf("\n✨ LEVEL UP! Agora você é nível %d!\n", jogador->nivel);
    }
}


int main() {
    srand(time(NULL));

    Personagem jogador = {100, 20, 0, 1, 0};

  printf("⚔️ Tales Forest ⚔️\n");
    printf("Pressione ENTER...");
    getchar();

    while (jogador.vida > 0) {
        Personagem inimigo = {80 + rand()%40, 15 + rand()%10, 0, 1, 0};

        while (inimigo.vida > 0 && jogador.vida > 0) {
            limpar();

            printf("=== BATALHA ===\n");
            printf("Seu nível: %d | XP: %d\n", jogador.nivel, jogador.xp);
            
            printf("\nSua vida: ");
            barraVida(jogador.vida);

            printf("Vida do inimigo: ");
            barraVida(inimigo.vida);

            printf("\n1 - Atacar\n2 - Defender\n3 - Curar\n> ");
            int escolha;
            scanf("%d", &escolha);

            if (escolha == 1) atacar(&jogador, &inimigo);
            else if (escolha == 2) defender(&jogador);
            else if (escolha == 3) curar(&jogador);
            else printf("\nEscolha inválida!");

            if (inimigo.vida > 0) ataqueInimigo(&jogador, &inimigo);

            printf("\nPressione ENTER...");
            getchar();
            getchar();
        }

        if (jogador.vida > 0) {
            printf("\n🏆 Inimigo derrotado!\n");
            ganharXP(&jogador);
            printf("Pressione ENTER...");
            getchar();
            getchar();
        }
    }

    printf("\n💀 Fim de jogo...\n");
    return 0;
}