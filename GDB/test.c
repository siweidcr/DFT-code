#include <stdio.h>

// 演示函数参数的传递过程
// 可以使用vscdoe调试，或者gdb调试
// 编译命令 icx test1.c -o test1 -g -O0 -static

int mytest(int rdi, int rsi, int rdx, int rcx, int r8, int r9, int rsp8, int rsp9) {
    if (rdi==1){
        return rdi+rsi+rdx+rcx+r8+r9+rsp8+rsp9;
    } else {
        return 1;
    }
}

void mytest2(int *a) {
    int b[8];
    for (int i=0; i<8; i++){
        b[i] = a[i];
    }
    printf("%d\n",b[3]);
}

int main()
{
    int a[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    a[0] = 1024;
    int sum = mytest(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
    printf("%d\n",sum);
    mytest2(a);

    return 0;
}

