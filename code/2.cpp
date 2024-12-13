#include <stdio.h>

int main() {
    double length_mm, width_mm, height_mm;  // 长度、宽度、高度，单位为毫米
    double volume_m3;  // 体积，单位为立方米
    double buoyancy;  // 浮力，单位为牛顿

    // 获取用户输入的长宽高（单位毫米）
    printf("请输入物体的长度（毫米）: ");
    scanf("%lf", &length_mm);
    printf("请输入物体的宽度（毫米）: ");
    scanf("%lf", &width_mm);
    printf("请输入物体的高度（毫米）: ");
    scanf("%lf", &height_mm);

    // 计算体积（转换长度单位从毫米到米）
    volume_m3 = (length_mm / 1000) * (width_mm / 1000) * (height_mm / 1000);

    // 计算浮力（水的密度大约是1000 kg/m3）
    buoyancy = 1000 * volume_m3 * 9.81;  // 9.81 m/s2 是重力加速度

    // 输出结果
    printf("给定物体的浮力为: %.2f 牛顿\n", buoyancy);

    return 0;
}

