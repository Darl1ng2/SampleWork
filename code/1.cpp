#include <stdio.h>

int main() {
    double area;  // ���������λΪƽ����
    double pressure_difference;  // ѹ�����λΪ��˹��
    double force;  // ��Ҫ����������λΪţ��

    // ����ˮ��5�׵�ѹ����
    pressure_difference = 0.5 * 101325;  // �������ѹ��ѹ����

    // ��ȡ�û�����ı����
    printf("������������ƽ���ף�: ");
    scanf("%lf", &area);

    // ��������
    force = pressure_difference * area;

    // ������
    printf("��ˮ��5�������Ҫ������Ϊ: %.2f ţ��\n", force);

    return 0;
}

