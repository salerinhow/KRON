#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ===== STRUCT =====
typedef struct {
    int vida;
    int ataque;
    int defesa;
    int nivel;
    int xp;
    int classe;
    int pocao;
} Personagem;

// ===== FUNCOES =====
void limpar() {
    system("cls"); // Linux: clear
}

void barraVida(int vida) {
    int i;

    if (vida < 0) vida = 0;
    if (vida > 100) vida = 100;

    int blocos = (vida * 20) / 100;

    printf("[");
    for (i = 0; i < blocos; i++) printf("#");
    for (i = blocos; i < 20; i++) printf("-");
    printf("] %d HP\n", vida);
}

void atacar(Personagem *j, Personagem *i) {
    int dano = rand() % j->ataque + 5;
    i->vida -= dano;
    printf("\n[ATAQUE] Voce causou %d de dano!\n", dano);
}

void defender(Personagem *j) {
    j->defesa = 2;
    printf("\n[DEFESA] Defesa ativada!\n");
}

void curar(Personagem *j) {
    int cura = rand() % 15 + 10;
    j->vida += cura;
    if (j->vida > 100) j->vida = 100;
    printf("\n[CURA] Recuperou %d HP\n", cura);
}

void usarPocao(Personagem *j) {
    if (j->pocao > 0) {
        j->vida += 30;
        if (j->vida > 100) j->vida = 100;
        j->pocao--;
        printf("\n[POCAO] +30 HP\n");
    } else {
        printf("\n[ERRO] Sem pocoes!\n");
    }
}

// ===== SKILLS =====
void skill(Personagem *j, Personagem *i) {
    if (j->classe == 1) {
        int dano = rand() % 30 + 20;
        i->vida -= dano;
        printf("\n[SKILL] DEUS DA GUERRA! %d dano\n", dano);
    }
    else if (j->classe == 2) {
        int dano = rand() % 40 + 10;
        i->vida -= dano;
        printf("\n[SKILL] SURTO DE MANA! %d dano\n", dano);
    }
    else {
        int dano = rand() % 25 + 15;
        i->vida -= dano;
        printf("\n[SKILL] SMASHHHHH!!! %d dano\n", dano);
    }
}

void ataqueInimigo(Personagem *j, Personagem *i) {
    int dano = rand() % i->ataque + 5;

    if (j->defesa) {
        dano /= j->defesa;
        j->defesa = 0;
    }

    j->vida -= dano;
    printf("[INIMIGO] Causou %d dano\n", dano);
}

void ganharXP(Personagem *j) {
    int xpNecessario = j->nivel * 50;

    j->xp += 20;

    if (j->xp >= xpNecessario) {
        j->xp -= xpNecessario;
        j->nivel++;
        j->vida += 20;
        j->ataque += 5;

        printf("\n[LEVEL UP] Agora nivel %d\n", j->nivel);
    }
}

// ===== MAPA =====
void desenharMapa(char mapa[5][5]) {
    int i, k;
    for (i = 0; i < 5; i++) {
        for (k = 0; k < 5; k++) {
            printf("%c ", mapa[i][k]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));

    Personagem jogador;
    int classe;

    printf("==== EKOS: FURIA DA FLORESTA ====\n\n");

    printf("Escolha sua classe:\n\n");

    printf("1 - GUERREIRO\n");
    printf("   Vida alta | Ataque medio\n");
    printf("   Skill: DEUS DA GUERRA\n\n");

    printf("2 - MAGO\n");
    printf("   Vida baixa | Ataque alto\n");
    printf("   Skill: SURTO DE MANA\n\n");

    printf("3 - TANQUE\n");
    printf("   Vida muito alta | Defesa alta\n");
    printf("   Skill: SMASHHHHH\n\n");

    printf("> ");
    scanf("%d", &classe);

    if (classe == 1) {
        printf("\n[CLASSE] GUERREIRO\n");
        jogador = (Personagem){120, 15, 1, 1, 0, 1, 2};
    }
    else if (classe == 2) {
        printf("\n[CLASSE] MAGO\n");
        jogador = (Personagem){80, 25, 0, 1, 0, 2, 2};
    }
    else {
        printf("\n[CLASSE] TANQUE\n");
        jogador = (Personagem){150, 10, 2, 1, 0, 3, 2};
    }

    getchar(); getchar();

    int x = 2, y = 2;

    char mapa[5][5] = {
        {'.','.','.','.','.'},
        {'.','N','.','.','.'},
        {'.','.','P','.','.'},
        {'.','.','.','.','.'},
        {'.','.','.','.','.'}
    };

    while (jogador.vida > 0) {

        char comando;

        while (1) {
            limpar();
            printf("MAPA:\n\n");
            desenharMapa(mapa);

            printf("\nPocoes: %d\n", jogador.pocao);
            printf("WASD mover | Q sair\n> ");
            scanf(" %c", &comando);

            int nx = x, ny = y;

            if (comando == 'w' && y > 0) ny--;
            if (comando == 's' && y < 4) ny++;
            if (comando == 'a' && x > 0) nx--;
            if (comando == 'd' && x < 4) nx++;
            if (comando == 'q') return 0;

            if (mapa[ny][nx] == 'N') {
                printf("\n[NPC] Voce recebeu uma pocao!\n");
                jogador.pocao++;
                getchar(); getchar();
            }

            mapa[y][x] = '.';
            x = nx;
            y = ny;
            mapa[y][x] = 'P';

            if (rand() % 3 == 0) {
                printf("\n[ALERTA] Inimigo apareceu!\n");
                getchar(); getchar();
                break;
            }
        }

        Personagem inimigo = {80 + rand()%40, 15 + rand()%10, 0, 1, 0, 0, 0};

        while (inimigo.vida > 0 && jogador.vida > 0) {
            limpar();

            printf("===== BATALHA =====\n");
            printf("Nivel: %d | XP: %d/%d\n", jogador.nivel, jogador.xp, jogador.nivel * 50);

            printf("\nSua vida: ");
            barraVida(jogador.vida);

            printf("Vida inimigo: ");
            barraVida(inimigo.vida);

            printf("\n1 Atacar\n2 Defender\n3 Curar\n4 Skill\n5 Pocao\n> ");

            int e;
            scanf("%d", &e);

            if (e == 1) atacar(&jogador, &inimigo);
            else if (e == 2) defender(&jogador);
            else if (e == 3) curar(&jogador);
            else if (e == 4) skill(&jogador, &inimigo);
            else if (e == 5) usarPocao(&jogador);
            else printf("[ERRO] Opcao invalida!\n");

            if (inimigo.vida > 0)
                ataqueInimigo(&jogador, &inimigo);

            printf("\nPressione ENTER...");
            getchar(); getchar();
        }

        if (jogador.vida > 0) {
            printf("\n[VICTORIA] Inimigo derrotado!\n");
            ganharXP(&jogador);
            getchar(); getchar();
        }
    }

    printf("\n[FIM] GAME OVER\n");
    return 0;
}
