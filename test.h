#ifndef TEST_H
#define TEST_H

#define BUFFERTEST 4096
#define STRTEST 128

typedef struct{
    bool pass;
    char strCondition[STRTEST];
} Test;

void processTest(Test *t, char* strCond, bool condition);
void formatTest(Test t[BUFFERTEST],bool passed, bool not_passed, uint32_t size);


#endif
