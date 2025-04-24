#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dbg.h"
#include "duff.h"

int normal_copy(char *from, char *to, int count)
{
    int i = 0;

    for(i = 0; i < count; i++) {
        to[i] = from[i];
    }

    return i;
}

int duffs_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;

        switch(count % 8) {
            case 0: do { *to++ = *from++;
                        case 7: *to++ = *from++;
                        case 6: *to++ = *from++;
                        case 5: *to++ = *from++;
                        case 4: *to++ = *from++;
                        case 3: *to++ = *from++;
                        case 2: *to++ = *from++;
                        case 1: *to++ = *from++;
                    } while(--n > 0);
        }
    }

    return count;
}
int my_device_8(char *from, char *to, int count)
{
    {
	int n = (count + 7) / 8;
	switch(count % 8) {
	    case 0:
	    again: *to++ = *from++;

	    Duff(7, *to++ = *from++);
	            if(--n > 0) goto again;
	}
    }
    
    return count;
}

int my_device_16(char *from, char *to, int count)
{
    {
        int n = (count + 15) / 16;
        switch(count % 16) {
            case 0:
            again: *to++ = *from++;

            Duff(15, *to++ = *from++);
                    if(--n > 0) goto again;
        }
    }

    return count;
}

int zeds_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;

        switch(count % 8) {
            case 0:
            again: *to++ = *from++;

            case 7: *to++ = *from++;
            case 6: *to++ = *from++;
            case 5: *to++ = *from++;
            case 4: *to++ = *from++;
            case 3: *to++ = *from++;
            case 2: *to++ = *from++;
            case 1: *to++ = *from++;
                    if(--n > 0) goto again;
        }
    }

    return count;
}

int valid_copy(char *data, int count, char expects)
{
    int i = 0;
    for(i = 0; i < count; i++) {
        if(data[i] != expects) {
            log_err("[%d] %c != %c", i, data[i], expects);
            return 0;
        }
    }

    return 1;
}


int main(int argc, char *argv[])
{
    char from[10000] = {'a'};
    char to[10000] = {'c'};
    int rc = 0;
    struct timespec start, end;
    long long elapsed;

    char test[10000] = {'b'};
    memset(from, 'a', 10000);
    //speed test memset
    clock_gettime(CLOCK_MONOTONIC, &start);
    memset(test, 'x', 10000);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ( end.tv_sec - start.tv_sec )*1e9 + (end.tv_nsec - start.tv_nsec);
    printf("memset:程序运行时间为 %lld 纳秒\n", elapsed);
    check(valid_copy(test, 10000, 'x'), "test Not initialized right.");
    //speed test memmove
    clock_gettime(CLOCK_MONOTONIC, &start);
    memmove(test, from, 10000);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ( end.tv_sec - start.tv_sec )*1e9 + (end.tv_nsec - start.tv_nsec);
    printf("memmove:程序运行时间为 %lld 纳秒\n", elapsed);
    check(valid_copy(test, 10000, 'a'), "test move from 'from' Not initialized right.");
    //speed test memcpy
    clock_gettime(CLOCK_MONOTONIC, &start);
    memcpy(test, from, 10000);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ( end.tv_sec - start.tv_sec )*1e9 + (end.tv_nsec - start.tv_nsec);
    printf("momcpy:程序运行时间为 %lld 纳秒\n", elapsed);
    check(valid_copy(test, 10000, 'a'), "test copy from 'from' Not initialized right.");
 
    // setup the from to have some stuff
    memset(from, 'x', 10000);
    // set it to a failure mode
    memset(to, 'y', 10000);
    check(valid_copy(to, 10000, 'y'), "Not initialized right.");

    // use normal copy to
    clock_gettime(CLOCK_MONOTONIC, &start);
    rc = normal_copy(from, to, 10000);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ( end.tv_sec - start.tv_sec )*1e9 + (end.tv_nsec - start.tv_nsec);
    printf("normal copy:程序运行时间为 %lld 纳秒\n", elapsed);
    check(rc == 10000, "Normal copy failed: %d", rc);
    check(valid_copy(to, 10000, 'x'), "Normal copy failed.");

    // reset
    memset(to, 'y', 10000);

    // duffs version
    clock_gettime(CLOCK_MONOTONIC, &start);
    rc = duffs_device(from, to, 10000);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ( end.tv_sec - start.tv_sec )*1e9 + (end.tv_nsec - start.tv_nsec);    
    printf("duffs copy:程序运行时间为 %lld 纳秒\n", elapsed);
    check(rc == 10000, "Duff's device failed: %d", rc);
    check(valid_copy(to, 10000, 'x'), "Duff's device failed copy.");

    // reset
    memset(to, 'y', 10000);

    // zeds version
    clock_gettime(CLOCK_MONOTONIC, &start);
    rc = zeds_device(from, to, 10000);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ( end.tv_sec - start.tv_sec )*1e9 + (end.tv_nsec - start.tv_nsec);
    printf("zeds copy:程序运行时间为 %lld 纳秒\n", elapsed);
    check(rc == 10000, "Zed's device failed: %d", rc);
    check(valid_copy(to, 10000, 'x'), "Zed's device failed copy.");
    
    // reset
    memset(to, 'y', 10000);
   
    // my version 8
    clock_gettime(CLOCK_MONOTONIC, &start);
    rc = my_device_8(from, to, 10000);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ( end.tv_sec - start.tv_sec )*1e9 + (end.tv_nsec - start.tv_nsec);
    printf("my version_8:程序运行时间为 %lld 纳秒\n", elapsed);
    check(rc == 10000, "my device_8 failed: %d", rc);
    check(valid_copy(to, 10000, 'x'), "Zed's device failed copy.");

    // reset
    memset(to, 'y', 10000);
   
    // my version 16
    clock_gettime(CLOCK_MONOTONIC, &start);
    rc = my_device_16(from, to, 10000);
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ( end.tv_sec - start.tv_sec )*1e9 + (end.tv_nsec - start.tv_nsec);
    printf("my version_16:程序运行时间为 %lld 纳秒\n", elapsed);
    check(rc == 10000, "my device_16 failed: %d", rc);
    check(valid_copy(to, 10000, 'x'), "Zed's device failed copy.");

    return 0;
error:
    return 1;
}
