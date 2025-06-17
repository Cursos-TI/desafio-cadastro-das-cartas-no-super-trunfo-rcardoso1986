#include <stdio.h>
#include <string.h>

// Card structure to store attributes
typedef struct {
    char state;
    char code[4];
    char cityName[50];
    int population;
    float area;
    float gdp;
    int touristSpots;
    float populationDensity;
} Card;

// Calculate population density
float calculateDensity(int population, float area) {
    return population / area;
}

// Display card details
void displayCard(Card c, int cardNumber) {
    printf("\nCarta %d:\n", cardNumber);
    printf("Estado: %c\n", c.state);
    printf("Código: %s\n", c.code);
    printf("Nome da cidade: %s\n", c.cityName);
    printf("População: %d\n", c.population);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f bilhões BRL\n", c.gdp);
    printf("Número de pontos turísticos: %d\n", c.touristSpots);
}

// Show menu of attributes, skipping one if omit is set
void showMenu(int omit) {
    printf("Escolha um atributo:\n");
    if (omit != 1) printf("1 - População\n");
    if (omit != 2) printf("2 - Área\n");
    if (omit != 3) printf("3 - PIB\n");
    if (omit != 4) printf("4 - Número de pontos turísticos\n");
    if (omit != 5) printf("5 - Densidade demográfica\n");
    printf("Digite sua opção: ");
}

// Get attribute value from card by attribute choice
float getAttributeValue(Card c, int attribute) {
    switch (attribute) {
        case 1: return (float)c.population;
        case 2: return c.area;
        case 3: return c.gdp;
        case 4: return (float)c.touristSpots;
        case 5: return c.populationDensity;
        default: return 0.0f;
    }
}

// Get attribute name string by attribute choice
const char* getAttributeName(int attribute) {
    switch (attribute) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Número de pontos turísticos";
        case 5: return "Densidade demográfica";
        default: return "Atributo desconhecido";
    }
}

int main() {
    Card card1, card2;
    int level;

    printf("=== Jogo Super Trunfo ===\n");
    printf("Escolha o nível:\n");
    printf("1 - Novato (Cadastrar e Mostrar cartas)\n");
    printf("2 - Aventureiro (Comparar por 1 atributo)\n");
    printf("3 - Mestre (Comparar por 2 atributos)\n");
    printf("Digite o número do nível: ");
    scanf("%d", &level);

    if (level < 1 || level > 3) {
        printf("Nível inválido! Saindo do programa.\n");
        return 1;
    }

    if (level == 1) {
        // Register card 1
        printf("\nCadastro da Carta 1:\n");
        printf("Estado (letra de A a H): ");
        scanf(" %c", &card1.state);

        printf("Código da carta (ex: A01): ");
        scanf("%3s", card1.code);

        printf("Nome da cidade: ");
        getchar(); // limpar buffer
        fgets(card1.cityName, sizeof(card1.cityName), stdin);
        card1.cityName[strcspn(card1.cityName, "\n")] = 0; // remove \n

        printf("População: ");
        scanf("%d", &card1.population);

        printf("Área (km²): ");
        scanf("%f", &card1.area);

        printf("PIB (bilhões BRL): ");
        scanf("%f", &card1.gdp);

        printf("Número de pontos turísticos: ");
        scanf("%d", &card1.touristSpots);

        card1.populationDensity = calculateDensity(card1.population, card1.area);

        displayCard(card1, 1);

        // Register card 2
        printf("\nCadastro da Carta 2:\n");
        printf("Estado (letra de A a H): ");
        scanf(" %c", &card2.state);

        printf("Código da carta (ex: B02): ");
        scanf("%3s", card2.code);

        printf("Nome da cidade: ");
        getchar();
        fgets(card2.cityName, sizeof(card2.cityName), stdin);
        card2.cityName[strcspn(card2.cityName, "\n")] = 0;

        printf("População: ");
        scanf("%d", &card2.population);

        printf("Área (km²): ");
        scanf("%f", &card2.area);

        printf("PIB (bilhões BRL): ");
        scanf("%f", &card2.gdp);

        printf("Número de pontos turísticos: ");
        scanf("%d", &card2.touristSpots);

        card2.populationDensity = calculateDensity(card2.population, card2.area);

        displayCard(card2, 2);

        printf("\n--- Fim do nível Novato ---\n");
        return 0;
    }

    // Pré-cadastrar cartas para níveis 2 e 3
    card1.state = 'A';
    strcpy(card1.code, "A01");
    strcpy(card1.cityName, "Cidade Alpha");
    card1.population = 1000000;
    card1.area = 500.0;
    card1.gdp = 150.0;
    card1.touristSpots = 20;
    card1.populationDensity = calculateDensity(card1.population, card1.area);

    card2.state = 'B';
    strcpy(card2.code, "B02");
    strcpy(card2.cityName, "Cidade Beta");
    card2.population = 800000;
    card2.area = 450.0;
    card2.gdp = 180.0;
    card2.touristSpots = 25;
    card2.populationDensity = calculateDensity(card2.population, card2.area);

    displayCard(card1, 1);
    displayCard(card2, 2);

    if (level == 2) {
        int attr;
        printf("\nEscolha um atributo para comparar:\n");
        showMenu(0);
        scanf("%d", &attr);

        if (attr < 1 || attr > 5) {
            printf("Opção inválida!\n");
            return 1;
        }

        float val1 = getAttributeValue(card1, attr);
        float val2 = getAttributeValue(card2, attr);
        int winner;

        // Densidade demográfica: menor ganha, para os outros maior ganha
        if (attr == 5) {
            if (val1 < val2) winner = 1;
            else if (val2 < val1) winner = 2;
            else winner = 0;
        } else {
            if (val1 > val2) winner = 1;
            else if (val2 > val1) winner = 2;
            else winner = 0;
        }

        printf("\nComparando \"%s\" e \"%s\" pelo atributo \"%s\":\n", card1.cityName, card2.cityName, getAttributeName(attr));
        printf("%s: %.2f\n", card1.cityName, val1);
        printf("%s: %.2f\n", card2.cityName, val2);

        if (winner == 1)
            printf("Vencedor: %s\n", card1.cityName);
        else if (winner == 2)
            printf("Vencedor: %s\n", card2.cityName);
        else
            printf("Empate!\n");

        printf("\n--- Fim do nível Aventureiro ---\n");
        return 0;
    }

    if (level == 3) {
        int attr1 = 0, attr2 = 0;

        printf("\nEscolha o primeiro atributo para comparar:\n");
        showMenu(0);
        scanf("%d", &attr1);
        if (attr1 < 1 || attr1 > 5) {
            printf("Primeiro atributo inválido!\n");
            return 1;
        }

        printf("\nEscolha o segundo atributo (diferente do primeiro):\n");
        showMenu(attr1);
        scanf("%d", &attr2);
        if (attr2 < 1 || attr2 > 5 || attr2 == attr1) {
            printf("Segundo atributo inválido!\n");
            return 1;
        }

        float c1_val1 = getAttributeValue(card1, attr1);
        float c2_val1 = getAttributeValue(card2, attr1);
        float c1_val2 = getAttributeValue(card1, attr2);
        float c2_val2 = getAttributeValue(card2, attr2);

        int winner_attr1, winner_attr2;

        // Verifica vencedor atributo 1
        if (attr1 == 5) {
            if (c1_val1 < c2_val1) winner_attr1 = 1;
            else if (c2_val1 < c1_val1) winner_attr1 = 2;
            else winner_attr1 = 0;
        } else {
            if (c1_val1 > c2_val1) winner_attr1 = 1;
            else if (c2_val1 > c1_val1) winner_attr1 = 2;
            else winner_attr1 = 0;
        }

        // Verifica vencedor atributo 2
        if (attr2 == 5) {
            if (c1_val2 < c2_val2) winner_attr2 = 1;
            else if (c2_val2 < c1_val2) winner_attr2 = 2;
            else winner_attr2 = 0;
        } else {
            if (c1_val2 > c2_val2) winner_attr2 = 1;
            else if (c2_val2 > c1_val2) winner_attr2 = 2;
            else winner_attr2 = 0;
        }

        printf("\nComparando \"%s\" e \"%s\" pelos atributos \"%s\" e \"%s\":\n",
               card1.cityName, card2.cityName,
               getAttributeName(attr1), getAttributeName(attr2));
        printf("%s - %s: %.2f, %s: %.2f\n", card1.cityName,
               getAttributeName(attr1), c1_val1,
               getAttributeName(attr2), c1_val2);
        printf("%s - %s: %.2f, %s: %.2f\n", card2.cityName,
               getAttributeName(attr1), c2_val1,
               getAttributeName(attr2), c2_val2);

        // Decide vencedor final pela soma
        float sum1 = c1_val1 + c1_val2;
        float sum2 = c2_val1 + c2_val2;

        printf("Soma dos atributos para %s: %.2f\n", card1.cityName, sum1);
        printf("Soma dos atributos para %s: %.2f\n", card2.cityName, sum2);

        if (sum1 > sum2)
            printf("Vencedor: %s\n", card1.cityName);
        else if (sum2 > sum1)
            printf("Vencedor: %s\n", card2.cityName);
        else
            printf("Empate!\n");

        printf("\n--- Fim do nível Mestre ---\n");
        return 0;
    }

    return 0;
}
