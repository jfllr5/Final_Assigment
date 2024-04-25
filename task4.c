#include <stdio.h>

int list[50] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
    39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50
};
int element = 25;



#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    int left = 0;
    int right = sizeof(list) / sizeof(list[0]);
    int mid;

  
        while (left <= right) {
            mid = (left + right) / 2;

            if (list[mid] < element) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (list[mid] != element) {
            printf("Element %d not found\n", element);
        } else {
            printf("Element %d found\n", element);
        }
    
    
    printf("\n");

    return 0; // Ajout d'un return 0 pour indiquer une fin de programme réussie
}