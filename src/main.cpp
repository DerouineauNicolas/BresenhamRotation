#include <main.h>
#include <rotation.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]){
    int x,y,n;
    static const float defaultAngles[] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 
                                             157.5, 180, 202.5, 225, 247.5, 270,
                                             292.5, 315, 337.5};
    int use_method = 1;

    if (argc>1){
        use_method = (int)*argv[1] - 48; 
    }
    printf(" Use method %d \n",use_method );

    clock_t start, end;
    double cpu_time_used;
    
    unsigned char *datain = stbi_load("../data/Hutton_in_the_Forest_4K.jpg", &x, &y, &n, 1);
    if(!datain)
        printf("Failed to open input file");
    
    printf("%d %d %d \n", x, y, n);

    unsigned char *dataout = NULL;
    dataout = ( unsigned char *) malloc( x*y );

    size_t angleCount = sizeof(defaultAngles) / sizeof(defaultAngles[0]);
    char outputfilename[300] = {};

    for (size_t i=0; i<angleCount; ++i)
    {
        float angle = defaultAngles[i];
        printf("Rotating %f degree \n", angle);
        start = clock();
        if (use_method == 1)
            rotate_method1(datain, dataout, x, y, x, angle);
        else{
            rotate_method2(datain, dataout, x, y, x, angle);
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("it took  %f s \n", cpu_time_used);
        sprintf (outputfilename, "out_%f.png", angle);
        stbi_write_png(outputfilename, x, y, 1, dataout, x );
    }

    return 0;
}