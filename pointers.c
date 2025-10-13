/* #include <stdio.h>

int main() {

    // pointer = a "variable like" reference that holds a memory address to another variable

    int age = 21;
    int *pAge = &age;


    printf("address of age: %p\n", &age);
    printf("address of age: %p\n", pAge);


    printf("value of age %i\n", age);
} */

/* #include <stdio.h>

void swap(int *pA, int *pB) {
    int c = *pA;
    *pA = *pB;
    *pB = c;
}

int main() {
    int a;
    printf("Gib eine Zahl ein: ");
    scanf("%d", &a);
    int *pA = NULL;
    pA = &a;

    int b;
    printf("Gib eine Zahl ein: ");
    scanf("%d", &b);
    int *pB = NULL;
    pB = &b;

    printf("Before swap: a = %d, b = %d\n", a, b);

    swap(pA, pB);

    printf("After swap: a = %d, b = %d\n", a, b);
    

} */

#include <stdio.h>
#include <stdlib.h>

int sum(int *arr, int size) {

    int total = 0;
    int *ptr = arr;

    for (int i = 0; i < size; i++)
    {
        total += *ptr;
        ptr++;
        
    }
    

    return total;
}

int main() {

    int größeArray;
    printf("Größe Array: ");
    scanf("%d", &größeArray);

    int *arr = (int*) malloc (sizeof(int) * größeArray);

    for (int i = 0; i < größeArray; i++)
    {
        printf("Füge Zahlen hinzu: ");
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < größeArray; i++) {
        printf("%d\n", arr[i]);
    }

    printf("%d", sum(arr, größeArray));

    free(arr);

}