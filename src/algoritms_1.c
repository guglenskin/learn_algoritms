#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

typedef struct {
    double x;
    double y;
    bool visited;
    char name;
} Point;

// Функция для вычисления расстояния между двумя точками
double distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

//#################################
//#          АЛГОРИТМ             #
//#  ближайшего соседа для TSP    #
//#################################/

int find_nearest_neighbor(Point points[], int n, int current) {
    double min_dist = DBL_MAX;
    int nearest = -1;
    
    for (int i = 0; i < n; i++) {
        if (!points[i].visited && i != current) {
            double dist = distance(points[current], points[i]);
            if (dist < min_dist) {
                min_dist = dist;
                nearest = i;
            }
        }
    }
    
    return nearest;
}

void nearest_neighbor_tsp(Point points[], int n, int start_index, int route[]) {
    // Инициализация
    for (int i = 0; i < n; i++) points[i].visited = false;
    
    int current = start_index;
    points[current].visited = true;
    route[0] = current;
    
    // Основной цикл алгоритма
    for (int i = 1; i < n; i++) {
        int next = find_nearest_neighbor(points, n, current);
        if (next == -1) break;
        
        points[next].visited = true;
        route[i] = next;
        current = next;
    }
}
//#################################
//#     КОНЕЦ АЛГОРИТМА          #
//#################################

double calculate_route_length(Point points[], int n, int route[]) {
    double length = 0.0;
    for (int i = 0; i < n - 1; i++) {
        length += distance(points[route[i]], points[route[i+1]]);
    }
    return length;
}

void print_route(Point points[], int n, int route[]) {
    printf("Оптимальный маршрут: ");
    for (int i = 0; i < n; i++) {
        printf("%c", points[route[i]].name);
        if (i < n-1) printf(" → ");
    }
}

int main() {
    int n;
    printf("Введите количество точек: ");
    scanf("%d", &n);
    
    Point points[n];
    
    // Ввод координат точек
    for (int i = 0; i < n; i++) {
        points[i].name = 'A' + i;
        printf("Введите координаты точки %c (x y): ", points[i].name);
        scanf("%lf %lf", &points[i].x, &points[i].y);
        points[i].visited = false;
    }
    
    int route[n];
    int start_index = 0; // Начинаем с первой точки
    
    // Выполнение алгоритма
    nearest_neighbor_tsp(points, n, start_index, route);
    
    // Вывод результатов
    print_route(points, n, route);
    double length = calculate_route_length(points, n, route);
    printf("\nДлина маршрута: %.2f\n", length);
    
    return 0;
}