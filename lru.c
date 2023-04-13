#include <stdio.h>
#include <stdlib.h>

#define MAX_CACHE_SIZE 5

// Structure pour représenter un élément du cache
typedef struct {
    int key;
    int value;
} CacheItem;

// Structure pour représenter le cache
typedef struct {
    CacheItem items[MAX_CACHE_SIZE];
    int count;
} LRUCache;

// Fonction pour initialiser le cache
void initCache(LRUCache *cache) {
    cache->count = 0;
}

// Fonction pour chercher une clé dans le cache et la mettre à jour en cas d'utilisation
int getFromCache(LRUCache *cache, int key) {
    // Parcourir les éléments du cache
    for (int i = 0; i < cache->count; i++) {
        // Si la clé est trouvée
        if (cache->items[i].key == key) {
            // Mettre à jour l'élément utilisé en le déplaçant au début du cache
            CacheItem temp = cache->items[i];
            for (int j = i; j > 0; j--) {
                cache->items[j] = cache->items[j - 1];
            }
            cache->items[0] = temp;
            
            return cache->items[0].value;
        }
    }
    
    return -1; // Retourner -1 si la clé n'est pas trouvée dans le cache
}

// Fonction pour ajouter une clé-valeur dans le cache
void addToCache(LRUCache *cache, int key, int value) {
    // Si le cache est plein, supprimer l'élément le moins récemment utilisé (le dernier élément)
    if (cache->count == MAX_CACHE_SIZE) {
        cache->count--;
        for (int i = MAX_CACHE_SIZE - 1; i > 0; i--) {
            cache->items[i] = cache->items[i - 1];
        }
    }
    
    // Ajouter le nouvel élément au début du cache
    cache->items[cache->count].key = key;
    cache->items[cache->count].value = value;
    cache->count++;
}

int main() {
    LRUCache cache;
    initCache(&cache);
    
    // Exemple d'utilisation du cache
    addToCache(&cache, 1, 100);
    addToCache(&cache, 2, 200);
    addToCache(&cache, 3, 300);
    
    printf("Valeur pour la clé 1 : %d\n", getFromCache(&cache, 1)); // Doit afficher 100
    printf("Valeur pour la clé 2 : %d\n", getFromCache(&cache, 2)); // Doit afficher 200
    printf("Valeur pour la clé 3 : %d\n", getFromCache(&cache, 3)); // Doit afficher 300
    printf("Valeur pour la clé 4 : %d\n", getFromCache(&cache, 4)); // Doit afficher -1 (clé non trouvée)
    
    return 0;
}
