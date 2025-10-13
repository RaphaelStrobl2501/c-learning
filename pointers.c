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

/* #include <stdio.h>
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

} */

#include <stdio.h>
#include <stdlib.h>

int sum(int größeArray, int *arr) {
    int total = 0;
    int *ptr = arr;

    for (int i = 0; i < größeArray; i++)
    {
        total += *ptr;
        ptr++;
    }

    return total;
    
}

double durchschnitt(int größeArray, int total) {
    double schnitt = (double) total / größeArray;

    return schnitt;
}

int max(int *arr, int größeArray) {
    int maximum = arr[0];

    for (int i = 0; i < größeArray; i++)
    {
        if (arr[i] > maximum)
        {
            maximum = arr[i];
        }
    }

    return maximum;
}

int main() {

    int größeArray;
    printf("Größe Array: ");
    scanf("%d", &größeArray);

    int *arr = (int*) malloc (sizeof(int) * größeArray);

    for (int i = 0; i < größeArray; i++)
    {
        printf("Welche Zahlen soll der Array enthalten: ");
        scanf("%d", &arr[i]);
    }

    int total = sum(größeArray, arr);
    double schnitt = durchschnitt(größeArray, total);
    int maximum = max(arr, größeArray);

    printf("%d\n", total);

    printf("%.2lf\n", schnitt);

    printf("%d\n", maximum);

    /* for (int i = 0; i < größeArray; i++) // print array
    {
        printf("%d\n", arr[i]);
    } */



    free(arr);
}