#include "minunit.h"
#include <lcthw/ringbuffer.h>
#include <assert.h>
#define NUM_TESTS 3

static RingBuffer *buffer = NULL;
char *tests[] = {"test1 data", "test2 data", "test3 data"};


char *test_create()
{
    buffer = RingBuffer_create(50);
    mu_assert(buffer != NULL, "Failed to create ringbuffer.");

    return NULL;
}

char *test_destroy()
{
    mu_assert(buffer != NULL, "Failed to make ringbuffer");
    RingBuffer_destroy(buffer);

    return NULL;
}

char *test_write_read()
{
    int i = 0;
    int j;
    for(i = 0, j = 0; i < NUM_TESTS; i++) {
        j = RingBuffer_write(buffer, tests[i], strlen(tests[i]));
        mu_assert(j > 0, "Wrong in writing data.");
    }

    char *data = calloc(1, strlen(tests[0]) + 1);
    for(i = 0, j = 0; i < NUM_TESTS; i++) {    
	j = RingBuffer_read(buffer, data, strlen(tests[i]));
	data[strlen(tests[i])] = '\0';
	debug("j:%d,data:%s,tests[i]:%s\n",j,data,tests[i]);
        mu_assert(*data == *tests[i], "wrong data in read from buffer.");
    }

    mu_assert(RingBuffer_available_data(buffer) == 0, "Wrong case after write and read.");

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_write_read);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
