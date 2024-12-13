#include <stdio.h>

int main() {
    double area;  // 表面积，单位为平方米
    double pressure_difference;  // 压力差，单位为帕斯卡
    double force;  // 需要的推力，单位为牛顿

    // 设置水下5米的压力差
    pressure_difference = 0.5 * 101325;  // 半个大气压的压力差

    // 获取用户输入的表面积
    printf("请输入表面积（平方米）: ");
    scanf("%lf", &area);

    // 计算推力
    force = pressure_difference * area;

    // 输出结果
    printf("在水下5米深处，需要的推力为: %.2f 牛顿\n", force);

    return 0;
}

