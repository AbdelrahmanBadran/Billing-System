#include <time.h>
     
clock_t start, end;
double cpu_time_used;
     
start = clock();

void main(){
for(int a=0; a<11; a++) 
{
 printf("%d", a); 
}
}

end = clock();
cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("%d", cpu_time_used)