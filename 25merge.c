#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 100

// Structure to store product details
typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
} Product;

// Function to read products from file
int readProducts(Product products[]) {
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("No product list found.\n");
        return 0;
    }

    int count = 0;
    while (count < MAX_PRODUCTS && fscanf(file, " %[^,], %f", products[count].name, &products[count].price) == 2) {
        count++;
    }

    fclose(file);
    return count;
}

// Function to write sorted products to file
void writeProducts(Product products[], int count) {
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s, %.2f\n", products[i].name, products[i].price);
    }

    fclose(file);
}

// Merge function to merge two sorted subarrays
void merge(Product products[], int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    Product *leftArray = (Product *)malloc(leftSize * sizeof(Product));
    Product *rightArray = (Product *)malloc(rightSize * sizeof(Product));

    for (int i = 0; i < leftSize; i++) 
        leftArray[i] = products[left + i];
    for (int j = 0; j < rightSize; j++) 
        rightArray[j] = products[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < leftSize && j < rightSize) {
        if (leftArray[i].price <= rightArray[j].price) {
            products[k] = leftArray[i];
            i++;
        } else {
            products[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        products[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        products[k] = rightArray[j];
        j++;
        k++;
    }

    free(leftArray);
    free(rightArray);
}

// Merge Sort function
void mergeSort(Product products[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(products, left, mid);
        mergeSort(products, mid + 1, right);
        merge(products, left, mid, right);
    }
}

// Function to add a new product and sort the list
void addProduct() {
    Product products[MAX_PRODUCTS];
    int count = readProducts(products);

    if (count >= MAX_PRODUCTS) {
        printf("Product list is full!\n");
        return;
    }

    printf("Enter product name: ");
    scanf(" %[^\n]s", products[count].name);
    printf("Enter product price: ");
    scanf("%f", &products[count].price);
    count++;

    // Sort the products by price
    mergeSort(products, 0, count - 1);

    // Write sorted products back to file
    writeProducts(products, count);

    printf("Product added and sorted successfully!\n");
}

// Function to display sorted products
void displayProducts() {
    Product products[MAX_PRODUCTS];
    int count = readProducts(products);

    if (count == 0) {
        printf("No products available.\n");
        return;
    }

    printf("\nSorted Product List (by Price):\n");
    for (int i = 0; i < count; i++) {
        printf("%s - ₹%.2f\n", products[i].name, products[i].price);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nProduct Sorting System\n");
        printf("1. Add Product\n");
        printf("2. Display Sorted Products\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
