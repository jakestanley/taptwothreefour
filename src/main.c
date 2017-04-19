#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>

#define DIFF_MAX 20

long long int get_millis() {
    
    struct timeb timer;
    
    // returns false if fails
    ftime(&timer);

    long long int ms;
    ms = ((long long int) timer.time) * 1000ll + (long long int) timer.millitm;
    return ms;
}

int main(int argc, char** argv) {

    printf("Push 'Enter' to tap the beat");

    long long int last_ms = get_millis();

    // array to keep track of amounts
    int diff_counter = 0;
    
    long long int diffs[DIFF_MAX];
    char c = 'y';

    while(c != 'x') {

        // wait on enter press
        c = getchar();

        // figure out time passed
        long long int new_ms = get_millis();
        long long int diff_ms = new_ms - last_ms;

        // push array values back
        int i;
        for(i = (diff_counter-1); i >= 0; i--) {
            
            int adj_index = i+1;
            diffs[adj_index] = diffs[i];
        }

        // add the new diff
        diffs[0] = diff_ms;

        // increment the diff counter if 
        if(diff_counter < DIFF_MAX) {
            diff_counter++;
        }

        // calculate new average
        int diff_total = 0;

        for(int j = 0; j < diff_counter; j++) {
            diff_total += diffs[j];
        }

        float diff_avg = diff_total / diff_counter;

        // calculate bpm
        float bpm = 60000 / diff_avg;
        printf("\n%.6fbpm (%d samples over last %dms)", bpm, diff_counter, diff_total);
        
        // set last_ms for next loop iteration
        last_ms = new_ms;
    }
}

