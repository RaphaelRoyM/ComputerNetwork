#include<stdio.h>
#include<string.h>

#define INF 1000 // A large number representing infinity

int main()
{
    int count, src_router, i, j, k, w, v, min;
    int cost_matrix[100][100], dist[100], last[100];
    int flag[100];

    printf("Enter the number of routers: ");
    scanf("%d", &count);

    printf("Enter the cost matrix values: \n");
    for(i = 0; i < count; i++){
        for(j = 0; j < count; j++){
            printf("%d -> %d: ", i, j);
            scanf("%d", &cost_matrix[i][j]);

            // If cost_matrix[i][j] is 0 and i != j, set it to INF (no path between them)
            if(i != j && cost_matrix[i][j] == 0) {
                cost_matrix[i][j] = INF;
            }
        }
    }

    printf("Enter the source router: ");
    scanf("%d", &src_router);

    // Initialize dist[] and last[] arrays
    for(v = 0; v < count; v++){
        flag[v] = 0;
        last[v] = src_router;
        if (v == src_router)
            dist[v] = 0; // Distance to itself is 0
        else
            dist[v] = cost_matrix[src_router][v] == INF ? INF : cost_matrix[src_router][v]; // Distance to other routers
    }

    flag[src_router] = 1;

    // Dijkstra-like algorithm to find the shortest path
    for(i = 0; i < count - 1; i++){ // Repeat until all routers are processed
        min = INF;
        for(w = 0; w < count; w++){
            if(!flag[w] && dist[w] < min){
                v = w;
                min = dist[w];
            }
        }

        flag[v] = 1; // Mark the node as processed

        for(w = 0; w < count; w++){
            if(!flag[w] && cost_matrix[v][w] != INF && dist[v] + cost_matrix[v][w] < dist[w]){
                dist[w] = dist[v] + cost_matrix[v][w];
                last[w] = v;
            }
        }
    }

    // Print the shortest path and the corresponding cost for each router
    for(i = 0; i < count; i++){
        if(i == src_router){
            continue; // Skip the source router
        }

        printf("\n%d ==> %d\nPath taken: %d", src_router, i, i);
        w = i;
        while(w != src_router){
            printf("<--%d", last[w]);
            w = last[w];
        }

        //printf("<--%d", src_router); 
        // Finally, print the source router
        printf("\nShortest path cost: %d\n\n", dist[i]);
    }

    // Print the dist[] array (minimum distances from source router to all other routers)
    printf("Shortest distances from router %d:\n", src_router);
    for(int l = 0; l < count; l++) {
        if (dist[l] == INF)
            printf("Router %d is unreachable.\n", l);
        else
            printf("Distance to router %d: %d\n", l, dist[l]);
    }

    return 0;
}

