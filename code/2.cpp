#include <stdio.h>

int main() {
    double length_mm, width_mm, height_mm;  // ���ȡ���ȡ��߶ȣ���λΪ����
    double volume_m3;  // �������λΪ������
    double buoyancy;  // ��������λΪţ��

    // ��ȡ�û�����ĳ���ߣ���λ���ף�
    printf("����������ĳ��ȣ����ף�: ");
    scanf("%lf", &length_mm);
    printf("����������Ŀ�ȣ����ף�: ");
    scanf("%lf", &width_mm);
    printf("����������ĸ߶ȣ����ף�: ");
    scanf("%lf", &height_mm);

    // ���������ת�����ȵ�λ�Ӻ��׵��ף�
    volume_m3 = (length_mm / 1000) * (width_mm / 1000) * (height_mm / 1000);

    // ���㸡����ˮ���ܶȴ�Լ��1000 kg/m3��
    buoyancy = 1000 * volume_m3 * 9.81;  // 9.81 m/s2 ���������ٶ�

    // ������
    printf("��������ĸ���Ϊ: %.2f ţ��\n", buoyancy);

    return 0;
}

