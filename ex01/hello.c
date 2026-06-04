#include <stdio.h>

int main() {
	printf("Hello World\n");
	char name[100];  // 存储用户输入的字符串（最多100个字符）
    	printf("请输入一些内容：");
    	scanf("%s", name);  // 读取用户输入的字符串（以空格或回车结束）
    	printf("你输入的内容是：%s\n", name);
    return 0;
}