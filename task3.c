#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    int64_t a = 1234567;
    int64_t b = 9876;

  
	int64_t result = a * b; // Calculer le résultat à l'intérieur de la boucle
	printf("Multiplication: %" PRId64 " * %" PRId64 " = %" PRId64 "\n", a, b, result);
    
    
    printf("\n");

    return 0; // Ajout d'un return 0 pour indiquer une fin de programme réussie
}