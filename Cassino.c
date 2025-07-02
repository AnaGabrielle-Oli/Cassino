#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
	char nome[50];
	char senha[16];
	char saldo[20];
	int apostas;
	int *chave_secreta;	
}Jogador;

Jogador jog;

typedef struct{
	float saldoDescript;
	float valorRecebido;
}JogadorDescript;

JogadorDescript jogD;

float valorGasto;

void criptografia(char userDados[]){
	char letra[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9'};

	for (int i = 0; userDados[i] != '\0'; i++) {
		for (int j = 0; j < 36; j++) {
			if (userDados[i] == letra[j]) {
				userDados[i] = letra[(j + 3) % 36];
				break;
			}
    	}    
    }
}

void desCriptografia(char userDados[], float *dadoDescript){
	char copia[20];
    strcpy(copia, userDados);
	char *fimptr;
	
	char letra[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9'};

	for (int i = 0; copia[i] != '\0'; i++) {
		for (int j = 0; j < 36; j++) {
			if (copia[i] == letra[j]) {
				copia[i] = letra[(j + 36 - 3) % 36];
				break;
			}
    	}    
    }
    float valor = strtof(copia, &fimptr);
    *dadoDescript = valor / 100;
}

void roleta(Jogador *j, JogadorDescript *jd, float valorGasto){
	
	system("cls");
	char valorStr[20];
	int numero[3];
	//jd->valorRecebido -= 1.00;
	valorGasto += 1.00;
	
	printf("\nCASSINO\n");
	
	for (int i=0; i<3; i++){
		numero[i] = rand() % 6;
		printf("%d  ", numero[i]);	
	}
	if (numero[0] == numero[1] && numero[1] == numero[2]) {
		    jd->valorRecebido += 10.00;
		    printf("\n+ 10,00");
	} else if (numero[0] == numero[1] || numero[0] == numero[2] || numero[1] == numero[2]){
	    jd->valorRecebido += 3.00;
	    printf("\n+ 3,00");
	}else{
		printf("\n+ 0,00");
	}
	
	printf("\n\nJogar de novo?[s/n]\n");
	char opcao = getchar();
	getchar();
	
	if (opcao == 's'){
		roleta(j, jd, valorGasto);
	}else{
		printf("Voce ganhou: %.2f\n", jd->valorRecebido);
		desCriptografia(j->saldo, &jd->saldoDescript);
		jd->saldoDescript += jd->valorRecebido - valorGasto;
		jd->valorRecebido = 0;
		
		
		int valor = (int)(jd->saldoDescript * 100);
		sprintf(valorStr, "%d", valor);
		criptografia(valorStr);
		strcpy(j->saldo, valorStr);
		
		valorGasto = 0;
		
		system("pause");
		system("cls");
	}
}

void perfil(Jogador *j);

void entrar(Jogador *j){
	
	char nome[50], senha[16];
	
	printf("\nLOGIN\n");

	printf("Insira seu nome de usuario (letras minusculas):\n");
	fgets(nome, sizeof(nome), stdin);
	criptografia(nome);

	if (strcmp(j->nome, nome) == 0) {
		
		printf("Insira sua senha (ate 15 letras e/ou numeros):\n");
		fgets(senha, sizeof(senha), stdin);
		criptografia(senha);	
		
		system("cls");
		
		if (strcmp(j->senha, senha) == 0) {
			perfil(&jog);
		}else{
			printf("Senha incorreta\n");
			j->nome[0] = '\0';
			j->senha[0] = '\0';
			j->saldo[0] = '\0';
		}
	}else{
		printf("Usuario desconhecido\n");
		j->nome[0] = '\0';
		j->senha[0] = '\0';
		j->saldo[0] = '\0';
	}
}

void cadastrar(Jogador *j){
	float valor;
	char valorStr[20];
	
	printf("\nCADASTRAR USUARIO\n");
	printf("Insira seu nome de usuario (letras minusculas):\n");
	fgets(j->nome, sizeof(j->nome), stdin);
	criptografia(j->nome);

	printf("Insira sua senha (ate 15 letras e/ou numeros):\n");
	fgets(j->senha, sizeof(j->senha), stdin);
	criptografia(j->senha);
	
	printf("Insira seu saldo:\n");
	scanf("%f", &valor);
	getchar();
	int valorInt = (int)(valor*100);
	sprintf(valorStr, "%d", valorInt);
	criptografia(valorStr);
	strcpy(j->saldo, valorStr); 	
	
	system("cls");
	entrar(&jog);
}

void verSaldo(Jogador *j, JogadorDescript *jd){
	char senha[16];
	
	printf("Insira sua senha (ate 15 letras e/ou numeros):\n");
	fgets(senha, sizeof(senha), stdin);
	criptografia(senha);
	
	if (strcmp(j->senha, senha) == 0) {
		desCriptografia(j->saldo, &jd->saldoDescript);
		printf("Saldo: %.2f", jd->saldoDescript);
	}else{
		printf("Senha incorreta\n");
		j->nome[0] = '\0';
		j->senha[0] = '\0';
		j->saldo[0] = '\0';
	}
}
	
void perfil(Jogador *j){
	char opcao;
	int selecao;
	
	while (1) {
		system ("cls");
        printf("Jogador: %s", j->nome);
        printf("Saldo (criptografado): %s\n\n", j->saldo);
        printf("Ver saldo? [s/n]: ");
        opcao = getchar();
        getchar(); 

        if (opcao == 's') {
            verSaldo(&jog, &jogD);
        }
        
        if (j->nome[0] != '\0') {
	    	printf("\n\nJOGAR [s/n]\n Ficha 1,00\n");
			char opcao = getchar();
			getchar();
	
			if (opcao == 's'){
				roleta(&jog,&jogD, valorGasto);
			}
		}
		printf("\n\n[1]Voltar ao perfil\n");
		printf("[2]Sair\n");
		scanf("%d", &selecao);
		getchar();
		
		if (selecao == 2){
			system("cls");
			break;
		}
	}
}

int menu(){
	
	int opcao;

	while (1) {
		printf("MENU\n");
		printf("[1] Entrar\n");
		printf("[2] Cadastre-se\n");
		printf("[3] Sair\n");
		scanf("%d", &opcao);
		getchar();  
		system("cls");

		if (opcao == 1) {
			entrar(&jog);   
		} else if (opcao == 2) {
			cadastrar(&jog);  
		} else if (opcao == 3) {
			return 0;
		} else {
		}
	}
}

int main(){
	
	srand(time(NULL));
	
	menu();
		
	return 0;
}
