#include <stdio.h>

int main() {
    double area_mm2;  // ���������λΪƽ������
    double area_m2;   // �����ת����ĵ�λΪƽ����
    double pressure_difference;  // ѹ�����λΪ��˹��
    double force;  // ��Ҫ����������λΪţ��

    // ����ˮ��5�׵�ѹ����
    pressure_difference = 0.5 * 101325;  // �������ѹ��ѹ����

    // ��ȡ�û�����ı������ƽ�����ף�
    printf("������������ƽ�����ף�: ");
    scanf("%lf", &area_mm2);

    // ��ƽ������ת��Ϊƽ����
    area_m2 = area_mm2 * 1e-6;

    // ��������
    force = pressure_difference * area_m2;

    // ������
    printf("��ˮ��5�������Ҫ������Ϊ: %.2f ţ��\n", force);

    return 0;
}

