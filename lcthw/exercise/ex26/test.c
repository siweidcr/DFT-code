#include <stdio.h>
#include <stdarg.h>

// 计算可变参数的和
int sum(int count, ...) {
    int total = 0;
    va_list args;
   
    // 初始化 args 以访问可变参数
    va_start(args, count);
   
    // 逐个访问可变参数
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
   
    // 清理 args
    va_end(args);
   
    return total;
}

int main() {
    printf("Sum of 1, 2, 3: %d\n", sum(3, 1, 2, 3)); // 输出 6
    printf("Sum of 4, 5, 6, 7: %d\n", sum(4, 4, 5, 6, 7)); // 输出 22
    return 0;
}
